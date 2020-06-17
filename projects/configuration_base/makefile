#config makefile

#flags
CC=g++   
CFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -g -I$(INC)
RFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC) 
LDFLAGS_DEBUG=-L../lib/libdebug -Wl,-rpath=../lib/libdebug
LDFLAGS_DEPEND=-L../lib/libdebug -Wl,-rpath,'$$ORIGIN'
LDFLAGS_RELEASE=-L$(DIR_RELEASE) -Wl,-rpath,'$$ORIGIN'

#config names
SRC=config.cpp
SRC_TEST=configuration_test.cpp
TARGET_DEBUG=./config
TARGET_RELEASE=./outrelease/config
OBJ_DEBUG=./config.o
OBJ_RELEASE=./objrelease/config.o
DIR_DEBUG=../lib/libdebug/
DIR_RELEASE=../lib/librelease/
INC=../include/

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libconfig.so 

release: $(DIR_RELEASE)libconfig.so 

all: $(DIR_DEBUG)libconfig.so $(DIR_RELEASE)libconfig.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)libconfig.so $(SRC_TEST) 
	$(CC) $(CFLAGS) -o $@ $(SRC_TEST) $(LDFLAGS_DEBUG) -lconfig 
	
#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)libconfig.so $(SRC_TEST) 
	$(CC) $(RFLAGS) $(LDFLAGS_RELEASE) -o $@ $(SRC_TEST) -lconfig  

#Debug SO
$(DIR_DEBUG)libconfig.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $< $ 
	
#Release SO
$(DIR_RELEASE)libconfig.so: $(OBJ_RELEASE)
	$(CC) $(RFLAGS) -shared -o $@ $< 
	
#Debug Object
$(OBJ_DEBUG): $(SRC) $(INC)config.hpp    
	$(CC) $(CFLAGS) -c -fpic -o $@ $<

#Release Object
$(OBJ_RELEASE): $(SRC) $(INC)config.hpp
	$(CC) $(RFLAGS) -c -fpic -o $@ $<

.PHONY: clean
clean: 
	rm $(OBJ_DEBUG) $(OBJ_RELEASE) $(TARGET_DEBUG) 
