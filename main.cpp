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
            } else if (cmd[0] == "load" && cmd.size() == 2) { // type the file name without the ".txt" extension
                string line, path = "../";
                path += cmd[1];
                path += ".txt";
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
                auto n = t.search(t.getRoot(), stoi(cmd[1]));
                cout << "Searching for records of student " << cmd[1] << "..." << endl;
                if (get<int>(n) == -1) {
                    cout << "Record not found: " << cmd[1] << endl;
                } else {
                    cout << "Record found: " << get<Node*>(n)->getKey(get<int>(n)) << endl;
                    get<Node*>(n)->getRecords(get<int>(n))->display();
                }
            } else if (cmd[0] == "range" && cmd.size() == 3) {
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
                auto d = t.search(t.getRoot(), stoi(cmd[1]));
                if (get<int>(d) == -1) {
                    cout << "Student not found" << endl;
                } else {
                    get<Node*>(d)->getRecords(get<int>(d))->delete_node(cmd[2]);
                    cout << "Successfully deleted course" << endl;
                }
            }
        } else {
            if (cmd[0] == "init") {
                t.setRoot(new Node(true));
                t.setLeafHead(t.getRoot());
                initialized = true;
                cout << "Initialized" << endl;
            } else {
                cout << "Tree not initialized: use 'init' to initialize." << endl;
            }
        }

        cout << "> ";
    }


    return 0;
}