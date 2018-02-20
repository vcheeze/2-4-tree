// allow configuration file
// implement verify

#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include "tree.h"

using namespace std;

int main(int argc, char*argv[]) {
//    cout << argc << endl;
//    cout << argv[0] << endl << argv[1] << endl << argv[2] << endl;
    Tree t;
    ifstream inputFile;
    string line;
    bool initialized = false;

    if (argc == 3 && strcmp(argv[1], "-c") == 0) {
        string path = "../sample_input/";
        path += argv[2];
        path += ".txt";
        inputFile.open(path);
        if (inputFile.is_open()) {
            cout << "Opened config file" << endl;
        } else {
            cout << "Failed to open config file" << endl;
        }
    }

    cout << "> ";

    while(true) {
        vector<string> cmd;
        if (inputFile.is_open()) {
            if (!getline(inputFile, line)) {
                inputFile.close();
            }
            // parse each line
            istringstream iss(line);
            copy(istream_iterator<string>(iss),
                 istream_iterator<string>(),
                 back_inserter(cmd));
        } else {
            // get the input
            string input;
            getline(cin, input);

            // parse the input
            istringstream iss(input);
            copy(istream_iterator<string>(iss),
                 istream_iterator<string>(),
                 back_inserter(cmd));
        }

        cout << cmd[0] << endl;

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


        if (initialized) { // if tree is initialized
            if (cmd[0] == "print" && cmd.size() == 1) { // print the contents of the tree in pre order
                t.preOrder(t.getRoot());
            } else if (cmd[0] == "ins") {
                cout << "Inserting " << cmd[1] << endl;
                t.insert(stoi(cmd[1]), cmd[2], cmd[3], cmd[4]);
            } else if (cmd[0] == "load" && cmd.size() == 2) { // type the file name without the ".txt" extension
                string line, path = "../sample_input/";
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
                       if (bulk[0] == "ins") {
                            cout << "Inserting " << bulk[1] << endl;
                            t.insert(stoi(bulk[1]), bulk[2], bulk[3], bulk[4]);
                        } else {
                            cout << "Invalid command found in file" << endl;
                            break;
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
                    cout << "Course ID | Course Name | Grade" << endl;
                    get<Node*>(n)->getRecords(get<int>(n))->display();
                }
            } else if (cmd[0] == "range" && cmd.size() == 3) {
                cout << "Range from " << cmd[1] << " to " << cmd[2] << endl;
                auto a = t.search(t.getRoot(), stoi(cmd[1]));
                auto b = t.search(t.getRoot(), stoi(cmd[2]));
                Node* n = get<Node*>(a);
                int i = get<int>(a);
                int j = get<int>(b);
                if (i == -1) { // can't find k1
                    cout << "Cannot find " << cmd[1] << endl;
                } else if (j == -1) {
                    cout << "Cannot find " << cmd[2] << endl;
                } else {
                    cout << "CourseID | Course Name | Grade" << endl;
                    t.range(n, i+1, stoi(cmd[2]));
                }
            } else if (cmd[0] == "gpa") {
                if (cmd.size() == 2) {
                    cout << "Average GPA for " << cmd[1] << endl;
                    auto g = t.search(t.getRoot(), stoi(cmd[1]));
                    Node *gNode = get<Node*>(g);
                    int gi = get<int>(g);
                    float average = t.gpa(gNode, gi);
                    if (average != 5.0) {
                        cout << average << endl;
                    }
                } else if (cmd.size() == 3) {
                    cout << "Average GPA from " << cmd[1] << " to " << cmd[2] << endl;
                    auto a = t.search(t.getRoot(), stoi(cmd[1]));
                    auto b = t.search(t.getRoot(), stoi(cmd[2]));
                    Node* n = get<Node*>(a);
                    int i = get<int>(a);
                    int j = get<int>(b);
                    if (i == -1) { // can't find student 1
                        cout << "Cannot find " << cmd[1] << endl;
                    } else if (j == -1) {
                        cout << "Cannot find " << cmd[2] << endl;
                    } else {
                        float average = t.gpa(n, i+1, stoi(cmd[2]));
                        if (average != 5.0) {
                            cout << average << endl;
                        }
                    }
                }
            } else if (cmd[0] == "top") {
                cout << "The " << cmd[1] << " most popular courses: " << endl;
                cout << t.top(stoi(cmd[1])) << endl;
            } else if (cmd[0] == "verify") {
                bool result = t.verify(t.getRoot());
                if (result) {
                    cout << "Verification result: true" << endl;
                } else {
                    cout << "Verification result: false" << endl;
                }
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
        } else { // if tree is not initialized
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
