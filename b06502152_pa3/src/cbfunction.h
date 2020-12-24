// **************************************************************************
//  File       [cbfunction.h]
//  Author     [Shu-Chuan Hsu]
//  Synopsis   [The sub program of 2020 fall Algorithm PA3]
// **************************************************************************
#ifndef _CBFUNCTION_H_
#define _CBFUNCTION_H_

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

class edge{
public:
    int u;
    int v;
    int w;
    edge(int u, int v, int w);
};

class Vertice{
public:
    int parent;
    int rank;
    int color; // 0 for white, 1 for gray, 2 for black
    Vertice();
};

class Graph{
public:
    string type;                                            //feature for undirected or directed graph
    int num_v;                                              //feature for num of vertices
    int num_e;                                              //feature for num of edges
    int has_cycle;                                          //record has cycle or not, if y/1, else n/0
    vector<vector<edge> > adj_list;                         //using adjacency list to store edges
    vector<edge> E;                                         //using vetor to store edges

    Graph();                    
    Graph(string, int, int);
    void removeAll(vector<edge>);                           //removing edges in adj_list and E, after running reversed_Kruskal()
    bool cycleDetect(edge& );                               //decting if add this edge will lead to cycle or not
    bool cycleDetect_helper(int, int, Vertice* );           //running DFS, source on vertice u, checking will it lead back to source
    void printEdges();                                      //printing all edges in E
    void printAdjList();                                    //printing all edges in adj_list
    void addEdge(edge);                                     //adding edges while constructing graph
    void removeEdge(edge);                                  //removing edge e in E and adj_list
    bool hasCycle();                                        //check the graph having cycle or not, if y/1, else n/0
    void DFS();                                             //DFS for all graph
    void DFS_Visit(Vertice *, int);                         //DFS_visit for all graph
    void sortEdges();                                       //using Merge Sort in PA1 to sort all edges in E
    void MergeSort(vector<edge>&);                          
    void MergeSortSubVector(vector<edge>&, int, int);
    void Merge(vector<edge>&, int, int, int, int);
};

class disjointSet{
public:
    Vertice *set;
    void makeSet(int num_v);
    void Union(int u, int v);
    int findSet(int u);
    void Link(int u, int v);
    disjointSet(int num_v);
};

bool edge_w_compare(edge a, edge b);
bool edge_v_compare(edge a, edge b);
bool edge_u_compare(edge a, edge b);
void MergeSort(vector<edge>&);
void MergeSortSubVector(vector<edge>&, int, int);
void Merge(vector<edge>&, int, int, int, int);
vector<edge> reversed_Kruskal(Graph&);
#endif