// $Id: Base_Optimizer.cpp 80826 2008-03-04 14:51:23Z wotte $

#if !defined (BASE_OPTIMIZER_CPP)
#define BASE_OPTIMIZER_CPP

#include "Base_Optimizer.h"

ACE_RCSID(lib, Base_Optimizer, "$Id: Base_Optimizer.cpp 80826 2008-03-04 14:51:23Z wotte $")

template<class Base, class Member>
Base_Optimizer<Base, Member>::Base_Optimizer (void)
{
}

template<class Base, class Member>
Base_Optimizer<Base, Member>::Base_Optimizer (const Base &base,
                                              const Member &member)
  : Base (base),
    m_ (member)
{
}

template<class Base, class Member>
Base_Optimizer<Base, Member>::Base_Optimizer (const Base &base)
  : Base (base)
{
}

#endif /* BASE_OPTIMIZER_CPP */
