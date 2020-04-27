#sorteshared_ptr makeshared_ptr

#flags
CC=g++   
CFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -g -I$(INC)
RFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC) 
LDFLAGS_DEBUG=-L$(DIR_DEBUG) -Wl,-rpath=../$(DIR_DEBUG)
LDFLAGS_RELEASE=-L$(DIR_RELEASE) -Wl,-rpath=../$(DIR_RELEASE)

#shared_ptr names
SRC=shared_ptr.cpp
SRC_TEST=shared_ptr_test.cpp
TARGET_DEBUG=./outdebug/shared_ptr
TARGET_RELEASE=./outrelease/shared_ptr
OBJ_DEBUG=./objdebug/shared_ptr.o
OBJ_RELEASE=./objrelease/shared_ptr.o
DIR_DEBUG=../lib/libdebug/
DIR_RELEASE=../lib/librelease/
INC=../include/

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libshared_ptr.so 

release: $(DIR_RELEASE)libshared_ptr.so 

all: $(DIR_DEBUG)libshared_ptr.so $(DIR_RELEASE)libshared_ptr.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)libshared_ptr.so $(SRC_TEST) 
	$(CC) $(CFLAGS) $(LDFLAGS_DEBUG) -o $@ $(SRC_TEST) -lshared_ptr -lpoint
	
#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)libshared_ptr.so $(SRC_TEST) 
	$(CC) $(RFLAGS) $(LDFLAGS_RELEASE) -o $@ $(SRC_TEST) -lshared_ptr 

#Debug SO
$(DIR_DEBUG)libshared_ptr.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $< 
	  
#Release SO
$(DIR_RELEASE)libshared_ptr.so: $(OBJ_RELEASE)
	$(CC) $(RFLAGS) -shared -o $@ $< 
	
#Debug Object
$(OBJ_DEBUG): $(SRC) $(INC)shared_ptr.hpp    
	$(CC) $(CFLAGS) -c -fpic -o $@ $<

#Release Object
$(OBJ_RELEASE): $(SRC) $(INC)shared_ptr.hpp
	$(CC) $(RFLAGS) -c -fpic -o $@ $<

.PHONY: clean
clean: 
	rm $(OBJ_DEBUG) $(OBJ_RELEASE) $(TARGET_DEBUG) 
