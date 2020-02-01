#dhcp makefile

#flags
CC=gcc   
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g -I../include
RFLAGS=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I../include 
LDFLAGS_DEBUG=-L../libdebug -Wl,-rpath=../../libdebug
LDFLAGS_RELEASE=-L../librelease -Wl,-rpath=../../librelease

#file names
TARGET_DEBUG=./outdebug/dhcp
TARGET_RELEASE=./outrelease/dhcp
SRC=dhcp.c
OBJ_DEBUG=./objdebug/dhcp.o
OBJ_RELEASE=./objrelease/dhcp.o
SRC_TEST=dhcp_test.c
DIR_DEBUG=../libdebug/
DIR_RELEASE=../librelease/
INC=../include/dhcp.h

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libdhcp.so 

release: $(DIR_RELEASE)libdhcp.so 

all: $(DIR_DEBUG)libdhcp.so $(DIR_RELEASE)libdhcp.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)libdhcp.so $(SRC_TEST) 
	$(CC) $(CFLAGS) $(LDFLAGS_DEBUG) -o $@ $(SRC_TEST) -ldhcp

#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)libdhcp.so $(SRC_TEST) 
	$(CC) $(RFLAGS) $(LDFLAGS_RELEASE) -o $@ $(SRC_TEST) -ldhcp	

#Debug SO
$(DIR_DEBUG)libdhcp.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $< -L../libdebug -Wl,-rpath,'$$ORIGIN' \
	 -ltrie -L../libdebug -Wl,-rpath,'$$ORIGIN' -lip -lm

#Release SO
$(DIR_RELEASE)libdhcp.so: $(OBJ_RELEASE)
	$(CC) $(RFLAGS) -shared -o $@ $< -L../librelease -Wl,-rpath,'$$ORIGIN' \
	-ltrie -L../libdebug -Wl,-rpath,'$$ORIGIN' -lip -lm

#Debug Object
$(OBJ_DEBUG): $(SRC) $(INC)    
	$(CC) $(CFLAGS) -c -fpic -o $@ $<

#Release Object
$(OBJ_RELEASE): $(SRC) $(INC)
	$(CC) $(RFLAGS) -c -fpic -o $@ $<

.PHONY: clean
clean: 
	rm $(OBJ_DEBUG) $(OBJ_RELEASE) $(TARGET_DEBUG) 


















