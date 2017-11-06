#include "maze.h"



SquareMaze::SquareMaze()
{

}
    
void SquareMaze::makeMaze(int width, int height)
{
    
    w = width;
    h = height;
    int size = w * h;
    down.clear();
    right.clear();
    d.addelements(size);
    for(int i = 0; i < size; i++){
        right.push_back(true);
        down.push_back(true);
    }
    
    int num = size;
    while(num > 1){
        for(int i = 0; i < size; i++){
            int flag = rand() % 2;
            //flag == 0 -> right
            //flag == 1 ->down
            if(flag == 0 && (i + 1) % width == 0){
                continue;
            }
            if(flag == 1 && i >= width * (height - 1)){
                continue;
            }
            
            int next = 0;
            if(flag == 0){
                next = i + 1;
            }
            else
            {
                next = i + width;
            }
            if(d.find(i) != d.find(next)){
                num--;
                d.setunion(i, next);
                if(flag == 0)
                    right[i] = false;
                else
                    down[i] = false;
            }
        }
        
    }
    
    
}
    
bool SquareMaze::canTravel(int x, int y, int dir) const
{
    if(x < 0 || y < 0 || x > w - 1 || y > h - 1)
        return false;
    int pos = w * y + x;
    if(dir == 0 && x < w - 1){
        return !right[pos];
    }
    //right
    if(dir == 1 && y < h - 1){
        return !down[pos];
    }
    //down
    if(dir == 2 && x > 0){
        return !right[pos - 1];
    }
    //left
    if(dir == 3 && y > 0){
        return !down[pos - w];
    }
    //up
    return false;
}
    
void SquareMaze::setWall(int x, int y, int dir, bool exists)
{
    int pos = x + y * w;
    if(dir == 0) 
        right[pos] = exists;
    if(dir == 1) 
        down[pos] = exists;
}
    
vector<int> SquareMaze::solveMaze()
{
    map<int, int> m;
    int size = w * h;
    
    for(int i = 0; i < size; i++)
    {
        m[i] = 0;
    }
    
    
    vector<int> prev;
    for(int i = 0; i < size; i++)
    {
        prev.push_back(0);
    }
    
    
    vector<int> retval;
    int total = help(m, 0, 0, prev);
    int pos = (h - 1) * w + xcoordinate;
    
    
    
    while(pos != 0)
    {
        if(prev[pos] == pos + 1)
        {
            retval.push_back(0);
        }
        
        else if(prev[pos] == pos + w)
        {
            retval.push_back(1);
        }
        
        else if(prev[pos] == pos - 1)
        {
            retval.push_back(2);
        }
        
        else if(prev[pos] == pos - w)
        {
            retval.push_back(3);
        }
        
         pos = prev[pos];
    }
    
    
    reverse(retval.begin(), retval.end());
    
    
    for(unsigned long i = 0; i < retval.size(); i++)
    {
        if(retval[i] == 0)
        {
            retval[i] = 2;
        }
        
        else if(retval[i] == 1)
        {
            retval[i] = 3;
        }
        
        else if(retval[i] == 2)
        {
            retval[i] = 0;
        }
        
        else if(retval[i] == 3)
        {
            retval[i] = 1;
        }
       
    }
    
    return retval;
     
}
int SquareMaze::help(map<int, int> & m, int startx, int starty, vector<int> & prev)
{
    queue<int> q;
    int pos = w * starty + startx;
    q.push(pos);
    while(!q.empty())
    {
        int head = q.front();
        q.pop();
        int x = head % w;
        int y = head / w;
        int value = m[head];
        
        if(canTravel(x, y, 0) && m[head + 1] == 0){
            m[head + 1] = value + 1;
            q.push(head + 1);
            prev[head + 1] = head;
        }//right
        
        if(canTravel(x, y, 1) && m[head + w] == 0){

            m[head + w] = value + 1;
            q.push(head + w);
            prev[head + w] = head;
        }//down
        
        if(canTravel(x, y, 2) && m[head - 1] == 0){
            m[head - 1] = value + 1;
            q.push(head - 1); 
            prev[head - 1] = head;
        }//left
        
        if(canTravel(x, y, 3) && m[head - w] == 0){
            
            m[head - w] = value + 1;
            q.push(head - w);
            prev[head - w] = head;
        }//up
        
        
   
    }// end of while
    
    
    xcoordinate = 0;
    int retval = 0;
    for(int i = 0; i < w; i++)
    {
        if(m[(h - 1) * w + i] > retval)
        {
            retval = m[(h - 1) * w + i];
            xcoordinate = i;
        }
    }
    
    return retval;
    
}
   
PNG* SquareMaze::drawMaze() const
{
    
    PNG* result = new PNG(w * 10 + 1, h * 10 + 1);
    
    for(int i = 10; i < w * 10 + 1; i++){
        (*result)(i, 0)->red = 0;
        (*result)(i, 0)->green = 0;
        (*result)(i, 0)->blue = 0;
    }
    
    for(int i = 0; i < h * 10 + 1; i++){
        (*result)(0, i)->red = 0;
        (*result)(0, i)->green = 0;
        (*result)(0, i)->blue = 0;
    }
    
    for(int x = 0; x < w; x++)
    {
        for(int y = 0; y < h; y++){
            if(right[w * y + x])
            {
                for(int k = 0; k <= 10; k++)
                {
                    (*result)((x + 1) * 10, y * 10 + k)->red = 0;
                    (*result)((x + 1) * 10, y * 10 + k)->green = 0;
                    (*result)((x + 1) * 10, y * 10 + k)->blue = 0;
                } 
            }
            if(down[w * y + x])
            {
                for(int k = 0; k <= 10; k++)
                {
                    (*result)(x * 10 + k, (y + 1) * 10)->red = 0;
                    (*result)(x * 10 + k, (y + 1) * 10)->green = 0;
                    (*result)(x * 10 + k, (y + 1) * 10)->blue = 0;
                }
            }
        }
    }
    return result;
    
    
}
    
PNG* SquareMaze::drawMazeWithSolution()
{
    PNG* result = this->drawMaze();
    vector<int> solution = this->solveMaze();
    
    int x = 5;
    int y = 5;
    
    for(unsigned long i = 0; i < solution.size(); i++)
    {
        if(solution[i] == 0)
        {
            for(int j = x; j <= x + 10; j++)
            {
                (*result)(j, y)->red = 255;
                (*result)(j, y)->green = 0;
                (*result)(j, y)->blue = 0;
            }
            x = x + 10;
        }//right
        
        if(solution[i] == 1)
        {
            for(int j = y; j <= y + 10; j++)
            {
                (*result)(x, j)->red = 255;
                (*result)(x, j)->green = 0;
                (*result)(x, j)->blue = 0;
            }
            y = y + 10;
        }//down
        
        if(solution[i] == 2)
        {
            for(int j = x - 10; j <= x; j++)
            {
                (*result)(j, y)->red = 255;
                (*result)(j, y)->green = 0;
                (*result)(j, y)->blue = 0;
            }
            x = x - 10;
        }//left
        
        if(solution[i] == 3)
        {
            for(int j = y - 10; j <= y; j++)
            {
                (*result)(x, j)->red = 255;
                (*result)(x, j)->green = 0;
                (*result)(x, j)->blue = 0;
            }
            y = y - 10;
        }//up
    }
    
    
    int dx = xcoordinate;
    int dy = h - 1;
    
    for(int k = 1; k <= 9; k++)
    {
        (*result)(dx * 10 + k, (dy + 1) * 10)->red = 255;
        (*result)(dx * 10 + k, (dy + 1) * 10)->green = 255;
        (*result)(dx * 10 + k, (dy + 1) * 10)->blue = 255;
    }
    
    return result;
}