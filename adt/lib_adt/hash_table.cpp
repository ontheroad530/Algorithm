#include <stdexcept>

#include "hash_table.h"
#include "visitor.h"

GYH::Hash_Table::Hash_Table(unsigned int len)
    :_length(len)
{
}

unsigned int GYH::Hash_Table::h(const GYH::Object &obj) const
{
    return obj.hash() % _length;
}


GYH::Chained_Hash_Table::Chained_Hash_Table(unsigned int len)
    :Hash_Table(len)
    ,_array(len)
{

}

GYH::Chained_Hash_Table::~Chained_Hash_Table()
{
    purge();
}

void GYH::Chained_Hash_Table::purge()
{
    for(unsigned int i = 0; i < _length; ++i)
    {
        if( is_onwer() )
        {
            List_Element<Object*> const *ptr;

            for(ptr = _array[i].head();
                ptr != 0; ptr = ptr->next() )
            {
                delete ptr->data();
            }
        }

        _array[i].purge();
    }

    _count = 0;
}

void GYH::Chained_Hash_Table::insert(GYH::Object &object)
{
    _array[ h(object) ].append(&object);
    ++_count;
}

void GYH::Chained_Hash_Table::withdraw(GYH::Object &object)
{
    _array[ h(object) ].extract(&object);
    --_count;
}

GYH::Object &GYH::Chained_Hash_Table::find(const GYH::Object &object) const
{
    List_Element<Object*> const* ptr;

    for(ptr = _array[ h(object) ].head();
        ptr != 0; ptr = ptr->next() )
    {
        if(object == *ptr->data())
        {
            return *ptr->data();
        }
    }

    return Null_Object::instance();
}

bool GYH::Chained_Hash_Table::is_member(const GYH::Object &object) const
{
    if( find(object) != Null_Object::instance())
        return true;

    return false;
}

void GYH::Chained_Hash_Table::accept(GYH::Visitor &visitor) const
{
    for(unsigned int i = 0; i < _array.length(); ++i)
    {
        List_Element<Object*>const *ptr = NULL;
        for(ptr = _array[i].head(); ptr != NULL; ptr = ptr->next())
        {
            visitor.visit( *ptr->data() );
        }
    }
}

GYH::Iterator &GYH::Chained_Hash_Table::new_iterator() const
{
    return *new Iter(_array);
}

int GYH::Chained_Hash_Table::compare_to(const GYH::Object &object) const
{
    Chained_Hash_Table const& hash_table = dynamic_cast<Chained_Hash_Table const&>(object);
    return GYH::compare(_count, hash_table._count);
}


GYH::Chained_Hash_Table::Iter::Iter(const Array<Linked_List<GYH::Object *> > &array)
    :_array( array )
    ,_queue(* new Queue_As_Array(array.length() ))
    ,_pos(0)
{
    _queue.rescind_ownership();
    reset();
}

void GYH::Chained_Hash_Table::Iter::reset()
{
    _queue.purge();
    for(_pos = 0; _pos < _array.length() && _queue.is_empty(); ++_pos)
    {
        List_Element<Object*>const *ptr = NULL;
        for(ptr = _array[_pos].head();
            ptr != NULL; ptr = ptr->next())
        {
            _queue.enqueue( *ptr->data() );
        }
    }
}

bool GYH::Chained_Hash_Table::Iter::is_done() const
{
    return _queue.is_empty();
}

GYH::Object &GYH::Chained_Hash_Table::Iter::operator *() const
{
    if( !_queue.is_empty() )
        return _queue.head();

    return Null_Object::instance();
}

void GYH::Chained_Hash_Table::Iter::operator ++()
{
    if( !_queue.is_empty() )
        _queue.dequeue();

    if( _queue.is_empty() )
    {
        for(; _pos < _array.length();)
        {
            Linked_List<Object*> const& link_list = _array[_pos];
            List_Element<Object*>const * ptr;
            for(ptr = link_list.head(); ptr != NULL; ptr = ptr->next())
            {
                _queue.enqueue( *ptr->data() );
            }

            ++_pos;
            if( !_queue.is_empty() )
                break;
        }
    }
}


GYH::Chained_Scatter_Table::Entry::Entry()
    :_object(NULL)
    ,_next(NULL_PTR)
{

}


GYH::Chained_Scatter_Table::Chained_Scatter_Table(unsigned int len)
    :Hash_Table(len)
    ,_array(len)
{

}

GYH::Chained_Scatter_Table::~Chained_Scatter_Table()
{
    purge();
}

void GYH::Chained_Scatter_Table::purge()
{
    for(unsigned int i =0; i < _length; ++i)
    {
        if(_array[i]._object != NULL)
        {
            if( is_onwer() )
                delete _array[i]._object;

            _array[i] = Entry();
        }
    }

    _count = 0;
}

void GYH::Chained_Scatter_Table::insert(GYH::Object &obj)
{
    if(_count == _length)
        throw std::domain_error("scatter table is full");

    unsigned int probe = h(obj);

    if( _array[probe]._object != NULL )
    {
        while( _array[probe]._next != Entry::NULL_PTR )
            probe = _array[probe]._next;

        unsigned int const tail = probe;
        probe = (probe + 1) % _length;
        while( _array[probe]._object )
            probe = (probe + 1) % _length;
        _array[tail]._next = probe;
    }

    _array[probe]._object = &obj;
    _array[probe]._next = Entry::NULL_PTR;
    ++_count;
}

GYH::Object &GYH::Chained_Scatter_Table::find(const GYH::Object &obj) const
{
    for(unsigned int probe = h(obj);
        probe != Entry::NULL_PTR; probe = _array[probe]._next)
    {
        if(obj == *_array[probe]._object )
            return *_array[probe]._object;
    }

    return Null_Object::instance();
}

void GYH::Chained_Scatter_Table::withdraw(GYH::Object &object)
{
    if(0 == _count)
        throw std::domain_error("scatter table is empty");

    unsigned int i = h(object);
    while (i != Entry::NULL_PTR && _array[i]._object != &object) {
        i = _array[i]._next;
    }

    if( Entry::NULL_PTR == i)
        throw std::invalid_argument("object not found");

    while(1)
    {
        unsigned int j;
        for(j = _array[i]._next;
            j != Entry::NULL_PTR; j = _array[j]._next)
        {
            unsigned int const hv = h( *_array[j]._object );
            bool contained = false;

            for(unsigned int k = _array[i]._next;
                k != _array[j]._next && !contained;
                k = _array[k]._next)
            {
                if(k == hv)
                    contained = true;
            }

            if( !contained )
                break;
        }

        if(j == Entry::NULL_PTR)
            break;

        _array[i]._object = _array[j]._object;
        i = j;
    }

    _array[i]._object = NULL;
    _array[i]._next = Entry::NULL_PTR;

    for(unsigned int j = (i + _length - 1U) % _length;
        j != i; j = (j + _length - 1U) % _length)
    {
        if( _array[j]._next == i)
        {
            _array[j]._next = Entry::NULL_PTR;
            break;
        }
    }

    --_count;
}

bool GYH::Chained_Scatter_Table::is_member(const GYH::Object &obj) const
{
    if( find(obj) != Null_Object::instance())
        return true;

    return false;
}

void GYH::Chained_Scatter_Table::accept(GYH::Visitor &visitor) const
{
    for(unsigned int i = 0; i < _array.length(); ++i)
    {
        visitor.visit(*_array[i]._object);
    }
}

GYH::Iterator &GYH::Chained_Scatter_Table::new_iterator() const
{
    return * new Null_Iterator();
}

int GYH::Chained_Scatter_Table::compare_to(const GYH::Object &obj) const
{
    Chained_Scatter_Table const& hash_table = dynamic_cast<Chained_Scatter_Table const&>(obj);
    return GYH::compare(_count, hash_table._count);
}
