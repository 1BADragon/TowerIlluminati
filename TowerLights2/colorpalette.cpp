#include "colorpalette.h"

colorPalette::colorPalette()
{
  count = 15;
}

colorPalette::~colorPalette()
{

}

QString colorPalette::getColor()
{
  switch(count--){
    case 0:
      return "white";
    case 1:
      return "red";
    case 2:
      return "green";
    case 3:
      return "blue";
    case 4:
      return "cyan";
    case 5:
      return "magenta";
    case 6:
      return "yellow";
    case 7:
      return "gray";
    case 8:
      return "black";
    case 9:
      return "darkRed";
    case 10:
      return "darkGreen";
    case 11:
      return "darkBlue";
    case 12:
      return "darkCyan";
    case 13:
      return "darkMagenta";
    case 14:
      return "#808000"; //dark yellow
    case 15:
      return "darkGray";
    default:
      return "#888888";
    }
}

