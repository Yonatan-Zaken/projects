#binary search tree makefile

#flags
CC=gcc   
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g -I../include
RFLAGS=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I../include 
LDFLAGS_DEBUG=-L../libdebug -Wl,-rpath=../../libdebug
LDFLAGS_RELEASE=-L../librelease -Wl,-rpath=../../librelease

#file names
TARGET_DEBUG=./outdebug/bst
TARGET_RELEASE=./outrelease/bst
SRC=bst.c
OBJ_DEBUG=./objdebug/bst.o
OBJ_RELEASE=./objrelease/bst.o
SRC_TEST=bst_test.c
DIR_DEBUG=../libdebug/
DIR_RELEASE=../librelease/
INC=../include/bst.h

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libbst.so 

release: $(DIR_RELEASE)libbst.so 

all: $(DIR_DEBUG)libbst.so $(DIR_RELEASE)libbst.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)libbst.so $(SRC_TEST) 
	$(CC) $(CFLAGS) $(LDFLAGS_DEBUG) -o $@ $(SRC_TEST) -lbst

#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)libbst.so $(SRC_TEST) 
	$(CC) $(RFLAGS) $(LDFLAGS_RELEASE) -o $@ $(SRC_TEST) -lbst	

#Debug SO
$(DIR_DEBUG)libbst.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $<

#Release SO
$(DIR_RELEASE)libbst.so: $(OBJ_RELEASE)
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


















