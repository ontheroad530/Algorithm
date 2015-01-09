#ifndef OBJECT_H
#define OBJECT_H

#include <ostream>

namespace GYH
{

typedef unsigned long Hash_Value;


int compare(int l, int r) const;
int compare(unsigned int l, unsigned int r) const;
int compare(double l, double r) const;
int compare(char l, char r) const;
int compare(const std::string& l, const std::string& r) const;


class Object
{
public:
    virtual ~Object();
    virtual bool is_null() const;
    virtual int compare(Object const&) const;
    virtual Hash_Value hash()const = 0;
    virtual void put(std::ostream& ) const = 0;

protected:
    virtual int compare_to(Object const&) const = 0;
};

class Null_Object: public Object
{
public:
    bool is_null() const;
    Hash_Value hash() const;
    void put(std::ostream &) const;

    static Null_Object& instance();
protected:
    int compare_to(const Object &) const;

private:
    Null_Object();
};

template<typename T>
class Wrapper: public Object
{
public:
    Wrapper();
    Wrapper(T const&);
    Wrapper& operator = (T const&);
    operator T const&() const;
    Hash_Value hash() const;
    void put(std::ostream &) const;

protected:
    int compare_to(const Object &) const;
    T   _datum;
};

template<typename T>
Wrapper<T>::Wrapper()
    :_datum()
{

}

template<typename T>
Wrapper<T>::Wrapper(const GYH::T &t)
    :_datum(t)
{

}

template<typename T>
Wrapper &Wrapper<T>::operator =(const GYH::T &t)
{
    _datum = t;
    return *this;
}

template<typename T>
Hash_Value Wrapper<T>::hash() const
{

}

template<typename T>
void Wrapper<T>::put(std::ostream &os) const
{
    os << _datum;
}

template<typename T>
int Wrapper<T>::compare_to(const Object &obj) const
{
    Wrapper<T> const& arg =
            dynamic_cast<Wrapper<T> const&>(obj);

    return GYH::compare(*this, obj);
}

template<typename T>
Wrapper<T>::operator const T &() const
{
    return _datum;
}


bool operator == (Object const& left, Object const& right);
bool operator != (Object const& left, Object const& right);
bool operator <= (Object const& left, Object const& right);
bool operator < (Object const& left, Object const& right);
bool operator >= (Object const& left, Object const& right);
bool operator > (Object const& left, Object const& right);
std::ostream& operator << (std::ostream& os, Object const& obj);

}
#endif // OBJECT_H
