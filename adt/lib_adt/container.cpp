#include <typeinfo>

#include "container.h"
#include "visitor.h"
#include "iterator.h"

namespace GYH
{

unsigned int Container::count() const
{
    return _count;
}

bool Container::is_empty() const
{
    return count() == 0;
}

bool Container::is_full() const
{
    return false;
}

Hash_Value Container::hash() const
{
    return _count;
}

void Container::put(std::ostream &os) const
{
    Putting_Visitor visitor(os);

    os << typeid(*this).name() << " {";
    accept(visitor);
    os << "}";
}

Iterator &Container::new_iterator() const
{
    return *new Null_Iterator();
}

Container::Container()
    :_count(0)
{
}



}
