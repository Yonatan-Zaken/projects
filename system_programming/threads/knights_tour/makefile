#knights_tour makefile

#flags
CC=gcc   
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g -I../../../ds/include 
LDFLAGS_DEBUG=-L../../../ds/libdebug -Wl,-rpath,'$$ORIGIN/../../../ds/libdebug'

#file names
TARGET_DEBUG=./knights_tour
SRC=knights_tour.c
OBJ_DEBUG=./knights_tour.o

.PHONY: clean release debug all


all: $(DIR_DEBUG)libknights_tour.so $(DIR_RELEASE)libknights_tour.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(OBJ_DEBUG) 
	$(CC) $(CFLAGS) $(LDFLAGS_DEBUG) -o $@ $(OBJ_DEBUG) -lbitsarray
	
#Debug Object
$(OBJ_DEBUG): $(SRC)    
	$(CC) $(CFLAGS) -c -fpic -o $@ $<

.PHONY: clean
clean: 
	rm $(OBJ_DEBUG) $(OBJ_RELEASE) $(TARGET_DEBUG) 


















