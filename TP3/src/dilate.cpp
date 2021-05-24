#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <cstdint>
#include "image.h"
#include "fileio.h"
#include "dilate.h"

int main(int argc, const char * argv[]) {
    if(argc !=4) {
        std::cout << "Usage : " << argv[0] << " <input.pgm> <output.pgm> adjacence\n";
        exit(EXIT_FAILURE);
    }
    if(atoi(argv[3]) != 4 && atoi(argv[3]) != 8) {
        std::cout << "Usage : adjacence 4 ou 8\n";
        exit(EXIT_FAILURE);
    }

    Image<uint8_t> image=readPGM(argv[1]);
    Image<uint8_t> image_sortie =readPGM(argv[1]);

    int nb_voisin = atoi(argv[3]);

    for (int j = 0; j < image.getDy(); j++){
        for (int i = 0; i <image.getDx(); i++){
            //le point n'est pas noir
            if(image(i,j)!= 0){
                image_sortie(i,j) = 255;
                if(nb_voisin == 4){
                    dilate_voisins_4adj(j,i,image_sortie);
                }
                else{
                    dilate_voisins_8adj(j,i,image_sortie);
                }
            }
        }
    }

    writePGM(image_sortie, argv[2]);
    
}

void dilate_voisins_4adj(int j, int i, Image<uint8_t> &image_sortie){
    //regarde si on est au bord
    if(j == 0){
        image_sortie(i,j+1) = 255;
    }
    else if(j == image_sortie.getDy()-1){
        image_sortie(i,j-1) = 255;
    }
    else{
        image_sortie(i,j-1) = 255;
        image_sortie(i,j+1) = 255;
    }
    if(i == 0){
        image_sortie(i+1,j) = 255;
    }
    else if(i == image_sortie.getDx()-1){
        image_sortie(i-1,j) = 255;
    }
    else{
        image_sortie(i+1,j) = 255;
        image_sortie(i-1,j) = 255;
    }
}

void dilate_voisins_8adj(int j, int i,Image<uint8_t> &image_sortie){
    dilate_voisins_4adj(j,i,image_sortie);
    //regarde si on est au bord
    if(j == 0){
        if(i == 0){
            image_sortie(i+1,j+1) = 255;
        }
        else if(i == image_sortie.getDx()-1){
            image_sortie(i-1,j+1) = 255;
        }
        else{
            image_sortie(i-1,j+1) = 255;
            image_sortie(i+1,j+1) = 255;
        }
    }
    else if(j == image_sortie.getDy()-1){
        if(i == 0){
            image_sortie(i+1,j-1) = 255;
        }
        else if(i == image_sortie.getDx()-1){
            image_sortie(i-1,j-1) = 255;
        }
        else{
            image_sortie(i-1,j-1) = 255;
            image_sortie(i+1,j-1) = 255;
        }
    }
    else{
        image_sortie(i-1,j+1) = 255;
        image_sortie(i+1,j+1) = 255;
        image_sortie(i-1,j-1) = 255;
        image_sortie(i+1,j-1) = 255;
    }
}