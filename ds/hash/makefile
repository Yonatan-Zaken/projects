#hash makefile

#flags
CC=gcc   
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g -I../include
RFLAGS=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I../include 
LDFLAGS_DEBUG=-L../libdebug -Wl,-rpath=../../libdebug
LDFLAGS_RELEASE=-L../librelease -Wl,-rpath=../../librelease

#file names
TARGET_DEBUG=./outdebug/hash
TARGET_RELEASE=./outrelease/hash
SRC=hash.c
OBJ_DEBUG=./objdebug/hash.o
OBJ_RELEASE=./objrelease/hash.o
SRC_TEST=hash_testguy.c
DIR_DEBUG=../libdebug/
DIR_RELEASE=../librelease/
INC=../include/hash.h

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libhash.so 

release: $(DIR_RELEASE)libhash.so 

all: $(DIR_DEBUG)libhash.so $(DIR_RELEASE)libhash.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)libhash.so $(SRC_TEST) 
	$(CC) $(CFLAGS) $(LDFLAGS_DEBUG) -o $@ $(SRC_TEST) -lhash

#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)libhash.so $(SRC_TEST) 
	$(CC) $(RFLAGS) $(LDFLAGS_RELEASE) -o $@ $(SRC_TEST) -lhash	

#Debug SO
$(DIR_DEBUG)libhash.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $< -L../libdebug -Wl,-rpath,'$$ORIGIN' -ldll -lm 

#Release SO
$(DIR_RELEASE)libhash.so: $(OBJ_RELEASE)
	$(CC) $(RFLAGS) -shared -o $@ $< -L../librelease -Wl,-rpath,'$$ORIGIN' -ldll

#Debug Object
$(OBJ_DEBUG): $(SRC) $(INC)    
	$(CC) $(CFLAGS) -c -fpic -o $@ $<

#Release Object
$(OBJ_RELEASE): $(SRC) $(INC)
	$(CC) $(RFLAGS) -c -fpic -o $@ $<

.PHONY: clean
clean: 
	rm $(OBJ_DEBUG) $(OBJ_RELEASE) $(TARGET_DEBUG) 


















