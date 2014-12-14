#include "pixelgroup.h"

PixelGroup::PixelGroup()
{
}

void PixelGroup::addPixel(Pixel p){
    group.push_back(p);
}

PixelGroup PixelGroup::moveNew(int x, int y){
    int length = group.size();
    for(int i = 0; i < length; i++){
        group[i].applyVector(x,y);
    }
    PixelGroup temp;
    temp.setGroup(group);
    return temp;
}

PixelGroup PixelGroup::moveNew(QPoint vector){
    int length = group.size();
    for(int i = 0; i < length; i++){
        group[i].applyVector(vector);
    }
    PixelGroup temp;
    temp.setGroup(group);
    return temp;
}

void PixelGroup::move(int x, int y){
    int length = group.size();
    for(int i = 0; i < length; i++){
         group[i].applyVector(x,y);
    }
}

void PixelGroup::move(QPoint vector){
    int length = group.size();
    for(int i = 0; i < length; i++){
        group[i].applyVector(vector);
    }
}

void PixelGroup::setGroup(QList<Pixel> g){
    group = g;
}

int PixelGroup::getSize(){
    return group.size();
}
