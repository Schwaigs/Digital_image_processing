#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <cstdint>
#include "image.h"
#include "fileio.h"
#include "histogramme.h"

int main(int argc, const char * argv[]) {
     if(argc !=2) {
        std::cout << "Usage : " << argv[0] << " <input.pgm>\n";
        exit(EXIT_FAILURE);
    }

    Image<uint8_t> image=readPGM(argv[1]);
    int histo [256] = {};
    histogramme(image,histo);

    for (int k = 0; k < 256 ; k++){
        std::cout << k << " " << histo[k] << "\n";
    }
    return 0;
}
