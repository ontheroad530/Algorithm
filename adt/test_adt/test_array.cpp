#include <iostream>

#include "test_array.h"
#include "array.h"
#include "object.h"

using namespace GYH;


void test_array()
{
    std::cout << "****test array start********" << std::endl;
    Array<Int> a(3);
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;

    std::cout << "a: " << std::endl;
    for(unsigned int i = 0; i < a.size(); ++i)
        std::cout << a[i] << " ";
    std::cout << std::endl;


    Array<Int> b(a);

    std::cout << "b: " << std::endl;
    for(unsigned int i = 0; i < b.size(); ++i)
        std::cout << b[i] << " ";
    std::cout << std::endl;


    Array<Int> c = a;
    c.set_length(4);
    c[3] = 4;

    std::cout << "c: " << std::endl;
    for(unsigned int i = 0; i < c.size(); ++i)
        std::cout << c[i] << " ";
    std::cout << std::endl;

    Array_2D<Int> arrary_2d(3, 3);
    for(int i =0; i < 3; ++i)
        for(int j = 0; j < 3; ++j)
            arrary_2d[i][j] = i + j;

    for(int i =0; i < 3; ++i)
        for(int j = 0; j < 3; ++j)
            std::cout << arrary_2d[i][j] << " ";
    std::cout << std::endl;

    std::cout << "****test array end********" << std::endl;

}
