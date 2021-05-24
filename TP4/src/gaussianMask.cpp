#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <cstdint>
#include <math.h>
#include "image.h"
#include "fileio.h"
#include "gaussianMask.h"

Image<double> gaussianMask(double sigma) {

    int n = 5*sigma;
    if( n % 2 != 1){
        n--;
    }

    Image<double> masque=Image<double>(n,n);
    double val_total_masque = 0.0;
    int centre = n/2;

    for (int j = 0; j < masque.getDy(); j++){
        for (int i = 0; i < masque.getDx(); i++){
            masque(i,j) = ( 1 / (2*M_PI*sigma*sigma) ) * exp( - ((i-centre)*(i-centre) + (j-centre)*(j-centre))/(2*sigma*sigma) );
            val_total_masque += masque(i,j);
            std::cout << "masque [ " << i << " , " << j << " ] = " << masque(i,j) << "\n";
        }
    }

    std::cout << "Total masque  = " << val_total_masque << "\n";
    return masque;
}