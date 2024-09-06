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

    void LinkedList::append_node(Node& newNode)
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

    void LinkedList::insert_node(Node& newNode, int position)
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
        
        while(NodePtr != nullptr)
        {
            for(int i = 0; i < position - 1; i++)
            {
                NodePtr = NodePtr->next;
            }
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

    void LinkedList::print_list() const
    {
        Node* NodePtr = head;
        while (NodePtr != nullptr)
        {
            cout << "There are " << NodePtr->treeNum << " trees on block " << NodePtr->blockNum << " of street " << NodePtr->streetName << "." << endl;
            NodePtr = NodePtr->next;
        }
    }

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

void getdatafromCSV(vector<LinkedList>& streetList, const string& filename)
{
    ifstream infile(filename);

    
}
