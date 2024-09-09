
#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP
#endif

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Node {
    public:
        Node();
        Node(string streetName, int blockNum, int treeNum);
        Node(Node& other);
        Node* next = nullptr;
        Node* prev = nullptr;
        string streetName;
        int treeNum;
        int blockNum;
};

class LinkedList 
{
private:

public: 
    //constructor and destructor
    string streetName;

    LinkedList();
    LinkedList(std::string inpStreetName);
    LinkedList(const LinkedList& other);
    ~LinkedList();

    Node* head;
    Node* tail;

    void append_node(Node* newNode);

    void insert_node(Node* newNode, int position);

    void delete_node(const int& block);

    void print_list() const;

    int size_of_list() const;

    Node* search_list(const int& block);

};

void getdatafromCSV(vector<LinkedList>& streetList, const string& filename);