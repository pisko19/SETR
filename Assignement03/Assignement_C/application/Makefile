DEFAULT_TARGET = sm
OBJECTS = ./Functions/Functions.o ./timers/timers.o ../src-gen/Statechart.o  ./main.o

CFLAGS = -g -Wall -O3 

# -pthread replaces -D_REENTRANT and -lpthreads
# from gcc manual "sets flags for both the preprocessor and linker"
CLFLAGS = -pthread

LDLIBS =
CC = gcc

INC = -I./timers -I./Functions -I./debug -I../src-gen -I../src

.PHONY : clean
.PHONY : run

# Generate application
$(DEFAULT_TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(DEFAULT_TARGET) $(CLFLAGS)
	
# Generate object files
%.o: %.c %.h
	$(CC) $(CFLAGS) $(CLFLAGS) $(INC) -c $< -o $@ 

# for  c files without .h
%.o: %.c
	$(CC) $(CFLAGS) $(CLFLAGS) $(INC) -c $< -o $@ 
	
clean:
	rm -f *.o $(DEFAULT_TARGET)

run: $(DEFAULT_TARGET)
	./$(DEFAULT_TARGET)

