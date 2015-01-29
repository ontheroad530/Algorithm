#include "visitor.h"

namespace GYH
{

Putting_Visitor::Putting_Visitor(std::ostream &os)
    :_stream(os)
    ,_comma(false)
{

}

void Putting_Visitor::visit(Object &obj)
{
    if(_comma)
        _stream << ", ";

    _stream << obj;
    _comma = true;
}

}
