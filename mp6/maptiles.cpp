/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage> const& theTiles)
{
    /**
     * @todo Implement this function!
     */
    vector<Point<3>> vec;
    map<Point<3>, TileImage> m;
    for(unsigned long i = 0; i < theTiles.size(); i++){
        RGBAPixel rgb = theTiles[i].getAverageColor();
        Point<3> p(rgb.red, rgb.green, rgb.blue);
        m[p] = theTiles[i];
        vec.push_back(p);
    }
    int r = theSource.getRows();
    int c = theSource.getColumns();
    MosaicCanvas * canvas = new MosaicCanvas(r, c);
    KDTree<3> temp(vec);
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            RGBAPixel region = theSource.getRegionColor(i, j);
            Point<3> point(region.red, region.green, region.blue);
            Point<3> neighbor = temp.findNearestNeighbor(point);
            canvas->setTile(i, j, m[neighbor]);
        }
    }
    return canvas;
}

