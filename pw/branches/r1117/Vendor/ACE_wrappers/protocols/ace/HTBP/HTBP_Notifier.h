// -*- C++ -*-

//=============================================================================
/**
 *  @file   HTBP_Notifier.h
 *
 *  $Id: HTBP_Notifier.h 80826 2008-03-04 14:51:23Z wotte $
 *
 *  @author Phil Mesnier, Priyanka Gontla
 */
//=============================================================================

#ifndef ACE_HTBP_NOTIFIER_H
#define ACE_HTBP_NOTIFIER_H
#include /**/ "ace/pre.h"

#include "ace/Event_Handler.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "HTBP_Export.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

namespace ACE
{
  namespace HTBP
  {
    // Forward declarations.
    class Channel;

    class HTBP_Export Notifier : public ACE_Event_Handler
    {
    public:
      Notifier (Channel *ch);
      int handle_input(ACE_HANDLE );
      int handle_output(ACE_HANDLE );

      void unregister (void);

      ACE_HANDLE get_handle (void) const;

    private:
      Channel *channel_;
    };
  }
}

ACE_END_VERSIONED_NAMESPACE_DECL

#include /**/ "ace/post.h"
#endif /* ACE_HTBP_NOTIFIER_H */
