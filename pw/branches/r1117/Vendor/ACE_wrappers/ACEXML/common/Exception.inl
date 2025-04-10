// -*- C++ -*- $Id: Exception.inl 80826 2008-03-04 14:51:23Z wotte $

ACEXML_INLINE const ACEXML_Char *
ACEXML_Exception::id (void) const
{
  return ACEXML_Exception::exception_name_;
}

ACEXML_INLINE ACEXML_Exception*
ACEXML_Exception::_downcast (ACEXML_Exception* x)
{
  return x;
}
