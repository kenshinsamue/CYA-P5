
# Macros

CC = g++
OBJ = main.o set_calculator.o 

all: $(OBJ)
	$(CC) -std=c++14 -g -Wall -o set_calculator   $(OBJ)
	$(RM) $(OBJ)
clean:
	$(RM) $(OBJ) set_calculator
main.o: main.cc
set_calculator.o: set_calculator.cc

