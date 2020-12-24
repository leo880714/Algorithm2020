// **************************************************************************
//  File       [main.cpp]
//  Author     [Shu-Chuan Hsu]
//  Synopsis   [The main program of 2020 fall Algorithm PA2]
// **************************************************************************

#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>
#include "mpsfunction.h"
using namespace std;
#define INT_MAX __INT_MAX__

int main(int argc, char* argv[])
{
    //////////// read the input file /////////////
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2],ios::out);
    vector<int> chords;
    int num = 0;
    int chord_idx_1 = 0; 
    int chord_idx_2 = 0; 
    fin >> num;
    chords.reserve(num);
    while (fin >> chord_idx_1 >> chord_idx_2){
        chords[chord_idx_1] = chord_idx_2;
        chords[chord_idx_2] = chord_idx_1;
    }

    //////////// function part /////////////
    //initialize matrix
    int** m = new int* [num];
    for(int i = 0; i < num; i++)
        m[i] = new int[num];
    
    int** visited = new int* [num];
    for(int i = 0; i < num; i++)
        visited[i] = new int [num];

    int** road = new int* [num];
    for(int i = 0; i < num; i++)
        road[i] = new int [num];

    cout << mps_topdown(0, num-1, m, visited ,road, chords) << endl;

    vector<vector<int> > ans;
    find_chords_topdown(0, num-1, road, chords, ans);
    //cout << ans.size() << endl;
    sort(ans.begin(), ans.end());
    /*
    for(int i = 0; i < ans.size(); i++)
        cout << ans[i][0]  << " " << ans[i][1] << "\n";*/

    //////////// write the output file ///////////
    fout << ans.size() << "\n";
    for (int i = 0; i < ans.size(); i++)
        fout << ans[i][0] << " " << ans[i][1] << "\n";
    fin.close();
    //fout.close();
    return 0;
}
