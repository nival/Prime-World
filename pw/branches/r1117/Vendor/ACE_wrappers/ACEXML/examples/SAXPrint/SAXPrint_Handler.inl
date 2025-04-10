// -*- C++ -*-  $Id: SAXPrint_Handler.inl 80826 2008-03-04 14:51:23Z wotte $

ACEXML_INLINE void
ACEXML_SAXPrint_Handler::inc_indent (void)
{
  this->indent_ += 1;
}

ACEXML_INLINE void
ACEXML_SAXPrint_Handler::dec_indent (void)
{
  this->indent_ -= 1;
}
