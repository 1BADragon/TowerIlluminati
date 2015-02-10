#include "pixelgroup.h"

PixelGroup::PixelGroup()
{
}

void PixelGroup::addPixel(Pixel p){
    group.push_back(p);
}

PixelGroup PixelGroup::moveNew(int x, int y){

}

PixelGroup PixelGroup::moveNew(QPoint vector){

}

void PixelGroup::move(int x, int y){

}

void PixelGroup::move(QPoint vector){

}

void PixelGroup::setGroup(QList<Pixel> g){
    group = g;
}

int PixelGroup::getSize(){
    return group.size();
}
