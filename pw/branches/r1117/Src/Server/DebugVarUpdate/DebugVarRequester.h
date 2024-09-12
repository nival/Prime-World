#pragma once

#include "System/Thread.h"
#include "System/HPTimer.h"

#include "Server/DebugVarUpdate/RDebugVarReporter.auto.h" 

namespace NDebug
{
typedef NHPTimer::FTime TIMESTAMP;

enum TSpecialUpdatePeriod {
  ONCE = 0,
  COMMAND = -1
};

struct SClientVar
{
  TIMESTAMP lastRequested;
  TIMESTAMP lastReceived;
  TIMESTAMP updPeriod; // 0 == once (dont auto-update); 
  wstring   wsValue;
  bool      isChecked; // используется механизмом GetNextUpdatedVar()

  inline SClientVar() {}

  inline SClientVar( const TIMESTAMP period_ ): updPeriod( period_ ), isChecked(true)
  { lastRequested = lastReceived = 0; }
};

const TIMESTAMP DEFAULT_UPDATE_PERIOD = 10.0;
const TIMESTAMP REMOTE_CMD_PERIOD = -1.0; // период < 0 будем считать признаком "immediate" команды, для интерфейса RunCmd
const TIMESTAMP MAX_REMOTE_WAIT_TIME = 1.0;

class DebugVarRequesterMap; // forward
typedef long TUserId;

class DebugVarRequester: public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1(DebugVarRequester, BaseObjectMT);
public:
  typedef nstl::map<wstring, SClientVar> TClientVars;

protected:
  TClientVars vars;
  TUserId userId; // пригодится для ForEach

  // не знаю, нужна ли при нашей step-идеологии thread-safety.. на единичном requester пока точно уберу, пусть через Map лезут
  //threading::Mutex mutex;

  StrongMT<RDebugVarReporter> remote;
  TIMESTAMP timeRemoteRequested;
  bool waitingForRemote;  // "все еще ждем" (на каждом Step поругиваясь в лог)

  TIMESTAMP lastVarsReceived; // когда последний раз получали что-нибудь валидное в CallbackValueReceive
  TIMESTAMP lastVarsChecked;  // когда у нас последний раз забирали значения переменных

  // поскольку mutex убираем, пусть создается строго через DebugVarRequesterMap 
  // (доступ к указателю и ReqVar оставляем для гибкой настройки списка запрашиваемых переменных)
  friend class DebugVarRequesterMap; 
  DebugVarRequester();
  ~DebugVarRequester();

public: 

  void AttachTo( rpc::Node* node );
  void AttachQuery( rpc::Node* node, const char *path );
  void Detach();

  // периодически шлем удаленному Reporter'у пачку запросов: на все переменные, у которых истек период апдейта
  void UpdateStep();
    void CallbackValueReceive( const wchar_t* reply ); // CALLBACK for remote DebugVar requests
    void CallbackCmdReplyReceive( const wchar_t* reply ); // CALLBACK for remote RunCommand requests
    void CallbackRemotePtrReceive( RDebugVarReporter* ); // ответ на Query<RDebugVarReporter>
  bool IsReady(); // есть валидный remote (или пока что ждем его)

  inline bool ReqVarOnce( const wstring &name ) { return ReqVar( name, 0 ); } 
  bool ReqVar( const wstring &name, TIMESTAMP secPeriod = DEFAULT_UPDATE_PERIOD );
  bool RemoveVar( const wstring &name );
  
  // возвращаем только готовое значение (полученное от удаленного reporter'а), если еще не получали -> false
  bool GetValue( const wstring &name, wstring& outValue ) const; 

  // т.к. мутексы убрали, механизм проверки тоже НЕ THREAD-SAFE, разумеется; считаем процесс вызова Callback-ов строго синхронным
  inline bool IsChecked() { return (lastVarsChecked >= lastVarsReceived); } // true = не было апдейтов за отчетный период
  inline void SetChecked() { lastVarsChecked = lastVarsReceived; } // переменные проверили, до следующего Receive можно не дергать 

  bool GetNextUpdatedVar( wstring &outName, wstring& outValue ); // каждая возвращенная переменная сразу помечается как checked
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SScenarioVar
{
  TIMESTAMP updPeriod; // 0 == once (dont auto-update); 
  wstring   wsName;
  inline SScenarioVar(): updPeriod( 0 ) {}
  inline SScenarioVar( const wstring &name_, const TIMESTAMP period_ ): wsName( name_ ), updPeriod( period_ ) {}
  inline SScenarioVar( const wchar_t *name_, const TIMESTAMP period_ ): wsName( name_ ), updPeriod( period_ ) {}

  bool Parse( const nstl::string &pair, bool cmd_may_omit_period=false );
};

/// DebugVarRequesterMap.
///
/// Для реального использования часто требуется не единственный DebugVarRequester, 
/// а целый их набор (индексируемый по некому long connectionId),
/// чтобы, например, на каждое соединение (клиента) вешать свой "опросчик переменных".
/// Также желательно, чтобы эти "опросчики" создавались с единым "сценарием опроса", 
/// т.е. списком запрашиваемых переменных с их соотв. периодичностями.
class DebugVarRequesterMap: public NonCopyable
{
public:
  typedef nstl::vector< SScenarioVar > TScenarioVars;
protected:
  TScenarioVars defaultScenario;
  
  typedef nstl::map<TUserId, StrongMT<DebugVarRequester> > TRequesters;
  TRequesters requesters;

  // не знаю, нужна ли при нашей step-идеологии thread-safety.. пусть будет
  threading::Mutex mutex;

public:  
  DebugVarRequesterMap() {}
  ~DebugVarRequesterMap();

  // возвращаем указатель для того чтобы можно было понавешать дополнительные запросы переменных 
  // (особенно если не используется дефолт-сценарий)
  DebugVarRequester* AddRequester( TUserId userId, rpc::Node* node, bool bApplyDefaultScenario = true );
  DebugVarRequester* QueryRequester( TUserId userId, rpc::Node* node, const char *path, bool bApplyDefaultScenario = true );
  bool RemoveRequester( TUserId userId );

  // добавляем "одноразовую" переменную/команду, для конкретного реквестера, без добавления к общему сценарию
  bool AddImmediate( TUserId userId, const wstring &name, TIMESTAMP secPeriod = REMOTE_CMD_PERIOD );

  // добавляем переменную "для немедленного исполнения всем", т.е. ко всем существующим requester'ам (но не к default сценариям)
  void AddVarBroadcast( const wstring &name, TIMESTAMP secPeriod );

  // чтобы можно было вызывать цепочкой в одну строчку: req.AddScenario().AddScenario()...
  DebugVarRequesterMap& AddScenario( const wstring &varName, const TIMESTAMP secUpdatePeriod = 0 );
  void AddScenarios( const TScenarioVars& vec ); // добавляем сразу вектор (напр. из конфига)
  bool RemoveScenario( const wstring &varName ); // удаляем переменную из сценария (true если и правда была такая)
  bool RemoveScenarioByPrefix( const wstring &varName ); // удаляем из сценария все переменные с данным префиксом (true если была хоть одна такая)
  void ClearScenarios() { defaultScenario.clear(); }
  void ListScenarios( wstring& out ); // простой дамп в формате "name:period \n name:period.."
 
  // возвращаем только готовое значение (полученное от удаленного reporter'а), если еще не получали -> false
  bool GetValue( const TUserId userId, const wstring &name, wstring& outValue ) const; 

  // пробегаем по коллекции запрашивалок, может кому-то пора тянуть переменные с другого конца
  void UpdateStep();

  // следующий "опросчик" (список переменных клиента), в котором что-то изменилось (был Receive) за отчетный период
  DebugVarRequester* GetNextUpdated();

  typedef void (*TCallbackType)(const TUserId&, wstring&, wstring&, void*); // foreach-callback, получит все "свежие" vars
  int ForEachUpdatedVar( TCallbackType funcCallback, void* param); 
};

} // namespace NDebug
