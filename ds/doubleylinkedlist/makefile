#doubleylinkedlist makefile

#flags
CC=gcc   
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g -I../include
RFLAGS=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I../include 
LDFLAGS_DEBUG=-L../libdebug -Wl,-rpath=../../libdebug
LDFLAGS_RELEASE=-L../librelease -Wl,-rpath=../../librelease

#file names
TARGET_DEBUG=./outdebug/dll
TARGET_RELEASE=./outrelease/dll
SRC=dll.c
OBJ_DEBUG=./objdebug/dll.o
OBJ_RELEASE=./objrelease/dll.o
SRC_TEST=dll_test.c
DIR_DEBUG=../libdebug/
DIR_RELEASE=../librelease/
INC=../include/dllist.h

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libdll.so 

release: $(DIR_RELEASE)libdll.so 

all: $(DIR_DEBUG)libdll.so $(DIR_RELEASE)libdll.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)libdll.so $(SRC_TEST) 
	$(CC) $(CFLAGS) $(LDFLAGS_DEBUG) -o $@ $(SRC_TEST) -ldll

#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)libdll.so $(SRC_TEST) 
	$(CC) $(RFLAGS) $(LDFLAGS_RELEASE) -o $@ $(SRC_TEST) -ldll	

#Debug SO
$(DIR_DEBUG)libdll.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $<

#Release SO
$(DIR_RELEASE)libdll.so: $(OBJ_RELEASE)
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


















