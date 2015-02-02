#include "association.h"

namespace GYH
{


Association::Association(Object &key)
    :_key( &key )
    ,_value( NULL )
{
}

Association::Association(Object &key, Object &value)
    :_key( &key )
    ,_value( &value)
{

}

Association::~Association()
{
    if( is_onwer() )
    {
        if( _key )
            delete _key;
        if( _value )
            delete _value;
    }
}

Object &Association::key() const
{
    if( _key )
        return *_key;
    else
        return Null_Object::instance();
}

Object &Association::value() const
{
    if( _value )
        return *_value;
    else
        return Null_Object::instance();
}

Hash_Value Association::hash() const
{
    return Hash_Value();
}

void Association::put(std::ostream &os) const
{
    os << "Association { ";
    if( _key )
        os << *_key;
    if( _value )
        os << ", "  << *_value;
    os << "}";
}

int Association::compare_to(const Object &obj) const
{
    Association const& association =
            dynamic_cast<Association const&>(obj);

    return key().compare(association.key());
}


}
