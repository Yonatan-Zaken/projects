#circularbuffer makefile

#flags
CC=gcc   
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g -I../include
RFLAGS=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I../include 
LDFLAGS_DEBUG=-L../libdebug -Wl,-rpath=../../libdebug
LDFLAGS_RELEASE=-L../librelease -Wl,-rpath=../../librelease

#file names
TARGET_DEBUG=./outdebug/circularbuffer
TARGET_RELEASE=./outrelease/circularbuffer
SRC=circularbuffer.c
OBJ_DEBUG=./objdebug/circularbuffer.o
OBJ_RELEASE=./objrelease/circularbuffer.o
SRC_TEST=circularbuffer_test.c
DIR_DEBUG=../libdebug/
DIR_RELEASE=../librelease/
INC=../include/circularbuffer.h

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libcircularbuffer.so 

release: $(DIR_RELEASE)libcircularbuffer.so 

all: $(DIR_DEBUG)libcircularbuffer.so $(DIR_RELEASE)libcircularbuffer.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)libcircularbuffer.so $(SRC_TEST) 
	$(CC) $(CFLAGS) $(LDFLAGS_DEBUG) -o $@ $(SRC_TEST) -lcircularbuffer

#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)libcircularbuffer.so $(SRC_TEST) 
	$(CC) $(RFLAGS) $(LDFLAGS_RELEASE) -o $@ $(SRC_TEST) -lcircularbuffer	

#Debug SO
$(DIR_DEBUG)libcircularbuffer.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $<

#Release SO
$(DIR_RELEASE)libcircularbuffer.so: $(OBJ_RELEASE)
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


















