#include "Image.h"

void Image::ReadImage(string name) {
    fstream file(name, ios_base::in | ios_base::binary);
    if (file.is_open()) {
        file.read(&header.idLength, sizeof(header.idLength));
        file.read(&header.colorMapType, sizeof(header.colorMapType));
        file.read(&header.imageType, sizeof(header.imageType));
        file.read((char *)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
        file.read((char *)&header.colorMapLength, sizeof(header.colorMapLength));
        file.read((char *)&header.colorMapDepth, sizeof(header.colorMapDepth));

        file.read((char *)&header.xOrigin, sizeof(header.xOrigin));
        file.read((char *)&header.yOrigin, sizeof(header.yOrigin));
        file.read((char *)&header.width, sizeof(header.width));
        file.read((char *)&header.height, sizeof(header.height));
        file.read((char *)&header.bitsPerPixel, sizeof(header.bitsPerPixel));
        file.read((char *)&header.imageDescriptor, sizeof(header.imageDescriptor));

        unsigned int totalPixels = header.height * header.width;

        for (unsigned int i = 0; i < totalPixels; i++) {
            Pixel pixel;
            file.read((char *)&pixel.blue, sizeof(pixel.blue));
            file.read((char *)&pixel.green, sizeof(pixel.green));
            file.read((char *)&pixel.red, sizeof(pixel.red));

            pixel.bInt = CharToInt(pixel.blue);
            pixel.gInt = CharToInt(pixel.green);
            pixel.rInt = CharToInt(pixel.red);

            pixelVector.push_back(pixel);
        }
        file.close();
    }
}
void Image::WriteImage(string name) {
    fstream file(name, ios_base::out | ios_base::binary);

    file.write(&header.idLength, sizeof(header.idLength));
    file.write(&header.colorMapType, sizeof(header.colorMapType));
    file.write(&header.imageType, sizeof(header.imageType));
    file.write((char *)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
    file.write((char *)&header.colorMapLength, sizeof(header.colorMapLength));
    file.write((char *)&header.colorMapDepth, sizeof(header.colorMapDepth));

    file.write((char *)&header.xOrigin, sizeof(header.xOrigin));
    file.write((char *)&header.yOrigin, sizeof(header.yOrigin));
    file.write((char *)&header.width, sizeof(header.width));
    file.write((char *)&header.height, sizeof(header.height));
    file.write((char *)&header.bitsPerPixel, sizeof(header.bitsPerPixel));
    file.write((char *)&header.imageDescriptor, sizeof(header.imageDescriptor));

    for (unsigned int i = 0; i < pixelVector.size(); i++) {
        Pixel pixel = pixelVector.at(i);
        file.write((char *)&pixel.blue, 1);
        file.write((char *)&pixel.green, 1);
        file.write((char *)&pixel.red, 1);
    }
    file.close();



}

unsigned int Image::CharToInt(unsigned char _char) {
    return (unsigned int)(_char - '\0');
}

unsigned char Image::IntToChar(unsigned int _int) {
    return (unsigned char)(_int + '\0');
}

void Image::PrintHeader() {
    cout << header.idLength << endl;
    cout << header.colorMapType << endl;
    cout << header.imageType << endl;
    cout << header.colorMapOrigin << endl;
    cout << header.colorMapLength << endl;
    cout << header.colorMapDepth << endl;
    cout << header.xOrigin << endl;
    cout << header.yOrigin << endl;
    cout << header.width << endl;
    cout << header.height << endl;
    cout << header.bitsPerPixel << endl;
    cout << header.imageDescriptor << endl;
}

void Image::setInts() {
    for (unsigned int i = 0; i < pixelVector.size(); i++) {
        pixelVector[i].gInt = CharToInt(pixelVector[i].green);
        pixelVector[i].bInt = CharToInt(pixelVector[i].blue);
        pixelVector[i].rInt = CharToInt(pixelVector[i].red);
    }
}

Image::Header Image::getHeader() {
    return header;
}

void Image::setHeader(Image::Header &headerData) {
    header.idLength = headerData.idLength;
    header.colorMapType = headerData.colorMapType;
    header.imageType = headerData.imageType;
    header.colorMapOrigin = headerData.colorMapOrigin;
    header.colorMapLength = headerData.colorMapLength;
    header.colorMapDepth = headerData.colorMapDepth;
    header.xOrigin = headerData.xOrigin;
    header.yOrigin = headerData.yOrigin;
    header.width = headerData.width;
    header.height = headerData.height;
    header.bitsPerPixel = headerData.bitsPerPixel;
    header.imageDescriptor = headerData.imageDescriptor;
}

vector<Pixel> Image::getPixelVector() {
    return pixelVector;
}

void Image::setPixelVector(vector<Pixel> &_pixelVector) {
    for (unsigned int i = 0; i < _pixelVector.size(); i++) {
        pixelVector.push_back(_pixelVector[i]);
    }
}

void Image::PrintPixelVector() {
    for (unsigned int i = 0; i < pixelVector.size(); i++) {
        cout << CharToInt(pixelVector[i].red) << "," << CharToInt(pixelVector[i].green) << "," << CharToInt(pixelVector[i].blue) << endl;
    }
}

