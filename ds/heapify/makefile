#heapify makefile

#flags
CC=gcc   
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g -I../include
RFLAGS=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I../include 
LDFLAGS_DEBUG=-L../libdebug -Wl,-rpath=../../libdebug
LDFLAGS_RELEASE=-L../librelease -Wl,-rpath=../../librelease

#file names
TARGET_DEBUG=./outdebug/heapify
TARGET_RELEASE=./outrelease/heapify
SRC=heapify.c
OBJ_DEBUG=./objdebug/heapify.o
OBJ_RELEASE=./objrelease/heapify.o
SRC_TEST=heapify_test.c
DIR_DEBUG=../libdebug/
DIR_RELEASE=../librelease/
INC=../include/heapify.h

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libheapify.so 

release: $(DIR_RELEASE)libheapify.so 

all: $(DIR_DEBUG)libheapify.so $(DIR_RELEASE)libheapify.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)libheapify.so $(SRC_TEST) 
	$(CC) $(CFLAGS) $(LDFLAGS_DEBUG) -o $@ $(SRC_TEST) -lheapify

#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)libheapify.so $(SRC_TEST) 
	$(CC) $(RFLAGS) $(LDFLAGS_RELEASE) -o $@ $(SRC_TEST) -lheapify	

#Debug SO
$(DIR_DEBUG)libheapify.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $< -L../libdebug -Wl,-rpath,'$$ORIGIN' \
	 -lvector

#Release SO
$(DIR_RELEASE)libheapify.so: $(OBJ_RELEASE)
	$(CC) $(RFLAGS) -shared -o $@ $< -L../librelease -Wl,-rpath,'$$ORIGIN' \
	-lvector

#Debug Object
$(OBJ_DEBUG): $(SRC) $(INC)    
	$(CC) $(CFLAGS) -c -fpic -o $@ $<

#Release Object
$(OBJ_RELEASE): $(SRC) $(INC)
	$(CC) $(RFLAGS) -c -fpic -o $@ $<

.PHONY: clean
clean: 
	rm $(OBJ_DEBUG) $(OBJ_RELEASE) $(TARGET_DEBUG) 


















