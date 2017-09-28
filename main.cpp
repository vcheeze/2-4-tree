#include <iostream>
#include <sstream>
#include <vector>
#include "tree.h"
using namespace std;




int main() {
    cout << "> ";
    Tree t;
    bool initialized = false;

    while(true) {
        // get the input
        string input;
        getline(cin, input);

        // parse the input
        istringstream iss(input);
        vector<string> cmd;
        copy(istream_iterator<string>(iss),
             istream_iterator<string>(),
             back_inserter(cmd));

        if (cmd[0] == "init" && !initialized) {
            t.setRoot(new Node(true));
            initialized = true;
            cout << "Initialized" << endl;
        } else if (cmd[0] == "print") { // print the contents of the tree in pre order
//            t.getRoot()->printKeys();
            t.preOrder(t.getRoot());
        } else if (cmd[0] == "ins") {
            if (initialized) {
                t.insert(/*t.getRoot(), */stoi(cmd[1]));
                cout << "Inserting " << cmd[1] << endl;
            }
        } else if (cmd[0] == "load") {
            cout << "Loading file" << endl;
        } else if (cmd[0] == "find") {
            int key = t.search(t.getRoot(), stoi(cmd[1]));
            cout << "Searching for " << cmd[1] << "..." << endl;
            if (key == 0) {
                cout << "Record not found " << cmd[1] << endl;
            } else {
                cout << "Record found: " << key << endl;
            }
        } else if (cmd[0] == "range") {
            cout << "Range from " << cmd[1] << " to " << cmd[2] << endl;
        } else if (cmd[0] == "gpa") {
            if (cmd[2].empty()) {
                cout << "GPA for " << cmd[1] << endl;
            } else {
                cout << "GPA from " << cmd[1] << " to " << cmd[2] << endl;
            }
        } else if (cmd[0] == "top") {
            cout << "The " << cmd[1] << " most popular courses: " << endl;
        } else if (cmd[0] == "verify") {
            cout << "Verification result: " << endl;
        } else if (cmd[0] == "del") {
            cout << "Deleting course " << cmd[2] << " from student " << cmd[1] << endl;
        } else if (cmd[0] == "exit") {
            cout << "Exit the Program" << endl;
            break;
        } else {
            cout << "Invalid command. Please enter a valid command." << endl;
        }

        cout << "> ";
    }


    return 0;
}