#include "ownership.h"

namespace GYH
{

Ownership::Ownership()
    :_is_owner(true)
{

}

Ownership::Ownership(Ownership &arg)
    :_is_owner(arg._is_owner)
{
    arg._is_owner = false;
}

void Ownership::assert_ownership()
{
    _is_owner = true;
}

void Ownership::rescind_ownership()
{
    _is_owner = false;
}

bool Ownership::is_onwer() const
{
    return _is_owner;
}


}
