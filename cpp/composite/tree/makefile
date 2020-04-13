#sortedlist makefile

#flags
CC=g++   
CFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -g -I../../include
RFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I../../include 
LDFLAGS_DEBUG=-L../libdebug -Wl,-rpath=../../libdebug
LDFLAGS_RELEASE=-L../librelease -Wl,-rpath=../../librelease

#file names
TARGET_DEBUG=./outdebug/tree
TARGET_RELEASE=./outrelease/tree
SRC=tree.c
OBJ_DEBUG=./objdebug/tree.o
OBJ_RELEASE=./objrelease/tree.o
SRC_TEST=tree_test.cpp
DIR_DEBUG=../libdebug/
DIR_RELEASE=../librelease/
INC=../include/sortedlist.h

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libtree.so 

release: $(DIR_RELEASE)libtree.so 

all: $(DIR_DEBUG)libtree.so $(DIR_RELEASE)libstree.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)libtree.so $(SRC_TEST) 
	$(CC) $(CFLAGS) $(LDFLAGS_DEBUG) -o $@ $(SRC_TEST) -ltree
	
#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)libtree.so $(SRC_TEST) 
	$(CC) $(RFLAGS) $(LDFLAGS_RELEASE) -o $@ $(SRC_TEST) -ltree	

#Debug SO
$(DIR_DEBUG)libstree.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $< -L../libdebug -Wl,-rpath,'$$ORIGIN' \
	 -ldll 

#Release SO
$(DIR_RELEASE)libtree.so: $(OBJ_RELEASE)
	$(CC) $(RFLAGS) -shared -o $@ $< -L../librelease -Wl,-rpath,'$$ORIGIN' \
	-ldll

#Debug Object
$(OBJ_DEBUG): $(SRC) $(INC)    
	$(CC) $(CFLAGS) -c -fpic -o $@ $<

#Release Object
$(OBJ_RELEASE): $(SRC) $(INC)
	$(CC) $(RFLAGS) -c -fpic -o $@ $<

.PHONY: clean
clean: 
	rm $(OBJ_DEBUG) $(OBJ_RELEASE) $(TARGET_DEBUG) 


















