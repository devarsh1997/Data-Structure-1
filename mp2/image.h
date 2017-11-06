#ifndef IMAGE_H
#define IMAGE_H





#include "png.h"


class Image : public PNG
{
public:
    void flipleft();
    void adjustbrightness(int r, int g, int b);
    void invertcolors();
   
  
    // the function definitions from the Doxygen go here
};


#endif