#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <cstdint>
#include "image.h"
#include "fileio.h"

void histogramme(Image<uint8_t> image, int* histo){
    for (int j = 0; j < image.getDy(); j++){
        for (int i = 0; i <image.getDx(); i++){
            int val = image(i,j);
            histo[val]++;
        }
    }
}