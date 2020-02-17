#circularbuffer makefile

#flags
CC=gcc   
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g -I../../include
RFLAGS=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I../include 
LDFLAGS_DEBUG=-L../../libdebug -Wl,-rpath,'$$ORIGIN/../../libdebug'

#file names
TARGET_DEBUG=./prod_or_cons
TARGET_RELEASE=./outrelease/circularbuffer
SRC=./prod_or_cons.c
OBJ_DEBUG=./circularbuffer.o
SRC_TEST=prod_or_cons.o
DIR_DEBUG=../libdebug/
INC=../../include/circularbuffer.h

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libcircularbuffer.so 

release: $(DIR_RELEASE)libcircularbuffer.so 

all: $(DIR_DEBUG)libcircularbuffer.so $(DIR_RELEASE)libcircularbuffer.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(SRC_TEST) 
	$(CC) $(CFLAGS) $(LDFLAGS_DEBUG) -o $@ $(SRC_TEST) -lcircularbuffer -pthread

#Debug Object
$(OBJ_DEBUG): $(SRC) $(INC)    
	$(CC) $(CFLAGS) -c -fpic -o $@ $<

.PHONY: clean
clean: 
	rm $(OBJ_DEBUG) $(OBJ_RELEASE) $(TARGET_DEBUG) 


















