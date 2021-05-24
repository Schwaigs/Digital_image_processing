#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <cstdint>
#include "image.h"
#include "fileio.h"
#include "histogramme.h"
#include "equalize.h"

int main(int argc, const char * argv[]) {
     if(argc !=3) {
        std::cout << "Usage : " << argv[0] << " <input.pgm> <output.pgm>\n";
        exit(EXIT_FAILURE);
    }

    Image<uint8_t> image=readPGM(argv[1]);
    int histo [256] = {};
    histogramme(image,histo);
    
    double Imin = search_min_img(histo);
    std::cout << "Imin = " << Imin << "\n";
    double Imax = search_max_img(histo);
    std::cout << "Imax = " << Imax << "\n";
    equalize_img(image,Imin,Imax,argv[2],histo);
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

double somme(double Imin, int offset, int * histo){
    double sum = 0;
    for (int j = Imin; j <= offset; j++){
        sum += histo[j];
    }
    return sum;
}

void equalize_img(Image<uint8_t> image, double Imin, double Imax,const char* nom, int * histo){
    for (int j = 0; j < image.getDy(); j++){
        for (int i = 0; i <image.getDx(); i++){
            std::cout << "test " << ((Imax - Imin) / (double)image.getSize()) << "\n";
            image(i,j) = ((Imax - Imin) / (double)image.getSize()) * somme(Imin,image(i,j),histo);
        }
    }
    writePGM(image,nom);
    int new_histo [256] = {};
    histogramme(image,new_histo);
    for (int k = 0; k < 256 ; k++){
        std::cout << k << " " << new_histo[k] << "\n";
    }
}