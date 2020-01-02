#bitsarray makefile

#flags
CC=gcc   
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g -I../include
RFLAGS=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I../include 
LDFLAGS_DEBUG=-L../libdebug -Wl,-rpath=../../libdebug
LDFLAGS_RELEASE=-L../librelease -Wl,-rpath=../../librelease

#file names
TARGET_DEBUG=./outdebug/bitsarray
TARGET_RELEASE=./outrelease/bitsarray
SRC=bitsarray.c
OBJ_DEBUG=./objdebug/bitsarray.o
OBJ_RELEASE=./objrelease/bitsarray.o
SRC_TEST=bitsarray_test.c
DIR_DEBUG=../libdebug/
DIR_RELEASE=../librelease/
INC=../include/bitsarray.h

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libbitsarray.so 

release: $(DIR_RELEASE)libbitsarray.so 

all: $(DIR_DEBUG)libbitsarray.so $(DIR_RELEASE)libbitsarray.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)libbitsarray.so $(SRC_TEST) 
	$(CC) $(CFLAGS) $(LDFLAGS_DEBUG) -o $@ $(SRC_TEST) -lbitsarray

#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)libbitsarray.so $(SRC_TEST) 
	$(CC) $(RFLAGS) $(LDFLAGS_RELEASE) -o $@ $(SRC_TEST) -lbitsarray	

#Debug SO
$(DIR_DEBUG)libbitsarray.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $<

#Release SO
$(DIR_RELEASE)libbitsarray.so: $(OBJ_RELEASE)
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


















