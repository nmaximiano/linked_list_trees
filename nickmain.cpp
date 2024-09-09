// 4:29pm Sunday,
// Final main file. Read treeData.csv and then ask for user input.
// have a vector that holds each linked list
// Prints all street names, then ask user to select a street (or add street). then asks users to select a block number on that street.
// Prints street name, block number, and number of trees on that block. Then asks for more input:
// 1. Next Block, 2. Prev block, 3. change street, 4. add tree, 5. remove tree, 6. exit

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "linked_list.hpp" // make sure to include linked_list.cpp in the compilation

using namespace std;

void skipLines() {
    cout << endl << endl << endl << endl << endl;
}

LinkedList* chooseStreet(const vector<string>& streets, vector<LinkedList>& streetList) {
    while (true) {
        cout << endl << "Choose a street: " << endl;
        for (int i = 0; i < streets.size(); i++) {
            cout << streets[i] << endl;
        }
        cout << endl;
        string street;
        cin >> street;
        cout << endl;
        for (int i = 0; i < streetList.size(); i++) {
            if (streetList[i].streetName == street) {
                return &streetList[i];
            }
        }
        cout << "Invalid street" << endl;
        exit(1);
        return nullptr;
    }
}

Node* chooseBlock(LinkedList* street) {
    Node* current = street->head;
    cout << "Available blocks: ";
    while (current != nullptr) {
        cout << current->blockNum << " ";
        current = current->next;
    }
    cout << endl << "Choose a block on " << street->streetName <<  " (" << street->size_of_list() << " blocks):" << endl;
    string block;
    cin >> block;
    cout << endl;
    int blockNum = stoi(block);
    Node* blockNode = street->search_list(blockNum);
    return blockNode;
}

string displayBlock(Node* blockNode) {
    while (true) {
        cout << endl << "Street: " << blockNode->streetName << endl;
        cout << "Block: " << blockNode->blockNum << endl;
        cout << "Trees: " << blockNode->treeNum << endl << endl;
        cout << "1  Next Block" << endl;
        cout << "2  Prev Block" << endl;
        cout << "3  Change Street" << endl;
        cout << "4  Add Block (as next)" << endl;
        cout << "5  Edit Block (current)" << endl;
        cout << "6  Exit" << endl;
        string choice;
        cin >> choice;
        int choiceNum = stoi(choice);
        if (choiceNum >= 1 && choiceNum <= 6) {
            return choice;
        }
        else {
            cout << "Invalid choice" << endl;
        }
        

    }
    return "";
}

void readCSV(const string& filename, vector<string>& streetListName, vector<LinkedList>& streetList) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }


    // grab each variable from csv

    string line;
    while (getline(infile, line)) {
        stringstream ss(line);
        string streetName, blockNumStr, treeNumStr;

        getline(ss, streetName, ',');
        getline(ss, blockNumStr, ',');
        getline(ss, treeNumStr, ',');

        // check if street already exists
        bool streetExists = false;
        for (int i = 0; i < streetListName.size(); i++) {
            // street exists
            if (streetListName[i] == streetName) {
                Node* newNode = new Node(streetName, stoi(blockNumStr), stoi(treeNumStr));
                streetList[i].append_node(newNode);
                streetExists = true;
                break;
            }
        } // street doesn't exist
        if (!streetExists) {
            streetListName.push_back(streetName);
            LinkedList newStreet(streetName);
            Node* newNode = new Node(streetName, stoi(blockNumStr), stoi(treeNumStr));
            newStreet.append_node(newNode);
            streetList.push_back(newStreet);
        }
    }
}

void printStreets(const vector<string>& streets) {
    for (int i = 0; i < streets.size(); i++) {
        cout << streets[i] << endl;
    }
}

int main() {
    vector<string> streetListName;
    vector<LinkedList> streetList;
    readCSV("treeData.csv", streetListName, streetList);
    //printStreets(streetListName);
    LinkedList* inpStreet = chooseStreet(streetListName, streetList);
    Node* block = chooseBlock(inpStreet);
    string numInp = displayBlock(block);
    return 0;
}