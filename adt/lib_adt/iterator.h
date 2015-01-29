#ifndef ITERATOR_H
#define ITERATOR_H

#include "object.h"

namespace GYH
{


class Iterator
{
public:
    virtual ~Iterator();
    virtual void reset() = 0;
    virtual bool is_done() const = 0;
    virtual Object& operator * () const = 0;
    virtual void operator ++ () = 0;
};


class Null_Iterator: public Iterator
{
public:
    Null_Iterator();
    void reset();
    bool is_done() const;
    Object& operator *() const;
    void operator ++();
};


}
#endif // ITERATOR_H
