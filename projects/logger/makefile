#logger makefile

#flags
CC=g++   
CFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -g -I$(INC) -I./
RFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC) 
LDFLAGS_DEBUG=-L../lib/libdebug -Wl,-rpath=../../lib/libdebug
LDFLAGS_RELEASE=-L$(DIR_RELEASE) -Wl,-rpath,'$$ORIGIN'

#logger names
SRC=logger.cpp
SRC_TEST=logger_test.cpp
TARGET_DEBUG=./outdebug/logger
TARGET_RELEASE=./outrelease/logger
OBJ_DEBUG=./objdebug/logger.o
OBJ_RELEASE=./objrelease/logger.o
DIR_DEBUG=../lib/libdebug/
DIR_RELEASE=../lib/librelease/
INC=../include/

.PHONY: clean release debug all

debug: $(DIR_DEBUG)liblogger.so 

release: $(DIR_RELEASE)liblogger.so 

all: $(DIR_DEBUG)liblogger.so $(DIR_RELEASE)liblogger.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)liblogger.so $(SRC_TEST) 
	$(CC) $(CFLAGS) -o $@ $(SRC_TEST) $(LDFLAGS_DEBUG) -llogger -lboost_system -lboost_thread -pthread
	
#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)liblogger.so $(SRC_TEST) 
	$(CC) $(RFLAGS) -o $@ $(SRC_TEST) $(LDFLAGS_RELEASE) -llogger
	
#Debug SO
$(DIR_DEBUG)liblogger.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $< 

#Release SO
$(DIR_RELEASE)liblogger.so: $(OBJ_RELEASE) 
	$(CC) $(RFLAGS) -shared -o $@ $< 
	
#Debug Object
$(OBJ_DEBUG): $(SRC) $(INC)logger.hpp    
	$(CC) $(CFLAGS) -c -fpic -o $@ $<

#Release Object
$(OBJ_RELEASE): $(SRC) $(INC)logger.hpp
	$(CC) $(RFLAGS) -c -fpic -o $@ $<

.PHONY: clean
clean: 
	rm $(OBJ_DEBUG) $(OBJ_RELEASE) $(TARGET_DEBUG) 
