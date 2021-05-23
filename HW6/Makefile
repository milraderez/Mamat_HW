#!/bin/bash
CXX = g++
CXXLINK = $(CXX)
CXXFLAGS = -g -Wall -std=c++11
EXEC = firewall.exe
OBJS = main.o
RM = rm -rf *.o libfirewall.so $(EXEC)
LIBS = libfirewall.so libinput.so
LIB_OBJS = string.o field.o ip.o port.o

$(EXEC) : ${OBJS} ${LIBS}
	$(CXX) ${CXXFLAGS} $(OBJS) -o $(EXEC) -lfirewall -linput -L.

libfirewall.so: ${LIB_OBJS}
	$(CXXLINK) $(CXXFLAGS) -shared ${LIB_OBJS} -o libfirewall.so -L.

string.o: string.cpp string.h
	$(CXX) $(CXXFLAGS) -c -fpic string.cpp

field.o: field.cpp field.h string.h
	$(CXX) $(CXXFLAGS) -c -fpic field.cpp

ip.o: ip.cpp ip.h field.h
	$(CXX) $(CXXFLAGS) -c -fpic ip.cpp

port.o: port.cpp port.h field.h
	$(CXX) $(CXXFLAGS) -c -fpic port.cpp

main.o: main.cpp ip.h port.h string.h input.h
	$(CXX) $(CXXFLAGS) -c -fpic main.cpp

clean:
	$(RM)