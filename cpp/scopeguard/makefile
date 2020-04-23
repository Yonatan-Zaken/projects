#scopeguard make

#flags
CC=g++   
CFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -g -I$(INC) \
-I../../system_programming/include
RFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC) 
LDFLAGS_DEBUG=-L$(DIR_DEBUG) -Wl,-rpath=../$(DIR_DEBUG)
LDFLAGS_RELEASE=-L$(DIR_RELEASE) -Wl,-rpath=../$(DIR_RELEASE)
LDFLAGS_WATCHDOG=-L$(DIR_WATCHDOG) -Wl,-rpath=../$(DIR_WATCHDOG) 

#scopeguard names
SRC=scopeguard.cpp
SRC_TEST=scopeguard_test.cpp
TARGET_DEBUG=./outdebug/scopeguard
TARGET_RELEASE=./outrelease/scopeguard
OBJ_DEBUG=./objdebug/scopeguard.o
OBJ_RELEASE=./objrelease/scopeguard.o
DIR_DEBUG=../lib/libdebug/
DIR_RELEASE=../lib/librelease/
DIR_WATCHDOG=../../system_programming/libdebug
INC=../include/

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libscopeguard.so 

release: $(DIR_RELEASE)libscopeguard.so 

all: $(DIR_DEBUG)libscopeguard.so $(DIR_RELEASE)libscopeguard.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)libscopeguard.so $(SRC_TEST) 
	$(CC) $(CFLAGS) $(LDFLAGS_DEBUG) -o $@ $(SRC_TEST) -lscopeguard \
	$(LDFLAGS_WATCHDOG) -lwd $(LDFLAGS_WATCHDOG) -lwdhelper -lpthread 
	 
#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)libscopeguard.so $(SRC_TEST) 
	$(CC) $(RFLAGS) $(LDFLAGS_RELEASE) -o $@ $(SRC_TEST) 

#Debug SO
$(DIR_DEBUG)libscopeguard.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $< 
	  
#Release SO
$(DIR_RELEASE)libscopeguard.so: $(OBJ_RELEASE)
	$(CC) $(RFLAGS) -shared -o $@ $< 
	
#Debug Object
$(OBJ_DEBUG): $(SRC) $(INC)scopeguard.hpp    
	$(CC) $(CFLAGS) -c -fpic -o $@ $<

#Release Object
$(OBJ_RELEASE): $(SRC) $(INC)scopeguard.hpp
	$(CC) $(RFLAGS) -c -fpic -o $@ $<

.PHONY: clean
clean: 
	rm $(OBJ_DEBUG) $(OBJ_RELEASE) $(TARGET_DEBUG) 
