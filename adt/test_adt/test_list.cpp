#include <iostream>

#include "test_list.h"
#include "linked_list.h"
#include "object.h"

using namespace GYH;

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
