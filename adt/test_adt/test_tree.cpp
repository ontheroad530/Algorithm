#include <iostream>
#include <sstream>

#include "test_tree.h"
#include "tree.h"

using namespace GYH;

void test_tree()
{
    std::cout << "****test tree start********" << std::endl;

    Binary_Tree tree(* new Int(1));
    tree.left().attach_key( * new Int(2) );
    tree.right().attach_key( * new Int(3) );

    tree.left().attach_left( *new Binary_Tree(*new Double(2.1)));
    tree.left().attach_right( *new Binary_Tree( *new Double(2.2)));

    tree.right().attach_left( *new Binary_Tree(* new Double(3.1)));
    tree.right().attach_right( *new Binary_Tree( *new Double(3.2)));

    Iterator& iter = tree.new_iterator();
    while( !iter.is_done() )
    {
        std::cout << *iter << " ";
        ++iter;
    }

    std::cout << std::endl;

    std::stringstream ss;
    std::cout << "pre order: " << std::endl;
    tree.depth_first_traversal(* new Pre_Order(*new Putting_Visitor(ss)));
    std::cout << ss.str() << std::endl;

    std::cout << "in order: " << std::endl;
    ss.str("");
    tree.depth_first_traversal(* new In_Order(*new Putting_Visitor(ss)));
    std::cout << ss.str() << std::endl;

    std::cout << "post order: " << std::endl;
    ss.str("");
    tree.depth_first_traversal(* new Post_Order(*new Putting_Visitor(ss)));
    std::cout << ss.str() << std::endl;

    std::cout << "****test tree end********" << std::endl;

}
