#servicelocator makefile

#flags
CC=g++   
CFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -g -I$(INC)
RFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC) 
LDFLAGS_DEBUG=-L../lib/libdebug -Wl,-rpath=../lib/libdebug
LDFLAGS_DEPEND=-L../lib/libdebug -Wl,-rpath,'$$ORIGIN'
LDFLAGS_RELEASE=-L$(DIR_RELEASE) -Wl,-rpath,'$$ORIGIN'

#servicelocator names
SRC=servicelocator.cpp
SRC_TEST=servicelocator_test.cpp
TARGET_DEBUG=./servicelocator
TARGET_RELEASE=./outrelease/servicelocator
DIR_DEBUG=../lib/libdebug/
DIR_RELEASE=../lib/librelease/
INC=../include/

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libservicelocator.so 

release: $(DIR_RELEASE)libservicelocator.so 

all: $(DIR_DEBUG)libservicelocator.so $(DIR_RELEASE)libservicelocator.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(SRC_TEST) 
	$(CC) $(CFLAGS) -o $@ $(SRC_TEST) $(LDFLAGS_DEBUG) -lreactor $(LDFLAGS_DEBUG) -llogger $(LDFLAGS_DEBUG) -lthread_pool -lboost_system  -lboost_thread -pthread -lboost_chrono

#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)libservicelocator.so $(SRC_TEST) 
	$(CC) $(RFLAGS) $(LDFLAGS_RELEASE) -o $@ $(SRC_TEST) -lservicelocator  

.PHONY: clean
clean: 
	rm $(TARGET_DEBUG) 
