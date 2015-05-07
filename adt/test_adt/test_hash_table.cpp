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

    Chained_Scatter_Table chained_scatter_table(5);
    chained_scatter_table.insert( *new Double(1.1));
    chained_scatter_table.insert( *new Double(2.1));
    chained_scatter_table.insert( *new Double(3.1));
    chained_scatter_table.insert( *new Double(4.1));
    chained_scatter_table.insert( *new Double(5.1));

    std::stringstream ss_s;
    Putting_Visitor visit(ss_s);
    chained_scatter_table.accept(visit);
    std::cout << ss_s.str() << std::endl;

    std::cout << "****test Chained_Hash_Table end********" << std::endl;
}
