#include "list.h"


namespace GYH
{

List_As_Linked_List::List_As_Linked_List()
    :_linked_list()
{

}

bool List_As_Linked_List::is_member(const Object &obj) const
{
    List_Element<Object*> const* ptr;
    for(ptr = _linked_list.head(); ptr; ptr = ptr->next())
    {
        if( &obj == ptr->data() )
            return true;
    }

    return false;
}

void List_As_Linked_List::insert(Object &obj)
{
    _linked_list.append(&obj);
    ++_count;
}

void List_As_Linked_List::withdraw(Object &obj)
{
    if(0 == _count)
        throw std::domain_error("list is empty");

    _linked_list.extract(&obj);
    --_count;
}

Object &List_As_Linked_List::find(const Object &obj) const
{
    List_Element<Object*> const* ptr;

    for(ptr = _linked_list.head(); ptr; ptr = ptr->next())
    {
        if( obj == *ptr->data() )
            return *ptr->data();
    }

    return Null_Object::instance();
}

Object &List_As_Linked_List::operator [](unsigned int offset) const
{
    if( offset >= _count)
        throw std::domain_error("invalid offset");

    unsigned int i = 0;
    List_Element<Object*> const* ptr = _linked_list.head();

    while( i < offset && ptr)
    {
        ptr = ptr->next();
        ++i;
    }

    if( 0 == ptr)
        throw std::domain_error("should never happen");

    return *ptr->data();
}

Object &List_As_Linked_List::operator [](const Position &pos) const
{
    Pos const& position = dynamic_cast<Pos const&>(pos);

    if( &position._list != this || position._element == NULL)
        throw std::invalid_argument("invalid position");

    return *position._element->data();
}

Position &List_As_Linked_List::find_position(const Object &obj) const
{
    List_Element<Object*> const * ptr =
            _linked_list.head();

    while(ptr && *ptr->data() != obj)
        ptr = ptr->next();

    return *new Pos(*this, ptr);
}

void List_As_Linked_List::withdraw(const Position &pos)
{
    Pos const& position = dynamic_cast<Pos const&>(pos);

    if(_count == 0)
        throw std::domain_error("list is empty");

    if( &position._list != this || position._element == NULL)
        throw std::invalid_argument("invalid position");

    _linked_list.extract(position._element->data());
}

void List_As_Linked_List::inser_after(const Position &pos, Object &obj)
{
    Pos const& position = dynamic_cast<Pos const&>(pos);
    if( &position._list != this || position._element == NULL)
        throw std::invalid_argument("invalid position");

    _linked_list.insert_after(position._element, &obj);
    ++_count;
}

void List_As_Linked_List::inser_before(const Position &pos, Object &obj)
{
    Pos const& position = dynamic_cast<Pos const&>(pos);
    if( &position._list != this || position._element == NULL)
        throw std::invalid_argument("invalid position");

    _linked_list.insert_before(position._element, &obj);
    ++_count;
}

void List_As_Linked_List::purge()
{
    List_Element<Object*>const * element;
    if( is_onwer() )
    {
        for( element = _linked_list.head(); element; element = element->next() )
        {
            if( element->data() )
                delete element->data();
        }
    }
}

void List_As_Linked_List::accept(Visitor &visitor) const
{
    List_Element<Object*>const * element = _linked_list.head();
    while( element && !visitor.is_done() )
    {
        element  = element->next();
        visitor.visit( *element->data() );
    }
}

int List_As_Linked_List::compare_to(const Object &obj) const
{
    List_As_Linked_List const & list_as_linked_list
            = dynamic_cast<List_As_Linked_List const &>(obj);

    return GYH::compare(this->_linked_list.size(), list_as_linked_list._linked_list.size());
}

List_As_Linked_List::Pos::Pos(const List_As_Linked_List &list,
                              const List_Element<Object *> * element)
    :_list(list)
    ,_element(element)
{

}

void List_As_Linked_List::Pos::reset()
{
    _element = _list._linked_list.head();
}

bool List_As_Linked_List::Pos::is_done() const
{
    return _element == NULL;
}

Object &List_As_Linked_List::Pos::operator *() const
{
    if(_element)
        return *_element->data();
    else
        return Null_Object::instance();
}

void List_As_Linked_List::Pos::operator ++()
{
    if(_element)
        _element = _element->next();
}


}
