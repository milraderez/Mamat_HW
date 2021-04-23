#!/bin/bash
CC = gcc
CCLINK = $(CC)
CFLAGS = -g -Wall -std=c99
EXEC = prog
OBJS = main.o file0.o file1.o file2.o file3.o file4.o
RM = rm -rf *.o *.exe $(EXEC)
STDLIB = /usr/include/stdlib.h
STDIO = /usr/include/stdio.h
#STDLIB and STDIO are full paths to the containing folder
#linking the exe
$(EXEC) : $(OBJS)
	$(CCLINK) $(OBJS) -o $(EXEC)

#dependcy objects
main.o: main.c file0.h file1.h file2.h file3.h file4.h $(STDIO) $(STDLIB)
	$(CC) $(CFLAGS) -c main.c

file0.o: file0.c file0.h file1.h file4.h $(STDIO) $(STDLIB)
	$(CC) $(CFLAGS) -c file0.c

file1.o: file1.c file1.h file2.h $(STDIO) $(STDLIB)
	$(CC) $(CFLAGS) -c file1.c

file2.o: file2.c file1.h file2.h file3.h $(STDIO) $(STDLIB)
	$(CC) $(CFLAGS) -c file2.c
				
file3.o: file3.c file3.h $(STDIO) $(STDLIB)
	$(CC) $(CFLAGS) -c file3.c	

file4.o: file4.c file0.h file4.h $(STDIO) $(STDLIB)
	$(CC) $(CFLAGS) -c file4.c			

#make clean
clean:
	$(RM)