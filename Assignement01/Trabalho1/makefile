CXX = g++
CXXFLAGS = -Wall -Wfatal-errors -ggdb -pthread

TARGETS = ass01

.PHONY:	all clean cleanall

all: $(TARGETS)
ass01: main.o MyDLL.o Testes.o
	$(CXX) -o $@ $^ $(CXXFLAGS)
	
main.o: main.c
	gcc -c main.c
	
MyDLL.o: MyDLL.c MyDLL.h
	gcc -c MyDLL.c
	
Testes.o: Testes.c Testes.h
	gcc -c Testes.c
