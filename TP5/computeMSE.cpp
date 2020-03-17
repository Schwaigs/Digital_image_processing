#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <cstdint>
#include <tgmath.h>
#include "image.h"
#include "fileio.h"
#include "computeMSE.h"

void computeMSE(const char * nom_img_entree, const char *  nom_img_sortie) {

    Image<uint8_t> image = readPGM(nom_img_entree);
    Image<uint8_t> image_sortie = readPGM(nom_img_sortie);

    int mse = 0;

    //parcours des pixels de l'image
    for (int j = 0; j < image.getDy(); j++){
        for (int i = 0; i <image.getDx(); i++){

            //on ajoute pour chaque pixel le carré de la différence de niveau de gris entre les deux images
            mse += pow(image(i,j) - image_sortie(i,j),2);
            //std::cout << "  val [ " << i << " , " << j << " ]  départ = " << (int)image(i,j) << " random = " << random << " sortie = " << (int)image_sortie(i,j) << "\n";

        }
    }

    //on divise la somme obtenue par le nombre de pixel de nos images
    mse = mse/(image.getDx()*image.getDy());
    std::cout << "MSE =" << mse << "\n";
    
}