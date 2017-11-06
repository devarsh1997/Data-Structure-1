/**
 * @file quadtree.cpp
 * Quadtree class implementation.
 * @date Spring 2008
 */


#include "quadtree.h"

Quadtree::Quadtree(){
    root = NULL;
    d = 0;
}


Quadtree::Quadtree(PNG const & source, int resolution ){
    d = resolution;
    root = buildTreeHelp(source, 0, 0, resolution);
}


Quadtree::Quadtree(Quadtree const & other){
    root = copy(other.root);
    d = other.d;
}	

Quadtree::QuadtreeNode* Quadtree::copy(QuadtreeNode* other)
{
    QuadtreeNode* result = NULL;
    if(other != NULL){
        result = new QuadtreeNode;
        result->element = other->element;
        result->nwChild = copy(other->nwChild);
        result->neChild = copy(other->neChild);
        result->swChild = copy(other->swChild);
        result->seChild = copy(other->seChild);
    }
    return result;
}

Quadtree::~Quadtree(){
    clear(root);
}


void Quadtree::clear(QuadtreeNode* & root)
{
    if(root !=  NULL){
        clear(root->nwChild);
        clear(root->neChild);
        clear(root->swChild);
        clear(root->seChild);
    
        delete root;
        root = NULL; 
    }
    
}

Quadtree& Quadtree::operator=(Quadtree const & other){
    if(this != &other)
    {
        clear(root);
        root = copy(other.root);
        d = other.d;
    }
    return *this;
}

void Quadtree::buildTree(PNG const & source,int resolution)
{
    clear(root);
    root = buildTreeHelp(source, 0, 0, resolution);
    d = resolution;
}

Quadtree::QuadtreeNode* Quadtree::buildTreeHelp(PNG const & source, int x, int y, int resolution)
{
    
    QuadtreeNode* temp = new QuadtreeNode;
    
    if(resolution == 1){
        temp->element = *source(x, y);
        temp->nwChild = NULL;
        temp->neChild = NULL;
        temp->swChild = NULL;
        temp->seChild = NULL;
        
        return temp;
    }
    
    temp->nwChild = buildTreeHelp(source, x, y, resolution / 2);
    temp->neChild = buildTreeHelp(source, x + resolution / 2, y, resolution / 2);
    temp->swChild = buildTreeHelp(source, x, y + resolution / 2, resolution / 2);
    temp->seChild = buildTreeHelp(source, x + resolution / 2, y + resolution / 2, resolution / 2);
    
     
    temp->element.red = (temp->nwChild->element.red + temp->neChild->element.red 
      + temp->swChild->element.red + temp->seChild->element.red) / 4;
    temp->element.green = (temp->nwChild->element.green + temp->neChild->element.green 
      + temp->swChild->element.green + temp->seChild->element.green) / 4;
    temp->element.blue = (temp->nwChild->element.blue + temp->neChild->element.blue 
     + temp->swChild->element.blue + temp->seChild->element.blue) / 4;
    
    return temp;
    
}






RGBAPixel Quadtree::getPixel(int x, int y) const
{
    if(root == NULL || x >= d || y >= d || x < 0 || y < 0) {
        RGBAPixel result;
        return result;
    }
    return getPixelHelp(root, x, y, d);
}

RGBAPixel Quadtree::getPixelHelp(QuadtreeNode* croot, int x, int y, int resolution) const
{
    if(croot->nwChild == NULL || croot->neChild == NULL || croot->swChild == NULL || croot->seChild == NULL){
        return croot->element;
    }
    
    if(x < resolution / 2 && y < resolution / 2) 
        return getPixelHelp(croot->nwChild, x, y, resolution / 2);
    else if (x >= resolution / 2 && y < resolution / 2) 
        return getPixelHelp(croot->neChild, x - resolution / 2, y, resolution / 2);
    else if (x < resolution / 2 && y >= resolution / 2) 
        return getPixelHelp(croot->swChild, x, y - resolution / 2, resolution / 2);
    else 
        return getPixelHelp(croot->seChild, x - resolution / 2, y - resolution / 2, resolution / 2);

}


PNG Quadtree::decompress() const
{
    if(root == NULL){
        return PNG();
    }
    PNG result(d, d);
    for(int i = 0; i < d; i++){
        for(int j = 0; j < d; j++){
            *result(i, j) = getPixel(i, j);
        }
    }
    return result;
}




void Quadtree::clockwiseRotate()
{
    clockwiseRotateHelp(root);
}

void Quadtree::clockwiseRotateHelp(QuadtreeNode* & root)
{
    if(root == NULL) return;
    
    QuadtreeNode* t1 = root->nwChild;
    QuadtreeNode* t2 = root->neChild;
    QuadtreeNode* t3 = root->swChild;
    QuadtreeNode* t4 = root->seChild;
    
    root->neChild = t1;
    root->seChild = t2;
    root->nwChild = t3;
    root->swChild = t4;
    
    clockwiseRotateHelp(root->nwChild);
    clockwiseRotateHelp(root->neChild);
    clockwiseRotateHelp(root->swChild);
    clockwiseRotateHelp(root->seChild);
    
}



void Quadtree::prune(int tolerance)
{
    pruneHelp(root, tolerance);
}
void Quadtree::pruneHelp(QuadtreeNode* & root, int tolerance)
{
    if(root == NULL){
        return;
    }
    if(root->nwChild == NULL || root->neChild == NULL || root->swChild == NULL || root->seChild == NULL){
        return;
    }
    if(checkLeaf(root, tolerance, root->element) == true){
        clear(root->nwChild);
        clear(root->neChild);
        clear(root->swChild);
        clear(root->seChild);
        return;
    }
    else{
        pruneHelp(root->nwChild, tolerance);
        pruneHelp(root->neChild, tolerance);
        pruneHelp(root->swChild, tolerance);
        pruneHelp(root->seChild, tolerance);
    }
    
}

bool Quadtree::checkLeaf(QuadtreeNode* croot, int tolerance, RGBAPixel r) const{
    if(croot->nwChild == NULL || croot->neChild == NULL || croot->swChild == NULL || croot->seChild == NULL){
        int red = croot->element.red;
        int green = croot->element.green;
        int blue = croot->element.blue;
        if((red - r.red)*(red - r.red) + (green - r.green)*(green- r.green) + (blue - r.blue) * (blue - r.blue) <= tolerance){
            return true;
        }else{
            return false;
        }
    }
    return checkLeaf(croot->nwChild, tolerance, r) && checkLeaf(croot->neChild, tolerance, r) 
        && checkLeaf(croot->swChild, tolerance, r) && checkLeaf(croot->seChild, tolerance, r);
    
}
 

int Quadtree::pruneSize(int tolerance) const
{
    return pruneSizeHelp(root, tolerance);
}
int Quadtree::pruneSizeHelp(QuadtreeNode* croot, int tolerance) const
{
    if(croot == NULL){
        return 0;
    }
    if(croot->nwChild == NULL || croot->neChild == NULL || croot->swChild == NULL || croot->seChild == NULL){
        return 1;
    }
    if(checkLeaf(croot, tolerance, croot->element) == true){
        return 1;
    }
    return pruneSizeHelp(croot->nwChild, tolerance) + pruneSizeHelp(croot->neChild, tolerance)
        + pruneSizeHelp(croot->swChild, tolerance) + pruneSizeHelp(croot->seChild, tolerance);
}

int Quadtree::idealPrune(int numLeaves) const
{
    
    return idealPruneHelp(0, 255 * 255 * 3, numLeaves);
}
int Quadtree::idealPruneHelp(int l, int r, int numLeaves) const
{
    if(l > r) return l;
    int tolerance = (l + r) / 2;
    if(pruneSize(tolerance) > numLeaves) return idealPruneHelp(tolerance + 1, r, numLeaves);
    else return idealPruneHelp(l, tolerance - 1, numLeaves);
}

