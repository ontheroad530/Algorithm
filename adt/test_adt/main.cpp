#include "test_array.h"
#include "test_list.h"
#include "test_stack.h"
#include "test_queue.h"
#include "test_hash_table.h"
#include "test_tree.h"

int main()
{
    test_array();
    test_linked_list();
    test_list();
    test_stack();
    test_queue();
    test_hash_table();
    test_tree();

    return 0;
}

