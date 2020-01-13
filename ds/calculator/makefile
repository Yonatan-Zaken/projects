#arithmetic makefile

#flags
CC=gcc   
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g -I../include 
RFLAGS=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I../include 
LDFLAGS_DEBUG=-L../libdebug -Wl,-rpath=../../libdebug
LDFLAGS_RELEASE=-L../librelease -Wl,-rpath=../../librelease

#file names
TARGET_DEBUG=./outdebug/arithmetic
TARGET_RELEASE=./outrelease/arithmetic
SRC=arithmetic.c
OBJ_DEBUG=./objdebug/arithmetic.o
OBJ_RELEASE=./objrelease/arithmetic.o
SRC_TEST=calculator_test.c calculator.c
DIR_DEBUG=../libdebug/
DIR_RELEASE=../librelease/
INC=../include/arithmetic.h

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libarithmetic.so 

release: $(DIR_RELEASE)libarithmetic.so 

all: $(DIR_DEBUG)libarithmetic.so $(DIR_RELEASE)libarithmetic.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)libarithmetic.so $(SRC_TEST) 
	$(CC) $(CFLAGS) $(LDFLAGS_DEBUG) -o $@ $(SRC_TEST) -larithmetic  

#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)libarithmetic.so $(SRC_TEST) 
	$(CC) $(RFLAGS) $(LDFLAGS_RELEASE) -o $@ $(SRC_TEST) -larithmetic	

#Debug SO
$(DIR_DEBUG)libarithmetic.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $< -L../libdebug -Wl,-rpath,'$$ORIGIN' \
	 -lstack -lm

#Release SO
$(DIR_RELEASE)libarithmetic.so: $(OBJ_RELEASE)
	$(CC) $(RFLAGS) -shared -o $@ $< -L../librelease -Wl,-rpath,'$$ORIGIN' \
	-lstack 

#Debug Object
$(OBJ_DEBUG): $(SRC) $(INC)    
	$(CC) $(CFLAGS) -c -fpic -o $@ $<

#Release Object
$(OBJ_RELEASE): $(SRC) $(INC)
	$(CC) $(RFLAGS) -c -fpic -o $@ $<

.PHONY: clean
clean: 
	rm $(OBJ_DEBUG) $(OBJ_RELEASE) $(TARGET_DEBUG) 


















