#include "LinkedList.h"


LinkedList::LinkedList() {
    head = nullptr;
    tail = nullptr;
}

LinkedList::~LinkedList() {
    node *curr = head;
    node *next;
    while(curr != nullptr) {
        next = curr->next;
        delete curr;
        curr = next;
    }
    head = nullptr;
}

node* LinkedList::getHead() {
    return head;
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
    delete curr;
}

/* Helpful tutorial: https://www.cs.bu.edu/teaching/c/linked-list/delete/ */
void LinkedList::delete_node(string id) {
    auto *curr = new node;
    node *prev = nullptr;

    for (curr = head;
         curr != nullptr;
         prev = curr, curr = curr->next) {

        if (curr->courseID == id) { // found the value
            if (prev == nullptr) {
                // fix beginning pointer
                head = curr->next;
            } else {
                // previous node's next skips over removed node;
                prev->next = curr->next;
            }
            delete curr;
            return;
        }
    }
}

void LinkedList::display() {
    auto *temp = new node;
    temp = head;
    while(temp != nullptr) {
        cout << temp->courseID << " | " << temp->courseName << " | " << temp->grade << endl;
        temp = temp->next;
    }
}
