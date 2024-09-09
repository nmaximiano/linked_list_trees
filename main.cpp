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

// make strings compatible for comparison
string convertToLower(string str) {
    for (int i = 0; i < str.size(); i++) {
        str[i] = tolower(str[i]);
    }
    return str;
}

// choose street menu selection
LinkedList* chooseStreet(const vector<string>& streets, vector<LinkedList>& streetList) {
    // loop until valid street is chosen
    while (true) {
        cout << endl << "Choose a street: " << endl;
        for (int i = 0; i < streets.size(); i++) {
            cout << streets[i] << endl;
        }
        cout << endl;
        string street;
        cin >> street;
        cout << endl;
        // compare street input to street list
        for (int i = 0; i < streetList.size(); i++) {
            string lowerStreet = convertToLower(streetList[i].streetName);
            string lowerInp = convertToLower(street);
            if (lowerStreet == lowerInp) {
                return &streetList[i];
            }
        }
        cout << "Invalid street" << endl;
        continue;
        return nullptr;
    }
}

// choose block menu selection
Node* chooseBlock(LinkedList* street) {
    // loop until valid block is chosen
    while (true) {
        Node* current = street->head;
        // list available blocks
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
    
        if (blockNum >= 1 && blockNum <= street->size_of_list()) {
            Node* blockNode = street->search_list(blockNum);
            return blockNode;
        } else {
            cout << "Invalid block" << endl;
            continue;
        }
    }
    return nullptr;
}

int displayBlock(Node* blockNode) {
    while (true) {
        cout << endl << "Street: " << blockNode->streetName << endl;
        cout << "Block: " << blockNode->blockNum << endl;
        cout << "Trees: " << blockNode->treeNum << endl << endl;
        cout << "1  Next Block" << endl;
        cout << "2  Prev Block" << endl;
        cout << "3  Change Street" << endl;
        cout << "4  Exit" << endl;
        string choice;
        cin >> choice;
        int choiceNum = stoi(choice);
        if (choiceNum == 1) {
            if (blockNode->next != nullptr) {
                blockNode = blockNode->next;
            }
            else {
                cout << "No next block" << endl;
                continue;
            }
        } else if (choiceNum == 2) {
            if (blockNode->prev != nullptr) {
                blockNode = blockNode->prev;
            }
            else {
                cout << "No previous block" << endl;
                continue;
            }
        } else if (choiceNum >= 3 && choiceNum <= 6) {
            return choiceNum;
        }
        else {
            cout << "Invalid choice" << endl;
        }
        

    }
    return 0;
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

int main() {
    vector<string> streetListName;
    vector<LinkedList> streetList;
    readCSV("treeData.csv", streetListName, streetList);
    while (true) {
        LinkedList* inpStreet = chooseStreet(streetListName, streetList);
        Node* block = chooseBlock(inpStreet);
        while (true) {
            int numInp = displayBlock(block);
            if (numInp == 1) {
                // 1 check if next block exists and go to it (continue displayBlock loop)
                if (block->next != nullptr) {
                    block = block->next;
                    continue;
                }
                else {
                    cout << endl << "No next block" << endl;
                }
                continue;
            }
            if (numInp == 2) {
                // 2 check if prev block exists and go to it (continue displayBlock loop)
                if (block->prev != nullptr) {
                    block = block->prev;
                    continue;
                }
                else {
                    cout << endl << "No previous block" << endl;
                }
                continue;
            }
            if (numInp == 3) {
                // 3 go back to chooseStreet loop
                break;
            }
            if (numInp == 4) {
                // 4 exit
                return 0;
            }
        }
    }
    return 0;
}