#include <iostream>
#include <vector>
#include "Image.h"

using namespace std;

//Helper functions
float scaleValue(float _float){
    _float += 0.5f;
    return _float;
}

unsigned int clamp(int value){
    unsigned int result;
    if (value < 0){
        result = 0;
    }
    else if (value > 255){
        result = 255;
    }
    else {
        result = value;
    }
    return result;
}

float screenFunc(float factor, unsigned int a, unsigned int b){
    float result = 1.0f - factor * ((1.0f - ((float)(a) / 255.0f)) * (1.0f - ((float)(b) / 255.0f)));
    return result;
}

bool isDark(unsigned int value){
    return (value < (unsigned int)127);
}

Image multiply(Image &a, Image &b){
    Image result;
    Image::Header newHeader = a.getHeader();
    result.setHeader(newHeader);
    a.setInts();
    b.setInts();
    vector<Pixel> aPixels = a.getPixelVector();
    vector<Pixel> bPixels = b.getPixelVector();
    vector<Pixel> resultPixels;

    for (unsigned int i = 0; i < aPixels.size(); i++){
        Pixel resultPixel;
        unsigned int bInt = (unsigned int)(scaleValue(aPixels[i].bInt * bPixels[i].bInt / 255.0f));
        unsigned char bChar = a.IntToChar(bInt);
        resultPixel.blue = bChar;
        unsigned int gInt = (unsigned int)(scaleValue(aPixels[i].gInt * bPixels[i].gInt / 255.0f));
        unsigned char gChar = a.IntToChar(gInt);
        resultPixel.green = gChar;
        unsigned int rInt = (unsigned int)(scaleValue(aPixels[i].rInt * bPixels[i].rInt / 255.0f));
        unsigned char rChar = a.IntToChar(rInt);
        resultPixel.red = rChar;
        resultPixels.push_back(resultPixel);
    }
    result.setPixelVector(resultPixels);
    return result;
}

Image subtract(Image &a, Image &b){
    Image result;
    Image::Header newHeader = a.getHeader();
    result.setHeader(newHeader);
    a.setInts();
    b.setInts();
    vector<Pixel> aPixels = a.getPixelVector();
    vector<Pixel> bPixels = b.getPixelVector();
    vector<Pixel> resultPixels;
    int sub;

    for (unsigned int i = 0; i < aPixels.size(); i++){
        Pixel resultPixel;
        sub = aPixels[i].bInt - bPixels[i].bInt;
        unsigned int bInt = clamp(sub);
        unsigned char bChar = a.IntToChar(bInt);
        resultPixel.blue = bChar;
        sub = aPixels[i].gInt - bPixels[i].gInt;
        unsigned int gInt = clamp(sub);
        unsigned char gChar = a.IntToChar(gInt);
        resultPixel.green = gChar;
        sub = aPixels[i].rInt - bPixels[i].rInt;
        unsigned int rInt = clamp(sub);
        unsigned char rChar = a.IntToChar(rInt);
        resultPixel.red = rChar;
        resultPixels.push_back(resultPixel);
    }
    result.setPixelVector(resultPixels);
    return result;
}

Image screen(Image &a, Image &b){
    Image result;
    Image::Header newHeader = a.getHeader();
    result.setHeader(newHeader);
    a.setInts();
    b.setInts();
    vector<Pixel> aPixels = a.getPixelVector();
    vector<Pixel> bPixels = b.getPixelVector();
    vector<Pixel> resultPixels;

    for (unsigned int i = 0; i < aPixels.size(); i++){
        Pixel resultPixel;

        float blue = screenFunc(1.0f, aPixels[i].bInt, bPixels[i].bInt);
        unsigned int bInt = (unsigned int)scaleValue(blue * 255.0f);
        unsigned char bChar = a.IntToChar(bInt);
        resultPixel.blue = bChar;

        float green = screenFunc(1.0f, aPixels[i].gInt, bPixels[i].gInt);
        unsigned int gInt = (unsigned int)scaleValue(green * 255.0f);
        unsigned char gChar = a.IntToChar(gInt);
        resultPixel.green = gChar;

        float red = screenFunc(1.0f, aPixels[i].rInt, bPixels[i].rInt);
        unsigned int rInt = (unsigned int)scaleValue(red * 255.0f);
        unsigned char rChar = a.IntToChar(rInt);
        resultPixel.red = rChar;

        resultPixels.push_back(resultPixel);
    }
    result.setPixelVector(resultPixels);
    return result;
}

Image overlay(Image &a, Image &b){
    Image result;
    Image::Header newHeader = a.getHeader();
    result.setHeader(newHeader);
    a.setInts();
    b.setInts();
    vector<Pixel> aPixels = a.getPixelVector();
    vector<Pixel> bPixels = b.getPixelVector();
    vector<Pixel> resultPixels;

    for (unsigned int i = 0; i < aPixels.size(); i++){
        Pixel resultPixel;
        unsigned int bInt;
        unsigned int gInt;
        unsigned int rInt;
        //Blue
        if (isDark(bPixels[i].bInt)) {
            bInt = (unsigned int)(2.0f * scaleValue(aPixels[i].bInt * bPixels[i].bInt / 255.0f));
        }
        else {
            float blue = screenFunc(2.0f, aPixels[i].bInt, bPixels[i].bInt);
            bInt = (unsigned int)scaleValue(blue * 255.0f);
        }
        unsigned char bChar = a.IntToChar(bInt);
        resultPixel.blue = bChar;
        //Green
        if (isDark(bPixels[i].gInt)) {
            gInt = (unsigned int)(2.0f * scaleValue(aPixels[i].gInt * bPixels[i].gInt / 255.0f));
        }
        else {
            float green = screenFunc(2.0f, aPixels[i].gInt, bPixels[i].gInt);
            gInt = (unsigned int)scaleValue(green * 255.0f);
        }
        unsigned char gChar = a.IntToChar(gInt);
        resultPixel.green = gChar;
        //Red
        if (isDark(bPixels[i].rInt)) {
            rInt = (unsigned int)(2.0f * scaleValue(aPixels[i].rInt * bPixels[i].rInt / 255.0f));
        }
        else {
            float red = screenFunc(2.0f, aPixels[i].rInt, bPixels[i].rInt);
            rInt = (unsigned int)scaleValue(red * 255.0f);
        }
        unsigned char rChar = a.IntToChar(rInt);
        resultPixel.red = rChar;
        resultPixels.push_back(resultPixel);
    }
    result.setPixelVector(resultPixels);
    return result;
}

Image combine(Image &_rLayer, Image &_gLayer, Image &_bLayer){
    Image rLayer,gLayer,bLayer,result;
    rLayer = _rLayer;
    gLayer = _gLayer;
    bLayer = _bLayer;
    Image::Header newHeader = rLayer.getHeader();
    result.setHeader(newHeader);
    vector<Pixel> rPixels = rLayer.getPixelVector();
    vector<Pixel> gPixels = gLayer.getPixelVector();
    vector<Pixel> bPixels = bLayer.getPixelVector();
    vector<Pixel> outPixels;
    for (unsigned int i = 0; i < rPixels.size(); i++) {
        Pixel outPixel;
        outPixel.red = rPixels[i].red;
        outPixel.green = gPixels[i].green;
        outPixel.blue = bPixels[i].blue;
        outPixels.push_back(outPixel);
    }
    result.setPixelVector(outPixels);
    result.setInts();
    return result;
}

Image flip(Image &_input){
    Image input = _input;
    Image result;
    Image::Header newHeader = input.getHeader();
    result.setHeader(newHeader);
    vector<Pixel> inPixels = input.getPixelVector();
    vector<Pixel> outPixels;
    int i = newHeader.height * newHeader.width - 1;
    for (i; i > -1; --i) {
        Pixel outPixel;
        outPixel.red = inPixels[i].red;
        outPixel.green = inPixels[i].green;
        outPixel.blue = inPixels[i].blue;
        outPixels.push_back(outPixel);
    }
    result.setPixelVector(outPixels);
    result.setInts();
    return result;
}

Image onlyred(Image &_input){
    Image input = _input;
    Image result;
    Image::Header newHeader = input.getHeader();
    result.setHeader(newHeader);
    vector<Pixel> inPixels = input.getPixelVector();
    vector<Pixel> rPixels;
    for (unsigned int i = 0; i < inPixels.size(); i++) {
        Pixel rPixel;
        rPixel.red = inPixels[i].red;
        rPixel.green = inPixels[i].red;
        rPixel.blue = inPixels[i].red;
        rPixels.push_back(rPixel);
    }
    result.setPixelVector(rPixels);
    result.setInts();
    return result;
}

Image onlygreen(Image &_input){
    Image input = _input;
    Image result;
    Image::Header newHeader = input.getHeader();
    result.setHeader(newHeader);
    vector<Pixel> inPixels = input.getPixelVector();
    vector<Pixel> gPixels;
    for (unsigned int i = 0; i < inPixels.size(); i++) {
        Pixel gPixel;
        gPixel.red = inPixels[i].green;
        gPixel.green = inPixels[i].green;
        gPixel.blue = inPixels[i].green;
        gPixels.push_back(gPixel);
    }
    result.setPixelVector(gPixels);
    result.setInts();
    return result;
}

Image onlyblue(Image &_input){
    Image input = _input;
    Image result;
    Image::Header newHeader = input.getHeader();
    result.setHeader(newHeader);
    vector<Pixel> inPixels = input.getPixelVector();
    vector<Pixel> bPixels;
    for (unsigned int i = 0; i < inPixels.size(); i++) {
        Pixel bPixel;
        bPixel.red = inPixels[i].blue;
        bPixel.green = inPixels[i].blue;
        bPixel.blue = inPixels[i].blue;
        bPixels.push_back(bPixel);
    }
    result.setPixelVector(bPixels);
    result.setInts();
    return result;
}

Image addred(Image &_input, unsigned int redAdd){
    Image input = _input;
    Image result;
    vector<Pixel> inPixels = input.getPixelVector();
    Image::Header newHeader = input.getHeader();
    result.setHeader(newHeader);
    int temp;
    vector<Pixel> outPixels;
    for (unsigned int i = 0; i < inPixels.size(); i++) {
        Pixel outPixel;
        outPixel.green = inPixels[i].green;
        outPixel.blue = inPixels[i].blue;
        temp = inPixels[i].rInt + redAdd;
        unsigned int rInt = clamp(temp);
        unsigned char rChar = input.IntToChar(rInt);
        outPixel.red = rChar;
        outPixels.push_back(outPixel);
    }
    result.setPixelVector(outPixels);
    return result;
}

Image addgreen(Image &_input, unsigned int greenAdd){
    Image input = _input;
    Image result;
    vector<Pixel> inPixels = input.getPixelVector();
    Image::Header newHeader = input.getHeader();
    result.setHeader(newHeader);
    int temp;
    vector<Pixel> outPixels;
    for (unsigned int i = 0; i < inPixels.size(); i++) {
        Pixel outPixel;
        outPixel.red = inPixels[i].red;
        outPixel.blue = inPixels[i].blue;
        temp = inPixels[i].gInt + greenAdd;
        unsigned int gInt = clamp(temp);
        unsigned char gChar = input.IntToChar(gInt);
        outPixel.green = gChar;
        outPixels.push_back(outPixel);
    }
    result.setPixelVector(outPixels);
    return result;
}

Image addblue(Image &_input, unsigned int blueAdd){
    Image input = _input;
    Image result;
    vector<Pixel> inPixels = input.getPixelVector();
    Image::Header newHeader = input.getHeader();
    result.setHeader(newHeader);
    int temp;
    vector<Pixel> outPixels;
    for (unsigned int i = 0; i < inPixels.size(); i++) {
        Pixel outPixel;
        outPixel.green = inPixels[i].green;
        outPixel.red = inPixels[i].red;
        temp = inPixels[i].bInt + blueAdd;
        unsigned int bInt = clamp(temp);
        unsigned char bChar = input.IntToChar(bInt);
        outPixel.blue = bChar;
        outPixels.push_back(outPixel);
    }
    result.setPixelVector(outPixels);
    return result;
}

Image scalered(Image &_input, unsigned int redScale){
    Image input = _input;
    Image result;
    Image::Header newHeader = input.getHeader();
    result.setHeader(newHeader);
    vector<Pixel> inPixels = input.getPixelVector();
    vector<Pixel> outPixels;
    for (unsigned int i = 0; i < inPixels.size(); i++) {
        Pixel outPixel;
        unsigned int rInt;
        float red = ((float)inPixels[i].rInt / 255.0f) * (float)(redScale);
        rInt = (unsigned int)scaleValue(red * 255.0f);
        rInt = clamp(rInt);
        unsigned char rChar = input.IntToChar(rInt);
        outPixel.red = rChar;
        outPixel.green = inPixels[i].green;
        outPixel.blue = inPixels[i].blue;
        outPixels.push_back(outPixel);
    }
    result.setPixelVector(outPixels);
    result.setInts();
    return result;
}

Image scalegreen(Image &_input, unsigned int greenScale){
    Image input = _input;
    Image result;
    Image::Header newHeader = input.getHeader();
    result.setHeader(newHeader);
    vector<Pixel> inPixels = input.getPixelVector();
    vector<Pixel> outPixels;
    for (unsigned int i = 0; i < inPixels.size(); i++) {
        Pixel outPixel;
        unsigned int gInt;
        float green = ((float)inPixels[i].gInt / 255.0f) * (float)(greenScale);
        gInt = (unsigned int)scaleValue(green * 255.0f);
        gInt = clamp(gInt);
        unsigned char gChar = input.IntToChar(gInt);
        outPixel.green = gChar;
        outPixel.red = inPixels[i].red;
        outPixel.blue = inPixels[i].blue;
        outPixels.push_back(outPixel);
    }
    result.setPixelVector(outPixels);
    result.setInts();
    return result;
}

Image scaleblue(Image &_input, unsigned int blueScale){
    Image input = _input;
    Image result;
    Image::Header newHeader = input.getHeader();
    result.setHeader(newHeader);
    vector<Pixel> inPixels = input.getPixelVector();
    vector<Pixel> outPixels;
    for (unsigned int i = 0; i < inPixels.size(); i++) {
        Pixel outPixel;
        unsigned int bInt;
        float blue = ((float)inPixels[i].bInt / 255.0f) * (float)(blueScale);
        bInt = (unsigned int)scaleValue(blue * 255.0f);
        bInt = clamp(bInt);
        unsigned char bChar = input.IntToChar(bInt);
        outPixel.blue = bChar;
        outPixel.green = inPixels[i].green;
        outPixel.red = inPixels[i].red;
        outPixels.push_back(outPixel);
    }
    result.setPixelVector(outPixels);
    result.setInts();
    return result;
}

//Task functions
//Multiply
void task1(){
    Image layer,pattern,result;
    layer.ReadImage("input/layer1.tga");
    pattern.ReadImage("input/pattern1.tga");
    result = multiply(layer,pattern);
    result.WriteImage("input/part1.tga");
}

//Subtract
void task2(){
    Image layer,car,result;
    layer.ReadImage("input/layer2.tga");
    car.ReadImage("input/car.tga");
    result = subtract(car,layer);
    result.WriteImage("input/part2.tga");
}

//Screen Blend
void task3(){
    Image layer,pattern,temp,text,result;
    layer.ReadImage("input/layer1.tga");
    pattern.ReadImage("input/pattern2.tga");
    temp = multiply(layer, pattern);
    text.ReadImage("input/text.tga");
    result = screen(temp, text);
    result.WriteImage("input/part3.tga");
}

//Subtraction Blend
void task4(){
    Image layer,circles,temp,pattern,result;
    layer.ReadImage("input/layer2.tga");
    circles.ReadImage("input/circles.tga");
    temp = multiply(layer,circles);
    pattern.ReadImage("input/pattern2.tga");
    result = subtract(temp,pattern);
    result.WriteImage("input/part4.tga");
}

//Overlay Blend
void task5(){
    Image layer,pattern,result;
    layer.ReadImage("input/layer1.tga");
    pattern.ReadImage("input/pattern1.tga");
    result = overlay(layer,pattern);
    result.WriteImage("input/part5.tga");
}

//Green add
void task6(){
    Image car,result;
    car.ReadImage("input/car.tga");
    result = addgreen(car,200);
    result.WriteImage("input/part6.tga");
}

//Red/Blue multiply
void task7(){
    Image car,result;
    car.ReadImage("input/car.tga");
    result = scaleblue(car,0);
    result = scalered(result,4);
    result.WriteImage("input/part7.tga");
}

//Separate channels
void task8(){
    Image car,redOut,greenOut,blueOut;
    car.ReadImage("input/car.tga");
    redOut = onlyred(car);
    greenOut = onlygreen(car);
    blueOut = onlyblue(car);
    redOut.WriteImage("input/part8_r.tga");
    greenOut.WriteImage("input/part8_g.tga");
    blueOut.WriteImage("input/part8_b.tga");
}

//Combine channels
void task9(){
    Image rLayer,gLayer,bLayer,result;
    rLayer.ReadImage("input/layer_red.tga");
    gLayer.ReadImage("input/layer_green.tga");
    bLayer.ReadImage("input/layer_blue.tga");
    result = combine(rLayer,gLayer,bLayer);
    result.WriteImage("input/part9.tga");
}

//Rotate 180
void task10(){
    Image text,result;
    text.ReadImage("input/text2.tga");
    result = flip(text);
    result.WriteImage("input/part10.tga");
}


void isTGA(string input){
    try {
        if (input.substr(input.find('.'), 4) == ".tga") {
            string yes = "you did it!";
        }
    }
    catch(exception &ex) {
        cout << "Invalid argument, invalid file name." << endl;
    }
}

void todo(Image &_input, string firstImage, string output, vector<string> args) {

    isTGA(firstImage);
    Image trackingImage = _input;
    string method;
    bool isError = false;

    for (int i = 0; i < args.size(); i++) {

        method = args[i];

        //Multiply?
        if (method == "multiply") {
            try {
                string secondImage = args[i+1];
                isTGA(secondImage);
                Image input2;
                input2.ReadImage(secondImage);
                if (i == 0)
                    cout << "Mulitplying " << firstImage << " and " << secondImage << " ..." << endl;
                else
                    cout << "... and multiplying " << secondImage << " with previous step ..." << endl;
                trackingImage = multiply(trackingImage, input2);
                i++;
            }
            catch(exception &ex) {
                cout << "Missing argument." << endl;
                isError = true;
            }
        }
        //Subtract?
        else if (method == "subtract") {
            try {
                string secondImage = args[i+1];
                isTGA(secondImage);
                Image input2;
                input2.ReadImage(secondImage);
                if (i==0)
                cout << "Subtracting " << secondImage << " from " << firstImage << " ..." << endl;
                else
                cout << "... and subtracting " << secondImage << " from previous step ..." << endl;
                trackingImage = subtract(trackingImage, input2);
                i++;
            }
            catch(exception &ex) {
                cout << "Missing argument." << endl;
                isError = true;
            }
        }
        //Overlay?
        else if (method == "overlay") {
            try {
                string secondImage = args[i+1];
                isTGA(secondImage);
                Image input2;
                input2.ReadImage(secondImage);
                if (i==0)
                cout << "Overlaying " << firstImage << " with " << secondImage << " ..." << endl;
                else
                cout << "... and overlaying " << secondImage << " with previous step ..." << endl;
                trackingImage = overlay(trackingImage, input2);
                i++;
            }
            catch(exception &ex) {
                cout << "Missing argument." << endl;
                isError = true;
            }
        }
        //Screen?
        else if (method == "screen") {
            try {
                string secondImage = args[i+1];
                isTGA(secondImage);
                Image input2;
                input2.ReadImage(secondImage);
                if (i==0)
                cout << "Screening " << secondImage << " with " << firstImage << " ..." << endl;
                else
                cout << "... and screening " << secondImage << " with previous step ..." << endl;
                trackingImage = screen(input2, trackingImage);
                i++;
            }
            catch(exception &ex) {
                cout << "Missing argument." << endl;
                isError = true;
            }
        }
        //Combine?
        else if (method == "combine") {
            try {
                string secondImage = args[i+1];
                isTGA(secondImage);
                string thirdImage = args[i+2];
                isTGA(thirdImage);
                Image input2, input3;
                input2.ReadImage(secondImage);
                input3.ReadImage(thirdImage);
                if (i==0)
                cout << "Combining channels of " << firstImage << ", " << secondImage << ", and " << thirdImage << " ..."
                     << endl;
                else
                    cout << "... and combining previous step with the channels of " << secondImage << " and " << thirdImage << " ..." << endl;
                trackingImage = combine(trackingImage, input2, input3);
                i++;
                i++;
            }
            catch(exception &ex) {
                cout << "Missing argument." << endl;
                isError = true;
            }
        }
        //Flip?
        else if (method == "flip") {
            if (i==0)
            cout << "Flipping " << firstImage << " ..." << endl;
            else
                cout << "... and flipping output of previous step ..." << endl;
            trackingImage = flip(trackingImage);
        }
        //Onlyred?
        else if (method == "onlyred") {
            if (i==0)
                cout << "Separating the red channel from " << firstImage << " ..." << endl;
            else
                cout << "... and separating the red channel from previous step ..." << endl;
            trackingImage = onlyred(trackingImage);
        }
        //Onlygreen?
        else if (method == "onlygreen") {
            if (i==0)
                cout << "Separating the green channel from " << firstImage << " ..." << endl;
            else
                cout << "... and separating the red channel from previous step ..." << endl;
            trackingImage = onlygreen(trackingImage);
        }
        //Onlyblue?
        else if (method == "onlyblue") {
            if (i==0)
                cout << "Separating the blue channel from " << firstImage << " ..." << endl;
            else
                cout << "... and separating the red channel from previous step ..." << endl;
            trackingImage = onlyblue(trackingImage);
        }
        //Addred?
        else if (method == "addred") {
            try{
                string temp = args[i+1];
                try {
                    int add = stoi(temp);
                    if (i==0)
                        cout << "Adding " << add << " to the red channel of " << firstImage << " ..." << endl;
                    else
                        cout << "... and adding" << add << " to the red channel of previous step" << endl;
                    trackingImage = addred(trackingImage, add);
                    i++;
                }
                catch (exception &ex) {
                    cout << "Invalid argument, expected number." << endl;
                    isError = true;
                }
            }
            catch(exception &ex) {
                cout << "Missing argument." << endl;
                isError = true;
            }
        }
        //Addgreen?
        else if (method == "addgreen") {
            try{
                string temp = args[i+1];
                try {
                    int add = stoi(temp);
                    if (i==0)
                        cout << "Adding " << add << " to the green channel of " << firstImage << " ..." << endl;
                    else
                        cout << "... and adding" << add << " to the green channel of previous step" << endl;
                    trackingImage = addgreen(trackingImage, add);
                    i++;
                }
                catch (exception &ex) {
                    cout << "Invalid argument, expected number." << endl;
                    isError = true;
                }
            }
            catch(exception &ex) {
                cout << "Missing argument." << endl;
                isError = true;
            }
        }
        //Addblue?
        else if (method == "addblue") {
            try {
                string temp = args[i+1];
                try {
                    int add = stoi(temp);
                    if (i==0)
                        cout << "Adding " << add << " to the blue channel of " << firstImage << " ..." << endl;
                    else
                        cout << "... and adding" << add << " to the blue channel of previous step" << endl;
                    trackingImage = addblue(trackingImage, add);
                    i++;
                }
                catch (exception &ex) {
                    cout << "Invalid argument, expected number." << endl;
                    isError = true;
                }
            }
            catch(exception &ex) {
                cout << "Missing argument." << endl;
                isError = true;
            }
        }
        //Scalered?
        else if (method == "scalered") {
            try {
                string temp = args[i+1];
                try {
                    int factor = stoi(temp);
                    if(i==0)
                        cout << "Scaling the red channel of " << firstImage << " by " << factor << " ..." << endl;
                    else
                        cout << "... and scaling the red channel of previous step by " << factor << endl;
                    trackingImage = scalered(trackingImage, factor);
                    i++;
                }
                catch (exception &ex) {
                    cout << "Invalid argument, expected number." << endl;
                    isError = true;
                }
            }
            catch(exception &ex) {
                cout << "Missing argument." << endl;
                isError = true;
            }
        }
        //Scalegreen?
        else if (method == "scalegreen") {
            try {
                string temp = args[i+1];
                try {
                    int factor = stoi(temp);
                    if (i==0)
                        cout << "Scaling the green channel of " << firstImage << " by " << factor << " ..." << endl;
                    else
                        cout << "... and scaling the green channel of previous step by " << factor << endl;
                    trackingImage = scalegreen(trackingImage, factor);
                    i++;
                }
                catch (exception &ex) {
                    cout << "Invalid argument, expected number." << endl;
                    isError = true;
                }
            }
            catch(exception &ex) {
                cout << "Missing argument." << endl;
                isError = true;
            }
        }
        //Scaleblue?
        else if (method == "scaleblue") {
            try {
                string temp = args[i+1];
                try {
                    int factor = stoi(temp);
                    if (i==0)
                        cout << "Scaling the blue channel of " << firstImage << " by " << factor << " ..." << endl;
                    else
                        cout << "... and scaling the blue channel of previous step by " << factor << endl;
                    trackingImage = scaleblue(trackingImage, factor);
                    i++;
                }
                catch (exception &ex) {
                    cout << "Invalid argument, expected number." << endl;
                    isError = true;
                }
            }
            catch(exception &ex) {
                cout << "Missing argument." << endl;
                isError = true;
            }
        }
        else {
            if (!isError) {
                cout << "Invalid method name." << endl;
                isError = true;
            }
        }

    }
    if (!isError) {
        trackingImage.WriteImage(output);
        cout << "... and saving output to " << output << "!" << endl;
    }
}







//Main
int main(int argc, char* argv[]) {

    //Are there any arguments at all?
    if (argc > 1) {

        string init = argv[1];

        if (init == "--help") {
            cout << "Project 2: Image Processing, Spring 2023\n\nUsage:\n   ./project.exe [output] [firstImage] [method] [...]" << endl;
        }
        else {
            string output = argv[1];
            string firstImage = argv[2];
            Image start;
            start.ReadImage(firstImage);

            vector<string> args;
            for (unsigned int i = 3; i < argc; i++){
                string current = argv[i];
                args.push_back(current);
            }
            todo(start, firstImage, output, args);
        }
    }


    else {
        cout << "Project 2: Image Processing, Spring 2023\n\nUsage:\n   ./project.exe [output] [firstImage] [method] [...]" << endl;
    }


    // .\project2.exe output\test.tga input\layer2.tga subtract input\car.tga

//    task1();
//    task2();
//    task3();
//    task4();
//    task5();
//    task6();
//    task7();
//    task8();
//    task9();
//    task10();

    return 0;
}