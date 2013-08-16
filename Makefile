CC=clang++
CC_VER=3.3
_FLAGS=-std=c++11
CFLAGS= $(_FLAGS) -O3 -Wall -fslp-vectorize -march=native -mtune=native
INCLUDE=-I/usr/include 
LFLAGS= $(_FLAGS) -L/usr/libs -ldl -lboost_system -lboost_thread -llua -pthread


MKDIR=mkdir -p
CP=cp *.lua 

STATIC= lua_container.cpp default_config.cpp di_container.cpp exec_environment.cpp run.cpp
STATIC_FOLDER=core

TEST=buffer_tester 

BOOST_SAMPLE=mirror_boost_asio_sample

SHARED=default_rulemgr dynamic_rulemgr basic_session_manager tcp_session async_linked_list_buffer
SHARED_FOLDER=external

BUILD=build
TBUILD=$(BUILD)/temp

OBJECTS=$(STATIC:%.cpp=$(TBUILD)/%.cpp.o)

APP_NAME=Fenrir


all:core shared test

core: build_dirs $(STATIC) 
	$(CC) $(LFLAGS) -O4 $(OBJECTS) -o $(BUILD)/$(APP_NAME)
	$(CP) $(BUILD)

build_dirs:
	${MKDIR} ${BUILD}
	${MKDIR} ${TBUILD}

$(STATIC):
	$(CC) $(CFLAGS) -c $(INCLUDE) $(STATIC_FOLDER)/$@ -o $(TBUILD)/$@.o

shared: $(SHARED)

$(SHARED): 
	$(CC) $(CFLAGS) -shared -fPIC $(SHARED_FOLDER)/$@.cpp -o $(BUILD)/$@.so

test: $(TEST)

$(TEST):
	$(CC) $(CFLAGS) -ldl -O3 $@.cpp -o $(BUILD)/$@
	
boost: $(BOOST_SAMPLE)

$(BOOST_SAMPLE):
	$(CC) $(CFLAGS) -lboost_system -lboost_thread $@.cpp -o $(BUILD)/$@