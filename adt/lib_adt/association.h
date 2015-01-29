#ifndef ASSOCIATION_H
#define ASSOCIATION_H

#include "object.h"
#include "ownership.h"

namespace GYH
{


class Association: public Object, public Ownership
{
public:
    Association(Object&);
    Association(Object&, Object&);
    ~Association();

    Object& key() const;
    Object& value() const;

    Hash_Value hash() const;
    void put(std::ostream &) const;

protected:
    int compare_to(const Object &) const;

    Object*     _key;
    Object*     _value;
};

}

#endif // ASSOCIATION_H
