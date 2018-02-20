//
// Created by Peeta on 9/24/17.
//


#ifndef INC_2_4_TREE_TREE_H
#define INC_2_4_TREE_TREE_H


#include "Node.h"
#include "LinkedList.h"
#include "MaxHeap.h"

using namespace std;

class Tree {
    Node* root;
    Node* leaf_head;
    void freeNode(Node* n);
    float letterToGPA(string grade);
    bool checkNodeNumber(Node* x);
    bool checkKeys(Node* x);
public:
    Tree();
    ~Tree();

    void setRoot(Node* n);
    Node* getRoot();
    void setLeafHead(Node *n);
    Node* getLeafHead();

    void setLeafNode(Node* x);
    tuple<Node*, int> search(Node* x, int k);
    void insertRecord(Node* x, int pos, string id, string name, string grade);
    void split(Node* x, int i);
    void insertNonFull(Node* x, int k);
    void insertMax(Node* x, int k);
    void insert(int k, string id, string name, string grade);
    void range(Node* x, int i, int k2);
    float gpa(Node* x, int i);
    float gpa(Node* x, int i, int k2);
    vector<string> getAllCourses(Node* x, vector<string> courses);
    string top(int n);
    bool verify(Node* n);

    void preOrder(Node* n);
};


#endif //INC_2_4_TREE_TREE_H
