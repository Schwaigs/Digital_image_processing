#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <cstdint>
#include "image.h"
#include "fileio.h"
#include "histogramme.h"
#include "k_means.h"

int main(int argc, const char * argv[]) {
    if(argc !=4) {
        std::cout << "Usage : " << argv[0] << " <input.pgm> <output.pgm> parties\n";
        exit(EXIT_FAILURE);
    }

    Image<uint8_t> image=readPGM(argv[1]);
    int histo [256] = {};
    histogramme(image,histo);
    /*for (int k = 0; k < 256 ; k++){
        std::cout << k << " " << histo[k] << "\n";
    }*/
    int part = atoi(argv[3]);

    //initialisation des seuils pour chaque partie
    double * tab_seuils = (double *) malloc(part*sizeof(double));
    int borne = 0;
    for (int i = 0; i < part; i++){ //pour chaque partie 
        int r = rand()%(256-borne)+borne;
        tab_seuils[i] = (double) r;
        borne = tab_seuils[i];
        std::cout << "Seuil n°"<< i << " = " << borne << "\n";
    }
    double * tab_new_seuils = (double *) malloc(part*sizeof(double));
    for (int i = 0; i < part; i++){
        tab_new_seuils[i] = 0;
    }

    bool seuils_egaux = false;
    while(seuils_egaux == false){
        double borne_inf = 0;
        for (int i = 0; i < part; i++){
            std::cout << "Partie n°"<< i <<"\n";
            std::cout << "  Seuil  = " << tab_seuils[i] << "\n";
            double new_seuil = calcul_s(borne_inf,(tab_seuils[i]+tab_seuils[i+1])/2,histo);
            tab_new_seuils[i] = new_seuil;
            borne_inf = (tab_seuils[i]+tab_seuils[i+1])/2;
        }
        int cpt_same = 0;
        for (int j = 0; j < part; j++){
            if(tab_new_seuils[j] == tab_seuils[j]){
                cpt_same++;
            }
        }
        if(cpt_same == part){
            seuils_egaux = true;
        }
    }
    threshold(image,tab_new_seuils,argv[2],part);
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

double calcul_s(double inf, double sup, int * histo){
    //calul de la moyenne pour la partie
    double u = (1/somme_pixel(inf,sup,histo)) * somme_pour_moy(inf,sup,histo);
    std::cout << "  moyenne = " << u << "\n";

    return u;
}

void threshold(Image<uint8_t> image, double * seuils, const char * nom, int part){
    
    for (int j = 0; j < image.getDy(); j++){
        for (int i = 0; i <image.getDx(); i++){
            //au dela du dernier seuil le pixel prends la valeur de celui-ci
            if(seuils[part-1] < image(i,j)){
                image(i,j) = seuils[part-1];
            }
            //avant le premier seuil le pixel prends la valeur de celui-ci
            else if(seuils[0] > image(i,j)){
                image(i,j) = seuils[0];
            }
            else{
                int k = 1;
                while (seuils[k] < image(i,j)){
                   k++;
                }
                int s_min = seuils[k-1];
                int s_max = seuils[k];
                //cherche quel seuil est le plus proche
                if(image(i,j)-s_min > s_max-image(i,j)){
                    image(i,j) = seuils[s_max];
                }
                else{
                    image(i,j) = seuils[s_min];
                }
            }
        }
    }

    writePGM(image, nom);

    int new_histo [256] = {};
    histogramme(image,new_histo);
    for (int l = 0; l < part; l++){
        std::cout << "histo[" << l << "] = " << new_histo[l] << "\n";
    }
}
