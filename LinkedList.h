//
// Created by Peeta on 9/28/17.
// Adapted from implementation in:
// https://www.codementor.io/codementorteam/a-comprehensive-guide-to-implementation-of-singly-linked-list-using-c_plus_plus-ondlm5azr
//

#ifndef INC_2_4_TREE_LINKEDLIST_H
#define INC_2_4_TREE_LINKEDLIST_H


#include <string>
#include <utility>
#include <iostream>

using namespace std;

struct node {
    string courseID;
    string courseName;
    string grade;
    node* next = nullptr;
};


class LinkedList {
    node *head, *tail;
public:
    // constructor
    LinkedList();
    ~LinkedList();

    // methods
    node* getHead();
    void createNode(string id, string name, string grade);
    void insert_start(string id, string name, string grade);
    void insert_pos(int pos, string id, string name, string grade);
    void delete_first();
    void delete_last();
    void delete_pos(int pos);
    void delete_node(string id);
    void display();
};


#endif // INC_2_4_TREE_LINKEDLIST_H
