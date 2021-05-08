#include "fileio.h"

/// 
/// Read grayscale 8bits image in binary PGM format
/// 
/// Exemple:
/// P5
/// 10 20
/// 255
/// ....... BINARY DATA   ..............
Image <uint8_t> readPGM(const std::string &inputFile)
{
    Image <uint8_t> error;
    std::ifstream file(inputFile);
    if(file.is_open()) {
        std::string line;
        std::getline(file,line);
        // only binary, greyscale PGM
        if(line=="P5") {
            int dx,dy,maxValue;
            std::getline(file,line);
            // remove comments beginning by '#'
            while(line[0]=='#') 
                std::getline(file,line);
            std::stringstream ss(line);
            ss >> dx >> dy;
            std::getline(file,line);
            ss.clear();
            ss.str(line);
            ss>>maxValue;
            int size=dx*dy;
            std::vector<uint8_t> buffer(size);
            file.read(reinterpret_cast<char *> (buffer.data()),size);
            Image <uint8_t> result(dx,dy,buffer);
            return result;
            
        }
        file.close();
    }
   
    return error;
}

///
/// Write grayscale 8bits image in binary PGM format
///
int writePGM(const Image<uint8_t> &image, const std::string &outputFile)
{
    std::ofstream file(outputFile,std::ios_base::trunc  | std::ios_base::binary);
    if(file.is_open()) {
        std::string line;
        
        int dx=image.getDx();
        int dy=image.getDy();
        int size=dx*dy;
        
        file << "P5\n" << dx << " " << dy << "\n" << "255" ;
        file << "\n";
        
        file.write(reinterpret_cast<char *>(image.getData().data()),size);
        
        file.close();
    }
    else return -1;
    
    return 0;
}

