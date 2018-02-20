//
// Created by Peeta on 9/24/17.
//

#ifndef INC_2_4_TREE_NODE_H
#define INC_2_4_TREE_NODE_H


#include <cstdio>
#include "LinkedList.h"

using namespace std;

#define MAX_KEYS 4
#define MAX_CHILDREN 5

class Node {
    Node *parent = nullptr;
    int n = 0;
    int keys[MAX_KEYS] = {0};
    bool leaf = false;
    // set children to void pointer so that it can point at Node as well as LinkedList in the leaf nodes
    void *c[MAX_CHILDREN] = {nullptr};
public:
    Node();

    explicit Node(bool leaf);
    ~Node();

    // methods
    void setParent(Node* p);
    Node* getParent();
    void setNumber(int number);
    int getNumber();
    void setLeaf(bool l);
    bool getLeaf();
    void setChild(void* child, int i);
    Node* getChild(int i);
    LinkedList* getRecords(int i);
    void setKey(int k, int i);
    int getKey(int i);
    void printKeys();
};


#endif //INC_2_4_TREE_NODE_H
