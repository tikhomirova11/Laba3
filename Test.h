#include <iostream>
#include "BinaryTree.h"

int Test() 
{
    Tree<int>* Test;
    Test = new Tree<int>();

    Test->insert_node(22);
    Test->insert_node(14);
    Test->insert_node(9);
    Test->insert_node(1);
    Test->insert_node(0);
    Test->insert_node(10);
    Test->insert_node(3);

    if (Test->height() == 4)
        std::cout << "Test Height: success" << "\n";
    else 
        std::cout << "Test Height: fail" << "\n";


    if (Test->find_node(10) != nullptr)
        std::cout << "Test FindNode: success" << "\n";
    else 
        std::cout << "Test FindNode: fail" << "\n";


    if (Test->check_element(3) == true && Test->check_element(99) == false)
        std::cout << "Test CheckElement: success" << "\n";
    else {
        std::cout << "Test CheckElement: fail" << "\n";
    };


    Test->delete_node(Test->find_node(Test->get_root(), 3));
    if (Test->check_element(3) == false)
        std::cout << "Test DeleteNode: success" << "\n";
    else 
        cout << "Test DeleteNode: fail" << "\n";

    Test->insert_node(3);


    Tree<int>* Test_i;
    Test_i = new Tree<int>();

    Test_i->insert_node(1);
    Test_i->insert_node(3);
    Test_i->insert_node(0);

    if (Test->find_sub_tree(Test_i) == true)
        cout << "Test Find Sub Tree: success" << "\n";
    else 
        cout << "Test Find Sub Tree: fail" << "\n";



    Tree<int>* tree1;
    tree1 = new Tree<int>();

    tree1 = Test->sub_tree(1);

    if (tree1->check_element(1) == true && tree1->check_element(3) == true && tree1->check_element(0) == true)
        cout << "Test SubTree: success" << "\n";
    else 
        cout << "Test SubTree: fail" << "\n";


    delete Test;
    delete Test_i;
    delete tree;
    delete tree1;

    return 0;
}