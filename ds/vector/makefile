#vector makefile

#flags
CC=gcc   
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g -I../include
RFLAGS=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I../include 
LDFLAGS_DEBUG=-L../libdebug -Wl,-rpath=../../libdebug
LDFLAGS_RELEASE=-L../librelease -Wl,-rpath=../../librelease

#file names
TARGET_DEBUG=./outdebug/vector
TARGET_RELEASE=./outrelease/vector
SRC=vector.c
OBJ_DEBUG=./objdebug/vector.o
OBJ_RELEASE=./objrelease/vector.o
SRC_TEST=vector_test.c
DIR_DEBUG=../libdebug/
DIR_RELEASE=../librelease/
INC=../include/vector.h

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libvector.so 

release: $(DIR_RELEASE)libvector.so 

all: $(DIR_DEBUG)libvector.so $(DIR_RELEASE)libvector.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)libvector.so $(SRC_TEST) 
	$(CC) $(CFLAGS) $(LDFLAGS_DEBUG) -o $@ $(SRC_TEST) -lvector

#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)libvector.so $(SRC_TEST) 
	$(CC) $(RFLAGS) $(LDFLAGS_RELEASE) -o $@ $(SRC_TEST) -lvector	

#Debug SO
$(DIR_DEBUG)libvector.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $<

#Release SO
$(DIR_RELEASE)libvector.so: $(OBJ_RELEASE)
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


















