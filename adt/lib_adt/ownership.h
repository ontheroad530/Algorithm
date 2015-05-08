#ifndef OWNERSHIP_H
#define OWNERSHIP_H

namespace GYH
{

class Ownership
{
protected:
    Ownership();
    Ownership(Ownership& arg);

public:
    void assert_ownership();
    void rescind_ownership();
    bool is_owner() const;

private:
    bool    _is_owner;
};

}

#endif // OWNERSHIP_H
