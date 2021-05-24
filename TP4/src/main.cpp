#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <cstdint>
#include "image.h"
#include "fileio.h"
#include "convolve.h"
#include "gaussianMask.h"
#include "detectArete.h"
#include "rehausseCouleur.h"

int main(int argc, const char * argv[]) {
    if(argc !=4) {
        std::cout << "Usage : " << argv[0] << " <input.pgm> <output.pgm> sigma\n";
        exit(EXIT_FAILURE);
    }
    double sigma = atof(argv[3]);

    Image<double> mask = gaussianMask(sigma);

    const char * entree = argv[1];
    //const char * entree_Y = argv[2];
    const char * sortie = argv[2];
    convolve(entree,sortie,mask);
    //rehausseCouleur(entree,sortie);
    //detectArete(entree,sortie);
    //communArete(entree,entree_Y,sortie);
    

    return 0;
}
