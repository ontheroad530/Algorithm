#ifndef VISITOR_H
#define VISITOR_H

#include <ostream>

#include "object.h"

namespace GYH
{

class Visitor
{
public:
    virtual void visit(Object&) = 0;
    virtual bool is_done() { return false; }
};

class Putting_Visitor: public Visitor
{
public:
    Putting_Visitor(std::ostream& );

    void visit(Object &);

private:
    std::ostream&   _stream;
    bool            _comma;
};

class Pre_Post_Visitor: public Visitor
{
public:
    virtual void pre_visit(Object&){}
    virtual void visit(Object&){}
    virtual void post_visit(Object&){}
};

class Pre_Order: public Pre_Post_Visitor
{
public:
    Pre_Order(Visitor& v);

    void pre_visit(Object& obj);

private:
    Visitor&  _visitor;
};

class In_Order: public Pre_Post_Visitor
{
public:
    In_Order(Visitor& v);

    void visit(Object &obj);

private:
    Visitor&    _visitor;
};

class Post_Order: public Pre_Post_Visitor
{
public:
    Post_Order(Visitor& v);

    void post_visit(Object& obj);

private:
    Visitor&    _visitor;
};

}

#endif // VISITOR_H
