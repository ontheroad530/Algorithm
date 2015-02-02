#include <iostream>

#include "test_queue.h"
#include "queue.h"

using namespace GYH;

void test_queue()
{
    std::cout << "****test queue start********" << std::endl;

    Queue_As_Array queue(4);

    queue.enqueue(* new Int(1));
    queue.enqueue(* new Int(2));
    queue.enqueue(* new Int(3));

    std::cout << queue.dequeue() << std::endl;

    Deque_As_Array deque(4);
    deque.enqueue_tail( * new Int(1) );
    deque.enqueue_head( * new Int(2) );
    deque.enqueue_tail( * new Int(3) );
    deque.enqueue_head( * new Int(4) );

    std::cout << deque.dequeue_head() << std::endl;
    std::cout << deque.dequeue_tail() << std::endl;

    std::cout << "****test queue end********" << std::endl;

}
