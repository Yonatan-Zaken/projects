#scopeguard make

#flags
CC=g++   
CFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -g -I$(INC) \
-I../../system_programming/include
RFLAGS=-std=c++98 -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -I$(INC) 
LDFLAGS_DEBUG=-L$(DIR_DEBUG) -Wl,-rpath=../$(DIR_DEBUG)
LDFLAGS_RELEASE=-L$(DIR_RELEASE) -Wl,-rpath=../$(DIR_RELEASE)
LDFLAGS_WATCHDOG=-L$(DIR_WATCHDOG) -Wl,-rpath=$(DIR_WATCHDOG) 

#scopeguard names
SRC=scopeguard.cpp
SRC_TEST=scopeguard_test.cpp
TARGET_DEBUG=./outdebug/scopeguard
TARGET_RELEASE=./outrelease/scopeguard
OBJ_DEBUG=./objdebug/scopeguard.o
OBJ_RELEASE=./objrelease/scopeguard.o
DIR_DEBUG=../lib/libdebug/
DIR_RELEASE=../lib/librelease/
DIR_WATCHDOG=/home/yonatan10/yonatan-zaken/system_programming/libdebug
INC=../include/

.PHONY: clean release debug all

all: 

test: $(TARGET_DEBUG)  

#Debug Out
$(TARGET_DEBUG): $(SRC_TEST) 
	$(CC) $(CFLAGS) -o $@ $(SRC_TEST) $(LDFLAGS_WATCHDOG) -lwd -pthread
	
.PHONY: clean
clean:
	rm $(OBJ_DEBUG) $(OBJ_RELEASE) $(TARGET_DEBUG) 
