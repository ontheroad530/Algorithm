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

Pre_Order::Pre_Order(Visitor &v)
    :_visitor(v)
{

}

void Pre_Order::pre_visit(Object &obj)
{
    _visitor.visit(obj);
}

In_Order::In_Order(Visitor &v)
    :_visitor(v)
{

}

void In_Order::visit(Object &obj)
{
    _visitor.visit(obj);
}

Post_Order::Post_Order(Visitor &v)
    :_visitor(v)
{

}

void Post_Order::post_visit(Object &obj)
{
    _visitor.visit(obj);
}

}
