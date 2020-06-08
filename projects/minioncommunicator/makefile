#minioncommunicator makefile

#flags
CC=g++   
CFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -g -I$(INC)
RFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC) 
LDFLAGS_DEBUG=-L../lib/libdebug -Wl,-rpath=../lib/libdebug
LDFLAGS_DEPEND=-L../lib/libdebug -Wl,-rpath,'$$ORIGIN'
LDFLAGS_RELEASE=-L$(DIR_RELEASE) -Wl,-rpath,'$$ORIGIN'

#minioncommunicator names
SRC=minioncommunicator.cpp
SRC_TEST=minioncommunicator_test.cpp 
TARGET_DEBUG=./minioncommunicator
TARGET_RELEASE=./outrelease/minioncommunicator
OBJ_DEBUG=./minioncommunicator.o
OBJ_RELEASE=./objrelease/minioncommunicator.o
DIR_DEBUG=../lib/libdebug/
DIR_RELEASE=../lib/librelease/
INC=../include/

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libminioncommunicator.so 

release: $(DIR_RELEASE)libminioncommunicator.so 

all: $(DIR_DEBUG)libminioncommunicator.so $(DIR_RELEASE)libminioncommunicator.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(SRC_TEST) 
	$(CC) $(CFLAGS) -o $@ $(SRC_TEST) $(LDFLAGS_DEBUG) -lminioncommunicator 
	
#Debug SO
$(DIR_DEBUG)libminioncommunicator.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $< $(LDFLAGS_DEPEND) -lreactor $(LDFLAGS_DEPEND) -lUDPClient

#Debug Object
$(OBJ_DEBUG): $(SRC) $(INC)minioncommunicator.hpp     
	$(CC) $(CFLAGS) -c -fpic -o $@ $<

#Release Object
$(OBJ_RELEASE): $(SRC) $(INC)minioncommunicator.hpp
	$(CC) $(RFLAGS) -c -fpic -o $@ $<

.PHONY: clean
clean: 
	rm $(OBJ_DEBUG) $(OBJ_RELEASE) $(TARGET_DEBUG) 
