#ifndef SCENE_H
#define SCENE_H

#include "image.h"
#include <iostream>

class Scene
{
public:
    int* x;
    int* y;

    Scene(int max);
    
    ~Scene();
    
    Scene(const Scene &source);
    
    void Copy(const Scene &source);
    
    void Clear();
    
    const Scene& operator=(const Scene& source);
    
    void changemaxlayers(int newmax);
    
    void addpicture(const char*fileName, int index, int x, int y);
    
    void changelayer(int index, int newindex);
    
    void translate(int index, int xcoord, int ycoord);
    
    void deletepicture(int index);
    
    Image* getpicture(int index) const;
    
    Image drawscene() const;
    
private:
    
    int layer;
   
    Image** images;




};



#endif