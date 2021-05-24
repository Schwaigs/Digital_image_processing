CC = g++
CPPFLAGS = -Wall -Wextra -O3 -std=c++11

all: main

fileio.o: fileio.cpp 
	$(CC) $(CPPFLAGS) -c fileio.cpp

convolve.o: convolve.cpp 
	$(CC) $(CPPFLAGS) -c convolve.cpp

gaussianMask.o: gaussianMask.cpp 
	$(CC) $(CPPFLAGS) -c gaussianMask.cpp

rehausseCouleur.o: rehausseCouleur.cpp 
	$(CC) $(CPPFLAGS) -c rehausseCouleur.cpp

detectArete.o: detectArete.cpp 
	$(CC) $(CPPFLAGS) -c detectArete.cpp

main: main.o fileio.o convolve.o gaussianMask.o rehausseCouleur.o detectArete.o
	$(CC) $(CPPFLAGS) main.o fileio.o convolve.o gaussianMask.o rehausseCouleur.o detectArete.o -o main

main.o: main.cpp 
	$(CC) $(CPPFLAGS) -c main.cpp

clean:
	rm *.o