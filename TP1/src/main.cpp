#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <cstdint>
#include "image.h"
#include "fileio.h"

int main(int argc, const char * argv[]) {
    if(argc !=3) {
        std::cout << "Usage : " << argv[0] << " <input.pgm> <output.pgm> \n";
        exit(EXIT_FAILURE);
    }

    Image<uint8_t> image=readPGM(argv[1]);
    
    writePGM(image, argv[2]);

    return 0;
}
