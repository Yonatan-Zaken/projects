#stack makefile

#flags
CC=gcc   
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g -I../include
RFLAGS=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I../include 
LDFLAGS_DEBUG=-L../libdebug -Wl,-rpath=../../libdebug
LDFLAGS_RELEASE=-L../librelease -Wl,-rpath=../../librelease

#file names
TARGET_DEBUG=./outdebug/stack
TARGET_RELEASE=./outrelease/stack
SRC=stack.c
OBJ_DEBUG=./objdebug/stack.o
OBJ_RELEASE=./objrelease/stack.o
SRC_TEST=stack_test.c
DIR_DEBUG=../libdebug/
DIR_RELEASE=../librelease/
INC=../include/stack.h

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libstack.so 

release: $(DIR_RELEASE)libstack.so 

all: $(DIR_DEBUG)libstack.so $(DIR_RELEASE)libstack.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)libstack.so $(SRC_TEST) 
	$(CC) $(CFLAGS) $(LDFLAGS_DEBUG) -o $@ $(SRC_TEST) -lstack

#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)libstack.so $(SRC_TEST) 
	$(CC) $(RFLAGS) $(LDFLAGS_RELEASE) -o $@ $(SRC_TEST) -lstack	

#Debug SO
$(DIR_DEBUG)libstack.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $<

#Release SO
$(DIR_RELEASE)libstack.so: $(OBJ_RELEASE)
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


















