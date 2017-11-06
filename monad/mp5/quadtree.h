/**
 * @file quadtree.h
 * Quadtree class definition.
 * @date Spring 2008
 */


#ifndef QUADTREE_H
#define QUADTREE_H

#include "png.h"

/**
 * A tree structure that is used to compress PNG images.
 */
class Quadtree
{
  public:
  
  
    Quadtree();
    
    Quadtree(PNG const & source, int resolution ); 	
    
    Quadtree(Quadtree const & other);
    
    ~Quadtree();
    
    void buildTree(PNG const & source,int resolution);	
    
    Quadtree & operator=(Quadtree const & other);
    
    
    RGBAPixel getPixel(int x, int y) const;
    
    PNG decompress() const;
    
    void clockwiseRotate ();
    
    void prune(int tolerance);	
    
    int pruneSize(int tolerance) const;
    
    int idealPrune(int numLeaves) const;

  private:
    /**
     * A simple class representing a single node of a Quadtree.
     * You may want to add to this class; in particular, it could
     * probably use a constructor or two...
     */
    class QuadtreeNode
    {
      public:
        QuadtreeNode* nwChild; /**< pointer to northwest child */
        QuadtreeNode* neChild; /**< pointer to northeast child */
        QuadtreeNode* swChild; /**< pointer to southwest child */
        QuadtreeNode* seChild; /**< pointer to southeast child */

        RGBAPixel element; /**< the pixel stored as this node's "data" */
        
    };

    QuadtreeNode* root; /**< pointer to root of quadtree */
    int d;

    QuadtreeNode* copy(QuadtreeNode* other);
    
    void clear(QuadtreeNode* & root);
    
    QuadtreeNode* buildTreeHelp(PNG const &source, int x, int y, int resolution);

    void clockwiseRotateHelp(QuadtreeNode* & root);
    
    RGBAPixel getPixelHelp(QuadtreeNode* root, int x, int y, int resolution) const;
    
    void pruneHelp(QuadtreeNode* & croot, int tolerance);
    
    bool checkLeaf(QuadtreeNode* croot, int tolerance, RGBAPixel r) const;
    
    int pruneSizeHelp(QuadtreeNode* croot, int tolerance) const;
    

/**** Functions for testing/grading                      ****/
/**** Do not remove this line or copy its contents here! ****/
#include "quadtree_given.h"
};

#endif







