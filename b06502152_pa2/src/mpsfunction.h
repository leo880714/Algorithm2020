// **************************************************************************
//  File       [mpsfunction.h]
//  Author     [Shu-Chuan Hsu]
//  Synopsis   [The sub program of 2020 fall Algorithm PA2]
// **************************************************************************

#ifndef MPSFUNCTION_H
#define MPSFUNCTION_H
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
void findchords(int , int, int**, vector<int>& , vector<vector<int> >&);
vector<vector<int> > mps(vector<int>&, int);
int mps_topdown(int , int , int**, int** , int** , vector<int>& );
void find_chords_topdown(int , int, int**, vector<int>& , vector<vector<int> >&);
#endif