// $Id: Dispatch_Deferrer.inl 80826 2008-03-04 14:51:23Z wotte $

namespace Kokyu
{

ACE_INLINE
Dispatch_Deferrer_Attributes::Dispatch_Deferrer_Attributes()
{
}

ACE_INLINE
Dispatch_Deferrer::Dispatch_Deferrer()
  : msg_strat_()
  , rgq_(this->msg_strat_)
  , timers_()
  , react_()
  , task_(0)
{
}

ACE_INLINE
Dispatch_Deferrer::~Dispatch_Deferrer()
{
  this->react_.close();

  this->timers_.close();
}

} //namespace Kokyu
