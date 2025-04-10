/* -*- C++ -*- */
// Proactor.i,v 4.7 2001/12/24 22:36:17 schmidt Exp

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

ACE_INLINE int
TRB_Proactor::run_event_loop (void)
{
  ACE_TRACE ("TRB_Proactor::run_event_loop");
  TRB_Proactor *p = TRB_Proactor::instance ();

  if (p == 0)
    return -1;

  return p->proactor_run_event_loop (TRB_Proactor::check_reconfiguration);
}

ACE_INLINE int
TRB_Proactor::run_event_loop (ACE_Time_Value &tv)
{
  ACE_TRACE ("TRB_Proactor::run_event_loop (tv)");
  TRB_Proactor *p = TRB_Proactor::instance ();

  if (p == 0)
    return -1;

  return p->proactor_run_event_loop 
    (tv, TRB_Proactor::check_reconfiguration);
}

ACE_INLINE int
TRB_Proactor::reset_event_loop(void)
{
  ACE_TRACE ("TRB_Proactor::reset_event_loop");
  TRB_Proactor *p = TRB_Proactor::instance ();

  if (p == 0)
    return -1;

  return p->proactor_reset_event_loop ();
}

ACE_INLINE int
TRB_Proactor::end_event_loop (void)
{
  ACE_TRACE ("TRB_Proactor::end_event_loop");
  TRB_Proactor *p = TRB_Proactor::instance ();

  if (p == 0)
    return -1;

  return p->proactor_end_event_loop ();
}

ACE_INLINE int
TRB_Proactor::event_loop_done (void)
{
  ACE_TRACE ("TRB_Proactor::event_loop_done");
  TRB_Proactor *p = TRB_Proactor::instance ();

  if (p == 0)
    return -1;

  return p->proactor_event_loop_done ();
}

ACE_INLINE int
TRB_Proactor::post_wakeup_completions (int how_many)
{
  ACE_TRACE ("TRB_Proactor::post_wakeup_completions");
  TRB_Proactor *p = TRB_Proactor::instance ();

  if (p == 0)
    return -1;

  return p->proactor_post_wakeup_completions (how_many);
}

ACE_END_VERSIONED_NAMESPACE_DECL

