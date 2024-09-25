// $Id: Entity_Manager.cpp 80826 2008-03-04 14:51:23Z wotte $

#include "ACEXML/parser/parser/Entity_Manager.h"

#if !defined (__ACEXML_INLINE__)
# include "ACEXML/parser/parser/Entity_Manager.inl"
#endif /* __ACEXML_INLINE__ */


ACEXML_Entity_Manager::ACEXML_Entity_Manager (void)
  : entities_ (0)
{

}

ACEXML_Entity_Manager::~ACEXML_Entity_Manager (void)
{
  this->reset();
}

