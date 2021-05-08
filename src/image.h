#ifndef image_h
#define image_h

#include <vector>

template <class T>
class Image
{
    /// classe générique codant une image de type T. T doit être précisé lors de l'instanciation.
    /// Exemple :
    /// Image<uint8_t> image(10,5);  // instancie une image dont les pixels sont de type uint8_t, de taille 10x5
    /// Image<float> image(512,512); // instancie une image dont les pixels sont de type float, de taille 512x512

  private:
    int dx;              /// largeur
    int dy;              /// hauteur
    int size;            /// nombre de pixels de l'image
    
    /// Tableau qui contient les valeurs des pixels de l'image. 
    /// Les pixels sont rangés ligne par ligne, de manière contigue
    /// Les valeurs des pixels ont le type T, qui est le paramètre de la classe générique.
    /// Par exemple, dans le cas d'une image 8 bits, le type est Image<uint8_t> et les valeurs ont toutes le type uint8_t
    std::vector<T> data; 
  
  public:
    /// construit une image de taille (dx,dy) (par défaut 0)
    Image(int dx = 0, int dy = 0);

    Image(int dx , int dy , const std::vector<T> &data);


    /// constructeur de copie, permettant d'écrire Image B; Image A(B);
    Image(const Image &image);

    /// opérateur d'affectation permettant d'écrire Image B; Image A=B;
    Image &operator=(const Image &);

    int getDx() const;
    int getDy() const;
    int getSize() const;
    std::vector<T> getData() const;

    /// valeur min
    T getMin() const;
    /// valeur max
    T getMax() const;

    /// affiche sur la sortie standard la valeur des pixels de l'image
    void print();

    /// surcharge de l'opérateur () permettant d'écrire une valeur à la position (x,y) : A(x,y)=v
    T &operator()(const int &x, const int &y);
    /// surcharge de l'opérateur () permettant de lire une valeur à la position (x,y) : v=A(x,y)
    T operator()(const int &x, const int &y) const;

     /// surcharge de l'opérateur () permettant d'écrire une valeur à l'indice i : A(i)=v
    T &operator()(const int &i);
    /// surcharge de l'opérateur () permettant de lire une valeur à l'indice i : v=A(i)
    T operator()(const int &i) const;
};

#include "image.hpp"

#endif /* image_h */
