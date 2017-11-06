#include "scene.h"
#include <iostream>

using namespace std;



    Scene::Scene(int max)
    {
        layer = max;
        x = new int[max];
        y = new int[max];
        images = new Image*[max];
        for ( int i = 0; i < max; i++)
        {
            images[i] = NULL;
            x[i] = 0;
            y[i] = 0;
            
        }
    }//////
    
    Scene::~Scene()
    {    
        Clear();
    }/////
    
    Scene::Scene(const Scene &source)
    {
        Copy(source);
        
    }/////
    void Scene::Copy(const Scene &source){
       
        layer = source.layer;
        images = new Image*[source.layer];
        x = new int[source.layer];
        y = new int[source.layer];
        for ( int i = 0; i < layer; i++)
        {
            if(source.images[i] != NULL)
            {
                images[i] = new Image;
                *(images[i]) = *(source.images[i]);
                
                x[i] = source.x[i];
                y[i] = source.y[i];
            }
            else
            {
                images[i] = NULL;
                
                x[i] = 0;
                y[i] = 0;
            }
        }
        
    }//////
    void Scene::Clear()
    {
        for ( int i = 0; i < layer; i++)
        {
            delete images[i];
            images[i] = NULL;
        }
        delete[] images;
        images = NULL;
        delete[] x;
        x = NULL;
        delete[] y;
        y = NULL;
    }//////
    
    const Scene& Scene::operator=(const Scene& source)
    {
    
        if (this != &source)
        {
            Clear();
            Copy(source);
        }
        return *this;
    }///////
    
    void Scene::changemaxlayers(int newmax)
    {
        if(newmax < layer)
        {
            for(int i = newmax; i < layer; i++)
            {
                if(images[i] != NULL)
                {
                    cout << "invalid newmax" << endl;
                    return;
                }
            }
        }
        
        ///////////////////////////////
        
        Image** newimages = new Image*[newmax];
        int* xx = new int[newmax];
        int* yy = new int[newmax];
        
        
        for (int i = 0; i < newmax; i++)
        {
            if (images[i] != NULL && i <= layer - 1)
            {
                newimages[i] = images[i];
                xx[i] = x[i];
                yy[i] = y[i];
            }
            else
            {
                newimages[i] = NULL;
                xx[i] = 0;
                yy[i] = 0;
            }
        }
        
        delete[] images;
        delete[] x;
        delete[] y;
        
        layer = newmax;
        images = newimages;
        x = xx;
        y = yy;
        
        newimages = NULL;
        xx = NULL;
        yy = NULL;
            
    }//////
    
    void Scene::addpicture(const char*fileName, int index, int xcoord, int ycoord)
    {
        if(index > layer - 1 || index < 0)
        {
            cout << "index out of bounds" << endl;
        }
        else
        {
            if(images[index] != NULL)
            {
                
                delete images[index];
                images[index] = NULL;
                Image* result = new Image;
                result->readFromFile(fileName);
                
                images[index] = result;
                x[index] = xcoord;
                y[index] = ycoord;
            }
            else
            {
                Image* result = new Image;
                result->readFromFile(fileName);
                
                images[index] = result;
                x[index] = xcoord;
                y[index] = ycoord;
            }
            
        }
        
    }/////////
    
    void Scene::changelayer(int index, int newindex)
    {
        
        if( index > layer - 1 || newindex > layer - 1 || index < 0 || newindex < 0)
        {
            cout << "invalid index" << endl;
            
            return;
        }
        
        
        if (index == newindex)
        {
            return; 
        }
            
        if (images[index] == NULL)
        {
            images[newindex] = NULL;
            x[newindex] = 0;
            y[newindex] = 0;
            
            return;
        }
        
        if (images[newindex] != NULL)
        {
            delete images[newindex];
            images[newindex] = NULL;
            images[newindex] = images[index];
            images[index] = NULL;
            
            x[newindex] = x[index];
            y[newindex] = y[index];
            
            x[index] = 0;
            y[index] = 0;
            
            return;
        }
        
        if(images[newindex] == NULL)
        {
            images[newindex] = images[index];
            x[newindex] = x[index];
            y[newindex] = y[index];
            
            images[index] = NULL;
            x[index] = 0;
            y[index] = 0;
            
            return;
        }
        
    }///////
    
    void Scene::translate(int index, int xcoord, int ycoord)
    {
        if(images[index] == NULL || index > layer - 1 || index < 0)
            cout << "invalid index" << endl;
        else
        {
            x[index] = xcoord;
            y[index] = ycoord;
        }
    }
    
    void Scene::deletepicture(int index)
    {
        if(index > layer - 1 || images[index] == NULL || index < 0)
            cout << "invalid index" << endl;
        else
        {
            delete images[index];
            images[index] = NULL;
        }
    }
    
    Image* Scene::getpicture(int index) const
    {
    
        if(index > layer - 1 || images[index] == NULL || index < 0)
        {
            cout << "invalid index" << endl;
            return NULL;
        }
        else
            return images[index];
    }
    
    Image Scene::drawscene() const
    {
  
        size_t w = 0;
        size_t h = 0;
        for(int i = 0; i < layer; i++)
        {
            if(images[i] != NULL)
            {
                if (images[i]->width() + x[i] > w)
                    w = images[i]->width() + x[i];
                if (images[i]->height() + y[i] > h)
                    h = images[i]->height() + y[i];
            }
        }
        
        ///////////////////////////////////////////////////////
        
        Image output;
        output.resize(w, h);
        
        for(int i = 0; i < layer; i++)
        {
            if(images[i] != NULL)
            {
                for (int xi = 0; xi < images[i]->width(); xi++)
                {
                    for(int yi = 0; yi < images[i]->height(); yi++)  
                    {
                        *(output(xi + x[i], yi + y[i])) = *((*images[i])(xi, yi));
  
                    } 
                
                } 
            }    
        }
        
        
        return output;
     
    }/////////
    
    
    
    
    
    
    
    
    
    