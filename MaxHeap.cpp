#include "MaxHeap.h"


void MaxHeap::swap(tuple_list array, int i, int j) {
    tuple<string, int> tmp ("", 0);
    get<string>(tmp) = get<string>(array[i]);
    get<int>(tmp) = get<int>(array[i]);
    array[i] = array[j];
    array[j] = tmp;
}

void MaxHeap::maxHeapify(tuple_list array, int curIndex, int heapSize) {
    // left child in heap
    int leftChild = 2*curIndex+1;

    // right child in heap
    int rightChild = 2*curIndex+2;

    // index pointing to the largest element(out of node and its two children)
    int largestIndex = curIndex;

    if (leftChild < heapSize && (get<int>(array[leftChild]) > get<int>(array[curIndex]))) {
        largestIndex = leftChild;
    }

    if (rightChild < heapSize && (get<int>(array[rightChild]) > get<int>(array[largestIndex]))) {
        largestIndex = rightChild;
    }

    // make the largest element as node and maxHeapify the corresponding sub-tree
    // since the swap operation could result in violation of max-heap property for corresponding sub-tree
    if (largestIndex != curIndex) {
        swap(array, curIndex, largestIndex);
        maxHeapify(array, largestIndex, heapSize);
    }
}

void MaxHeap::buildMaxHeap(tuple_list array, int heapSize) {
    // find index of the last internal node
    int lastElementIndex = array.size() - 1;
    int lastInternalNodeIndex = (lastElementIndex - 1)/2;

    // call maxHeapify for all internal nodes
    for (int i = lastInternalNodeIndex; i >= 0; i--) {
        maxHeapify(array, i, heapSize);
    }
}

string MaxHeap::extractMax(tuple_list array, int heapSize) {
    string maxElement;
    maxElement = get<string>(array[0]);
    swap(array, 0, heapSize-1);
    maxHeapify(array, 0, heapSize-1);

    return maxElement;
}

string MaxHeap::findNthMostFrequentCourse(vector<string> array, int n) {
    if (array.empty() || array.size() < n) {
        cout << "Invalid input case" << endl;
        return "Failed";
    }

    // build hashTable containing frequency of each element in the array
    hashmap frequencyTable;

    for (int i = 0; i < array.size(); i++) {
        if (frequencyTable.find(array[i]) == frequencyTable.end()) {
            frequencyTable[array[i]] = 1;
        } else {
            int prevFrequency = frequencyTable.at(array[i]);
            frequencyTable[array[i]] = prevFrequency + 1;
        }
    }

    // check if the number of frequencies we have got is at least equal to 'n'
    if (frequencyTable.size() < n) {
        cout << "Nth most popular course cannot be found" << endl;
        return "Failed";
    }

    // then create the array of tuples(number, frequency) out of hashTable of frequencies
    tuple_list list;
    auto it = frequencyTable.begin();
    int i = 0;

    while (it != frequencyTable.end()) {
        list.push_back(make_tuple(it->first, it->second));
        i++;
        it++;
    }

    // build max-heap using this array of tuples
    int heapSize = list.size();
    buildMaxHeap(list, heapSize);

    // do extractMax operation 'n' times on this max-heap.
    // return the aggregate of all the extractMax operations
    string result, temp;
    for (i = 0; i < n; i++) {
        temp = extractMax(list, heapSize);
        result += temp;
        result += " | ";
        list.erase(list.begin());
//            list.erase(remove(list.begin(), list.end(), temp), list.end());
        heapSize -= 1;
    }

    return result;
}
