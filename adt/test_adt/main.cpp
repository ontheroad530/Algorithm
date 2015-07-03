#include "test_array.h"
#include "test_list.h"
#include "test_stack.h"
#include "test_queue.h"
#include "test_hash_table.h"
#include "test_tree.h"
#include "test_priority.h"

int main()
{
#if 0
    test_array();
    test_linked_list();
    test_list();
    test_stack();
    test_queue();
    test_hash_table();
    test_tree();
#endif

    test_binary_heap();

    return 0;
}

