#ifndef MAZE_H
#define MAZE_H
#include "dsets.h"
#include "png.h"
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <map>
class SquareMaze
{
    public:
    
    SquareMaze(); 
    
    void makeMaze(int width, int height);
    
    bool canTravel(int x, int y, int dir) const;
    
    void setWall(int x, int y, int dir, bool exists);
    
    vector<int> solveMaze();
    
    PNG* drawMaze() const;
    
    PNG* drawMazeWithSolution();	
    
    
    private:
    
    int w;
    int h;
    DisjointSets d;
    vector<bool>right;
    vector<bool>down;
    int xcoordinate;
    int help(map<int, int> & m, int x, int y, vector<int> & prev);
};


#endif
