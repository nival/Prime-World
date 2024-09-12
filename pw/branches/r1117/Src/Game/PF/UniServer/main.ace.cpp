#pragma warning( disable : 4996)
#include <ace/ACE.h>

int ace_init()
{
  return ACE::init();
}

int ace_fini()
{
  return ACE::fini();
}
