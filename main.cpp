#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
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
//        cout << cmd.size() << endl;

        if (cmd[0] != "init"
            && cmd[0] != "exit"
            && cmd[0] != "print"
            && cmd[0] != "ins"
            && cmd[0] != "load"
            && cmd[0] != "find"
            && cmd[0] != "range"
            && cmd[0] != "gpa"
            && cmd[0] != "top"
            && cmd[0] != "verify"
            && cmd[0] != "del") {
            cout << "Invalid command. Please enter a valid command." << endl;
        }

        if (cmd[0] == "exit" && cmd.size() == 1) {
            cout << "Exit the Program" << endl;
            break;
        }


        if (initialized) {
            if (cmd[0] == "print" && cmd.size() == 1) { // print the contents of the tree in pre order
                t.preOrder(t.getRoot());
            } else if (cmd[0] == "ins") {
                t.insert(stoi(cmd[1]), cmd[2], cmd[3], cmd[4]);
                cout << "Inserting " << cmd[1] << endl;
            } else if (cmd[0] == "load" && cmd.size() == 2) {
                string line, path = "../";
                path += cmd[1];
                ifstream inputFile;
                inputFile.open(path);
                if (inputFile.is_open()) {
                    while (getline(inputFile, line)) {
                        // parse each line
                        istringstream iss2(line);
                        vector<string> bulk;
                        copy(istream_iterator<string>(iss2),
                             istream_iterator<string>(),
                             back_inserter(bulk));
                        if (bulk[0] == "print") {
                            t.preOrder(t.getRoot());
                            cout << endl;
                        } else {
                            t.insert(stoi(bulk[1]), bulk[2], bulk[3], bulk[4]);
                        }
                    }
                    inputFile.close();
                } else {
                    cout << "Failed to load file" << endl;
                }
            } else if (cmd[0] == "find" && cmd.size() == 2) { // print out info of the student
                /*Node* n = t.search(t.getRoot(), stoi(cmd[1]));
                cout << "Searching for records of student " << cmd[1] << "..." << endl;
                if (n == nullptr) {
                    cout << "Record not found " << cmd[1] << endl;
                } else {
                    cout << "Record found: " << endl;
                    n->printKeys();
                }*/
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
            }
        } else {
            if (cmd[0] == "init") {
                t.setRoot(new Node(true));
                initialized = true;
                cout << "Initialized" << endl;
            }
        }

        cout << "> ";
    }


    return 0;
}