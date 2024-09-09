#include "linked_list.hpp"

//node constructor
Node::Node() {
    streetName = "";
    treeNum = 0;
    blockNum = 0;
    next = nullptr;
    prev = nullptr;
}

Node::Node(std::string streetName, int blockNum, int treeNum) {
    this->streetName = streetName;
    this->blockNum = blockNum;
    this->treeNum = treeNum;
    next = nullptr;
    prev = nullptr;
}

Node::Node(Node& other) {
    streetName = other.streetName;
    treeNum = other.treeNum;
    blockNum = other.blockNum;
    next = other.next;
    prev = other.prev;
}

    //constructor
LinkedList::LinkedList()
    {
        head = nullptr;
        tail = nullptr;
    }  

LinkedList::LinkedList(std::string inpStreetName)
    {
        head = nullptr;
        tail = nullptr;
        this->streetName = inpStreetName;
    }

    //copy constructor
LinkedList::LinkedList(const LinkedList& other)
    {
        head = nullptr;
        tail = nullptr;
        this->streetName = other.streetName;
        Node* NodePtr = other.head;
        while(NodePtr != nullptr)
        {
            Node* newNode = new Node(NodePtr->streetName, NodePtr->blockNum, NodePtr->treeNum);
            append_node(newNode);
            NodePtr = NodePtr->next;
        }
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
    void LinkedList::append_node(Node* newNode)
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
    void LinkedList::insert_node(Node* newNode, int position) {

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
            NodePtr->next = newNode;
        }
    }

/* delete_node
 *Date created: 9/6/2024
 *Date last edited: 9/6/2024
	* deletes specified node */
    void LinkedList::delete_node(const int& block)
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
    Node* LinkedList::search_list(const int& block)
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


