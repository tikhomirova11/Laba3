#include <iostream>
#include <iomanip>
#include "BinaryTree.h"
#include "Test.h"

using namespace std;

int main()
{
    cout << "Hi! Please, choose type of list: \n1. int \n2. double" << endl;

    int choice(0);
    cin >> choice;

    if ((choice > 2) || (choice < 1))
    {
        while ((choice > 2) || (choice < 1))
        {
            cout << "ERROR! WRONG NUMBER!\n Please, try again." << endl;
            cin >> choice;
        }
    }

    Tree<int>* Tree1;
    Tree1 = new Tree<int>();
    if (choice == 1) Tree1->entering();

    Tree<double>* Tree2;
    Tree2 = new Tree<double>();  
    if (choice == 2) Tree2->entering();

    int ch = 0;
    do
    {
        cout << " \n Choose the operation : \n1. Find min and max \n2. Delete element \n3. Print \n4. Find Sub Tree \n5. Hight \n6. Sub tree \n7. Test \n 8. Exit" << endl;
        cin >> ch; 

        if ((ch > 6) || (ch < 1))
        {
            while ((ch > 8) || (ch < 1))
            {
                cout << "ERROR NUMBER!\nPlease, try again:";
                cin >> ch;
            }
        }

        switch (ch)
        {
        case 1:

            if (choice == 1)
            {
                cout << endl << "Minimum is: " << (Tree1->find_min(Tree1->get_root()))->get_data() << endl;
                cout << endl << "Maximum is: " << (Tree1->find_max(Tree1->get_root()))->get_data() << endl;
            }

            if (choice == 2)
            {
                cout << endl << "Minimum is: " << (Tree2->find_min(Tree2->get_root()))->get_data() << endl;
                cout << endl << "Maximum is: " << (Tree2->find_max(Tree2->get_root()))->get_data() << endl;
            }
            break;
          
        case 2:
            int a;
            cout << "Enter node value you want to delete:";     /* попробуем удалить узел с ключем a */
            cin >> a;

            if (choice == 1)
            {
                Tree1->delete_node(Tree1->find_node(Tree1->get_root(), a));
                cout << "Rezult:\n";
                Tree1->inorder_walk(Tree1->get_root());
            }
            if (choice == 2)
            {
                Tree2->delete_node(Tree2->find_node(Tree2->get_root(), a));      /* если их несколько, то удалится первый найденный */
                cout << "Rezult:\n";
                Tree2->inorder_walk(Tree2->get_root());
            }
            break;

        case 3:
            if (choice == 1) Tree1->print_tree(Tree1->get_root(), Tree1->height());
            if (choice == 2) Tree2->print_tree(Tree2->get_root(), Tree2->height());
            break;
        case 5:
            if (choice == 1) std::cout << Tree1->height();
            if (choice == 2) std::cout << Tree2->height();
            break;
        case 6:
            int ptr1;
            double ptr2;
            cout << "Enter element: ";
            if (choice == 1) { cin >> ptr1; }
            else cin >> ptr2;

            Tree<int>* sub1;
            sub1 = new Tree<int>();

            if (choice == 1) 
            {
                sub1 = Tree1->sub_tree(ptr1);
                sub1->print_tree(sub1->get_root(), sub1->height());
            }

            Tree<double>* sub2;
            sub2 = new Tree<double>();

            if (choice == 2) 
            {
                sub2 = Tree2->sub_tree(ptr2);
                sub2->print_tree(sub2->get_root(), sub2->height());
            }
            break;
        case 4:
            Tree<int> * f1;
            f1 = new Tree<int>();

            if (choice == 1) 
            {
                f1->entering();
                if (Tree1->find_sub_tree(f1) == true) { cout << "\nTrue"; }
                else cout << "\nFalse";
            }

            Tree<double>* f2;
            f2 = new Tree<double>();

            if (choice == 2) 
            {
                f2->entering();
                if (Tree2->find_sub_tree(f2) == true)
                {
                    cout << "\nTrue";
                }
                else cout << "\nFalse";
            }
            break;
        case 7:
            Test();
        case 8:
            cout << "\nThanks for using this program";

        }
        


    } while (ch != 8);


    return 0;

}