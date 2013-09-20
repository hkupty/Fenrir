#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <ev++.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <resolv.h>
#include <errno.h>
#include <list>

#include "external/async_linked_list_buffer.cpp"
#include "external/tcp_session.cpp"
#include "headers/observable.hpp"
#include "headers/session.hpp"


sessions::session* s1;

buffers::message_buffer* asbuff_1;
buffers::message_buffer* asbuff_2;
buffers::message_buffer* asbuff_3;
buffers::message_buffer* asbuff_4;

struct Buffer {
    char       *data;
    ssize_t len;
    ssize_t pos;

    Buffer(const char *bytes, ssize_t nbytes) {
        pos = 0;
        len = nbytes;
        data = new char[nbytes];
        memcpy(data, bytes, nbytes);
    }

    virtual ~Buffer() {
        delete [] data;
    }

    char *dpos() {
        return data + pos;
    }

    ssize_t nbytes() {
        return len - pos;
    }
};
  
//
//   A single instance of a non-blocking Echo handler
//
class EchoInstance {
private:
    ev::io                  io;
    static int              total_clients;
    int                     sfd;
    sessions::buffer_data*  bdata;    

    // Buffers that are pending write
    std::list<Buffer*>      write_queue;

    // Generic callback
    void callback(ev::io &watcher, int revents) {
        if (EV_ERROR & revents) {
                perror("got invalid event");
                return;
        }

        if (revents & EV_READ) 
                read_cb(watcher);

        if (revents & EV_WRITE) 
                write_cb(watcher);

        if (write_queue.empty()) {
                io.set(ev::READ);
        } else {
                io.set(ev::READ|ev::WRITE);
        }
    }

    // Socket is writable
    void write_cb(ev::io &watcher) {
        if (write_queue.empty()) {
                io.set(ev::READ);
                return;
        }

        Buffer* buffer = write_queue.front();
                  
        ssize_t written = write(watcher.fd, buffer->dpos(), buffer->nbytes());
        if (written < 0) {
                perror("read error");
                return;
        }

        buffer->pos += written;
        if (buffer->nbytes() == 0) {
                write_queue.pop_front();
                delete buffer;
        }
    }

    // Receive message from client socket
    void read_cb(ev::io &watcher) {
        char       buffer[1024];

        ssize_t   nread = recv(watcher.fd, buffer, sizeof(buffer), 0);

        if (nread < 0) {
                perror("read error");
                return;
        }

        if (nread == 0) {
                // Gack - we're deleting ourself inside of ourself!
                delete this;
        } else {
                // Send message bach to the client
                //write_queue.push_back(new Buffer(buffer, nread));
                s1->put_message_in(buffer, bdata);

        }
    }

public:
    EchoInstance(int s, sessions::buffer_data* _bdata) : sfd(s), bdata(_bdata) {
        fcntl(s, F_SETFL, fcntl(s, F_GETFL, 0) | O_NONBLOCK); 

        printf("Got connection\n");
        total_clients++;

        io.set<EchoInstance, &EchoInstance::callback>(this);

        io.start(s, ev::READ);
}

// effictivly a close and a destroy
    virtual ~EchoInstance() {
        // Stop and free watcher if client socket is closing
        io.stop();

        delete bdata;

        close(sfd);

        printf("%d client(s) connected.\n", --total_clients);
    }
};
  
class EchoServer {
private:
        ev::io           io;
        ev::sig         sio;
        int               s;

        std::vector<EchoInstance*> eiv;
  
public:
 
    void io_accept(ev::io &watcher, int revents) {
        if (EV_ERROR & revents) {
                perror("got invalid event");
                return;
        }

        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);

        int client_sd = accept(watcher.fd, (struct sockaddr *)&client_addr, &client_len);

        if (client_sd < 0) {
                perror("accept error");
                return;
        }

        EchoInstance *client = new EchoInstance(client_sd, s1->get_free_bdata());

        eiv.push_back(client);
    }
  
    static void signal_cb(ev::sig &signal, int revents) {
        signal.loop.break_loop();
    }

    EchoServer(int port) {
        printf("Listening on port %d\n", port);

        struct sockaddr_in addr;

        s = socket(PF_INET, SOCK_STREAM, 0);

        addr.sin_family = AF_INET;
        addr.sin_port     = htons(port);
        addr.sin_addr.s_addr = INADDR_ANY;

        if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
                perror("bind");
        }

        fcntl(s, F_SETFL, fcntl(s, F_GETFL, 0) | O_NONBLOCK); 

        listen(s, 5);

        io.set<EchoServer, &EchoServer::io_accept>(this);
        io.start(s, ev::READ);

        sio.set<&EchoServer::signal_cb>();
        sio.start(SIGINT);
    }
      
    virtual ~EchoServer() {
        std::cout << "Ending Server" << std::endl;
        shutdown(s, SHUT_RDWR);
        close(s);

        for (std::vector<EchoInstance*>::iterator i = eiv.begin(); i != eiv.end(); ++i)
        {
            delete *i;
        }
    }
};

int EchoInstance::total_clients = 0;


class in_getter : public observer<sessions::session_data>
{
public:
    in_getter() {};
    ~in_getter() {};

    virtual void update(sessions::session_data s) const
    {
        std::cout << "Got Notification.. updating.." << std::endl;
        std::string msg = std::string(s1->get_message_in(s.buffer));

        std::cout << msg << std::endl;
    }
};

int main(int argc, char **argv) 
{        
        std::cout << "Preparing" << std::endl;

        s1 = new sessions::tcp_session;

        asbuff_1 = new buffers::async_linked_list_buffer;
        asbuff_2 = new buffers::async_linked_list_buffer;
        asbuff_3 = new buffers::async_linked_list_buffer;
        asbuff_4 = new buffers::async_linked_list_buffer;

        in_getter n_in_g;

        std::cout << "Registering" << std::endl;

        s1->set_name(std::string("S_1"));

        s1->attach(IN, dynamic_cast<observer<sessions::session_data>*>(&n_in_g));

        s1->register_mbuffer(asbuff_1,"b1");
        s1->register_mbuffer(asbuff_2,"b2");
        s1->register_mbuffer(asbuff_3,"b3");
        s1->register_mbuffer(asbuff_4,"b4");

        std::cout << "Starting" << std::endl;

        std::cout << "Done!" << std::endl;

        int         port = 50600;
  
        if (argc > 1)
                port = atoi(argv[1]);
                  
        ev::default_loop       loop;
        EchoServer       echo(port);
  
        loop.run(0);

        delete asbuff_1;
        delete asbuff_2;
        delete asbuff_3;
        delete asbuff_4;

        return 0;
}