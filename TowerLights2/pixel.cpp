#include "pixel.h"

Pixel::Pixel()
{
    color.setNamedColor("grey");
}

Pixel::Pixel(QColor c){
    color = c;
}

void Pixel::setColor(int r, int g, int b){
    color.setRgb(r, g, b);
}

void Pixel::setColor(QColor c){
    color = c;
}

QColor Pixel::getColor(){
    return color;
}

void Pixel::operator = (const Pixel& other){
    color = other.color;
}
