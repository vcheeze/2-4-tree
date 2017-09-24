#include <iostream>
#include <sstream>
#include <vector>
#include "Node.h"
using namespace std;




Node create() {
    Node n(true);
    return n;
}


void split(Node x, int i) {
    Node z;
    Node y = *x.getChild(i);
    int t = y.getNumber() / 2;
    z.setLeaf(y.getLeaf());
    z.setNumber(y.getNumber() - t);

    int j;
    for (j = 0; j < t; j++) {
        z.setKey(y.getKey(j+t), j);
    }

    if (!y.getLeaf()) {
        for (j = 0; j < t; j++) {
            z.setChild(y.getChild(j+t), j);
        }
    }
    y.setNumber(t);

    for (j = x.getNumber()-1; j > i+1; j--) {
        x.setChild(x.getChild(j), j+1);
    }
    x.setChild(&z, i+1);

    for (j = x.getNumber() - 1; j > i; j--) {
        x.setKey(x.getKey(j), j+1);
    }

    x.setKey(y.getKey(t-1), i);
    x.setNumber(x.getNumber()+1);
}


void insertNonFull(Node x, int k) {
    int i = x.getNumber();

    if (x.getLeaf()) {
        while(i >= 1 && k < x.getKey(i-1)) {
            x.setKey(x.getKey(i-1), i);
            i--;
        }
        x.setKey(k, i);
        x.setNumber(x.getNumber()+1);
    } else {
        while (i >= 1 && k < x.getKey(i-1)) {
            i--;
        }
        i++;
        if (x.getChild(i-1)->getNumber() == 4) {
            split(x, i-1);
            if (k > x.getKey(i-1)) {
                i++;
            }
        }
        insertNonFull(*x.getChild(i-1), k);
    }
}


void insertMax(Node x, int k) {
    int i = x.getNumber();

    if (x.getLeaf()) {
        x.setKey(k, i);
        x.setNumber(x.getNumber() + 1);
    } else {
        x.setKey(k, i);
        if (x.getChild(i-1)->getNumber() == 4) {
            split(x, i-1);
            i++;
        }
        insertMax(*x.getChild(i-1), k);
    }
}


void insert(Node root, int k) {
    int i = root.getNumber();
    Node s;
    if (i == 4) {
        s.setLeaf(false);
        s.setNumber(1);
        s.setChild(&root, 0);
        s.setKey(root.getKey(3), 0);
        root = s;
        split(s, 0);
        if (k > s.getKey(1)) {
            insertMax(s, k);
        } else {
            insertNonFull(s, k);
        }
    } else {
        if (k > s.getKey(i)) {
            insertMax(root, k);
        } else {
            insertNonFull(root, k);
        }
    }

}


int main() {
    cout << "> ";
    Node root;
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
            root = create();
            initialized = true;
            cout << "Initialized" << endl;
        } else if (cmd[0] == "ins") {
            if (initialized) {
                insert(root, stoi(cmd[1]));
                cout << "Inserting " << cmd[1] << endl;
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