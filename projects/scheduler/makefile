#scheduler makefile

#flags
CC=g++   
CFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -g -I$(INC)
RFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC) 
LDFLAGS_DEBUG=-L../lib/libdebug -Wl,-rpath=../../lib/libdebug
LDFLAGS_RELEASE=-L$(DIR_RELEASE) -Wl,-rpath,'$$ORIGIN'

#scheduler names
SRC=scheduler.cpp
SRC_TEST=scheduler_test.cpp
TARGET_DEBUG=./outdebug/scheduler
TARGET_RELEASE=./outrelease/scheduler
OBJ_DEBUG=./objdebug/scheduler.o
OBJ_RELEASE=./objrelease/scheduler.o
DIR_DEBUG=../lib/libdebug/
DIR_RELEASE=../lib/librelease/
INC=../include/

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libscheduler.so 

release: $(DIR_RELEASE)libscheduler.so 

all: $(DIR_DEBUG)libscheduler.so $(DIR_RELEASE)libscheduler.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)libscheduler.so $(SRC_TEST) 
	$(CC) $(CFLAGS) -o $@ $(SRC_TEST) $(LDFLAGS_DEBUG) -lscheduler -ltimer -lreactor -lboost_system -lboost_chrono
	
#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)libscheduler.so $(SRC_TEST) 
	$(CC) $(RFLAGS) $(LDFLAGS_RELEASE) -o $@ $(SRC_TEST) -lscheduler  

#Debug SO
$(DIR_DEBUG)libscheduler.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $< -L$(DIR_DEBUG) -Wl,-rpath,'$$ORIGIN' -ltimer
	
#Release SO
$(DIR_RELEASE)libscheduler.so: $(OBJ_RELEASE)
	$(CC) $(RFLAGS) -shared -o $@ $< 
	
#Debug Object
$(OBJ_DEBUG): $(SRC) $(INC)scheduler.hpp    
	$(CC) $(CFLAGS) -c -fpic -o $@ $<

#Release Object
$(OBJ_RELEASE): $(SRC) $(INC)scheduler.hpp
	$(CC) $(RFLAGS) -c -fpic -o $@ $<

.PHONY: clean
clean: 
	rm $(OBJ_DEBUG) $(OBJ_RELEASE) $(TARGET_DEBUG) 
