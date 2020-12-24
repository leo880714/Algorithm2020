// **************************************************************************
//  File       [mpsfunction.cpp]
//  Author     [Shu-Chuan Hsu]
//  Synopsis   [The sub program of 2020 fall Algorithm PA2]
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
void findchords(int i, int j, int** road, vector<int>& chords, vector<vector<int> >& ans){
    while(j - i > 1){
        if(road[i][j] == 2){
            int k = chords[j];
            vector<int> temp;
            temp.push_back(chords[j]);
            temp.push_back(j);
            //pair<int, int> temp(chords[j], j);
            ans.push_back(temp);
            //cout << chords[j] << "  " << j << endl;
            findchords(i+1, j-1, road, chords, ans);
            j = i - 1;
        }
        else if(road[i][j] == 3){
            int k = chords[j];
            vector<int> temp;
            temp.push_back(chords[j]);
            temp.push_back(j);
            //pair<int, int> temp(chords[j], j);
            ans.push_back(temp);
            //cout << chords[j] << "  " << j << endl;
            findchords(k, j-1, road, chords, ans);
            j = k - 1;
        }
        else
        {
            j--;
        }
    }
}


vector<vector<int> > mps(vector<int>& chords, int num){
    //////////// function part /////////////
    // initializing tables
    int** m = new int* [num];
    for(int i = 0; i < num; i++)
        m[i] = new int [num];

    int** road = new int* [num];
    for(int i = 0; i < num; i++)
        road[i] = new int [num ];

    //dynamics programming part
    int k = 0;
    int j = 0;
    for(int l = 1; l <= num - 1; l++){
        for(int i = 0; i <= num - l - 1; i++){
            j = i + l;
            k = chords[j];

            if(k < i || k > j){
                m[i][j] = m[i][j-1];
            }
            else if(k == i){
                m[i][j] = m[i+1][j-1] + 1;
                road[i][j] = 2;
            }
            else{
                if(m[i][j-1]>=(m[i][k-1]+1+m[k+1][j-1])){
                    m[i][j] = m[i][j-1];
                }
                else{
                    m[i][j]=m[i][k-1]+1+m[k+1][j-1];
                    road[i][j] = 3;
                }
            }
        } 
    }

    cout << m[0][num-1] << endl; 
    vector<vector<int> > ans;
    findchords(0, num-1, road, chords, ans);
    sort(ans.begin(), ans.end());
    /*
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i][0]<< " " << ans[i][1] << "\n";
    }*/
    return ans;
}

int mps_topdown(int i, int j, int** m, int** visited, int** road , vector<int>& chords){
    //cout << "<" << i << "|" << j << "> ";
    if(visited[i][j] != 0){
        return m[i][j];
    }
    else if(i == j){
        m[i][j] = 0;
        return 0;
    }
    else if(j - i == 1){
        if(chords[j] == i){
            m[i][j] = 1;
            visited[i][j] = 1;
            road[i][j] = 4;
            return 1;
        }
        else{
            m[i][j] = 0;
            visited[i][j] = 1;
            return 0;
        }
    }
    else{
        int k = chords[j];

        if(k < i || k > j){
            if(m[i][j] == 0)
                m[i][j] = mps_topdown(i, j-1, m, visited, road, chords);
            road[i][j] = 1;
            visited[i][j] = 1;
        }
        else if(k == i){
            if(visited[i][j] == 0){
                m[i][j] = mps_topdown(i+1, j-1, m, visited, road, chords) + 1;
            }
            road[i][j] = 2;
            visited[i][j] = 1;
        }
        else{
            if(visited[i][k-1] == 0){
                m[i][k-1] = mps_topdown(i, k-1, m, visited, road, chords);
                visited[i][k-1] = 1;
            }
            if(visited[k+1][j-1] == 0){
                m[k+1][j-1] = mps_topdown(k+1, j-1, m, visited, road, chords);
                visited[k+1][j-1] = 1;
            }
            if(visited[i][j-1] == 0){
                m[i][j-1] = mps_topdown(i, j-1, m, visited, road, chords );
                visited[i][j-1] = 1;
            }
            
            if(m[i][j-1]> (m[i][k-1] + 1 + m[k+1][j-1])){
                m[i][j] = m[i][j-1];
                visited[i][j] = 1;
                road[i][j] = 1;
            }
            else{
                m[i][j]= m[i][k-1] + 1 + m[k+1][j-1];
                visited[i][j] = 1;
                road[i][j] = 3;
            }
        }
    }
    return m[i][j];
}

void find_chords_topdown(int i, int j , int** road, vector<int>& chords, vector<vector<int> >& ans){
    //cout << i << "|" << j << " -> " << road[i][j] << endl; 
    if(i == j)
        return;
    else{
        if(road[i][j] == 4){
            vector<int> temp;
            temp.push_back(chords[j]);
            temp.push_back(j);
            ans.push_back(temp);
            return;
        }
        else if(road[i][j] == 1){
            find_chords_topdown(i, j-1, road, chords, ans);
        }
        else if(road[i][j] == 2){
            vector<int> temp;
            temp.push_back(chords[j]);
            temp.push_back(j);
            ans.push_back(temp);
            find_chords_topdown(i+1, j-1, road, chords, ans);
        }
        else if(road[i][j] == 3){
            vector<int> temp;
            temp.push_back(chords[j]);
            temp.push_back(j);
            ans.push_back(temp);
            find_chords_topdown(i, chords[j]-1, road, chords, ans);
            find_chords_topdown(chords[j]+1, j-1, road, chords, ans);
        }
    }
}