#priorityq makefile

#flags
CC=gcc   
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g -I../include
RFLAGS=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I../include 
LDFLAGS_DEBUG=-L../libdebug -Wl,-rpath=../../libdebug
LDFLAGS_RELEASE=-L../librelease -Wl,-rpath=../../librelease

#file names
TARGET_DEBUG=./outdebug/priorityq
TARGET_RELEASE=./outrelease/priorityq
SRC=priorityq.c
OBJ_DEBUG=./objdebug/priorityq.o
OBJ_RELEASE=./objrelease/priorityq.o
SRC_TEST=priorityq_test.c
DIR_DEBUG=../libdebug/
DIR_RELEASE=../librelease/
INC=../include/priorityqueue.h

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libpriorityq.so 

release: $(DIR_RELEASE)libpriorityq.so 

all: $(DIR_DEBUG)libpriorityq.so $(DIR_RELEASE)libpriorityq.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)libpriorityq.so $(SRC_TEST) 
	$(CC) $(CFLAGS) $(LDFLAGS_DEBUG) -o $@ $(SRC_TEST) -lpriorityq

#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)libpriorityq.so $(SRC_TEST) 
	$(CC) $(RFLAGS) $(LDFLAGS_RELEASE) -o $@ $(SRC_TEST) -lpriorityq	

#Debug SO
$(DIR_DEBUG)libpriorityq.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $< -L../libdebug -Wl,-rpath,'$$ORIGIN' \
	 -lsortedlist

#Release SO
$(DIR_RELEASE)libpriorityq.so: $(OBJ_RELEASE)
	$(CC) $(RFLAGS) -shared -o $@ $< -L../librelease -Wl,-rpath,'$$ORIGIN' \
	-lsortedlist

#Debug Object
$(OBJ_DEBUG): $(SRC) $(INC)    
	$(CC) $(CFLAGS) -c -fpic -o $@ $<

#Release Object
$(OBJ_RELEASE): $(SRC) $(INC)
	$(CC) $(RFLAGS) -c -fpic -o $@ $<

.PHONY: clean
clean: 
	rm $(OBJ_DEBUG) $(OBJ_RELEASE) $(TARGET_DEBUG) 


















