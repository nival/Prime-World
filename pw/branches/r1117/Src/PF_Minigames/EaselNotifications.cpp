#include "stdafx.h"

#include "EaselNotifications.h"

#include "../System/Updater.h"

namespace PF_Minigames
{

NDebug::PerformanceDebugVar easelPerf_WorldClientNotifications("World-Client notify", "EaselPerf", 0, 0.0f, true);

EaselNotifier::EaselNotifier( PF_Core::IWorld* _pWorld )
: PF_Core::WorldObjectBase(_pWorld, false )
{
 // updater = new Updater::CUpdater();
}

void EaselNotifier::Register( tObserver& observer )
{
  updater.Register(&observer);
}

void EaselNotifier::Register(int _typeID, Updater::IUpdateProcessorFunc *_pFunc)
{
  updater.Register(_typeID,_pFunc);
}

bool EaselNotifier::Notify( tNotification& notification )
{
  NDebug::PerformanceDebugVarGuard(easelPerf_WorldClientNotifications, false);

  //
  // REMARK !!! для чего тут передача по ссылке, когда потом берется указатель
  // да и внешний объект нужно создавать с помощью new
  // не явное описание, чисто интуитивно первый раз передал ссылочный объект
  // как результат все упало
  //
  // Тут проблема не в ссылке, а в CObjectBase. Его можно создавать только через new и передавать только через CObj/CPtr.
  // Но в таком случае надо проверять на валидность. Получается много проверок на пустом месте - эдакая паранойя. Передача по указателю тоже 
  // ничего с точки зрения языка не значит. В общем виде ты в этом случае ты должен озаботиться о new/delete. Если внутри его присвоить CObj, то 
  // delete вызовет такое же падение. 

  updater.Push( &notification, false);
  return true;
}

} // namespace PF_Minigames

BASIC_REGISTER_CLASS( PF_Minigames::IEaselNotifier )
REGISTER_SAVELOAD_CLASS_NM( EaselNotifier, PF_Minigames )
