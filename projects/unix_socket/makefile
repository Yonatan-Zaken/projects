#unixsocket makefile

#flags
CC=g++   
CFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -g -I$(INC)
RFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC) 
LDFLAGS_DEBUG=-L../lib/libdebug -Wl,-rpath=../lib/libdebug
LDFLAGS_RELEASE=-L$(DIR_RELEASE) -Wl,-rpath,'$$ORIGIN'

#unixsocket names
SRC=unixsocket.cpp
SRC_TEST=unixsocket_test.cpp 
TARGET_DEBUG=./unixsocket
TARGET_RELEASE=./outrelease/unixsocket
OBJ_DEBUG=./unixsocket.o
OBJ_RELEASE=./objrelease/unixsocket.o
DIR_DEBUG=../lib/libdebug/
DIR_RELEASE=../lib/librelease/
INC=../include/

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libunixsocket.so 

release: $(DIR_RELEASE)libunixsocket.so 

all: $(DIR_DEBUG)libunixsocket.so $(DIR_RELEASE)libunixsocket.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(SRC_TEST) 
	$(CC) $(CFLAGS) -o $@ $(SRC_TEST) $(LDFLAGS_DEBUG) -lunixsocket 
	
#Debug SO
$(DIR_DEBUG)libunixsocket.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $< -L../lib/libdebug -Wl,-rpath,'$$ORIGIN' -llogger
	  
#Debug Object
$(OBJ_DEBUG): $(SRC) $(INC)unixsocket.hpp     
	$(CC) $(CFLAGS) -c -fpic -o $@ $<

#Release Object
$(OBJ_RELEASE): $(SRC) $(INC)unixsocket.hpp
	$(CC) $(RFLAGS) -c -fpic -o $@ $<

.PHONY: clean
clean: 
	rm $(OBJ_DEBUG) $(OBJ_RELEASE) $(TARGET_DEBUG) 
