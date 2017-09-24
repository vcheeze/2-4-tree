//
// Created by Peeta on 9/24/17.
//

#ifndef INC_2_4_TREE_NODE_H
#define INC_2_4_TREE_NODE_H


#include <cstdio>

#define MAX_KEYS 4
#define MAX_CHILDREN 5


class Node {
    Node *parent = nullptr;
    int n = 0;
    int keys[MAX_KEYS] = {0};
    bool leaf = false;
    Node *c[MAX_CHILDREN] = {nullptr};
public:
    Node();

    explicit Node(bool leaf);
    ~Node();

    // methods
    void setNumber(int number);
    int getNumber();
    void setLeaf(bool l);
    bool getLeaf();
    void setChild(Node *child, int i);
    Node* getChild(int i);
    void setKey(int k, int i);
    int getKey(int i);
};

Node::Node() {
//    puts("Default constructor");
}

Node::Node(const bool leaf)
: leaf(leaf) {
//    puts("Leaf constructor");
}

Node::~Node() {
//    printf("Destructor");
}

void Node::setNumber(const int number) {
    n = number;
}

int Node::getNumber() {
    return n;
}

void Node::setLeaf(const bool l) {
    leaf = l;
}

bool Node::getLeaf() {
    return leaf;
}

void Node::setChild(Node *child, int i) {
    c[i] = child;
}

Node *Node::getChild(int i) {
    return c[i];
}

void Node::setKey(int k, int i) {
    keys[i] = k;
}

int Node::getKey(int i) {
    return keys[i];
}


#endif //INC_2_4_TREE_NODE_H
