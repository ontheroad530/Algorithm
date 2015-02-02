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

}

#endif // VISITOR_H
