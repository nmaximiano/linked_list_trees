#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;


class LinkedList 
{
private:

struct Node 
    {
    //doubly linked implementation
    Node* next = nullptr;
    Node* prev = nullptr;
    int treeNum = 0;
    string blockNum;
    string streetName;
    };

public: 
    //constructor and destructor
    LinkedList();
    ~LinkedList();

    Node* head;
    Node* tail;

    void append_node(Node *newNode);

    void insert_node(Node *newNode, int position);

    void delete_node(const string& block);

    void print_list() const;

    int size_of_list() const;

    Node* search_list(const string& block);

    bool streetInList(string name);

    void parseFile(ifstream &infile, string &transfer, string &street, stringstream &allData, string &block, int&trees, int &numlines, LinkedList &Street);

    Node *createNewNode(string streetName, string block, int trees);


};

bool openStreetData(ifstream &infile, string filename);

int main()
{
    LinkedList List;

    ifstream infile;
    stringstream allData;
    string transfer = "", street = "" , block = "";
    int trees = 0;
    int numlines = 0;
    bool infileIsOpen = false;

    infileIsOpen = openStreetData(infile, "treeData.csv");

    if(!infileIsOpen)
    {
        cout << "The file did not open" << endl;
        exit(-1);
    }else 
    {
        cout << "THE FILE OPENED!!" << endl;
    }

    List.parseFile(infile, transfer, street, allData, block, trees, numlines, List);

    List.print_list();


    cout << "You found " << List.search_list("3")->streetName << " street" << endl;


}
    //constructor
    LinkedList::LinkedList()
    {
        head = nullptr;
        tail = nullptr;
    }  

    //destructor
    LinkedList::~LinkedList()
    {
        Node* NodePtr = head;

        while(NodePtr != nullptr)
        {
            Node* NextPtr = NodePtr->next;
            delete NodePtr;
            NodePtr = NextPtr;
        }
    }


/* append_node
 *Date created: 9/6/2024
 *Date last edited: 9/6/2024
	* adds existing node to the end of the linked list. */
    void LinkedList::append_node(Node *newNode)
    {

        //if list is empty, add to front
        if(head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        //if list populated, add to end
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        
    }

/* insert_node
 *Date created: 9/6/2024
 *Date last edited: 9/6/2024
	* adds node to linked list in specified position */
    void LinkedList::insert_node(Node *newNode, int position)
    {

        if(position == 0)
        {
            if (head == nullptr)
            {
                head = tail = newNode;
            }
            else
            {
                newNode->next = head;
                head->prev = newNode;
                head = newNode;
            }
        }

        Node* NodePtr = head;
        int i = 0;
        while(NodePtr != nullptr && i < position - 1)
        {
            NodePtr = NodePtr->next;
            i++;
        
        }

        if(NodePtr == nullptr)
        {
            append_node(newNode);
        }
        else if(NodePtr->next == nullptr)
        {
            tail = newNode;
            NodePtr->next = newNode;
            newNode->prev = NodePtr;
        }
        else
        {
            newNode->next = NodePtr->next;
            newNode->prev = NodePtr;
            NodePtr->next->prev = newNode;
            NodePtr->next = newNode ;
        }
    }

/* delete_node
 *Date created: 9/6/2024
 *Date last edited: 9/6/2024
	* deletes specified node */
    void LinkedList::delete_node(const string& block)
    {
        Node* NodePtr = head;

        while(NodePtr != nullptr)
        {
            if(NodePtr->blockNum == block)
            {
                if(NodePtr == head)
                {
                    head = NodePtr->next;
                    if(head != nullptr)
                    {
                        head->prev = nullptr;
                    }
                }
                else
                {
                    NodePtr->prev->next = NodePtr->next;
                }
                if(NodePtr == tail)
                {
                    tail = NodePtr->prev;
                    if(tail != nullptr)
                    {
                        tail->next = nullptr;
                    }
                }
                else if(NodePtr->next != nullptr)
                {
                    NodePtr->next->prev = NodePtr->prev;
                }

                delete NodePtr;
                return;
            }
            NodePtr = NodePtr->next;
        }
        cout << "Node does not exist" << endl;
    }

/* print_list
 *Date created: 9/6/2024
 *Date last edited: 9/6/2024
	* writes contents of linked list to console */
    void LinkedList::print_list() const
    {
        Node* NodePtr = head;
        while (NodePtr != nullptr)
        {
            cout << "There are " << NodePtr->treeNum << " trees on block " << NodePtr->blockNum << " of street " << NodePtr->streetName << "." << endl;
            NodePtr = NodePtr->next;
        }
        
    }

/* size_of_list
 *Date created: 9/6/2024
 *Date last edited: 9/6/2024
	* returns the size of the list */
    int LinkedList::size_of_list() const
    {
        int size = 0;
        Node* NodePtr = head;
        while (NodePtr != nullptr)
        {
            size++;
            NodePtr = NodePtr->next;
        }
        return size;
    }

/* append_node
 *Date created: 9/6/2024
 *Date last edited: 9/6/2024
	* returns specified node from list */
    LinkedList::Node* LinkedList::search_list(const string& block)
    {
        Node* NodePtr = head;

        while(NodePtr != nullptr)
        {
            if(NodePtr->blockNum == block)
            {
                return NodePtr;
            }
            NodePtr = NodePtr->next;
        }
        cout << "Node does not exist" << endl;
        return nullptr;
    }





//making parse file
LinkedList::Node *LinkedList::createNewNode(string streetName, string block, int trees)
{
    Node* newNode = new Node;
    newNode->streetName = streetName;
    newNode->blockNum = block;
    newNode->treeNum = trees;

    return newNode;
}

bool LinkedList::streetInList(string name)
{
    Node* nodePtr = head;

    while(nodePtr != nullptr)
    {
        if(nodePtr->streetName == name) //found street name return true
        {
            return true; 
        }

        if(nodePtr->next == nullptr) //return false if next ptr is nullptr becasue street name not found
        {
            return false;
        }
        nodePtr = nodePtr->next;
    }
    return false; 

}





void LinkedList::parseFile(ifstream &infile, string &transfer, string &street, stringstream &allData, string &block, int&trees, int &numlines, LinkedList &Street)
{
    Node* nodePtr= nullptr;
    string streetName = "";
    string blockNum = "";
    int numTrees = 0;

    while(!infile.eof())
    {
        getline(infile, transfer);
        allData.clear();
        allData.str(transfer);

        if (transfer != "" && transfer != "\n")
        {
            for(int i = 0; i < 3; i++)
            {
                if(i==0)
                {
                    
                    getline(allData, street, ',');
                        streetName = street;
                }
                else if (i == 1)
                {
                    getline(allData, block, ',');
                        blockNum = block;   //block number is in the second column
                }
                else if(i==2)
                {
                    allData >> trees; //everything in the last column is the trees
                    numTrees = trees;
                }
            }
            Street.append_node(Street.createNewNode(streetName, block, trees));
            cout << "Processed a street..." << endl;
        }

        numlines++;
    }

    cout << endl << "All data collected" << endl;
    return;

}

bool openStreetData(ifstream &infile, string filename)
{
    infile.open(filename);
    if (infile.is_open())
    {
        return true;
    }
    return false;
}