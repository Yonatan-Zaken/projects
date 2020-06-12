#dirmonitor makefile

#flags
CC=g++   
CFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -g -I$(INC)
RFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC) 
LDFLAGS_DEBUG=-L../lib/libdebug -Wl,-rpath=../lib/libdebug
LDFLAGS_DEPEND=-L../lib/libdebug -Wl,-rpath,'$$ORIGIN'
LDFLAGS_RELEASE=-L$(DIR_RELEASE) -Wl,-rpath,'$$ORIGIN'

#dirmonitor names
SRC=dirmonitor.cpp
SRC_TEST=dirmonitor_test.cpp
TARGET_DEBUG=./dirmonitor
TARGET_RELEASE=./outrelease/dirmonitor
OBJ_DEBUG=./dirmonitor.o
OBJ_RELEASE=./objrelease/dirmonitor.o
DIR_DEBUG=../lib/libdebug/
DIR_RELEASE=../lib/librelease/
INC=../include/

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libdirmonitor.so 

release: $(DIR_RELEASE)libdirmonitor.so 

all: $(DIR_DEBUG)libdirmonitor.so $(DIR_RELEASE)libdirmonitor.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)libdirmonitor.so $(SRC_TEST) 
	$(CC) $(CFLAGS) -o $@ $(SRC_TEST) $(LDFLAGS_DEBUG) -ldirmonitor -lreactor
	
#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)libdirmonitor.so $(SRC_TEST) 
	$(CC) $(RFLAGS) $(LDFLAGS_RELEASE) -o $@ $(SRC_TEST) -ldirmonitor  

#Debug SO
$(DIR_DEBUG)libdirmonitor.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $< $ $(LDFLAGS_DEPEND) -linotify $(LDFLAGS_DEPEND) -lreactor
	
#Release SO
$(DIR_RELEASE)libdirmonitor.so: $(OBJ_RELEASE)
	$(CC) $(RFLAGS) -shared -o $@ $< 
	
#Debug Object
$(OBJ_DEBUG): $(SRC) $(INC)dirmonitor.hpp    
	$(CC) $(CFLAGS) -c -fpic -o $@ $<

#Release Object
$(OBJ_RELEASE): $(SRC) $(INC)dirmonitor.hpp
	$(CC) $(RFLAGS) -c -fpic -o $@ $<

.PHONY: clean
clean: 
	rm $(OBJ_DEBUG) $(OBJ_RELEASE) $(TARGET_DEBUG) 
