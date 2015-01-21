#include <typeinfo>
#include <cstring>

#include "object.h"

namespace GYH
{

bool operator == (Object const& left, Object const& right)
{ return left.compare(right) == 0; }

bool operator != (Object const& left, Object const& right)
{ return left.compare(right) != 0; }

bool operator <= (Object const& left, Object const& right)
{ return left.compare(right) <= 0; }

bool operator < (Object const& left, Object const& right)
{ return left.compare(right) < 0; }

bool operator >= (Object const& left, Object const& right)
{ return left.compare(right) >= 0; }

bool operator > (Object const& left, Object const& right)
{ return left.compare(right) > 0; }

std::ostream& operator << (std::ostream& os, Object const& obj)
{
    obj.put(os);
    return os;
}

Object::~Object()
{

}

bool Object::is_null() const
{
    return false;
}

int Object::compare(const Object &obj) const
{
    if(typeid(*this) == typeid(obj))
        return compare_to(obj);
    else if( typeid(*this).before(typeid(obj)) )
        return -1;
    else
        return 1;
}

inline bool Null_Object::is_null() const
{
    return true;
}

inline Hash_Value Null_Object::hash() const
{
    return 0;
}

void Null_Object::put(std::ostream &os) const
{
    os << "Null_Object";
}

Null_Object &Null_Object::instance()
{
    static Null_Object null;
    return null;
}

inline int Null_Object::compare_to(const Object &) const
{
    return 0;
}

Null_Object::Null_Object()
{

}

int compare(int l, int r)
{
    if(l == r)
        return 0;
    return l > r ? 1 : -1;
}

int compare(unsigned int l, unsigned int r)
{
    if(l == r)
        return 0;
    return l > r ? 1 : -1;
}

int compare(double l, double r)
{
    if(l == r)
        return 0;
    return l > r ? 1 : -1;
}

int compare(char l, char r)
{
    if(l == r)
        return 0;
    return l > r ? 1 : -1;
}

int compare(const std::string &l, const std::string &r)
{
    return strcmp(l.c_str(), r.c_str());
}

}



