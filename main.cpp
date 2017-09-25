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
            t.preOrder(t.getRoot());
        } else if (cmd[0] == "ins") {
            if (initialized) {
                t.insert(t.getRoot(), stoi(cmd[1]));
                cout << "Inserting " << cmd[1] << endl;
                t.preOrder(t.getRoot());
            }
        } else if (input == "load") {
            cout << "Loading file" << endl;
        } else if (input == "exit") {
            cout << "Exit the Program" << endl;
            break;
        }

        cout << "> ";
    }


    return 0;
}