#ifndef fileio_h
#define fileio_h

#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdint>
#include "image.h"

Image<uint8_t> readPGM(const std::string &inputFile);
int writePGM(const Image<uint8_t> &image8b, const std::string &outputFile);


#endif /* fileio_h */
