#UDPServer makefile

#flags
CC=g++   
CFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -g -I$(INC)
RFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC) 
LDFLAGS_DEBUG=-L../lib/libdebug -Wl,-rpath=../../lib/libdebug
LDFLAGS_RELEASE=-L$(DIR_RELEASE) -Wl,-rpath,'$$ORIGIN'

#UDPServer names
SRC=UDPServer.cpp
SRC_TEST=UDPServer_test.cpp
TARGET_DEBUG=./outdebug/UDPServer
TARGET_RELEASE=./outrelease/UDPServer
OBJ_DEBUG=./objdebug/UDPServer.o
OBJ_RELEASE=./objrelease/UDPServer.o
DIR_DEBUG=../lib/libdebug/
DIR_RELEASE=../lib/librelease/
INC=../include/

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libUDPServer.so 

release: $(DIR_RELEASE)libUDPServer.so 

all: $(DIR_DEBUG)libUDPServer.so $(DIR_RELEASE)libUDPServer.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)libUDPServer.so $(SRC_TEST) 
	$(CC) $(CFLAGS) -o $@ $(SRC_TEST) $(LDFLAGS_DEBUG) -lUDPServer -DLOG_LEVEL=4
	
#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)libUDPServer.so $(SRC_TEST) 
	$(CC) $(RFLAGS) $(LDFLAGS_RELEASE) -o $@ $(SRC_TEST) -lUDPServer  

#Debug SO
$(DIR_DEBUG)libUDPServer.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $< -L$(DIR_DEBUG) -Wl,-rpath,'$$ORIGIN' -lsocket
	
#Release SO
$(DIR_RELEASE)libUDPServer.so: $(OBJ_RELEASE)
	$(CC) $(RFLAGS) -shared -o $@ $< 
	
#Debug Object
$(OBJ_DEBUG): $(SRC) $(INC)UDPServer.hpp    
	$(CC) $(CFLAGS) -c -fpic -o $@ $<

#Release Object
$(OBJ_RELEASE): $(SRC) $(INC)UDPServer.hpp
	$(CC) $(RFLAGS) -c -fpic -o $@ $<

.PHONY: clean
clean: 
	rm $(OBJ_DEBUG) $(OBJ_RELEASE) $(TARGET_DEBUG) 
