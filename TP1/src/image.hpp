#include "image.h"

#include <iostream>
#include <cstring> // memcpy

template<class T>
Image<T>::Image(int dx, int dy):dx(0),dy(0)
{
    if(dx>=0 && dy>=0) {
        this->dx=dx;
        this->dy=dy;
        this->size=dx*dy;
        this->data=std::vector<T>(this->size);
    }    
}

template<class T>
Image<T>::Image(int dx, int dy, const std::vector<T> &data)
{
    if(dx>=0 && dy>=0 && data.size() == (unsigned long)dx*dy) {
        this->dx=dx;
        this->dy=dy;
        this->size=dx*dy;
        this->data=data;
    }    
}

template<class T>
Image<T>::Image(const Image<T> &image)
{
    this->dx=image.dx;
    this->dy=image.dy;
    this->size=image.size;
    this->data=image.data;    
}

template<class T>  
Image<T> &Image<T>::operator=(const Image<T> &image)
{
    if(this!=&image)
    {
    this->dx=image.dx;
    this->dy=image.dy;
    this->size=dx*dy;
    this->data=image.data;
    }
    return *this;
}

template<class T>
int Image<T>::getDx() const
{
    return dx;
}

template<class T>
int Image<T>::getDy() const
{
    return dy;
}

template<class T> 
int Image<T>::getSize() const
{
    return size;
}
    
template<class T> 
std::vector<T> Image<T>::getData() const
{
    return data;
}

/// valeur min
template<class T>
T Image<T>::getMin() const
{   
    if(this->data.size()==0) 
        return(T(0));
    T min=data[0];
    for(int i=0; i<size; ++i) {
        if(data[i] < min)
            min=data[i];
    }
    return min;
}

/// valeur max
template<class T>
T Image<T>::getMax() const
{
     if(this->data.size()==0) 
        return(T(0));
    T max=data[0];
    for(int i=0; i<size; ++i) {
        if(data[i] > max)
            max=data[i];
    }
    return max;
}
template<class T>
void Image<T>::print()
{
    
    for(int x=0; x<dx; x++) {
        std::cout.width(3);
        std::cout << "----";
    }
    std::cout << "\n";
    
    for(int y=0; y<dy; y++) {
        for(int x=0; x<dx; x++) {
            std::cout.width(3);
            std::cout << (double)(*this)(x,y) << "|";
        }
        std::cout << "\n";
        for(int x=0; x<dx; x++) {
            std::cout.width(3);
            std::cout << "----";
        }
        std::cout << "\n";
    }
}

    
template<class T>
T &Image<T>::operator()(const int &x, const int &y)
{
    return data[y*dx+x];
}

template<class T>
T Image<T>::operator() (const int &x, const int &y) const
{
    return data[y*dx+x];
}

   
template<class T>
T &Image<T>::operator()(const int &i)
{
    return data[i];
}

template<class T>
T Image<T>::operator() (const int &i) const
{
    return data[i];
}
    