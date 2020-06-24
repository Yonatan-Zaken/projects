#dlopener makefile

#flags
CC=g++   
CFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -g -I$(INC)
RFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC) 
LDFLAGS_DEBUG=-L../lib/libdebug -Wl,-rpath=../lib/libdebug
LDFLAGS_DEPEND=-L../lib/libdebug -Wl,-rpath,'$$ORIGIN'
LDFLAGS_RELEASE=-L$(DIR_RELEASE) -Wl,-rpath,'$$ORIGIN'

#dlopener names
SRC=dlopener.cpp
SRC_TEST=dlopener_test.cpp
TARGET_DEBUG=./dlopener
TARGET_RELEASE=./outrelease/dlopener
OBJ_DEBUG=./dlopener.o
OBJ_RELEASE=./objrelease/dlopener.o
DIR_DEBUG=../lib/libdebug/
DIR_RELEASE=../lib/librelease/
INC=../include/

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libdlopener.so 

release: $(DIR_RELEASE)libdlopener.so 

all: $(DIR_DEBUG)libdlopener.so $(DIR_RELEASE)libdlopener.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)libdlopener.so $(SRC_TEST) 
	$(CC) $(CFLAGS) -o $@ $(SRC_TEST) $(LDFLAGS_DEBUG) -lplugin -lconfig -lframework -ltimer -ldirmonitor -lthread_pool -lplugin_manager -ldlopener -lboost_system -lboost_filesystem -lboost_chrono -lboost_thread -pthread -ldl
	
#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)libdlopener.so $(SRC_TEST) 
	$(CC) $(RFLAGS) $(LDFLAGS_RELEASE) -o $@ $(SRC_TEST) -ldlopener  

#Debug SO
$(DIR_DEBUG)libdlopener.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $< $(LDFLAGS_DEPEND) -lplugin $(LDFLAGS_DEPEND) -lplugin_manager -ldl
	
#Release SO
$(DIR_RELEASE)libdlopener.so: $(OBJ_RELEASE)
	$(CC) $(RFLAGS) -shared -o $@ $< 
	
#Debug Object
$(OBJ_DEBUG): $(SRC) $(INC)dlopener.hpp    
	$(CC) $(CFLAGS) -c -fpic -o $@ $<

#Release Object
$(OBJ_RELEASE): $(SRC) $(INC)dlopener.hpp
	$(CC) $(RFLAGS) -c -fpic -o $@ $<

.PHONY: clean
clean: 
	rm $(OBJ_DEBUG) $(OBJ_RELEASE) $(TARGET_DEBUG) 
