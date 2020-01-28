#scheduler makefile

#flags
CC=gcc   
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g -I../include -I../../ds/include
RFLAGS=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I../include \
-I../../ds/include  
LDFLAGS_DEBUG=-L../libdebug -Wl,-rpath=../../libdebug
LDFLAGS_RELEASE=-L../librelease -Wl,-rpath=../../librelease

#file names
TARGET_DEBUG=./outdebug/scheduler
TARGET_RELEASE=./outrelease/scheduler
SRC=scheduler.c
SRC_TASK=task.c
OBJ_DEBUG=./objdebug/scheduler.o
OBJ_DEBUG_TASK=./objdebug/task.o
OBJ_RELEASE=./objrelease/scheduler.o
OBJ_RELEASE_TASK=./objrelease/task.o
SRC_TEST=scheduler_test.c
DIR_DEBUG=../libdebug/
DIR_RELEASE=../librelease/
INC=../include/scheduler.h
INC_TASK=../include/task.h ../include/uid.h

.PHONY: clean release debug all test

debug: $(DIR_DEBUG)libtask.so $(DIR_DEBUG)libscheduler.so 

release: $(DIR_RELEASE)libtask.so $(DIR_RELEASE)libscheduler.so

all: debug release

test: $(TARGET_DEBUG) 

#Debug Out
$(TARGET_DEBUG): $(DIR_DEBUG)libscheduler.so $(SRC_TEST) 
	$(CC) $(CFLAGS) $(LDFLAGS_DEBUG) -o $@ $(SRC_TEST) -lscheduler 

#Release Out
$(TARGET_RELEASE): $(DIR_RELEASE)libscheduler.so $(SRC_TEST) 
	$(CC) $(RFLAGS) $(LDFLAGS_RELEASE) -o $@ $(SRC_TEST) -lscheduler	

#Debug SO
$(DIR_DEBUG)libscheduler.so: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -shared -o $@ $< -L../libdebug \
	-Wl,-rpath=/home/codesila/git/system_programming/libdebug -ltask \
	-L../../ds/libdebug -Wl,-rpath=/home/codesila/git/ds/libdebug -lheapify
	
$(DIR_DEBUG)libtask.so: $(OBJ_DEBUG_TASK)
	$(CC) $(CFLAGS) -shared -o $@ $< -L../libdebug \
	-Wl,-rpath=/home/codesila/git/system_programming/libdebug -luid

#Release SO
$(DIR_RELEASE)libscheduler.so: $(OBJ_RELEASE)
	$(CC) $(RFLAGS) -shared -o $@ $< -L../librelease \
	-Wl,-rpath=/home/codesila/git/system_programming/librelease -ltask \
	-L../../ds/librelease -Wl,-rpath=/home/codesila/git/ds/librelease -lheapify 

$(DIR_RELEASE)libtask.so: $(OBJ_RELEASE_TASK)
	$(CC) $(RFLAGS) -shared -o $@ $< -L../librelease \
	-Wl,-rpath=/home/codesila/git/system_programming/librelease -luid 

#Debug Object
$(OBJ_DEBUG): $(SRC) $(INC)    
	$(CC) $(CFLAGS) -c -fpic -o $@ $<

$(OBJ_DEBUG_TASK): $(SRC_TASK) $(INC_TASK) 	
	$(CC) $(CFLAGS) -c -fpic -o $@ $<
    
#Release Object
$(OBJ_RELEASE): $(SRC) $(INC)
	$(CC) $(RFLAGS) -c -fpic -o $@ $<

$(OBJ_RELEASE_TASK): $(SRC_TASK) $(INC_TASK)
	$(CC) $(RFLAGS) -c -fpic -o $@ $<

.PHONY: clean
clean: 
	rm $(OBJ_DEBUG) $(OBJ_RELEASE) $(TARGET_DEBUG) 


















