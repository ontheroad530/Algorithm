#include "tree.h"
#include "queue.h"


void GYH::Tree::depth_first_traversal(GYH::Pre_Post_Visitor &visitor) const
{
    if( visitor.is_done() )
        return;

    if( !is_empty() )
    {
        visitor.pre_visit( key() );
        for(unsigned int i = 0; i < degree(); ++i)
            subtree(i).depth_first_traversal(visitor);
        visitor.post_visit( key() );
    }
}

void GYH::Tree::breadth_first_traversal(GYH::Visitor &visitor) const
{
    Queue_As_Linked_list& queue = *new Queue_As_Linked_list();
    queue.rescind_ownership();

    if( !is_empty() )
        queue.enqueue( const_cast<Tree&>(*this) );

    while( !queue.is_empty() && !visitor.is_done())
    {
        Tree const& head =
                dynamic_cast<Tree const&>( queue.dequeue() );

        visitor.visit( head.key() );
        for(unsigned int i = 0; i < head.degree(); ++i)
        {
            Tree& child = head.subtree(i);
            if( !child.is_empty() )
                queue.enqueue( child );
        }
    }

    delete &queue;
}

void GYH::Tree::accept(GYH::Visitor &visitor) const
{
    depth_first_traversal(* new Pre_Order(visitor) );
}

GYH::Iterator &GYH::Tree::new_iterator() const
{
    return *new Iter(*this);
}


GYH::Tree::Iter::Iter(const GYH::Tree &tree)
    :_tree(tree)
    ,_stack(* new Stack_As_Linked_List())
{
    _stack.rescind_ownership();
    reset();
}

GYH::Tree::Iter::~Iter()
{
    delete &_stack;
}

void GYH::Tree::Iter::reset()
{
    _stack.purge();
    if( !_tree.is_empty() )
        _stack.push( const_cast<Tree&>(_tree) );
}

bool GYH::Tree::Iter::is_done() const
{
    return _stack.is_empty();
}

GYH::Object &GYH::Tree::Iter::operator *() const
{
    if( !_stack.is_empty() )
    {
        Tree const& top =
                dynamic_cast<Tree const&>( _stack.top() );

        return top.key();
    }
    else
        return Null_Object::instance();
}

void GYH::Tree::Iter::operator ++()
{
    if( !_stack.is_empty() )
    {
        Tree const& top =
                dynamic_cast<Tree const&>( _stack.pop() );

        for(int i = top.degree() - 1; i >= 0; --i)
        {
            Tree& subtree = top.subtree(i);
            if( !subtree.is_empty() )
                _stack.push( subtree );
        }
    }
}


GYH::General_Tree::General_Tree(GYH::Object &key)
    :_key( &key )
    ,_degree(0)
    ,_list()
{

}

GYH::General_Tree::~General_Tree()
{
    purge();
}

void GYH::General_Tree::purge()
{
    List_Element<General_Tree*> const* ptr;

    if( is_owner() )
        delete _key;

    for(ptr = _list.head(); ptr != NULL; ptr = ptr->next() )
        delete ptr->data();

    _key = 0;
    _list.purge();
}

GYH::Object &GYH::General_Tree::key() const
{
    return *_key;
}

GYH::General_Tree &GYH::General_Tree::subtree(unsigned int i) const
{
    if(i >= _degree)
        throw std::domain_error("invalid subtree index");

    unsigned int j = 0;
    List_Element<General_Tree*> const * ptr = _list.head();

    while( j<i && ptr!=NULL)
    {
        ++j;
        ptr = ptr->next();
    }

    if(ptr == 0)
        throw std::domain_error("should never happen");

    return *ptr->data();
}

void GYH::General_Tree::attach_subtree(GYH::General_Tree &t)
{
    _list.append( &t );
    ++_degree;
}

GYH::General_Tree &GYH::General_Tree::detach_subtree(GYH::General_Tree &t)
{
    _list.extract( &t );
    --_degree;

    return t;
}


GYH::Binary_Tree::Binary_Tree()
    :_key(NULL)
    ,_left(NULL)
    ,_right(NULL)
{

}

GYH::Binary_Tree::Binary_Tree(GYH::Object &key)
    :_key( &key )
    ,_left( new Binary_Tree())
    ,_right( new Binary_Tree())
{

}

GYH::Binary_Tree::~Binary_Tree()
{
    purge();
}

void GYH::Binary_Tree::purge()
{
    if( !is_empty() )
    {
        if( is_owner() )
            delete _key;

        delete _left;
        delete _right;

        _key = 0;
        _left = 0;
        _right = 0;
    }
}

void GYH::Binary_Tree::depth_first_traversal(GYH::Pre_Post_Visitor &visitor) const
{
    if( visitor.is_done() )
        return;

    if( !is_empty() )
    {
        visitor.pre_visit( *_key );
        _left->depth_first_traversal( visitor );
        visitor.visit( *_key );
        _right->depth_first_traversal( visitor );
        visitor.post_visit( *_key );
    }
}

GYH::Object &GYH::Binary_Tree::key() const
{
    if( is_empty() )
        throw std::domain_error("invalid operation");

    return *_key;
}

void GYH::Binary_Tree::attach_key(GYH::Object & obj)
{
    if( !is_empty() )
        purge();

    _key = &obj;
    _left = new Binary_Tree();
    _right = new Binary_Tree();

}

GYH::Object &GYH::Binary_Tree::detach_key()
{
    Object& obj = *_key;
    purge();

    return obj;
}

GYH::Binary_Tree &GYH::Binary_Tree::left() const
{
    if( is_empty() )
        throw std::domain_error("invalid operation");

    return *_left;
}

GYH::Binary_Tree &GYH::Binary_Tree::right() const
{
    if( is_empty() )
        throw std::domain_error("invalid operation");

    return *_right;
}

void GYH::Binary_Tree::attach_left(GYH::Binary_Tree &t)
{
    if( is_empty() )
        throw std::domain_error("invalid operation");

    delete _left;
    _left = &t;
}

void GYH::Binary_Tree::attach_right(GYH::Binary_Tree &t)
{
    if( is_empty() )
        throw std::domain_error("invalid operation");

    delete _right;
    _right = &t;
}

GYH::Binary_Tree &GYH::Binary_Tree::detach_left()
{
    if( is_empty() )
        throw std::domain_error("invalid operation");

    Binary_Tree& tree = *_left;
    delete _left;
    _left = NULL;

    return tree;
}

GYH::Binary_Tree &GYH::Binary_Tree::detach_right()
{
    if( is_empty() )
        throw std::domain_error("invalid operation");

    Binary_Tree& tree = *_right;
    delete _right;
    _right = NULL;

    return tree;
}

bool GYH::Binary_Tree::is_empty() const
{
    return _key == NULL;
}

unsigned int GYH::Binary_Tree::degree() const
{
    return 2U;
}

bool GYH::Binary_Tree::is_leaf() const
{
    if( is_empty() )
        throw std::domain_error("invalid operation");

    return _left->is_empty() && _right->is_empty();
}

int GYH::Binary_Tree::height() const
{
    if( is_empty() )
        return 0;

    if( is_leaf() )
        return 1;

    int left_h = _left->height();
    int right_h = _right->height();

    return left_h >= right_h ? left_h+1 : right_h+1;
}

GYH::Tree &GYH::Binary_Tree::subtree(unsigned int i) const
{
    if( i >= degree() )
        throw std::domain_error("invalid operation");

    if(0 == i)
        return *_left;
    else if( 1 == i)
        return *_right;
    else
        throw std::domain_error("invalid operation");
}

int GYH::Binary_Tree::compare_to(const GYH::Object &obj) const
{
    Binary_Tree const& arg =
            dynamic_cast<Binary_Tree const&>(obj);

    if( is_empty() )
        return arg.is_empty() ? 0 : -1;
    else if( arg.is_empty() )
        return 1;
    else
    {
        int result = key().compare( arg.key() );
        if(0 == result )
            result = left().compare_to( arg.left() );
        if(0 == result )
            result = right().compare_to( arg.right() );

        return result;
    }

}
