#ifndef WINDOWNAMEMAPINTERFACE_H_INCLUDED
#define WINDOWNAMEMAPINTERFACE_H_INCLUDED


namespace NNameMap
{
  class ReadonlyVariant;
  _interface IMap;
};


namespace UI
{

_interface IWindowNameMapInterface : public IBaseInterfaceST
{
  NI_DECLARE_CLASS_1( IWindowNameMapInterface, IBaseInterfaceST );

  virtual NNameMap::ReadonlyVariant * GetVariant( const char * name, bool registerNameMap ) = 0;
};

} //namespace UI

#endif //WINDOWNAMEMAPINTERFACE_H_INCLUDED
