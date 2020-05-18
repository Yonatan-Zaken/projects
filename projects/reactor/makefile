#reactor makefile

#flags
CC=g++   
CFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -g -I$(INC) -I./
RFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC) 
LDFLAGS_DEBUG=-L../lib/libdebug -Wl,-rpath=../../lib/libdebug
LDFLAGS_RELEASE=-L$(DIR_RELEASE) -Wl,-rpath,'$$ORIGIN'

#reactor names
SRC=reactor.cpp
SRC_TEST=reactor_test.cpp
TARGET_DEBUG=./outdebug/reactor
TARGET_RELEASE=./outrelease/reactor
OBJ_DEBUG=./objdebug/reactor.o
OBJ_RELEASE=./objrelease/reactor.o
DIR_DEBUG=../lib/libdebug/
DIR_RELEASE=../lib/librelease/
INC=../include/

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libreactor.so 

release: $(DIR_RELEASE)libreactor.so 

all: $(DIR_DEBUG)libreactor.so $(DIR_RELEASE)libreactor.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)libreactor.so $(SRC_TEST) 
	$(CC) $(CFLAGS) -o $@ $(SRC_TEST) $(LDFLAGS_DEBUG) -lreactor 
	
#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)libreactor.so $(SRC_TEST) 
	$(CC) $(RFLAGS) -o $@ $(SRC_TEST) $(LDFLAGS_RELEASE) -lreactor
	
#Debug SO
$(DIR_DEBUG)libreactor.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $< -L$(DIR_DEBUG) -Wl,-rpath,'$$ORIGIN' -lfdlistner

#Release SO
$(DIR_RELEASE)libreactor.so: $(OBJ_RELEASE) 
	$(CC) $(RFLAGS) -shared -o $@ $< $(LDFLAGS_DEBUG) -lfdlistner
	
#Debug Object
$(OBJ_DEBUG): $(SRC) $(INC)reactor.hpp    
	$(CC) $(CFLAGS) -c -fpic -o $@ $<

#Release Object
$(OBJ_RELEASE): $(SRC) $(INC)reactor.hpp
	$(CC) $(RFLAGS) -c -fpic -o $@ $<

.PHONY: clean
clean: 
	rm $(OBJ_DEBUG) $(OBJ_RELEASE) $(TARGET_DEBUG) 
