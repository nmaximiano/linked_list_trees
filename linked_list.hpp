
#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP
#endif

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

    struct Node 
    {
    //doubly linked implementation
    Node* next;
    Node* prev;
    int treeNum;
    int blockNum;
    string streetName;
    };

class LinkedList 
{
private:

public: 
    //constructor and destructor
    LinkedList();
    ~LinkedList();

    Node* head;
    Node* tail;

    void append_node(Node& newNode);

    void insert_node(Node& newNode, int position);

    void delete_node(const int& block);

    void print_list() const;

    int size_of_list() const;

    Node* search_list(const int& block);

};

void getdatafromCSV(vector<LinkedList>& streetList, const string& filename);