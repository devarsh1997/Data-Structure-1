/* Your code here! */
#include "dsets.h"
using namespace std;

void DisjointSets::addelements(int num)
{
    for(int i = 0; i < num; i++)
    {
        v.push_back(-1);
    }
}

int DisjointSets::find(int elem)
{
    if(v[elem] < 0)
        return elem;
    else{
        v[elem] = find(v[elem]);
        return v[elem];
    }
}

void DisjointSets::setunion(int a,  int b)
{
    int root1 = find(a);
    int root2 = find(b);
    
    if(root1 == root2)
        return;
    int newsize = v[root1] + v[root2];
    
    if(v[root1] <= v[root2])
    {
        v[root1] = newsize;
        v[root2] = root1;
    }
    else
    {
        v[root2] = newsize;
        v[root1] = root2;
    }
}
