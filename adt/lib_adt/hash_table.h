#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "array.h"
#include "queue.h"
#include "container.h"
#include "linked_list.h"

namespace GYH
{

class Hash_Table : public Searchable_Container
{
public:
    Hash_Table(unsigned int);
    virtual unsigned int h(Object const&) const;

protected:
    unsigned int    _length;
};

class Chained_Hash_Table: public Hash_Table
{
    class Iter;
    friend class Iter;
public:
    Chained_Hash_Table(unsigned int);
    ~Chained_Hash_Table();

    void purge();
    void insert(Object &object);
    void withdraw(Object &object);
    Object& find(const Object &) const;

    bool is_member(Object const&) const;
    void accept(Visitor&) const;
    Iterator& new_iterator() const;

private:
    int compare_to(Object const&) const;

private:
    Array< Linked_List<Object*> >   _array;
};

class Chained_Hash_Table::Iter: public Iterator
{
public:
    Iter(Array< Linked_List<Object*> > const&);
    void reset();
    bool is_done() const;
    Object& operator * () const;
    void operator ++ ();

private:
    Array< Linked_List<Object*> > const&   _array;
    Queue&  _queue;
    unsigned int     _pos;
};


class Chained_Scatter_Table: public Hash_Table
{
    class Entry
    {
    public:
        Entry();

        enum { NULL_PTR = ~0U };

        Object*         _object;
        unsigned int    _next;
    };

public:
    Chained_Scatter_Table(unsigned int);
    ~Chained_Scatter_Table();

    void purge();
    void insert(Object &);
    Object& find(const Object &) const;
    void withdraw(Object &object);

    bool is_member(Object const&) const;
    void accept(Visitor&) const;
    Iterator& new_iterator() const;

private:
    int compare_to(Object const&) const;

private:
    Array<Entry>    _array;
};

}
#endif // HASH_TABLE_H
