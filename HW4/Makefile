#!/bin/bash
CC = gcc
CCLINK = $(CC)
CFLAGS = -g -Wall -std=c99
EXEC = prog.exe
OBJS = libgrades.so
RM = rm -rf libgrades.so *.o
#linking the exe

#dependcy objects
libgrades.so: grades.o 
	$(CCLINK) -shared grades.o -o libgrades.so -llinked-list -L.

grades.o: grades.c grades.h linked-list.h
	$(CC) $(CFLAGS) -c -fpic grades.c		

#make clean
clean:
	$(RM)