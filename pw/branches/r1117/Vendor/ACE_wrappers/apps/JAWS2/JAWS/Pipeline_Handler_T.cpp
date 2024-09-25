// $Id: Pipeline_Handler_T.cpp 80826 2008-03-04 14:51:23Z wotte $

#ifndef JAWS_PIPELINE_HANDLER_T_CPP
#define JAWS_PIPELINE_HANDLER_T_CPP

#include "JAWS/Pipeline_Handler_T.h"

ACE_RCSID(JAWS, Pipeline_Handler_T, "$Id: Pipeline_Handler_T.cpp 80826 2008-03-04 14:51:23Z wotte $")

template <class TYPE>
JAWS_Pipeline_Abstract_Handler<TYPE>::JAWS_Pipeline_Abstract_Handler (void)
{
}

template <class TYPE>
JAWS_Pipeline_Abstract_Handler<TYPE>::~JAWS_Pipeline_Abstract_Handler (void)
{
}

template <class TYPE> int
JAWS_Pipeline_Abstract_Handler<TYPE>::put (ACE_Message_Block *mb,
                                           ACE_Time_Value *tv)
{
  TYPE *data = reinterpret_cast <TYPE *> (mb->data_block ());

  int status = this->handle_put (data, tv);

  return status;
}

#endif /* !defined (JAWS_PIPELINE_HANDLER_T_CPP) */
