#include "linked_list.hpp"

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
    void LinkedList::append_node(Node newNode)
    {
        Node* newPtr = new Node(newNode);

        //if list is empty, add to front
        if(head == nullptr)
        {
            head = newPtr;
            tail = newPtr;
        }
        //if list populated, add to end
        else
        {
            tail->next = newPtr;
            newPtr->prev = tail;
            tail = newPtr;
        }
        
    }

/* insert_node
 *Date created: 9/6/2024
 *Date last edited: 9/6/2024
	* adds node to linked list in specified position */
    void LinkedList::insert_node(Node newNode, int position)
    {
        Node* newPtr = new Node(newNode);

        if(position == 0)
        {
            if (head == nullptr)
            {
                head = tail = newPtr;
            }
            else
            {
                newPtr->next = head;
                head->prev = newPtr;
                head = newPtr;
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
            tail = newPtr;
            NodePtr->next = newPtr;
            newPtr->prev = NodePtr;
        }
        else
        {
            newPtr->next = NodePtr->next;
            newPtr->prev = NodePtr;
            NodePtr->next->prev = newPtr;
            NodePtr->next = newPtr;
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


