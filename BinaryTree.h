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
    Tree();                                                    /* конструктор */
    Tree(TreeNode<T>*);
    int insert_node(const T&);                         /* вставляет узел */
    TreeNode<T>* delete_node(TreeNode<T>*);     /* удаляет узел */
    void inorder_walk(TreeNode<T>*);                   /* печатает все ключи в неубывающем порядке */
    void print_tree(TreeNode<T>*, int);
    void entering();
    int height (TreeNode<T>*);
    int height();
    bool find_sub_tree(Tree<T>*);
    bool check_element(const T&);
    bool equality(Tree<T>*);
    Tree<T>* sub_tree(const T&);
    TreeNode<T>* find_max(TreeNode<T>*);         /* находит узел с минимальным значением ключа и возвращает указатель на него */
    TreeNode<T>* find_min(TreeNode<T>*);
    TreeNode<T>* find_node(TreeNode<T>*, const T&);
    TreeNode<T>* find_node(const T&);
    TreeNode<T>* find_succsessor(const T&);     /* находит элемент с ключем, следующим за данным числом */
    TreeNode<T>* get_root();                            /* возвращает указатель на корень дерева */
private:
    TreeNode<T>* root;                                  /* собственно, сам корень */
};

template<class T>
Tree<T>::Tree()
{
    root = 0;                      /* в начале дерево пусто */
}

template<class T>
Tree<T>::Tree(TreeNode<T>* r)
{
    root = r;
}

template<class T>
int Tree<T>::insert_node(const T& x)
{
    TreeNode<T>* n = new TreeNode<T>(x);  /* создаем новый узел, его мы будем вставлять */
    TreeNode<T>* ptr;
    TreeNode<T>* ptr1 = nullptr;

    n->parent = n->left = n->right = 0;          /* он - лист */
    ptr = root;
    while (ptr != 0)                     /* идем от корня и ищем подходящее место для нашего нового элемента, оно должно быть свободно */
    {
        ptr1 = ptr;                 /* будущий родитель нового узла */
        if (x < ptr->get_data())  /* по определению нашего дерева - слева значение ключа меньше родителя, */
            ptr = ptr->left;
        else
            ptr = ptr->right;   /* справа - больше */
    }
    n->parent = ptr1;
    if (ptr1 == 0)                       /* дерево было пусто? */
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

/* возможны три случая - если у z нет детей, то помещаем 0 в соответствующее поле
 * родителя z, если у z есть один ребенок, то можно вырезать z, соединив его родителя напрямую с
 * его ребенком. Если же детей двое, то требуются некоторые приготовления: мы находим следующий
 * (в смысле порядка на ключах) за z элемент y; у него нет левого ребенка (всегда). Теперь можно
 * скопировать ключ и дополнительные данные из вершины y в вершину z, а саму вершину y удалить
 * описанным выше способом */

template<class T>
TreeNode<T>* Tree<T>::delete_node(TreeNode<T>* z)
{
    TreeNode<T>* y;
    TreeNode<T>* x;
    if (z->left == 0 || z->right == 0)               /* в этой и следующих двух строках ищем вершину y, которую мы потом вырежем из дерева. Это либо z, либо следующий за z */
        y = z;
    else
        y = find_succsessor(z->get_data());
    if (y->left != 0)                                  /* x - указатель на существующего ребенка y или 0 если таковых нет */
        x = y->left;
    else
        x = y->right;
    if (x != 0)                                        /* эта и следующие 9 строк - вырезание y */
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
    if (y != z)                                        /* если мы вырезали вершин, отличную от z, то ее данные перемещаем в z */
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
    TreeNode<T>* x = find_node(root, val);                     /* получим указатель на ноду с ключем val */
    TreeNode<T>* y;
    if (x == 0)
        return 0;
    if (x->right != 0)                                                /* если у нее есть правые дети, то следующий элемент - минимальный в правом поддереве */
        return find_min(x->right);
    y = x->parent;
    while (y != 0 && x == y->right)                                   /* иначе - идем вверх и ищем первый элемент, являющийся левым потомком своего родителя */
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

    cout << "Enter elements:" << endl;   /* заполняем его */
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

