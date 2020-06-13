#include <iostream>
#ifndef _TREE_H
#define _TREE_H
using namespace std;

template <class T> class Tree;
#include "node.h"

template <class T>
class Tree
{
public:
    Tree();                                                    /* ����������� */
    Tree(TreeNode<T>*);
    int insert_node(const T&);                         /* ��������� ���� */
    TreeNode<T>* delete_node(TreeNode<T>*);     /* ������� ���� */
    void inorder_walk(TreeNode<T>*);                   /* �������� ��� ����� � ����������� ������� */
    void print_tree(TreeNode<T>*, int);
    void entering();
    int height (TreeNode<T>*);
    int height();
    bool find_sub_tree(Tree<T>*);
    bool check_element(const T&);
    bool equality(Tree<T>*);
    Tree<T>* sub_tree(const T&);
    TreeNode<T>* find_max(TreeNode<T>*);         /* ������� ���� � ����������� ��������� ����� � ���������� ��������� �� ���� */
    TreeNode<T>* find_min(TreeNode<T>*);
    TreeNode<T>* find_node(TreeNode<T>*, const T&);
    TreeNode<T>* find_node(const T&);
    TreeNode<T>* find_succsessor(const T&);     /* ������� ������� � ������, ��������� �� ������ ������ */
    TreeNode<T>* get_root();                            /* ���������� ��������� �� ������ ������ */
private:
    TreeNode<T>* root;                                  /* ����������, ��� ������ */
};

template<class T>
Tree<T>::Tree()
{
    root = 0;                      /* � ������ ������ ����� */
}

template<class T>
Tree<T>::Tree(TreeNode<T>* r)
{
    root = r;
}

template<class T>
int Tree<T>::insert_node(const T& x)
{
    TreeNode<T>* n = new TreeNode<T>(x);  /* ������� ����� ����, ��� �� ����� ��������� */
    TreeNode<T>* ptr;
    TreeNode<T>* ptr1 = nullptr;

    n->parent = n->left = n->right = 0;          /* �� - ���� */
    ptr = root;
    while (ptr != 0)                     /* ���� �� ����� � ���� ���������� ����� ��� ������ ������ ��������, ��� ������ ���� �������� */
    {
        ptr1 = ptr;                 /* ������� �������� ������ ���� */
        if (x < ptr->get_data())  /* �� ����������� ������ ������ - ����� �������� ����� ������ ��������, */
            ptr = ptr->left;
        else
            ptr = ptr->right;   /* ������ - ������ */
    }
    n->parent = ptr1;
    if (ptr1 == 0)                       /* ������ ���� �����? */
        root = n;
    else
    {
        if (x < ptr1->get_data())
            ptr1->left = n;
        else
            ptr1->right = n;
    }
    return 0;
}

/* �������� ��� ������ - ���� � z ��� �����, �� �������� 0 � ��������������� ����
 * �������� z, ���� � z ���� ���� �������, �� ����� �������� z, �������� ��� �������� �������� �
 * ��� ��������. ���� �� ����� ����, �� ��������� ��������� �������������: �� ������� ���������
 * (� ������ ������� �� ������) �� z ������� y; � ���� ��� ������ ������� (������). ������ �����
 * ����������� ���� � �������������� ������ �� ������� y � ������� z, � ���� ������� y �������
 * ��������� ���� �������� */

template<class T>
TreeNode<T>* Tree<T>::delete_node(TreeNode<T>* z)
{
    TreeNode<T>* y;
    TreeNode<T>* x;
    if (z->left == 0 || z->right == 0)               /* � ���� � ��������� ���� ������� ���� ������� y, ������� �� ����� ������� �� ������. ��� ���� z, ���� ��������� �� z */
        y = z;
    else
        y = find_succsessor(z->get_data());
    if (y->left != 0)                                  /* x - ��������� �� ������������� ������� y ��� 0 ���� ������� ��� */
        x = y->left;
    else
        x = y->right;
    if (x != 0)                                        /* ��� � ��������� 9 ����� - ��������� y */
        x->parent = y->parent;
    if (y->parent == 0)
        root = x;
    else
    {
        if (y == (y->parent)->left)
            (y->parent)->left = x;
        else
            (y->parent)->right = x;
    }
    if (y != z)                                        /* ���� �� �������� ������, �������� �� z, �� �� ������ ���������� � z */
        z->data = y->get_data();
    return y;
}
template<class T>
TreeNode<T>* Tree<T>::find_max(TreeNode<T>* x)
{
    while (x->right != 0)                              
        x = x->right;
    return x;
}

template<class T>
TreeNode<T>* Tree<T>::find_min(TreeNode<T>* x)
{
    while (x->left != 0)
        x = x->left;
    return x;
}

template<class T>
TreeNode<T>* Tree<T>::find_succsessor(const T& val)
{
    TreeNode<T>* x = find_node(root, val);                     /* ������� ��������� �� ���� � ������ val */
    TreeNode<T>* y;
    if (x == 0)
        return 0;
    if (x->right != 0)                                                /* ���� � ��� ���� ������ ����, �� ��������� ������� - ����������� � ������ ��������� */
        return find_min(x->right);
    y = x->parent;
    while (y != 0 && x == y->right)                                   /* ����� - ���� ����� � ���� ������ �������, ���������� ����� �������� ������ �������� */
    {
        x = y;
        y = y->parent;
    }
    return y;
}
template<class T>
TreeNode<T>* Tree<T>::find_node(TreeNode<T>* n, const T& val)
{
    if (n == 0 || val == n->get_data())
        return n;
    if (val > n->get_data())
        return find_node(n->right, val);
    else
        return find_node(n->left, val);
}

template<class T>
TreeNode<T>* Tree<T>:: find_node(const T& val)
{
    return find_node(this -> root, val);
}

template<class T>
void Tree<T>::inorder_walk(TreeNode<T>* n)
{
    if (n != 0)
    {
        inorder_walk(n->left);
        std:: cout << n->get_data() << std:: endl;
        inorder_walk(n->right);
    }
}

template<class T>
void Tree<T>::entering()
{
    int n = 0;
    cout << " Enter number of elements: " << endl;
    cin >> n;

    cout << "Enter elements:" << endl;   /* ��������� ��� */
    for (int i = 0; i < n; i++)
    {
        T a;
        cin >> a;
        insert_node(a);
    }

}

template<class T>
void Tree<T>::print_tree(TreeNode<T>* Node, int lvl) {
    if (Node != nullptr) {

        print_tree(Node->right, lvl + 1);
        for (int i = 0; i < lvl - this->height(); i++) std::cout << "    ";
        std::cout << "[" << lvl - this->height() << "]";
        std::cout << Node->get_data() << "\n";
        print_tree(Node->left, lvl + 1);
    }
}

template<class T>
int Tree<T>:: height(TreeNode<T>* Node) {
    int L, R;

    if (Node->left == nullptr && Node->right == nullptr) {
        return 0;
    }
    else {
        if (Node->left != nullptr) {
            L = height(Node->left) + 1;
        }
        else L = 0;

        if (Node->right != nullptr) {
            R = height(Node->right) + 1;
        }
        else R = 0;
    }
    if (L > R) {
        return L;
    }
    else return R;

}

template<class T>
Tree<T>* Tree<T>::sub_tree(const T& x)
{
    TreeNode<T>* newNode = this->find_node(x);
    Tree<T>* newTree = new Tree<T>(newNode);

    return newTree;
}

template<class T>
bool Tree<T>::find_sub_tree(Tree<T>* subtree) {
    if (subtree->get_root() == nullptr && this->get_root() != nullptr)
        return false;
    if (subtree->get_root() == this->get_root())
        return true;
    if (this->check_element(subtree->get_root()->data)) {
        Tree<T>* checktree = this->sub_tree(subtree->get_root()->data);
        return checktree->equality(subtree);
    }
    else return false;
}

template<class T>
bool Tree<T>::check_element(const T& value) {
    TreeNode<T>* tmp = this->root;

    while (tmp != nullptr) {
        if (value < tmp->get_data()) {
            tmp = tmp->left;
        }
        else {
            if (value > tmp->get_data()) {
                tmp = tmp->right;
            }
            else return true;
        }
    }

    if (tmp == nullptr) return false;
}

template<class T>
bool Tree<T>:: equality(Tree<T>* tree)
{
    if ((this->root != nullptr && tree->get_root() == nullptr) || (this->root == nullptr && tree->get_root() != nullptr)) {
        return false;
    }
    if (this->root == nullptr && tree->get_root() == nullptr) {
        return true;
    }

    bool res = true;
    TreeNode<T>* ThisRight = root->right;
    TreeNode<T>* ThisLeft = root->left;
    TreeNode<T>* TreeRight = tree->get_root()->right;
    TreeNode<T>* TreeLeft = tree->get_root()->left;

    if (ThisLeft != nullptr && TreeLeft != nullptr) {
        res = res && this->sub_tree(ThisLeft->data)->equality(tree->sub_tree(TreeLeft->data));
    }
    else if (TreeLeft == nullptr && TreeRight == nullptr) {}
    else return false;

    if (ThisRight != nullptr && TreeRight != nullptr) {
        res = res && this->sub_tree(ThisRight->data)->equality(tree->sub_tree(TreeRight->data));
    }
    else if (ThisLeft == nullptr && ThisRight == nullptr) {}
    else return false;

    return res;
}

template<class T>
int Tree<T>:: height() {
    return height(root);
}
template<class T>
TreeNode<T>* Tree<T>::get_root()
{
    return root;
}
#endif


//////////////////////////////////////////////

