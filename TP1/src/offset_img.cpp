#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <cstdint>
#include "image.h"
#include "fileio.h"

int main(int argc, const char * argv[]) {
    if(argc !=3) {
        std::cout << "Usage : " << argv[0] << " dx dy\n";
        exit(EXIT_FAILURE);
    }
    int dx = atoi(argv[1]);
    int dy = atoi(argv[2]);

    Image<uint8_t> image = Image<uint8_t>(dx,dy);

    for (uint8_t j = 0; j < dy; j++){
        for (uint8_t i = 0; i <dx; i++){
            image(i,j) = j*dx+i;
        }
    }

    image.print();
    return 0;
}