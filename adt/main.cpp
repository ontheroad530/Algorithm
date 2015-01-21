#include <iostream>

#include "array.h"
#include "linked_list.h"
#include "object.h"

using namespace GYH;

void test_array();
void test_linked_list();

int main()
{
    Int a = 3;
    Int b = 2;
    Int c = a + b;

    std::cout << c << std::endl;
//    test_array();
//    test_linked_list();
}


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

void test_linked_list()
{
    std::cout << "****test linked_list start********" << std::endl;

    Linked_List<Double> list;
    list.append(1.1);
    list.prepend(2.0);
    list.purge();

    list.append(4.1);
    list.prepend(3.2);
    list.append(5.4);

    list.extract(3.2);

    list.insert_after(list.tail(), 8.7);

    list.insert_after(list.head(), 7.6);

    list.insert_before(list.head(), 6.5);

    Linked_List<Double> list2(list);
    Linked_List<Double> list3 = list;

    if( !list.empty() )
    {
        std::cout << "list: " << list.size() << std::endl;
        std::cout << list.first() << std::endl;
        std::cout << list.last() << std::endl;
    }

    if( !list2.empty() )
    {
        std::cout << "list2: " << list.size() << std::endl;
        std::cout << list2.first() << std::endl;
        std::cout << list2.last() << std::endl;
    }

    if( !list3.empty() )
    {
        std::cout << "list3: " << list.size() << std::endl;
        std::cout << list3.first() << std::endl;
        std::cout << list3.last() << std::endl;
    }

    std::cout << "****test linked_list end********" << std::endl;
}

