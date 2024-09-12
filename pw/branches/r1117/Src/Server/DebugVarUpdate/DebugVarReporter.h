#pragma once

#include "RPC/RPC.h"
#include "RPC/LocalEntityFactory.h"
#include "RPC/GateKeeper.h"


namespace NDebug
{

static const char *VarPathSuffix = ".var";
 
REMOTE class DebugVarReporter : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( DebugVarReporter, BaseObjectMT )
public: 

  RPC_ID();

  wchar_t buf[1024]; // а то что мы как бедные родственники
  
  DebugVarReporter();
  DebugVarReporter( rpc::GateKeeper *gateKeeper, const char* serviceName );

  ~DebugVarReporter();

  REMOTE const wchar_t* GetDebugVar(const wstring &sVarName);
  REMOTE const wchar_t* RunRemoteCommand(const wstring &cmd);

  // если хотим зарегистрировать готовый инстанс ответчика (напр. мы уже объ€вили его полем своего класса),
  // регистрируем готовый объект через этот RegisterObject(), и выдаем свое им€ сервиса (reporter добавит к нему суффикс)
  void RegisterObject( rpc::GateKeeper *gateKeeper, const char* serviceName );

  // если не хотим создавать ответчик статически, а хотим создавать его по вызову с remote стороны, 
  //  нужно зарегистрировать свою фабрику объектов здесь (желательно сразу после создани€ gatekeeper и factory)
  static void AttachTo( rpc::LocalEntityFactory* factory );
};

} // namespace DebugVar
