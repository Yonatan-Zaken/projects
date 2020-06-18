#master makefile

#flags
CC=g++   
CFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -g -I$(INC)
RFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC) 
LDFLAGS_DEBUG=-L../lib/libdebug -Wl,-rpath=../lib/libdebug
LDFLAGS_DEPEND=-L../lib/libdebug -Wl,-rpath,'$$ORIGIN'
LDFLAGS_RELEASE=-L$(DIR_RELEASE) -Wl,-rpath,'$$ORIGIN'
LOGGER_FLAGS=-lboost_system -lboost_thread -pthread

#master names
SRC=master.cpp
SRC_TEST=master_test.cpp 
TARGET_DEBUG=./master
TARGET_RELEASE=./outrelease/master
OBJ_DEBUG=./master.o
OBJ_RELEASE=./objrelease/master.o
DIR_DEBUG=../lib/libdebug/
DIR_RELEASE=../lib/librelease/
INC=../include/

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libmaster.so 

release: $(DIR_RELEASE)libmaster.so 

all: $(DIR_DEBUG)libmaster.so $(DIR_RELEASE)libmaster.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(SRC_TEST) 
	$(CC) $(CFLAGS) -o $@ $(SRC_TEST) $(LDFLAGS_DEBUG) -lmaster $(LOGGER_FLAGS) -ldirmonitor -lthread_pool -lconfig -lframework -lboost_chrono $(LOGGER_FLAGS)

#Debug SO
$(DIR_DEBUG)libmaster.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $< $(LDFLAGS_DEPEND) -lminioncommunicator $(LDFLAGS_DEPEND) -lNBDCommunicator  $(LDFLAGS_DEPEND) -llogger $(LDFLAGS_DEPEND) -lframework 

#Debug Object
$(OBJ_DEBUG): $(SRC) $(INC)master.hpp     
	$(CC) $(CFLAGS) -c -fpic -o $@ $<

#Release Object
$(OBJ_RELEASE): $(SRC) $(INC)master.hpp
	$(CC) $(RFLAGS) -c -fpic -o $@ $<

.PHONY: clean
clean: 
	rm $(OBJ_DEBUG) $(OBJ_RELEASE) $(TARGET_DEBUG) 
