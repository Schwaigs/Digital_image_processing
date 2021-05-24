#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <cstdint>
#include "image.h"
#include "fileio.h"
#include "histogramme.h"
#include "normalize.h"

int main(int argc, const char * argv[]) {
     if(argc !=5) {
        std::cout << "Usage : " << argv[0] << " <input.pgm> <output.pgm> min max\n";
        exit(EXIT_FAILURE);
    }

    Image<uint8_t> image=readPGM(argv[1]);
    int Jmin = atoi(argv[3]);
    int Jmax = atoi(argv[4]);
    int histo [256] = {};
    histogramme(image,histo);
    
    double Imin = search_min_img(histo);
    std::cout << "Imin = " << Imin << "\n";
    double Imax = search_max_img(histo);
    std::cout << "Imax = " << Imax << "\n";
    normalize_img(image,Imin,Imax,Jmin,Jmax,argv[2]);
}

double search_min_img(int * histo){
    double min = 0;
    int i = 0;
    while (min == 0){
        min = (double)histo[i];
        i++;
    }
    return i-1;
}

double search_max_img(int * histo){
    double max = 0;
    int i = 255;
    while (max == 0){
        max = (double)histo[i];
        i--;
    }
    return i+1;
}

void normalize_img(Image<uint8_t> image, double Imin, double Imax, int Jmin, int Jmax,const char* nom){
    for (int j = 0; j < image.getDy(); j++){
        for (int i = 0; i <image.getDx(); i++){
            image(i,j) = (double)Jmin + (image(i,j) - Imin) * (((double)Jmax - (double)Jmin)/(Imax - Imin));
        }
    }
    writePGM(image,nom);
    int new_histo [256] = {};
    std::cout << "Histo 2 : \n";
    histogramme(image,new_histo);
    for (int k = 0; k < 256 ; k++){
        std::cout << k << " " << new_histo[k] << "\n";
    }
}