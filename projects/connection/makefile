#connection makefile

#flags
CC=g++   
CFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -g -I$(INC)
RFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC) 
LDFLAGS_DEBUG=-L../lib/libdebug -Wl,-rpath=../../lib/libdebug
LDFLAGS_RELEASE=-L$(DIR_RELEASE) -Wl,-rpath,'$$ORIGIN'

#connection names
SRC=connection.cpp
SRC_TEST=connection_test.cpp
TARGET_DEBUG=./outdebug/connection
TARGET_RELEASE=./outrelease/connection
OBJ_DEBUG=./objdebug/connection.o
OBJ_RELEASE=./objrelease/connection.o
DIR_DEBUG=../lib/libdebug/
DIR_RELEASE=../lib/librelease/
INC=../include/

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libconnection.so 

release: $(DIR_RELEASE)libconnection.so 

all: $(DIR_DEBUG)libconnection.so $(DIR_RELEASE)libconnection.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)libconnection.so $(SRC_TEST) 
	$(CC) $(CFLAGS) -o $@ $(SRC_TEST) $(LDFLAGS_DEBUG) -lconnection 

#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)libconnection.so $(SRC_TEST) 
	$(CC) $(RFLAGS) $(LDFLAGS_RELEASE) -o $@ $(SRC_TEST) -lconnection  

#Debug SO
$(DIR_DEBUG)libconnection.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $< -L$(DIR_DEBUG) -Wl,-rpath,'$$ORIGIN' -lUDPServer -L$(DIR_DEBUG) -Wl,-rpath,'$$ORIGIN' -lmessage
	
#Release SO
$(DIR_RELEASE)libconnection.so: $(OBJ_RELEASE)
	$(CC) $(RFLAGS) -shared -o $@ $< 
	
#Debug Object
$(OBJ_DEBUG): $(SRC) $(INC)connection.hpp    
	$(CC) $(CFLAGS) -c -fpic -o $@ $<

#Release Object
$(OBJ_RELEASE): $(SRC) $(INC)connection.hpp
	$(CC) $(RFLAGS) -c -fpic -o $@ $<

.PHONY: clean
clean: 
	rm $(OBJ_DEBUG) $(OBJ_RELEASE) $(TARGET_DEBUG) 
