/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    
    Vertex start1 = graph.getStartingVertex();
    graph.setVertexLabel(start1, "unvisited");
    queue<Vertex> q1;
    q1.push(start1);
    while(!q1.empty())
    {
        Vertex head = q1.front();
        vector<Vertex> alladjacent = graph.getAdjacent(head);
        q1.pop();
        for(int i = 0; i < alladjacent.size(); i++)
        {
	         if(graph.getVertexLabel(alladjacent[i]) != "unvisited"){
	             graph.setVertexLabel(alladjacent[i], "unvisited");
	             graph.setEdgeLabel(head, alladjacent[i], "unvisited");
	             q1.push(alladjacent[i]);
	         }
        }
    }
    
    Vertex start = graph.getStartingVertex();
    int retval = INT_MAX;
    Vertex one = start;
    Vertex two = start;
    graph.setVertexLabel(start, "visited");
    queue<Vertex> q;
    q.push(start);
    while(!q.empty())
    {
        Vertex head = q.front();
        vector<Vertex> alladjacent = graph.getAdjacent(head);
        q.pop();
        for(int i = 0; i < alladjacent.size(); i++)
        {
            if(graph.getVertexLabel(alladjacent[i]) == "unvisited"){
                graph.setVertexLabel(alladjacent[i], "visited");
                graph.setEdgeLabel(head, alladjacent[i], "visited");
                q.push(alladjacent[i]);
    
            }
            else{
                if(graph.getEdgeLabel(head, alladjacent[i]) == "unvisited")
                {
                    graph.setEdgeLabel(head, alladjacent[i], "cross");
                }
            }
            int weight = graph.getEdgeWeight(head, alladjacent[i]);
            
            if(weight < retval){
                retval = weight;
                one = head;
                two = alladjacent[i];
            }
            
        }
    }
    graph.setEdgeLabel(one, two, "MIN");
    return retval;
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    /* Your code here! */
    unordered_map<Vertex, int> m;
    int retval = 0;
    vector<Vertex> v = graph.getVertices();
    for(int i = 0; i < v.size(); i++){
        m[v[i]] = INT_MAX;
        graph.setVertexLabel(v[i], "unvisited");
    }
    m[start] = 0;
    queue<Vertex> q;
    q.push(start);
    while(!q.empty())
    {
        Vertex head = q.front();
        q.pop();
        vector<Vertex> alladjacent = graph.getAdjacent(head);
        for(int i = 0; i < alladjacent.size(); i++)
        {
            if(graph.getVertexLabel(alladjacent[i]) == "unvisited"){
                if(m[alladjacent[i]] > m[head] + 1){
                    m[alladjacent[i]] = m[head] + 1;
                }

                q.push(alladjacent[i]);
            }
        }
        graph.setVertexLabel(head, "visited");
       
    }
     if(graph.getVertexLabel(end) == "visited")
     {
        retval = m[end];
     }
     else
     {
         return -1;
     }
     
     for(int i = 0; i < v.size(); i++){
        graph.setVertexLabel(v[i], "unvisited");
     }
     
     int min = retval;
     queue<Vertex> q2;
     q2.push(end);
     while(!q2.empty())
     {
        Vertex head = q2.front();
        q2.pop();
        vector<Vertex> alladjacent = graph.getAdjacent(head);
        for(int i = 0; i < alladjacent.size(); i++)
        {
            if(m[alladjacent[i]] == min - 1){
                graph.setEdgeLabel(head, alladjacent[i], "MINPATH");
                min--;
                q2.push(alladjacent[i]);
                break;
            }
        } 
        if(min == 0)
        {
            break;
        }
     }
     
     return retval;
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    /* Your code here! */
    vector<Vertex> v = graph.getVertices();
    vector<Edge> e = graph.getEdges();
    sort(e.begin(), e.end());
    DisjointSets d;
    d.addelements(v.size());
    unordered_map<Vertex, int>m;
    for(int i = 0; i < v.size(); i++){
        m[v[i]] = i;
    }
    int i = 0;
    while(i < e.size())
    {
        Edge edge = e[i];
        Vertex v1 = edge.source;
        Vertex v2 = edge.dest;
        if(d.find(m[v1]) != d.find(m[v2]))
        {
            d.setunion(m[v1],  m[v2]);
            graph.setEdgeLabel(v1, v2, "MST");
        }
        i++;
    }
}

