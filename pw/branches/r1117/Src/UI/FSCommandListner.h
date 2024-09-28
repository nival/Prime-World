#pragma once

namespace UI
{

class FlashContainer2;

_interface IFSCommandListner : public IBaseInterfaceST
{
  NI_DECLARE_CLASS_1( IFSCommandListner, IBaseInterfaceST )

  virtual void OnFSCommand( FlashContainer2* _wnd, const char* listenerID,  const char* args, const wchar_t * argsW  ) = 0;
};

} 


