#sortedlist makefile

#flags
CC=gcc   
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g -I../include -D_POSIX_C_SOURCE
RFLAGS=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I../include 
LDFLAGS_DEBUG=-L../libdebug -Wl,-rpath=../../libdebug
LDFLAGS_RELEASE=-L../librelease -Wl,-rpath=../../librelease

#file names
TARGET_DEBUG=./outdebug/app
TARGET_RELEASE=./outrelease/app
SRC=wd.c
OBJ_DEBUG=./objdebug/wd.o
OBJ_RELEASE=./objrelease/wd.o
SRC_TEST=app.c
DIR_DEBUG=../libdebug/
DIR_RELEASE=../librelease/
INC=../include/wd.h

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libwd.so 

release: $(DIR_RELEASE)libwd.so 

all: $(DIR_DEBUG)libwd.so $(DIR_RELEASE)libwd.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)libwd.so $(SRC_TEST) 
	$(CC) $(CFLAGS) $(LDFLAGS_DEBUG) -o $@ $(SRC_TEST) -lwd -pthread

#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)libwd.so $(SRC_TEST) 
	$(CC) $(RFLAGS) $(LDFLAGS_RELEASE) -o $@ $(SRC_TEST) -lwd -pthread

#Debug SO
$(DIR_DEBUG)libwd.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $< -L../libdebug -Wl,-rpath,'$$ORIGIN' \
    -lwdhelper 

#Release SO
$(DIR_RELEASE)libwd.so: $(OBJ_RELEASE)
	$(CC) $(RFLAGS) -shared -o $@ $< -L../librelease -Wl,-rpath,'$$ORIGIN' \
	-lwdhelper 

#Debug Object
$(OBJ_DEBUG): $(SRC) $(INC)    
	$(CC) $(CFLAGS) -c -fpic -o $@ $<

#Release Object
$(OBJ_RELEASE): $(SRC) $(INC)
	$(CC) $(RFLAGS) -c -fpic -o $@ $<

.PHONY: clean
clean: 
	rm $(OBJ_DEBUG) $(OBJ_RELEASE) $(TARGET_DEBUG) 


















