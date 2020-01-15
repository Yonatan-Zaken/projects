#binary search tree makefile

#flags
CC=gcc   
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g -I../include
RFLAGS=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I../include 
LDFLAGS_DEBUG=-L../libdebug -Wl,-rpath=../../libdebug
LDFLAGS_RELEASE=-L../librelease -Wl,-rpath=../../librelease

#file names
TARGET_DEBUG=./outdebug/avl
TARGET_RELEASE=./outrelease/avl
SRC=avl.c
OBJ_DEBUG=./objdebug/avl.o
OBJ_RELEASE=./objrelease/avl.o
SRC_TEST=avl_test.c
DIR_DEBUG=../libdebug/
DIR_RELEASE=../librelease/
INC=../include/avl.h

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libavl.so 

release: $(DIR_RELEASE)libavl.so 

all: $(DIR_DEBUG)libavl.so $(DIR_RELEASE)libavl.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)libavl.so $(SRC_TEST) 
	$(CC) $(CFLAGS) $(LDFLAGS_DEBUG) -o $@ $(SRC_TEST) -lavl

#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)libavl.so $(SRC_TEST) 
	$(CC) $(RFLAGS) $(LDFLAGS_RELEASE) -o $@ $(SRC_TEST) -lavl	

#Debug SO
$(DIR_DEBUG)libavl.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $<

#Release SO
$(DIR_RELEASE)libavl.so: $(OBJ_RELEASE)
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


















