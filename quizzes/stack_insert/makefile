#stack_insert makefile

#flags
CC=gcc   
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g -I../../ds/include
LDFLAGS_DEBUG=-L../../ds/libdebug -Wl,-rpath,'$$ORIGIN/../../ds/libdebug'

#file names
TARGET_DEBUG=./stack_insert
SRC=./stack_insert.c
OBJ_DEBUG=./stack_insert.o
SRC_TEST=./stack_test.c
INC=../../ds/include/stack.h

.PHONY: clean debug 

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(OBJ_DEBUG) 
	$(CC) $(CFLAGS) -o $@ $(OBJ_DEBUG) $(LDFLAGS_DEBUG) -lstack

#Debug Object
$(OBJ_DEBUG): $(SRC) $(INC)    
	$(CC) $(CFLAGS) -c -fpic -o $@ $<

.PHONY: clean
clean: 
	rm $(OBJ_DEBUG) $(TARGET_DEBUG) 


















