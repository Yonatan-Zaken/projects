#NBDCommunicator makefile

#flags
CC=g++   
CFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -g -I$(INC)
RFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC) 
LDFLAGS_DEBUG=-L../lib/libdebug -Wl,-rpath=../lib/libdebug
LDFLAGS_DEPEND=-L../lib/libdebug -Wl,-rpath,'$$ORIGIN'
LDFLAGS_RELEASE=-L$(DIR_RELEASE) -Wl,-rpath,'$$ORIGIN'

#NBDCommunicator names
SRC=NBDCommunicator.cpp
SRC_TEST=NBDCommunicator_test.cpp 
TARGET_DEBUG=./NBDCommunicator
TARGET_RELEASE=./outrelease/NBDCommunicator
OBJ_DEBUG=./NBDCommunicator.o
OBJ_RELEASE=./objrelease/NBDCommunicator.o
DIR_DEBUG=../lib/libdebug/
DIR_RELEASE=../lib/librelease/
INC=../include/

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libNBDCommunicator.so 

release: $(DIR_RELEASE)libNBDCommunicator.so 

all: $(DIR_DEBUG)libNBDCommunicator.so $(DIR_RELEASE)libNBDCommunicator.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(SRC_TEST) 
	$(CC) $(CFLAGS) -o $@ $(SRC_TEST) $(LDFLAGS_DEBUG) -lNBDCommunicator 
	
#Debug SO
$(DIR_DEBUG)libNBDCommunicator.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $< $(LDFLAGS_DEPEND) -lreactor $(LDFLAGS_DEPEND) -lunixsocket
	  
#Debug Object
$(OBJ_DEBUG): $(SRC) $(INC)NBDCommunicator.hpp     
	$(CC) $(CFLAGS) -c -fpic -o $@ $<

#Release Object
$(OBJ_RELEASE): $(SRC) $(INC)NBDCommunicator.hpp
	$(CC) $(RFLAGS) -c -fpic -o $@ $<

.PHONY: clean
clean: 
	rm $(OBJ_DEBUG) $(OBJ_RELEASE) $(TARGET_DEBUG) 
