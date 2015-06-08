#include <cstdlib>

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


GYH::BST &GYH::BST::left() const
{
    return dynamic_cast<BST&>(Binary_Tree::left());
}

GYH::BST &GYH::BST::right() const
{
    return dynamic_cast<BST&>(Binary_Tree::right());
}

GYH::Object &GYH::BST::find(const GYH::Object &obj) const
{
    if( is_empty() )
        return Null_Object::instance();

    int const diff = obj.compare( *_key );
    if(0 == diff)
        return *_key;
    else if(diff < 0)
        return left().find(obj);
    else
        return right().find(obj);
}

GYH::Object &GYH::BST::find_min() const
{
    if( is_empty() )
        return Null_Object::instance();
    else if( left().is_empty() )
        return *_key;
    else
        return left().find_min();
}

GYH::Object &GYH::BST::find_max() const
{
    if( is_empty() )
        return Null_Object::instance();
    else if( right().is_empty() )
        return *_key;
    else
        return right().find_max();
}

void GYH::BST::insert(GYH::Object &obj)
{
    if( is_empty() )
        attach_key(obj);
    else
    {
        int const diff = obj.compare(*_key);
        if(0 == diff)
            throw std::invalid_argument("duplicate key");
        else if(diff < 0)
            left().insert(obj);
        else
            right().insert(obj);
    }
    balance();
}

void GYH::BST::withdraw(GYH::Object &obj)
{
    if( is_empty() )
        throw std::invalid_argument("object not found");

    int const diff = obj.compare(*_key);
    if(0 == diff)
    {
        if( !left().is_empty() )
        {
            Object& max = left().find_max();
            _key = &max;
            left().withdraw(max);
        }
        else if( !right().is_empty() )
        {
            Object& min = right().find_min();
            _key = &min;
            right().withdraw(min);
        }
        else
            detach_key();
    }
    else if(diff < 0)
        left().withdraw(obj);
    else
        right().withdraw(obj);

    balance();
}

bool GYH::BST::is_member(const GYH::Object &obj) const
{
    if( find(obj) != Null_Object::instance())
        return true;

    return false;
}

void GYH::BST::attach_key(GYH::Object &obj)
{
    if(!is_empty())
        throw std::domain_error("invalid operation");

    _key = &obj;
    _left = new BST();
    _right = new BST();
}

GYH::Object &GYH::BST::detach_key()
{
    if( !is_leaf() )
        throw std::domain_error("invalid operation");

    Object& result = *_key;
    delete _left;
    delete _right;
    _key = 0;
    _left = 0;
    _right = 0;

    return result;
}

void GYH::BST::balance()
{

}


GYH::AVL_Tree::AVL_Tree()
    :BST()
    ,_height(-1)
{

}

int GYH::AVL_Tree::height() const
{
    return _height;
}

GYH::AVL_Tree &GYH::AVL_Tree::left() const
{
    return dynamic_cast<AVL_Tree&>(BST::left());
}

GYH::AVL_Tree &GYH::AVL_Tree::right() const
{
    return dynamic_cast<AVL_Tree&>(BST::right());
}

int GYH::AVL_Tree::balance_factor() const
{
    if( is_empty() )
        return 0;
    else
        return left().height() - right().height();
}

void GYH::AVL_Tree::adjust_height()
{
    if( is_empty() )
        _height = -1;
    else
        _height = std::max( left().height(), right().height() ) + 1;
}

void GYH::AVL_Tree::ll_rotation()
{
    if( is_empty() )
        throw std::domain_error("invalid rotation");

    Binary_Tree* const tmp = _right;
    _right = _left;
    _left = right()._left;
    right()._left = right()._right;
    right()._right = tmp;

    Object* const tmp_obj = _key;
    _key = right()._key;
    right()._key = tmp_obj;

    right().adjust_height();
    adjust_height();
}

void GYH::AVL_Tree::lr_rotation()
{
    if( is_empty() )
        throw std::domain_error("invalid rotation");

    left().rr_rotation();
    ll_rotation();
}

void GYH::AVL_Tree::rr_rotation()
{
    if( is_empty() )
        throw std::domain_error("invalid rotaion");

    Binary_Tree* const tmp = _left;
    _left = _right;
    _right = left()._right;
    left()._right = left()._left;
    left()._left = tmp;

    Object* const tmp_obj = _key;
    _key = left()._key;
    left()._key = tmp_obj;

    left().adjust_height();
    adjust_height();
}

void GYH::AVL_Tree::rl_rotation()
{
    if( is_empty() )
        throw std::domain_error("invalid rotaion");

    right().ll_rotation();
    rr_rotation();
}

void GYH::AVL_Tree::attach_key(GYH::Object &obj)
{
    if( !is_empty() )
        throw std::domain_error("invalid operation");

    _key = &obj;
    _left = new AVL_Tree();
    _right = new AVL_Tree();
    _height = 0;
}

GYH::Object &GYH::AVL_Tree::detach_key()
{
    _height = -1;
    return BST::detach_key();
}

void GYH::AVL_Tree::balance()
{
    adjust_height();
    if( abs( balance_factor()) > 1 )
    {
        if( balance_factor() > 0 )
        {
            if( left().balance_factor() > 0 )
                ll_rotation();
            else
                lr_rotation();
        }
        else
        {
            if( right().balance_factor() < 0 )
                rr_rotation();
            else
                rl_rotation();
        }
    }
}


GYH::MWay_Tree::MWay_Tree(unsigned int m)
    :_m(m)
    ,_num_of_keys(0)
{

}

GYH::MWay_Tree::~MWay_Tree()
{
    purge();
}

GYH::Object &GYH::MWay_Tree::key() const
{
    throw std::invalid_argument("invalid operation");
    return Null_Object::instance();
}

GYH::Object &GYH::MWay_Tree::key(unsigned int pos) const
{
    if(0 == pos || pos > _num_of_keys )
        throw std::invalid_argument("invalid operation");

    return *_key[pos];
}

GYH::MWay_Tree &GYH::MWay_Tree::subtree(unsigned int pos) const
{
    if(pos > _num_of_keys)
        throw std::invalid_argument("invalid operation");

    return *_subtree[pos];
}

bool GYH::MWay_Tree::is_leaf() const
{
    if( is_empty() )
        throw std::domain_error("invalid operation");

    for(unsigned int i = 0; i <= _num_of_keys; ++i)
    {
        if( !_subtree[i]->is_empty() )
            return false;
    }

    return true;
}

unsigned int GYH::MWay_Tree::degree() const
{
    return _num_of_keys;
}

int GYH::MWay_Tree::height() const
{
    if( is_empty() )
        return 0;

    if( is_leaf() )
        return 1;

    int height = 0;
    for(unsigned int i = 0; i < _num_of_keys; ++i)
    {
        int tmp = _subtree[i]->height();
        height = height >= tmp ? height : tmp;
    }

    return height + 1;
}

void GYH::MWay_Tree::depth_first_traversal(GYH::Pre_Post_Visitor &visitor) const
{
    if( !is_empty() )
    {
        for(unsigned int i = 0; i <= _num_of_keys + 1; ++i)
        {
            if(i >= 2)
                visitor.post_visit(*_key[i-1]);
            if( i <= _num_of_keys - 1)
                visitor.pre_visit(*_key[i+1]);
            if(i >= 1 && i <= _num_of_keys)
                visitor.visit(*_key[i]);
            if( i <= _num_of_keys)
                _subtree[i]->depth_first_traversal(visitor);
        }
    }
}

GYH::Object &GYH::MWay_Tree::find(const GYH::Object &obj) const
{
    if( is_empty() )
        return Null_Object::instance();

    unsigned int const index = find_index(obj);
    if( index != 0 && obj == *_key[index] )
        return *_key[index];
    else
        return subtree(index).find(obj);
}

GYH::Object &GYH::MWay_Tree::find_min() const
{
    if( is_empty() )
        return Null_Object::instance();
    else if( _subtree[0]->is_empty() )
        return *_key[1];
    else
        return dynamic_cast<MWay_Tree*>(_subtree[1])->find_min();
}

GYH::Object &GYH::MWay_Tree::find_max() const
{
    if( is_empty() )
        return Null_Object::instance();
    else if( _subtree[_num_of_keys]->is_empty() )
        return *_key[_num_of_keys];
    else
        return dynamic_cast<MWay_Tree*>(_subtree[_num_of_keys])->find_max();
}

bool GYH::MWay_Tree::is_member(const GYH::Object &obj) const
{
    if( find(obj) != Null_Object::instance() )
        return true;

    return false;
}

void GYH::MWay_Tree::insert(GYH::Object &obj)
{
    if( is_empty() )
    {
        _subtree[0] = new MWay_Tree(_m);
        _key[1] = &obj;
        _subtree[1] = new MWay_Tree(_m);
        _num_of_keys = 1;
    }
    else
    {
        unsigned int const index = find_index(obj);
        if( index != 0 && obj == *_key[index])
            throw std::invalid_argument("duplicate key");
        if(_num_of_keys < _m - 1U)
        {
            for(unsigned int i = _num_of_keys; i > index; --i)
            {
                _key[i + 1] = _key[i];
                _subtree[i + 1] = _subtree[i];
            }
            _key[index + 1] = &obj;
            _subtree[index + 1] = new MWay_Tree(_m);
            ++_num_of_keys;
        }
        else
            _subtree[index]->insert(obj);
    }
}

void GYH::MWay_Tree::withdraw(GYH::Object &obj)
{
    if( is_empty() )
        throw std::invalid_argument("object not found");

    unsigned int const index = find_index(obj);
    if( index != 0 && obj == *_key[index])
    {
        if( !_subtree[index-1U]->is_empty() )
        {
            Object& max = _subtree[index - 1U]->find_max();
            _key[index] = &max;
            _subtree[index-1U]->withdraw(max);
        }
        else if( !_subtree[index]->is_empty() )
        {
            Object& min = _subtree[index]->find_min();
            _key[index] = &min;
            _subtree[index]->withdraw(min);
        }
        else
        {
            --_num_of_keys;
            delete _subtree[index];
            for(unsigned int i = index; i <= _num_of_keys; ++i)
            {
                _key[i] = _key[i+1];
                _subtree[i] = _subtree[i+1];
            }
            if(0 == _num_of_keys)
                delete _subtree[0];
        }
    }
    else
        _subtree[index]->withdraw(obj);
}

void GYH::MWay_Tree::purge()
{
    if( is_empty() )
        return;

    if( is_owner() )
    {
        for(unsigned int i = 1; i <= _num_of_keys; ++i)
        {
            delete _key[i];
        }
    }
    for(unsigned int i = 0; i <= _num_of_keys; ++i)
    {
        delete _subtree[i];
    }
    _num_of_keys = 0;
}

unsigned int GYH::MWay_Tree::find_index(const GYH::Object &obj) const
{
    if( is_empty() )
        throw std::domain_error("invalid operation");

    if( obj < *_key[1] )
        return 0;

    unsigned int left = 1;
    unsigned int right = _num_of_keys;
    while( left < right)
    {
        int const middle = (left + right + 1) / 2;
        if( obj >= *_key[middle] )
            left = middle;
        else
            right = middle - 1U;
    }

    return left;
}

int GYH::MWay_Tree::compare_to(const GYH::Object &obj) const
{
    const MWay_Tree& other = dynamic_cast<const MWay_Tree&>(obj);
    return GYH::compare(_num_of_keys, other._num_of_keys);
}
