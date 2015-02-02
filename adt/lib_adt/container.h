#ifndef CONTAINER_H
#define CONTAINER_H

#include "object.h"
#include "ownership.h"
#include "iterator.h"
#include "visitor.h"

namespace GYH
{

class Container: public virtual Object, public virtual Ownership
{
public:
    virtual unsigned int count() const;
    virtual bool is_empty() const;
    virtual bool is_full() const;
    virtual Hash_Value hash() const;
    virtual void put(std::ostream &) const;
    virtual Iterator& new_iterator() const;

    virtual void purge() = 0;
    virtual void accept(Visitor&) const = 0;


protected:
    Container();
    unsigned int    _count;
};

class Searchable_Container: public virtual Container
{
public:
    virtual bool is_member(Object const&) const = 0;
    virtual void insert(Object&) = 0;
    virtual void withdraw(Object&) = 0;
    virtual Object& find(Object const&) const = 0;
};

}
#endif // CONTAINER_H
