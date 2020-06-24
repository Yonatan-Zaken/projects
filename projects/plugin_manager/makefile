#plugin_manager makefile

#flags
CC=g++   
CFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -g -I$(INC)
RFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC) 
LDFLAGS_DEBUG=-L../lib/libdebug -Wl,-rpath=../lib/libdebug
LDFLAGS_DEPEND=-L../lib/libdebug -Wl,-rpath,'$$ORIGIN'
LDFLAGS_RELEASE=-L$(DIR_RELEASE) -Wl,-rpath,'$$ORIGIN'

#plugin_manager names
SRC=plugin_manager.cpp
SRC_TEST=plugin_manager_test.cpp
TARGET_DEBUG=./plugin_manager
TARGET_RELEASE=./outrelease/plugin_manager
OBJ_DEBUG=./plugin_manager.o
OBJ_RELEASE=./objrelease/plugin_manager.o
DIR_DEBUG=../lib/libdebug/
DIR_RELEASE=../lib/librelease/
INC=../include/

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libplugin_manager.so 

release: $(DIR_RELEASE)libplugin_manager.so 

all: $(DIR_DEBUG)libplugin_manager.so $(DIR_RELEASE)libplugin_manager.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)libplugin_manager.so $(SRC_TEST) 
	$(CC) $(CFLAGS) -o $@ $(SRC_TEST) $(LDFLAGS_DEBUG) -lplugin_manager 
	
#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)libplugin_manager.so $(SRC_TEST) 
	$(CC) $(RFLAGS) $(LDFLAGS_RELEASE) -o $@ 

#Debug SO
$(DIR_DEBUG)libplugin_manager.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $< -lboost_filesystem
	
#Release SO
$(DIR_RELEASE)libplugin_manager.so: $(OBJ_RELEASE)
	$(CC) $(RFLAGS) -shared -o $@ $< 
	
#Debug Object
$(OBJ_DEBUG): $(SRC) $(INC)plugin_manager.hpp    
	$(CC) $(CFLAGS) -c -fpic -o $@ $<

#Release Object
$(OBJ_RELEASE): $(SRC) $(INC)plugin_manager.hpp
	$(CC) $(RFLAGS) -c -fpic -o $@ $<

.PHONY: clean
clean: 
	rm $(OBJ_DEBUG) $(OBJ_RELEASE) $(TARGET_DEBUG) 
