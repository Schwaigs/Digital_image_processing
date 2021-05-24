#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <cstdint>
#include "image.h"
#include "fileio.h"

int main(int argc, const char * argv[]) {
    if(argc !=2) {
        std::cout << "Usage : " << argv[0] << " <input.pgm> \n";
        exit(EXIT_FAILURE);
    }

    Image<uint8_t> image=readPGM(argv[1]);
    int dx = image.getDx();
    int dy = image.getDy();
    std::cout << "Dx : " << dx << "  Dy : " << dy <<"\n";

    int nb_pix = image.getSize();
    std::cout << "Nombre de pixels : " << nb_pix <<"\n";

    int val_min = image.getMin();
    int val_max = image.getMax();
    std::cout << "Valeur minimale : " << val_min << "  Valeur maximale : " << val_max <<"\n";
    
    int val_sum = 0;
    for (int i = 0; i < dx; i++){
        for (int j = 0; j < dy; j++){
            val_sum += image(i,j);
        }
    }
    std::cout << "Somme des valeurs des pixels : " << val_sum <<"\n";

    int moyenne = val_sum /nb_pix;
    std::cout << "Niveau de gris moyen : " << moyenne <<"\n";

    return 0;
}