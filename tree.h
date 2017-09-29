//
// Created by Peeta on 9/24/17.
//


#ifndef INC_2_4_TREE_TREE_H
#define INC_2_4_TREE_TREE_H

#include "Node.h"
#include "LinkedList.h"
using namespace std;


class Tree {
    Node* root;
    Node* leaf_head;
    void freeNode(Node* n);
//    Node* findInsertPos(Node* curr, int k);
public:
    Tree();
    ~Tree();

    void setRoot(Node* n);
    Node* getRoot();
    void setLeafHead(Node *n);
    Node* getLeafHead();

    tuple<Node*, int> search(Node* x, int k);
    void insertRecord(Node* x, int pos, string id, string name, string grade);
    void split(Node* x, int i);
    void insertNonFull(Node* x, int k);
    void insertMax(Node* x, int k);
    void insert(int k, string id, string name, string grade);
    void range(int k1, int k2);

    void preOrder(Node* n);
};

Tree::Tree() {
    root = nullptr;
    leaf_head = root;
}

Tree::~Tree() {
    freeNode(root);
}

void Tree::freeNode(Node* n) {
    if (n != nullptr) {
        if (n->getLeaf()) { // linked list destructor will automatically be called
            delete(n);
        } else {
            for (int i = 0; i < MAX_CHILDREN - 1; i++) {
                if (n->getChild(i) != nullptr) {
                    freeNode(n->getChild(i));
                }
            }
            delete (n);
        }
    }
}

/*Node* Tree::findInsertPos(Node* curr, int k) {
    int i = 0;
    while(curr->getKey(i) != 0) {
        if (k > curr->getKey(i)) { // keep going
            if (i == 4) { // reached the last key of this node
                findInsertPos(curr->getChild(4), k);
            } else {
                i++;
            }
        } else if (k <= curr->getKey(i)) { // found a potential position
            if (i == 0) { // if curr->getKey(i) is the first key of this node
                Node* p = curr->getParent();
                for(int j = 0; j < p->getNumber(); j++) {
                    if (k < p->getKey(j)) {
                        return p->getChild(j);
                    }
                }
            } else {
                return curr;
            }
        }
    }
    findInsertPos(curr->getChild(4), k);
}*/

void Tree::range(int k1, int k2) {

}

void Tree::setRoot(Node* n){
    root = n;
}

Node* Tree::getRoot() {
    return root;
}

void Tree::setLeafHead(Node *n) {
    leaf_head = n;
}

Node* Tree::getLeafHead() {
    return leaf_head;
}

tuple<Node*, int> Tree::search(Node* x, int k) { // return node pointer of the key found
    int i = 1;

    while(i <= x->getNumber() && k > x->getKey(i-1)) {
        i++;
    }

    if (i <= x->getNumber() &&  k == x->getKey(i-1)) {
        if (x->getLeaf()) {
            return make_tuple(x, i-1);
        } else {
            return search(x->getChild(i-1), k);
        }
    }

    return make_tuple(x, -1);

/*    if (x->getLeaf()) {
        return nullptr;
    } else {
        return search(x->getChild(i-1), k);
    }*/
}

void Tree::insertRecord(Node *x, int pos, string id, string name, string grade) {
    auto* l = new LinkedList;
    l->createNode(id, name, grade);
    if (x->getLeaf()) {
        x->setChild(l, 0);
    } else {
        cout << "Node is not a leaf node. Cannot insert record." << endl;
    }
}

void Tree::split(Node* x, int i) {
    auto * z = new Node();
    Node* y = x->getChild(i);
    int t = y->getNumber() / 2;
    z->setLeaf(y->getLeaf());
    z->setNumber(y->getNumber() - t);

    int j;
    for (j = 0; j < t; j++) {
        z->setKey(y->getKey(j+t), j);
        y->setKey(0, j+t); // reset the keys of y to 0
    }

    if (!y->getLeaf()) {
        for (j = 0; j < t; j++) {
            z->setChild(y->getChild(j+t), j);
            y->setChild(nullptr, j+t); // reset the pointers of y to null
        }
    }
    y->setNumber(t);
    if (y->getLeaf()) {
        y->setChild(z, 4); // make the smaller leaf node point to the larger leaf node
    }

    for (j = x->getNumber()-1; j >= i+1; j--) { // check this
        x->setChild(x->getChild(j), j+1);
    }
    x->setChild(z, i+1);
    z->setParent(x);

    for (j = x->getNumber() - 1; j > i; j--) {
        x->setKey(x->getKey(j), j+1);
    }

    x->setKey(x->getKey(i), i+1);
    x->setKey(y->getKey(t-1), i);
    x->setNumber(x->getNumber()+1);
}


void Tree::insertNonFull(Node* x, int k) {
    int i = x->getNumber();

    if (x->getLeaf()) {
        while(i >= 1 && k < x->getKey(i-1)) {
            x->setKey(x->getKey(i-1), i);
            i--;
        }
        x->setKey(k, i);
        x->setNumber(x->getNumber()+1);
    } else {
        while (i >= 1 && k < x->getKey(i-1)) {
            i--;
        }
        i++;
        if (x->getChild(i-1)->getNumber() == 4) {
            split(x, i-1);
            if (k > x->getKey(i-1)) {
                i++;
            }
        }
        insertNonFull(x->getChild(i-1), k);
    }
}


void Tree::insertMax(Node* x, int k) {
    int i = x->getNumber();

    if (x->getLeaf()) {
        x->setKey(k, i);
        x->setNumber(x->getNumber() + 1);
    } else {
        x->setKey(k, i-1);
        if (x->getChild(i-1)->getNumber() == 4) {
            split(x, i-1);
            i++;
        }
        insertMax(x->getChild(i-1), k);
    }
}


void Tree::insert(int k, string id, string name, string grade) {
    auto x = search(root, k);
    if (get<int>(x) != -1) { // if the node with key k is found
        insertRecord(get<Node*>(x), get<int>(x), id, name, grade);
        return;
    }

    int i = root->getNumber();
    if (i == 4) {
        auto * s = new Node();
        s->setLeaf(false);
        s->setNumber(1);
        s->setChild(root, 0);
        root->setParent(s);
        s->setKey(root->getKey(3), 0);
        root = s;
        split(s, 0);
        if (k > s->getKey(1)) {
            insertMax(s, k);
        } else {
            insertNonFull(s, k);
        }
    } else {
        if (k > root->getKey(i-1)) {
            insertMax(root, k);
        } else {
            insertNonFull(root, k);
        }
    }
}

void Tree::preOrder(Node *n) {
    if (n) {
        if (n->getLeaf()) { // if n is a leaf node, do not print the children
            n->printKeys();
        } else {
            n->printKeys();
            for (int i = 0; i < MAX_CHILDREN - 1; i++) {
                if (n->getChild(i) != nullptr) {
                    preOrder(n->getChild(i));
                }
            }
        }
    }
}


#endif //INC_2_4_TREE_TREE_H
