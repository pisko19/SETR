CXX = g++
CXXFLAGS = -Wall -Wfatal-errors -ggdb -pthread

TARGETS = ass02

.PHONY: all clean cleanall

all: $(TARGETS)

ass02: main.o Uart.o Testes.o unity.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

main.o: ../source/main.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

Uart.o: ../source/Uart.c ../header/Uart.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

Testes.o: ../source/Testes.c ../header/Testes.h 
	$(CXX) $(CXXFLAGS) -c $< -o $@

unity.o: ../source/unity.c ../header/unity.h ../header/unity.h 
	$(CXX) $(CXXFLAGS) -c $< -o $@

