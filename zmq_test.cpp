#include <zmq.hpp>
#include <string>
#include <iostream>


#include "external/async_linked_list_buffer.cpp"
#include "external/tcp_session.cpp"
#include "headers/observable.hpp"
#include "headers/session.hpp"

sessions::session* s1;

buffers::message_buffer* asbuff_1;
buffers::message_buffer* asbuff_2;
buffers::message_buffer* asbuff_3;
buffers::message_buffer* asbuff_4;

class in_getter : public observer<sessions::session_data>
{
public:
    in_getter() {};
    ~in_getter() {};

    virtual void update(sessions::session_data s) const
    {
        auto buff = s1->get_message_in(s.buffer);

        std::cout << s.buffer->buffer_name << ": ";
        std::cout << buff.to_string() << std::endl;
    }
};

int client()
{
    zmq::context_t context (2);
    zmq::socket_t sock (context, ZMQ_DEALER);
    sock.connect("tcp://localhost:50600");
     
    int request_nbr;
    for (request_nbr = 0; request_nbr != 100000; request_nbr++) 
    {
        zmq::message_t request(7);
        memset (request.data (), '-', 6);
        std::cout << "Fenrir" << static_cast<char *>(request.data ()) << std::endl;

        sock.send ( &request, 0);
         
        // zmq::message_t reply;
        // sock.recv ( &reply, 0);
        // printf ("Received World %d\n", request_nbr);
    }
    sock.close();
    return 0;
}

int server () 
{
    s1 = new sessions::tcp_session;

    asbuff_1 = new buffers::async_linked_list_buffer;
    asbuff_2 = new buffers::async_linked_list_buffer;
    asbuff_3 = new buffers::async_linked_list_buffer;
    asbuff_4 = new buffers::async_linked_list_buffer;

	zmq::context_t context (1);
	zmq::socket_t socket (context, ZMQ_STREAM);
	socket.bind ("tcp://*:50600");
	in_getter n_in_g;

    s1->set_name(std::string("S_1"));

    s1->attach(IN, dynamic_cast<observer<sessions::session_data>*>(&n_in_g));

    s1->register_mbuffer(asbuff_1,"b1");
    s1->register_mbuffer(asbuff_2,"b2");
    s1->register_mbuffer(asbuff_3,"b3");
    s1->register_mbuffer(asbuff_4,"b4");

	while (true) {
		zmq::message_t request;
		socket.recv (&request);
        msg_t message(request.data(), request.size());
        // auto bdata = s1->buffer_for_connection("b1");

        auto bdata = s1->get_free_bdata();

        s1->put_message_in(message, bdata);
	}

	return 0;
}

int main(int argc, char *argv[])
{
    if (argc > 1)
        return client();
    return server();
}