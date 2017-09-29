#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include "tree.h"
using namespace std;

// work on else condition for invalid command


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

        if (initialized) {
            if (cmd.size() == 1 && cmd[0] == "print") { // print the contents of the tree in pre order
                t.preOrder(t.getRoot());
            } else if (/*cmd.size() == 5 && */cmd[0] == "ins") {
                t.insert(/*t.getRoot(), */stoi(cmd[1]));
                cout << "Inserting " << cmd[1] << endl;
            } else if (cmd[0] == "load") {
                string line, path = "../";
                path += cmd[1];
                ifstream inputFile;
                inputFile.open(path);
                if (inputFile.is_open()) {
//                cout << "Successfully loaded file" << endl;
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
                            t.insert(stoi(bulk[1]));
                        }
                    }
                    inputFile.close();
                } else {
                    cout << "Failed to load file" << endl;
                }
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
            }/* else {
                cout << "Invalid command. Please enter a valid command." << endl;
            }*/
        } else {
            if (cmd[0] == "init") {
                t.setRoot(new Node(true));
//            t.setLeafHead(t.getRoot());
                initialized = true;
                cout << "Initialized" << endl;
            }/* else {
                cout << "Invalid command. Please enter a valid command." << endl;
            }*/
        }

        if (cmd[0] == "exit") {
            cout << "Exit the Program" << endl;
            break;
        }

        cout << "> ";
    }


    return 0;
}