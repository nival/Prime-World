// $Id: Dispatcher_Impl.inl 80826 2008-03-04 14:51:23Z wotte $

namespace Kokyu
{

ACE_INLINE
int Dispatcher_Impl::init (const Dispatcher_Attributes& attr)
{
  return init_i (attr);
}

ACE_INLINE
int Dispatcher_Impl::dispatch (const Dispatch_Command* cmd,
                               const QoSDescriptor& qos_info)
{
  return dispatch_i (cmd, qos_info);
}

ACE_INLINE
int Dispatcher_Impl::shutdown ()
{
  return shutdown_i ();
}

ACE_INLINE
int Dispatcher_Impl::activate ()
{
  return activate_i ();
}

}
