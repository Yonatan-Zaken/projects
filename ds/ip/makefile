#binary search tree makefile

#flags
CC=gcc   
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g -I../include
RFLAGS=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I../include 
LDFLAGS_DEBUG=-L../libdebug -Wl,-rpath=../../libdebug
LDFLAGS_RELEASE=-L../librelease -Wl,-rpath=../../librelease

#file names
TARGET_DEBUG=./outdebug/ip
TARGET_RELEASE=./outrelease/ip
SRC=ip.c
OBJ_DEBUG=./objdebug/ip.o
OBJ_RELEASE=./objrelease/ip.o
SRC_TEST=ip_test.c
DIR_DEBUG=../libdebug/
DIR_RELEASE=../librelease/
INC=../include/ip.h

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libip.so 

release: $(DIR_RELEASE)libip.so 

all: $(DIR_DEBUG)libip.so $(DIR_RELEASE)libip.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)libip.so $(SRC_TEST) 
	$(CC) $(CFLAGS) $(LDFLAGS_DEBUG) -o $@ $(SRC_TEST) -lip

#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)libip.so $(SRC_TEST) 
	$(CC) $(RFLAGS) $(LDFLAGS_RELEASE) -o $@ $(SRC_TEST) -lip	

#Debug SO
$(DIR_DEBUG)libip.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $<

#Release SO
$(DIR_RELEASE)libip.so: $(OBJ_RELEASE)
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


















