//
// Created by Peeta on 9/28/17.
//

#ifndef INC_2_4_TREE_LINKEDLIST_H
#define INC_2_4_TREE_LINKEDLIST_H


#include <string>
#include <utility>

using namespace std;

struct node {
    string courseID;
    string courseName;
    string grade;
    node* next;
};


class LinkedList {
    node *head, *tail;
public:
    // constructor
    LinkedList();

    void createNode(string id, string name, string grade);
};

LinkedList::LinkedList() {
    head = nullptr;
    tail = nullptr;
}

void LinkedList::createNode(const string id, const string name, const string grade) {
    auto *temp = new node;
    temp->courseID = id;
    temp->courseName = name;
    temp->grade = grade;
    temp->next = nullptr;
    if (head == nullptr) {
        head = temp;
        tail = temp;
        temp = nullptr;
    } else {
        tail->next = temp;
        tail = temp;
    }
}


#endif //INC_2_4_TREE_LINKEDLIST_H
