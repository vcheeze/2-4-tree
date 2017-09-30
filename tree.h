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
    float letterToGPA(string grade);
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
            delete n;
        }
    }
}

float Tree::letterToGPA(string grade) {
    if (grade == "A") {
        return 4.0;
    } else if (grade == "A-") {
        return 3.7;
    } else if (grade == "B+") {
        return 3.3;
    } else if (grade == "B") {
        return 3.0;
    } else if (grade == "B-") {
        return 2.7;
    } else if (grade == "C+") {
        return 2.3;
    } else if (grade == "C") {
        return 2.0;
    } else if (grade == "C-") {
        return 1.7;
    } else if (grade == "D+") {
        return 1.3;
    } else if (grade == "D") {
        return 1.0;
    } else if (grade == "D-") {
        return 0.7;
    }

    return 0.0;
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

void Tree::setLeafNode(Node* x) {
    if (x->getLeaf()) {
        leaf_head = x;
    } else {
        if (x->getChild(0) != nullptr) {
            setLeafNode(x->getChild(0));
        }
    }
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
    } else if (i <= x->getNumber() && k < x->getKey(i-1)) {
        if (x->getLeaf()) {
            return make_tuple(x, -1);
        } else {
            return search(x->getChild(i-1), k);
        }
    }

    return make_tuple(x, -1);
}

void Tree::insertRecord(Node *x, int pos, string id, string name, string grade) {
    if (x->getLeaf()) {
        if (x->getRecords(pos) != nullptr) {
            x->getRecords(pos)->createNode(id, name, grade);
        } else {
            auto *l = new LinkedList;
            l->createNode(id, name, grade);
            x->setChild(l, pos);
        }
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

    for (j = 0; j < t; j++) {
        z->setChild(y->getChild(j+t), j);
        y->setChild(nullptr, j+t); // reset the pointers of y to null
    }
    z->setChild(y->getChild(4), 4);
    y->setNumber(t);
    if (y->getLeaf()) {
        y->setChild(z, 4); // make the smaller leaf node point to the larger leaf node
    }

    for (j = x->getNumber()-1; j >= i+1; j--) {
        x->setChild(x->getChild(j), j+1);
    }
    x->setChild(z, i+1);
    z->setParent(x);

    for (j = x->getNumber() - 1; j >= i; j--) {
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
            x->setChild(x->getRecords(i-1), i);
            x->setChild(nullptr, i-1);
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
        x->setNumber(x->getNumber()+1);
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
//        setLeafNode(root);
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
        auto y = search(root, k);
        if (get<int>(y) != -1) { // if the node with key k is found
            insertRecord(get<Node*>(y), get<int>(y), id, name, grade);
        }
    } else {
        if (k > root->getKey(i-1)) {
            insertMax(root, k);
        } else {
            insertNonFull(root, k);
        }
        auto z = search(root, k);
        if (get<int>(z) != -1) { // if the node with key k is found
            insertRecord(get<Node*>(z), get<int>(z), id, name, grade);
        }
    }

    // setLeafNode(root); // set the first node on the leaf level
}

void Tree::range(Node* x, int i, int k2) {
    if (x->getLeaf()) { // only traverse if x is a leaf node
        while (i <= x->getNumber() && k2 > x->getKey(i - 1)) {
            if (x->getRecords(i-1) != nullptr) {
                x->getRecords(i-1)->display();
            }
            i++;
        }

        if (i <= x->getNumber() && k2 == x->getKey(i - 1)) {
            x->getRecords(i-1)->display();
        } else {
            range(x->getChild(4), 1, k2);
        }
    }
}

float Tree::gpa(Node* x, int i) {
    if (x->getLeaf()) {
        float total = 0.0, count = 0.0;
        node* temp;
        temp = x->getRecords(i)->getHead();
        while(temp != nullptr) {
            string g = temp->grade;
            total += letterToGPA(g);
            count += 1.0;
            temp = temp->next;
        }
        return total/count;
    }
    return 5.0; // error value to return
}

float Tree::gpa(Node* x, int i, int k2) {
    if (x->getLeaf()) {
        node* temp;
        float total = 0.0, count = 0.0;

        while(i <= x->getNumber() && k2 > x->getKey(i-1)) {
            if (x->getRecords(i-1) != nullptr) {
                temp = x->getRecords(i-1)->getHead();
                while(temp != nullptr) {
                    string g = temp->grade;
                    total += letterToGPA(g);
                    count += 1.0;
                    temp = temp->next;
                }
            }
            i++;
        }

        if (i <= x->getNumber() && k2 == x->getKey(i - 1)) {
            if (x->getRecords(i-1) != nullptr) {
                temp = x->getRecords(i-1)->getHead();
                while(temp != nullptr) {
                    string g = temp->grade;
                    total += letterToGPA(g);
                    count += 1.0;
                    temp = temp->next;
                }
            }
        } else {
            gpa(x->getChild(4), 0, k2);
        }
    }

    return 5.0; // error value to return
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
