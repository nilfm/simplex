CC = g++
CFLAGS = -std=c++11 -O2 -Wall -Wextra -Wpedantic 

all: main.o Matrix.o Row.o Simplex.o
	$(CC) $(CFLAGS) -o main.x main.o Matrix.o Row.o Simplex.o
    
main.o: main.cc Matrix.cc Matrix.hh Row.cc Row.hh Simplex.hh Simplex.cc Includes.hh
	$(CC) $(CFLAGS) -c main.cc
   
Simplex.o: Simplex.cc Simplex.hh Matrix.cc Matrix.hh Row.cc Row.hh
	$(CC) $(CFLAGS) -c Simplex.cc

Matrix.o: Matrix.cc Matrix.hh Row.cc Row.hh Includes.hh
	$(CC) $(CFLAGS) -c Matrix.cc
    
Row.o: Row.cc Row.hh Includes.hh
	$(CC) $(CFLAGS) -c Row.cc

clean:
	rm *.x *.o
