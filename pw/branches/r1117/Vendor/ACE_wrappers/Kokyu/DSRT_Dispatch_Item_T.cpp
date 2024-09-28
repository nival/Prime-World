// $Id: DSRT_Dispatch_Item_T.cpp 80826 2008-03-04 14:51:23Z wotte $

#ifndef DSRT_DISPATCH_ITEM_T_CPP
#define DSRT_DISPATCH_ITEM_T_CPP

#include "DSRT_Dispatch_Item_T.h"

#if ! defined (__ACE_INLINE__)
#include "DSRT_Dispatch_Item_T.inl"
#endif /* __ACE_INLINE__ */

ACE_RCSID(Kokyu, DSRT_Dispatch_Item, "$Id: DSRT_Dispatch_Item_T.cpp 80826 2008-03-04 14:51:23Z wotte $")

namespace Kokyu
{

template <class DSRT_Scheduler_Traits>
DSRT_Dispatch_Item_var<DSRT_Scheduler_Traits>::
DSRT_Dispatch_Item_var (DSRT_Dispatch_Item<DSRT_Scheduler_Traits> *p)
  :ACE_Strong_Bound_Ptr<DSRT_Dispatch_Item<DSRT_Scheduler_Traits>,
                        ACE_SYNCH_MUTEX> (p)
{
}

template <class DSRT_Scheduler_Traits>
DSRT_Dispatch_Item_var<DSRT_Scheduler_Traits>::
DSRT_Dispatch_Item_var (const DSRT_Dispatch_Item_var &r)
  :ACE_Strong_Bound_Ptr<DSRT_Dispatch_Item<DSRT_Scheduler_Traits>,
                        ACE_SYNCH_MUTEX> (r)
{
}

}

#endif /* DSRT_DISPATCH_ITEM_T_CPP */
