#sortedlist makefile

#flags
CC=g++   
CFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -g -I../../include
RFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I../../include 
LDFLAGS_DEBUG=-L$(DIR_DEBUG) -Wl,-rpath=../$(DIR_DEBUG)
LDFLAGS_RELEASE=-L$(DIR_RELEASE) -Wl,-rpath=../$(DIR_DEBUG)

#file names
TARGET_DEBUG=./outdebug/tree
TARGET_RELEASE=./outrelease/tree
SRC=tree.cpp
OBJ_DEBUG=./objdebug/tree.o
OBJ_RELEASE=./objrelease/tree.o
SRC_TEST=tree_test.cpp
DIR_DEBUG=../../lib/libdebug/
DIR_RELEASE=../../lib/librelease/
INC=../../include/tree.hpp

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libtree.so 

release: $(DIR_RELEASE)libtree.so 

all: $(DIR_DEBUG)libtree.so $(DIR_RELEASE)libtree.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)libtree.so $(SRC_TEST) 
	$(CC) $(CFLAGS) $(LDFLAGS_DEBUG) -o $@ $(SRC_TEST) -ltree -ldirectory -lfile
	
#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)libtree.so $(SRC_TEST) 
	$(CC) $(RFLAGS) $(LDFLAGS_RELEASE) -o $@ $(SRC_TEST) -ltree	-ldirectory -lfile

#Debug SO
$(DIR_DEBUG)libtree.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $< 
	  
#Release SO
$(DIR_RELEASE)libtree.so: $(OBJ_RELEASE)
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


















