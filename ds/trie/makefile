#trie makefile

#flags
CC=gcc   
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g -I../include
RFLAGS=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I../include 
LDFLAGS_DEBUG=-L../libdebug -Wl,-rpath=../../libdebug
LDFLAGS_RELEASE=-L../librelease -Wl,-rpath=../../librelease

#file names
TARGET_DEBUG=./outdebug/trie
TARGET_RELEASE=./outrelease/trie
SRC=trie.c
OBJ_DEBUG=./objdebug/trie.o
OBJ_RELEASE=./objrelease/trie.o
SRC_TEST=trie_test.c
DIR_DEBUG=../libdebug/
DIR_RELEASE=../librelease/
INC=../include/trie.h

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libtrie.so 

release: $(DIR_RELEASE)libtrie.so 

all: $(DIR_DEBUG)libtrie.so $(DIR_RELEASE)libtrie.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)libtrie.so $(SRC_TEST) 
	$(CC) $(CFLAGS) $(LDFLAGS_DEBUG) -o $@ $(SRC_TEST) -ltrie -lm

#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)libtrie.so $(SRC_TEST) 
	$(CC) $(RFLAGS) $(LDFLAGS_RELEASE) -o $@ $(SRC_TEST) -ltrie	-lm

#Debug SO
$(DIR_DEBUG)libtrie.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $<

#Release SO
$(DIR_RELEASE)libtrie.so: $(OBJ_RELEASE)
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


















