#include "colorpaletteassigner.h"

#include <iostream>


QString colorPaletteAssigner::getColor()
{
  switch(counter++){
    case 0:
      return "#000000";
    case 1:
      return "#ff0000";
    case 2:
      return "#ffff00";
    case 3:
      return "#00ff00";
    case 4:
      return "#00ffff";
    case 5:
      return "#0000ff";
    case 6:
      return "#ff00ff";
    case 7:
      return "#ffffff";
    default:
      return "#888888";
  }
}

