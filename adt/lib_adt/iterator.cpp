#include "iterator.h"

namespace GYH
{

Iterator::~Iterator()
{

}

Null_Iterator::Null_Iterator()
{
}

void Null_Iterator::reset()
{
}

bool Null_Iterator::is_done() const
{
    return true;
}

Object &Null_Iterator::operator *() const
{
    return Null_Object::instance();
}

void Null_Iterator::operator ++()
{

}


}
