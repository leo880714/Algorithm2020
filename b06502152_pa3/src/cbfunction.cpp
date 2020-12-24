// **************************************************************************
//  File       [cbfunction.cpp]
//  Author     [Shu-Chuan Hsu]
//  Synopsis   [The sub program of 2020 fall Algorithm PA3]
// **************************************************************************
#include "cbfunction.h"
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
/////////////////FOR CLASS EDGE/////////////////
edge::edge(int u, int v, int w){
    this->u = u;
    this->v = v;
    this->w = w;
}

/////////////////FOR CLASS VERTICE/////////////////
Vertice::Vertice(){
    parent = 0;
    rank = 0;
    color = 0; // 0 for White, 1 for Gray, 2 for Black
}

/////////////////FOR CLASS GRAPG/////////////////
Graph::Graph(){
    type = "";  
    num_v = 0;
    num_e = 0;
    has_cycle = 0;
}

Graph::Graph(string t, int v, int e){
    type = t;
    num_v = v;
    num_e = e;
    has_cycle = 0;
    adj_list.reserve(v);
}

void Graph::printEdges(){
    cout << "----------------- print edges -------------------\n";
    for(int i = 0; i < num_e; i++)
        cout << E[i].u << " " << E[i].v << " " << E[i].w << endl;
}

void Graph::printAdjList(){
    cout << "----------------- adjlist edges -------------------\n";
    for(int i = 0; i < num_v; i++){
        for(int j = 0; j < adj_list[i].size(); j++){
            cout << i << " | ";
            cout << adj_list[i][j].u << " " << adj_list[i][j].v << " " << adj_list[i][j].w << endl;
        }
    }
}

void Graph::addEdge(edge e){
    E.push_back(e);
    /*
    if (type == "u")
        adj_list[e.v].push_back(edge(e.v, e.u, e.w));*/
    adj_list[e.u].push_back(e);
}

void Graph::removeAll(vector<edge> rmEdges){
    for(int i = rmEdges.size()-1; i >=0; i--){
        removeEdge(rmEdges[i]);
    }
}

void Graph::removeEdge(edge e){
    for (int i = 0; i < num_e; i++){
        if (e.u == E[i].u && e.v == E[i].v && e.w == E[i].w){
            E.erase(E.begin() + i);
            break;
        }
    }
    /*
    if (type == "u"){
        for (int i = 0; i < adj_list[e.v].size(); i++){
            if (e.u == adj_list[e.v][i].v && e.v == adj_list[e.v][i].u && e.w == adj_list[e.v][i].w){
                adj_list[e.v].erase(adj_list[e.v].begin() + i);
                break;
            }
        }
    }
    */
    for (int i = 0; i < adj_list[e.u].size(); i++){
        if (e.u == adj_list[e.u][i].u && e.v == adj_list[e.u][i].v && e.w == adj_list[e.u][i].w){
            adj_list[e.u].erase(adj_list[e.u].begin() + i);
            break;
        }
    }
    num_e -= 1;
}

bool Graph::hasCycle(){   
    DFS();
    if(has_cycle ==1){
        has_cycle = 0;
        return true;
    }
    return false;
}

bool Graph::cycleDetect(edge& d){
    Vertice *v = new Vertice[num_v];
    return cycleDetect_helper(d.u, d.v, v);
}

bool Graph::cycleDetect_helper(int target, int u, Vertice* v){
    v[u].color = 1;
    for(int i = 0; i < adj_list[u].size(); i++){
        int t = adj_list[u][i].v;
        if(t == target) 
            return true;
        if(v[t].color == 0){
            if(cycleDetect_helper(target, t, v))
                return true;
        }
    }
    v[u].color = 2;
    return false;
}

void Graph::DFS(){
    Vertice *v = new Vertice[num_v]; //initialize  all Vertice with color white(0)
    for (int i = 0; i < num_v; i++){
        if (v[i].color == 0){
            DFS_Visit(v, i);
        }
    }
    delete[] v;
}

void Graph::DFS_Visit(Vertice *v, int u){
    v[u].color = 1; // color as Gray
    for (int i = 0; i < adj_list[u].size(); i++){
        //cout << "current vertice:  <" << u << "|" << v[u].color << ">" << " -> <" << adj_list[u][i].v << "|" << v[adj_list[u][i].v].color << ">";
        if (v[adj_list[u][i].v].color == 0){
            //cout << "keep DFS\n";
            v[adj_list[u][i].v].parent = u;
            DFS_Visit(v, adj_list[u][i].v);
        }
        else if(v[u].parent == adj_list[u][i].v){
        }
        else if(v[adj_list[u][i].v].color == 2){
        }
        else if(v[adj_list[u][i].v].color == 1){
            //cout << "has cycle\n";
            has_cycle = 1;
        }
    }
    v[u].color = 2;
}

void Graph::sortEdges(){
    MergeSort(E);
}

void Graph::MergeSort(vector<edge>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

void Graph::MergeSortSubVector(vector<edge>& data, int low, int high) {
    if((high-low) >= 1){
        int middle1 = (low + high)/2;
        int middle2 = middle1 + 1;
        MergeSortSubVector(data, low, middle1);
        MergeSortSubVector(data, middle2, high);
        Merge(data, low, middle1, middle2, high);
    } 
}

void Graph::Merge(vector<edge>& data, int low, int middle1, int middle2, int high){
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int leftIdx = low;
    int rightIdx = middle2;
    int combineIdx = low;
    vector<edge> left;
    vector<edge> right;
    for(int i = 0; i < middle1 - low + 1; i++){
        left.push_back(data[low+i]);
    }
    for(int i = 0; i < high - middle2 + 1; i++){
        right.push_back(data[middle2+i]);
    }
    int l = 0;
    int r = 0;
    while((l < left.size()) && (r < right.size())){
        if(left[l].w >  right[r].w){
            data[combineIdx] = left[l];
            combineIdx++;
            l++;
        }
        else{
            data[combineIdx] = right[r];
            combineIdx++;
            r++;
        }
    }
    if ( l == left.size() ){// if at end of left vector                                                      
        while(r < right.size()){
            data[combineIdx] = right[r];
            r++;
            combineIdx++;
        }
    }                                                                                                                        
    else{// at end of right vector 
        // copy in rest of left vector
        while(l < left.size()){
            data[combineIdx] = left[l];
            l++;
            combineIdx++;
        }
    }
}

/////////////////FOR CLASS DISJOINTSET/////////////////
disjointSet::disjointSet(int num_v){
    set = new Vertice[num_v];
    makeSet(num_v);
}

void disjointSet::makeSet(int num_v){
    for (int i = 0; i < num_v; i++){
        set[i].parent = i;
        set[i].rank = 0;
    }
}

void disjointSet::Union(int u, int v){
    Link(findSet(u), findSet(v));
}

int disjointSet::findSet(int u){
    if (set[u].parent != u){
        set[u].parent = findSet(set[u].parent);
    }
    return set[u].parent;
}

void disjointSet::Link(int u, int v){
    if (set[u].rank < set[v].rank){
        set[v].parent = u;
    }
    else{
        set[u].parent = v;
        if (set[u].rank == set[v].rank){
            set[v].rank += 1;
        }
    }
}

bool edge_w_compare(edge a, edge b){
    return a.w > b.w;
}

bool edge_v_compare(edge a, edge b){
    return a.v < b.v;
}

bool edge_u_compare(edge a, edge b){
    return a.u < b.u;
}

/////////////////FOR GLOBAL FUNCTION/////////////////
vector<edge> reversed_Kruskal(Graph& g){
    disjointSet s(g.num_v);
    vector<edge> rmEdges;
    //g.printEdges();

    for (int i = 0; i < g.E.size(); i++){
        //cout << i << " : " << g.E[i].u << " " << g.E[i].v << " " << g.E[i].w;
        if (s.findSet(g.E[i].u) != s.findSet(g.E[i].v)){
            //cout << " union!";
            s.Union(g.E[i].u, g.E[i].v);
        }
        else{
            //cout << i << " : " << E[i].u << " " << E[i].v << " " << E[i].w << endl;;
            rmEdges.push_back(g.E[i]);
            //g.removeEdge(g.E[i]);
        }
        //cout << endl;
    }
    return rmEdges;
}

void MergeSort(vector<edge>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}
void MergeSortSubVector(vector<edge>& data, int low, int high) {
    if((high-low) >= 1){
        int middle1 = (low + high)/2;
        int middle2 = middle1 + 1;
        MergeSortSubVector(data, low, middle1);
        MergeSortSubVector(data, middle2, high);
        Merge(data, low, middle1, middle2, high);
    } 
}
void Merge(vector<edge>& data, int low, int middle1, int middle2, int high){
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int leftIdx = low;
    int rightIdx = middle2;
    int combineIdx = low;
    vector<edge> left;
    vector<edge> right;
    for(int i = 0; i < middle1 - low + 1; i++){
        left.push_back(data[low+i]);
    }
    for(int i = 0; i < high - middle2 + 1; i++){
        right.push_back(data[middle2+i]);
    }
    int l = 0;
    int r = 0;
    while((l < left.size()) && (r < right.size())){
        if(left[l].w >  right[r].w){
            data[combineIdx] = left[l];
            combineIdx++;
            l++;
        }
        else{
            data[combineIdx] = right[r];
            combineIdx++;
            r++;
        }
    }
    if ( l == left.size() ){// if at end of left vector                                                      
        while(r < right.size()){
            data[combineIdx] = right[r];
            r++;
            combineIdx++;
        }
    }                                                                                                                        
    else{// at end of right vector 
        // copy in rest of left vector
        while(l < left.size()){
            data[combineIdx] = left[l];
            l++;
            combineIdx++;
        }
    }
}