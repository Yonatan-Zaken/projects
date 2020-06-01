#command makefile

#flags
CC=g++   
CFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -g -I$(INC)
RFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC) 
LDFLAGS_DEBUG=-L../lib/libdebug -Wl,-rpath=../lib/libdebug
LDFLAGS_RELEASE=-L$(DIR_RELEASE) -Wl,-rpath,'$$ORIGIN'

#command names
SRC=command.cpp
SRC_TEST=command_test.cpp
TARGET_DEBUG=./command
TARGET_RELEASE=./outrelease/command
OBJ_DEBUG=./command.o
OBJ_RELEASE=./objrelease/command.o
DIR_DEBUG=../lib/libdebug/
DIR_RELEASE=../lib/librelease/
INC=../include/

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libcommand.so 

release: $(DIR_RELEASE)libcommand.so 

all: $(DIR_DEBUG)libcommand.so $(DIR_RELEASE)libcommand.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)libcommand.so $(SRC_TEST) 
	$(CC) $(CFLAGS) $(LDFLAGS_DEBUG) -o $@ $(SRC_TEST) -lcommand -lmessage
	
#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)libcommand.so $(SRC_TEST) 
	$(CC) $(RFLAGS) $(LDFLAGS_RELEASE) -o $@ $(SRC_TEST) -lcommand  

#Debug SO
$(DIR_DEBUG)libcommand.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $< 
	  
#Release SO
$(DIR_RELEASE)libcommand.so: $(OBJ_RELEASE) 
	$(CC) $(RFLAGS) -shared -o $@ $< $(LDFLAGS_DEBUG) -lmessage
	
#Debug Object
$(OBJ_DEBUG): $(SRC) $(INC)command.hpp    
	$(CC) $(CFLAGS) -c -fpic -o $@ $<

#Release Object
$(OBJ_RELEASE): $(SRC) $(INC)command.hpp
	$(CC) $(RFLAGS) -c -fpic -o $@ $<

.PHONY: clean
clean: 
	rm $(OBJ_DEBUG) $(OBJ_RELEASE) $(TARGET_DEBUG) 
