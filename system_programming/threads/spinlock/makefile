#doubleylinkedlist makefile

#flags
CC=gcc   
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g -I../../../ds/include
RFLAGS=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I../include 
LDFLAGS_DEBUG=-L../libdebug -Wl,-rpath=../../libdebug
LDFLAGS_RELEASE=-L../librelease -Wl,-rpath=../../librelease

#file names
TARGET_DEBUG=./producer_consumer3
SRC=producer_consumer3.c
OBJ_DEBUG=./producer_consumer3.o
SRC_TEST=producer_consumer3.c
DIR_DEBUG=../libdebug/
INC=../../ds/include/dllist.h

.PHONY: clean release debug all

all: $(DIR_DEBUG)libdll.so $(DIR_RELEASE)libdll.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(SRC_TEST) 
	$(CC) $(CFLAGS) $(LDFLAGS_DEBUG) -o $@ $(SRC_TEST) \
	-L../../../ds/libdebug -Wl,-rpath,'$$ORIGIN/../../../ds/libdebug' -ldll -pthread

#Debug Object
$(OBJ_DEBUG): $(SRC) $(INC)    
	$(CC) $(CFLAGS) -c -fpic -o $@ $<

.PHONY: clean
clean: 
	rm $(OBJ_DEBUG) $(OBJ_RELEASE) $(TARGET_DEBUG) 


















