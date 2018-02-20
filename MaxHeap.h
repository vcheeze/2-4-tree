//
// Created by Peeta on 9/30/17.
// Adapted from Min Heap implementation in: http://www.ideserve.co.in/learn/find-the-nth-most-frequent-number-in-array
//

#ifndef INC_2_4_TREE_MAXHEAP_H
#define INC_2_4_TREE_MAXHEAP_H


#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

class MaxHeap { // using this as a frequency counter
    typedef vector< tuple<string, int> > tuple_list;
    typedef unordered_map<string, int> hashmap;
public:
    void swap(tuple_list array, int i, int j);

    void maxHeapify(tuple_list array, int curIndex, int heapSize);

    void buildMaxHeap(tuple_list array, int heapSize);

    string extractMax(tuple_list array, int heapSize);

    string findNthMostFrequentCourse(vector<string> array, int n);
};


#endif //INC_2_4_TREE_MAXHEAP_H
