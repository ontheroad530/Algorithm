#include "queue.h"

namespace GYH
{

Queue_As_Array::Queue_As_Array(unsigned int size)
    :_head(0)
    ,_tail( size - 1U )
    ,_array(size)
{

}

Queue_As_Array::~Queue_As_Array()
{
    purge();
}

void Queue_As_Array::purge()
{
       if( is_owner() )
       {
           for(unsigned int i = 0; i < _count; ++i)
           {
               delete _array[_head];
               if( ++_head == _array.length() )
                   _head = 0;
           }
       }

       _count = 0;
}

void Queue_As_Array::accept(Visitor &visitor) const
{
    for( unsigned i = _head; i != _tail; ++i)
    {
        if(i == _array.length() )
            i = 0;

        if( !visitor.is_done() )
            visitor.visit( *_array[i] );
    }
}

Object &Queue_As_Array::head() const
{
    if( 0 == _count)
        throw std::domain_error("queue is empty");

    return *_array[_head];
}

void Queue_As_Array::enqueue(Object &obj)
{
    if( _count == _array.length() )
        throw std::domain_error("queue is full");
    if( ++_tail == _array.length() )
        _tail = 0;

    _array[_tail] = &obj;
    ++_count;
}

Object &Queue_As_Array::dequeue()
{
    if( 0 == _count)
        throw std::domain_error("queue is empty");

    Object& result = *_array[_head];
    if( ++_head == _array.length() )
        _head = 0;
    --_count;

    return result;
}

int Queue_As_Array::compare_to(const Object &obj) const
{
    Queue_As_Array const & queue_as_array =
            dynamic_cast<Queue_As_Array const&>(obj);

    return GYH::compare( _count, queue_as_array._count);
}

void Deque::enqueue(Object &obj)
{
    enqueue_tail(obj);
}

Object &Deque::dequeue()
{
    return dequeue_head();
}

Deque_As_Array::Deque_As_Array(unsigned int size)
    :Queue_As_Array(size)
{

}

Object &Deque_As_Array::head() const
{
    return Queue_As_Array::head();
}

Object &Deque_As_Array::tail() const
{
    if( 0 == _count )
        throw std::domain_error("deque is empty");

    return *_array[_tail];
}

void Deque_As_Array::enqueue_head(Object &obj)
{
    if( _count == _array.length() )
        throw std::domain_error("deque is full");

    if(0 == _head)
        _head = _array.length() - 1U;

    _array[_head] = &obj;
    ++_count;
}

void Deque_As_Array::enqueue_tail(Object &obj)
{
    Queue_As_Array::enqueue(obj);
}

Object &Deque_As_Array::dequeue_head()
{
    return Queue_As_Array::dequeue();
}

Object &Deque_As_Array::dequeue_tail()
{
    if(0 == _count)
        throw std::domain_error("deque is empty");

    Object& result = *_array[_tail];
    if(0 == _tail)
        _tail = _array.length() - 1U;

    --_count;

    return result;
}

void Deque_As_Array::enqueue(Object &obj)
{
    Deque::enqueue(obj);
}

Object &Deque_As_Array::dequeue()
{
    return Deque::dequeue();
}

Queue_As_Linked_list::Queue_As_Linked_list()
    :_list()
{

}

Queue_As_Linked_list::~Queue_As_Linked_list()
{
    purge();
}

void Queue_As_Linked_list::purge()
{
       if( is_owner() )
       {
           List_Element<Object*> const * ptr;
           for(ptr = _list.head(); ptr != 0; ptr = ptr->next() )
               delete ptr->data();
       }

       _list.purge();
       _count = 0;
}

void Queue_As_Linked_list::accept(Visitor &visitor) const
{
    List_Element<Object*> const * ptr;
    for(ptr = _list.head(); ptr != 0; ptr = ptr->next())
    {
        if( !visitor.is_done() )
            visitor.visit( *ptr->data() );
    }
}

Object &Queue_As_Linked_list::head() const
{
    if(_count == 0)
        throw std::domain_error("queue is empty");

    return *_list.first();
}

void Queue_As_Linked_list::enqueue(Object &obj)
{
    _list.append(&obj);
    ++_count;
}

Object &Queue_As_Linked_list::dequeue()
{
    if(_count == 0)
        throw std::domain_error("queue is empty");

    Object& result = *_list.first();
    _list.extract(&result);
    --_count;

    return result;
}

int Queue_As_Linked_list::compare_to(const Object &obj) const
{
    Queue_As_Linked_list const & queue_as_linked_list =
            dynamic_cast<Queue_As_Linked_list const&>(obj);

    return GYH::compare( _count, queue_as_linked_list._count);
}

}
