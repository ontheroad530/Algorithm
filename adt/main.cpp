#include <iostream>

#include "array.h"
#include "linked_list.h"


void test_array();
void test_linked_list();

int main()
{
    test_array();
    test_linked_list();
}


void test_array()
{
    std::cout << "****test array start********" << std::endl;
    Array<int> a(3);
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;

    std::cout << "a: " << std::endl;
    for(unsigned int i = 0; i < a.size(); ++i)
        std::cout << a[i] << " ";
    std::cout << std::endl;


    Array<int> b(a);

    std::cout << "b: " << std::endl;
    for(unsigned int i = 0; i < b.size(); ++i)
        std::cout << b[i] << " ";
    std::cout << std::endl;


    Array<int> c = a;

    std::cout << "c: " << std::endl;
    for(unsigned int i = 0; i < c.size(); ++i)
        std::cout << c[i] << " ";
    std::cout << std::endl;

    std::cout << "****test array end********" << std::endl;

}

void test_linked_list()
{
    std::cout << "****test linked_list start********" << std::endl;

    Linked_List<int> list;
    list.append(1);
    list.prepend(2);
    list.purge();

    list.append(4);
    list.prepend(3);
    list.append(5);

    list.extract(3);

    list.insert_after(list.tail(), 8);

    list.insert_after(list.head(), 7);

    list.insert_before(list.head(), 6);

    Linked_List<int> list2(list);
    Linked_List<int> list3 = list;

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
