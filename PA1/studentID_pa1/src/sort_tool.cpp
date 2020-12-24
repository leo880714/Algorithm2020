// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
// **************************************************************************

#include "sort_tool.h"
#include<iostream>

// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    for(int i = 0; i < data.size(); i++){
        int key = data[i];
        int j = i - 1;
        while(j >= 0 && data[j] > key ){
            data[j+1] = data[j];
            j--;
        }
        data[j+1] = key;
    }
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data){
    QuickSortSubVector(data, 0, data.size() - 1);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    if(low < high){
        int pivot = Partition(data, low, high);
        /*
        cout << "  smaller part: ";
        for(int i = low; i <= pivot; i++)
            cout << data[i] <<  "   ";
        cout << endl;
        cout << "  larger part: ";
        for(int i = pivot+1; i <= high; i++)
            cout << data[i] <<  "   ";
        cout << endl;*/
        QuickSortSubVector(data, low, pivot);
        QuickSortSubVector(data, pivot+1, high);
    }
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    // Hint : Textbook page 171
    int med = (low+high)/2;
    int pivot = data[med];
    
    if(data[low] < data[high]){
        if(data[med] > data[high])
            pivot = data[high];
        else{
            if(data[med] > data[low])
                pivot = data[med];
            else
                pivot = data[low];
        }
    }
    else{
        if(data[med] > data[low])
            pivot = data[low];
        else{
            if(data[med] > data[high])
                pivot = data[med];
            else
                pivot = data[high];
        }
    }
    int i = low-1;
    int j = high+1;
    while(1){
        do {
            i++;
        } while (data[i] < pivot);

        do {
            j--;
        } while (data[j] > pivot);
 
        if (i >= j)
            return j;
        swap(data[i], data[j]);
    }
    return j;
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    if((high-low) >= 1){
        int middle1 = (low + high)/2;
        int middle2 = middle1 + 1;
        MergeSortSubVector(data, low, middle1);
        MergeSortSubVector(data, middle2, high);
        Merge(data, low, middle1, middle2, high);
    }   
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int leftIdx = low;
    int rightIdx = middle2;
    int combineIdx = low;
    vector<int> left;
    vector<int> right;
    for(int i = 0; i < middle1 - low + 1; i++){
        left.push_back(data[low+i]);
    }
    for(int i = 0; i < high - middle2 + 1; i++){
        right.push_back(data[middle2+i]);
    }

    /*
    for(int i = 0; i < middle1 - low + 1; i++){
        cout << left[i] << " ";
    }
    cout << endl;
    for(int i = 0; i < high - middle2 + 1; i++){
         cout << right[i] << " ";
    }
    cout << endl;*/

    int l = 0;
    int r = 0;
    while((l < left.size()) && (r < right.size())){
        if(left[l] < right[r]){
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
    /*
    for(int i = low ;i <= high; i++)
        cout << data[i] << "    ";
    cout << endl;*/
}

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 0; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    int left = 2 * root + 1;
    int right = 2 * root + 2;
    int largest = right;
    if(right >= heapSize)
        largest = left;
    
    bool isLeaf = false;
    if(right >= heapSize && left >= heapSize)
        isLeaf = true;

    if(left < heapSize && right < heapSize && data[left] > data[right]){
        largest = left;
    }

    if(!isLeaf && largest != root && data[root] < data[largest]){
        swap(data[largest], data[root]);
        MaxHeapify(data, largest);
    }

}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for(int i = heapSize/2 - 1; i>= 0; i--)
        MaxHeapify(data, i);
}

