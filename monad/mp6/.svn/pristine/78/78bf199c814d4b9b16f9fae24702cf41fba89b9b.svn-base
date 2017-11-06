/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if(first[curDim] < second[curDim])
        return true;
    else if(first[curDim] > second[curDim])
        return false;
    else
        return first < second;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    double t1 = 0;
    for(int i = 0; i < Dim; i++){
        t1 = t1 + (target[i] - potential[i]) * (target[i] - potential[i]);
    }
    double t2 = 0;
    for(int i = 0; i < Dim; i++){
        t2 = t2 + (target[i] - currentBest[i]) * (target[i] - currentBest[i]);
    }
    if(t1 < t2) 
        return true;
    else if (t1 > t2)
        return false;
    else 
        return potential < currentBest;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
     if(!newPoints.empty()){
         points = newPoints;
         build(0, newPoints.size() - 1, 0);
     }
}
template <int Dim>
void KDTree<Dim>::build(int left, int right, int dim)
{
    if(left >= right) return;
    int mid = (left + right) / 2;
    quickSelect(left, right, mid, dim);
    if(left < mid) 
        build(left, mid - 1, (dim + 1) % Dim);
    if(right > mid) 
        build(mid + 1, right, (dim + 1) % Dim);
}
template <int Dim>
void KDTree<Dim>::quickSelect(int left, int right, int k, int dim)
{
    if(left == right) return;
    int pivot = (left + right) / 2;
    int pivotIndex = partition(left, right, pivot, dim);
    if(pivotIndex == k) 
        return;
    else if(k < pivotIndex)
        quickSelect(left, pivotIndex - 1, k, dim);
    else
        quickSelect(pivotIndex + 1, right, k, dim);
    
}
template <int Dim>
int KDTree<Dim>::partition(int left, int right, int pivotIndex, int dim)
{
    Point<Dim> pivotValue = points[pivotIndex];
    Point<Dim> temp1 = points[pivotIndex];
    Point<Dim> temp2 = points[right];
    points[right] = temp1;
    points[pivotIndex] = temp2;
    
    int storeIndex = left;
    for(int i = left; i < right; i++){
        if(points[i] == pivotValue || smallerDimVal(points[i], pivotValue, dim))
        {
            Point<Dim> temp3 = points[i];
            Point<Dim> temp4 = points[storeIndex];
            points[storeIndex] = temp3;
            points[i] = temp4;
            storeIndex++;
        }
    }
    Point<Dim> temp5 = points[right];
    Point<Dim> temp6 = points[storeIndex];
    points[storeIndex] = temp5;
    points[right] = temp6;
    return storeIndex;
}


template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    if(points.empty()) return Point<Dim>();
    return findHelp(query, 0, points.size() - 1, 0, points[(points.size() - 1) / 2]);
    
}


template <int Dim>
Point<Dim> KDTree<Dim>::findHelp(const Point<Dim>& query, int left, int right, int dim, const Point<Dim>& curr) const
{
    
    bool l = true;
    Point<Dim>result = curr;
    if(left == right)
    {
        if(shouldReplace(query, result, points[left]))
        {
            result = points[left];
            return result;
        }
        result = curr;
        return result;
    }
    int mid = (left + right) / 2;
    
    if(smallerDimVal(points[mid], query, dim) && right > mid){
        result = findHelp(query,mid + 1, right, (dim + 1) % Dim, result);
        l = false;
    }
    
    if(smallerDimVal(query, points[mid], dim) && (left < mid)){
        result = findHelp(query,left, mid - 1, (dim + 1) % Dim, result);
        l = true;
    }
    
    
    
    if(shouldReplace(query, result, points[mid])){
        result = points[mid];
    }
    
    int distance = 0;
    for(int i = 0; i < Dim; i++){
        distance = distance + (query[i] - result[i])*(query[i] - result[i]);
    }
    int temp = (points[mid][dim] - query[dim])*(points[mid][dim] - query[dim]);
    if(temp <= distance)
    {
        if(l == true && right > mid)
            result = findHelp(query,mid + 1, right, (dim + 1) % Dim, result);
        if(l == false && left < mid)
            result = findHelp(query,left, mid - 1, (dim + 1) % Dim, result);
    }
    
    return result;
}









