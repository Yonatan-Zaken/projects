#linkedlist makefile

#flags
CC=gcc   
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g -I../include
RFLAGS=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I../include 
LDFLAGS_DEBUG=-L../libdebug -Wl,-rpath=../../libdebug
LDFLAGS_RELEASE=-L../librelease -Wl,-rpath=../../librelease

#file names
TARGET_DEBUG=./outdebug/linkedlist
TARGET_RELEASE=./outrelease/linkedlist
SRC=linkedlist.c
OBJ_DEBUG=./objdebug/linkedlist.o
OBJ_RELEASE=./objrelease/linkedlist.o
SRC_TEST=linkedlist_test.c
DIR_DEBUG=../libdebug/
DIR_RELEASE=../librelease/
INC=../include/linkedlist.h

.PHONY: clean release debug all

debug: $(DIR_DEBUG)liblinkedlist.so 

release: $(DIR_RELEASE)liblinkedlist.so 

all: $(DIR_DEBUG)liblinkedlist.so $(DIR_RELEASE)liblinkedlist.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)liblinkedlist.so $(SRC_TEST) 
	$(CC) $(CFLAGS) $(LDFLAGS_DEBUG) -o $@ $(SRC_TEST) -llinkedlist

#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)liblinkedlist.so $(SRC_TEST) 
	$(CC) $(RFLAGS) $(LDFLAGS_RELEASE) -o $@ $(SRC_TEST) -llinkedlist	

#Debug SO
$(DIR_DEBUG)liblinkedlist.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $<

#Release SO
$(DIR_RELEASE)liblinkedlist.so: $(OBJ_RELEASE)
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


















