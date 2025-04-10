// $Id: HTTP_Policy.cpp 80826 2008-03-04 14:51:23Z wotte $

#include "HTTP_Policy.h"

ACE_RCSID(PROTOTYPE, HTTP_Policy, "$Id: HTTP_Policy.cpp 80826 2008-03-04 14:51:23Z wotte $")

HTTP_Policy::HTTP_Policy (JAWS_Concurrency_Base *concurrency)
  : concurrency_ (concurrency)
{
}

JAWS_Concurrency_Base *
HTTP_Policy::update (void *)
{
  /* for now, we always return the same concurrency strategy */
  return this->concurrency_;
}
