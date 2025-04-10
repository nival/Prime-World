// $Id: ParserContext.cpp 80826 2008-03-04 14:51:23Z wotte $

#include "ACEXML/parser/parser/ParserContext.h"

#if !defined (__ACEXML_INLINE__)
# include "ACEXML/parser/parser/ParserContext.inl"
#endif /* __ACEXML_INLINE__ */

ACEXML_Parser_Context::~ACEXML_Parser_Context()
{
  delete this->instream_;
  this->instream_ = 0;
  delete this->locator_;
  this->locator_ = 0;
}

