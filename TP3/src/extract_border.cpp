#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <cstdint>
#include "image.h"
#include "fileio.h"
#include "extract_border.h"

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
    Image<uint8_t> image_sortie =Image<uint8_t>(image.getDx(),image.getDy());

    int nb_voisin = atoi(argv[3]);
    int * tab_voisin = (int *) malloc(nb_voisin*sizeof(int));

    for (int j = 0; j < image.getDy(); j++){
        for (int i = 0; i <image.getDx(); i++){
            //le point n'est pas noir
            if(image(i,j)!= 0){
                if(nb_voisin == 4){
                    voisins_4adj(j,i,image,tab_voisin);
                }
                else{
                    voisins_8adj(j,i,image,tab_voisin);
                }
                //parcours des voisins
                int nb_voisin_fond = 0;
                int nb_voisin_obj = 0;
                for (int k = 0; k < nb_voisin; k++){
                    if(tab_voisin[k] == 0){
                        nb_voisin_fond++;
                    }
                    else if(tab_voisin[k] == 255){
                        nb_voisin_obj++;
                    }
                }
                if( nb_voisin_fond > 0 && nb_voisin_obj > 0){
                    image_sortie(i,j) = 255;
                }
                else{
                    image_sortie(i,j) = 0;
                }
            }
            else{
                image_sortie(i,j) = 0;
            }
        }
    }

    writePGM(image_sortie, argv[2]);
    
}

void voisins_4adj(int j, int i, Image<uint8_t> image, int * tab){
    //regarde si on est au bord
    if(j == 0){
        tab[0] = -1;
    }
    else if(j == image.getDy()-1){
        tab[2] = -1;
    }
    else{
        tab[0] = image(i,j-1);
        tab[2] = image(i,j+1);
    }
    if(i == 0){
        tab[1] = -1;
    }
    else if(i == image.getDx()-1){
        tab[3] = -1;
    }
    else{
        tab[1] = image(i+1,j);
        tab[3] = image(i-1,j);
    }
}

void voisins_8adj(int j, int i, Image<uint8_t> image, int * tab){
    voisins_4adj(j,i,image,tab);
    //regarde si on est au bord
    if(j == 0){
        if(i == 0){
            tab[4] = -1;
            tab[5] = -1;
            tab[7] = -1;
            tab[6] = image(i+1,j+1);
        }
        else if(i == image.getDx()-1){
            tab[4] = -1;
            tab[5] = -1;
            tab[6] = -1;
            tab[7] = image(i-1,j+1);
        }
        else{
            tab[4] = -1;
            tab[5] = -1;
            tab[7] = image(i-1,j+1);
            tab[6] = image(i+1,j+1);
        }
    }
    else if(j == image.getDy()-1){
        if(i == 0){
            tab[4] = -1;
            tab[6] = -1;
            tab[7] = -1;
            tab[5] = image(i+1,j-1);
        }
        else if(i == image.getDx()-1){
            tab[7] = -1;
            tab[5] = -1;
            tab[6] = -1;
            tab[4] = image(i-1,j-1);
        }
        else{
            tab[4] = image(i-1,j-1);
            tab[5] = image(i+1,j-1);
        }
    }
    else{
        tab[7] = image(i-1,j+1);
        tab[6] = image(i+1,j+1);
        tab[4] = image(i-1,j-1);
        tab[5] = image(i+1,j-1);
    }
}