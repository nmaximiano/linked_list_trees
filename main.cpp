#include "linked_list.hpp"

int main()
{
    LinkedList List;

    Node Street1;
    Street1.blockNum = 1;
    Street1.streetName = "Mission";
    Street1.treeNum = 5;

    Node Street2;
    Street2.blockNum = 2;
    Street2.streetName = "Sharp";
    Street2.treeNum = 10;

    Node Street3;
    Street3.blockNum = 3;
    Street3.streetName = "Sharp";
    Street3.treeNum = 10;

    Node Street4;
    Street4.blockNum = 4;
    Street4.streetName = "Sharp";
    Street4.treeNum = 6;

    List.append_node(Street1);
    List.append_node(Street2);
    List.append_node(Street3);
    List.insert_node(Street4, 1);


    List.print_list();

    List.delete_node(4); //specify which block number to delete

    List.print_list();

    cout << "You found " << List.search_list(3)->streetName << " street" << endl;


}