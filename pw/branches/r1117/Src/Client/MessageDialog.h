#pragma once

namespace UI
{
class Window;
};

namespace NMainLoop
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
_interface IMessageScreenCallback : public IBaseInterfaceST
{
  NI_DECLARE_CLASS_1( IMessageScreenCallback, IBaseInterfaceST );

  virtual void  SetupMessageWindow(UI::Window * pScreenBaseWindow) = 0;
  virtual void  OnYesButton() = 0;
  virtual void  OnNoButton() = 0;
  virtual bool  OnEscapeKey() = 0;
};

} //namespace NMainLoop
