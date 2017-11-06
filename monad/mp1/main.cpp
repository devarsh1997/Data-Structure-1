#include <algorithm>
#include <iostream>

#include "rgbapixel.h"
#include "png.h"

using namespace std;

PNG rotate(PNG original)
{
    PNG result;
    result.resize(original.width(), original.height());
    for(size_t yi = 0; yi < original.height(); yi++)
    {
        for(size_t xi = 0; xi < original.width(); xi++)
        {
            result(xi, yi)->red = original(original.width()-1-xi, original.height()-1-yi)->red;
            result(xi, yi)->green = original(original.width()-1-xi, original.height()-1-yi)->green;
            result(xi, yi)->blue = original(original.width()-1-xi, original.height()-1-yi)->blue;
            
            
        }
    }
    return result;
}// end of rotate

int main()
{

   
    PNG image("in.png");
    image = rotate(image);
    
    image.writeToFile("out.png");
    
    
   
    
    return 0;
}