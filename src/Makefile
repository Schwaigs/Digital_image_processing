CC = g++
CPPFLAGS = -Wall -Wextra -O3 -std=c++11

all: main

fileio.o: fileio.cpp 
	$(CC) $(CPPFLAGS) -c fileio.cpp

median.o: median.cpp 
	$(CC) $(CPPFLAGS) -c median.cpp

bruit.o: bruit.cpp 
	$(CC) $(CPPFLAGS) -c bruit.cpp

computeMSE.o: computeMSE.cpp 
	$(CC) $(CPPFLAGS) -c computeMSE.cpp

main: main.o fileio.o median.o bruit.o computeMSE.o
	$(CC) $(CPPFLAGS) main.o fileio.o median.o bruit.o computeMSE.o -o main

main.o: main.cpp 
	$(CC) $(CPPFLAGS) -c main.cpp

clean:
	rm *.o