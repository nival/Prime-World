#ifndef SYSTEM_BASEINTERFACE_H_INCLUDED
#define SYSTEM_BASEINTERFACE_H_INCLUDED

#include "../DefaultTypes.h"
#include "BasicFactory.h"
#include "PointersMacroses.h"
#include "PointersDetail.h"

_interface IBinSaver;
class BaseObjectST;
class WeakPointerProxyST;


_interface IBaseInterfaceST : public SerializableBase
{
  NI_DECLARE_CLASS_1( IBaseInterfaceST, SerializableBase )

  typedef IBaseInterfaceST    BaseInterfaceType;
  typedef BaseObjectST        BaseObjectType;
  typedef WeakPointerProxyST  WeakPointerProxyType;

  virtual BaseObjectST *          CastToBaseObject() = 0;
  virtual WeakPointerProxyST *    AcquireWeakProxy() = 0;

  virtual                        ~IBaseInterfaceST() {};
};



//FIXME: ugly copy-paste
//NOTE: but macrouses are worse
_interface IBaseInterfaceMT : public SerializableBase
{
  NI_DECLARE_CLASS_1( IBaseInterfaceMT, SerializableBase )
  virtual int OnDestroyContents() { return 0; }

  typedef IBaseInterfaceMT    BaseInterfaceType;
  typedef BaseObjectMT        BaseObjectType;
  typedef WeakPointerProxyMT  WeakPointerProxyType;

  virtual BaseObjectMT *          CastToBaseObject() = 0;
  virtual WeakPointerProxyMT *    AcquireWeakProxy() = 0;

  virtual                        ~IBaseInterfaceMT() {};
};

#endif //SYSTEM_BASEINTERFACE_H_INCLUDED
