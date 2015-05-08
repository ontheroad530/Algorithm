#include "stack.h"

namespace GYH
{

Stack_As_Array::Stack_As_Array(unsigned int size)
    :_array(size)
{

}

Stack_As_Array::~Stack_As_Array()
{
    purge();
}

void Stack_As_Array::purge()
{
    if( is_owner() )
    {
        for(unsigned int i = 0; i < _count; ++i)
            delete _array[i];
    }

    _count = 0;
}

void Stack_As_Array::accept(Visitor &visitor) const
{
    for( unsigned int i = 0;
         i < _count && !visitor.is_done(); ++i)
    {
        visitor.visit( *_array[i] );
    }
}

Object &Stack_As_Array::top() const
{
    if( 0 == _count)
        throw std::domain_error("stack is empty");

    return *_array[_count - 1U];
}

void Stack_As_Array::push(Object &obj)
{
    if( _count == _array.length() )
    {
        _array.set_length( _array.length() * 2);
//        throw std::domain_error(" stack is full ");
    }

    _array[_count++] = &obj;
}

Object &Stack_As_Array::pop()
{
    if(0 == _count)
        throw std::domain_error(" stack is empty");

    if( _count < _array.length() / 2)
        _array.set_length( _array.length() / 2);

    return *_array[--_count];
}

Iterator &Stack_As_Array::new_iterator() const
{
    return *new Iter( *this );
}

int Stack_As_Array::compare_to(const Object &obj) const
{
    Stack_As_Array const & stack_as_array =
            dynamic_cast<Stack_As_Array const&>(obj);

    return GYH::compare(_count, stack_as_array._count);
}

Stack_As_Array::Iter::Iter(const Stack_As_Array &stack)
    :_stack(stack)
{
    reset();
}

void Stack_As_Array::Iter::reset()
{
    _position = 0;
}

bool Stack_As_Array::Iter::is_done() const
{
    return _position >= _stack._count;
}

Object &Stack_As_Array::Iter::operator *() const
{
    if( _position < _stack._count )
        return *_stack._array[_position];
    else
        return Null_Object::instance();
}

void Stack_As_Array::Iter::operator ++()
{
    if( _position < _stack._count)
        ++_position;
}

Stack_As_Linked_List::Stack_As_Linked_List()
    :_list()
{

}

Stack_As_Linked_List::~Stack_As_Linked_List()
{
    purge();
}

void Stack_As_Linked_List::purge()
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

void Stack_As_Linked_List::push(Object &obj)
{
    _list.prepend( &obj );
    ++_count;
}

Object &Stack_As_Linked_List::pop()
{
    if( _count == 0)
        throw std::domain_error("stack is empty");

    Object& result = *_list.first();
    _list.extract( &result );
    --_count;

    return result;
}

Object &Stack_As_Linked_List::top() const
{
    if( _count == 0)
        throw std::domain_error("stack is empty");

    return *_list.first();
}

void Stack_As_Linked_List::accept(Visitor &visitor) const
{
    List_Element<Object*> const* ptr;

    for(ptr = _list.head();
        ptr != 0 && !visitor.is_done();
        ptr = ptr->next())
    {
        visitor.visit( *ptr->data() );
    }
}

Iterator &Stack_As_Linked_List::new_iterator() const
{
    return * new Iter(*this);
}

int Stack_As_Linked_List::compare_to(const Object &obj) const
{
    Stack_As_Linked_List const & stack_as_list =
            dynamic_cast<Stack_As_Linked_List const&>(obj);

    return GYH::compare(_count, stack_as_list._count);
}

Stack_As_Linked_List::Iter::Iter(const Stack_As_Linked_List &stack)
    :_stack(stack)
{
    reset();
}

void Stack_As_Linked_List::Iter::reset()
{
    _pos = _stack._list.head();
}

bool Stack_As_Linked_List::Iter::is_done() const
{
    return _pos == 0;
}

Object &Stack_As_Linked_List::Iter::operator *() const
{
    if( _pos != 0 )
        return *_pos->data();
    else
        return Null_Object::instance();
}

void Stack_As_Linked_List::Iter::operator ++()
{
    if( _pos != 0)
        _pos = _pos->next();
}


}
