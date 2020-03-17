#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <cstdint>
#include <random>
#include "image.h"
#include "fileio.h"
#include "median.h"

void bruit_impuls(const char * nom_img_entree, const char *  nom_img_sortie, double p) {
    //p la propabilité pour pixel d'être corrompu

    Image<uint8_t> image=readPGM(nom_img_entree);
    Image<uint8_t> image_sortie = Image<uint8_t>(image.getDx(),image.getDy());

    //parcours des pixels de l'image
    for (int j = 0; j < image.getDy(); j++){
        for (int i = 0; i <image.getDx(); i++){
            
            //on tire un chiffre entre 0 et 99
            int random = rand() % 100; 

            //si le nombre aléatoire tiré est plus petit que la probabilité p
            //alors le pixel est corrumpu
            if (random <= p*100){

                //tirage d'un deuxième chiffre (0 ou 1)
                int color = rand() % 2;

                //si le chiffre tiré vaut 0 le pixel devient noir
                if(color == 0){
                    image_sortie(i,j) = 0;
                }
                //sinon le pixel devient blanc
                else{
                    image_sortie(i,j) = 255;
                }
            }

            //sinon le pixel garde le même niveau de gris
            else{
                image_sortie(i,j) = image(i,j);
            }

            //std::cout << "  val [ " << i << " , " << j << " ]  départ = " << (int)image(i,j) << " random = " << random << " sortie = " << (int)image_sortie(i,j) << "\n";

        }
    }

    //on ecrit l'image obtenue
    writePGM(image_sortie, nom_img_sortie);
    
}

void bruit_gauss(const char * nom_img_entree, const char *  nom_img_sortie, double mu, double sigma) {
    //mu la moyenne autour de laquelle va se centrer la distribution du bruit
    //sigma l'écart type de la distribution

    Image<uint8_t> image=readPGM(nom_img_entree);
    Image<double> image_sortie = Image<double>(image.getDx(),image.getDy());

    //On se sert d'une distribution normale pour générer le bruit sur notre image
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(mu,sigma);

    //parcours des pixels de l'image
    for (int j = 0; j < image.getDy(); j++){
        for (int i = 0; i <image.getDx(); i++){
            
            //on tire une valeur aléatoire 
            //chaque pixel est corrumpu en additionnant cette valeur aléatoire à son niveau de gris initial
            double rand_val = distribution(generator);

            //les niveaux de gris des pixels ne doivent pas sortir des bornes O et 255
            //donc en cas de dépassement, on attribut les valeurs extêmes
            if( (int)image(i,j) + rand_val < 0){
                image_sortie(i,j) = 0;
            }
            else if ( (int)image(i,j) + rand_val > 255) {
                image_sortie(i,j) = 255;
            }
            else {
                image_sortie(i,j) = image(i,j) + rand_val;
            }
            
            //std::cout << "  val [ " << i << " , " << j << " ]  départ = " << (int)image(i,j) << " random = " << rand_val << " sortie = " << (double)image_sortie(i,j) << " sortie uint8_t = " << (int)image_sortie(i,j) << "\n";

        }
    }
    
    //Convertion de notre image de sortie en uint8_t
    Image<uint8_t> image_sortie_conv = Image<uint8_t>(image.getDx(),image.getDy());
    for (int j = 0; j < image_sortie.getDy(); j++){
        for (int i = 0; i <image_sortie.getDx(); i++){
            image_sortie_conv(i,j) = (uint8_t)image_sortie(i,j);
        }
    } 

    //on ecrit l'image obtenue
    writePGM(image_sortie_conv, nom_img_sortie);
    
}