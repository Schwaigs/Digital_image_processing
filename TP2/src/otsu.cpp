#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <cstdint>
#include "image.h"
#include "fileio.h"
#include "histogramme.h"
#include "otsu.h"

int main(int argc, const char * argv[]) {
    if(argc !=3) {
        std::cout << "Usage : " << argv[0] << " <input.pgm> <output.pgm>\n";
        exit(EXIT_FAILURE);
    }

    Image<uint8_t> image=readPGM(argv[1]);
    int histo [256] = {};
    histogramme(image,histo);
    for (int k = 0; k < 256 ; k++){
        std::cout << k << " " << histo[k] << "\n";
    }
    
    double n = image.getSize(); //nombre de pixel de l'image
    double var_inter = 0;
    int seuil = 0;
    for(int i = 0; i <256; i++){
        double var_seuil = otsu_seuil(i,n,histo);
        std::cout << "var inter = " << var_inter << " var seuil = " << var_seuil <<"\n";
        if(var_inter < var_seuil){
            var_inter = var_seuil;
            seuil = i;
        }
    }
    std::cout << "Seuil = " << seuil << "\n";

    threshold(image,seuil,argv[2]);
    
}

double somme_pour_moy(double c_min, int c_max, int * histo){
    double sum = 0;
    for (int j = c_min; j < c_max; j++){
        sum += histo[j] * j;
        //std::cout << "sum = " << sum << "   histo[ " << j << " ] = " << histo[j] << "\n";
    }
    //std::cout << "sum offset " << offset << " = " << sum << "\n";
    return sum;
}

double somme_pixel(double c_min, int c_max, int * histo){
    double sum = 0;
    for (int j = c_min; j < c_max; j++){
        sum += histo[j];
        //std::cout << "sum = " << sum << "   histo[ " << j << " ] = " << histo[j] << "\n";
    }
    //std::cout << "sum offset " << offset << " = " << sum << "\n";
    return sum;
}

double otsu_seuil(double seuil, double n, int * histo){
    std::cout << "Seuil  = " << seuil << "\n";
    double p_fg = somme_pixel(seuil,256,histo) / n;
    std::cout << "      pfg  = " << p_fg << "\n";
    double p_bg = somme_pixel(0,seuil,histo) / n;
    std::cout << "      pbg  = " << p_bg << "\n";
    double u_fg = (1/somme_pixel(seuil,256,histo)) * somme_pour_moy(seuil,256,histo);
    double u_bg = (1/somme_pixel(0,seuil,histo)) * somme_pour_moy(0,seuil,histo);

    double var_inter_classe = p_fg * p_bg * (u_bg - u_fg) * (u_bg - u_fg);
    return var_inter_classe;
}

void threshold(Image<uint8_t> image, double seuil, const char * nom){
    
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

    writePGM(image, nom);

    int new_histo [256] = {};
    histogramme(image,new_histo);
    std::cout << "histo[0] = " << new_histo[0] << "\n";
    std::cout << "histo[255] = " << new_histo[255] << "\n";
}
