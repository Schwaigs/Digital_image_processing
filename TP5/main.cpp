#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <cstdint>
#include "image.h"
#include "fileio.h"
#include "median.h"
#include "bruit.h"
#include "computeMSE.h"

int main(int argc, const char * argv[]) {

    if(argc < 2) {
        std::cout << "Arguments manquant ! Programmes possibles : 1 : median, 2 : impuls, 3 : gauss et 4 : mse \n";
        exit(EXIT_FAILURE);
    }

    switch(atoi(argv[1])){

        case 1: {
            if(argc !=5) {
                std::cout << "Usage : " << argv[0] << " 1 <input.pgm> <output.pgm> <filter_size>\n";
                exit(EXIT_FAILURE);
            }

            const char * entree = argv[2];
            const char * sortie = argv[3];
            int n = atoi(argv[4]);
            median(entree,sortie,n);
            break;
        }

        case 2: {
            if(argc !=5) {
                std::cout << "Usage : " << argv[0] << " 2 <input.pgm> <output.pgm> <probability>\n";
                exit(EXIT_FAILURE);
            }

            const char * entree = argv[2];
            const char * sortie = argv[3];
            double p = atof(argv[4]);
            bruit_impuls(entree,sortie,p);
            break;
        }

        case 3: {
            if(argc !=6) {
                std::cout << "Usage : " << argv[0] << " 3 <input.pgm> <output.pgm> <mu> <sigma>\n";
                exit(EXIT_FAILURE);
            }

            const char * entree = argv[2];
            const char * sortie = argv[3];
            double mu = atof(argv[4]);
            double sigma = atof(argv[5]);
            bruit_gauss(entree,sortie,mu,sigma);
            break;
        }

        case 4: {
            if(argc !=4) {
                std::cout << "Usage : " << argv[0] << " 4 <image1.pgm> <image2.pgm>\n";
                exit(EXIT_FAILURE);
            }

            const char * img1 = argv[2];
            const char * img2 = argv[3];
            computeMSE(img1,img2);
            break;
        }

        default:{
            std::cout << "Pas de programme pour " << argv[1] << " ! Programmes possibles : median, impuls, gauss et mse\n";
            exit(EXIT_FAILURE);
        }

    }

    return 0;
}
