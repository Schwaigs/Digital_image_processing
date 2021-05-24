CC = g++
CPPFLAGS = -Wall -Wextra -O3 -std=c++11

all: main extract_border dilate

fileio.o: fileio.cpp 
	$(CC) $(CPPFLAGS) -c fileio.cpp

extract_border: extract_border.o fileio.o
	$(CC) $(CPPFLAGS) extract_border.o fileio.o -o extract_border

extract_border.o: extract_border.cpp 
	$(CC) $(CPPFLAGS) -c extract_border.cpp

dilate: dilate.o fileio.o
	$(CC) $(CPPFLAGS) dilate.o fileio.o -o dilate

dilate.o: dilate.cpp 
	$(CC) $(CPPFLAGS) -c dilate.cpp

main: main.o fileio.o
	$(CC) $(CPPFLAGS) main.o fileio.o -o main

main.o: main.cpp 
	$(CC) $(CPPFLAGS) -c main.cpp

clean:
	rm *.o