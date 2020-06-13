#ifndef _NODE_H
#define _NODE_H

template <class T> 
class TreeNode
{
    friend class Tree<T>;
public:
    TreeNode(const T&);
    T get_data();
protected:
    TreeNode* left;           /* ��������� �� ������ ������� */
    TreeNode* right;          /* ��������� �� ������� ������� */
    TreeNode* parent;         /* ��������� �� �������� */
    T data;            /* ���� */
};

template<class T>
TreeNode <T>::TreeNode(const T& a)
{
    data = a;
    left = right = 0;
}

template <class T>
T TreeNode <T>::get_data()
{
    return data;
}
#endif