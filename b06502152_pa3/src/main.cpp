// **************************************************************************
//  File       [main.cpp]
//  Author     [Shu-Chuan Hsu]
//  Synopsis   [The main program of 2020 fall Algorithm PA3]
// **************************************************************************

#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "cbfunction.h"
using namespace std;

void help_message() {
    cout << "Usage: ./cb <input file name> <output file name>" << endl;
}

int main(int argc, char *argv[]){
    ////////////////////// Read Input File //////////////////////
 	if(argc!=3) {
 		help_message();
         exit(1);
 	}

    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2], ios::out);
    char buffer[30];
    string type;
    int num_v = 0;
    int num_e = 0;
    fin.getline(buffer,30);
    type = buffer[0];
    fin.getline(buffer,30);
    num_v= atoi(buffer);
    fin.getline(buffer,30);
    num_e= atoi(buffer);
    Graph g(type, num_v, num_e);
    if (!fin) {
 		cout << "Error: Input File Not Found" <<endl;
 		exit(1);
	}

    for(int i = 0; i < num_e; i++){
        fin.getline(buffer,30);
        char * pch;
        int data[3];
        int count = 0;
        pch = strtok (buffer," ");
        while (pch != NULL){
            data[count] = atoi(pch);
            count++;
            pch = strtok (NULL," ");
        }
        g.addEdge(edge(data[0], data[1], data[2]));
    }
    fin.close();

    ////////////////////// Main Body //////////////////////
    vector<edge> rmEdges;
    int weightcost = 0;

    //cout << "/////////////// Checking State ///////////////\n";
    //cout << "Has Cycle or Not :" << g.hasCycle() << endl;
    //cout << "/////////////// Cycle Breaking ///////////////\n";

    if(g.type ==  "u")
        sort(g.E.begin(), g.E.end(), edge_w_compare);
    else
        g.sortEdges();

    if (type == "u"){
        rmEdges = reversed_Kruskal(g);
        //g.removeAll(rmEdges);
    }
    else if (type == "d"){
        rmEdges = reversed_Kruskal(g);
        g.removeAll(rmEdges);
        
        vector<int> tmp_remove_idx;
        //sort(rmEdges.begin(), rmEdges.end(), edge_w_compare);
        MergeSort(rmEdges);
        for(int i = 0; i < rmEdges.size(); i++){
            if(rmEdges[i].w > 0){
                if(g.cycleDetect(rmEdges[i])){
                    //cout << "\n";
                }
                else{
                    //cout << " ->add!\n";
                    g.addEdge(rmEdges[i]);
                    tmp_remove_idx.push_back(i);
                }
            }   
        }
        for(int i = tmp_remove_idx.size()-1; i >= 0; i--){
            rmEdges.erase(rmEdges.begin()+tmp_remove_idx[i]);
        }
    }

    //cout << "Has Cycle or Not :"  << g.hasCycle() << endl;

    //cout << "/////////////// Cycle Breaking Complete ////////////////\n";
    for (int i = 0; i < rmEdges.size(); i++)
        weightcost += rmEdges[i].w;

    cout << weightcost << "\n";
    /*
    sort(rmEdges.begin(), rmEdges.end(), edge_v_compare);
    sort(rmEdges.begin(), rmEdges.end(), edge_u_compare);
    */

    /*
    for (int i = 0; i < rmEdges.size(); i++)
        cout << rmEdges[i].u << " " << rmEdges[i].v << " " << rmEdges[i].w << endl;
    */

    ////////////////////// Write Output File //////////////////////
    fout << weightcost << "\n";
    for (int i = 0; i < rmEdges.size(); i++)
        fout << rmEdges[i].u << " " << rmEdges[i].v << " " << rmEdges[i].w << "\n";
    fout.close();
    
    return 0;
}
