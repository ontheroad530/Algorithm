#include "priority_queue.h"

GYH::Priority_Queue::Priority_Queue()
{
}


GYH::Binary_Heap::Binary_Heap(unsigned int len)
    :_array(len, 1)
{

}

GYH::Binary_Heap::~Binary_Heap()
{
    purge();
}

void GYH::Binary_Heap::enqueue(GYH::Object &obj)
{
    if(_count == _array.length() )
        throw std::domain_error("priority queue is full");

    ++_count;
    unsigned int i = _count;
    while( i > 1 && *_array[i / 2] > obj )
    {
        _array[i] = _array[i / 2];
        i /= 2;
    }
    _array[i] = &obj;
}

GYH::Object &GYH::Binary_Heap::find_min() const
{
    if(0 == _count)
        throw std::domain_error("priority queue is empty");

    return *_array[1];
}

GYH::Object &GYH::Binary_Heap::dequeue_min()
{
    if(0 == _count)
        throw std::domain_error("priority queue is empty");

    Object& result = *_array[1];
    Object& last = *_array[_count];
    --_count;

    unsigned int i = 1;
    while(2 * i < _count + 1)
    {
        unsigned int child =  2 * i;
        if( child + 1 < _count + 1
                && *_array[child + 1] < *_array[child])
            ++child;

        if(last <= *_array[child] )
            break;

        _array[i] = _array[child];
        i = child;
    }

    _array[i] = &last;
    return result;
}

void GYH::Binary_Heap::purge()
{
    if( is_owner() )
    {
        for(unsigned int i = 1; i < _count + 1; ++i)
        {
            delete _array[i];
        }
        _count = 0;
    }
}

void GYH::Binary_Heap::accept(GYH::Visitor &) const
{

}

int GYH::Binary_Heap::compare_to(const GYH::Object &obj) const
{
    const Binary_Heap& other = dynamic_cast<const Binary_Heap&>(obj);
    return GYH::compare(_count, other._count);
}
