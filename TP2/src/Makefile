CC = g++
CPPFLAGS = -Wall -Wextra -O3 -std=c++11

all: main otsu k_means

fileio.o: fileio.cpp 
	$(CC) $(CPPFLAGS) -c fileio.cpp

histogramme.o: histogramme.h histogramme.cpp
	$(CC) $(CPPFLAGS) -c histogramme.cpp

otsu: otsu.o fileio.o histogramme.o
	$(CC) $(CPPFLAGS) otsu.o histogramme.o fileio.o -o otsu

otsu.o: otsu.cpp 
	$(CC) $(CPPFLAGS) -c otsu.cpp

k_means: k_means.o fileio.o histogramme.o
	$(CC) $(CPPFLAGS) k_means.o histogramme.o fileio.o -o k_means

k_means.o: k_means.cpp 
	$(CC) $(CPPFLAGS) -c k_means.cpp

main: main.o fileio.o
	$(CC) $(CPPFLAGS) main.o fileio.o -o main

main.o: main.cpp 
	$(CC) $(CPPFLAGS) -c main.cpp

clean:
	rm *.o