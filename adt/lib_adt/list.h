#ifndef LIST_H
#define LIST_H

#include "iterator.h"
#include "container.h"
#include "linked_list.h"

namespace GYH
{

class Position : public Iterator
{

};

class List : public virtual Searchable_Container
{
public:
    virtual Object& operator [] (unsigned int) const = 0;
    virtual Object& operator [] (Position const&) const = 0;
    virtual Position& find_position(Object const&) const = 0;
    virtual void withdraw(Position const &) = 0;
};

class Ordered_List : public virtual List
{
public:
    virtual void inser_after(Position const&, Object&) = 0;
    virtual void inser_before(Position const&, Object&) = 0;
};

class List_As_Linked_List : public virtual Ordered_List
{
public:
    class Pos;
    friend class Pos;
public:
    List_As_Linked_List();

    virtual bool is_member(Object const&) const;
    virtual void insert(Object&);
    virtual void withdraw(Object &);
    virtual Object& find(Object const&) const;

    virtual Object& operator [] (unsigned int) const;
    virtual Object& operator [] (Position const&) const;
    virtual Position& find_position(Object const&) const;
    virtual void withdraw(Position const &);

    virtual void inser_after(Position const&, Object&);
    virtual void inser_before(Position const&, Object&);


    virtual void purge();
    virtual void accept(Visitor&) const;

protected:
    int compare_to(const Object &) const;

protected:
    Linked_List<Object*>    _linked_list;
};

class List_As_Linked_List::Pos : public Position
{
    friend class List_As_Linked_List;
public:
    Pos(List_As_Linked_List const&, List_Element<Object*> const*);

    virtual void reset();
    virtual bool is_done() const;
    virtual Object& operator * () const;
    virtual void operator ++ ();

private:
    List_As_Linked_List const&      _list;
    List_Element<Object*> const*    _element;
};

}
#endif // LIST_H
