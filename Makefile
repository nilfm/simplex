CC = g++
CFLAGS = -std=c++11 -O2 -Wall -Wextra -Wpedantic 

all: main.o Matrix.o Row.o
	$(CC) $(CFLAGS) -o main.x main.o Matrix.o Row.o
    
main.o: main.cc Matrix.cc Matrix.hh Row.cc Row.hh Includes.hh
	$(CC) $(CFLAGS) -c main.cc
    
Matrix.o: Matrix.cc Matrix.hh Row.cc Row.hh Includes.hh
	$(CC) $(CFLAGS) -c Matrix.cc
    
Row.o: Row.cc Row.hh Includes.hh
	$(CC) $(CFLAGS) -c Row.cc
