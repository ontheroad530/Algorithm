#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "container.h"
#include "array.h"

namespace GYH
{

class Priority_Queue: public virtual Container
{
public:
    Priority_Queue();

    virtual void enqueue(Object& ) = 0;
    virtual Object& find_min() const = 0;
    virtual Object& dequeue_min() = 0;
};

class Mergeable_Priority_Queue: public virtual Priority_Queue
{
public:
    virtual void merge(Mergeable_Priority_Queue& ) = 0;
};

class Binary_Heap: public Priority_Queue
{
public:
    Binary_Heap(unsigned int);
    ~Binary_Heap();

    virtual void enqueue(Object& );
    virtual Object& find_min() const;
    virtual Object& dequeue_min();

    virtual void purge();
    virtual void accept(Visitor&) const;

protected:
    virtual int compare_to(Object const&) const;

private:
    Array<Object*>  _array;
};

}
#endif // PRIORITY_QUEUE_H
