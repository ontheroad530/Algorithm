#include <iostream>

#include "test_stack.h"
#include "stack.h"

using namespace GYH;

void test_stack()
{
    std::cout << "****test stack start********" << std::endl;

    Stack_As_Array stack(3);
    stack.push(* new Int(1));
    stack.push(* new Int(2));
    stack.push(* new Int(3));
    stack.push(* new Int(4));
    stack.push(* new Int(5));

    Iterator& iter = stack.new_iterator();
    while( !iter.is_done() )
    {
        std::cout << *iter << "  ";
        ++iter;
    }
    delete &iter;
    std::cout << std::endl;

    Object& tmp = stack.top();
    Object& tmp2 = stack.pop();
    Object& tmp3 = stack.pop();

    std::cout << tmp << "  " << tmp2 << "  " << tmp3 << std::endl;

    std::cout << "****test stack end********" << std::endl;

}
