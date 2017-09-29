//
// Created by Peeta on 9/24/17.
//

#ifndef INC_2_4_TREE_NODE_H
#define INC_2_4_TREE_NODE_H


#include <cstdio>
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
    void setKey(int k, int i);
    int getKey(int i);
    void printKeys();
};

Node::Node() {
    puts("Node default constructor");
}

Node::Node(const bool leaf)
: leaf(leaf) {
    puts("Leaf constructor");
}

Node::~Node() {
    printf("Destructor");
}

/*void Node::copy_to(Node* node) {
    node->setParent(parent);
    node->setNumber(n);
    for (int i = 0; i < MAX_KEYS; i++) {
        node->setKey(keys[i], i);
    }
    node->setLeaf(leaf);
    for (int i = 0; i < MAX_CHILDREN; i++) {
        node->setChild(c[i], i);
    }
}*/

void Node::setParent(Node* p) {
    parent = p;
}

Node* Node::getParent() {
    return parent;
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

void Node::setChild(void* child, int i) {
    c[i] = child;
}

Node *Node::getChild(int i) {
    auto * node = static_cast<Node*>(c[i]);
    return node;
}

void Node::setKey(int k, int i) {
    keys[i] = k;
}

int Node::getKey(int i) {
    return keys[i];
}

void Node::printKeys() {
    for (int i = 0; i < MAX_KEYS; i++) {
        cout << getKey(i) << " ";
    }
    cout << endl;
}


#endif //INC_2_4_TREE_NODE_H
