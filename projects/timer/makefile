#timer makefile

#flags
CC=g++   
CFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -g -I$(INC)
RFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC) 
LDFLAGS_DEBUG=-L../lib/libdebug -Wl,-rpath=../../lib/libdebug
LDFLAGS_RELEASE=-L$(DIR_RELEASE) -Wl,-rpath,'$$ORIGIN'

#timer names
SRC=timer.cpp
SRC_TEST=timer_test.cpp
TARGET_DEBUG=./outdebug/timer
TARGET_RELEASE=./outrelease/timer
OBJ_DEBUG=./objdebug/timer.o
OBJ_RELEASE=./objrelease/timer.o
DIR_DEBUG=../lib/libdebug/
DIR_RELEASE=../lib/librelease/
INC=../include/

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libtimer.so 

release: $(DIR_RELEASE)libtimer.so 

all: $(DIR_DEBUG)libtimer.so $(DIR_RELEASE)libtimer.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)libtimer.so $(SRC_TEST) 
	$(CC) $(CFLAGS) -o $@ $(SRC_TEST) $(LDFLAGS_DEBUG) -ltimer -lboost_system -lboost_chrono
	
#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)libtimer.so $(SRC_TEST) 
	$(CC) $(RFLAGS) $(LDFLAGS_RELEASE) -o $@ $(SRC_TEST) -ltimer  

#Debug SO
$(DIR_DEBUG)libtimer.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $<  -L$(DIR_DEBUG) -Wl,-rpath,'$$ORIGIN' -lreactor
	  
#Release SO
$(DIR_RELEASE)libtimer.so: $(OBJ_RELEASE)
	$(CC) $(RFLAGS) -shared -o $@ $< 
	
#Debug Object
$(OBJ_DEBUG): $(SRC) $(INC)timer.hpp    
	$(CC) $(CFLAGS) -c -fpic -o $@ $<

#Release Object
$(OBJ_RELEASE): $(SRC) $(INC)timer.hpp
	$(CC) $(RFLAGS) -c -fpic -o $@ $<

.PHONY: clean
clean: 
	rm $(OBJ_DEBUG) $(OBJ_RELEASE) $(TARGET_DEBUG) 
