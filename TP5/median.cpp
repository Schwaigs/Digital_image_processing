#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <cstdint>
#include <algorithm> 
#include <vector> 
#include "image.h"
#include "fileio.h"
#include "median.h"

void median(const char * nom_img_entree, const char *  nom_img_sortie, int n) {

    Image<uint8_t> image=readPGM(nom_img_entree);
    Image<uint8_t> image_sortie = Image<uint8_t>(image.getDx(),image.getDy());
    std::vector<uint8_t> voisins;

    // parcours des pixels de l'image
    for (int j = 0; j < image.getDy(); j++){
        for (int i = 0; i <image.getDx(); i++){

            // parcours du voisinnage
            for (int l = 0; l < n; l++){
                for (int k = 0; k < n; k++){
                    // Si le voisin est dans l'image
                    int posX_voisin = i + k - (n/2);
                    int posY_voisin = j + l - (n/2);

                    if ( (posX_voisin >= 0) && (posX_voisin < image.getDx()) && (posY_voisin >= 0) && (posY_voisin < image.getDy()) ){
                        voisins.push_back(image(posX_voisin,posY_voisin));
                    }

                }
            }
            
            std::sort(voisins.begin(),voisins.end());
            
            /*std::cout << "  val [ " << i << " , " << j << " ]  voisins :";
            for (int m = 0; m < (int)voisins.size(); m++)
                std::cout << ' ' << (int)voisins[m];
            std::cout << '\n';*/

            image_sortie(i,j) = voisins[((int)voisins.size())/2];
            //std::cout << "  val [ " << i << " , " << j << " ]  sortie index = " << ((int)voisins.size())/2 << " sortie = " << (int)image_sortie(i,j) << "\n";
        
            voisins.clear();
        }
    }
    
    writePGM(image_sortie, nom_img_sortie);
    
}