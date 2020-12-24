// **************************************************************************
//  File       [main.cpp]
//  Author     [Shu-Chuan Hsu]
//  Synopsis   [The main program of 2020 fall Algorithm PA2]
// **************************************************************************

#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cmath>
using namespace std;


void findchords(int i, int j , int** road, map<int, int> chords);
void mps_topdown(int i, int j, int** road, int** chords);

int main(int argc, char* argv[])
{
    //////////// read the input file /////////////
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2],ios::out);
    map<int, int> chords;
    map<int, int>::iterator iter;
    int num = 0;
    int chord_idx_1 = 0; 
    int chord_idx_2 = 0; 
    fin >> num;
    while (fin >> chord_idx_1 >> chord_idx_2){
        chords[chord_idx_1] = chord_idx_2;
        chords[chord_idx_2] = chord_idx_1;
    }
    //////////// test fin part /////////////
    /*
    cout << "# of points : " << num << endl;
    for(iter = chords.begin(); iter != chords.end(); iter++){
        cout << iter->first <<  " <-> " << iter->second << endl;
    }
    */
    //////////// function part /////////////
    
    // initializing tables
    int** m = new int*[num];
    for(int i = 0; i < num; i++)
        m[i] = new int [num];

    for(int i = 0;i < num; i++)
        for(int j = 0; j < num; j++)
            m[i][j] = 0;
    
    int** road = new int*[num];
    for(int i = 0; i < num; i++)
        road[i] = new int [num];

    for(int i = 0;i < num; i++)
        for(int j = 0; j < num; j++)
            road[i][j] = 0;

    cout << "finishing initializing tables" << endl;
    //dynamics programming part
    for(int l = 1; l <= num - 1; l++){
        for(int i = 0; i <= num - l - 1; i++){
            int j = i + l;
            int k = chords[j];

            if(k < i || k > j){
                m[i][j] = m[i][j-1];
            }
            else if(k == i){
                m[i][j] = m[i+1][j-1] + 1;
                road[i][j] = 2;
            }
            else{
                m[i][j] = max(m[i][j-1], (m[i][k-1] + 1 + m[k+1][j-1]));
                if((m[i][k-1] + 1 + m[k+1][j-1]) > m[i][j-1])
                    road[i][j] = 3;
            }
        } 
    }
    cout << m[0][num-1] << endl; 
    findchords(0, num-1, road, chords);
    
    /*
    cout << "matrix of m \n";
    for(int i = 0; i < num; i++){
        for(int j = 0; j < num; j++)
            cout << m[i][j] <<  "   ";
        cout << endl;
    }

    cout << "matrix of road \n";
    for(int i = 0; i < num; i++){
        for(int j = 0; j < num; j++)
            cout << road[i][j] <<  "   ";
        cout << endl;
    }*/

    //////////// write the output file ///////////
    /*
    fout << "# " << chords.size() << " data points" <<endl;
    fout << "# index number" << endl;
    for (int i = 0; i < data.size(); i++)
        fout << i << " " <<data[i] << endl;*/
    fin.close();
    //fout.close();
    return 0;
}

void findchords(int i, int j , int** road, map<int, int> chords){
    while(j - i > 1){
        if(road[i][j] == 2){
            int k = chords[j];
            cout << chords[j] << "  " << j << endl;
            findchords(i+1, j-1, road, chords);
            j = i - 1;
        }
        else if(road[i][j] == 3){
            int k = chords[j];
            cout << chords[j] << "  " << j << endl;
            findchords(k, j-1, road, chords);
            j = k - 1;
        }
        else
        {
            j--;
        }
    }
}