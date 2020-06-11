#inotify makefile

#flags
CC=g++   
CFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -g -I$(INC)
RFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC) 
LDFLAGS_DEBUG=-L../lib/libdebug -Wl,-rpath=../lib/libdebug
LDFLAGS_DEPEND=-L../lib/libdebug -Wl,-rpath,'$$ORIGIN'
LDFLAGS_RELEASE=-L$(DIR_RELEASE) -Wl,-rpath,'$$ORIGIN'

#inotify names
SRC=inotify.cpp
SRC_TEST=inotify_test.cpp
TARGET_DEBUG=./inotify
TARGET_RELEASE=./outrelease/inotify
OBJ_DEBUG=./inotify.o
OBJ_RELEASE=./objrelease/inotify.o
DIR_DEBUG=../lib/libdebug/
DIR_RELEASE=../lib/librelease/
INC=../include/

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libinotify.so 

release: $(DIR_RELEASE)libinotify.so 

all: $(DIR_DEBUG)libinotify.so $(DIR_RELEASE)libinotify.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)libinotify.so $(SRC_TEST) 
	$(CC) $(CFLAGS) -o $@ $(SRC_TEST) $(LDFLAGS_DEBUG) -linotify 
	
#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)libinotify.so $(SRC_TEST) 
	$(CC) $(RFLAGS) $(LDFLAGS_RELEASE) -o $@ $(SRC_TEST) -linotify  

#Debug SO
$(DIR_DEBUG)libinotify.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $< $
	
#Release SO
$(DIR_RELEASE)libinotify.so: $(OBJ_RELEASE)
	$(CC) $(RFLAGS) -shared -o $@ $< 
	
#Debug Object
$(OBJ_DEBUG): $(SRC) $(INC)inotify.hpp    
	$(CC) $(CFLAGS) -c -fpic -o $@ $<

#Release Object
$(OBJ_RELEASE): $(SRC) $(INC)inotify.hpp
	$(CC) $(RFLAGS) -c -fpic -o $@ $<

.PHONY: clean
clean: 
	rm $(OBJ_DEBUG) $(OBJ_RELEASE) $(TARGET_DEBUG) 
