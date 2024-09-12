#ifndef NAMEMAPPEDWINDOW_H_INCLUDED
#define NAMEMAPPEDWINDOW_H_INCLUDED

#include "Window.h"
#include "WindowNameMapInterface.h"

namespace UI
{

class NameMappedWindow : public Window, public IWindowNameMapInterface
{
  NI_DECLARE_REFCOUNT_CLASS_2( NameMappedWindow, Window, IWindowNameMapInterface );

public:
  DECLARE_LUA_TYPEINFO( NameMappedWindow );

  NameMappedWindow() {}

  virtual void OnNameMapChanged() {}

protected:
  void ResetNameMapAssociations();

  //IWindowNameMapInterface
  virtual NNameMap::ReadonlyVariant * GetVariant( const char * name, bool registerNameMap );
};

} //namespace UI

#endif //NAMEMAPPEDWINDOW_H_INCLUDED
