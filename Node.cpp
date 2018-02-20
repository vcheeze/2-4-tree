#include "Node.h"


Node::Node() = default;

Node::Node(const bool leaf)
: leaf(leaf) {
    puts("Leaf constructor");
}

Node::~Node() = default;

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
    auto *node = static_cast<Node*>(c[i]);
    return node;
}

LinkedList* Node::getRecords(int i) {
    auto *l = static_cast<LinkedList*>(c[i]);
    return l;
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
