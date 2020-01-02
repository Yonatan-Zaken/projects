#queue makefile

#flags
CC=gcc   
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g -I../include
RFLAGS=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I../include 
LDFLAGS_DEBUG=-L../libdebug -Wl,-rpath=../../libdebug
LDFLAGS_RELEASE=-L../librelease -Wl,-rpath=../../librelease

#file names
TARGET_DEBUG=./outdebug/queue
TARGET_RELEASE=./outrelease/queue
SRC=queue.c
OBJ_DEBUG=./objdebug/queue.o
OBJ_RELEASE=./objrelease/queue.o
SRC_TEST=queue_test.c
DIR_DEBUG=../libdebug/
DIR_RELEASE=../librelease/
INC=../include/queue.h

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libqueue.so 

release: $(DIR_RELEASE)libqueue.so 

all: $(DIR_DEBUG)libqueue.so $(DIR_RELEASE)libqueue.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)libqueue.so $(SRC_TEST) 
	$(CC) $(CFLAGS) $(LDFLAGS_DEBUG) -o $@ $(SRC_TEST) -lqueue

#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)libqueue.so $(SRC_TEST) 
	$(CC) $(RFLAGS) $(LDFLAGS_RELEASE) -o $@ $(SRC_TEST) -lqueue	

#Debug SO
$(DIR_DEBUG)libqueue.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $< -L../libdebug -Wl,-rpath,'$$ORIGIN'/\
	 -llinkedlist

#Release SO
$(DIR_RELEASE)libqueue.so: $(OBJ_RELEASE)
	$(CC) $(RFLAGS) -shared -o $@ $< -L../librelease -Wl,-rpath,'$$ORIGIN'/\
	-llinkedlist

#Debug Object
$(OBJ_DEBUG): $(SRC) $(INC)    
	$(CC) $(CFLAGS) -c -fpic -o $@ $<

#Release Object
$(OBJ_RELEASE): $(SRC) $(INC)
	$(CC) $(RFLAGS) -c -fpic -o $@ $<

.PHONY: clean
clean: 
	rm $(OBJ_DEBUG) $(OBJ_RELEASE) $(TARGET_DEBUG) 


















