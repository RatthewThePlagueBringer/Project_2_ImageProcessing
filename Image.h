#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#pragma once

using namespace std;

struct Pixel {
    unsigned char blue;
    unsigned char green;
    unsigned char red;
    unsigned int rInt;
    unsigned int bInt;
    unsigned int gInt;
};

class Image {
public:
    struct Header {
        char idLength;
        char colorMapType;
        char imageType;
        short colorMapOrigin;
        short colorMapLength;
        char colorMapDepth;
        short xOrigin;
        short yOrigin;
        short width;
        short height;
        char bitsPerPixel;
        char imageDescriptor;
    };

    //Loading
    void ReadImage(string name);

    //Writing
    void WriteImage(string name);

    //Converting
    unsigned int CharToInt(unsigned char _char);
    unsigned char IntToChar(unsigned int _int);

    void setInts();

    //Accessors/Mutators
    Header getHeader();
    void setHeader(Header &headerData);
    vector<Pixel> getPixelVector();
    void setPixelVector(vector<Pixel> &vect);

    void PrintHeader();
    void PrintPixelVector();

    Header header;
private:

    Pixel pixel;
    vector<Pixel> pixelVector;
};

