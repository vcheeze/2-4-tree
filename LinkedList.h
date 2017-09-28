//
// Created by Peeta on 9/28/17.
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

    // methods
    void createNode(string id, string name, string grade);
    void insert_start(string id, string name, string grade);
    void insert_pos(int pos, string id, string name, string grade);
    void delete_first();
    void delete_last();
    void delete_pos(int pos);
    void display();
};

LinkedList::LinkedList() {
    head = nullptr;
    tail = nullptr;
}

void LinkedList::createNode(string id, string name, string grade) {
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

void LinkedList::insert_start(string id, string name, string grade) {
    auto *temp = new node;
    temp->courseID = id;
    temp->courseName = name;
    temp->grade = grade;
    temp->next = head;
    head = temp;
}

void LinkedList::insert_pos(int pos, string id, string name, string grade) {
    auto *prev = new node;
    auto *curr = new node;
    auto *temp = new node;

    curr = head;
    for (int i = 1; i < pos; i++) {
        prev = curr;
        curr = curr->next;
    }
    temp->courseID = id;
    temp->courseName = name;
    temp->grade = grade;
    prev->next = temp;
    temp->next = curr;
}

void LinkedList::delete_first() {
    auto *temp = new node;
    temp = head;
    head = head->next;
    delete temp;
}

void LinkedList::delete_last() {
    auto *curr = new node;
    auto *prev = new node;

    curr = head;
    while(curr->next != nullptr) {
        prev = curr;
        curr = curr->next;
    }
    tail = prev;
    prev->next = nullptr;
    delete curr;
}

void LinkedList::delete_pos(int pos) {
    auto *curr = new node;
    auto *prev = new node;

    curr = head;
    for (int i = 1; i < pos; i++) {
        prev = curr;
        curr = curr->next;
    }
    prev->next = curr->next;
}

void LinkedList::display() {
    auto *temp = new node;
    temp = head;
    while(temp != nullptr) {
        cout << temp->courseID << " | " << temp->courseName << " | " << temp->grade << endl;
        temp = temp->next;
    }
}


#endif //INC_2_4_TREE_LINKEDLIST_H
