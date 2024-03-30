CXX = g++
CXXFLAGS = -Wall -Wfatal-errors -ggdb -pthread

TARGETS = ass02

.PHONY:	all clean cleanall

all: $(TARGETS)
ass02: main.o Uart.o
	$(CXX) -o $@ $^ $(CXXFLAGS)
	
main.o: main.c
	gcc -c main.c
	
Uart.o: Uart.c Uart.h
	gcc -c Uart.c
