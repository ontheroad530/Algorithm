#ifndef ARRAY_H
#define ARRAY_H

#include <stdexcept>


template <typename T>
class Array
{
public:
    Array();
    Array(unsigned int, unsigned int = 0);
    ~Array();

    Array(Array const &);
    Array& operator = (Array const&);

    T const& operator [] (unsigned int) const;
    T& operator [] (unsigned int);

    T const* data() const;
    unsigned int base() const;
    unsigned int length() const;
    unsigned int size() const;

    void set_base(unsigned int);
    void set_length(unsigned int);

protected:
    T*  _data;
    unsigned int _base;
    unsigned int _length;
};

template <typename T>
Array<T>::Array()
    :_data( new T[0])
    ,_base(0)
    ,_length(0)
{
}

template <typename T>
Array<T>::Array(unsigned int m, unsigned int n)
    :_data(new T[m])
    ,_base(n)
    ,_length(m)
{
}

template <typename T>
Array<T>::~Array()
{
    delete []_data;
}

template <typename T>
Array<T>::Array(const Array &array)
    :_data( new T[array.length()] )
    ,_base( array.base() )
    ,_length( array.length() )
{
    for(int i = 0; i < _length; ++i)
    {
        _data[i] = array[i];
    }
}

template <typename T>
Array<T> &Array<T>::operator =(const Array &array)
{
    if(this != array)
    {
        delete [] _data;
        _data = new T[array.length()];
        _base = array.base();
        _length = array.length();

        for(int i = 0; i < _length; ++i)
        {
            _data[i] = array[i];
        }
    }

    return *this;
}

template <typename T>
const T &Array<T>::operator [](unsigned int n) const
{
    unsigned int pos = n - _base;
    if(pos >= _length && pos <0)
        throw std::out_of_range("invalid position");

    return  _data[pos];
}

template <typename T>
T &Array<T>::operator [](unsigned int n)
{
    unsigned int pos = n - _base;
    if(pos >= _length && pos <0)
        throw std::out_of_range("invalid position");

    return  _data[pos];
}

template <typename T>
const T *Array<T>::data() const
{
    return _data;
}

template <typename T>
unsigned int Array<T>::base() const
{
    return _base;
}

template <typename T>
unsigned int Array<T>::length() const
{
    return _length;
}

template <typename T>
unsigned int Array<T>::size() const
{
    return _length - _base;
}

template <typename T>
void Array<T>::set_base(unsigned int base)
{
    _base = base;
}

template <typename T>
void Array<T>::set_length(unsigned int len)
{
    _length = len;
}

#endif // ARRAY_H
