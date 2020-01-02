#uid makefile

#flags
CC=gcc   
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g -I../include
RFLAGS=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I../include 
LDFLAGS_DEBUG=-L../libdebug -Wl,-rpath=../../libdebug
LDFLAGS_RELEASE=-L../librelease -Wl,-rpath=../../librelease

#file names
TARGET_DEBUG=./outdebug/uid
TARGET_RELEASE=./outrelease/uid
SRC=uid.c
OBJ_DEBUG=./objdebug/uid.o
OBJ_RELEASE=./objrelease/uid.o
SRC_TEST=uid_test.c
DIR_DEBUG=../libdebug/
DIR_RELEASE=../librelease/
INC=../include/uid.h

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libuid.so 

release: $(DIR_RELEASE)libuid.so 

all: $(DIR_DEBUG)libuid.so $(DIR_RELEASE)libuid.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)libuid.so $(SRC_TEST) 
	$(CC) $(CFLAGS) $(LDFLAGS_DEBUG) -o $@ $(SRC_TEST) -luid

#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)libuid.so $(SRC_TEST) 
	$(CC) $(RFLAGS) $(LDFLAGS_RELEASE) -o $@ $(SRC_TEST) -luid	

#Debug SO
$(DIR_DEBUG)libuid.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $<

#Release SO
$(DIR_RELEASE)libuid.so: $(OBJ_RELEASE)
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


















