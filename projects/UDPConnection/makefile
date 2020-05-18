#UDPConnection makefile

#flags
CC=g++   
CFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -g -I$(INC)
RFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC) 
LDFLAGS_DEBUG=-L../lib/libdebug -Wl,-rpath=../../lib/libdebug
LDFLAGS_RELEASE=-L$(DIR_RELEASE) -Wl,-rpath,'$$ORIGIN'

#UDPConnection names
SRC=UDPConnection.cpp
SRC_TEST=UDPConnection_test.cpp
TARGET_DEBUG=./outdebug/UDPConnection
TARGET_RELEASE=./outrelease/UDPConnection
OBJ_DEBUG=./objdebug/UDPConnection.o
OBJ_RELEASE=./objrelease/UDPConnection.o
DIR_DEBUG=../lib/libdebug/
DIR_RELEASE=../lib/librelease/
INC=../include/

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libUDPConnection.so 

release: $(DIR_RELEASE)libUDPConnection.so 

all: $(DIR_DEBUG)libUDPConnection.so $(DIR_RELEASE)libUDPConnection.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)libUDPConnection.so $(SRC_TEST) 
	$(CC) $(CFLAGS) -o $@ $(SRC_TEST) $(LDFLAGS_DEBUG) -lUDPConnection -DLOG_LEVEL=4
	
#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)libUDPConnection.so $(SRC_TEST) 
	$(CC) $(RFLAGS) $(LDFLAGS_RELEASE) -o $@ $(SRC_TEST) -lUDPConnection  

#Debug SO
$(DIR_DEBUG)libUDPConnection.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $< -L$(DIR_DEBUG) -Wl,-rpath,'$$ORIGIN' -lsocket
	
#Release SO
$(DIR_RELEASE)libUDPConnection.so: $(OBJ_RELEASE)
	$(CC) $(RFLAGS) -shared -o $@ $< 
	
#Debug Object
$(OBJ_DEBUG): $(SRC) $(INC)UDPConnection.hpp    
	$(CC) $(CFLAGS) -c -fpic -o $@ $<

#Release Object
$(OBJ_RELEASE): $(SRC) $(INC)UDPConnection.hpp
	$(CC) $(RFLAGS) -c -fpic -o $@ $<

.PHONY: clean
clean: 
	rm $(OBJ_DEBUG) $(OBJ_RELEASE) $(TARGET_DEBUG) 
