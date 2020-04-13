#sortedlist makefile

#flags
CC=g++   
CFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -g -I../../include
RFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I../../include 
LDFLAGS_DEBUG=-L$(DIR_DEBUG) -Wl,-rpath=../../../lib/libdebug
LDFLAGS_RELEASE=-L$(DIR_RELEASE) -Wl,-rpath=../../../lib/librelease

#file names
TARGET_DEBUG=./outdebug/directory
TARGET_RELEASE=./outrelease/directory
SRC=directory.cpp
OBJ_DEBUG=./objdebug/directory.o
OBJ_RELEASE=./objrelease/directory.o
SRC_TEST=directory_test.cpp
DIR_DEBUG=../../lib/libdebug/
DIR_RELEASE=../../lib/librelease/
INC=../../include/directory.hpp

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libdirectory.so 

release: $(DIR_RELEASE)libdirectory.so 

all: $(DIR_DEBUG)libdirectory.so $(DIR_RELEASE)libdirectory.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)libdirectory.so $(SRC_TEST) 
	$(CC) $(CFLAGS) $(LDFLAGS_DEBUG) -o $@ $(SRC_TEST) -ldirectory -lfile
	
#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)libdirectory.so $(SRC_TEST) 
	$(CC) $(RFLAGS) $(LDFLAGS_RELEASE) -o $@ $(SRC_TEST) -ldirectory -lfile

#Debug SO
$(DIR_DEBUG)libdirectory.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $< 
	  
#Release SO
$(DIR_RELEASE)libdirectory.so: $(OBJ_RELEASE)
	$(CC) $(RFLAGS) -shared -o $@ $< 
	
#Debug Object
$(OBJ_DEBUG): $(SRC) $(INC)    
	$(CC) $(CFLAGS) -c -fpic -o $@ $<

#Release Object
$(OBJ_RELEASE): $(SRC) $(INC)
	$(CC) $(RFLAGS) -c -fpic -o $@ $<

.PHONY: clean
clean: 
	rm $(OBJ_DEBUG) $(OBJ_RELEASE) $(TARGET_DEBUG) 


















