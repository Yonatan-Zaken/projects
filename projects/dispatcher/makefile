#dispatcher makefile

#flags
CC=g++   
CFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -g -I$(INC)
RFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC) 
LDFLAGS_DEBUG=-L../lib/libdebug -Wl,-rpath=../lib/libdebug
LDFLAGS_RELEASE=-L$(DIR_RELEASE) -Wl,-rpath,'$$ORIGIN'

#dispatcher names
SRC=dispatcher.cpp
SRC_TEST=dispatcher_test.cpp tests.cpp
TARGET_DEBUG=./dispatcher
TARGET_RELEASE=./outrelease/dispatcher
OBJ_DEBUG=./dispatcher.o
OBJ_RELEASE=./objrelease/dispatcher.o
DIR_DEBUG=../lib/libdebug/
DIR_RELEASE=../lib/librelease/
INC=../include/

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libdispatcher.so 

release: $(DIR_RELEASE)libdispatcher.so 

all: $(DIR_DEBUG)libdispatcher.so $(DIR_RELEASE)libdispatcher.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(SRC_TEST) 
	$(CC) $(CFLAGS) $(LDFLAGS_DEBUG) -o $@ $(SRC_TEST) -llogger -lboost_system -lboost_thread -pthread
	
#Debug SO
$(DIR_DEBUG)libdispatcher.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $< $(LDFLAGS_DEBUG) 
	  
#Debug Object
$(OBJ_DEBUG): $(SRC) $(INC)dispatcher.hpp    
	$(CC) $(CFLAGS) -c -fpic -o $@ $<

#Release Object
$(OBJ_RELEASE): $(SRC) $(INC)dispatcher.hpp
	$(CC) $(RFLAGS) -c -fpic -o $@ $<

.PHONY: clean
clean: 
	rm $(OBJ_DEBUG) $(OBJ_RELEASE) $(TARGET_DEBUG) 
