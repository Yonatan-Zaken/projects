#thread_pool makefile

#flags
CC=g++   
CFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -g -I$(INC) 
RFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC) 
LDFLAGS_DEBUG=-L../lib/libdebug -Wl,-rpath=../lib/libdebug
LDFLAGS_RELEASE=-L$(DIR_RELEASE) -Wl,-rpath,'$$ORIGIN'

#thread_pool names
SRC=thread_pool.cpp
SRC_TEST=threadpool_test.cpp
SRC_TEST_TWO=tests.cpp 
TARGET_DEBUG=./thread_pool
TARGET_RELEASE=./outrelease/thread_pool
OBJ_DEBUG=./objdebug/thread_pool.o
OBJ_RELEASE=./objrelease/thread_pool.o
DIR_DEBUG=../lib/libdebug/
DIR_RELEASE=../lib/librelease/
INC=../include/

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libthread_pool.so 

release: $(DIR_RELEASE)libthread_pool.so 

all: $(DIR_DEBUG)libthread_pool.so $(DIR_RELEASE)libthread_pool.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)libthread_pool.so $(SRC_TEST_TWO) $(SRC_TEST) 
	$(CC) $(CFLAGS) -o $@ $(SRC_TEST_TWO) $(SRC_TEST)  $(LDFLAGS_DEBUG) -lthread_pool -lboost_thread -lboost_chrono -lboost_system 

#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)libthread_pool.so $(SRC_TEST) 
	$(CC) $(RFLAGS) -o $@ $(SRC_TEST) $(LDFLAGS_RELEASE) -lthread_pool

#Debug SO
$(DIR_DEBUG)libthread_pool.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $< $(LDFLAGS_DEBUG) -llogger

#Release SO
$(DIR_RELEASE)libthread_pool.so: $(OBJ_RELEASE) 
	$(CC) $(RFLAGS) -shared -o $@ $< $(LDFLAGS_DEBUG) 

#Debug Object
$(OBJ_DEBUG): $(SRC) $(INC)thread_pool.hpp    
	$(CC) $(CFLAGS) -c -fpic -o $@ $<

#Release Object
$(OBJ_RELEASE): $(SRC) $(INC)thread_pool.hpp
	$(CC) $(RFLAGS) -c -fpic -o $@ $<

.PHONY: clean
clean: 
	rm $(OBJ_DEBUG) $(OBJ_RELEASE) $(TARGET_DEBUG) 
