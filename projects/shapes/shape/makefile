#sorteshapes makeshapes

#flags
CC=g++   
CFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -g -I$(INC)
RFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC) 
LDFLAGS_DEBUG=-L$(DIR_DEBUG) -Wl,-rpath=../$(DIR_DEBUG)
LDFLAGS_RELEASE=-L$(DIR_RELEASE) -Wl,-rpath=../$(DIR_RELEASE)

#shapes names
SRC=shapes.cpp
SRC_TEST=shapes_test.cpp
TARGET_DEBUG=./outdebug/shapes
TARGET_RELEASE=./outrelease/shapes
OBJ_DEBUG=./objdebug/shapes.o
OBJ_RELEASE=./objrelease/shapes.o
DIR_DEBUG=../lib/
DIR_RELEASE=../lib/
INC=../include/

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libshapes.so 

release: $(DIR_RELEASE)libshapes.so 

all: $(DIR_DEBUG)libshapes.so $(DIR_RELEASE)libshapes.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)libshapes.so $(SRC_TEST) 
	$(CC) $(CFLAGS) $(LDFLAGS_DEBUG) -o $@ $(SRC_TEST) -lshapes -lpoint 
	
#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)libshapes.so $(SRC_TEST) 
	$(CC) $(RFLAGS) $(LDFLAGS_RELEASE) -o $@ $(SRC_TEST) -lshapes 

#Debug SO
$(DIR_DEBUG)libshapes.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $< -L$(DIR_DEBUG) -Wl,-rpath,'$$ORIGIN' -lpoint
	  
#Release SO
$(DIR_RELEASE)libshapes.so: $(OBJ_RELEASE)
	$(CC) $(RFLAGS) -shared -o $@ $< 
	
#Debug Object
$(OBJ_DEBUG): $(SRC) $(INC)shapes.hpp    
	$(CC) $(CFLAGS) -c -fpic -o $@ $<

#Release Object
$(OBJ_RELEASE): $(SRC) $(INC)shapes.hpp
	$(CC) $(RFLAGS) -c -fpic -o $@ $<

.PHONY: clean
clean: 
	rm $(OBJ_DEBUG) $(OBJ_RELEASE) $(TARGET_DEBUG) 
