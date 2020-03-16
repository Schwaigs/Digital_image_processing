#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <cstdint>
#include <random>
#include "image.h"
#include "fileio.h"
#include "median.h"

void bruit_impuls(const char * nom_img_entree, const char *  nom_img_sortie, double p) {

    Image<uint8_t> image=readPGM(nom_img_entree);
    Image<uint8_t> image_sortie = Image<uint8_t>(image.getDx(),image.getDy());

    // parcours des pixels de l'image
    for (int j = 0; j < image.getDy(); j++){
        for (int i = 0; i <image.getDx(); i++){
            
            //propabilité de devenir du bruit pour ce pixel
            int random = rand() % 100; //tire un chiffre enre 0 et 99

            if (random <= p*100){
                //soit noir soit blanc
                int color = rand() % 2;
                if(color == 0){
                    image_sortie(i,j) = 0;
                }
                else{
                    image_sortie(i,j) = 255;
                }
            }

            else{
                image_sortie(i,j) = image(i,j);
            }

            //std::cout << "  val [ " << i << " , " << j << " ]  départ = " << (int)image(i,j) << " random = " << random << " sortie = " << (int)image_sortie(i,j) << "\n";

        }
    }
    
    writePGM(image_sortie, nom_img_sortie);
    
}

void bruit_gauss(const char * nom_img_entree, const char *  nom_img_sortie, double mu, double sigma) {

    Image<uint8_t> image=readPGM(nom_img_entree);
    Image<double> image_sortie = Image<double>(image.getDx(),image.getDy());


    std::default_random_engine generator;
    std::normal_distribution<double> distribution(mu,sigma);

    // parcours des pixels de l'image
    for (int j = 0; j < image.getDy(); j++){
        for (int i = 0; i <image.getDx(); i++){
            
            double rand_val = distribution(generator);

            image_sortie(i,j) = image(i,j) + rand_val;
            
            if( image_sortie(i,j) < 0){
                image_sortie(i,j) = 0;
            }
            else if (image_sortie(i,j) > 255) {
                image_sortie(i,j) = 255;
            }
           
            //std::cout << "  val [ " << i << " , " << j << " ]  départ = " << (int)image(i,j) << " random = " << rand_val << " sortie = " << (double)image_sortie(i,j) << " sortie uint8_t = " << (int)image_sortie(i,j) << "\n";

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