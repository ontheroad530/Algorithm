#include <iostream>
#include <sstream>

#include "test_hash_table.h"
#include "hash_table.h"

using namespace GYH;

void test_hash_table()
{
    std::cout << "****test Chained_Hash_Table start********" << std::endl;

    Chained_Hash_Table chained_hash_table(5);

    chained_hash_table.insert(* new Int(1));
    chained_hash_table.insert(* new Int(2));
    chained_hash_table.insert(* new Int(3));
    chained_hash_table.insert(* new Int(4));

    chained_hash_table.withdraw(* new Int(1) );

    std::cout << chained_hash_table.find(* new Int(2) ) << std::endl;

    std::stringstream ss;
    Putting_Visitor visitor(ss);
    chained_hash_table.accept(visitor);
    std::cout << ss.str() << std::endl;

    Iterator& iter = chained_hash_table.new_iterator();

    while( !iter.is_done() )
    {
        std::cout << *iter << std::endl;
        ++iter;
    }

    std::cout << "****test Chained_Hash_Table end********" << std::endl;
}
