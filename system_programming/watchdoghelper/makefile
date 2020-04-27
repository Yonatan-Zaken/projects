#sortedlist makefile

#flags
CC=gcc   
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g -I../include -D_POSIX_C_SOURCE
RFLAGS=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I../include 
LDFLAGS_DEBUG=-L/home/yonatan10/yonatan-zaken/system_programming/libdebug \
-Wl,-rpath=/home/yonatan10/yonatan-zaken/system_programming/libdebug
LDFLAGS_RELEASE=-L../librelease -Wl,-rpath=../../librelease

#file names
TARGET_DEBUG=./outdebug/main_wd_out
TARGET_RELEASE=./outrelease/main_wd_out
SRC=wdhelper.c
OBJ_DEBUG=./objdebug/wdhelper.o
OBJ_RELEASE=./objrelease/wdhelper.o
SRC_TEST=main_wd.c
DIR_DEBUG=../libdebug/
DIR_RELEASE=../librelease/
INC=../include/wdhelper.h

.PHONY: clean release debug all

debug: $(DIR_DEBUG)libwdhelper.so 

release: $(DIR_RELEASE)libwdhelper.so 

all: $(DIR_DEBUG)libwdhelper.so $(DIR_RELEASE)libwdhelper.so

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)libwdhelper.so $(SRC_TEST) 
	$(CC) $(CFLAGS) $(LDFLAGS_DEBUG) -o $@ $(SRC_TEST) -lwdhelper -pthread

#Release Out	
$(TARGET_RELEASE): $(DIR_RELEASE)libwdhelper.so $(SRC_TEST) 
	$(CC) $(RFLAGS) $(LDFLAGS_RELEASE) -o $@ $(SRC_TEST) -lwdhelper -pthread	

#Debug SO
$(DIR_DEBUG)libwdhelper.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $< -L../libdebug -Wl,-rpath,'$$ORIGIN' \
	-lscheduler 

#Release SO
$(DIR_RELEASE)libwdhelper.so: $(OBJ_RELEASE)
	$(CC) $(RFLAGS) -shared -o $@ $< -L../librelease -Wl,-rpath,'$$ORIGIN' \
	-lscheduler 

#Debug Object
$(OBJ_DEBUG): $(SRC) $(INC)    
	$(CC) $(CFLAGS) -c -fpic -o $@ $<

#Release Object
$(OBJ_RELEASE): $(SRC) $(INC)
	$(CC) $(RFLAGS) -c -fpic -o $@ $<

.PHONY: clean
clean: 
	rm $(OBJ_DEBUG) $(OBJ_RELEASE) $(TARGET_DEBUG) 


















