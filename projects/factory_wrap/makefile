#factory_wrap makefile

#flags
CC=g++   
CFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -g -I$(INC)
RFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC) 
LDFLAGS_DEBUG=-L../lib/libdebug -Wl,-rpath=../lib/libdebug
LDFLAGS_RELEASE=-L$(DIR_RELEASE) -Wl,-rpath,'$$ORIGIN'

#factory_wrap names
SRC=factory_wrap.cpp
SRC_TEST=factory_wrap_test.cpp
TARGET_DEBUG=./factory_wrap
TARGET_RELEASE=./outrelease/factory_wrap
OBJ_DEBUG=./factory_wrap.o
OBJ_RELEASE=./objrelease/factory_wrap.o
DIR_DEBUG=../lib/libdebug/
DIR_RELEASE=../lib/librelease/
INC=../include/

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libfactory_wrap.so 

release: $(DIR_RELEASE)libfactory_wrap.so 

all: $(DIR_DEBUG)libfactory_wrap.so $(DIR_RELEASE)libfactory_wrap.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)libfactory_wrap.so $(SRC_TEST) 
	$(CC) $(CFLAGS) $(LDFLAGS_DEBUG) -o $@ $(SRC_TEST) -lfactory_wrap 
	
#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)libfactory_wrap.so $(SRC_TEST) 
	$(CC) $(RFLAGS) $(LDFLAGS_RELEASE) -o $@ $(SRC_TEST) -lfactory_wrap  

#Debug SO
$(DIR_DEBUG)libfactory_wrap.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $< 
	  
#Release SO
$(DIR_RELEASE)libfactory_wrap.so: $(OBJ_RELEASE)
	$(CC) $(RFLAGS) -shared -o $@ $< 
	
#Debug Object
$(OBJ_DEBUG): $(SRC) $(INC)factory_wrap.hpp    
	$(CC) $(CFLAGS) -c -fpic -o $@ $<

#Release Object
$(OBJ_RELEASE): $(SRC) $(INC)factory_wrap.hpp
	$(CC) $(RFLAGS) -c -fpic -o $@ $<

.PHONY: clean
clean: 
	rm $(OBJ_DEBUG) $(OBJ_RELEASE) $(TARGET_DEBUG) 
