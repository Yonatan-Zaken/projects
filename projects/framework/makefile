#framework makefile

#flags
CC=g++   
CFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -g -I$(INC)
RFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC) 
LDFLAGS_DEBUG=-L../lib/libdebug -Wl,-rpath=../lib/libdebug
LDFLAGS_DEPEND=-L../lib/libdebug -Wl,-rpath,'$$ORIGIN'
LDFLAGS_RELEASE=-L$(DIR_RELEASE) -Wl,-rpath,'$$ORIGIN'

#framework names
SRC=framework.cpp
SRC_TEST=framework_test.cpp
TARGET_DEBUG=./framework
TARGET_RELEASE=./outrelease/framework
OBJ_DEBUG=./framework.o
OBJ_RELEASE=./objrelease/framework.o
DIR_DEBUG=../lib/libdebug/
DIR_RELEASE=../lib/librelease/
INC=../include/

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libframework.so 

release: $(DIR_RELEASE)libframework.so 

all: $(DIR_DEBUG)libframework.so $(DIR_RELEASE)libframework.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)libframework.so $(SRC_TEST) 
	$(CC) $(CFLAGS) -o $@ $(SRC_TEST) $(LDFLAGS_DEBUG) -lframework -lconfig -lscheduler -ltimer -lthread_pool -ldirmonitor -lstorage -llogger -lboost_system -lboost_chrono -lboost_thread -pthread
	
#Release Out
$(TARGET_RELEASE): $(DIR_RELEASE)libframework.so $(SRC_TEST)
	$(CC) $(RFLAGS) $(LDFLAGS_RELEASE) -o $@ $(SRC_TEST) -lframework  

#Debug SO
$(DIR_DEBUG)libframework.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $< $ $(LDFLAGS_DEPEND) -lconfig $(LDFLAGS_DEPEND) -ltimer $(LDFLAGS_DEPEND) -ldirmonitor $(LDFLAGS_DEPEND) -lreactor $(LDFLAGS_DEPEND) -lscheduler $(LDFLAGS_DEPEND) -lthread_pool $(LDFLAGS_DEPEND) -lstorage $(LDFLAGS_DEPEND) -llogger
	
#Release SO
$(DIR_RELEASE)libframework.so: $(OBJ_RELEASE)
	$(CC) $(RFLAGS) -shared -o $@ $< 
	
#Debug Object
$(OBJ_DEBUG): $(SRC) $(INC)framework.hpp    
	$(CC) $(CFLAGS) -c -fpic -o $@ $<

#Release Object
$(OBJ_RELEASE): $(SRC) $(INC)framework.hpp
	$(CC) $(RFLAGS) -c -fpic -o $@ $<

.PHONY: clean
clean: 
	rm $(OBJ_DEBUG) $(OBJ_RELEASE) $(TARGET_DEBUG) 
