CC = g++
CPPFLAGS = -Wall -Wextra -O3 -std=c++11

all: main print_info offset_img threshold negate compute_histo normalize equalize

fileio.o: fileio.cpp 
	$(CC) $(CPPFLAGS) -c fileio.cpp

histogramme.o: histogramme.h histogramme.cpp
	$(CC) $(CPPFLAGS) -c histogramme.cpp

print_info: print_info.o fileio.o
	$(CC) $(CPPFLAGS) print_info.o fileio.o -o print_info

print_info.o: print_info.cpp 
	$(CC) $(CPPFLAGS) -c print_info.cpp

offset_img: offset_img.o fileio.o
	$(CC) $(CPPFLAGS) offset_img.o fileio.o -o offset_img

offset_img.o: offset_img.cpp 
	$(CC) $(CPPFLAGS) -c offset_img.cpp

threshold: threshold.o fileio.o
	$(CC) $(CPPFLAGS) threshold.o fileio.o -o threshold

threshold.o: threshold.cpp 
	$(CC) $(CPPFLAGS) -c threshold.cpp

negate: negate.o fileio.o
	$(CC) $(CPPFLAGS) negate.o fileio.o -o negate

negate.o: negate.cpp 
	$(CC) $(CPPFLAGS) -c negate.cpp

compute_histo: compute_histo.o fileio.o histogramme.o
	$(CC) $(CPPFLAGS) compute_histo.o histogramme.o fileio.o -o compute_histo

compute_histo.o: compute_histo.cpp 
	$(CC) $(CPPFLAGS) -c compute_histo.cpp

normalize: normalize.o fileio.o histogramme.o
	$(CC) $(CPPFLAGS) normalize.o histogramme.o fileio.o -o normalize

normalize.o: normalize.cpp 
	$(CC) $(CPPFLAGS) -c normalize.cpp

equalize: equalize.o fileio.o histogramme.o
	$(CC) $(CPPFLAGS) equalize.o histogramme.o fileio.o -o equalize

equalize.o: equalize.cpp 
	$(CC) $(CPPFLAGS) -c equalize.cpp

main: main.o fileio.o
	$(CC) $(CPPFLAGS) main.o fileio.o -o main

main.o: main.cpp 
	$(CC) $(CPPFLAGS) -c main.cpp

clean:
	rm *.o