#minion makefile

#flags
CC=g++   
CFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -g -I$(INC)
RFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC) 
LDFLAGS_DEBUG=-L../lib/libdebug -Wl,-rpath=../lib/libdebug
LDFLAGS_DEPEND=-L../lib/libdebug -Wl,-rpath,'$$ORIGIN'
LDFLAGS_RELEASE=-L$(DIR_RELEASE) -Wl,-rpath,'$$ORIGIN'

#minion names
SRC=minion.cpp
SRC_TEST=minion_test.cpp
TARGET_DEBUG=./minion
TARGET_RELEASE=./outrelease/minion
OBJ_DEBUG=./minion.o
OBJ_RELEASE=./objrelease/minion.o
DIR_DEBUG=../lib/libdebug/
DIR_RELEASE=../lib/librelease/
INC=../include/

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libminion.so 

release: $(DIR_RELEASE)libminion.so 

all: $(DIR_DEBUG)libminion.so $(DIR_RELEASE)libminion.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)libminion.so $(SRC_TEST) 
	$(CC) $(CFLAGS) -o $@ $(SRC_TEST) $(LDFLAGS_DEBUG) -lminion -lconnection -lUDPServer -lstorage -lfactory_wrap -lcommand -lframework -ltimer -ldirmonitor -lthread_pool -lconfig -lboost_system -lboost_thread -lboost_chrono

#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)libminion.so $(SRC_TEST) 
	$(CC) $(RFLAGS) $(LDFLAGS_RELEASE) -o $@ $(SRC_TEST) -lminion  

#Debug SO
$(DIR_DEBUG)libminion.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $< $(LDFLAGS_DEPEND) -lreactor $(LDFLAGS_DEPEND) -lconnection $(LDFLAGS_DEPEND) -lstorage $(LDFLAGS_DEPEND) -lfactory_wrap $(LDFLAGS_DEPEND) -lcommand $(LDFLAGS_DEPEND) -lframework
	
#Release SO
$(DIR_RELEASE)libminion.so: $(OBJ_RELEASE)
	$(CC) $(RFLAGS) -shared -o $@ $< 
	
#Debug Object
$(OBJ_DEBUG): $(SRC) $(INC)minion.hpp    
	$(CC) $(CFLAGS) -c -fpic -o $@ $<

#Release Object
$(OBJ_RELEASE): $(SRC) $(INC)minion.hpp
	$(CC) $(RFLAGS) -c -fpic -o $@ $<

.PHONY: clean
clean: 
	rm $(OBJ_DEBUG) $(OBJ_RELEASE) $(TARGET_DEBUG) 
