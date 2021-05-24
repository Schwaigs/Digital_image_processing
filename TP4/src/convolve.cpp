#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <cstdint>
#include "image.h"
#include "fileio.h"
#include "convolve.h"

void convolve(const char * nom_img_entree, const char *  nom_img_sortie, Image<double> &masque) {

    Image<uint8_t> image=readPGM(nom_img_entree);
    Image<double> image_sortie = Image<double>(image.getDx(),image.getDy());

    double val_total_masque = 0.0;
    for (int a = 0; a < masque.getDy(); a++){
        for (int b = 0; b < masque.getDx(); b++){
            val_total_masque += masque(b,a);
        }
    }
   //std::cout << "Total masque  = " << val_total_masque << "\n";

    // parcours des pixels de l'image
    for (int j = 0; j < image.getDy(); j++){
        for (int i = 0; i <image.getDx(); i++){

            // parcours du voisinnage
            double val_sortie = 0.0;
            for (int l = 0; l < masque.getDy(); l++){
                for (int k = 0; k < masque.getDx(); k++){
                    // Si le voisin est dans l'image
                    int posX_voisin = i + k - (masque.getDx()/2);
                    int posY_voisin = j + l - (masque.getDy()/2);
                    //std::cout << "pixel [ " << i << " , " << j << " ]  et voisin [ " << posX_voisin << " , " << posY_voisin << "]   val voisin = " << (double)image(posX_voisin,posY_voisin) << "  val masque = " << masque(k,l) << "\n";

                    if ( (posX_voisin >= 0) && (posX_voisin < image.getDx()) && (posY_voisin >= 0) && (posY_voisin < image.getDy()) ){
                        val_sortie += ( (double)image(posX_voisin,posY_voisin) ) * masque(k,l);
                    }

                }
            }

            image_sortie(i,j) = val_sortie/val_total_masque;
            //std::cout << "  val [ " << i << " , " << j << " ]  départ = " << (double)image(i,j) << " sortie = " << val_sortie << " arrivée = " << image_sortie(i,j) << "\n";
        }
    }
    
    // Convertion image_sortie en uint8_t
    Image<uint8_t> image_sortie_conv = Image<uint8_t>(image.getDx(),image.getDy());
    for (int j = 0; j < image_sortie.getDy(); j++){
        for (int i = 0; i <image_sortie.getDx(); i++){
            image_sortie_conv(i,j) = (uint8_t)image_sortie(i,j);
        }
    }    
    writePGM(image_sortie_conv, nom_img_sortie);
    
}