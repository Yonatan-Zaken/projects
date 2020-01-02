#sortedlist makefile

#flags
CC=gcc   
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g -I../include
RFLAGS=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I../include 
LDFLAGS_DEBUG=-L../libdebug -Wl,-rpath=../../libdebug
LDFLAGS_RELEASE=-L../librelease -Wl,-rpath=../../librelease

#file names
TARGET_DEBUG=./outdebug/sorted_list
TARGET_RELEASE=./outrelease/sorted_list
SRC=sorted_list.c
OBJ_DEBUG=./objdebug/sorted_list.o
OBJ_RELEASE=./objrelease/sorted_list.o
SRC_TEST=sorted_list_test.c
DIR_DEBUG=../libdebug/
DIR_RELEASE=../librelease/
INC=../include/sortedlist.h

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libsortedlist.so 

release: $(DIR_RELEASE)libsortedlist.so 

all: $(DIR_DEBUG)libsortedlist.so $(DIR_RELEASE)libsortedlist.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)libsortedlist.so $(SRC_TEST) 
	$(CC) $(CFLAGS) $(LDFLAGS_DEBUG) -o $@ $(SRC_TEST) -lsortedlist

#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)libsortedlist.so $(SRC_TEST) 
	$(CC) $(RFLAGS) $(LDFLAGS_RELEASE) -o $@ $(SRC_TEST) -lsortedlist	

#Debug SO
$(DIR_DEBUG)libsortedlist.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $< -L../libdebug -Wl,-rpath,'$$ORIGIN' \
	 -ldll 

#Release SO
$(DIR_RELEASE)libsortedlist.so: $(OBJ_RELEASE)
	$(CC) $(RFLAGS) -shared -o $@ $< -L../librelease -Wl,-rpath,'$$ORIGIN' \
	-ldll

#Debug Object
$(OBJ_DEBUG): $(SRC) $(INC)    
	$(CC) $(CFLAGS) -c -fpic -o $@ $<

#Release Object
$(OBJ_RELEASE): $(SRC) $(INC)
	$(CC) $(RFLAGS) -c -fpic -o $@ $<

.PHONY: clean
clean: 
	rm $(OBJ_DEBUG) $(OBJ_RELEASE) $(TARGET_DEBUG) 


















