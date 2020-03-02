#flip_list makefile

#flags
CC=gcc   
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g -I../../ds/include
LDFLAGS_DEBUG=-L../../ds/libdebug -Wl,-rpath,'$$ORIGIN/../../ds/libdebug'

#file names
TARGET_DEBUG=./flip_list
SRC=./flip_list.c
OBJ_DEBUG=./flip_list.o
SRC_TEST=stack_test.c
INC=../../ds/include/linkedlist.h

.PHONY: clean debug 

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(OBJ_DEBUG) 
	$(CC) $(CFLAGS) $(LDFLAGS_DEBUG) -o $@ $(OBJ_DEBUG) -llinkedlist 

#Debug Object
$(OBJ_DEBUG): $(SRC) $(INC)    
	$(CC) $(CFLAGS) -c -fpic -o $@ $<

.PHONY: clean
clean: 
	rm $(OBJ_DEBUG) $(TARGET_DEBUG) 


















