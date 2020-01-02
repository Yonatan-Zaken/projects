#make file - this is a comment section
#compiler
CC=gcc -ansi -pedantic-errors -Wall -Wextra -g -I./../include\

#vsa file name
TARGET=vsa

#object files
OBJ=vsa.o vsa_test.o\

scheduler:  $(OBJ)   
	$(CC) -o $(TARGET) $(OBJ) 

.PHONY: clean
clean: 
	rm clean $(OBJ)
