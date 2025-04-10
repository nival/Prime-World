// Proactor_Impl.cpp
#include "TProactor/Proactor_Impl.h"

#if ((defined (ACE_WIN32) && !defined (ACE_HAS_WINCE)) || (defined (ACE_HAS_AIO_CALLS) || defined(ACE_HAS_AIO_EMULATION)))
// This only works on Win32 platforms and on Unix platforms supporting
// aio calls.


ACE_BEGIN_VERSIONED_NAMESPACE_DECL

TRB_Proactor_Impl::~TRB_Proactor_Impl (void)
{
}


int
TRB_Proactor_Impl::post_wakeup_completions (int how_many)
{
  TRB_Wakeup_Completion wakeup_completion (&this->wakeup_handler_,
                                           0,  // act
                                           0,  // completion key
                                           0,  // priority
                                           ACE_SIGRTMIN);
  for (ssize_t ci = 0; ci < how_many; ci++)
    {
      TRB_Asynch_Result_Impl * result_impl =
        this->create_result_impl (wakeup_completion);

      if (result_impl == 0 || result_impl->post () < 0)
        return -1;
    }

  return 0;
}



ACE_END_VERSIONED_NAMESPACE_DECL

#endif /* (ACE_WIN32 && ACE_HAS_WINCE) || ACE_HAS_AIO_CALLS */
