#include "pixel.h"

Pixel::Pixel(int x, int y)
{
    color.setNamedColor("grey");
    point.setX(x);
    point.setY(y);
}

Pixel::Pixel(QPoint p, QColor c){
    color = c;
    point = p;
}

void Pixel::setPoint(int x, int y){
    point.setX(x);
    point.setY(y);
}

void Pixel::setPoint(QPoint p){
    point = p;
}

void Pixel::setColor(int r, int g, int b){
    color.setRgb(r, g, b);
}

void Pixel::setColor(QColor c){
    color = c;
}

QPoint Pixel::getPoint(){
    return point;
}

QColor Pixel::getColor(){
    return color;
}

void Pixel::applyVector(int x, int y){
    point.setX(point.x() + x);
    point.setY(point.y() + y);
}

void Pixel::applyVector(QPoint p){
    point += p;
}

void Pixel::operator = (const Pixel& other){
    point = other.point;
    color = other.color;
}
