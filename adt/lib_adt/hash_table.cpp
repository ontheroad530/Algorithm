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
    for(int i = 0; i < (int)_array.length(); ++i)
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
    for(_pos = 0; _pos < (int)_array.length() && _queue.is_empty(); ++_pos)
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
        for(; _pos < (int)_array.length();)
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
