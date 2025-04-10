// $Id: DLL_Test_Parent.cpp 80826 2008-03-04 14:51:23Z wotte $

#include "DLL_Test_Parent.h"
#include "ace/Log_Msg.h"

ACE_RCSID (tests,
           DLL_Test_Parent,
           "$Id: DLL_Test_Parent.cpp 80826 2008-03-04 14:51:23Z wotte $")


Parent::~Parent (void)
{
}

void
Parent::test (void)
{
  ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("parent called\n")));
}
