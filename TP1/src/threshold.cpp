#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <cstdint>
#include "image.h"
#include "fileio.h"

int main(int argc, const char * argv[]) {
     if(argc !=4) {
        std::cout << "Usage : " << argv[0] << " <input.pgm> <output.pgm> seuil\n";
        exit(EXIT_FAILURE);
    }

    int seuil = atoi(argv[3]);
    std::cout << "Seuil : " << seuil << "\n";

    Image<uint8_t> image=readPGM(argv[1]);
    
    for (int j = 0; j < image.getDy(); j++){
        for (int i = 0; i <image.getDx(); i++){
            if (image(i,j) < seuil){
                image(i,j) = 0;
            }
            else{
                image(i,j) = 255;
            }
        }
    }

    writePGM(image, argv[2]);

    return 0;
}