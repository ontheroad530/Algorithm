#include "test_priority.h"
#include "priority_queue.h"

#include <iostream>

using namespace GYH;

void test_binary_heap()
{
    std::cout << "****test binary heap start********" << std::endl;

    Binary_Heap binary_heap(10);
    binary_heap.enqueue(* new Int(3));
    binary_heap.enqueue(* new Int(7));
    binary_heap.enqueue(* new Int(2));
    binary_heap.enqueue(* new Int(5));
    binary_heap.enqueue(* new Int(9));
    binary_heap.enqueue(* new Int(1));

    Object& min = binary_heap.find_min();
    std::cout << min << std::endl;

    binary_heap.dequeue_min();
    binary_heap.dequeue_min();

    Object& min2 = binary_heap.find_min();
    std::cout << min2 << std::endl;

    binary_heap.enqueue(* new Int(2));

    Object& min3 = binary_heap.find_min();
    std::cout << min3 << std::endl;

    std::cout << "****test binary heap end********" << std::endl;
}
