#serializer makefile

#flags
CC=g++   
CFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -g -I$(INC) -I../shapes/include
RFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC) 
LDFLAGS_DEBUG=-L../lib/libdebug -Wl,-rpath=../../lib/libdebug
LDFLAGS_RELEASE=-L$(DIR_RELEASE) -Wl,-rpath,'$$ORIGIN'

#serializer names
SRC=serializer_test.cpp
SRC_TEST=serializer_test.cpp
TARGET_DEBUG=./outdebug/serializer
TARGET_RELEASE=./outrelease/serializer
OBJ_DEBUG=./objdebug/serializer_test.o
OBJ_RELEASE=./objrelease/serializer.o
DIR_DEBUG=../lib/libdebug/
DIR_RELEASE=../lib/librelease/
INC=../include/

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libserializer.so 

release: $(DIR_RELEASE)libserializer.so 

all: $(DIR_DEBUG)libserializer.so $(DIR_RELEASE)libserializer.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(SRC_TEST) 
	$(CC) $(CFLAGS) -o $@ $(SRC_TEST) -L../shapes/lib -Wl,-rpath=../../shapes/lib -lcircle -L../shapes/lib -Wl,-rpath=../shapes/lib -lshapes -L../shapes/lib -Wl,-rpath=../shapes/lib -lpoint -L../shapes/lib -Wl,-rpath=../shapes/lib -ldraw -L../shapes/lib -Wl,-rpath=../shapes/lib -lglut_utils
	
#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)libserializer.so $(SRC_TEST) 
	$(CC) $(RFLAGS) $(LDFLAGS_RELEASE) -o $@ $(SRC_TEST) -lserializer  

.PHONY: clean
clean: 
	rm $(OBJ_DEBUG) $(OBJ_RELEASE) $(TARGET_DEBUG) 
