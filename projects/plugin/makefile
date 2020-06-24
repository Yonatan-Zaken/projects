#plugin makefile

#flags
CC=g++   
CFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -g -I$(INC)
RFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC) 
LDFLAGS_DEBUG=-L../lib/libdebug -Wl,-rpath=../lib/libdebug
LDFLAGS_DEPEND=-L../lib/libdebug -Wl,-rpath,'$$ORIGIN'
LDFLAGS_RELEASE=-L$(DIR_RELEASE) -Wl,-rpath,'$$ORIGIN'

#plugin names
SRC=plugin.cpp
SRC_TEST=plugin_test.cpp
TARGET_DEBUG=./plugin
TARGET_RELEASE=./outrelease/plugin
OBJ_DEBUG=./plugin.o
OBJ_RELEASE=./objrelease/plugin.o
DIR_DEBUG=../lib/libdebug/
DIR_RELEASE=../lib/librelease/
INC=../include/

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libplugin.so 

release: $(DIR_RELEASE)libplugin.so 

all: $(DIR_DEBUG)libplugin.so $(DIR_RELEASE)libplugin.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)libplugin.so $(SRC_TEST) 
	$(CC) $(CFLAGS) -o $@ $(SRC_TEST) $(LDFLAGS_DEBUG) -lplugin -ldl
	
#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)libplugin.so $(SRC_TEST) 
	$(CC) $(RFLAGS) $(LDFLAGS_RELEASE) -o $@ $(SRC_TEST) -lplugin  

#Debug SO
$(DIR_DEBUG)libplugin.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $< -ldl
	
#Release SO
$(DIR_RELEASE)libplugin.so: $(OBJ_RELEASE)
	$(CC) $(RFLAGS) -shared -o $@ $< 
	
#Debug Object
$(OBJ_DEBUG): $(SRC) $(INC)plugin.hpp    
	$(CC) $(CFLAGS) -c -fpic -o $@ $<

#Release Object
$(OBJ_RELEASE): $(SRC) $(INC)plugin.hpp
	$(CC) $(RFLAGS) -c -fpic -o $@ $<

.PHONY: clean
clean: 
	rm $(OBJ_DEBUG) $(OBJ_RELEASE) $(TARGET_DEBUG) 
