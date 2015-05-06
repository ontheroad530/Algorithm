#ifndef QUEUE_H
#define QUEUE_H

#include "container.h"
#include "array.h"

namespace GYH
{

class Queue : public virtual Container
{
public:
    virtual Object& head() const = 0;
    virtual void enqueue(Object&) = 0;
    virtual Object& dequeue() = 0;
};

class Queue_As_Array : public virtual Queue
{
public:
    Queue_As_Array(unsigned int);
    ~Queue_As_Array();

    void purge();
    void accept(Visitor &) const;

    Object& head() const;
    void enqueue(Object &);
    Object& dequeue();

protected:
    int compare_to(const Object &) const;

protected:
    unsigned int    _head;
    unsigned int    _tail;
    Array<Object*>  _array;
};

class Deque : public virtual Queue
{
public:
    virtual Object& head() const = 0;
    virtual Object& tail() const = 0;
    virtual void enqueue(Object &);
    virtual void enqueue_head(Object& ) = 0;
    virtual void enqueue_tail(Object& ) = 0;
    virtual Object& dequeue();
    virtual Object& dequeue_head() = 0;
    virtual Object& dequeue_tail() = 0;
};

class Deque_As_Array : public Deque, public Queue_As_Array
{
public:
    Deque_As_Array(unsigned int);

    virtual Object& head() const;
    virtual Object& tail() const;
    virtual void enqueue_head(Object& );
    virtual void enqueue_tail(Object& );
    virtual Object& dequeue_head();
    virtual Object& dequeue_tail();

    virtual void enqueue(Object &);
    virtual Object& dequeue();
};

}
#endif // QUEUE_H
