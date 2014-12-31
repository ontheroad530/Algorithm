#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdexcept>

template<typename T>
class Linked_List;

template<typename T>
/**
 * @brief The List_Element class
 */
class List_Element
{
public:

    T const& data() const;
    List_Element const * next() const;

    friend class Linked_List<T>;

private:
    List_Element(const T&, List_Element*);

    T   _data;
    List_Element*   _next;
};


template<typename T>
const T &List_Element<T>::data() const
{
    return _data;
}

template<typename T>
const List_Element<T> *List_Element<T>::next() const
{
    return _next;
}

template<typename T>
List_Element<T>::List_Element(const T &data, List_Element *next)
    :_data(data)
    ,_next(next)
{
}


template<typename T>
/**
 * @brief The Linked_List class
 */
class Linked_List
{
public:
    Linked_List();
    ~Linked_List();

    Linked_List(Linked_List const&);
    Linked_List& operator = (Linked_List const &);

    List_Element<T> const* head() const;
    List_Element<T> const* tail() const;

    bool empty() const;
    T const& first() const;
    T const& last() const;

    int size() const;

    void prepend(T const&);
    void append(T const&);
    void extract(T const&);
    void purge();
    void insert_after(List_Element<T> const*, T const&);
    void insert_before(List_Element<T> const*, T const&);

private:
    List_Element<T>* _head;
    List_Element<T>* _tail;
};

template<typename T>
Linked_List<T>::Linked_List()
    :_head(NULL)
    ,_tail(NULL)
{

}

template<typename T>
Linked_List<T>::~Linked_List()
{
    purge();
}

template<typename T>
Linked_List<T>::Linked_List(const Linked_List &arg)
    :_head(NULL)
    ,_tail(NULL)
{
    List_Element<T> const * ptr;
    for(ptr = arg._head; ptr != NULL; ptr = ptr->_next)
    {
        append(ptr->data());
    }
}

template<typename T>
Linked_List<T> &Linked_List<T>::operator =(const Linked_List &arg)
{
    if(this != &arg)
    {
        purge();

        List_Element<T> const * ptr;
        for(ptr = arg._head; ptr != NULL; ptr = ptr->_next)
        {
            append(ptr->data());
        }
    }

    return *this;
}

template<typename T>
const List_Element<T> *Linked_List<T>::head() const
{
    return _head;
}

template<typename T>
const List_Element<T> *Linked_List<T>::tail() const
{
    return _tail;
}

template<typename T>
bool Linked_List<T>::empty() const
{
    return _head == NULL;
}

template<typename T>
const T &Linked_List<T>::first() const
{
    if(_head == NULL)
        throw std::domain_error("list is empty");

    return _head->data();
}

template<typename T>
const T &Linked_List<T>::last() const
{
    if(_tail == NULL)
        throw std::domain_error("list is empty");

    return _tail->data();
}

template<typename T>
int Linked_List<T>::size() const
{
    int size = 0;

    List_Element<T> const * ptr;
    for(ptr = _head; ptr != NULL; ptr = ptr->_next)
        ++size;

    return size;
}

template<typename T>
void Linked_List<T>::prepend(const T &item)
{
    List_Element<T>* const tmp = new List_Element<T>(item, _head);

    if(!tmp)
    {
        throw std::out_of_range("new List_Element error");
    }

    if(!_head)
        _tail = tmp;
    _head = tmp;
}

template<typename T>
void Linked_List<T>::append(const T &item)
{
    List_Element<T>* const tmp = new List_Element<T>(item, NULL);

    if(!tmp)
        throw std::out_of_range("new List_Element error");

    if(!_head)
        _head = tmp;
    else
        _tail->_next = tmp;

    _tail = tmp;
}

template<typename T>
void Linked_List<T>::extract(const T &item)
{
    List_Element<T>* ptr = _head;
    List_Element<T>* prev_ptr = NULL;

    while(!ptr && ptr->data() != item)
    {
        prev_ptr = ptr;
        ptr = ptr->_next;
    }

    if(!ptr)
        throw std::invalid_argument("item not found");

    if(ptr == _head)
        _head = ptr->_next;
    else
        prev_ptr->_next = ptr->_next;

    if(ptr == _tail)
        _tail = prev_ptr;

    delete ptr;
}

template<typename T>
void Linked_List<T>::purge()
{
    while(_head)
    {
        List_Element<T>* const tmp = _head;
        _head = _head->_next;
        delete tmp;
    }

    _tail = NULL;
}

template<typename T>
void Linked_List<T>::insert_after(const List_Element<T> *arg, const T &item)
{
    List_Element<T>* ptr = const_cast<List_Element<T>* >(arg);
    if(!ptr)
        throw std::invalid_argument("invaild position");

    List_Element<T>* const tmp = new List_Element<T>(item, ptr->_next);
    if(!tmp)
        throw std::out_of_range("new List_Element error");

    ptr->_next = tmp;

    if(ptr == _tail)
        _tail = tmp;
}

template<typename T>
void Linked_List<T>::insert_before(const List_Element<T> *arg, const T &item)
{
    List_Element<T>* ptr = const_cast<List_Element<T>* >(arg);
    if(!ptr)
        throw std::invalid_argument("invaild position");

    List_Element<T>* const tmp = new List_Element<T>(item, ptr);
    if(!tmp)
        throw std::out_of_range("new List_Element error");

    if(ptr == _head)
        _head = tmp;
    else
    {
        List_Element<T>* prev_ptr = _head;
        while(prev_ptr != NULL && prev_ptr->_next != ptr)
            prev_ptr = prev_ptr->_next;

        if(!prev_ptr)
            throw std::invalid_argument("invaild position");

        prev_ptr->_next = tmp;
    }
}

#endif // LINKED_LIST_H
