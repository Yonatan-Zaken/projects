#recursion makefile

#flags
CC=gcc   
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g -I../../ds/include
RFLAGS=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I../../ds/include 
LDFLAGS_DEBUG=-L../../ds/libdebug -Wl,-rpath=../../../ds/libdebug
LDFLAGS_RELEASE=-L../../ds/librelease -Wl,-rpath=../../../ds/librelease

#file names
TARGET_DEBUG=./outdebug/recursion
TARGET_RELEASE=./outrelease/recursion
SRC=recursion.c
OBJ_DEBUG=./objdebug/recursion.o
OBJ_RELEASE=./objrelease/recursion.o
SRC_TEST=recursion_test.c
DIR_DEBUG=../../ds/libdebug/
DIR_RELEASE=../../ds/librelease/
INC=../../ds/include/recursion.h

.PHONY: clean release debug all

debug: $(DIR_DEBUG)librecursion.so 

release: $(DIR_RELEASE)librecursion.so 

all: $(DIR_DEBUG)librecursion.so $(DIR_RELEASE)librecursion.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)librecursion.so $(SRC_TEST) 
	$(CC) $(CFLAGS) $(LDFLAGS_DEBUG) -o $@ $(SRC_TEST) -lrecursion

#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)librecursion.so $(SRC_TEST) 
	$(CC) $(RFLAGS) $(LDFLAGS_RELEASE) -o $@ $(SRC_TEST) -lrecursion	

#Debug SO
$(DIR_DEBUG)librecursion.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $< -L../../ds/libdebug -Wl,-rpath,'$$ORIGIN' \
	 -llinkedlist

#Release SO
$(DIR_RELEASE)librecursion.so: $(OBJ_RELEASE)
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


















