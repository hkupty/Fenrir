CC=clang++
CC_VER=3.3
CCFLAGS=-std=c++11
CFLAGS= $(CCFLAGS) -O3 -Wall -fslp-vectorize -march=native -mtune=native
INCLUDE=-I/usr/include 
LFLAGS= $(CCFLAGS) -L/usr/libs -ldl -lboost_system -lboost_thread -llua -pthread


MKDIR=mkdir -p
CP=cp *.lua 

STATIC= lua_container.cpp default_config.cpp di_container.cpp exec_environment.cpp run.cpp
STATIC_FOLDER=core

SHARED=default_rulemgr dynamic_rulemgr basic_session_manager tcp_session
SHARED_FOLDER=external

BUILD=build
TBUILD=$(BUILD)/temp

OBJECTS=$(STATIC:%.cpp=$(TBUILD)/%.cpp.o)

APP_NAME=Fenrir


all:core shared

core: build_dirs $(STATIC) 
	$(CC) $(LFLAGS) -O4 $(OBJECTS) -o $(BUILD)/$(APP_NAME)
	$(CP) $(BUILD)

shared: $(SHARED)

$(STATIC):
	$(CC) $(CFLAGS) -c $(INCLUDE) $(STATIC_FOLDER)/$@ -o $(TBUILD)/$@.o

build_dirs:
	${MKDIR} ${BUILD}
	${MKDIR} ${TBUILD}
	
$(SHARED): 
	$(CC) $(CFLAGS) -shared -fPIC $(SHARED_FOLDER)/$@.cpp -o $(BUILD)/$@.so
