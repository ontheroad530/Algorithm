#ifndef TREE_H
#define TREE_H

#include "container.h"
#include "stack.h"

namespace GYH
{

class Pre_Post_Visitor;
class Tree : public virtual Container
{
    class Iter;
public:
    virtual Object& key() const = 0;
    virtual Tree& subtree(unsigned int) const = 0;
    virtual bool is_leaf() const = 0;
    virtual unsigned int degree() const = 0;
    virtual int height() const = 0;
    virtual void depth_first_traversal(Pre_Post_Visitor&) const;
    virtual void breadth_first_traversal(Visitor&) const;

    void accept(Visitor &) const;
    Iterator& new_iterator() const;
};

class Tree::Iter : public Iterator
{
public:
    Iter(Tree const&);
    ~Iter();

    void reset();
    bool is_done() const;
    Object& operator *()const;
    void operator ++();

private:
    Tree const& _tree;
    Stack&  _stack;
};

class General_Tree : public Tree
{
public:
    General_Tree(Object &);
    ~General_Tree();

    void purge();

    Object& key() const;
    General_Tree& subtree(unsigned int) const;
    void attach_subtree(General_Tree&);
    General_Tree& detach_subtree(General_Tree&);

protected:
    Object*                     _key;
    unsigned int                _degree;
    Linked_List<General_Tree*>  _list;
};

class Binary_Tree : public virtual Tree
{
public:
    Binary_Tree();
    Binary_Tree(Object&);
    ~Binary_Tree();

    void purge();
    void depth_first_traversal(Pre_Post_Visitor &) const;

    Object& key() const;
    virtual void attach_key(Object&);
    virtual Object& detach_key();
    virtual Binary_Tree& left()const;
    virtual Binary_Tree& right()const;
    virtual void attach_left(Binary_Tree&);
    virtual void attach_right(Binary_Tree&);
    virtual Binary_Tree& detach_left();
    virtual Binary_Tree& detach_right();

    bool is_empty()const;
    unsigned int degree() const;
    bool is_leaf() const;
    int height() const;
    Tree& subtree(unsigned int) const;

protected:
    int compare_to(const Object &) const;

protected:
    Object*         _key;
    Binary_Tree*    _left;
    Binary_Tree*    _right;
};

class Search_Tree : public virtual Tree, public virtual Searchable_Container
{
public:
    virtual Object& find_min() const = 0;
    virtual Object& find_max() const = 0;
};

class BST : public Binary_Tree, public Search_Tree
{
public:
    BST& left() const;
    BST& right() const;

    Object& find(Object const&) const;
    Object& find_min() const;
    Object& find_max() const;

    void insert(Object&);
    void withdraw(Object&);

    bool is_member(Object const&) const;

protected:
    virtual void attach_key(Object&);
    virtual Object& detach_key();
    virtual void balance();
};


class AVL_Tree: public BST
{
public:
    AVL_Tree();

    int height() const;
    AVL_Tree& left() const;
    AVL_Tree& right() const;


protected:
    int balance_factor()const;
    void adjust_height();
    void ll_rotation();
    void lr_rotation();
    void rr_rotation();
    void rl_rotation();
    void attach_key(Object &);
    Object& detach_key();
    void balance();

protected:
    int     _height;
};

}
#endif // TREE_H
