//!Component('RPC/all')
//!Component('System/Threading')
//!Component('System/NSTL')
//!Component('System/Asserts')
//!Component('System/Streams')
//!Component('System/Dumpers')
//!Component('System/Random')
//!Component('Network/Transport')
//!Component('Network/LocalNetDriver')
//!Component('RPC/RPCMixin')
//!Component('System/Commands')

#include "stdafx.h"
#if defined( NV_WIN_PLATFORM )
#include <rpc.h>
#endif // defined( NV_WIN_PLATFORM )
#include <cxxtest/TestSuite.h>

#include "Network/Transport.h"
#include "Network/TransportInitializer.h"
#include "Network/LocalNetDriver.h"
#include "Network/TransportMessages.h"
#include "Network/AddressTranslator.h"

#include <System/BinSaver.h>
#include <System/BitData.h>
#include <System/fixedvector.h>
#include <System/IDGenerator.h>
#include <System/RandomGen.h>
#include <System/FileSystem/FilePath.h>
#include <RPC/RPC.h>
#include <RPC/P2PNode.h>
#include <RPC/CppWrapper.h>
#pragma warning( disable: 4189 )
#include "RPCMixin.h"

// как создается обЪект на mirror сервере ?
// объект, созданный на одном из серверов должен создаваться и на соседних по требованию с создавшего сервера
// есть параметры создания объекта
// есть параметры объекта, которые синхронизируются по всем копиям
// параметры объекта для создания - могут быть интерфейсы и данные
// репликация параметров может быть выборочной
// репликация может быть настраиваемого качества (полная гарантия, количество retry попыток)
// тестирование должно быть возможно на локальной машине
// могут быть только серверные объекты, или только клиентские
// переводом управления объектами с сервера на сервер занимается специальный алгоритм
// сервер решает какие объекты создать для клиента (зачем в BigWorld часть логики по изменению алгоритмов вынесена на клиент ?)
// не обязательно у создаваемой сущности будет позиция
// создание сущности по сути отвязано от репликации
// насколько репликация данных связана с разрабатываемыми алгоритмами ? (есть ощущение что очень связано, но как ?)
// клиент и сервер должны уметь получать управление при изменении данных
// вариант - все что реплицируется, является обязательно частью системы данных, при этом поля могут быть persistent 
// что значит persistent - как связана структура данных и SQL сервер
// как меняется структура данных и хранимые данные на сервере ?
// рабочие сервера отделены от клиента - у клиентов нет понимания где сейчас находится управление
// какая функциональность будет достаточной чтобы сделать оценку сложности задачи ?
// мир разбит на квадраты размера 200x200 метров - все ресурсы скачиваются по ним
// есть однозначное соответствие - сектор и необходимые для него данные, root-ами являются сущности, которые находятся на этом секторе
// редактирование поддерживает эту секторность
// для сервера и клиента способ хранения данных должен быть прозрачным - это означает что способы хранения разные, но доступ к ним одинаковый
// также это означает что задание структуры делается в одном месте
// изменения данных по возможности должны быть инкрементальными - например при изменении ландшафта должны присылаться только изменившиеся данные
// AI работает на сервере, но на клиенте должна быть возможность получать серверные данные, необходимые для качественной визуализации
// что происходит когда игрок убивает моба - он возрождается ?
// должны уметь ли серверные объекты сохранять свои данные на сервере ?
// синхронизация между тестовым и игровыми серверами должны происходить в обе стороны ?
// каким образом отображаются объекты для которых не хватает данных ?
// необходима адаптивная система выкачивания контента для клиента - в первую очередь качается то что игрок видит
// миров может быть большое количество - база данных должна поддерживать это 

// features
// создание сервера
// создание на сервере сущности, двигающейся по кругу
// создание простейшего клиента
// подключение к серверу
// отображение соответсвующей сущности на клиенте и ее визуализации
// добавление цвета и размера точки

namespace test 
{

struct RemoteApi : BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1(RemoteApi, BaseObjectMT);
  RPC_ID();
  int processedCount;
  int param0;
  RemoteApi():processedCount(0), param0(0) 
  {
    constructorsCalled ++;
  }

  RemoteApi(int param0):param0(param0) 
  {
    constructorsCalled ++;
  }

  static int destructorsCalled;
  static int constructorsCalled;
  static void Reset()
  {
    destructorsCalled = 0;
    constructorsCalled = 0;
  }

  ~RemoteApi()
  {
    destructorsCalled ++;
  }

  REMOTE void callRemote()
  {
    processedCount ++;
  }
  REMOTE void callRemoteParam(int param)
  {
    processedCount ++;
  }

}; 
int RemoteApi::constructorsCalled = 0;
int RemoteApi::destructorsCalled = 0;

struct MissedRemoteApi : BaseObjectMT
{
  RPC_ID();
  NI_DECLARE_REFCOUNT_CLASS_1(MissedRemoteApi, BaseObjectMT);
}; 

class RRemoteApi : public rpc::IRemoteEntity, public BaseObjectMT 
{
  NI_DECLARE_REFCOUNT_CLASS_2( RRemoteApi, rpc::IRemoteEntity, BaseObjectMT );
public:
  RPC_INFO("test::RemoteApi", 0xBAADF00A);

  RRemoteApi():handler(0) {}

  RRemoteApi(rpc::EntityHandler* handler, rpc::IRemoteEntity* _parent):
  handler(handler),
  parent(_parent)
  {
  }

  ~RRemoteApi()
  {
    if (handler)
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }

  void callRemote()
  {
    handler->Go(handler->Call(0));
  }

  void callRemoteParam(int param)
  {
    handler->Go(handler->Call(1, param));
  }

  REMOTE RRemoteApi* getRemoteApi()
  {
    return 0;
  }


  friend class EntityHandler;
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RRemoteApi::ID(), RRemoteApi::CRC32}, handler->GetGUID() }; return info; }
  virtual rpc::EntityHandler* GetHandler() { return handler; } 

  bool Update(rpc::IUpdateCallback* callback=0)
  {
    return handler->Update(this, callback);
  }
  rpc::INode* GetNode(int index) { return GetHandler()->GetNode(index); }
  rpc::INode* GetNode(const char* name) { return GetHandler()->GetNode(name); }

  virtual rpc::IUpdateCallback* GetUpdateCallback() { StrongMT<rpc::IRemoteEntity> _parent = parent.Lock(); return handler->GetUpdateCallback(_parent); }
  virtual void SetParent(rpc::IRemoteEntity* _parent) { parent = _parent; }
private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;

};
static rpc::SimpleRemoteEntityFactory<test::RRemoteApi> factory_test_RRemoteApi;


class LRemoteApi : public rpc::ILocalEntity, BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( LRemoteApi, rpc::ILocalEntity, BaseObjectMT);
public:

  LRemoteApi() {}
  LRemoteApi(test::RemoteApi* xxx, rpc::IEntityMap* entityMap, rpc::ILocalEntityFactory* _factory=0): // TODO: move to SObj here
  xxx(xxx),
  factory(_factory)
  {
  }

  ~LRemoteApi()
  {
    if (factory)
    {
      factory->Destroy(this);
    }
  }

  virtual rpc::CallResult::Enum Call(const rpc::MethodCallHeader& call, rpc::MethodCall& resultCall, rpc::Arguments& args, const byte* paramsData, int _paramsSize)
  {
    static const rpc::MethodInfo methods[] = 
    {
      {"callRemote", 0, false, rpc::GetMethodCode(&test::RemoteApi::callRemote) },
      {"callRemoteParam", 1, false, rpc::GetMethodCode(&test::RemoteApi::callRemoteParam) },
    };
    if (call.id >= sizeof(methods)/sizeof(rpc::MethodInfo) || call.id < 0)
    {
      return rpc::CallResult::WrongMethodId;
    }
    rpc::MethodCallStack stack = rpc::FillStack(call, args, paramsData, _paramsSize, methods[call.id]);
    if (stack.isValid)
    {
      return vcall(call.id, resultCall, stack)?rpc::CallResult::OK : rpc::CallResult::DataCorruption;
    }
    return rpc::CallResult::DataCorruption;
  }

  virtual void Publish()
  {
  }

  bool vcall(byte methodId, rpc::MethodCall& call, rpc::MethodCallStack& stack) 
  {
    bool popResult = true;
    switch (methodId)
    {
    case 0: rpc::VCall(stack, xxx.Get(), &test::RemoteApi::callRemote, popResult); break;
    case 1: rpc::VCall(stack, xxx.Get(), &test::RemoteApi::callRemoteParam, popResult); break;
    default:
      popResult = false;
      break;
    }
    return popResult;
  }

  virtual uint GetClassCrc() const { return 0xBAADF00A; }
  virtual int GetMemberIndex(const void*) { return -1; }
  virtual void* _Get(uint classId) { return (classId == rpc::_GetId("test::RemoteApi", rpc::GeneratedType)) ? xxx : 0; }

private:
  StrongMT<test::RemoteApi> xxx;
  rpc::ILocalEntityFactory* factory;
};

} // test

NI_DEFINE_REFCOUNT(test::RemoteApi);

namespace test
{
  class RSimpleReplicated : public rpc::IRemoteEntity, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_2(RSimpleReplicated, rpc::IRemoteEntity, BaseObjectMT);
  public:
    RPC_INFO("test::SimpleReplicated", 0xBAADF00C);

    RSimpleReplicated():handler(0) 
    {
    }

    RSimpleReplicated(rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent):
    handler(_handler),
    parent(_parent),
      _vi_accessor(6),
      _vi(&_vi_accessor),
      _vd_accessor(7),
      _vd(&_vd_accessor),
      _name_accessor(8),
      _name(&_name_accessor),
      _wname_accessor(10),
      _wname(&_wname_accessor),
      _snapshots_accessor(12),
      _snapshots(&_snapshots_accessor)
    {
      _i = 0;
      _d = 0;
      _s = 0;
      _f = 0;
      _b = 0;
      _BoolVar = false;
      _vi_accessor.Init(this);
      _vd_accessor.Init(this);
      _name_accessor.Init(this);
      _wname_accessor.Init(this);
      _snapshots_accessor.Init(this);
    }

    ~RSimpleReplicated()
    {
      if (handler)
      {
        handler->OnDestruct(*this);
        handler = 0;
      }
    }

    inline bool IsUpdated() const { return handler->IsUpdated(); }

    void seti(int value) { handler->Set(this, 0, value, _i); }
    int geti() const { return _i; }

    void setd(double value) { handler->Set(this, 1, value, _d); }
    double getd() const { return _d; }

    void sets(short value) { handler->Set(this, 2, value, _s); }
    short gets() const { return _s; }

    void setf(float value) { handler->Set(this, 3, value, _f); }
    float getf() const { return _f; }

    void set_BoolVar(bool value) { handler->Set(this, 4, value, _BoolVar); }
    bool get_BoolVar() const { return _BoolVar; }

    void set_b(byte value) { handler->Set(this, 5, value, _b); }
    byte get_b() const { return _b; }

    void set_vi(int index, int value) 
    { 
      _vi_accessor.Set<int>(index, value, _vi[index]);
      _vi[index] = value; 
    }
    rpc::vector<int>& get_vi() { return _vi; }

    void set_vd(int index, double value) 
    { 
      _vd_accessor.Set(index, value, _vd[index]);
      _vd[index] = value; 
    }
    rpc::vector<double>& get_vd() { return _vd; }

    void set_name(const char* value) 
    { 
      _name.assign(value, true); 
    }
    void set_name(int index, char value) 
    { 
      _name_accessor.Set(index, value, _name[index]);
      _name[index] = value; 
    }
    rpc::rpcstring& get_name() { return _name; }

    void set_wname(const wchar_t* value) 
    { 
      _wname.assign(value, true); 
    }
    void set_wname(int index, wchar_t value) 
    { 
      _wname_accessor.Set(index, value, _wname[index]);
      _wname[index] = value; 
    }
    rpc::rpcwstring& get_wname() { return _wname; }

    void set_ptr(RSimpleReplicated* value) { handler->Set(this, 9, value, _ptr); }
    StrongMT<RSimpleReplicated>& get_ptr() { return _ptr; }
    StrongMT<RSimpleReplicated> _ptr;

    void setquat(const CQuat&  value) { handler->Set(this, 11, value, _quat); }
    const CQuat&  getquat() const { return _quat; }
    CQuat  _quat;

    void set_shapshots(int index, const InitialSnapshot& value) 
    { 
      _snapshots_accessor.Set<InitialSnapshot>(index, value, _snapshots[index]);
      _snapshots[index] = value; 
    }
    rpc::vector<InitialSnapshot>& get_snapshots() { return _snapshots; }

    void Commit(bool publishAfterCommit=false)
    {
      handler->Commit(publishAfterCommit);
    }

    void Rollback()
    {
      handler->Rollback(this);
    }
    bool Update(rpc::IUpdateCallback* callback=0)
    {
      return handler->Update(this, callback);
    }
    virtual rpc::IUpdateCallback* GetUpdateCallback() { StrongMT<rpc::IRemoteEntity> _parent = parent.Lock(); return handler->GetUpdateCallback(_parent); }

    bool SetUpdateCallback(rpc::IUpdateCallback* callback=0)
    {
      return handler->SetUpdateCallback(callback);
    }
    void SetParent(rpc::IRemoteEntity* _parent) { parent = _parent; }
  protected:
    friend class rpc::Gate;
    rpc::EntityHandler* GetHandler() { return handler; }
    virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RSimpleReplicated::ID(), RSimpleReplicated::CRC32}, handler->GetGUID() }; return info; }

    virtual bool RollbackMember(byte memberId, rpc::ArgReader& s) 
    {
      switch (memberId)
      {
      case 0: return s.Rollback(_i); 
      case 1: return s.Rollback(_d); 
      case 2: return s.Rollback(_s); 
      case 3: return s.Rollback(_f);    
      case 4: return s.Rollback(_BoolVar);
      case 5: return s.Rollback(_b); 
      case 6: return s.Rollback(_vi); 
      case 7: return s.Rollback(_vd); 
      case 8: return s.Rollback(_name); 
      case 9: return s.Rollback(_ptr); 
      case 10: return s.Rollback(_wname); 
      case 11: return s.Rollback(_quat); 
      case 12: return s.Rollback(_snapshots); 
      default:
        return false;
      }
    }

    virtual bool vset(byte memberId, rpc::ArgReader& s) { 
      switch (memberId)
      {
      case 0: return s.Assign(_i); 
      case 1: return s.Assign(_d); 
      case 2: return s.Assign(_s); 
      case 3: return s.Assign(_f); 
      case 4: return s.Assign(_BoolVar);
      case 5: return s.Assign(_b);    
      case 6: return s.Assign((nstl::vector<int>&)_vi); 
      case 7: return s.Assign((nstl::vector<double>&)_vd); 
      case 8: return s.Assign((nstl::string&)_name); 
      case 9: return s.Assign(_ptr); 
      case 10: return s.Assign((nstl::wstring&)_wname); 
      case 11: return s.Assign(_quat); 
      case 12: return s.Assign((nstl::vector<InitialSnapshot>&)_snapshots); 
      default:
        return false;
      }
    }

    virtual bool Synchronize(rpc::ArgWriter* args)
    {
      args->Sync(0, _i);
      args->Sync(1, _d);
      args->Sync(2, _s);
      args->Sync(3, _f);
      args->Sync(4, _BoolVar);
      args->Sync(5, _b);
      args->Sync(6, (nstl::vector<int>&)_vi);
      args->Sync(7, (nstl::vector<double>&)_vd);
      args->Sync(8, (nstl::string&)_name);
      args->Sync(9, _ptr);
      args->Sync(10, (nstl::wstring&)_wname);
      args->Sync(11, _quat);
      args->Sync(12, (nstl::vector<InitialSnapshot>&)_snapshots);
      return true;
    }
  private:
    rpc::VectorAccessor _snapshots_accessor;
    rpc::vector<InitialSnapshot> _snapshots;

    rpc::VectorAccessor _vi_accessor;
    rpc::vector<int> _vi;
    rpc::VectorAccessor _vd_accessor;
    rpc::vector<double> _vd;
    rpc::StringAccessor _name_accessor;
    rpc::rpcstring _name;
    rpc::WStringAccessor _wname_accessor;
    rpc::rpcwstring _wname;
    int _i;
    double _d;
    short _s;
    float _f;
    byte _b;
    bool _BoolVar;

    StrongMT<rpc::EntityHandler> handler;
    WeakMT<rpc::IRemoteEntity> parent;
  };

  static rpc::SimpleRemoteEntityFactory<test::RSimpleReplicated> factory_test_RSimpleReplicated;
}
NI_DEFINE_REFCOUNT(test::RSimpleReplicated);

namespace test
{
  typedef double MyType;
  enum MyEnum 
  {
    Enum1,
    Enum2,
  };

  struct SimpleStruct{
    int i;
    float f;
    double d;
    short s;
    SimpleStruct(int _i, float _f, double _d, short _s):i(_i), f(_f), d(_d), s(_s) {}
    SimpleStruct():i(0), f(0.f), d(0), s(0) {}
  };

  struct ComplexRabbit : BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_1(ComplexRabbit, BaseObjectMT);
  public:
    RPC_ID();
    nstl::Bool<false> is_processed;
    int int_param0;
    float float_param0;
    double double_param0;
    nstl::string string_param0;
    nstl::string nsltString_param0;
    nstl::vector<int> vector_param0;
    nstl::vector<double> vector_param1;
    bool bool_param0;
    short short_param0;
    SimpleStruct s;
    nstl::Bool<false> isStructParamRecieved;
    long long long_long_param0;
    MyType MyType_param0;
    MyEnum MyEnum_param0;
    SimpleStruct r;
    bool timeIsSet;
    int vector_after_param;

    ComplexRabbit()
    {
      int_param0 = -1;
      double_param0 = -1.0; 
      float_param0 = -1.f;        
      bool_param0 = false;
      is_object_deleted++;
      timeIsSet = false;
    }
    static int is_object_deleted;

    ~ComplexRabbit()
    {
      is_object_deleted--;
    }

    REMOTE void process()
    {
      is_processed = true;
    }

    REMOTE void processStruct(const SimpleStruct& _s)
    {

      s = _s;
      isStructParamRecieved = true;
    }

    REMOTE void processInt(int value)
    {
      int_param0 = value;
    }

    REMOTE void processFloat(float value)
    {
      float_param0 = value;
    }

    REMOTE void processDouble(double value)
    {
      double_param0 = value;
    }

    REMOTE void processFloatInt(float fvalue, int ivalue)
    {
      float_param0 = fvalue;
      int_param0 = ivalue;
    }

    REMOTE void processString(const char* value)
    {
      if (value)
      {
        string_param0 = value;
      } else
      {
        string_param0.clear();
      }
    }

    REMOTE void processNSLTString( const nstl::string& value )
    {
      nsltString_param0 = value;
    }

    REMOTE void processVector(const nstl::vector<int>& value)
    {
      vector_param0 = value;
    }

    nstl::vector<InitialSnapshot> vector_param_snapshot;
    REMOTE void processVector2(const nstl::vector<InitialSnapshot>& value, int param)
    {
      vector_param_snapshot = value;
      vector_after_param = param;
    }

    REMOTE void processVectorWithDoubles(const nstl::vector<double>& value)
    {
      vector_param1 = value;
    }

    REMOTE void processBool(bool value)
    {
      bool_param0 = value;
    }

    REMOTE void processShort(short value)
    {
      short_param0 = value;
    }

    REMOTE int processIntWithReturnValueInt(int value) 
    {
      return 2*value;
    }

    REMOTE int processIntWithReturnValueIntAsync(int value) 
    {
      return 3*value;
    }

    REMOTE int processIntWithReturnValueIntAsyncLong(int value) 
    {
      threading::Event e(false, false);
      e.Wait(value);
      return value;
    }

    REMOTE double processDoubleWithReturnValueDoubleAsync(double value) 
    {
      return 4*value;
    }

    REMOTE void processLongLong(long long value) 
    {
      long_long_param0 = value;
    }

    REMOTE void processMyType(MyType value)
    {
      MyType_param0 = value;
    }

    REMOTE void processMyEnum(MyEnum value)
    {
      MyEnum_param0 = value;
    }

    REMOTE const SimpleStruct& processReturnStructRef()
    {
      r.d = 555;
      r.f = 100.f;
      r.i = 777;
      r.s = 12;
      return r;
    }

    REMOTE SimpleStruct processReturnStruct(const SimpleStruct& _s)
    {
      s = _s;
      r.d = 111;
      r.f = 200.f;
      r.i = 877;
      r.s = 24;
      return r;
    }

    REMOTE void processRecieveTime(const NHPTimer::STime& recieveTime)
    {
      timeIsSet = true;
    }
  };

  int ComplexRabbit::is_object_deleted = 0;

  class RSimpleRabbit;

  struct SimpleRabbit  : BaseObjectMT
  {
    RPC_ID();
    NI_DECLARE_REFCOUNT_CLASS_1(SimpleRabbit, BaseObjectMT);
  public:

    SimpleRabbit():api(0) {
      constructor_number_called = 1;
      simpleRabbitsCount++;
      localApi = new test::RemoteApi;
    }

    SimpleRabbit(RRemoteApi* _api, short value):
    api(_api)
    {
      constructor_number_called = 3;
      simpleRabbitsCount++;
      localApi = new test::RemoteApi;
    }

    SimpleRabbit(short value):
    short_creation_param0(value)
    {
      constructor_number_called = 2;
      simpleRabbitsCount++;
      localApi = new test::RemoteApi;
    }    

    ~SimpleRabbit()
    {
      simpleRabbitsCount--;
    }

    REMOTE void process()
    {
      is_processed = true;
    }

    REMOTE void processSnapshot(const InitialSnapshot& _msg)
    {
      msg = _msg;
      isSnapshotRecieved = true;
    }

    REMOTE void processTwoSnapshots(const InitialSnapshot& _msg0, const InitialSnapshot& _msg1)
    {
      msg0 = _msg0;
      msg1 = _msg1;
      isSnapshotRecieved = true;
    }

    REMOTE const InitialSnapshot& processSnapshotReturnSnapshot(const InitialSnapshot& _msg)
    {
      msg = _msg;
      isSnapshotRecieved = true;
      return msg; 
    }

    REMOTE SMatchmakingStatus getStatus()
    {
      status.progress = 50;
      status.requestsAccepted = 2;
      status.sessionId = "good session";
      return status; 
    }

    REMOTE void processApi()
    {
      api->callRemote();
    }

    REMOTE void processVectorsOfSnapshots(const nstl::vector<InitialSnapshot>& _vmsg)
    {
      vmsg = _vmsg;
    }

    REMOTE const nstl::vector<byte>& processReturnVectorOfBytes()
    {
      vectorOfBytes.resize(0);
      vectorOfBytes.push_back('A');
      vectorOfBytes.push_back('B');
      return vectorOfBytes;
    }

    REMOTE void processByte(byte value)
    {
      byteValue = value;
    }

    REMOTE void processRemoteApi(test::RRemoteApi* api, bool del)
    {
      if (!del)
      {
        rapi = api;
      }
    }

    REMOTE void processSimpleRabbit(test::RSimpleRabbit* api)
    {
      rabbit = api;
    }


    REMOTE void processVectorOfStrings(const nstl::vector<nstl::string>& _vs)
    {
      vs = _vs;
    }
    REMOTE void processVectorOfWStrings(const nstl::vector<nstl::wstring>& _wvs)
    {
      wvs = _wvs;
    }
    REMOTE void processWString( const nstl::wstring& value )
    {
      ws = value;
    }

    REMOTE test::RRemoteApi* GetRRemoteApi()
    {
      return rapi;
    }

    REMOTE test::RRemoteApi* GetLocalRemoteApi()
    {
      if (localApiGateName.length() > 0)
      {
        return RemotePtrInOtherGate<test::RRemoteApi>(localApi, localApiGateName.c_str());
      } 
      else
      {
        return RemotePtr<test::RRemoteApi>(localApi);
      }
    }

    REMOTE const nstl::string& processWithReturnValueNSTLStringAsync()
    {
      return string_param0;
    }

    REMOTE void processLocalRemoteApi(test::RRemoteApi* api)
    {
      rapi = api;
      rapi->callRemoteParam(555);
    }

    REMOTE void processFixedVector(const FixedVector<int, 100>& v)
    {
      fixedVector = v;
    }

    REMOTE void processMemoryBlock(const rpc::MemoryBlock& _b)
    {
      b = _b;
    }

    REMOTE void processMemoryBlockVector(nstl::vector<rpc::MemoryBlock>& _blocks)
    {
      blocks.resize(_blocks.size());
      for (int i=0;i<_blocks.size();++i)
      {
        blocks[i] = _blocks[i];
      }
    }
    REMOTE void SetSimpleReplicated(test::RSimpleReplicated* api)
    {
      replica = api;
    }

    rpc::CachedMemoryBlock b;
    nstl::vector<rpc::CachedMemoryBlock> blocks;
    nstl::Bool<false> is_processed;
    short short_creation_param0;
    int constructor_number_called;
    InitialSnapshot msg;
    InitialSnapshot msg0;
    InitialSnapshot msg1;
    nstl::Bool<false> isSnapshotRecieved;
    StrongMT<RRemoteApi> api;
    nstl::vector<InitialSnapshot> vmsg;
    byte byteValue;                                                                       
    static int simpleRabbitsCount;
    nstl::vector<byte> vectorOfBytes;
    nstl::vector<nstl::string> vs;
    nstl::vector<nstl::wstring> wvs;
    nstl::wstring ws;
    StrongMT<test::RRemoteApi> rapi;
    StrongMT<test::RSimpleRabbit> rabbit;
    StrongMT<test::RemoteApi> localApi;
    StrongMT<test::RSimpleReplicated> replica;
    nstl::string string_param0;
    FixedVector<int, 100> fixedVector;
    SMatchmakingStatus status;
    nstl::string localApiGateName;
  };

  int SimpleRabbit::simpleRabbitsCount = 0;

  struct BadCrc32Class : BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_1(BadCrc32Class, BaseObjectMT);
    RPC_ID();
    BadCrc32Class() {}

    REMOTE void process() {}
  };
} // test
//autogenerated code
NI_DEFINE_REFCOUNT(test::ComplexRabbit);

namespace test 
{
  class RComplexRabbit : public rpc::IRemoteEntity, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_2( RComplexRabbit, rpc::IRemoteEntity, BaseObjectMT );
  public:
    RPC_INFO("test::ComplexRabbit", 0xBAADF00D);

    RComplexRabbit():handler(0) {}

    RComplexRabbit(rpc::EntityHandler* handler, rpc::IRemoteEntity* _parent):
    handler(handler),
    parent(_parent)
    {
    }

    ~RComplexRabbit()
    {
      if (handler)
      {
        handler->OnDestruct(*this);
        handler = 0;
      }
    }

    void process()
    {
      handler->Go(handler->Call(0));
    }

    void processInt(int value)
    {
      handler->Go(handler->Call(1, value));
    }

    void processFloat(float value)
    {
      handler->Go(handler->Call(2, value));
    }

    void processDouble(double value)
    {
      handler->Go(handler->Call(3, value));
    }

    void processFloatInt(float fvalue, int ivalue)
    {
      handler->Go(handler->Call(4, fvalue, ivalue));
    }

    void processString(const char* value)
    {
      handler->Go(handler->Call(5, value));
    }

    void processVector(const nstl::vector<int>& value)
    {
      handler->Go(handler->Call(6, value));
    }

    void processVector2(const nstl::vector<InitialSnapshot>& value, int param)
    {
      handler->Go(handler->Call(22, value, param));
    }

    void processVectorWithDoubles(const nstl::vector<double>& value)
    {
      handler->Go(handler->Call(7, value));
    }

    void processBool(bool value)
    {
      handler->Go(handler->Call(8, value));
    }

    void processShort(short value)
    {
      handler->Go(handler->Call(9, value));
    }

    int processIntWithReturnValueInt(int value)
    {
      rpc::Transaction* transaction = handler->Call(10, value);
      rpc::ICallRoutine& return_call = transaction->RegisterSynchronousCall(transaction->GetInfo());  
      handler->Go(transaction);
      //va_list v = return_call.Wait();
      rpc::VArgList v = return_call.Wait();
      return va_arg(v, int);
    }

    template <typename T>
    void processIntWithReturnValueIntAsync(int value, T* object, void (T::*reply)(int result)) 
    {
      rpc::Transaction* transaction = handler->Call(11, value);
      transaction->RegisterAsyncCall(transaction->GetInfo(), new rpc::FunctorNoContext<T, int>(object, reply));  
      handler->Go(transaction);
    }

    template <typename T>
    void processDoubleWithReturnValueDoubleAsync(double value, T* object, void (T::*func)(double result)) 
    {
      rpc::Transaction* transaction = handler->Call(12, value);
      transaction->RegisterAsyncCall(transaction->GetInfo(), new rpc::FunctorNoContext<T, double>(object, func));  
      handler->Go(transaction);
    }

    template <typename T>
    void processIntWithReturnValueIntAsyncLong(int value, T* object, void (T::*func)(int result)) 
    {
      rpc::Transaction* transaction = handler->Call(13, value);
      transaction->RegisterAsyncCall(transaction->GetInfo(), new rpc::FunctorNoContext<T, int>(object, func));  
      handler->Go(transaction);
    }
    
    template <typename T, typename C>
    void processIntWithReturnValueIntAsyncLong(int value, T* object, void (T::*func)(int result, C context, rpc::CallStatus status), const C& context, float timeout=0.f) 
    {
      rpc::Transaction* transaction = handler->Call(13, value);
      transaction->RegisterAsyncCall(transaction->GetInfo(), new rpc::FunctorContext<T, int, C>(object, func, context), timeout);  
      handler->Go(transaction);
    }

    void processStruct(const SimpleStruct& value0)
    {
      handler->Go(handler->Call(14, value0));
    }

    void processNSTLString(const nstl::string& value)
    {
      handler->Go(handler->Call(15, value));
    }

    void processLongLong(long long value)
    {
      handler->Go(handler->Call(16, value));
    }

    void processMyType(MyType value)
    {
      handler->Go(handler->Call(17, value));
    }

    void processMyEnum(MyEnum value)
    {
      handler->Go(handler->Call(18, (int)value));
    }

    template <typename T>
    void processReturnStructRef(T* object, void (T::*func)( const SimpleStruct& result ) )
    {
      rpc::Transaction* transaction = handler->Call( 19 );
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::RefFunctorNoContext<T, const SimpleStruct>(object, func) );
      handler->Go(transaction);
    }

    template <typename T>
    void processReturnStruct(SimpleStruct o, T* object, void (T::*func)( SimpleStruct result ))
    {
      rpc::Transaction* transaction = handler->Call( 20, o );
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorNoContext<T, SimpleStruct>(object, func) );
      handler->Go(transaction);
    }

    void processRecieveTime()
    {
      handler->Go(handler->Call(21));
    }

    rpc::INode* GetNode(int index) { return GetHandler()->GetNode(index); }
    rpc::INode* GetNode(const char* name) { return GetHandler()->GetNode(name); }
    virtual rpc::IUpdateCallback* GetUpdateCallback() { StrongMT<rpc::IRemoteEntity> _parent = parent.Lock(); return handler->GetUpdateCallback(_parent); }
    virtual void SetParent(rpc::IRemoteEntity* _parent) { parent = _parent; }
    rpc::EntityHandler* GetHandler() { return handler; }
  protected:
    friend class rpc::Gate;
    virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RComplexRabbit::ID(), RComplexRabbit::CRC32}, handler->GetGUID() }; return info; }
  private:
    StrongMT<rpc::EntityHandler> handler;
    rpc::IEntityMap* xxx;
    WeakMT<rpc::IRemoteEntity> parent;
  };
  static rpc::SimpleRemoteEntityFactory<test::RComplexRabbit> factory_test_RComplexRabbit;

  class LComplexRabbit : public rpc::ILocalEntity, BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_2( LComplexRabbit, rpc::ILocalEntity, BaseObjectMT );
  public:
    LComplexRabbit() {}
    LComplexRabbit(test::ComplexRabbit* xxx, rpc::IEntityMap* _entityMap, rpc::ILocalEntityFactory* _factory=0):
    xxx(xxx),
    entityMap(_entityMap),
    factory(_factory)
    {
    }

    ~LComplexRabbit() 
    {
      if (factory)
      {
        factory->Destroy(this);
      }
    }

    virtual rpc::CallResult::Enum Call(const rpc::MethodCallHeader& call, rpc::MethodCall& resultCall, rpc::Arguments& args, const byte* paramsData, int _paramsSize)
    {
      static const rpc::MethodInfo methods[] = 
      {
        { "test::ComplexRabbit::process", 0, false, rpc::GetMethodCode(&test::ComplexRabbit::process) },
        { "test::ComplexRabbit::processInt", 1, false, rpc::GetMethodCode(&test::ComplexRabbit::processInt) },
        { "test::ComplexRabbit::processFloat", 1, false, rpc::GetMethodCode(&test::ComplexRabbit::processFloat) },
        { "test::ComplexRabbit::processDouble", 1, false, rpc::GetMethodCode(&test::ComplexRabbit::processDouble) },
        { "test::ComplexRabbit::processFloatInt", 2, false, rpc::GetMethodCode(&test::ComplexRabbit::processFloatInt) },
        { "test::ComplexRabbit::processString", 1, false, rpc::GetMethodCode(&test::ComplexRabbit::processString) },
        { "test::ComplexRabbit::processVector", 1, false, rpc::GetMethodCode(&test::ComplexRabbit::processVector) },
        { "test::ComplexRabbit::processVectorWithDoubles", 1, false, rpc::GetMethodCode(&test::ComplexRabbit::processVectorWithDoubles) },
        { "test::ComplexRabbit::processBool", 1, false, rpc::GetMethodCode(&test::ComplexRabbit::processBool) },
        { "test::ComplexRabbit::processShort", 1, false, rpc::GetMethodCode(&test::ComplexRabbit::processShort) },
        { "test::ComplexRabbit::processIntWithReturnValueInt", 1, false, rpc::GetMethodCode(&test::ComplexRabbit::processIntWithReturnValueInt) },
        { "test::ComplexRabbit::processIntWithReturnValueIntAsync", 1, false, rpc::GetMethodCode(&test::ComplexRabbit::processIntWithReturnValueIntAsync) },
        { "test::ComplexRabbit::processDoubleWithReturnValueDoubleAsync", 1, false, rpc::GetMethodCode(&test::ComplexRabbit::processDoubleWithReturnValueDoubleAsync) },
        { "test::ComplexRabbit::processIntWithReturnValueIntAsyncLong", 1, false, rpc::GetMethodCode(&test::ComplexRabbit::processIntWithReturnValueIntAsyncLong) },
        { "test::ComplexRabbit::processStruct", 1, false, rpc::GetMethodCode(&test::ComplexRabbit::processStruct) },
        { "test::ComplexRabbit::processNSLTString", 1, false, rpc::GetMethodCode(&test::ComplexRabbit::processNSLTString) },
        { "test::ComplexRabbit::processLongLong", 1, false, rpc::GetMethodCode(&test::ComplexRabbit::processLongLong) },
        { "test::ComplexRabbit::processMyType", 1, false, rpc::GetMethodCode(&test::ComplexRabbit::processMyType) },
        { "test::ComplexRabbit::processMyEnum", 1, false, rpc::GetMethodCode(&test::ComplexRabbit::processMyEnum) },
        { "test::ComplexRabbit::processReturnStructRef", 0, false, rpc::GetMethodCode(&test::ComplexRabbit::processReturnStructRef) },
        { "test::ComplexRabbit::processReturnStruct", 1, false, rpc::GetMethodCode(&test::ComplexRabbit::processReturnStruct) },
        { "test::ComplexRabbit::processRecieveTime", 1, true, rpc::GetMethodCode(&test::ComplexRabbit::processRecieveTime) },
        { "test::ComplexRabbit::processVector2", 2, false, rpc::GetMethodCode(&test::ComplexRabbit::processVector2) },
      };
      if (call.id >= sizeof(methods)/sizeof(rpc::MethodInfo) || call.id < 0)
      {
        return rpc::CallResult::WrongMethodId;
      }
      rpc::MethodCallStack stack = rpc::FillStack(call, args, paramsData, _paramsSize, methods[call.id]);
      if (stack.isValid)
      {
        return vcall(call.id, resultCall, stack)?rpc::CallResult::OK : rpc::CallResult::DataCorruption;
      }
      return rpc::CallResult::DataCorruption;
    }

    virtual void Publish()
    {
    }

    typedef void (ComplexRabbit::*TprocessVector)(const nstl::vector<int>* v);
    typedef void (ComplexRabbit::*TprocessVectorWithDoubles)(const nstl::vector<double>* v);
    typedef void (ComplexRabbit::*TprocessStruct)(const SimpleStruct* _s);
    typedef void (ComplexRabbit::*TprocessNSLTString)(const nstl::string* value);
    typedef SimpleStruct (ComplexRabbit::*TprocessReturnStruct)(const SimpleStruct* _s);
    typedef void (ComplexRabbit::*TprocessRecieveTime)(const NHPTimer::STime* value);
    typedef void (ComplexRabbit::*TprocessVector2)(const nstl::vector<InitialSnapshot>* v, int param);

    bool vcall(byte methodId, rpc::MethodCall& call, rpc::MethodCallStack& stack) 
    {
      bool popResult = true;
      switch (methodId)
      {
      case 0: rpc::VCall(stack, xxx.Get(), &test::ComplexRabbit::process, popResult); break;   
      case 1: rpc::VCall(stack, xxx.Get(), &test::ComplexRabbit::processInt, popResult); break;   
      case 2: rpc::VCall(stack, xxx.Get(), &test::ComplexRabbit::processFloat, popResult); break;   
      case 3: rpc::VCall(stack, xxx.Get(), &test::ComplexRabbit::processDouble, popResult); break;   
      case 4: rpc::VCall(stack, xxx.Get(), &test::ComplexRabbit::processFloatInt, popResult); break;   
      case 5: rpc::VCall(stack, xxx.Get(), &test::ComplexRabbit::processString, popResult); break;   
      case 6: rpc::VCall(stack, xxx.Get(), TprocessVector(&test::ComplexRabbit::processVector), popResult); break;
      case 7: rpc::VCall(stack, xxx.Get(), TprocessVectorWithDoubles(&test::ComplexRabbit::processVectorWithDoubles), popResult); break;
      case 8: rpc::VCall(stack, xxx.Get(), &test::ComplexRabbit::processBool, popResult); break;   
      case 9: rpc::VCall(stack, xxx.Get(), &test::ComplexRabbit::processShort, popResult); break;   
      case 10: 
        {
          int result = rpc::VCall(stack, xxx.Get(), &test::ComplexRabbit::processIntWithReturnValueInt, popResult); 
          call.Prepare(10).Push(result);
        }
        break;
      case 11: 
        {
          int result = rpc::VCall(stack, xxx.Get(), &test::ComplexRabbit::processIntWithReturnValueIntAsync, popResult);
          call.Prepare(11).Push(result);
        }
        break;
      case 12: 
        {
          double result = rpc::VCall(stack, xxx.Get(), &test::ComplexRabbit::processDoubleWithReturnValueDoubleAsync, popResult);
          call.Prepare(12).Push(result);
        }
        break;
      case 13: 
        {
          int result = rpc::VCall(stack, xxx.Get(), &test::ComplexRabbit::processIntWithReturnValueIntAsyncLong, popResult); 
          call.Prepare(13).Push(result);
        }
        break;
      case 14: rpc::VCall(stack, xxx.Get(), TprocessStruct(&test::ComplexRabbit::processStruct), popResult); break;
      case 15: rpc::VCall(stack, xxx.Get(), TprocessNSLTString(&test::ComplexRabbit::processNSLTString), popResult); break;
      case 16: 
        {
          rpc::VCall(stack, xxx.Get(), &test::ComplexRabbit::processLongLong, popResult);
        }
        break;
      case 17: rpc::VCall(stack, xxx.Get(), &test::ComplexRabbit::processMyType, popResult); break;
      case 18: rpc::VCall(stack, xxx.Get(), &test::ComplexRabbit::processMyEnum, popResult); break;
      case 19:
        {
          const SimpleStruct& result = rpc::VCall(stack, xxx.Get(), &test::ComplexRabbit::processReturnStructRef, popResult);
          call.Prepare( 19 ).Push( result );
        }
        break;
      case 20:
        {
          SimpleStruct result = rpc::VCall(stack, xxx.Get(), TprocessReturnStruct(&test::ComplexRabbit::processReturnStruct), popResult);
          call.Prepare( 20 ).PushByValue( result );
        }
        break;
      case 21: rpc::VCall(stack, xxx.Get(), TprocessRecieveTime(&test::ComplexRabbit::processRecieveTime), popResult); break;
      case 22: rpc::VCall(stack, xxx.Get(), TprocessVector2(&test::ComplexRabbit::processVector2), popResult); break;
      default:
        popResult = false;
        break;
      }
      return popResult;
    }

    virtual int GetMemberIndex(const void*) { return -1; }
    virtual void* _Get(uint classId) { return (classId == rpc::_GetId("test::ComplexRabbit", rpc::GeneratedType) ) ? xxx : 0; }
    virtual uint GetClassCrc() const { return 0xBAADF00D; }
  private:
    StrongMT<test::ComplexRabbit> xxx;
    rpc::ILocalEntityFactory* factory;
    rpc::IEntityMap* entityMap;
  };

  class RSimpleRabbit : public rpc::IRemoteEntity, public BaseObjectMT 
  {
    NI_DECLARE_REFCOUNT_CLASS_2( RSimpleRabbit, rpc::IRemoteEntity, BaseObjectMT );
  public:
    RPC_INFO("test::SimpleRabbit", 0xBAADF00A);

    RSimpleRabbit():handler(0){}

    RSimpleRabbit(rpc::EntityHandler* handler, rpc::IRemoteEntity* _parent):
    handler(handler),
    parent(_parent)
    {
    }

    ~RSimpleRabbit()
    {
      if (handler)
      {
        handler->OnDestruct(*this);
        handler = 0;
      }
    }

    virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RSimpleRabbit::ID(), RSimpleRabbit::CRC32}, handler->GetGUID() }; return info; }
    inline bool IsUpdated() const { return handler->IsUpdated(); }

    void process()
    {
      handler->Go(handler->Call(0));
    }

    void processSnapshot(const InitialSnapshot& msg)
    {
      handler->Go(handler->Call(1, msg));
    }

    void processTwoSnapshots(const InitialSnapshot& _msg0, const InitialSnapshot& _msg1)
    {
      handler->Go(handler->Call(2, _msg0, _msg1));
    }

    template <typename T>
    void processSnapshotReturnSnapshot(const InitialSnapshot& _msg, T* object, void (T::*func)(const InitialSnapshot& result) )
    {
      rpc::Transaction* transaction = handler->Call(3, _msg);
      transaction->RegisterAsyncCall(transaction->GetInfo(), new rpc::RefFunctorNoContext<T, const InitialSnapshot>(object, func));  
      handler->Go(transaction);
    }

    void processApi()
    {
      handler->Go(handler->Call(4));
    }

    void processVectorsOfSnapshots(const nstl::vector<InitialSnapshot>& _vmsg)
    {
      handler->Go(handler->Call(5, _vmsg));
    }

    template <typename T>
    void processReturnVectorOfBytes(T* object, void (T::*func)( const nstl::vector<byte>& result) )
    {
      rpc::Transaction* transaction = handler->Call(6);
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::RefFunctorNoContext<T, const nstl::vector<byte> >(object, func) );
      handler->Go(transaction);
    }

    void processByte(byte value)
    {
      handler->Go(handler->Call(7, value));
    }

    void processRemoteApi(test::RRemoteApi* api, bool save)
    {
      handler->Go(handler->Call(8, api, save));
    }

    void processVectorOfStrings(const nstl::vector<nstl::string>& _vs)
    {
      handler->Go(handler->Call(9, _vs));
    }

    void processVectorOfWStrings(const nstl::vector<nstl::wstring>& _wvs)
    {
      handler->Go(handler->Call(10, _wvs));
    }

    void processWString( const nstl::wstring& value )
    {
      handler->Go(handler->Call(11, value));
    }

    template <typename T>
    void GetRRemoteApi(T* object, void (T::*func)(test::RRemoteApi* result)) 
    {
      rpc::Transaction* transaction = handler->Call(12);
      transaction->RegisterAsyncCall(transaction->GetInfo(), new rpc::FunctorNoContext<T, test::RRemoteApi*>(object, func));  
      handler->Go(transaction);
    }

    template <typename T>
    void GetLocalRemoteApi(T* object, void (T::*func)(test::RRemoteApi* result)) 
    {
      rpc::Transaction* transaction = handler->Call(13);
      transaction->RegisterAsyncCall(transaction->GetInfo(), new rpc::FunctorNoContext<T, test::RRemoteApi*>(object, func));  
      handler->Go(transaction);
    }

    template <typename T>
    void processWithReturnValueNSTLStringAsync( T* object, void (T::*func)( const nstl::string& result ) )
    {
      rpc::Transaction* transaction = handler->Call(14);
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::RefFunctorNoContext<T, const nstl::string>(object, func) );
      handler->Go(transaction);
    }

    void processLocalRemoteApi(test::RRemoteApi* api)
    {
      handler->Go(handler->Call(15, api));
    }

    void processFixedVector(const FixedVector<int, 100>& _vs)
    {
      handler->Go(handler->Call(16, _vs));
    }

    rpc::ECallResult::Enum processMemoryBlock(const rpc::MemoryBlock& _b)
    {
      return handler->Go(handler->Call(17, _b));
    }

    void processMemoryBlockVector(nstl::vector<rpc::MemoryBlock>& _blocks)
    {
      handler->Go(handler->Call(18, _blocks));
    }
    void SetSimpleReplicated(test::RSimpleReplicated* api)
    {
      handler->Go(handler->Call(19, api));
    }

    template <typename T>
    void getStatus(T* object, void (T::*func)(test::SMatchmakingStatus result) )
    {
      rpc::Transaction* transaction = handler->Call(20);
      transaction->RegisterAsyncCall(transaction->GetInfo(), new rpc::FunctorNoContext<T, const test::SMatchmakingStatus>(object, func));  
      handler->Go(transaction);
    }

    void processSimpleRabbit(test::RSimpleRabbit* api)
    {
      handler->Go(handler->Call(21, api));
    }

    template <typename T>
    void Ping(const nstl::vector<byte>& value, T* object, void (T::*func)(const nstl::vector<byte>& result) )
    {
      rpc::Transaction* transaction = handler->Ping(value);
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::RefFunctorNoContext<T, const nstl::vector<byte> >(object, func) );
      handler->Go(transaction);
    }

    virtual rpc::IUpdateCallback* GetUpdateCallback() { StrongMT<rpc::IRemoteEntity> _parent = parent.Lock(); return handler->GetUpdateCallback(_parent); }
    virtual void SetParent(rpc::IRemoteEntity* _parent) { parent = _parent; }
    rpc::EntityHandler* GetHandler() { return handler; }
    protected:
      friend class rpc::Gate;
    private:
      StrongMT<rpc::EntityHandler> handler;
      rpc::IEntityMap* xxx;
      WeakMT<rpc::IRemoteEntity> parent;
  };
  static rpc::SimpleRemoteEntityFactory<test::RSimpleRabbit> factory_test_RSimpleRabbit;


  class LSimpleRabbit : public rpc::ILocalEntity, public BaseObjectMT
  {
    typedef void (SimpleRabbit::*TprocessSnapshot)(const InitialSnapshot* _msg);
    typedef void (SimpleRabbit::*TprocessTwoSnapshots)(const InitialSnapshot* _msg0, const InitialSnapshot* _msg1);
    typedef const InitialSnapshot& (SimpleRabbit::*TprocessSnapshotReturnSnapshot)(const InitialSnapshot* _msg);
    typedef void (SimpleRabbit::*TprocessVectorsOfSnapshots)(const nstl::vector<InitialSnapshot>* _vmsg);
    typedef void (SimpleRabbit::*TprocessVectorsOfStrings)(const nstl::vector<nstl::string>* _vmsg);
    typedef void (SimpleRabbit::*TprocessVectorsOfWStrings)(const nstl::vector<nstl::wstring>* _vmsg);
    typedef void (SimpleRabbit::*TprocessWString)(const nstl::wstring* _msg);
    typedef void (SimpleRabbit::*TprocessFixedVector)(const FixedVector<int, 10>* _vmsg);
    typedef void (SimpleRabbit::*TprocessMemoryBlock)(const rpc::MemoryBlock* _msg);
    typedef void (SimpleRabbit::*TprocessMemoryBlockVector)(const nstl::vector<rpc::MemoryBlock>* _msg);

    NI_DECLARE_REFCOUNT_CLASS_2(LSimpleRabbit, rpc::ILocalEntity, BaseObjectMT);
  public:

    LSimpleRabbit() {}
    LSimpleRabbit(test::SimpleRabbit* xxx, rpc::IEntityMap* _entityMap, rpc::ILocalEntityFactory* _factory=0): // TODO: move to SObj here
    xxx(xxx),
    factory(_factory)
    {
    }

    ~LSimpleRabbit() 
    {
      if (factory)
      {
        factory->Destroy(this);
      }
    }

    virtual rpc::CallResult::Enum Call(const rpc::MethodCallHeader& call, rpc::MethodCall& resultCall, rpc::Arguments& args, const byte* paramsData, int _paramsSize)
    {
      static const rpc::MethodInfo methods[] = 
      {
        { "test::SimpleRabbit::process", 0, rpc::GetMethodCode(&test::SimpleRabbit::process) }, 
        { "test::SimpleRabbit::processSnapshot", 1, rpc::GetMethodCode(&test::SimpleRabbit::processSnapshot) }, 
        { "test::SimpleRabbit::processTwoSnapshots", 2, rpc::GetMethodCode(&test::SimpleRabbit::processTwoSnapshots) }, 
        { "test::SimpleRabbit::processSnapshotReturnSnapshot", 1, rpc::GetMethodCode(&test::SimpleRabbit::processSnapshotReturnSnapshot) }, 
        { "test::SimpleRabbit::processApi", 0, rpc::GetMethodCode(&test::SimpleRabbit::processApi) }, 
        { "test::SimpleRabbit::processVectorsOfSnapshots", 1, rpc::GetMethodCode(&test::SimpleRabbit::processVectorsOfSnapshots) }, 
        { "test::SimpleRabbit::processReturnVectorOfBytes", 0, rpc::GetMethodCode(&test::SimpleRabbit::processReturnVectorOfBytes) }, 
        { "test::SimpleRabbit::processByte", 1, rpc::GetMethodCode(&test::SimpleRabbit::processByte) }, 
        { "test::SimpleRabbit::processRemoteApi", 2, rpc::GetMethodCode(&test::SimpleRabbit::processRemoteApi) }, 
        { "test::SimpleRabbit::processVectorOfStrings", 1, rpc::GetMethodCode(&test::SimpleRabbit::processVectorOfStrings) }, 
        { "test::SimpleRabbit::processVectorOfWStrings", 1, rpc::GetMethodCode(&test::SimpleRabbit::processVectorOfWStrings) }, 
        { "test::SimpleRabbit::processWString", 1, rpc::GetMethodCode(&test::SimpleRabbit::processWString) }, 
        { "test::SimpleRabbit::GetRRemoteApi", 0, rpc::GetMethodCode(&test::SimpleRabbit::GetRRemoteApi) }, 
        { "test::SimpleRabbit::GetLocalRemoteApi", 0, rpc::GetMethodCode(&test::SimpleRabbit::GetLocalRemoteApi) }, 
        { "test::SimpleRabbit::processWithReturnValueNSTLStringAsync", 0, rpc::GetMethodCode(&test::SimpleRabbit::processWithReturnValueNSTLStringAsync) },  
        { "test::SimpleRabbit::processLocalRemoteApi", 1, rpc::GetMethodCode(&test::SimpleRabbit::processLocalRemoteApi) }, 
        { "test::SimpleRabbit::processFixedVector", 1, rpc::GetMethodCode(&test::SimpleRabbit::processFixedVector) }, 
        { "test::SimpleRabbit::processMemoryBlock", 1, rpc::GetMethodCode(&test::SimpleRabbit::processMemoryBlock) }, 
        { "test::SimpleRabbit::processMemoryBlockVector", 1, rpc::GetMethodCode(&test::SimpleRabbit::processMemoryBlockVector) }, 
        { "test::SimpleRabbit::SetSimpleReplicated", 1, rpc::GetMethodCode(&test::SimpleRabbit::SetSimpleReplicated) }, 
        { "test::SimpleRabbit::getStatus", 0, rpc::GetMethodCode(&test::SimpleRabbit::getStatus) }, 
        { "test::SimpleRabbit::processSimpleRabbit", 1, rpc::GetMethodCode(&test::SimpleRabbit::processSimpleRabbit) }, 
      };
      if (call.id >= sizeof(methods)/sizeof(rpc::MethodInfo) || call.id < 0)
      {
        return rpc::CallResult::WrongMethodId;
      }
      rpc::MethodCallStack stack = rpc::FillStack(call, args, paramsData, _paramsSize, methods[call.id]);
      if (stack.isValid)
      {
        return vcall(call.id, resultCall, stack)?rpc::CallResult::OK : rpc::CallResult::DataCorruption;
      }
      return rpc::CallResult::DataCorruption;
    }
    virtual void Publish()
    {
    }
    bool vcall(byte methodId, rpc::MethodCall& call, rpc::MethodCallStack& stack) 
    {
      bool popResult = true;
      switch (methodId)
      {
      case 0: rpc::VCall(stack, xxx.Get(), &test::SimpleRabbit::process, popResult); break;
      case 1: rpc::VCall(stack, xxx.Get(), TprocessSnapshot(&test::SimpleRabbit::processSnapshot), popResult); break;
      case 2: rpc::VCall(stack, xxx.Get(), TprocessTwoSnapshots(&test::SimpleRabbit::processTwoSnapshots), popResult); break;
      case 3: 
        {
          const InitialSnapshot& result = VCall(stack, xxx.Get(), TprocessSnapshotReturnSnapshot(&test::SimpleRabbit::processSnapshotReturnSnapshot), popResult);
          call.Prepare(3).Push(result);
        }
        break;   
      case 4: rpc::VCall(stack, xxx.Get(), &test::SimpleRabbit::processApi, popResult); break;
      case 5: rpc::VCall(stack, xxx.Get(), TprocessVectorsOfSnapshots(&test::SimpleRabbit::processVectorsOfSnapshots), popResult); break;
      case 6:
        {
          const nstl::vector<byte>& result = rpc::VCall(stack, xxx.Get(), &test::SimpleRabbit::processReturnVectorOfBytes, popResult);
          call.Prepare( 6 ).Push( result );
        }
        break;
      case 7: rpc::VCall(stack, xxx.Get(), &test::SimpleRabbit::processByte, popResult); break;
      case 8: rpc::VCall(stack, xxx.Get(), &test::SimpleRabbit::processRemoteApi, popResult); break;
      case 9: rpc::VCall(stack, xxx.Get(), TprocessVectorsOfStrings(&test::SimpleRabbit::processVectorOfStrings), popResult); break;
      case 10: rpc::VCall(stack, xxx.Get(), TprocessVectorsOfWStrings(&test::SimpleRabbit::processVectorOfWStrings), popResult); break;
      case 11: rpc::VCall(stack, xxx.Get(), TprocessWString(&test::SimpleRabbit::processWString), popResult); break;
      case 12: 
        {
          test::RRemoteApi* result = VCall(stack, xxx.Get(), &test::SimpleRabbit::GetRRemoteApi, popResult);
          call.Prepare(12).Push(result);
        }
        break;   
      case 13: 
        {
          test::RRemoteApi* result = VCall(stack, xxx.Get(), &test::SimpleRabbit::GetLocalRemoteApi, popResult);
          call.Prepare(13).Push(result);
        }
        break;   
      case 14: 
        {
          const nstl::string& result = rpc::VCall( stack, xxx.Get(), &test::SimpleRabbit::processWithReturnValueNSTLStringAsync, popResult); 
          call.Prepare(14).Push(result);
        }
        break;
      case 15: rpc::VCall(stack, xxx.Get(), &test::SimpleRabbit::processLocalRemoteApi, popResult); break;
      case 16: rpc::VCall(stack, xxx.Get(), TprocessFixedVector(&test::SimpleRabbit::processFixedVector), popResult); break;
      case 17: rpc::VCall(stack, xxx.Get(), TprocessMemoryBlock(&test::SimpleRabbit::processMemoryBlock), popResult); break;
      case 18: rpc::VCall(stack, xxx.Get(), TprocessMemoryBlockVector(&test::SimpleRabbit::processMemoryBlockVector), popResult); break;
      case 19: rpc::VCall(stack, xxx.Get(), &test::SimpleRabbit::SetSimpleReplicated, popResult); break;
      case 20: 
        {
          test::SMatchmakingStatus result = VCall(stack, xxx.Get(), &test::SimpleRabbit::getStatus, popResult);
          call.Prepare(20).PushByValue(result);
        }
        break;   
      case 21: rpc::VCall(stack, xxx.Get(), &test::SimpleRabbit::processSimpleRabbit, popResult); break;
      default:
        popResult = false;
        break;
      }
      return popResult;
    }

    virtual int GetMemberIndex(const void*) { return -1; }
    virtual void* _Get(uint classId) { return (classId == rpc::_GetId("test::SimpleRabbit", rpc::GeneratedType)) ? xxx : 0; }
    virtual uint GetClassCrc() const { return 0xBAADF00A; }
  private:
    StrongMT<test::SimpleRabbit> xxx;
    rpc::ILocalEntityFactory* factory;
  };

  class RBadCrc32Class : public rpc::IRemoteEntity, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_2( RBadCrc32Class, rpc::IRemoteEntity, BaseObjectMT )
  public:
    RPC_INFO("test::BadCrc32Class", 0xBAADF00A);

    RBadCrc32Class():handler(0) {}

    RBadCrc32Class(rpc::EntityHandler* handler, rpc::IRemoteEntity* _parent):
    handler(handler),
    parent(_parent)
    {
    }

    ~RBadCrc32Class()
    {
      if (handler)
      {
        handler->OnDestruct(*this);
        handler = 0;
      }
    }

    void process()
    {
      handler->Go(handler->Call(0));
    }
    virtual rpc::IUpdateCallback* GetUpdateCallback() { StrongMT<rpc::IRemoteEntity> _parent = parent.Lock(); return handler->GetUpdateCallback(_parent); }
    virtual void SetParent(rpc::IRemoteEntity* _parent) { parent = _parent; }
protected:
    friend class EntityHandler;
    virtual rpc::EntityHandler* GetHandler() { return handler; } 
    virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RBadCrc32Class::ID(), RBadCrc32Class::CRC32}, handler->GetGUID() }; return info; }

  private:
    StrongMT<rpc::EntityHandler> handler;
    rpc::IEntityMap* xxx;
    WeakMT<rpc::IRemoteEntity> parent;
  };

  static rpc::SimpleRemoteEntityFactory<test::RBadCrc32Class> factory_test_RBadCrc32Class;


  class LBadCrc32Class : public rpc::ILocalEntity, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_2(LBadCrc32Class, rpc::ILocalEntity, BaseObjectMT);
  public:

    LBadCrc32Class() {}
    LBadCrc32Class(test::BadCrc32Class* xxx, rpc::IEntityMap* entityMap, rpc::ILocalEntityFactory* _factory=0): // TODO: move to SObj here
    xxx(xxx),
    factory(_factory)
    {
    }

    ~LBadCrc32Class()
    {
      if (factory)
      {
        factory->Destroy(this);
        delete xxx;
      }
    }

    virtual rpc::CallResult::Enum Call(const rpc::MethodCallHeader& call, rpc::MethodCall& resultCall, rpc::Arguments& args, const byte* paramsData, int _paramsSize)
    {
      static const rpc::MethodInfo methods[] = 
      {
        { "test::BadCrc32Class::process", 0, rpc::GetMethodCode(&test::BadCrc32Class::process) }, 
      };
      if (call.id >= sizeof(methods)/sizeof(rpc::MethodInfo) || call.id < 0)
      {
        return rpc::CallResult::WrongMethodId;
      }
      rpc::MethodCallStack stack = rpc::FillStack(call, args, paramsData, _paramsSize, methods[call.id]);
      if (stack.isValid)
      {
        return vcall(call.id, resultCall, stack)?rpc::CallResult::OK : rpc::CallResult::DataCorruption;
      }
      return rpc::CallResult::DataCorruption;
    }    
    virtual void Publish()
    {
    }
    bool vcall(byte methodId, rpc::MethodCall& call, rpc::MethodCallStack& stack) 
    {
      bool popResult = true;
      switch (methodId)
      {
      case 0: rpc::VCall(stack, xxx, &test::BadCrc32Class::process, popResult); break;
      default:
        popResult = false;
        break;
      }
      return popResult;
    }

    virtual int GetMemberIndex(const void*) { return -1; }
    virtual void* _Get(uint classId) { return (classId == rpc::_GetId("test::BadCrc32Class", rpc::GeneratedType)) ? xxx : 0; }
    virtual uint GetClassCrc() const { return 0xAAAAAAAA; }  // bad crc of class 
  private:
    test::BadCrc32Class* xxx;
    rpc::ILocalEntityFactory* factory;
  };

} // test
NI_DEFINE_REFCOUNT(test::RBadCrc32Class);

struct ComplexRabbitFactory : rpc::ILocalEntityFactory
{
  rpc::ILocalEntity* Create(const rpc::LocalEntityCreationInfo& entityInfo, rpc::Arguments& args, rpc::IEntityMap* entityMap)
  {
    return new test::LComplexRabbit(new test::ComplexRabbit, entityMap, this);
  }
  virtual rpc::ILocalEntity* Create(uint classId, void* value, rpc::IEntityMap* entityMap) { 
    return new test::LComplexRabbit((test::ComplexRabbit*)value, entityMap);
  }
};
static ComplexRabbitFactory factory_ComplexRabbit;
static rpc::CreationEntry entryTestComplexRabbit(rpc::GetId<test::ComplexRabbit>(), factory_ComplexRabbit);


struct SimpleRabbitFactory : rpc::ILocalEntityFactory
{
  rpc::ILocalEntity* Create(const rpc::LocalEntityCreationInfo& entityInfo, rpc::Arguments& args, rpc::IEntityMap* entityMap)
  {
    test::SimpleRabbit* r = 0;
    bool popResult = true;
    if (0 == entityInfo.paramsCount)
    {
      r = new test::SimpleRabbit;
    } else if (1 == entityInfo.paramsCount) 
    {
      r = new test::SimpleRabbit(args.Pop<short>(popResult));
    }  else if (2 == entityInfo.paramsCount) 
    {
      test::RRemoteApi* api = args.PopEntity<test::RRemoteApi>(popResult);
      short value = args.Pop<short>(popResult);
      r = new test::SimpleRabbit(api, value);
    } else if (4 == entityInfo.paramsCount) 
    {
      test::RRemoteApi* api = args.PopEntity<test::RRemoteApi>(popResult);
      short value = args.Pop<short>(popResult);
      r = new test::SimpleRabbit(api, value);
    }
    NI_ASSERT(r, "Class implementation should be created");
    infos.push_back(entityInfo);
    return new test::LSimpleRabbit(r, entityMap, this);
  }
  nstl::vector<rpc::LocalEntityCreationInfo> infos;
};
static SimpleRabbitFactory factory_SimpleRabbit;
static rpc::CreationEntry entryTestSimpleRabbit(rpc::GetId<test::SimpleRabbit>(), factory_SimpleRabbit);

struct RemoteApiFactory : rpc::ILocalEntityFactory
{
  rpc::ILocalEntity* Create(const rpc::LocalEntityCreationInfo& entityInfo, rpc::Arguments& args, rpc::IEntityMap* entityMap)
  {
    return new test::LRemoteApi(new test::RemoteApi, entityMap, this);
  }
  rpc::ILocalEntity* Create(uint classId, void* entity, rpc::IEntityMap* entityMap) 
  { 
    return new test::LRemoteApi((test::RemoteApi*)entity, entityMap); 
  }

};

static RemoteApiFactory factory_RemoteApi;
static rpc::CreationEntry entryTestRemoteApi(rpc::GetId<test::RemoteApi>(), factory_RemoteApi);

struct BadCrc32ClassFactory : rpc::ILocalEntityFactory
{
  rpc::ILocalEntity* Create(const rpc::LocalEntityCreationInfo& entityInfo, rpc::Arguments& args, rpc::IEntityMap* entityMap)
  {
    return new test::LBadCrc32Class(new test::BadCrc32Class, entityMap, this);
  }
};
static BadCrc32ClassFactory factory_BadCrc32Class;
static rpc::CreationEntry entryBadCrc32Class(rpc::GetId<test::BadCrc32Class>(), factory_BadCrc32Class);

namespace rpc
{

rpc::ILocalEntity* CreateLocalEntity(test::ComplexRabbit* api, rpc::IEntityMap* entityMap)
{
  return new test::LComplexRabbit(api, entityMap);
}

rpc::ILocalEntity* CreateLocalEntity(test::SimpleRabbit* api, rpc::IEntityMap* entityMap)
{
  return new test::LSimpleRabbit(api, entityMap);
}

rpc::ILocalEntity* CreateLocalEntity(test::RemoteApi* api, rpc::IEntityMap* entityMap)
{
  return new test::LRemoteApi(api, entityMap);
}

rpc::ILocalEntity* CreateLocalEntity(test::BadCrc32Class* api, rpc::IEntityMap* entityMap)
{
  return new test::LBadCrc32Class(api, entityMap);
}


} // rpc


// end of autogenerated code

namespace test 
{

  REMOTE struct SimpleReplicated : BaseObjectMT
  {
    RPC_ID();
    NI_DECLARE_REFCOUNT_CLASS_1( SimpleReplicated, BaseObjectMT)
  public:
    SimpleReplicated()
    {
      i = 0;
      d = 0;
      s = 0;
      f = 0;
      b = 0;
      BoolVar = false;
      quat.x = 0;
      quat.y = 0;
      quat.z = 0;
      quat.w = 0;
    }
    SimpleReplicated(int value)
    {
      i = 888;
      d = 12;
      s = 443;
      f = 1.8f;
      b = 34;
      BoolVar = true;
      vi.push_back(76);
      vi.push_back(78);
      vd.push_back(16);
      vd.push_back(18);
      name = "Original";
      wname = L"OriginalW";
      ptr = new SimpleReplicated();
      test::InitialSnapshot s;
      s.serverTime = 999;
      snapshots.push_back(s);
    }

    REMOTE int i;
    REMOTE double d;
    REMOTE short s;
    REMOTE float f;
    REMOTE byte b;
    REMOTE bool BoolVar;
    REMOTE nstl::vector<int> vi;
    REMOTE nstl::vector<double> vd;
    REMOTE nstl::string name;
    REMOTE StrongMT<SimpleReplicated> ptr;
    REMOTE nstl::wstring wname;
    REMOTE CQuat quat;
    REMOTE nstl::vector<InitialSnapshot> snapshots;
  };

} // test
namespace test
{
  class LSimpleReplicated : public rpc::ILocalEntity, BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_2(LSimpleReplicated, rpc::ILocalEntity, BaseObjectMT);
  public:
    StrongMT<test::SimpleReplicated> xxx;

    LSimpleReplicated() {}
    LSimpleReplicated(test::SimpleReplicated* xxx, rpc::IEntityMap* entityMap, rpc::ILocalEntityFactory* _factory):
    xxx(xxx),
    factory(_factory)
    {
    }

    ~LSimpleReplicated()
    {
      if (factory)
      {
        factory->Destroy(this);
      }
    }

    virtual rpc::CallResult::Enum Call(const rpc::MethodCallHeader& call, rpc::MethodCall& resultCall, rpc::Arguments& args, const byte* paramsData, int _paramsSize)
    {
      return rpc::CallResult::DataCorruption;
    }
    virtual void Publish()
    {
    }
    bool vcall(byte methodId, rpc::MethodCall& call, rpc::MethodCallStack& stack) 
    {
      bool popResult = true;
      return popResult;
    }

    virtual bool vset(byte memberId, rpc::ArgReader& s) 
    {
      switch (memberId)
      {
      case 0: return s.Assign(xxx->i); 
      case 1: return s.Assign(xxx->d); 
      case 2: return s.Assign(xxx->s); 
      case 3: return s.Assign(xxx->f); 
      case 4: return s.Assign(xxx->BoolVar);
      case 5: return s.Assign(xxx->b); 
      case 6: return s.Assign(xxx->vi);
      case 7: return s.Assign(xxx->vd);
      case 8: return s.Assign(xxx->name); 
      case 9: return s.Assign(xxx->ptr); 
      case 10: return s.Assign(xxx->wname); 
      case 11: return s.Assign(xxx->quat); 
      case 12: return s.Assign(xxx->snapshots); 
      default:
        return false;
      }
    }

    virtual int GetMemberIndex(const void* memory) 
    { 
      if (&xxx->i == memory) return 0;
      if (&xxx->d == memory) return 1;
      if (&xxx->s == memory) return 2;
      if (&xxx->f == memory) return 3;
      if (&xxx->BoolVar == memory) return 4;
      if (&xxx->b == memory) return 5;
      if (&xxx->vi == memory) return 6;
      if (&xxx->vd == memory) return 7;
      if (&xxx->name == memory) return 8;
      if (&xxx->ptr == memory) return 9;
      if (&xxx->wname == memory) return 10;
      if (&xxx->quat == memory) return 11;
      if (&xxx->snapshots == memory) return 12;
      return -1;
    }

    virtual void* _Get(uint classId) { return (classId == rpc::_GetId("test::SimpleReplicated", rpc::GeneratedType)) ? xxx : 0; }
    virtual uint GetClassCrc() const { return 0xBAADF00C; }

    virtual void Update(rpc::ArgWriter* args)
    {
      args->Sync(0, xxx->i);
      args->Sync(1, xxx->d);
      args->Sync(2, xxx->s);
      args->Sync(3, xxx->f);
      args->Sync(4, xxx->BoolVar);
      args->Sync(5, xxx->b);
      args->Sync(6, xxx->vi);
      args->Sync(7, xxx->vd);
      args->Sync(8, xxx->name);
      args->Sync(9, xxx->ptr);
      args->Sync(10, xxx->wname);
      args->Sync(11, xxx->quat);
      args->Sync(12, xxx->snapshots);
    }
    rpc::ILocalEntityFactory* factory;
  };

  struct SimpleReplicatedFactory : rpc::ILocalEntityFactory
  {
    rpc::ILocalEntity* Create(const rpc::LocalEntityCreationInfo& entityInfo, rpc::Arguments& args, rpc::IEntityMap* entityMap)
    {
      test::SimpleReplicated* r = 0;
      if (0 == entityInfo.paramsCount)
      {
        r = new test::SimpleReplicated;
      } else
      if (1 == entityInfo.paramsCount)
      {
        bool result = true;
        r = new test::SimpleReplicated(args.Pop<int>(result));
      }

      NI_ASSERT(r, "Class implementation should be created");
      return new test::LSimpleReplicated(r, entityMap, this);
    }
    virtual rpc::ILocalEntity* Create(uint classId, void* value, rpc::IEntityMap* entityMap) 
    { 
      return new test::LSimpleReplicated((test::SimpleReplicated*)value, entityMap, this);
    }

  };

  static SimpleReplicatedFactory factory_SimpleReplicated;
  static rpc::CreationEntry entry_test_SimpleReplicated(rpc::GetId<test::SimpleReplicated>(), factory_SimpleReplicated);


} // test

namespace rpc
{

  template<> void RegisterRemoteFactory<class test::RComplexRabbit>(class test::RComplexRabbit *)
  {
    &test::factory_test_RComplexRabbit;
  }
  template<> void RegisterRemoteFactory<class test::RSimpleRabbit>(class test::RSimpleRabbit *)
  {
    &test::factory_test_RSimpleRabbit;
  }
  template<> void RegisterRemoteFactory<class test::RRemoteApi>(class test::RRemoteApi *)
  {
    &test::factory_test_RRemoteApi;
  }
  template<> void RegisterRemoteFactory<class test::RBadCrc32Class>(class test::RBadCrc32Class *)
  {
    &test::factory_test_RBadCrc32Class;
  }
  template<> void RegisterRemoteFactory<class test::RSimpleReplicated>(class test::RSimpleReplicated *)
  {
    &test::factory_test_RSimpleReplicated;
  }

}

void assertEquals(const char* m1, const char* m2)
{
  TS_ASSERT_EQUALS(nstl::string(m1), nstl::string(m2));
}
void assertEquals(const wchar_t* m1, const wchar_t* m2)
{
  TS_ASSERT_EQUALS(nstl::wstring(m1), nstl::wstring(m2));
}
// ограничение - количество методов в RPC классе <= 255
// ограничение - количество параметров в методе RPC класса <= 255 - 2 (destructor, constructor)
// ограничение - 32767 количество rpc классов 
// ограничение - размер сериализуемой структуры не больше чем ushort_MAX (65535)
// ограничение - размер структуры по значение  <= ushort_MAX (65535)

// TODO: +переменной количество параметров
// TODO: +синхронизация создания/удаления объектов
// TODO: +убрать запаковку через va_arg
// TODO: +простейшие типы параметров unsigned char, char, byte, short, const char*
// TODO: +удаление remote структур
// TODO: +указатели на remote структуры
// TODO: +вынести создание копий из служебных классов
// TODO: +вынести создание копий из служебных классов
// TODO: +конструктор с параметрами
// TODO: +переход на MethodCallInfo полностью
// TODO: +переход на корректные id (вместо индексов)
// TODO: +возврат параметров синхронная
// TODO: +возврат параметров асинхронная
// TODO: +сделать синхронизацию переменнных
// TODO: +генерация уникальных id для сущностей 
// TODO: +подсоединение с двух разных приложений
// TODO: +попробовать в реальном приложении
// TODO: +генерация entityId на сервере
// TODO: + корректная обработка отсутствующего типа
// TODO: +подумать насчет вызовов в две стороны
// TODO: +перейти на interlockedcounter вместо criticalsection
// TODO: +разобраться с тем какие нужны синхронизационные примитивы (interlocked)
// TODO: +убрать ограничение на размер стэка (корректно поддержать расчет необходимого размера)
// TODO: +объединить MemberSet и MethodCall
// TODO: +сделать автоматические фабрики создания IRemoteEntity по classId

// TODO: написать бумажку про RPC
// TODO: поддержка нарушения протокола
// TODO: callbacks на изменение клиентских данных
// TODO: поддержка создания объекта
// TODO: ref counting созданных серверных объектов
// TODO: асинхронное выполнение на host
// TODO: обработка случая асинхронного вызова и отваливания сервера

// TODO: поддержать ссылки на локальные структуры
// TODO: поддержать ссылки на удаленные структуры
// TODO: корректная обработка удаления объекта (+корректные обработки исключений)
// TODO: поддержать различие между Vector<int> и Vector<float>
// TODO: поддержать rpc через endianess
// TODO: рефакторинг создания сущностей - можно перевести на EntityHandler
// TODO: убрать различие между classId и classCrc

// ------ CURRENT FOCUS
// TODO: синхронизация Rданных от Oданных
// TODO: проверить случай присоединения (в случае передачи как параметра) к одной Lсущности а потом удаления ее с оригинального хоста (ref count)
// TODO: нужен ли reindex при работе с сущностью ?
// TODO: mirrored взаимодействия - продвижение вперед по шагам

class Test_SimpleTypesAsParams : public CxxTest::TestSuite, RPCMixin   
{
public:
  void test_DisconnectionWhileLocalApiProcessingCrash()
  {
    rpc::EnableLog(3);
    ManyToManyCase c;

    StrongMT<test::MockCorruptedPacketProcessor> root0P = new test::MockCorruptedPacketProcessor;
    StrongMT<test::MockCorruptedPacketProcessor> root1P = new test::MockCorruptedPacketProcessor;
    StrongMT<test::MockCorruptedPacketProcessor> leafP = new test::MockCorruptedPacketProcessor;

    StrongMT<test::RemoteApi> localApi = new test::RemoteApi;

    rpc::Gate& root0 = c.AddGate("root", root0P);
    rpc::Gate& root1 = c.AddGate("root", root1P);
    {
      rpc::Gate& leaf0 = c.AddGate("leaf0", leafP);
      c.ConnectGates(root0, leaf0);
      c.WaitForConnections();

      rpc::Node* a01 = c.GetNode(root0, leaf0);
      rpc::Node* a10 = c.GetNode(leaf0, root0);

      StrongMT<test::RSimpleRabbit> oobj = a01->Create<test::RSimpleRabbit>();
      while (oobj->GetHandler()->GetStatus() != rpc::Connected)
      {
        c.Poll();
      }
//      c.DisconnectGates(root0, leaf0);
 //     c.Poll();
  //    c.ConnectGates(root1, leaf0);
      oobj->processLocalRemoteApi(RemotePtr<test::RRemoteApi>(localApi));
      
      //TS_WAIT_FOR(localApi->processedCount == 1, 100);
      rpc::EnableLog(0);
    }
  }

  void test_Creation()
  {
    TwoNodesCase c;

    test::ComplexRabbit* lobject = c.cnode0->get<test::ComplexRabbit>(0);
    TS_ASSERT_EQUALS((test::ComplexRabbit*)0, lobject);

    StrongMT<test::RComplexRabbit> robject(c.cnode1->Create<test::RComplexRabbit>());
    c.Poll();
    lobject = c.cnode0->get<test::ComplexRabbit>(0);
    NI_ASSERT(lobject, "Child object should be");

    robject = 0;     
    waitForMissedEntity<test::ComplexRabbit>(c.cnode0, 0, c);
    TS_ASSERT_EQUALS(0, test::ComplexRabbit::is_object_deleted);
  }

  void test_EntityStatus()
  {
    TwoNodesCase c;

    test::ComplexRabbit* server_object = c.cnode0->get<test::ComplexRabbit>(0);
    TS_ASSERT_EQUALS((test::ComplexRabbit*)0, server_object);

    StrongMT<test::RComplexRabbit> client_object(c.cnode1->Create<test::RComplexRabbit>());
    TS_ASSERT_EQUALS(rpc::Connected, client_object->GetHandler()->GetStatus());
  }

  void test_DeletionOfRObjectAfterGateIsDown()
  {
    StrongMT<test::RComplexRabbit> clientObj;
    {
      TwoNodesCase c;
      clientObj = c.cnode1->Create<test::RComplexRabbit>();
      test::ComplexRabbit* serverObj = waitForEntity<test::ComplexRabbit>(c.cnode0, 0, c);
    }
  }

  void test_VoidCall()
  {
    TwoNodesCase c;
    StrongMT<test::RComplexRabbit> client_object(c.cnode1->Create<test::RComplexRabbit>()); 

    test::ComplexRabbit* server_object = waitForEntity<test::ComplexRabbit>(c.cnode0, 0, c); 
    TS_ASSERT_EQUALS(false, server_object->is_processed);

    client_object->process();
    c.Poll();
    TS_WAIT_FOR(server_object->is_processed == true, 100);
    TS_ASSERT_EQUALS(true, server_object->is_processed);

    for (int i=0;i<100;++i)
    {
      client_object->process();
      c.Poll();
    }
    client_object->process();
    c.Poll();
  }

  void test_GateDestruction()
  {
    StrongMT<test::RComplexRabbit> clientObject;
    {
      TwoNodesCase c;
      clientObject = c.cnode1->Create<test::RComplexRabbit>(); 

      test::ComplexRabbit* serverObject = waitForEntity<test::ComplexRabbit>(c.cnode0, 0, c); 
      c.Disconnect();
    }
  }

  void test_NativeSemantics()
  {
  }

  void test_CallWithParamsInt()
  {
    TwoNodesCase c;

    StrongMT<test::RComplexRabbit> client_object(c.cnode1->Create<test::RComplexRabbit>());

    test::ComplexRabbit* server_object = waitForEntity<test::ComplexRabbit>(c.cnode0, 0, c);
    client_object->processInt(555);
    TS_WAIT_FOR(555 == server_object->int_param0, 100);

    client_object->processInt(-555);
    TS_WAIT_FOR(-555 == server_object->int_param0, 100);
  }

  void test_CallWIthParamsByte()
  {
    TwoNodesCase c;

    StrongMT<test::RSimpleRabbit> client_object(c.cnode1->Create<test::RSimpleRabbit>());

    test::SimpleRabbit* server_object = waitForEntity<test::SimpleRabbit>(c.cnode0, 0, c);
    client_object->processByte(254);
    TS_WAIT_FOR(254 == server_object->byteValue, 100);

    client_object->processByte(4);
    TS_WAIT_FOR(4 == server_object->byteValue, 100);
  }

  void test_CallWIthParamsFloat()
  {
    TwoNodesCase c;

    StrongMT<test::RComplexRabbit> client_object(c.cnode0->Create<test::RComplexRabbit>());

    test::ComplexRabbit* server_object = waitForEntity<test::ComplexRabbit>(c.cnode1, 0, c);
    client_object->processFloat(2.f);
    c.Poll();
    TS_WAIT_FOR(2.f == server_object->float_param0, 100);
  }

  void test_CallWithParamTypedef()
  {
    TwoNodesCase c;

    StrongMT<test::RComplexRabbit> client_object(c.cnode0->Create<test::RComplexRabbit>());

    test::ComplexRabbit* server_object = waitForEntity<test::ComplexRabbit>(c.cnode1, 0, c);
    client_object->processMyType((test::MyType)1023);
    c.Poll();
    TS_WAIT_FOR(1023 == server_object->MyType_param0, 100);
  }

  void test_CallWithParamEnum()
  {
    TwoNodesCase c;

    StrongMT<test::RComplexRabbit> client_object(c.cnode0->Create<test::RComplexRabbit>());

    test::ComplexRabbit* server_object = waitForEntity<test::ComplexRabbit>(c.cnode1, 0, c);
    client_object->processMyEnum(test::Enum1);
    TS_WAIT_FOR(test::Enum1 == server_object->MyEnum_param0, 100);
    client_object->processMyEnum(test::Enum2);
    TS_WAIT_FOR(test::Enum2 == server_object->MyEnum_param0, 100);
  }

  void test_CallWithParamsLongLong()
  {
    TwoNodesCase c;

    StrongMT<test::RComplexRabbit> client_object(c.cnode0->Create<test::RComplexRabbit>());

    test::ComplexRabbit* server_object = waitForEntity<test::ComplexRabbit>(c.cnode1, 0, c);
    client_object->processLongLong((long long)1025);
    c.Poll();
    TS_WAIT_FOR(1025 == server_object->long_long_param0, 100);
  }

  void test_CallWIthParamsDouble()
  {
    TwoNodesCase c;

    StrongMT<test::RComplexRabbit> client_object(c.cnode0->Create<test::RComplexRabbit>());

    test::ComplexRabbit* server_object = waitForEntity<test::ComplexRabbit>(c.cnode1, 0, c);
    client_object->processDouble(1.0);
    c.Poll();

    TS_WAIT_FOR(fabs(1.0-server_object->double_param0) < 1e-2, 100);
  }

  void test_CallWIthParamsFloatInt()
  {
    TwoNodesCase c;

    StrongMT<test::RComplexRabbit> client_object(c.cnode0->Create<test::RComplexRabbit>());

    test::ComplexRabbit* server_object = waitForEntity<test::ComplexRabbit>(c.cnode1, 0, c);
    client_object->processFloatInt(1.f, 777);
    c.Poll();

    TS_WAIT_FOR(fabs(1.f-server_object->float_param0) < 1e-2f && 777 == server_object->int_param0, 100);
  }

  void test_TwoEntities()
  {
    TwoNodesCase c;

    StrongMT<test::RComplexRabbit> parent0(c.cnode0->Create<test::RComplexRabbit>());
    c.Poll();

    StrongMT<test::RComplexRabbit> parent1(c.cnode0->Create<test::RComplexRabbit>());

    test::ComplexRabbit* child0 = waitForEntity<test::ComplexRabbit>(c.cnode1, 0, c);
    test::ComplexRabbit* child1 = waitForEntity<test::ComplexRabbit>(c.cnode1, 1, c);
    TS_ASSERT_EQUALS(false, child0->is_processed);
    TS_ASSERT_EQUALS(false, child1->is_processed);

    parent1->process();
    c.Poll();
    TS_WAIT_FOR(true == child1->is_processed, 100);
  }

  void test_CallWithParamString()
  {
    TwoNodesCase c;

    StrongMT<test::RComplexRabbit> client_object(c.cnode0->Create<test::RComplexRabbit>());

    test::ComplexRabbit* server_object = waitForEntity<test::ComplexRabbit>(c.cnode1, 0,c );
    client_object->processString("Hello");
    TS_WAIT_FOR(nstl::string("Hello") == server_object->string_param0, 100);

    client_object->processString("");
    TS_WAIT_FOR(nstl::string("") == server_object->string_param0, 100);
  }

  void test_ConstCharNullAsParam()
  {
    TwoNodesCase c;

    StrongMT<test::RComplexRabbit> client_object(c.cnode0->Create<test::RComplexRabbit>());
    test::ComplexRabbit* server_object = waitForEntity<test::ComplexRabbit>(c.cnode1, 0,c );

    client_object->processString(0);
    TS_WAIT_FOR(nstl::string("") == server_object->string_param0, 100);
  }

  void test_WStringAsParam()
  {
    TwoNodesCase c;

    StrongMT<test::RSimpleRabbit> client_object(c.cnode0->Create<test::RSimpleRabbit>());

    test::SimpleRabbit* server_object = waitForEntity<test::SimpleRabbit>(c.cnode1, 0,c );
    nstl::wstring s(L"Hello, world!");
    client_object->processWString(s);
    TS_WAIT_FOR(s == server_object->ws, 100);
  }

  void test_CallWithParamVector()
  {
    TwoNodesCase c;

    StrongMT<test::RComplexRabbit> client_object(c.cnode0->Create<test::RComplexRabbit>());

    test::ComplexRabbit* server_object = waitForEntity<test::ComplexRabbit>(c.cnode1, 0, c);

    nstl::vector<int> v;
    v.resize(3);
    v[0] = 1;
    v[1] = 2;
    v[2] = 3;
    client_object->processVector(v);
    c.Poll();

    TS_WAIT_FOR(v.size() == server_object->vector_param0.size(), 100);
    TS_ASSERT_EQUALS(v[0], server_object->vector_param0[0]);
    TS_ASSERT_EQUALS(v[1], server_object->vector_param0[1]);
    TS_ASSERT_EQUALS(v[2], server_object->vector_param0[2]);
  }

  void test_CallWithParamVectorAndSecondArgument()
  {
    TwoNodesCase c;

    StrongMT<test::RComplexRabbit> client_object(c.cnode0->Create<test::RComplexRabbit>());

    test::ComplexRabbit* server_object = waitForEntity<test::ComplexRabbit>(c.cnode1, 0, c);

    nstl::vector<test::InitialSnapshot> v;
    test::InitialSnapshot s;
    client_object->processVector2(v, 555);

    TS_WAIT_FOR(555 == server_object->vector_after_param, 100);
  }
  
  struct MockProcessor1 : test::IPacketProcessor
  {
    void OnTest(TestPacketPipe* pipe, test::RComplexRabbit* object)
    {
      pipe->SetProcessor(this);
      nstl::vector<int> v;
      v.resize(255);
      v[0] = 1;
      v[1] = 2;
      v[2] = 3;
      object->processVector(v);
    }

    virtual void OnSend(byte* data, uint size)
    {
      rpc::PacketHeader header;
      if (rpc::ParsePacketHeader(data, size, header))
      {
        if (header.methodId == 6)
        {
          for (uint i=0;i<size-sizeof(uint);++i)
          {
            uint* idata = (uint*)(data+i);
            if (*idata == 255)
            {
              *idata = 0xFFFFFFFF;
              break;
            }
          }
        }
      }
    }
  };

  void test_CallWithParamVectorCorruptedBigSize()
  {
    check_PacketCorruption<MockProcessor1, test::RComplexRabbit, test::ComplexRabbit>();
  }
  
  struct MockProcessor2 : test::IPacketProcessor
  {
    void OnTest(TestPacketPipe* pipe, test::RSimpleRabbit* object)
    {
      pipe->SetProcessor(this);
      rpc::MemoryBlock b;
      b.size = 40;
      b.memory = (void*)"0123456789012345678901234567890123456789";
      object->processMemoryBlock(b);
    }

    virtual void OnSend(byte* data, uint size)
    {
      rpc::PacketHeader header;
      if (rpc::ParsePacketHeader(data, size, header))
      {
        if (header.methodId == 17)
        {
          for (uint i=0;i<size;++i)
          {
            if (data[i] == 8)
            {
              data[i] = 0;
              break;
            }
          }
        }
      }
    }
  };

  void test_CallWithParamMemoryBlockCorruptedAllocationSize()
  {
    check_PacketCorruption<MockProcessor2, test::RSimpleRabbit, test::SimpleRabbit>();
  }

  struct MockProcessor3 : test::IPacketProcessor
  {
    void OnTest(TestPacketPipe* pipe, test::RSimpleRabbit* object)
    {
      pipe->SetProcessor(this);
      rpc::MemoryBlock b;
      b.size = 40;
      b.memory = "0123456789012345678901234567890123456789";
      object->processMemoryBlock(b);
    }

    virtual void OnSend(byte* data, uint size)
    {
      rpc::PacketHeader header;
      if (rpc::ParsePacketHeader(data, size, header))
      {
        if (header.methodId == 17)
        {
          for (uint i=0;i<size;++i)
          {
            data[i] = 77;
          }
        }
      }
    }
  };

  void test_CallWithParamMemoryBlockCorruptedBlockSize()
  {
    check_PacketCorruption<MockProcessor3, test::RSimpleRabbit, test::SimpleRabbit>();
  }
  
  struct MockProcessor4 : test::IPacketProcessor
  {
    void OnTest(TestPacketPipe* pipe, test::RComplexRabbit* object)
    {
      pipe->SetProcessor(this);
      nstl::vector<int> v;
      v.resize(255);
      v[0] = 1;
      v[1] = 2;
      v[2] = 3;
      object->processVector(v);
    }

    virtual void OnSend(byte* data, uint size)
    {
      rpc::PacketHeader header;
      if (rpc::ParsePacketHeader(data, size, header))
      {
        if (header.methodId == 6)
        {
          for (uint i=0;i<size-sizeof(uint);++i)
          {
            uint* idata = (uint*)(data+i);
            if (*idata == 4)
            {
              *idata = 0xFFFE;
              break;
            }
          }
        }
      }
    }
  };

  void test_CallWithParamVectorCorruptedBigElementSize()
  {
    check_PacketCorruption<MockProcessor4, test::RComplexRabbit, test::ComplexRabbit>();
  }

  template <typename T, typename C, typename O>
  void check_PacketCorruption()
  {
    ManyToManyCase c;
    StrongMT<test::MockCorruptedPacketProcessor> gate0P = new test::MockCorruptedPacketProcessor("gate0", &c);
    StrongMT<test::MockCorruptedPacketProcessor> gate1P = new test::MockCorruptedPacketProcessor("gate1", &c);

    rpc::Gate& gate0 = c.AddGate("gate0", gate0P);
    rpc::Gate& gate1 = c.AddGate("gate1", gate1P);

    c.ConnectGates("gate0", "gate1");
    c.WaitForConnections();

    ManyToManyCase::GateLink link = c.GetGateLink(gate0, gate1);
    rpc::Node* a01 = c.GetNode(gate0, gate1);
    rpc::Node* a10 = c.GetNode(gate1, gate0);

    T p;

    StrongMT<C> client_object(a01->Create<C>());

    O* server_object = waitForEntity<O>(a10, 0, c);
    {
      test::AssertDisabler d;
      p.OnTest(link.pipe, client_object.Get());
      TS_WAIT_FOR(0 != gate1P->corruptedPipe, 100);
    }
  }

  template <typename T, typename C, typename O>
  void check_RandomTraffic()
  {
    const uint testsCount = 1;//0xFFFFFFFF;
    for (uint i=0;i<testsCount;++i)
    {
      ManyToManyCase c;
      StrongMT<test::MockCorruptedPacketProcessor> gate0P = new test::MockCorruptedPacketProcessor("gate0", &c);
      StrongMT<test::MockCorruptedPacketProcessor> gate1P = new test::MockCorruptedPacketProcessor("gate1", &c);

      rpc::Gate& gate0 = c.AddGate("gate0", gate0P);
      rpc::Gate& gate1 = c.AddGate("gate1", gate1P);

      c.ConnectGates("gate0", "gate1");
      c.WaitForConnections();

      ManyToManyCase::GateLink link = c.GetGateLink(gate0, gate1);
      rpc::Node* a01 = c.GetNode(gate0, gate1);
      rpc::Node* a10 = c.GetNode(gate1, gate0);

      T p;

      StrongMT<C> client_object(a01->Create<C>());

      O* server_object = waitForEntity<O>(a10, 0, c);
      {
        test::AssertDisabler d;
        p.OnTest(link.pipe, client_object.Get());
        c.Poll();
      }
    }
  }
  
  struct MockProcessor5 : test::IPacketProcessor
  {
    void OnTest(TestPacketPipe* pipe, test::RSimpleRabbit* object)
    {
      pipe->SetProcessor(this);
      nstl::vector<rpc::MemoryBlock> v;
      v.resize(3);
      v[0] = rpc::MemoryBlock((void*)"Data0", 5);
      v[1] = rpc::MemoryBlock((void*)"Data1", 5);;
      v[2] = rpc::MemoryBlock((void*)"Data2", 5);;
      object->processMemoryBlockVector(v);
    }

    virtual void OnSend(byte* data, uint size)
    {
      rpc::PacketHeader header;
      if (rpc::ParsePacketHeader(data, size, header))
      {
        if (header.methodId == 18)
        {
          const uint start = 16;
          const byte testcase[] = {64, 155, 153, 210, 189, 158, 68, 17, 199, 29, 87, 2, 131, 223, 152, 202, 104, 137, 166, 10, 139, 94 };
          for (uint i=start;i<size;++i)
          {
            data[i] = testcase[i-start];//byte(NRandom::Random(0, 255));
          }
          const int buf_size = 2048;
          static char buffer[buf_size];
          char* s = buffer;
          for (uint i=start;i<size;++i)
          {
            s += NStr::Printf(s, buf_size-(s-buffer), "%d, ", data[i]);
          }
          *s++ = '\n';
          *s = 0;
          OutputDebugString(buffer);
        }
      }
    }
  };

  void test_RandomTraffic()
  {
    check_RandomTraffic<MockProcessor5, test::RSimpleRabbit, test::SimpleRabbit>();
  }
  
  struct MockProcessor6 : test::IPacketProcessor
  {
    void OnTest(TestPacketPipe* pipe, test::RComplexRabbit* object)
    {
      pipe->SetProcessor(this);
      nstl::vector<int> v;
      v.resize(255);
      v[0] = 1;
      v[1] = 2;
      v[2] = 3;
      object->processVector(v);
    }

    virtual void OnSend(byte* data, uint size)
    {
      rpc::PacketHeader header;
      if (rpc::ParsePacketHeader(data, size, header))
      {
        if (header.methodId == 6)
        {
          for (uint i=0;i<size-sizeof(uint);++i)
          {
            uint* idata = (uint*)(data+i);
            if (*idata == 255)
            {
              *idata = 256;
              break;
            }
          }
        }
      }
    }
  };

  void test_CallWithParamVectorCorruptedChangeSize()
  {
    //check_VectorCorruption<MockProcessor6, test::RComplexRabbit, test::ComplexRabbit>();
  }
  
  struct MockProcessor7 : test::IPacketProcessor
  {
    void OnTest(TestPacketPipe* pipe, test::RSimpleRabbit* object)
    {
      pipe->SetProcessor(this);

      nstl::vector<test::InitialSnapshot> v;
      v.resize(255);
      object->processVectorsOfSnapshots(v);
    }
    virtual void OnSend(byte* data, uint size)
    {
      rpc::PacketHeader header;
      if (rpc::ParsePacketHeader(data, size, header))
      {
        if (header.methodId == 5)
        {
          for (uint i=0;i<size-sizeof(uint);++i)
          {
            uint* idata = (uint*)(data+i);
            if (*idata == 255)
            {
              *idata = 0xFFFFFFFF;
              break;
            }
          }
        }
      }
    }
  };

  void test_CallWithParamVectorOfSerializableStructsCorruptedBigSize()
  {
    check_PacketCorruption<MockProcessor7, test::RSimpleRabbit, test::SimpleRabbit>();
  }

  void test_CallWithParamVectorDoubles()
  {
    TwoNodesCase c;

    StrongMT<test::RComplexRabbit> client_object(c.cnode0->Create<test::RComplexRabbit>());

    test::ComplexRabbit* server_object = waitForEntity<test::ComplexRabbit>(c.cnode1, 0, c);

    nstl::vector<double> v;
    v.resize(2);
    v[0] = 1;
    v[1] = 2;
    client_object->processVectorWithDoubles(v);
    c.Poll();
    TS_WAIT_FOR(v.size() == server_object->vector_param1.size(), 100);
    TS_ASSERT_EQUALS(v[0], server_object->vector_param1[0]);
    TS_ASSERT_EQUALS(v[1], server_object->vector_param1[1]);
  }


  void test_CallWithParamVectorOfSerializableStructs()
  {
    TwoNodesCase c;

    StrongMT<test::RSimpleRabbit> client_object(c.cnode0->Create<test::RSimpleRabbit>());

    test::SimpleRabbit* server_object = waitForEntity<test::SimpleRabbit>(c.cnode1, 0, c);

    nstl::vector<test::InitialSnapshot> v;
    v.resize(2);

    test::InitialSnapshot snapshot0;
    snapshot0.serverTime = 7.f;
    {
      test::InitialSnapshot::DiffDesc desc;
      desc.id = 1004;
      desc.isDead = false;
      snapshot0.difference.push_back(desc);
    }

    test::InitialSnapshot snapshot1;
    snapshot1.serverTime = 2.f;
    {
      test::InitialSnapshot::DiffDesc desc;
      desc.id = 1001;
      desc.isDead = true;
      snapshot1.difference.push_back(desc);
    }

    v[0] = snapshot0;
    v[1] = snapshot1;

    client_object->processVectorsOfSnapshots(v);
    c.Poll();
    TS_WAIT_FOR(v.size() == server_object->vmsg.size(), 100);
    TS_ASSERT_EQUALS(v[0].serverTime, server_object->vmsg[0].serverTime);
    TS_ASSERT_EQUALS(v[1].serverTime, server_object->vmsg[1].serverTime);
  }

  void test_EmptyVectorOfSerializableStructs()
  {
    TwoNodesCase c;

    StrongMT<test::RSimpleRabbit> client_object(c.cnode0->Create<test::RSimpleRabbit>());

    test::SimpleRabbit* server_object = waitForEntity<test::SimpleRabbit>(c.cnode1, 0, c);

    nstl::vector<test::InitialSnapshot> v;
    client_object->processVectorsOfSnapshots(v);
    c.Poll();
    TS_WAIT_FOR(v.size() == server_object->vmsg.size(), 100);
  }

  void test_CallWithParamBool()
  {
    TwoNodesCase c;

    StrongMT<test::RComplexRabbit> client_object(c.cnode0->Create<test::RComplexRabbit>());
    test::ComplexRabbit* server_object = waitForEntity<test::ComplexRabbit>(c.cnode1, 0, c);

    client_object->processBool(true);
    c.Poll();
    TS_WAIT_FOR(true == server_object->bool_param0, 100);
  }

  void test_CallWithParamNSTLString()
  {
    TwoNodesCase c;

    StrongMT<test::RComplexRabbit> client_object(c.cnode0->Create<test::RComplexRabbit>());
    test::ComplexRabbit* server_object = waitForEntity<test::ComplexRabbit>(c.cnode1, 0, c);

    client_object->processNSTLString( string( "hello world" ) );
    TS_WAIT_FOR(string( "hello world" ) == server_object->nsltString_param0, 100);
  }

  void test_CallWithParamShort()
  {
    TwoNodesCase c;

    StrongMT<test::RComplexRabbit> client_object(c.cnode0->Create<test::RComplexRabbit>());
    test::ComplexRabbit* server_object = waitForEntity<test::ComplexRabbit>(c.cnode1, 0, c);

    client_object->processShort(555);
    c.Poll();
    TS_WAIT_FOR(555 == server_object->short_param0, 100);
  }

  void test_CallWithParamMemoryBlock()
  {
    TwoNodesCase c;

    StrongMT<test::RSimpleRabbit> client_object(c.cnode0->Create<test::RSimpleRabbit>());
    test::SimpleRabbit* server_object = waitForEntity<test::SimpleRabbit>(c.cnode1, 0, c);

    {
      byte block[5] = "1234";
      rpc::MemoryBlock b(block, 4);
      client_object->processMemoryBlock(b);
      crt::memset(block, 0, 5);
    }
    c.Poll();
    TS_WAIT_FOR(4 == server_object->b.size, 100);
    TS_ASSERT_SAME_DATA("1234", server_object->b.memory, 4);
  }

  void test_CallWithParamMemoryBlockLarge()
  {
    TwoNodesCase c;

    StrongMT<test::RSimpleRabbit> client_object(c.cnode0->Create<test::RSimpleRabbit>());
    test::SimpleRabbit* server_object = waitForEntity<test::SimpleRabbit>(c.cnode1, 0, c);

    {
      byte block[45000] = "1234";
      rpc::MemoryBlock b(block, 45000);
      client_object->processMemoryBlock(b);
    }
    c.Poll();
    TS_WAIT_FOR(45000 == server_object->b.size, 100);
  }

  void test_CallWithParamMemoryBlockVeryLarge()
  {
    TwoNodesCase c;

    StrongMT<test::RSimpleRabbit> client_object(c.cnode0->Create<test::RSimpleRabbit>());
    test::SimpleRabbit* server_object = waitForEntity<test::SimpleRabbit>(c.cnode1, 0, c);

    {
      byte block[70000] = "1234";
      rpc::MemoryBlock b(block, 70000);
      {
        test::AssertDisabler d;
        TS_ASSERT_EQUALS(rpc::ECallResult::TooLargeData, client_object->processMemoryBlock(b));
      }
    }
  }

  void test_CallWithParamMemoryBlockVector()
  {
    TwoNodesCase c;

    StrongMT<test::RSimpleRabbit> client_object(c.cnode0->Create<test::RSimpleRabbit>());
    test::SimpleRabbit* server_object = waitForEntity<test::SimpleRabbit>(c.cnode1, 0, c);

    {
      byte block0[5] = "1234";
      rpc::MemoryBlock b0(block0, 4);
      byte block1[5] = "5678";
      rpc::MemoryBlock b1(block1, 4);
      nstl::vector<rpc::MemoryBlock> v;
      v.push_back(b0);
      v.push_back(b1);
      client_object->processMemoryBlockVector(v);
      crt::memset(block0, 0, 5);
      crt::memset(block1, 0, 5);
    }
    c.Poll();
    TS_WAIT_FOR(2 == server_object->blocks.size(), 100);
    TS_ASSERT_EQUALS(4, server_object->blocks[0].size);
    TS_ASSERT_SAME_DATA("1234", server_object->blocks[0].memory, 4);
    TS_ASSERT_EQUALS(4, server_object->blocks[1].size);
    TS_ASSERT_SAME_DATA("5678", server_object->blocks[1].memory, 4);
  }


  void test_CallWithParamVectorOfStrings()
  {
    TwoNodesCase c;

    StrongMT<test::RSimpleRabbit> client_object(c.cnode0->Create<test::RSimpleRabbit>());

    test::SimpleRabbit* server_object = waitForEntity<test::SimpleRabbit>(c.cnode1, 0,c );

    nstl::vector<nstl::string> s;
    s.push_back("Hello!");
    s.push_back("World!");

    client_object->processVectorOfStrings(s);
    TS_WAIT_FOR(2 == server_object->vs.size(), 100);
    TS_ASSERT_EQUALS(nstl::string("Hello!"), server_object->vs[0] );
    TS_ASSERT_EQUALS(nstl::string("World!"), server_object->vs[1] );
  }

  void test_CallWithParamVectorOfWStrings()
  {
    TwoNodesCase c;

    StrongMT<test::RSimpleRabbit> client_object(c.cnode0->Create<test::RSimpleRabbit>());

    test::SimpleRabbit* server_object = waitForEntity<test::SimpleRabbit>(c.cnode1, 0,c );

    nstl::vector<nstl::wstring> s;
    s.push_back(L"Вадим");
    s.push_back(L"Петров");
    s.push_back(L"Hi!");

    client_object->processVectorOfWStrings(s);
    TS_WAIT_FOR(3 == server_object->wvs.size(), 100);
    TS_ASSERT_EQUALS(nstl::wstring(L"Вадим"), server_object->wvs[0] );
    TS_ASSERT_EQUALS(nstl::wstring(L"Петров"), server_object->wvs[1] );
    TS_ASSERT_EQUALS(nstl::wstring(L"Hi!"), server_object->wvs[2] );
  }

  void test_CObjInNode()
  {
    StrongMT<rpc::Node> node01;
    StrongMT<rpc::Node> node10;
    {
      ManyToManyCase c;

      rpc::Gate& gate0 = c.AddGate("gate0");
      rpc::Gate& gate1 = c.AddGate("gate1");

      c.ConnectGates("gate0", "gate1");
      c.WaitForConnections();
      node01 = c.GetNode(gate0, gate1);
      node10 = c.GetNode(gate1, gate0);
      c.DisconnectGates(gate0, gate1);
    }
    StrongMT<test::RSimpleRabbit> clientObject = node01->Create<test::RSimpleRabbit>();
    TS_ASSERT_EQUALS((test::RSimpleRabbit*)0, clientObject.Get());
  }

  void test_ComplexStruct()
  {
    TwoNodesCase c;

    StrongMT<test::RSimpleRabbit> clientObject(c.cnode1->Create<test::RSimpleRabbit>());
    c.Poll();

    test::SimpleRabbit* serverObject = waitForEntity<test::SimpleRabbit>(c.cnode0, 0, c); 
    test::InitialSnapshot snapshot;
    snapshot.serverTime = 4.f;

    {
      test::InitialSnapshot::DiffDesc desc;
      desc.id = 1004;
      desc.isDead = false;
      snapshot.difference.push_back(desc);
    }
    {
      test::InitialSnapshot::DiffDesc desc;
      desc.id = 1001;
      desc.isDead = true;
      snapshot.difference.push_back(desc);
    }
    clientObject->processSnapshot(snapshot);
    c.Poll();
    TS_WAIT_FOR(serverObject->isSnapshotRecieved == true, 10000);
    TS_ASSERT_EQUALS(true, serverObject->isSnapshotRecieved);
    TS_ASSERT_EQUALS(4.f, serverObject->msg.serverTime);
    TS_ASSERT_EQUALS(2, serverObject->msg.difference.size());
  }

  void test_TwoComplexStructs()
  {
    TwoNodesCase c;

    StrongMT<test::RSimpleRabbit> clientObject(c.cnode1->Create<test::RSimpleRabbit>());
    c.Poll();

    test::SimpleRabbit* serverObject = waitForEntity<test::SimpleRabbit>(c.cnode0, 0, c); 
    test::InitialSnapshot snapshot0;
    snapshot0.serverTime = 7.f;
    test::InitialSnapshot snapshot1;
    snapshot1.serverTime = 9.f;

    clientObject->processTwoSnapshots(snapshot0, snapshot1);

    TS_WAIT_FOR(serverObject->isSnapshotRecieved == true, 10000);
    TS_ASSERT_EQUALS(true, serverObject->isSnapshotRecieved);
    TS_ASSERT_EQUALS(7.f, serverObject->msg0.serverTime);
    TS_ASSERT_EQUALS(9.f, serverObject->msg1.serverTime);
  }

  void test_SerializableStructAsReturnValue()
  {
    TwoNodesCase c;

    StrongMT<test::RSimpleRabbit> clientObject(c.cnode1->Create<test::RSimpleRabbit>());
    c.Poll();

    test::SimpleRabbit* serverObject = waitForEntity<test::SimpleRabbit>(c.cnode0, 0, c); 

    StrongMT<rpc::RValue<test::SMatchmakingStatus> > t = new rpc::RValue<test::SMatchmakingStatus>;
    clientObject->getStatus(t.Get(), &rpc::RValue<test::SMatchmakingStatus>::OnCall);

    TS_WAIT_FOR(t->IsSet(), 10000);
    TS_ASSERT_EQUALS(50, t->result.progress);
    TS_ASSERT_EQUALS(2, t->result.requestsAccepted);
    assertEquals("good session", t->result.sessionId.c_str());
  }

  void test_ReturnComplexStruct()
  {
    TwoNodesCase c;

    StrongMT<test::RSimpleRabbit> clientObject(c.cnode1->Create<test::RSimpleRabbit>());
    c.Poll();

    test::SimpleRabbit* serverObject = waitForEntity<test::SimpleRabbit>(c.cnode0, 0, c); 
    test::InitialSnapshot snapshot;
    snapshot.serverTime = 7.f;
    {
      test::InitialSnapshot::DiffDesc desc;
      desc.id = 1004;
      desc.isDead = false;
      snapshot.difference.push_back(desc);
    }
    {
      test::InitialSnapshot::DiffDesc desc;
      desc.id = 1001;
      desc.isDead = true;
      snapshot.difference.push_back(desc);
    }

    StrongMT<rpc::RefValue<test::InitialSnapshot> > t = new rpc::RefValue<test::InitialSnapshot>;
    clientObject->processSnapshotReturnSnapshot(snapshot, t.Get(), &rpc::RefValue<test::InitialSnapshot>::OnCall);

    TS_WAIT_FOR(serverObject->isSnapshotRecieved == true, 10000);
    TS_WAIT_FOR(t->IsSet(), 10000);
    TS_ASSERT_EQUALS(true, serverObject->isSnapshotRecieved);
    TS_ASSERT_EQUALS(7.f, serverObject->msg.serverTime);
    TS_ASSERT_EQUALS(2, serverObject->msg.difference.size());
    TS_ASSERT_EQUALS(7.f, t->result.serverTime);
    TS_ASSERT_EQUALS(2, t->result.difference.size());
  }

  void test_ReturnVectorOfBytes()
  {
    TwoNodesCase c;

    StrongMT<test::RSimpleRabbit> clientObject(c.cnode1->Create<test::RSimpleRabbit>());
    c.Poll();

    test::SimpleRabbit* serverObject = waitForEntity<test::SimpleRabbit>(c.cnode0, 0, c); 

    StrongMT<rpc::RefValue<nstl::vector<byte> > > t = new rpc::RefValue<nstl::vector<byte> >;
    clientObject->processReturnVectorOfBytes(t.Get(), &rpc::RefValue<nstl::vector<byte> >::OnCall);

    TS_WAIT_FOR(t->IsSet(), 10000);
    TS_ASSERT_EQUALS(2, t->result.size());
  }

  void test_CallWithParamStruct()
  {
    TwoNodesCase c;

    StrongMT<test::RComplexRabbit> client_object(c.cnode0->Create<test::RComplexRabbit>());

    test::ComplexRabbit* server_object = waitForEntity<test::ComplexRabbit>(c.cnode1, 0,c );

    test::SimpleStruct s(1, 4.f, 5.0, 14);

    client_object->processStruct(s);
    c.Poll();

    TS_WAIT_FOR(true == server_object->isStructParamRecieved, 100);
    TS_ASSERT_EQUALS(true, server_object->isStructParamRecieved);
    TS_ASSERT_EQUALS(1, server_object->s.i);
    TS_ASSERT_EQUALS(4.f, server_object->s.f);
    TS_ASSERT_EQUALS(5.0, server_object->s.d);
    TS_ASSERT_EQUALS(14, server_object->s.s);
  }

  void test_EntityPing()
  {
    TwoNodesCase c;

    StrongMT<test::RSimpleRabbit> robj(c.cnode0->Create<test::RSimpleRabbit>());

    test::SimpleRabbit* lobj = waitForEntity<test::SimpleRabbit>(c.cnode1, 0,c );

    StrongMT<rpc::RefValue<nstl::vector<byte> > > t = new rpc::RefValue<nstl::vector<byte> >;
    nstl::vector<byte> data;
    data.resize(4);
    data[0] = 'A';
    data[1] = 'B';
    data[2] = 'C';
    data[3] = 'D';
    robj->Ping(data, t.Get(), &rpc::RefValue<nstl::vector<byte> >::OnCall);

    TS_WAIT_FOR(t->IsSet(), 100);
    TS_ASSERT_SAME_DATA(t->Get().begin(), data.begin(), 4);
  }

  void test_VoidCallWithSimpleRabbit()
  {
    TwoNodesCase c;

    StrongMT<test::RSimpleRabbit> client_object(c.cnode1->Create<test::RSimpleRabbit>());
    test::SimpleRabbit* server_object = waitForEntity<test::SimpleRabbit>(c.cnode0, 0, c);
    TS_ASSERT_EQUALS(false, server_object->is_processed);

    client_object->process();
    c.Poll();
    TS_WAIT_FOR(true == server_object->is_processed, 100);
    TS_ASSERT_EQUALS(1, server_object->constructor_number_called);
  }

  void test_ConstructorWithParams()
  {
    TwoNodesCase c;

    StrongMT<test::RSimpleRabbit> client_object(c.cnode0->Create<test::RSimpleRabbit>(short(777)));

    test::SimpleRabbit* server_object = waitForEntity<test::SimpleRabbit>(c.cnode1, 0, c);
    TS_ASSERT_EQUALS(777, server_object->short_creation_param0);
    TS_ASSERT_EQUALS(2, server_object->constructor_number_called);
  }

  void test_CorrectIDS()
  {
    TwoNodesCase c;

    StrongMT<test::RSimpleRabbit> p0(c.cnode0->Create<test::RSimpleRabbit>());
    StrongMT<test::RSimpleRabbit> p1(c.cnode0->Create<test::RSimpleRabbit>());
    StrongMT<test::RSimpleRabbit> p2(c.cnode0->Create<test::RSimpleRabbit>());

    test::SimpleRabbit* c0 = waitForEntity<test::SimpleRabbit>(c.cnode1, 0, c);
    test::SimpleRabbit* c1 = waitForEntity<test::SimpleRabbit>(c.cnode1, 1, c);
    test::SimpleRabbit* c2 = waitForEntity<test::SimpleRabbit>(c.cnode1, 2, c);

    p0 = 0;     
    p1 = 0;
    waitForMissedEntity<test::ComplexRabbit>(c.cnode1, 0, c);
    waitForMissedEntity<test::ComplexRabbit>(c.cnode1, 1, c);

    p2->process();
    c.Poll();
    TS_WAIT_FOR(true == c2->is_processed, 100);
  }

  void test_SynchronousReturnValue()
  {
    // This test doesn't pass because of sync call 
    /*
    TwoNodesCase c;

    StrongMT<test::RComplexRabbit> p0(c.cnode0->Create<test::RComplexRabbit>());
    c.Poll();
    for (int i=0;i<5;++i) 
    {
    TS_ASSERT_EQUALS(i*2, p0->processIntWithReturnValueInt(i));
    c.Poll();
    }*/
  } 

  void test_ASynchronousReturnIntValue()
  {
    TwoNodesCase c;

    StrongMT<test::RComplexRabbit> p0(c.cnode0->Create<test::RComplexRabbit>());
    c.Poll();

    for (int i=0;i<10;++i) 
    {
      StrongMT<rpc::RValue<int> > t = new rpc::RValue<int>;
      p0->processIntWithReturnValueIntAsync(i, t.Get(), &rpc::RValue<int>::OnCall);
      while(!t->IsSet()) c.Poll();
      TS_ASSERT_EQUALS(i*3, t->result);
    }
  }

  void test_ASynchronousReturnStructRef()
  {
    TwoNodesCase c;

    StrongMT<test::RComplexRabbit> p0(c.cnode0->Create<test::RComplexRabbit>());
    c.Poll();

    StrongMT<rpc::RefValue<test::SimpleStruct> > t = new rpc::RefValue<test::SimpleStruct>;
    p0->processReturnStructRef(t.Get(), &rpc::RefValue<test::SimpleStruct>::OnCall);
    while(!t->IsSet()) 
      c.Poll();
    TS_ASSERT_EQUALS(555, t->result.d);
    TS_ASSERT_EQUALS(100.f, t->result.f);
    TS_ASSERT_EQUALS(777, t->result.i);
    TS_ASSERT_EQUALS(12, t->result.s);
  }

  void test_ASynchronousReturnStruct()
  {
    TwoNodesCase c;
    test::SimpleStruct s(56, 58.f, 59, 12);

    StrongMT<test::RComplexRabbit> p0(c.cnode0->Create<test::RComplexRabbit>());
    test::ComplexRabbit* serverObject = waitForEntity<test::ComplexRabbit>(c.cnode1, 0, c);

    StrongMT<rpc::RValue<test::SimpleStruct> > t = new rpc::RValue<test::SimpleStruct>;
    p0->processReturnStruct(s, t.Get(), &rpc::RValue<test::SimpleStruct>::OnCall);

    while(!t->IsSet()) 
      c.Poll();

    TS_ASSERT_EQUALS(s.d, serverObject->s.d);
    TS_ASSERT_EQUALS(s.f, serverObject->s.f);
    TS_ASSERT_EQUALS(s.i, serverObject->s.i);
    TS_ASSERT_EQUALS(s.s, serverObject->s.s);

    TS_ASSERT_EQUALS(111, t->result.d);
    TS_ASSERT_EQUALS(200.f, t->result.f);
    TS_ASSERT_EQUALS(877, t->result.i);
    TS_ASSERT_EQUALS(24, t->result.s);
  }

  void test_ReceiveTime()
  {
    TwoNodesCase c;

    StrongMT<test::RComplexRabbit> p0(c.cnode0->Create<test::RComplexRabbit>());
    test::ComplexRabbit* serverObject = waitForEntity<test::ComplexRabbit>(c.cnode1, 0, c);

    p0->processRecieveTime();

    TS_WAIT_FOR(serverObject->timeIsSet, 100);
  }

  void test_ASynchronousReturnDoubleValue()
  {
    TwoNodesCase c;

    StrongMT<test::RComplexRabbit> p0(c.cnode0->Create<test::RComplexRabbit>());
    c.Poll();

    StrongMT<rpc::RValue<double> > t = new rpc::RValue<double>;
    p0->processDoubleWithReturnValueDoubleAsync(double(4), t.Get(), &rpc::RValue<double>::OnCall);
    while(!t->IsSet()) c.Poll();
    TS_ASSERT_EQUALS(double(16), t->result);
  }

  void test_ASynchronousReturnNstlString()
  {
    TwoNodesCase c;

    StrongMT<test::RSimpleRabbit> p0(c.cnode0->Create<test::RSimpleRabbit>());
    c.Poll();
    test::SimpleRabbit* serverObject = waitForEntity<test::SimpleRabbit>(c.cnode1, 0, c);
    serverObject->string_param0 = "Hello !";

    StrongMT<rpc::RefValue<nstl::string> > t = new rpc::RefValue<nstl::string>;
    p0->processWithReturnValueNSTLStringAsync(t.Get(), &rpc::RefValue<nstl::string>::OnCall);
    while(!t->IsSet()) c.Poll();
    assertEquals(serverObject->string_param0.c_str(), t->result.c_str());
  }

  void test_ASynchronousReturnIntWithLongProcessing()
  {
    TwoNodesCase c;

    StrongMT<test::RComplexRabbit> p0(c.cnode0->Create<test::RComplexRabbit>());
    c.Poll();

    StrongMT<rpc::RValue<int> > t0 = new rpc::RValue<int>;
    p0->processIntWithReturnValueIntAsyncLong(100, t0.Get(), &rpc::RValue<int>::OnCall);
    c.Poll();
    StrongMT<rpc::RValue<int> > t1 = new rpc::RValue<int>;
    p0->processIntWithReturnValueIntAsyncLong(200, t1.Get(), &rpc::RValue<int>::OnCall);
    c.Poll();
    while(!t0->IsSet() || !t1->IsSet()) c.Poll();
    TS_ASSERT_EQUALS(100, t0->result);
    TS_ASSERT_EQUALS(200, t1->result);
  }

  void test_ASynchronousReturnIntWithLongProcessingWithContext()
  {
    TwoNodesCase c;

    StrongMT<test::RComplexRabbit> p0(c.cnode0->Create<test::RComplexRabbit>());
    c.Poll();

    StrongMT<rpc::RValue<int> > t0 = new rpc::RValue<int>;
    p0->processIntWithReturnValueIntAsyncLong(100, t0.Get(), &rpc::RValue<int>::OnCallDetailed, 444);
    c.Poll();
    StrongMT<rpc::RValue<int> > t1 = new rpc::RValue<int>;
    p0->processIntWithReturnValueIntAsyncLong(200, t1.Get(), &rpc::RValue<int>::OnCallDetailed, 555);
    c.Poll();
    while(!t0->IsSet() || !t1->IsSet()) c.Poll();
    TS_ASSERT_EQUALS(100, t0->result);
    TS_ASSERT_EQUALS(444, t0->context);
    TS_ASSERT_EQUALS(200, t1->result);
    TS_ASSERT_EQUALS(555, t1->context);
  }

  void test_ASynchronousReturnIntWithLongProcessingWithContextAndTimeout()
  {
    TwoNodesCase c;

    StrongMT<test::RComplexRabbit> p0(c.cnode0->Create<test::RComplexRabbit>());
    c.Poll();

    StrongMT<rpc::RValue<int> > t1 = new rpc::RValue<int>;
    p0->processIntWithReturnValueIntAsyncLong(200, t1.Get(), &rpc::RValue<int>::OnCallDetailed, 555, 0.5f);

    NHPTimer::STime startTime;
    NHPTimer::GetTime(startTime);
    while (true)
    {
      c.GetGate(0).Poll();
      NHPTimer::STime curTime;
      NHPTimer::GetTime(curTime);
      if (NHPTimer::Time2Seconds(curTime-startTime) >= 1.f)
      {
        break;
      }
    } 
    TS_ASSERT_EQUALS(true, t1->IsSet());
    TS_ASSERT_EQUALS(555, t1->context);
    TS_ASSERT_EQUALS(rpc::CallTimedOut, t1->status);
  }

  void test_CallWithParamVectorEmpty()
  {
    TwoNodesCase c;

    StrongMT<test::RComplexRabbit> client_object(c.cnode0->Create<test::RComplexRabbit>());
    test::ComplexRabbit* server_object = waitForEntity<test::ComplexRabbit>(c.cnode1, 0, c);

    server_object->vector_param0.resize( 10, 0 );

    nstl::vector<int> v;
    client_object->processVector(v);
    c.Poll();

    TS_WAIT_FOR(v.size() == server_object->vector_param0.size(), 100);
  }

  void test_CallWithParamFixedVector()
  {
    TwoNodesCase c;

    StrongMT<test::RSimpleRabbit> client_object(c.cnode0->Create<test::RSimpleRabbit>());
    test::SimpleRabbit* server_object = waitForEntity<test::SimpleRabbit>(c.cnode1, 0, c);

    FixedVector<int, 100> v;
    v.push_back(100);
    v.push_back(101);
    v.push_back(102);
    client_object->processFixedVector(v);
    c.Poll();

    TS_WAIT_FOR(v.size() == server_object->fixedVector.size(), 100);
    TS_WAIT_FOR(v.capacity() == server_object->fixedVector.capacity(), 100);
  }

  void test_DisconnectDoneBeforePoll()
  {
    OneToManyCase c("root");
    rpc::Gate& root = c.GetRootGate();
    rpc::Gate& leaf0 = c.AddConnectedGate("leaf0");

    c.DisconnectGates(root, leaf0);
    c.Poll();
  }

  void test_TwoToOnePipesSimpleCall()
  {
    OneToManyCase c("root");

    rpc::Gate& root = c.GetRootGate();
    rpc::Gate& leaf0 = c.AddConnectedGate("leaf0");
    rpc::Gate& leaf1 = c.AddConnectedGate("leaf1");

    rpc::Node* a01 = c.GetNode(root, leaf0);
    rpc::Node* a02 = c.GetNode(root, leaf1);
    rpc::Node* a10 = c.GetNode(leaf0, root);
    rpc::Node* a20 = c.GetNode(leaf1, root);

    c.WaitForConnections();

    StrongMT<test::RComplexRabbit> client_object10(a10->Create<test::RComplexRabbit>());
    StrongMT<test::RComplexRabbit> client_object20(a20->Create<test::RComplexRabbit>());

    test::ComplexRabbit* server_object01 = waitForEntity<test::ComplexRabbit>(a01, 0, c);
    test::ComplexRabbit* server_object02 = waitForEntity<test::ComplexRabbit>(a02, 0, c);

    client_object10->process();
    client_object20->process();
    TS_WAIT_FOR(server_object01->is_processed == true, 100);
    TS_WAIT_FOR(server_object02->is_processed == true, 100);
  }

  void test_CreationOfManyEntities()
  {
    TwoNodesCase c;

    nstl::vector < StrongMT<test::RComplexRabbit> > items;
    const int maxObjects = 100; // use 0xFFFF+2 for test 3 bits compression, commented because of long creation time for 0xFFFF objects
    for (int i=0;i<maxObjects;++i)
    {
      StrongMT<test::RComplexRabbit> co(c.cnode1->Create<test::RComplexRabbit>());
      c.Poll();
      items.push_back(co);
    }
    StrongMT<test::RComplexRabbit> co(c.cnode1->Create<test::RComplexRabbit>());
    c.Poll();

    for (int i=0;i<maxObjects+1;++i)
    {
      test::ComplexRabbit* so = waitForEntity<test::ComplexRabbit>(c.cnode0, i, c);
    }
  }
  template <typename T>
  void TS_ASSERT_IN_VECTOR(const nstl::vector<T>& items, T item)
  {
    for (int i=0;i<items.size();++i)
    {
      if (items[i] == item)
      {
        return;
      }
    }
    TS_FAIL("Item not found in vector");
  }

  void test_GetNode()
  {
    OneToManyCase c("root");

    rpc::Gate& root = c.GetRootGate();
    rpc::Gate& leaf0 = c.AddConnectedGate("leaf0");
    rpc::Gate& leaf1 = c.AddConnectedGate("leaf1");

    rpc::Node* a01 = c.GetNode(root, leaf0);
    rpc::Node* a02 = c.GetNode(root, leaf1);
    c.WaitForConnections();

    StrongMT<test::RComplexRabbit> obj(a01->Create<test::RComplexRabbit>());
    TS_ASSERT_EQUALS(obj->GetNode(0), a01);
    TS_ASSERT_EQUALS(obj->GetNode(1), (rpc::INode*)0);

    root.Replicate(*obj.Get(), *a02);
    TS_ASSERT_EQUALS(obj->GetNode(2), (rpc::INode*)0);

    nstl::vector<rpc::INode*> nodes;
    nodes.push_back(obj->GetNode(0));
    nodes.push_back(obj->GetNode(1));
    TS_ASSERT_IN_VECTOR(nodes, (rpc::INode*)a01);
    TS_ASSERT_IN_VECTOR(nodes, (rpc::INode*)a02);

    TS_ASSERT_EQUALS(obj->GetNode("leaf0"), (rpc::INode*)a01);
    TS_ASSERT_EQUALS(obj->GetNode("leaf1"), (rpc::INode*)a02);
    TS_ASSERT_EQUALS(obj->GetNode("missedLeaf"), (rpc::INode*)0);

    root.Block(*obj.Get(), *a01);
    nodes.clear();
    nodes.push_back(obj->GetNode(0));
    nodes.push_back(obj->GetNode(1));
    TS_ASSERT_IN_VECTOR(nodes, (rpc::INode*)a01);
    TS_ASSERT_IN_VECTOR(nodes, (rpc::INode*)a02);
    TS_ASSERT_EQUALS(obj->GetNode("leaf0"), (rpc::INode*)a01);
    TS_ASSERT_EQUALS(obj->GetNode("leaf1"), (rpc::INode*)a02);

    root.Dereplicate(*obj.Get(), *a01);
    TS_ASSERT_EQUALS(obj->GetNode(0), a02);
    TS_ASSERT_EQUALS(obj->GetNode(1), (rpc::INode*)0);
    TS_ASSERT_EQUALS(obj->GetNode("leaf0"), (rpc::INode*)0);
    TS_ASSERT_EQUALS(obj->GetNode("leaf1"), (rpc::INode*)a02);
  }
};

typedef rpc::SPtrValue<test::RComplexRabbit> QueryTest;

class Test_TestsTODO : public CxxTest::TestSuite, RPCMixin   
{
public:
  void test_NodeDestructionWhileAsyncCallbackOntheWay()
  {

  }
  void test_SerializationWithChecking()
  {
  }
  void test_CallWithPointerToStruct()
  {
  }
  void test_CallWithRemoteObjectCreatedOnTheSameNode()
  {
  }

  void test_ReindexationOfCreatedRemoteEnitities()
  {

  }
  void test_DeletionOfRemoteEntitiesWhenConnectedFromDifferentNodes()
  {

  }

  void test_PatchedEntityCreation()
  {

  }

  void test_NumberOfMethodsInCodeGeneration()
  {
  }

};

class Test_PerfomanceAndLoadTests : public CxxTest::TestSuite, RPCMixin   
{
public:
  void test_MultiThreadedDeletion()
  {
    TwoNodesCase c;
    struct Client0Thread0
    {
		  Client0Thread0(rpc::Gate* gate, rpc::Node* node):
      node(node),
      gate(gate)
      {
        localApi = new test::RemoteApi;
      }

      virtual uint Process(volatile bool& isRunning)
      {
        while (isRunning)
        {
          StrongMT<test::RSimpleRabbit> rabbit = node->Create<test::RSimpleRabbit>();
          rabbits.push_back(rabbit);
          rabbit->processRemoteApi(RemotePtr<test::RRemoteApi>(localApi), false);
          gate->Poll();
          threading::Sleep(0);
        }
        return 0;
      }
      nstl::vector<StrongMT<test::RSimpleRabbit> > rabbits;
      rpc::Node* node;
      StrongMT<test::RemoteApi> localApi;
      rpc::Gate* gate;
    };

    struct Client1Thread0
    {
		  Client1Thread0(rpc::Gate* gate):
      gate(gate)
      {
      }

      virtual uint Process(volatile bool& isRunning)
      {
        while (isRunning)
        {
          gate->Poll();
          threading::Sleep(0);
        }
        return 0;
      }
      rpc::Gate* gate;
    };

    struct Client1Thread1
    {
		  Client1Thread1(rpc::Node* node):
      node(node),
      n(0),
      frame(0)
      {
      }

      virtual uint Process(volatile bool& isRunning)
      {
        while (isRunning)
        {
          test::SimpleRabbit* rabbit = node->get<test::SimpleRabbit>(n);
          if (rabbit)
          {
            rabbits.push_back(rabbit);
            n++;
          }
          if (frame % 5 == 0)
          {
            for (nstl::vector<test::SimpleRabbit*>::iterator it=rabbits.begin();it!=rabbits.end();)
            {
              if ((*it)->rapi != 0)
              {
                (*it)->rapi = 0;
                it = rabbits.erase(it);
              } else {
                ++it;
              }
            }
          }
          frame++;
          threading::Sleep(0);
        }
        return 0;
      }
      rpc::Node* node;
      nstl::vector<test::SimpleRabbit*> rabbits;
      int n;
      int frame;
    };
    /*rpc::EnableLog(1);
    Client0Thread0* c0t0 = new Client0Thread0(c.GetGate("node0"), c.cnode0);
    Client1Thread0* c1t0 = new Client1Thread0(c.GetGate("node1"));
    Client1Thread1* c1t1 = new Client1Thread1(c.cnode1);
    {
      threading::ProcessingThread<Client0Thread0> p00(*c0t0);
      threading::ProcessingThread<Client1Thread0> p10(*c1t0);
      threading::ProcessingThread<Client1Thread1> p11(*c1t1);
      for (int i=0;i<500;++i)
      {
        threading::Sleep(5);
      }
      p11.Stop(true, 5000);
      p10.Stop(true, 5000);
      p00.Stop(true, 5000);
    }
    delete c0t0;
    delete c1t0;
    delete c1t1;
    rpc::EnableLog(0);
    */
  }
  
  struct WorkerThread1
  {
    WorkerThread1(rpc::Node* node, threading::Mutex& _lock):
      node(node),
      lock(_lock)
      {
      }

      virtual uint Process(volatile bool& isRunning)
      {
        while (isRunning)
        {
          lock.Lock();
          StrongMT<test::RSimpleRabbit> rabbit = node->Create<test::RSimpleRabbit>();
          rabbit->process();
          lock.Unlock();
          threading::Sleep(0);
        }
        return 0;
      }
      rpc::Node* node;
      threading::Mutex& lock;
  };

  void test_MultiThreadedLocalProcessing()
  {
    TwoNodesCase c;
    int threadsCount = 2;
    nstl::vector<WorkerThread1*> workers;
    nstl::vector<threading::ProcessingThread<WorkerThread1> *> threads;
    threading::Mutex lock;
    for (int i=0;i<threadsCount;++i)
    {
      WorkerThread1* worker = new WorkerThread1(c.cnode0, lock);
      workers.push_back(worker);
      threading::ProcessingThread<WorkerThread1>* thread = new threading::ProcessingThread<WorkerThread1>(*worker);
      threads.push_back(thread);
    }
    for (int i=0;i<10;++i)
    {
      lock.Lock();
      c.Poll();
      lock.Unlock();
    }
    for (int i=0;i<threads.size();++i)
    {
      threads[i]->Stop(true);
      delete threads[i];
      delete workers[i];
    } 
  }
  
  struct WorkerThread2
  {
    WorkerThread2()
    {
      value = new rpc::RValue<int>;
    }
    virtual uint Process(volatile bool& isRunning)
    {
      while (isRunning)
      {
        for (int i=0;i<items.size();++i)
        {
          items[i]->processIntWithReturnValueIntAsync(i, value.Get(), &rpc::RValue<int>::OnCall);
        }
        threading::Sleep(10);
      }
      return 0;
    }
    StrongMT<rpc::RValue<int> > value;
    nstl::vector<StrongMT<test::RComplexRabbit> > items;
  };

  void test_MultiThreadedCallMethodWithReturnValue()
  {
    TwoNodesCase c;

    const int threadsCount = 2;

    nstl::vector<WorkerThread2*> workers;
    nstl::vector<threading::ProcessingThread<WorkerThread2> *> threads;
    for (int i=0;i<threadsCount;++i)
    {
      WorkerThread2* worker = new WorkerThread2();
      workers.push_back(worker);
      threading::ProcessingThread<WorkerThread2>* thread = new threading::ProcessingThread<WorkerThread2>(*worker, false);
      threads.push_back(thread);
    }
    const int entitiesCount = 20;
    for (int i=0;i<entitiesCount;++i)
    {
      StrongMT<test::RComplexRabbit> rabbit = c.cnode0->Create<test::RComplexRabbit>();     
      workers[i % threadsCount]->items.push_back(rabbit);
    }
    for (int i=0;i<threads.size();++i)
    {
      threads[i]->Resume();
    } 

    const int stepsCount = 10;
    for (int i=0;i<stepsCount;++i)
    {
      c.Poll();
    }

    for (int i=0;i<threads.size();++i)
    {
      threads[i]->Stop(true);
      delete threads[i];
      delete workers[i];
    } 
  }   
};

class Test_CorruptionAndBadSituations : public CxxTest::TestSuite, RPCMixin   
{
public:

  void CheckCorruption(void (*func)(rpc::MethodCall&)=0, int (*func2)(byte* buffer, int size)=0)
  {
    StrongMT<test::MockCorruptedPacketProcessor> processor0 = new test::MockCorruptedPacketProcessor;
    StrongMT<test::MockCorruptedPacketProcessor> processor1 = new test::MockCorruptedPacketProcessor;

    TwoNodesCase c(processor0, processor1);

    StrongMT<test::RComplexRabbit> client_object(c.cnode0->Create<test::RComplexRabbit>());

    test::ComplexRabbit* server_object = waitForEntity<test::ComplexRabbit>(c.cnode1, 0, c);

    rpc::MethodCall call(0, 0);
    call.Prepare(2).Push(2.f);

    if (func)
    {
      (*func)(call);
    }

    MemoryStream stream;
    call.info.SerializeCall(stream, 0);

    byte* buffer = (byte*)stream.GetBuffer();
    uint size = stream.GetPosition();

    if (func2)
    {
      size = (*func2)(buffer, size);
    }

    c.cnode0->GetPipe()->Send(buffer, size, false);
    rpc::IPacketPipe* expectedCorruptedPipe = c.cnode1->GetPipe();
    {
      test::AssertDisabler d;
      c.Poll();
    }
    TS_ASSERT_EQUALS(expectedCorruptedPipe, processor1->corruptedPipe);
  }

  static void CorruptParams(rpc::MethodCall& call)
  {
    for (int i=0;i<call.info.data.size();++i)
    {
      call.info.data[i] = rpc::ParamsCount;
    }
  }

  static int CorruptParamsCount(byte* buffer, int size)
  {
    rpc::MethodCallHeader* header = (rpc::MethodCallHeader*)buffer;
    header->paramsCount = 0;
    return size-5;
  }

  static void CorruptMethodType(rpc::MethodCall& call)
  {
    call.info.header.id = rpc::__TheLastOne__;
  }

  static void CorruptMethodId(rpc::MethodCall& call)
  {
    call.info.header.id = rpc::__TheLastOne__; // this method is not reserved and not used in Rabbit class
  }

  void test_CorruptedPacket_PatchedParams()
  {
    CheckCorruption(CorruptParams);
    CheckCorruption(0, CorruptParamsCount);
    CheckCorruption(CorruptMethodType);
    CheckCorruption(CorruptMethodId);
  }

  void test_CorruptedPacket_NoMessage()
  {
    StrongMT<test::MockCorruptedPacketProcessor> processor0 = new test::MockCorruptedPacketProcessor;
    StrongMT<test::MockCorruptedPacketProcessor> processor1 = new test::MockCorruptedPacketProcessor;

    TwoNodesCase c(processor0, processor1);

    StrongMT<test::RComplexRabbit> client_object(c.cnode0->Create<test::RComplexRabbit>());

    test::ComplexRabbit* server_object = waitForEntity<test::ComplexRabbit>(c.cnode1, 0, c);

    c.cnode1->GetPipe()->Send((const byte*)"12314", 5, false);
    rpc::IPacketPipe* expectedCorruptedNode = c.cnode0->GetPipe();
    {
      test::AssertDisabler d;
      c.Poll();
    }
    TS_ASSERT_EQUALS(expectedCorruptedNode, processor0->corruptedPipe);
  }

  void test_CorruptedPacket_FailedSerialization()
  {
    StrongMT<test::MockCorruptedPacketProcessor> processor0 = new test::MockCorruptedPacketProcessor;
    StrongMT<test::MockCorruptedPacketProcessor> processor1 = new test::MockCorruptedPacketProcessor;

    TwoNodesCase c(processor0, processor1);

    StrongMT<test::RComplexRabbit> client_object(c.cnode0->Create<test::RComplexRabbit>());

    test::ComplexRabbit* server_object = waitForEntity<test::ComplexRabbit>(c.cnode1, 0, c);

    byte data[6];
    *((int*)data) = 0xBAADF00D;
    data[4] = 4;
    data[5] = 7;

    c.cnode1->GetPipe()->Send(data, 6, false);
    rpc::IPacketPipe* expectedCorruptedNode = c.cnode0->GetPipe();
    {
      test::AssertDisabler d;
      c.Poll();
    }
    TS_ASSERT_EQUALS(expectedCorruptedNode, processor0->corruptedPipe);
  }
};

class Test_LocalAndRemotePointersAsParams : public CxxTest::TestSuite, RPCMixin   
{
public:
  void test_CallTwoLocalApis()
  {
    TwoNodesCase c;
    StrongMT<test::RemoteApi> localApi0 = new test::RemoteApi;
    StrongMT<test::RemoteApi> localApi1 = new test::RemoteApi;

    // creation of dummy object
    StrongMT<test::RSimpleRabbit> dummyObject(c.cnode1->Create<test::RSimpleRabbit>()); 
    waitForEntity<test::SimpleRabbit>(c.cnode0, 0, c);

    StrongMT<test::RSimpleRabbit> clientObject(c.cnode0->Create<test::RSimpleRabbit>()); 
    test::SimpleRabbit* serverObject = waitForEntity<test::SimpleRabbit>(c.cnode1, 0, c); 

    clientObject->processRemoteApi(RemotePtr<test::RRemoteApi>(localApi0), false);
    TS_WAIT_FOR(serverObject->rapi != 0, 100);

    serverObject->rapi->callRemote();
    TS_WAIT_FOR(localApi0->processedCount == 1, 100);

    clientObject->processRemoteApi(RemotePtr<test::RRemoteApi>(localApi1), false);
    c.Poll(); // remake

    serverObject->rapi->callRemote();
    TS_WAIT_FOR(localApi1->processedCount == 1, 100);
  }

  void test_CallOneLocalApisTwoTimes()
  {
    rpc::EnableLog(1);
    TwoNodesCase c;
    StrongMT<test::RemoteApi> localApi = new test::RemoteApi;

    StrongMT<test::RSimpleRabbit> clientObject0(c.cnode0->Create<test::RSimpleRabbit>()); 
    clientObject0->processRemoteApi(RemotePtr<test::RRemoteApi>(localApi), true);
    StrongMT<test::RSimpleRabbit> clientObject1(c.cnode0->Create<test::RSimpleRabbit>()); 
    clientObject1->processRemoteApi(RemotePtr<test::RRemoteApi>(localApi), false);

    test::SimpleRabbit* serverObject0 = waitForEntity<test::SimpleRabbit>(c.cnode1, 0, c); 
    test::SimpleRabbit* serverObject1 = waitForEntity<test::SimpleRabbit>(c.cnode1, 1, c); 
    TS_WAIT_FOR(serverObject1->rapi != 0, 100);

    localApi = 0;
    serverObject1->rapi = 0;
    for (int i=0;i<5;++i)
    {
      c.Poll();
    }
    rpc::EnableLog(0);
  }

  void test_DeletionOfLocalApi()
  {
    TwoNodesCase c;
    StrongMT<test::RemoteApi> localApi0 = new test::RemoteApi;

    // creation of dummy object
    StrongMT<test::RSimpleRabbit> clientObject(c.cnode0->Create<test::RSimpleRabbit>()); 
    test::SimpleRabbit* serverObject = waitForEntity<test::SimpleRabbit>(c.cnode1, 0, c); 

    clientObject->processRemoteApi(RemotePtr<test::RRemoteApi>(localApi0), false);
    TS_WAIT_FOR(serverObject->rapi != 0, 100);

    StrongMT<test::RRemoteApi> api = serverObject->rapi;
    TS_ASSERT_EQUALS(true, api->GetHandler()->IsConnected());
    c.Disconnect(false, true);
    TS_WAIT_FOR(api->GetHandler()->IsConnected() == false, 100);
  }

  void test_CallLocalApiTwoTimes()
  {
    TwoNodesCase c;
    StrongMT<test::RemoteApi> localApi = new test::RemoteApi;

    StrongMT<test::RSimpleRabbit> clientObject(c.cnode0->Create<test::RSimpleRabbit>()); 

    clientObject->processRemoteApi(RemotePtr<test::RRemoteApi>(localApi), false);
    clientObject->processRemoteApi(RemotePtr<test::RRemoteApi>(localApi), false);
  }

  void test_SecondLocalApiProcessing()
  {
    ManyToManyCase c;

    StrongMT<test::RemoteApi> localApi = new test::RemoteApi;

    rpc::Gate& root = c.AddGate("root");
    {
      rpc::Gate& leaf0 = c.AddGate("leaf0");
      c.ConnectGates(root, leaf0);
      c.WaitForConnections();

      rpc::Node* a01 = c.GetNode(root, leaf0);
      rpc::Node* a10 = c.GetNode(leaf0, root);

      StrongMT<test::RSimpleRabbit> obj = a01->Create<test::RSimpleRabbit>();
      test::SimpleRabbit* serverObject = waitForEntity<test::SimpleRabbit>(a10, 0, c); 
      obj->processRemoteApi(RemotePtr<test::RRemoteApi>(localApi), false);
      TS_WAIT_FOR(serverObject->rapi != 0, 100);
      serverObject->rapi = 0;
      c.Poll();
      c.Poll();
      obj->processRemoteApi(RemotePtr<test::RRemoteApi>(localApi), false); // should be no assert here
    }
  }


  void test_CallWithLocalApiAsConstructorParam()
  {
    TwoNodesCase c;
    StrongMT<test::RemoteApi> localApi = new test::RemoteApi;
    StrongMT<test::RSimpleRabbit> client_object(c.cnode0->Create<test::RSimpleRabbit>(RemotePtr<test::RRemoteApi>(localApi), short(124))); 

    test::SimpleRabbit* server_object = waitForEntity<test::SimpleRabbit>(c.cnode1, 0, c); 

    client_object->processApi();
    TS_WAIT_FOR(localApi->processedCount == 1, 100);
  }

  void test_CallWithLocalApiAsConstructorParamAndThenReplicate()
  {
    OneToManyCase c("root");

    rpc::Gate& root = c.GetRootGate();
    rpc::Gate& leaf0 = c.AddConnectedGate("leaf0");
    rpc::Gate& leaf1 = c.AddConnectedGate("leaf1");

    rpc::Node* a01 = c.GetNode(root, leaf0);
    rpc::Node* a10 = c.GetNode(leaf0, root);
    rpc::Node* a02 = c.GetNode(root, leaf1 );
    rpc::Node* a20 = c.GetNode(leaf1, root );

    TS_WAIT_FOR(c.IsConnected(), 100);

    StrongMT<test::RemoteApi> localApi = new test::RemoteApi(555);
    StrongMT<test::RSimpleRabbit> client_object = a10->Create<test::RSimpleRabbit>(RemotePtr<test::RRemoteApi>(localApi, 555), short(124)); 

    test::SimpleRabbit* server_object = waitForEntity<test::SimpleRabbit>(a01, 0, c); 
    root.Replicate(*server_object->api.Get(), *a02);

    test::RemoteApi* replicatedObject = waitForEntity<test::RemoteApi>(a20, 0, c);
    //TS_ASSERT_EQUALS(555, replicatedObject->param0);     
  }

  void test_CallWithLocalApiAsMethodParam()
  {
    TwoNodesCase c;
    StrongMT<test::RemoteApi> localApi = new test::RemoteApi;
    StrongMT<test::RSimpleRabbit> client_object(c.cnode0->Create<test::RSimpleRabbit>()); 

    test::SimpleRabbit* server_object = waitForEntity<test::SimpleRabbit>(c.cnode1, 0, c); 

    client_object->processLocalRemoteApi(RemotePtr<test::RRemoteApi>(localApi));
    TS_WAIT_FOR(localApi->processedCount == 1, 100);
  }

  void test_CallLocalApiSecondRegistration()
  {
    TwoNodesCase c;
    StrongMT<test::RemoteApi> localApi = new test::RemoteApi;
    StrongMT<test::RSimpleRabbit> clientObject0(c.cnode1->Create<test::RSimpleRabbit>(RemotePtr<test::RRemoteApi>(localApi), short(124))); 
    StrongMT<test::RSimpleRabbit> clientObject1(c.cnode1->Create<test::RSimpleRabbit>(RemotePtr<test::RRemoteApi>(localApi), short(124))); 

    c.Poll();

    clientObject0->processApi();
    clientObject1->processApi();
    TS_WAIT_FOR(localApi->processedCount != 0, 100);
    TS_WAIT_FOR(localApi->processedCount == 2, 100);
  }

  void test_CallApiMissedFactory()
  {
    TwoNodesCase c;
    StrongMT<test::MissedRemoteApi> localApi = new test::MissedRemoteApi;
    test::AssertDisabler d;
    rpc::IRemoteEntity* r = RemotePtr(localApi);
    StrongMT<test::RSimpleRabbit> clientObject(c.cnode1->Create<test::RSimpleRabbit>(r, short(124))); 
    TS_ASSERT_EQUALS((test::RSimpleRabbit*)0, clientObject.Get()); 
  }

  void test_CallWithRemoteEntityAsParam()
  {
    ManyToManyCase c;
    StrongMT<test::MockCorruptedPacketProcessor> rootP = new test::MockCorruptedPacketProcessor("root", &c);
    StrongMT<test::MockCorruptedPacketProcessor> leaf0P = new test::MockCorruptedPacketProcessor("leaf0", &c);
    StrongMT<test::MockCorruptedPacketProcessor> leaf1P = new test::MockCorruptedPacketProcessor("leaf1", &c);

    rpc::Gate& root = c.AddGate("root", rootP);
    rpc::Gate& leaf0 = c.AddGate("leaf0", leaf0P);
    rpc::Gate& leaf1 = c.AddGate("leaf1", leaf1P);
    c.ConnectGates(root, leaf0);
    c.ConnectGates(root, leaf1);
    c.WaitForConnections();

    rpc::Node* a01 = c.GetNode(root, leaf0);
    rpc::Node* a02 = c.GetNode(root, leaf1);
    rpc::Node* a10 = c.GetNode(leaf0, root);
    rpc::Node* a20 = c.GetNode(leaf1, root);

    StrongMT<test::RRemoteApi> api = a01->Create<test::RRemoteApi>();
    StrongMT<test::RSimpleRabbit> obj = a02->Create<test::RSimpleRabbit>();
    test::RemoteApi* lapi = waitForEntity<test::RemoteApi>(a10, 0, c); 
    test::SimpleRabbit* lobj= waitForEntity<test::SimpleRabbit>(a20, 1, c); 
    obj->processRemoteApi(api, false);
    TS_WAIT_FOR(lobj->rapi != 0, 100);
    lobj->rapi->callRemote();
    TS_WAIT_FOR(lapi->processedCount == 1, 100);

    lobj->rapi->callRemote();
    TS_WAIT_FOR(lapi->processedCount == 2, 100);

    obj->processRemoteApi(api, false);
    c.Poll();
  }

  void test_DifferentChannels()
  {
    ManyToManyCase c;
    StrongMT<test::MockCorruptedPacketProcessor> gsP = new test::MockCorruptedPacketProcessor("gs", &c);
    StrongMT<test::MockCorruptedPacketProcessor> lobbyP = new test::MockCorruptedPacketProcessor("lobby", &c);
    StrongMT<test::MockCorruptedPacketProcessor> gcP = new test::MockCorruptedPacketProcessor("gc", &c);

    rpc::Gate& gs = c.AddGate("gs", gsP);
    rpc::Gate& lobby = c.AddGate("lobby", lobbyP);
    rpc::Gate& gc = c.AddGate("gc", gcP);
    c.ConnectGates(lobby, gs);
    c.ConnectGates(lobby, gc);
    c.WaitForConnections();

    rpc::Node* lobby_gs = c.GetNode(lobby, gs);
    rpc::Node* gs_lobby = c.GetNode(gs, lobby);
    rpc::Node* lobby_gc = c.GetNode(lobby, gc);
    rpc::Node* gc_lobby = c.GetNode(gc, lobby);

    StrongMT<test::RSimpleRabbit> api = lobby_gs->Create<test::RSimpleRabbit>();
    StrongMT<test::RSimpleRabbit> obj = lobby_gc->Create<test::RSimpleRabbit>();
    test::SimpleRabbit* lapi = waitForEntity<test::SimpleRabbit>(gs_lobby, 0, c); 
    test::SimpleRabbit* lobj = waitForEntity<test::SimpleRabbit>(gc_lobby, 1, c); 
    lapi->localApiGateName = "gsr";
    obj->processSimpleRabbit(api);
    TS_WAIT_FOR(lobj->rabbit != 0, 100);


    StrongMT<rpc::SPtrValue<test::RRemoteApi> > q = new rpc::SPtrValue<test::RRemoteApi>;

    lobj->rabbit->GetLocalRemoteApi(q.Get(), &rpc::SPtrValue<test::RRemoteApi>::OnCall);
    TS_WAIT_FOR(q->IsSet() == true, 100);

    //q->Get()->callRemote();
    //TS_WAIT_FOR(lapi->localApi->processedCount == 1, 100); // to uncomment this issue we need to refactor ManyToManyCase to support multiple pipe names but single id
  }

  void test_CallWithQueiredRemoteEntityAsParam()
  {
    ManyToManyCase c;
    StrongMT<test::MockCorruptedPacketProcessor> rootP = new test::MockCorruptedPacketProcessor("root", &c);
    StrongMT<test::MockCorruptedPacketProcessor> leaf0P = new test::MockCorruptedPacketProcessor("leaf0", &c);
    StrongMT<test::MockCorruptedPacketProcessor> leaf1P = new test::MockCorruptedPacketProcessor("leaf1", &c);

    rpc::Gate& root = c.AddGate("root", rootP);
    rpc::Gate& leaf0 = c.AddGate("leaf0", leaf0P);
    rpc::Gate& leaf1 = c.AddGate("leaf1", leaf1P);

    c.ConnectGates(root, leaf0);
    c.ConnectGates(root, leaf1);

    rpc::Node* a01 = c.GetNode(root, leaf0);
    rpc::Node* a02 = c.GetNode(root, leaf1);
    rpc::Node* a10 = c.GetNode(leaf0, root);
    rpc::Node* a20 = c.GetNode(leaf1, root);

    StrongMT<test::RemoteApi> oobj = new test::RemoteApi;
    leaf0.RegisterObject(oobj, "rpc://megaobject");

    StrongMT<rpc::SPtrValue<test::RRemoteApi> > q = new rpc::SPtrValue<test::RRemoteApi>;
    a01->Query<test::RRemoteApi>("rpc://megaobject", q.Get(), &rpc::SPtrValue<test::RRemoteApi>::OnCall);

    StrongMT<test::RSimpleRabbit> obj = a02->Create<test::RSimpleRabbit>();
    TS_WAIT_FOR(q->IsSet(), 100);
    StrongMT<test::RRemoteApi> api = q->Get();

    test::SimpleRabbit* lobj= waitForEntity<test::SimpleRabbit>(a20, 1, c); 
    obj->processRemoteApi(api, false);
    TS_WAIT_FOR(lobj->rapi != 0, 100);
    lobj->rapi->callRemoteParam(555);
    TS_WAIT_FOR(oobj->processedCount == 1, 100);

    lobj->rapi->callRemote();
    TS_WAIT_FOR(oobj->processedCount == 2, 100);

    obj->processRemoteApi(api, false);
    c.Poll();
  }

  void test_CallWithRemoteEntityAsParamAndConnectionOnCall()
  {
    ManyToManyCase c;
    StrongMT<test::MockCorruptedPacketProcessor> rootP = new test::MockCorruptedPacketProcessor("root", &c);
    StrongMT<test::MockCorruptedPacketProcessor> leaf0P = new test::MockCorruptedPacketProcessor("leaf0", &c);
    StrongMT<test::MockCorruptedPacketProcessor> leaf1P = new test::MockCorruptedPacketProcessor("leaf1", &c);
    

    rpc::Gate& root = c.AddGate("root", rootP);
    rpc::Gate& leaf0 = c.AddGate("leaf0", leaf0P);
    rpc::Gate& leaf1 = c.AddGate("leaf1", leaf1P);
    c.ConnectGates(root, leaf0);
    c.ConnectGates(root, leaf1);
    c.WaitForConnections();

    rpc::Node* a01 = c.GetNode(root, leaf0);
    rpc::Node* a02 = c.GetNode(root, leaf1);
    rpc::Node* a10 = c.GetNode(leaf0, root);
    rpc::Node* a20 = c.GetNode(leaf1, root);

    StrongMT<test::RRemoteApi> api = a01->Create<test::RRemoteApi>();
    StrongMT<test::RSimpleRabbit> obj = a02->Create<test::RSimpleRabbit>();
    test::RemoteApi* lapi = waitForEntity<test::RemoteApi>(a10, 0, c); 
    test::SimpleRabbit* lobj= waitForEntity<test::SimpleRabbit>(a20, 1, c); 
    obj->processRemoteApi(api, false);
    TS_WAIT_FOR(lobj->rapi != 0, 100);
    TS_ASSERT_EQUALS(0, leaf1P->connections.size());      
    lobj->rapi->callRemote();
    TS_ASSERT_EQUALS(1, leaf1P->connections.size());
    assertEquals("leaf0", leaf1P->connections[0].c_str());
    TS_WAIT_FOR(lapi->processedCount == 1, 100);

    lobj->rapi->callRemote();
    TS_WAIT_FOR(lapi->processedCount == 2, 100);

    obj->processRemoteApi(api, false);
    c.Poll();
  }

  void test_RemotePointerAsReturnValue()
  {
    ManyToManyCase c;
    StrongMT<test::MockCorruptedPacketProcessor> rootP = new test::MockCorruptedPacketProcessor("root", &c);
    StrongMT<test::MockCorruptedPacketProcessor> leaf0P = new test::MockCorruptedPacketProcessor("leaf0", &c);
    StrongMT<test::MockCorruptedPacketProcessor> leaf1P = new test::MockCorruptedPacketProcessor("leaf1", &c);

    rpc::Gate& root = c.AddGate("root", rootP);
    rpc::Gate& leaf0 = c.AddGate("leaf0", leaf0P);
    rpc::Gate& leaf1 = c.AddGate("leaf1", leaf1P);
    c.ConnectGates(root, leaf0);
    c.ConnectGates(root, leaf1);
    c.WaitForConnections();

    rpc::Node* a01 = c.GetNode(root, leaf0);
    rpc::Node* a02 = c.GetNode(root, leaf1);
    rpc::Node* a10 = c.GetNode(leaf0, root);
    rpc::Node* a20 = c.GetNode(leaf1, root);

    StrongMT<test::RRemoteApi> api = a01->Create<test::RRemoteApi>();
    StrongMT<test::RSimpleRabbit> obj = a02->Create<test::RSimpleRabbit>();
    test::RemoteApi* lapi = waitForEntity<test::RemoteApi>(a10, 0, c); 
    test::SimpleRabbit* lobj= waitForEntity<test::SimpleRabbit>(a20, 1, c); 
    obj->processRemoteApi(api, false);
    TS_WAIT_FOR(lobj->rapi != 0, 100);

    StrongMT<rpc::SPtrValue<test::RRemoteApi> > t = new rpc::SPtrValue<test::RRemoteApi>;
    obj->GetRRemoteApi(t.Get(), &rpc::SPtrValue<test::RRemoteApi>::OnCall);
    TS_WAIT_FOR(t->IsSet() == true, 100);
    t->result->callRemote();
    TS_WAIT_FOR(lapi->processedCount == 1, 100); 
  }

  void test_LocalRemotePointerAsReturnValue()
  {
    ManyToManyCase c;
    rpc::Gate& root = c.AddGate("root");
    rpc::Gate& leaf0 = c.AddGate("leaf0");
    c.ConnectGates(root, leaf0);
    c.WaitForConnections();

    rpc::Node* a01 = c.GetNode(root, leaf0);
    rpc::Node* a10 = c.GetNode(leaf0, root);

    StrongMT<test::RSimpleRabbit> obj = a01->Create<test::RSimpleRabbit>();
    test::SimpleRabbit* lobj= waitForEntity<test::SimpleRabbit>(a10, 0, c); 

    {
      StrongMT<rpc::SPtrValue<test::RRemoteApi> > t0 = new rpc::SPtrValue<test::RRemoteApi>;
      {
        StrongMT<rpc::SPtrValue<test::RRemoteApi> > t = new rpc::SPtrValue<test::RRemoteApi>;
        obj->GetLocalRemoteApi(t.Get(), &rpc::SPtrValue<test::RRemoteApi>::OnCall);
        TS_WAIT_FOR(t->IsSet() == true, 100);
        t->result->callRemote();
        TS_WAIT_FOR(lobj->localApi->processedCount == 1, 100);

        obj->GetLocalRemoteApi(t0.Get(), &rpc::SPtrValue<test::RRemoteApi>::OnCall);
        TS_WAIT_FOR(t0->IsSet() == true, 100);
      }
      t0->result->callRemote();
      TS_WAIT_FOR(lobj->localApi->processedCount == 2, 100);
    }
    c.Poll();
  }

  void test_DeletionOfTransferredRemotePointer()
  {
    {
      ManyToManyCase c;
      test::RemoteApi::Reset();
      {
        StrongMT<test::MockCorruptedPacketProcessor> rootP = new test::MockCorruptedPacketProcessor("root", &c);
        StrongMT<test::MockCorruptedPacketProcessor> leaf0P = new test::MockCorruptedPacketProcessor("leaf0", &c);
        StrongMT<test::MockCorruptedPacketProcessor> leaf1P = new test::MockCorruptedPacketProcessor("leaf1", &c);

        rpc::Gate& root = c.AddGate("root", rootP);
        rpc::Gate& leaf0 = c.AddGate("leaf0", leaf0P);
        rpc::Gate& leaf1 = c.AddGate("leaf1", leaf1P);
        c.ConnectGates(root, leaf0);
        c.ConnectGates(root, leaf1);
        c.WaitForConnections();

        rpc::Node* a01 = c.GetNode(root, leaf0);
        rpc::Node* a02 = c.GetNode(root, leaf1);
        rpc::Node* a10 = c.GetNode(leaf0, root);
        rpc::Node* a20 = c.GetNode(leaf1, root);

        TS_ASSERT_EQUALS(0, test::RemoteApi::constructorsCalled);
        StrongMT<test::RRemoteApi> api = a01->Create<test::RRemoteApi>();
        test::RemoteApi* lapi = waitForEntity<test::RemoteApi>(a10, 0, c); 
        TS_ASSERT_EQUALS(1, test::RemoteApi::constructorsCalled); 

        StrongMT<test::RSimpleRabbit> obj = a02->Create<test::RSimpleRabbit>();
        test::SimpleRabbit* lobj= waitForEntity<test::SimpleRabbit>(a20, 1, c); 
        TS_ASSERT_EQUALS(2, test::RemoteApi::constructorsCalled);  // localApi in SimpleRabbit was created

        obj->processRemoteApi(api, false);
        TS_WAIT_FOR(lobj->rapi != 0, 100);

        lobj->rapi = 0;
        for (int i=0;i<10;++i)
        {
          c.Poll();
        }
        TS_ASSERT_EQUALS(0, test::RemoteApi::destructorsCalled);
      }
      TS_WAIT_FOR(test::RemoteApi::destructorsCalled == 1, 100); // because of addRef while SharePtr
    }
    TS_ASSERT_EQUALS(2, test::RemoteApi::destructorsCalled);  
  }

  void test_DeletionOfRemotePointerWhileTransferOnTheWay()
  {
    ManyToManyCase c;
    test::RemoteApi::Reset();
    StrongMT<test::MockCorruptedPacketProcessor> rootP = new test::MockCorruptedPacketProcessor("root", &c);
    StrongMT<test::MockCorruptedPacketProcessor> leaf0P = new test::MockCorruptedPacketProcessor("leaf0", &c);
    StrongMT<test::MockCorruptedPacketProcessor> leaf1P = new test::MockCorruptedPacketProcessor("leaf1", &c);

    rpc::Gate& root = c.AddGate("root", rootP);
    rpc::Gate& leaf0 = c.AddGate("leaf0", leaf0P);
    rpc::Gate& leaf1 = c.AddGate("leaf1", leaf1P);
    c.ConnectGates(root, leaf0);
    c.ConnectGates(root, leaf1);
    c.WaitForConnections();

    rpc::Node* a01 = c.GetNode(root, leaf0);
    rpc::Node* a02 = c.GetNode(root, leaf1);
    rpc::Node* a10 = c.GetNode(leaf0, root);
    rpc::Node* a20 = c.GetNode(leaf1, root);

    StrongMT<test::RRemoteApi> api = a01->Create<test::RRemoteApi>();
    test::RemoteApi* lapi = waitForEntity<test::RemoteApi>(a10, 0, c); 

    StrongMT<test::RSimpleRabbit> obj = a02->Create<test::RSimpleRabbit>();
    test::SimpleRabbit* lobj= waitForEntity<test::SimpleRabbit>(a20, 1, c); 

    obj->processRemoteApi(api, false);
    /*api = 0;
    for (int i=0;i<20;++i) // poll only root and leaf0
    {
      root.Poll();
      leaf0.Poll();
    }
    TS_WAIT_FOR(lobj->rapi != 0, 100);
    lobj->rapi->Update();*/
    for (int i=0;i<20;++i)
      c.Poll();
  }

  void test_CallWithRemoteEntityAsConstructorParam()
  {
    ManyToManyCase c;
    StrongMT<test::MockCorruptedPacketProcessor> rootP = new test::MockCorruptedPacketProcessor("root", &c);
    StrongMT<test::MockCorruptedPacketProcessor> leaf0P = new test::MockCorruptedPacketProcessor("leaf0", &c);
    StrongMT<test::MockCorruptedPacketProcessor> leaf1P = new test::MockCorruptedPacketProcessor("leaf1", &c);

    rpc::Gate& root = c.AddGate("root", rootP);
    rpc::Gate& leaf0 = c.AddGate("leaf0", leaf0P);
    rpc::Gate& leaf1 = c.AddGate("leaf1", leaf1P);
    c.ConnectGates(root, leaf0);
    c.ConnectGates(root, leaf1);

    rpc::Node* a01 = c.GetNode(root, leaf0);
    rpc::Node* a02 = c.GetNode(root, leaf1);
    rpc::Node* a10 = c.GetNode(leaf0, root);
    rpc::Node* a20 = c.GetNode(leaf1, root);
    TS_WAIT_FOR(c.IsConnected(), 100);

    StrongMT<test::RRemoteApi> api = a01->Create<test::RRemoteApi>();
    StrongMT<test::RSimpleRabbit> obj = a02->Create<test::RSimpleRabbit>(api, short(1234), short(1234), short(1234));
    test::RemoteApi* lapi = waitForEntity<test::RemoteApi>(a10, 0, c); 
    test::SimpleRabbit* lobj= waitForEntity<test::SimpleRabbit>(a20, 1, c); 
    obj->processRemoteApi(api, false);
    TS_WAIT_FOR(lobj->rapi != 0, 100);
    lobj->api->callRemote();
    TS_WAIT_FOR(lapi->processedCount == 1, 100);

    lobj->api->callRemote();
    TS_WAIT_FOR(lapi->processedCount == 2, 100);
  }

  void test_CallWithRemoteEntityAsConstructorParamPushedAsPointer()
  {
    ManyToManyCase c;
    StrongMT<test::MockCorruptedPacketProcessor> rootP = new test::MockCorruptedPacketProcessor("root", &c);
    StrongMT<test::MockCorruptedPacketProcessor> leaf0P = new test::MockCorruptedPacketProcessor("leaf0", &c);
    StrongMT<test::MockCorruptedPacketProcessor> leaf1P = new test::MockCorruptedPacketProcessor("leaf1", &c);

    rpc::Gate& root = c.AddGate("root", rootP);
    rpc::Gate& leaf0 = c.AddGate("leaf0", leaf0P);
    rpc::Gate& leaf1 = c.AddGate("leaf1", leaf1P);
    c.ConnectGates(root, leaf0);
    c.ConnectGates(root, leaf1);

    rpc::Node* a01 = c.GetNode(root, leaf0);
    rpc::Node* a02 = c.GetNode(root, leaf1);
    rpc::Node* a10 = c.GetNode(leaf0, root);
    rpc::Node* a20 = c.GetNode(leaf1, root);
    TS_WAIT_FOR(c.IsConnected(), 100);

    StrongMT<test::RRemoteApi> api = a01->Create<test::RRemoteApi>();
    StrongMT<test::RSimpleRabbit> obj = a02->Create<test::RSimpleRabbit>(api.Get(), short(1234), short(1234), short(1234));
    test::RemoteApi* lapi = waitForEntity<test::RemoteApi>(a10, 0, c); 
    test::SimpleRabbit* lobj= waitForEntity<test::SimpleRabbit>(a20, 1, c); 
    obj->processRemoteApi(api, false);
    TS_WAIT_FOR(lobj->rapi != 0, 100);
    lobj->api->callRemote();
    TS_WAIT_FOR(lapi->processedCount == 1, 100);

    lobj->api->callRemote();
    TS_WAIT_FOR(lapi->processedCount == 2, 100);
  }

  void test_CallWithNullLocalApiAsMethodParam()
  {
    // !!!!!!!!
  }

  void test_ChainOfRemotePtrCalls()
  {
    ManyToManyCase c;
    StrongMT<test::MockCorruptedPacketProcessor> bsP = new test::MockCorruptedPacketProcessor("BattleServer", &c);
    StrongMT<test::MockCorruptedPacketProcessor> bcP = new test::MockCorruptedPacketProcessor("BattleCoordinator", &c);
    StrongMT<test::MockCorruptedPacketProcessor> aisP = new test::MockCorruptedPacketProcessor("AiServer", &c);
    StrongMT<test::MockCorruptedPacketProcessor> clP = new test::MockCorruptedPacketProcessor("Client", &c);

    rpc::Gate& bs = c.AddGate("BattleServer", bsP);
    rpc::Gate& bc = c.AddGate("BattleCoordinator", bcP);
    rpc::Gate& ais = c.AddGate("AiServer", aisP);
    rpc::Gate& cl = c.AddGate("Client", clP);
    c.ConnectGates(bc, bs);
    c.ConnectGates(bc, ais);
    c.ConnectGates(ais, cl);
    c.WaitForConnections();

    rpc::Node* bc_bs = c.GetNode(bc, bs);
    rpc::Node* bs_bc = c.GetNode(bs, bc);
    rpc::Node* bc_ais = c.GetNode(bc, ais);
    rpc::Node* ais_bc = c.GetNode(ais, bc);
    rpc::Node* ais_cl = c.GetNode(ais, cl);
    rpc::Node* cl_ais = c.GetNode(cl, ais);

    StrongMT<test::RRemoteApi> api = bc_bs->Create<test::RRemoteApi>();
    test::RemoteApi* lapi0 = waitForEntity<test::RemoteApi>(bs_bc, 0, c); 

    StrongMT<test::RSimpleRabbit> bc_aisObject = bc_ais->Create<test::RSimpleRabbit>();
    test::SimpleRabbit* lobj0 = waitForEntity<test::SimpleRabbit>(ais_bc, 1, c); 

    StrongMT<test::RSimpleRabbit> ais_clObject = ais_cl->Create<test::RSimpleRabbit>();
    test::SimpleRabbit* lobj1 = waitForEntity<test::SimpleRabbit>(cl_ais, 0, c); 

    bc_aisObject->processRemoteApi(api, false);
    TS_WAIT_FOR(lobj0->rapi != 0, 100);

    ais_clObject->processRemoteApi(lobj0->rapi, false);
    TS_WAIT_FOR(lobj1->rapi != 0, 100);

    lobj1->rapi->callRemote();
    TS_WAIT_FOR(lapi0->processedCount == 1, 100);

    api = 0;
    lobj1->rapi = 0;
    c.Poll();

    api = bc_bs->Create<test::RRemoteApi>(); 
    test::RemoteApi* lapi1 = waitForEntity<test::RemoteApi>(bs_bc, 2, c); 
    TS_ASSERT_DIFFERS(lapi0, lapi1);
    bc_aisObject->processRemoteApi(api, false);

    test::RRemoteApi* oldApi = lobj0->rapi;
    TS_WAIT_FOR(lobj0->rapi.Get() != oldApi, 100);

    ais_clObject->processRemoteApi(lobj0->rapi, false);
    TS_WAIT_FOR(lobj1->rapi != 0, 100);

    lobj1->rapi->callRemote();
    TS_WAIT_FOR(lapi1->processedCount == 1, 100);
  }

  void test_DeletionOnPtrBeforeLinkWasProcessed()
  {

  }

  void test_NullRemotePointerAsParam()
  {
    TwoNodesCase c;
    test::RemoteApi localApi;

    StrongMT<test::RSimpleRabbit> client_object(c.cnode0->Create<test::RSimpleRabbit>()); 
    test::SimpleRabbit* server_object = waitForEntity<test::SimpleRabbit>(c.cnode1, 0, c); 

    server_object->rapi = new test::RRemoteApi( 0, 0 );
    client_object->processRemoteApi( 0, false );
    TS_WAIT_FOR(server_object->rapi == 0, 100);
  }

  void test_NullRemotePointerAsReturnValue()
  {
    TwoNodesCase c;
    test::RemoteApi localApi;

    StrongMT<test::RSimpleRabbit> client_object(c.cnode0->Create<test::RSimpleRabbit>()); 
    test::SimpleRabbit* server_object = waitForEntity<test::SimpleRabbit>(c.cnode1, 0, c); 

    StrongMT<rpc::SPtrValue<test::RRemoteApi> > t = new rpc::SPtrValue<test::RRemoteApi>;
    client_object->GetRRemoteApi(t.Get(), &rpc::SPtrValue<test::RRemoteApi>::OnCall);
    TS_WAIT_FOR(t->IsSet() == true, 100);
    TS_ASSERT( t->result == 0 );
  }

  void test_DeletionGateDuringCall()
  {
    StrongMT<test::RSimpleRabbit> robj;

    {
      TwoNodesCase c;

      robj = c.cnode0->Create<test::RSimpleRabbit>(); 
      test::SimpleRabbit* server_object = waitForEntity<test::SimpleRabbit>(c.cnode1, 0, c);
    }
    robj->process();
  }

};

class Test_NoFieldsReplication : public CxxTest::TestSuite, RPCMixin   
{
public:
  void test_Replicate()
  {
    OneToManyCase c("root");

    rpc::Gate& root = c.GetRootGate();
    rpc::Gate& leaf0 = c.AddConnectedGate("leaf0");
    rpc::Gate& leaf1 = c.AddConnectedGate("leaf1");

    rpc::Node* a01 = c.GetNode(root, leaf0);
    rpc::Node* a10 = c.GetNode(leaf0, root);
    rpc::Node* a02 = c.GetNode(c.GetRootGate(), leaf1 );
    rpc::Node* a20 = c.GetNode(leaf1, root );
    c.WaitForConnections();

    StrongMT<test::RSimpleRabbit> client_object01(a01->Create<test::RSimpleRabbit>(short(555)));
    test::SimpleRabbit* server_object01 = waitForEntity<test::SimpleRabbit>(a10, 0, c);
    TS_ASSERT_EQUALS(2, server_object01->constructor_number_called);
    TS_ASSERT_EQUALS(555, server_object01->short_creation_param0);
    rpc::LocalEntityCreationInfo info;
    info = factory_SimpleRabbit.infos[factory_SimpleRabbit.infos.size()-1];
    TS_ASSERT_EQUALS(rpc::GetId<test::SimpleRabbit>(), info.classId);
    TS_ASSERT_EQUALS(1, info.paramsCount);
    TS_ASSERT_EQUALS(false, info.isReplicated);

    TS_ASSERT_EQUALS(false, root.IsReplicated(*client_object01, *a02));

    root.Replicate(*client_object01, *a02);
    test::SimpleRabbit* server_object02 = waitForEntity<test::SimpleRabbit>(a20, 0, c);
    TS_ASSERT_EQUALS(2, server_object02->constructor_number_called);
    TS_ASSERT_EQUALS(555, server_object02->short_creation_param0);
    TS_ASSERT_EQUALS(true, root.IsReplicated(*client_object01, *a02));

    info = factory_SimpleRabbit.infos[factory_SimpleRabbit.infos.size()-1];
    TS_ASSERT_EQUALS(rpc::GetId<test::SimpleRabbit>(), info.classId);
    TS_ASSERT_EQUALS(1, info.paramsCount);
    TS_ASSERT_EQUALS(true, info.isReplicated);

    client_object01->process();
    TS_WAIT_FOR(server_object01->is_processed == true, 100);
    TS_WAIT_FOR(server_object02->is_processed == true, 100);
    TS_ASSERT_EQUALS(server_object01->is_processed, true);
    TS_ASSERT_EQUALS(server_object02->is_processed, true);

    root.Dereplicate(*client_object01, *a02);
    c.Poll();
    TS_WAIT_FOR(test::SimpleRabbit::simpleRabbitsCount == 1, 100);
    TS_ASSERT_EQUALS(false, root.IsReplicated(*client_object01, *a02));
  }

  void test_ReplicateToTheSameNode()
  {
    OneToManyCase c("root");

    rpc::Gate& root = c.GetRootGate();
    rpc::Gate& leaf0 = c.AddConnectedGate("leaf0");

    rpc::Node* a01 = c.GetNode(root, leaf0);
    rpc::Node* a10 = c.GetNode(leaf0, root);
    c.WaitForConnections();

    StrongMT<test::RSimpleRabbit> client_object01(a01->Create<test::RSimpleRabbit>(short(555)));
    test::SimpleRabbit* server_object01 = waitForEntity<test::SimpleRabbit>(a10, 0, c);

    test::AssertDisabler d;
    bool result = root.Replicate(*client_object01, *a01);
    TS_ASSERT_EQUALS(false, result);
  }

  void test_BlockNotReplicatedNodeThanUnblock()
  {
    OneToManyCase c("root");

    rpc::Gate& root = c.GetRootGate();
    rpc::Gate& leaf0 = c.AddConnectedGate("leaf0");
    rpc::Gate& leaf1 = c.AddConnectedGate("leaf1");

    rpc::Node* a01 = c.GetNode(root, leaf0);
    rpc::Node* a10 = c.GetNode(leaf0, root);
    rpc::Node* a02 = c.GetNode(c.GetRootGate(), leaf1 );
    rpc::Node* a20 = c.GetNode(leaf1, root );
    c.WaitForConnections();

    StrongMT<test::RSimpleRabbit> client_object01(a01->Create<test::RSimpleRabbit>(short(555)));
    test::SimpleRabbit* server_object01 = waitForEntity<test::SimpleRabbit>(a10, 0, c);

    root.Block(*client_object01, *a02);
    c.Poll();

    root.Unblock(*client_object01, *a02);
    test::SimpleRabbit* server_object02 = waitForEntity<test::SimpleRabbit>(a20, 0, c);
  }

  void test_BlockNotReplicatedNodeThanUnblockWithNoReplicate()
  {
    OneToManyCase c("root");

    rpc::Gate& root = c.GetRootGate();
    rpc::Gate& leaf0 = c.AddConnectedGate("leaf0");
    rpc::Gate& leaf1 = c.AddConnectedGate("leaf1");

    rpc::Node* a01 = c.GetNode(root, leaf0);
    rpc::Node* a10 = c.GetNode(leaf0, root);
    rpc::Node* a02 = c.GetNode(c.GetRootGate(), leaf1 );
    rpc::Node* a20 = c.GetNode(leaf1, root );
    c.WaitForConnections();

    StrongMT<test::RSimpleRabbit> client_object01(a01->Create<test::RSimpleRabbit>(short(555)));
    test::SimpleRabbit* server_object01 = waitForEntity<test::SimpleRabbit>(a10, 0, c);

    root.Block(*client_object01, *a02);
    c.Poll();

    TS_ASSERT_EQUALS(false, root.UnblockWithoutReplicate(*client_object01, *a02));
    c.Poll();
    c.Poll();
    waitForMissedEntity<test::SimpleRabbit>(a20, 0, c);
  }

  void test_MultiThreadedProcessing()
  {
    OneToManyCase c("root");
    rpc::Gate& gate1 = c.AddConnectedGate("leaf0", 4);

    rpc::Node* a01 = c.GetNode(c.GetRootGate(), gate1);
    c.WaitForConnections();
    nstl::vector<StrongMT<test::RSimpleRabbit> > objects;
    for (int i=0;i<4;++i)
    {
      StrongMT<test::RSimpleRabbit> obj = a01->Create<test::RSimpleRabbit>(short(i));
      objects.push_back(obj);
    }
    c.Poll();
  }

  void test_DereplicateWhenNotReplicated()
  {
    StrongMT<test::MockCorruptedPacketProcessor> processor0 = new test::MockCorruptedPacketProcessor;
    StrongMT<test::MockCorruptedPacketProcessor> processor1 = new test::MockCorruptedPacketProcessor;
    StrongMT<test::MockCorruptedPacketProcessor> processor2 = new test::MockCorruptedPacketProcessor;

    OneToManyCase c("root", processor0);

    rpc::Gate& gate1 = c.AddConnectedGate("leaf0", processor1);
    rpc::Gate& gate2 = c.AddConnectedGate("leaf1", processor2);

    rpc::Node* a01 = c.GetNode(c.GetRootGate(), gate1);
    rpc::Node* a02 = c.GetNode(c.GetRootGate(), gate2);

    rpc::Node* a10 = c.GetNode(gate1, c.GetRootGate());
    rpc::Node* a20 = c.GetNode(gate2, c.GetRootGate());
    c.WaitForConnections();

    StrongMT<test::RSimpleRabbit> client_object01(a01->Create<test::RSimpleRabbit>(short(555)));
    test::SimpleRabbit* server_object01 = waitForEntity<test::SimpleRabbit>(a10, 0, c);

    c.GetRootGate().Dereplicate(*client_object01, *a02);
    c.Poll();
    TS_ASSERT_EQUALS((rpc::IPacketPipe*)0, processor2->corruptedPipe);
  }

  void test_SendingDestructToBlockedPipes()
  {
    OneToManyCase c("root");
    rpc::Gate& gate1 = c.AddConnectedGate("leaf0");
    rpc::Node* a01 = c.GetNode(c.GetRootGate(), gate1);
    rpc::Node* a10 = c.GetNode(gate1, c.GetRootGate() );
    c.WaitForConnections();

    {
      StrongMT<test::RSimpleRabbit> client_object01(a01->Create<test::RSimpleRabbit>());
      test::SimpleRabbit* server_object01 = waitForEntity<test::SimpleRabbit>(a10, 0, c);

      c.GetRootGate().Block(*client_object01, *a01);
    }
    test::SimpleRabbit::simpleRabbitsCount = 555;
    c.Poll();
    TS_WAIT_FOR(test::SimpleRabbit::simpleRabbitsCount == 554, 100);
  }

  void test_StressedReplicate()
  {
    OneToManyCase c("root");
    rpc::Gate& g0 = c.GetRootGate();
    rpc::Gate& g1 = c.AddConnectedGate("leaf0");
    c.WaitForConnections();

    StrongMT<test::RSimpleRabbit> client_object01(c.GetNode(g0, g1)->Create<test::RSimpleRabbit>(short(555)));
    c.Poll();

    const int count = 1;
    const int blockCount = 2;

    char buffer[16];
    for (int i=0;i<count;++i)
    {
      NStr::Printf(buffer, 16, "leaf%d", i+1);
      rpc::Gate& gate = c.AddConnectedGate(buffer);
      c.WaitForConnections();
      g0.Replicate(*client_object01, *c.GetNode(g0, gate));
    }
    c.Poll();

    NHPTimer::STime startTime, curTime;
    NHPTimer::GetTime( startTime );
    for (int i=count;i>=1;--i)
    {
      rpc::Node* node = c.GetNode(g0, c.GetGate(i));
      for (int j=0;j<blockCount;++j)
      {
        g0.Block(*client_object01, *node);
      }
      for (int j=0;j<blockCount;++j)
      {
        g0.Unblock(*client_object01, *node);
      }
    }
    NHPTimer::GetTime( curTime );
    NHPTimer::STime diff = curTime - startTime;
    double time = NHPTimer::Time2Seconds( diff);
    //printf_s( "Total time: %.3f seconds, %.3f ms per call \n", time, time * 1000.0 / count );
  }
  
  struct MyReturnValueHandler :  public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_1(MyReturnValueHandler, BaseObjectMT);
    MyReturnValueHandler()
    {
      r = new rpc::SPtrValue<test::RRemoteApi>;
    }
    void OnCall(test::RSimpleRabbit* _result) 
    {  
      _result->GetLocalRemoteApi(r.Get(), &rpc::SPtrValue<test::RRemoteApi>::OnCall);
    }

    StrongMT<rpc::SPtrValue<test::RRemoteApi> > r;
  };

  void test_ForgetEntityWithCall()
  {
    OneToManyCase c("root");
    rpc::Gate& root = c.GetRootGate();
    rpc::Gate& leaf0 = c.AddConnectedGate("leaf0");
    rpc::Node* a01 = c.GetNode(root, leaf0);

    StrongMT<test::SimpleRabbit> lobject = new test::SimpleRabbit;
    leaf0.RegisterObject(lobject, "rpc://rabbit");
    StrongMT<MyReturnValueHandler> q = new MyReturnValueHandler;

    a01->Query<test::RSimpleRabbit>("rpc://rabbit", q.Get(), &MyReturnValueHandler::OnCall);
    while (!q->r->IsSet())
      c.Poll();

    for (int i=0;i<10;++i)
    {
      c.Poll();
    }
  }

  void test_QueiredReplicate()
  {
    OneToManyCase c("root");
    rpc::Gate& root = c.GetRootGate();
    rpc::Gate& leaf0 = c.AddConnectedGate("leaf0");
    rpc::Gate& leaf1 = c.AddConnectedGate("leaf1");
    rpc::Node* a01 = c.GetNode(root, leaf0);
    rpc::Node* a02 = c.GetNode(root, leaf1);
    rpc::Node* a10 = c.GetNode(leaf0, root);
    rpc::Node* a20 = c.GetNode(leaf1, root);
    c.WaitForConnections();

    StrongMT<test::ComplexRabbit> lobject = new test::ComplexRabbit;
    leaf0.RegisterObject(lobject, "rpc://rabbit");

    StrongMT<QueryTest> q = new QueryTest;
    a01->Query<test::RComplexRabbit>("rpc://rabbit", q.Get(), &QueryTest::OnCall);
    while (!q->IsSet())
      c.Poll();

    root.Replicate(*q->result, *a02);

    test::ComplexRabbit* lobject01 = waitForEntity<test::ComplexRabbit>(a10, 0, c);
    test::ComplexRabbit* lobject02 = waitForEntity<test::ComplexRabbit>(a20, 0, c);
    q->result->process();
    TS_WAIT_FOR(lobject01->is_processed == true, 100);
    TS_WAIT_FOR(lobject02->is_processed == true, 100);
    TS_ASSERT_EQUALS(lobject01->is_processed, true);
    TS_ASSERT_EQUALS(lobject02->is_processed, true);

    root.Dereplicate(*q->result, *a02);
    c.Poll();
    TS_WAIT_FOR(test::ComplexRabbit::is_object_deleted == 1, 100);
    TS_ASSERT_EQUALS(test::ComplexRabbit::is_object_deleted, 1);

    root.Dereplicate(*q->result, *a01);
    TS_ASSERT_EQUALS(false, root.IsReplicated(*q->result, *a01));
    c.Poll();
    //TODO: uncomment this
    //TS_WAIT_FOR(test::ComplexRabbit::is_object_deleted == 0, 100);
    //TS_ASSERT_EQUALS(test::ComplexRabbit::is_object_deleted, 1);
  }

  void test_RegisterUnregisterRefCounting()
  {
    OneToManyCase c("root");
    rpc::Gate& root = c.GetRootGate();
    rpc::Gate& leaf0 = c.AddConnectedGate("leaf0");
    c.WaitForConnections();

    StrongMT<test::ComplexRabbit> lobject = new test::ComplexRabbit;
    WeakMT<test::ComplexRabbit> wlobject( lobject );
    leaf0.RegisterObject(lobject, "rpc://rabbit");
    leaf0.UnregisterObject(lobject);
    lobject = 0;
    TS_ASSERT_EQUALS(false, (bool)wlobject.Lock());
  }

  void test_BlockUnblock()
  {
    OneToManyCase c("root");
    rpc::Gate& root = c.GetRootGate();
    rpc::Gate& leaf0 = c.AddConnectedGate("leaf0");
    rpc::Gate& leaf1 = c.AddConnectedGate("leaf1");
    rpc::Node* a01 = c.GetNode(root, leaf0);
    rpc::Node* a02 = c.GetNode(root, leaf1);
    rpc::Node* a10 = c.GetNode(leaf0, root);
    rpc::Node* a20 = c.GetNode(leaf1, root);
    c.WaitForConnections();

    StrongMT<test::RComplexRabbit> client_object01(a01->Create<test::RComplexRabbit>());
    root.Replicate(*client_object01, *a02);
    TS_ASSERT_EQUALS(true, root.IsReplicated(*client_object01, *a02));

    test::ComplexRabbit* server_object01 = waitForEntity<test::ComplexRabbit>(a10, 0, c);
    test::ComplexRabbit* server_object02 = waitForEntity<test::ComplexRabbit>(a20, 0, c);

    root.Block(*client_object01, *a02);
    TS_ASSERT_EQUALS(true, root.IsReplicated(*client_object01, *a02));

    client_object01->process();
    TS_WAIT_FOR(server_object01->is_processed == true, 100);
    TS_WAIT_FOR(server_object02->is_processed == false, 100);
    TS_ASSERT_EQUALS(server_object01->is_processed, true);
    TS_ASSERT_EQUALS(server_object02->is_processed, false);
    TS_ASSERT_EQUALS(test::ComplexRabbit::is_object_deleted, 2);

    server_object01->is_processed = false;
    root.Unblock(*client_object01, *a02);
    TS_ASSERT_EQUALS(true, root.IsReplicated(*client_object01, *a02));
    client_object01->process();
    TS_WAIT_FOR(server_object01->is_processed == true, 100);
    TS_WAIT_FOR(server_object02->is_processed == true, 100);
    TS_ASSERT_EQUALS(server_object01->is_processed, true);
    TS_ASSERT_EQUALS(server_object02->is_processed, true);
  }

  void test_ExclusiveCallWhenEntityIsBlocked()
  {
    OneToManyCase c("root");

    rpc::Gate& gate1 = c.AddConnectedGate("leaf0");
    rpc::Node* a01 = c.GetNode(c.GetRootGate(), gate1);
    rpc::Node* a10 = c.GetNode(gate1, c.GetRootGate());
    c.WaitForConnections();

    StrongMT<test::RComplexRabbit> object(a01->Create<test::RComplexRabbit>());
    test::ComplexRabbit* server_object01 = waitForEntity<test::ComplexRabbit>(a10, 0, c);
    c.GetRootGate().Block(*object, *a01);
    c.GetRootGate().SetExclusive(*object, *a01);
    object->process();
    c.Poll();
    TS_ASSERT_EQUALS(server_object01->is_processed, false);
  }

  void test_ExclusiveCall()
  {
    OneToManyCase c("root");
    rpc::Gate& root = c.GetRootGate();
    rpc::Gate& leaf0 = c.AddConnectedGate("leaf0");
    rpc::Gate& leaf1 = c.AddConnectedGate("leaf1");
    rpc::Node* a01 = c.GetNode(root, leaf0);
    rpc::Node* a02 = c.GetNode(root, leaf1);
    rpc::Node* a10 = c.GetNode(leaf0, root);
    rpc::Node* a20 = c.GetNode(leaf1, root);
    c.WaitForConnections();

    StrongMT<test::RComplexRabbit> client_object01(a01->Create<test::RComplexRabbit>());
    root.Replicate(*client_object01, *a02);

    test::ComplexRabbit* server_object01 = waitForEntity<test::ComplexRabbit>(a10, 0, c);
    test::ComplexRabbit* server_object02 = waitForEntity<test::ComplexRabbit>(a20, 0, c);

    root.SetExclusive(*client_object01, *a02);
    client_object01->process();
    TS_WAIT_FOR(server_object01->is_processed == false, 100);
    TS_WAIT_FOR(server_object02->is_processed == true, 100);
    TS_ASSERT_EQUALS(server_object01->is_processed, false);
    TS_ASSERT_EQUALS(server_object02->is_processed, true);

    server_object02->is_processed = false;
    root.ClearExclusive(*client_object01);
    client_object01->process();
    TS_WAIT_FOR(server_object01->is_processed == true, 100);
    TS_WAIT_FOR(server_object02->is_processed == true, 100);
    TS_ASSERT_EQUALS(server_object01->is_processed, true);
    TS_ASSERT_EQUALS(server_object02->is_processed, true);
  }

  void test_DereplicateAll()
  {
    test::SimpleRabbit::simpleRabbitsCount = 0; // reset test object
    OneToManyCase c("root");

    rpc::Gate& root = c.GetRootGate();
    rpc::Gate& leaf0 = c.AddConnectedGate("leaf0");
    rpc::Gate& leaf1 = c.AddConnectedGate("leaf1");
    c.WaitForConnections();

    rpc::Node* a01 = c.GetNode(root, leaf0);
    rpc::Node* a10 = c.GetNode(leaf0, root);
    rpc::Node* a02 = c.GetNode(c.GetRootGate(), leaf1 );
    rpc::Node* a20 = c.GetNode(leaf1, root );

    StrongMT<test::RSimpleRabbit> cobj0(a01->Create<test::RSimpleRabbit>(short(555)));
    StrongMT<test::RSimpleRabbit> cobj1(a01->Create<test::RSimpleRabbit>(short(555)));
    root.Replicate(*cobj0, *a02);
    root.Replicate(*cobj1, *a02);

    test::SimpleRabbit* sobj0 = waitForEntity<test::SimpleRabbit>(a20, 0, c);
    test::SimpleRabbit* sobj1 = waitForEntity<test::SimpleRabbit>(a20, 1, c);
    TS_ASSERT_EQUALS(true, root.IsReplicated(*cobj0, *a02));
    TS_ASSERT_EQUALS(true, root.IsReplicated(*cobj1, *a02));

    TS_ASSERT_EQUALS(4, test::SimpleRabbit::simpleRabbitsCount);

    root.DereplicateAll(*a02);
    TS_ASSERT_EQUALS(false, root.IsReplicated(*cobj0, *a02));
    TS_ASSERT_EQUALS(false, root.IsReplicated(*cobj1, *a02));

    TS_WAIT_FOR(test::SimpleRabbit::simpleRabbitsCount == 2, 100);
  }

  void test_DereplicateAllStressed()
  {
    test::SimpleRabbit::simpleRabbitsCount = 0; // reset test object
    OneToManyCase c("root");

    rpc::Gate& root = c.GetRootGate();
    rpc::Gate& leaf0 = c.AddConnectedGate("leaf0");
    rpc::Gate& leaf1 = c.AddConnectedGate("leaf1");
    c.WaitForConnections();

    rpc::Node* a01 = c.GetNode(root, leaf0);
    rpc::Node* a02 = c.GetNode(c.GetRootGate(), leaf1 );

    nstl::vector<StrongMT<test::RSimpleRabbit> > objects;
    for (int i=0;i<100;++i)
    {
      StrongMT<test::RSimpleRabbit> cobj0 = a01->Create<test::RSimpleRabbit>(short(555));
      objects.push_back(cobj0);
    }
    for (int i=0;i<objects.size();++i)
    {
      root.Replicate(*objects[i].Get(), *a02);
    }
    root.DereplicateAll(*a02);
  }

  void test_MemoryManagement()
  {
    TwoNodesCase c;
    StrongMT<test::RemoteApi> localApi = new test::RemoteApi;
    WeakMT<test::RemoteApi> localApiWeak( localApi );
    TS_ASSERT_EQUALS(true, (bool)localApiWeak.Lock());

    StrongMT<test::RSimpleRabbit> clientObject(c.cnode0->Create<test::RSimpleRabbit>()); 
    test::SimpleRabbit* serverObject = waitForEntity<test::SimpleRabbit>(c.cnode1, 0, c); 

    clientObject->processRemoteApi(RemotePtr<test::RRemoteApi>(localApi), false);
    TS_WAIT_FOR(serverObject->rapi != 0, 100);

    localApi = 0;
    TS_ASSERT_EQUALS(true, (bool)localApiWeak.Lock());

    serverObject->rapi = 0;
    TS_WAIT_FOR(localApiWeak.Lock()==0, 100);
  }

  void test_UpdateCallbackWhenNotConnected()
  {
    ManyToManyCase c;
    StrongMT<test::MockCorruptedPacketProcessor> rootP = new test::MockCorruptedPacketProcessor("root", &c);
    StrongMT<test::MockCorruptedPacketProcessor> leaf0P = new test::MockCorruptedPacketProcessor("leaf0", &c);
    StrongMT<test::MockCorruptedPacketProcessor> leaf1P = new test::MockCorruptedPacketProcessor("leaf1", &c);

    rpc::Gate& root = c.AddGate("root", rootP);
    rpc::Gate& leaf0 = c.AddGate("leaf0", leaf0P);
    rpc::Gate& leaf1 = c.AddGate("leaf1", leaf1P);
    c.ConnectGates(root, leaf0);
    c.ConnectGates(root, leaf1);
    c.WaitForConnections();

    rpc::Node* a01 = c.GetNode(root, leaf0);
    rpc::Node* a02 = c.GetNode(root, leaf1);
    rpc::Node* a10 = c.GetNode(leaf0, root);
    rpc::Node* a20 = c.GetNode(leaf1, root);

    StrongMT<test::RSimpleReplicated> replica(a01->Create<test::RSimpleReplicated>());
    StrongMT<test::RSimpleRabbit> clientObject(a02->Create<test::RSimpleRabbit>()); 
    test::SimpleRabbit* serverObject = waitForEntity<test::SimpleRabbit>(a20, 1, c); 

    clientObject->SetSimpleReplicated(replica);
    TS_WAIT_FOR(serverObject->replica != 0, 100);

    test::UpdateCallback callback;
    TS_ASSERT_EQUALS(true, serverObject->replica->Update(&callback));
    TS_WAIT_FOR(callback.isUpdated, 100);
  }

  void test_PublishAfterCommit()
  {
    ManyToManyCase c;
    StrongMT<test::MockCorruptedPacketProcessor> rootP = new test::MockCorruptedPacketProcessor("root", &c);
    StrongMT<test::MockCorruptedPacketProcessor> leaf0P = new test::MockCorruptedPacketProcessor("leaf0", &c);
    StrongMT<test::MockCorruptedPacketProcessor> leaf1P = new test::MockCorruptedPacketProcessor("leaf1", &c);

    rpc::Gate& root = c.AddGate("root", rootP);
    rpc::Gate& leaf0 = c.AddGate("leaf0", leaf0P);
    rpc::Gate& leaf1 = c.AddGate("leaf1", leaf1P);
    c.ConnectGates(root, leaf0);
    c.ConnectGates(root, leaf1);
    c.WaitForConnections();

    rpc::Node* a01 = c.GetNode(root, leaf0);
    rpc::Node* a02 = c.GetNode(root, leaf1);
    rpc::Node* a10 = c.GetNode(leaf0, root);
    rpc::Node* a20 = c.GetNode(leaf1, root);

    StrongMT<test::RSimpleReplicated> replica(a01->Create<test::RSimpleReplicated>());
    test::SimpleReplicated* replicaObject = waitForEntity<test::SimpleReplicated>(a10, 0, c); 

    StrongMT<test::RSimpleRabbit> clientObject(a02->Create<test::RSimpleRabbit>()); 
    test::SimpleRabbit* serverObject = waitForEntity<test::SimpleRabbit>(a20, 1, c); 

    clientObject->SetSimpleReplicated(replica);
    TS_WAIT_FOR(serverObject->replica != 0, 100);

    // что происходит с запросом на publish если есть неприконнекченные ноды ?  
    //  + отсылаются данные на приконнеченные ноды
    //  + запрос на publish на конкретную ноду кладется в очередь WeakMT<ILocalEntity> GateId EntityId
    //  + проверяется на каждом Poll список неотосланных ILocalEntity по EntityMap
    //  что происходит с запросом на publish если эти сущности не торопятся коннектится ?
    //  + посылается запрос на connect на клиента (в лучшем случае напрямую, в худшем через p2p)
    //  + добавляем ConnectRequest в протокол

    replica->seti( 444 );
    replica->Commit(true);
    TS_WAIT_FOR(replicaObject->i == 444, 100);
    TS_WAIT_FOR(serverObject->replica->geti() == 444, 100);
  }
};

class Test_Query : public CxxTest::TestSuite, RPCMixin   
{
public:
  void test_Query()
  {
    TwoNodesCase c;

    StrongMT<test::ComplexRabbit> server_object = new test::ComplexRabbit;
    c.GetGate("node0")->RegisterObject(server_object, "rpc://rabbit");

    StrongMT<QueryTest> q = new QueryTest;
    c.cnode1->Query<test::RComplexRabbit>("rpc://rabbit", q.Get(), &QueryTest::OnCall);
    while (!q->result)
      c.Poll();

    q->result->process();
    c.Poll();
    TS_WAIT_FOR(server_object->is_processed == true, 100);
    TS_ASSERT_EQUALS(true, server_object->is_processed);
  }

  void test_QueryTimeout()
  {
    TwoNodesCase c;

    StrongMT<test::ComplexRabbit> server_object = new test::ComplexRabbit;
    c.GetGate("node0")->RegisterObject(server_object, "rpc://rabbit");

    StrongMT<QueryTest> q = new QueryTest;
    c.cnode1->Query<test::RComplexRabbit>("rpc://rabbit", q.Get(), &QueryTest::OnCallDetailed, 555, 0.1f);
    c.Block();
    TS_WAIT_FOR(555 == q->context, 1000000);
    TS_ASSERT_EQUALS(rpc::CallTimedOut, q->status);
    TS_ASSERT_EQUALS((test::RComplexRabbit*)0, q->result);
  }

  void test_QueryDisconnect()
  {
    TwoNodesCase c;

    StrongMT<test::ComplexRabbit> server_object = new test::ComplexRabbit;
    c.GetGate("node0")->RegisterObject(server_object, "rpc://rabbit");

    StrongMT<QueryTest> q = new QueryTest;
    c.cnode1->Query<test::RComplexRabbit>("rpc://rabbit", q.Get(), &QueryTest::OnCallDetailed, 555, 0.1f);
    c.Disconnect(false, true);
    TS_WAIT_FOR(rpc::PipeDisconnected == q->status, 100);
    TS_ASSERT_EQUALS(555, q->context);
    TS_ASSERT_EQUALS((test::RComplexRabbit*)0, q->result); 
  }

  void test_Unregister()
  {
    TwoNodesCase c;

    StrongMT<test::ComplexRabbit> serverObject = new test::ComplexRabbit;
    c.GetGate("node0")->RegisterObject(serverObject, "rpc://rabbit");

    StrongMT<QueryTest> q = new QueryTest;
    c.cnode1->Query<test::RComplexRabbit>("rpc://rabbit", q.Get(), &QueryTest::OnCall);
    while (!q->result)
      c.Poll();

    TS_ASSERT_EQUALS(true, c.GetGate("node0")->UnregisterObject(serverObject));
    {
      test::AssertDisabler d;
      StrongMT<rpc::SPtrValue<test::RComplexRabbit> > q1 = new rpc::SPtrValue<test::RComplexRabbit>;
      c.cnode1->Query<test::RComplexRabbit>("rpc://rabbit", q1.Get(), &rpc::SPtrValue<test::RComplexRabbit>::OnCall);
      while (!q1->IsSet())
        c.Poll();
      TS_ASSERT_EQUALS((test::RComplexRabbit*)0, q1->result);
    }

    q->result->process();
    c.Poll();
    TS_WAIT_FOR(serverObject->is_processed == true, 100);
    TS_ASSERT_EQUALS(true, serverObject->is_processed);
  }

  void test_QueryByClassId()
  {
    TwoNodesCase c;

    StrongMT<test::ComplexRabbit> server_object = new test::ComplexRabbit;
    c.GetGate("node0")->RegisterObject(rpc::GetId<test::ComplexRabbit>(), server_object.Get(), "rpc://rabbit");

    StrongMT<QueryTest> q = new QueryTest;
    c.cnode1->Query(test::RComplexRabbit::ID(), test::RComplexRabbit::CRC32, "rpc://rabbit", q.Get(), &QueryTest::OnCall);
    while (!q->result)
      c.Poll();

    q->result->process();
    c.Poll();
    TS_WAIT_FOR(server_object->is_processed == true, 100);
    TS_ASSERT_EQUALS(true, server_object->is_processed);
  }
  
  void test_BadCrc32ClassQuery()
  {
    StrongMT<test::MockCorruptedPacketProcessor> p0 = new test::MockCorruptedPacketProcessor;
    StrongMT<test::MockCorruptedPacketProcessor> p1 = new test::MockCorruptedPacketProcessor;
    TwoNodesCase c(p0, p1);

    StrongMT<test::BadCrc32Class> server_object = new test::BadCrc32Class ;
    c.GetGate("node0")->RegisterObject(server_object, "rpc://rabbit");

    StrongMT<rpc::SPtrValue<test::RBadCrc32Class> > q = new rpc::SPtrValue<test::RBadCrc32Class>;
    c.cnode1->Query<test::RBadCrc32Class>("rpc://rabbit", q.Get(), &rpc::SPtrValue<test::RBadCrc32Class>::OnCall );

    rpc::IPacketPipe* expectedCorruptedPipe = c.cnode0->GetPipe();

    TS_WAIT_FOR(p0->corruptedPipe, 100);
    TS_ASSERT_EQUALS(expectedCorruptedPipe, p0->corruptedPipe);
  }

  void test_MissedQuery()
  {
    TwoNodesCase c;

    StrongMT<test::ComplexRabbit> server_object = new test::ComplexRabbit;
    c.GetGate("node0")->RegisterObject(server_object, "rpc://rabbit");

    StrongMT<QueryTest> q = new QueryTest;
    c.cnode1->Query<test::RComplexRabbit>("rpc://missedRabbit", q.Get(), &QueryTest::OnCall);
    {
      test::AssertDisabler d;

      while (!q->IsSet())
        c.Poll();
    }
    TS_ASSERT_EQUALS(q->result, (test::RComplexRabbit*)0);
  }

  void test_ProtectedQuery()
  {
    StrongMT<test::MockCorruptedPacketProcessor> p0 = new test::MockCorruptedPacketProcessor;
    StrongMT<test::MockCorruptedPacketProcessor> p1 = new test::MockCorruptedPacketProcessor;
    TwoNodesCase c(p0, p1);

    StrongMT<test::ComplexRabbit> server_object = new test::ComplexRabbit;
    c.GetGate("node0")->RegisterObject(server_object, "rpc://rabbit", "password");

    StrongMT<QueryTest> q = new QueryTest;
    c.cnode1->Query<test::RComplexRabbit>("rpc://rabbit", q.Get(), &QueryTest::OnCall, "password");
    while (!q->IsSet())
      c.Poll();

    q->result->process();
    c.Poll();
    TS_WAIT_FOR(server_object->is_processed == true, 100);
    TS_ASSERT_EQUALS(true, server_object->is_processed);

    q->Reset();
    c.cnode1->Query<test::RComplexRabbit>("rpc://rabbit", q.Get(), &QueryTest::OnCall, "bad_password");
    rpc::IPacketPipe* expectedCorruptedPipe = c.cnode0->GetPipe();
    TS_WAIT_FOR(p0->corruptedPipe, 100);
    TS_ASSERT_EQUALS(expectedCorruptedPipe, p0->corruptedPipe);
    TS_ASSERT_EQUALS((test::RComplexRabbit*)0, q->result);
  }

  void test_BadCrc32OfClass()
  {
    StrongMT<test::MockCorruptedPacketProcessor> p0 = new test::MockCorruptedPacketProcessor;
    StrongMT<test::MockCorruptedPacketProcessor> p1 = new test::MockCorruptedPacketProcessor;
    TwoNodesCase c(p0, p1);

    StrongMT<test::RBadCrc32Class> client_object(c.cnode1->Create<test::RBadCrc32Class>()); 
    //TS_ASSERT_EQUALS(true, client_object->IsValid());

    rpc::IPacketPipe* expectedCorruptedPipe = c.cnode0->GetPipe();
    {
      test::AssertDisabler d;
      c.Poll();
    }
    
    TS_ASSERT_EQUALS(expectedCorruptedPipe, p0->corruptedPipe);
    //TS_ASSERT_EQUALS(false, client_object->IsValid());

    client_object->process();
    c.Poll();
    //TS_ASSERT_EQUALS(false, client_object->IsValid());
  }


  void test_DisconnectionWithEmptyProcessor()
  {
    TwoNodesCase c;

    StrongMT<test::ComplexRabbit> server_object = new test::ComplexRabbit;
    c.GetGate("node0")->RegisterObject(server_object, "rpc://rabbit", "password");

    StrongMT<QueryTest> q = new QueryTest;
    c.cnode1->Query<test::RComplexRabbit>("rpc://rabbit", q.Get(), &QueryTest::OnCall, "bad_password");
    c.Poll();

    c.Disconnect(true, true);
  }

  void test_MissedFactory()
  {
    StrongMT<test::MockCorruptedPacketProcessor> p0 = new test::MockCorruptedPacketProcessor;
    StrongMT<test::MockCorruptedPacketProcessor> p1 = new test::MockCorruptedPacketProcessor;
    TwoNodesCase c(p0, p1);

    rpc::UnregisterFactory(test::RComplexRabbit::ID());

    StrongMT<test::RComplexRabbit> client_object(c.cnode1->Create<test::RComplexRabbit>()); 
    //TS_ASSERT_EQUALS(true, client_object->IsValid());

    rpc::IPacketPipe* expectedCorruptedPipe = c.cnode0->GetPipe();

    client_object->process();
    {
      test::AssertDisabler d;
      c.Poll();
    }
    rpc::RegisterFactory(test::RComplexRabbit::ID(), factory_ComplexRabbit); // register for future use
    TS_ASSERT_EQUALS(expectedCorruptedPipe, p0->corruptedPipe);
    //TS_ASSERT_EQUALS(false, client_object->IsValid());
  }

  void test_GateLocalFactory()
  {
    struct ComplexRabbitFactoryWithParam : rpc::ILocalEntityFactory
    {
      int param;
      rpc::ILocalEntity* Create(const rpc::LocalEntityCreationInfo& entityInfo, rpc::Arguments& args, rpc::IEntityMap* entityMap)
      {
        test::ComplexRabbit* rabbit = new test::ComplexRabbit();
        rabbit->processInt( param );
         return new test::LComplexRabbit(rabbit, entityMap, this);
      }
    };

    ComplexRabbitFactoryWithParam factory0,factory1;
    factory0.param = 11;
    factory1.param = 22;

    TwoNodesCase c;

    c.GetGate("node0")->RegisterFactory<test::ComplexRabbit>( factory0 );
    c.GetGate("node1")->RegisterFactory<test::ComplexRabbit>( factory1 );

    StrongMT<test::RComplexRabbit> p0(c.cnode0->Create<test::RComplexRabbit>());
    test::ComplexRabbit* server_object0 = waitForEntity<test::ComplexRabbit>(c.cnode1, 0, c);

    StrongMT<test::RComplexRabbit> p1(c.cnode1->Create<test::RComplexRabbit>());
    test::ComplexRabbit* server_object1 = waitForEntity<test::ComplexRabbit>(c.cnode0, 0, c);

    TS_ASSERT_EQUALS( server_object0->int_param0, 22 );
    TS_ASSERT_EQUALS( server_object1->int_param0, 11 );
  }

   void test_ClassIdInFactory()
   {
     struct MyMultiFactory : rpc::ILocalEntityFactory
     {
       int objectsProcessed;
       MyMultiFactory() : objectsProcessed(0) {}
       rpc::ILocalEntity* Create(const rpc::LocalEntityCreationInfo& entityInfo, rpc::Arguments& args, rpc::IEntityMap* entityMap)
       {
         ++objectsProcessed;
         if ( entityInfo.classId == rpc::GetId<test::ComplexRabbit>())
         {
           return new test::LComplexRabbit(new test::ComplexRabbit(), entityMap, this);
         }
         else if ( entityInfo.classId == rpc::GetId<test::SimpleRabbit>() )
         {
           return new test::LSimpleRabbit( new test::SimpleRabbit(), entityMap, this);
         }
         return 0;
       }
     };

     MyMultiFactory factory;
     TwoNodesCase c;

     c.GetGate("node1")->RegisterFactory<test::ComplexRabbit>( factory );
     c.GetGate("node1")->RegisterFactory<test::SimpleRabbit>( factory );

     StrongMT<test::RComplexRabbit> p0(c.cnode0->Create<test::RComplexRabbit>());
     StrongMT<test::RSimpleRabbit> p1(c.cnode0->Create<test::RSimpleRabbit>());
     test::ComplexRabbit* server_object0 = waitForEntity<test::ComplexRabbit>(c.cnode1, 0, c);
     test::SimpleRabbit* server_object1 = waitForEntity<test::SimpleRabbit>(c.cnode1, 1, c);

     TS_ASSERT( server_object0 );
     TS_ASSERT( server_object1 );
     TS_ASSERT_EQUALS( factory.objectsProcessed, 2 );
   }

   void test_DestructionInFactory()
   {
     struct MyRabbitFactory : rpc::ILocalEntityFactory
     {
       bool rabbitDestroyed;
       float destroyedObjectFloat;


       MyRabbitFactory() : rabbitDestroyed(false), destroyedObjectFloat(0) {}
       rpc::ILocalEntity* Create(const rpc::LocalEntityCreationInfo& entityInfo, rpc::Arguments& args, rpc::IEntityMap* entityMap)
       {
         test::ComplexRabbit* rabbit = new test::ComplexRabbit();
         return new test::LComplexRabbit(rabbit, entityMap, this);
       }

       void Destroy( rpc::ILocalEntity* entity ) 
       {
         test::ComplexRabbit* rabbit = entity->Get<test::ComplexRabbit>();
         if ( rabbit )
         {
           rabbitDestroyed = true;
           destroyedObjectFloat = rabbit->float_param0;
         }
       }
     };

     MyRabbitFactory factory;
     TwoNodesCase c;

     c.GetGate("node1")->RegisterFactory<test::ComplexRabbit>( factory );

     StrongMT<test::RComplexRabbit> p0 = c.cnode0->Create<test::RComplexRabbit>();
     test::ComplexRabbit* server_object0 = waitForEntity<test::ComplexRabbit>(c.cnode1, 0, c);

     TS_ASSERT( server_object0 );

     p0->processFloat( 22.f );
     p0 = 0;
     TS_WAIT_FOR( factory.rabbitDestroyed, 100 );
     TS_ASSERT_EQUALS( factory.destroyedObjectFloat, 22.f  );
   }

   void test_OriginNodeInFactory()
   {
     struct MyFactory : rpc::ILocalEntityFactory
     {
       rpc::Node* originNode;
       MyFactory() : originNode(0) {}
       rpc::ILocalEntity* Create(const rpc::LocalEntityCreationInfo& entityInfo, rpc::Arguments& args, rpc::IEntityMap* entityMap)
       {
         originNode = entityInfo.originNode;
         return new test::LComplexRabbit(new test::ComplexRabbit(), entityMap, this);
       }
     };

     MyFactory factory;
     TwoNodesCase c;

     c.GetGate("node1")->RegisterFactory<test::ComplexRabbit>( factory );

     StrongMT<test::RComplexRabbit> p0 = c.cnode0->Create<test::RComplexRabbit>();
     test::ComplexRabbit* server_object0 = waitForEntity<test::ComplexRabbit>(c.cnode1, 0, c);
     TS_ASSERT_EQUALS( factory.originNode, c.cnode1 );
   }
};

class Test_FieldsReplication : public CxxTest::TestSuite, RPCMixin
{
public:
  void test_VectorOfSerializableStructs()
  {
    Case<test::SimpleReplicated, test::RSimpleReplicated> c;
    TS_WAIT_FOR( c.ro->IsUpdated(), 100 );

    TS_ASSERT_EQUALS(0, c.lo->snapshots.size());
    test::InitialSnapshot s;
    s.serverTime = 555;
    c.ro->get_snapshots().push_back(s);
    TS_ASSERT_EQUALS(1, c.ro->get_snapshots().size());

    c.ro->Commit();
    while (c.lo->snapshots.size() != 1) c.Poll();
    TS_ASSERT_EQUALS(555, c.lo->snapshots[0].serverTime);

    c.ro->get_snapshots().eraseByIndex(0);
    TS_ASSERT_EQUALS(0, c.ro->get_snapshots().size());
    c.ro->Rollback();
    TS_ASSERT_EQUALS(1, c.ro->get_snapshots().size());
    TS_ASSERT_EQUALS(555, c.ro->get_snapshots()[0].serverTime);
  }

  void test_VectorOfSerializableStructsInitialFetch()
  {
    Case<test::SimpleReplicated, test::RSimpleReplicated> c(127);
    TS_ASSERT_EQUALS(1, c.lo->snapshots.size());

    TS_WAIT_FOR( c.ro->IsUpdated(), 100 );

    TS_ASSERT_EQUALS(1, c.ro->get_snapshots().size());
    TS_ASSERT_EQUALS(999, c.ro->get_snapshots()[0].serverTime);
  }

  void test_SimpleVectorOfInts()
  {
    Case<test::SimpleReplicated, test::RSimpleReplicated> c;
    TS_WAIT_FOR( c.ro->IsUpdated(), 100 );

    TS_ASSERT_EQUALS(0, c.lo->vi.size());
    c.ro->get_vi().append(125);
    c.ro->Commit();
    while (c.lo->vi.size() != 1) c.Poll();
    c.ro->set_vi( 0, 256 );
    c.ro->Commit();
    while (c.lo->vi[0] == 125) c.Poll();
    c.ro->get_vi().append(1);
    c.ro->get_vi().append(2);
    c.ro->Commit();
    while (c.lo->vi.size() != 3) c.Poll();
    TS_ASSERT_EQUALS(1, c.lo->vi[1]);
    TS_ASSERT_EQUALS(2, c.lo->vi[2]);

    c.ro->set_vi( 2, 128 );
    c.ro->Commit();
    while (c.lo->vi[2] == 2) c.Poll();

    c.ro->get_vi().eraseByIndex(1);
    c.ro->Commit();
    while (c.lo->vi.size() != 2) c.Poll();
    TS_ASSERT_EQUALS(256, c.lo->vi[0]);
    TS_ASSERT_EQUALS(128, c.lo->vi[1]);
  }

  void test_SimplePtrAlreadyCreatedOnServer()  
  {
    OneToManyCase c("root");
    rpc::Gate& gate0 = c.AddConnectedGate("leaf0");

    rpc::Node* a01 = c.GetNode(c.GetRootGate(), gate0);
    rpc::Node* a10 = c.GetNode(gate0, c.GetRootGate());

    {
      StrongMT<test::RSimpleReplicated> obj0 = a01->Create<test::RSimpleReplicated>(777);
      test::SimpleReplicated* lobj0 = waitForEntity<test::SimpleReplicated>(a10, 0, c);
      TS_WAIT_FOR( obj0->IsUpdated(), 100 );
      TS_ASSERT(obj0->get_ptr().Get() != 0);
    }
  }
  
  void test_UpdatingOnCreate()
  {
    Case<test::SimpleReplicated, test::RSimpleReplicated> c(127);
    TS_ASSERT_EQUALS(false, c.ro->IsUpdated());
    TS_WAIT_FOR( c.ro->IsUpdated(), 100 );

    TS_ASSERT_EQUALS(888, c.ro->geti());
    TS_ASSERT_EQUALS(12, c.ro->getd());
    TS_ASSERT_EQUALS(443, c.ro->gets());
    TS_ASSERT_EQUALS(1.8f, c.ro->getf());
    TS_ASSERT_EQUALS(34, c.ro->get_b());
    TS_ASSERT_EQUALS(true, c.ro->get_BoolVar());

    TS_ASSERT_EQUALS(2, c.ro->get_vi().size());
    TS_ASSERT_EQUALS(76, c.ro->get_vi()[0]);
    TS_ASSERT_EQUALS(78, c.ro->get_vi()[1]);

    TS_ASSERT_EQUALS(2, c.ro->get_vd().size());
    TS_ASSERT_EQUALS(16, c.ro->get_vd()[0]);
    TS_ASSERT_EQUALS(18, c.ro->get_vd()[1]);
    assertEquals("Original", c.ro->get_name().c_str());
  }

  void test_DeletionRObjectWhileUpdateContentOnTheWay()
  {
    OneToManyCase c("root");
    rpc::Gate& gate0 = c.AddConnectedGate("leaf0");
    rpc::Node* a01 = c.GetNode(c.GetRootGate(), gate0);
    rpc::Node* a10 = c.GetNode(gate0, c.GetRootGate());
    {
      StrongMT<test::RSimpleReplicated> obj = a01->Create<test::RSimpleReplicated>();
      test::SimpleReplicated* sobj01 = waitForEntity<test::SimpleReplicated>(a10, 0, c);
    }
    StrongMT<test::RSimpleRabbit> obj = a01->Create<test::RSimpleRabbit>();
    c.Poll();
    TS_ASSERT_EQUALS(false, obj->IsUpdated());
  }

  void test_SimpleInt()
  {
    Case<test::SimpleReplicated, test::RSimpleReplicated> c;
    TS_WAIT_FOR( c.ro->IsUpdated(), 100 );

    c.ro->seti( 255 );
    TS_ASSERT_EQUALS( 255, c.ro->geti() );

    c.ro->Commit();
    TS_WAIT_FOR(c.lo->i == 255, 100);

    c.ro->seti( c.ro->geti() + 2 );
    c.ro->Commit();
    TS_WAIT_FOR(c.lo->i == 257, 100);
  }

  void test_Struct()
  {
    Case<test::SimpleReplicated, test::RSimpleReplicated> c;
    TS_WAIT_FOR( c.ro->IsUpdated(), 100 );

    TS_ASSERT_EQUALS( 0.f, c.ro->getquat().x);
    TS_ASSERT_EQUALS( 0.f, c.ro->getquat().y);
    TS_ASSERT_EQUALS( 0.f, c.ro->getquat().z);
    TS_ASSERT_EQUALS( 0.f, c.ro->getquat().w);

    c.ro->setquat( CQuat(float(PI), 1.f, 0.f, 0.f) );
    TS_ASSERT_EQUALS( 1.f, c.ro->getquat().x );
    c.ro->Commit();
    TS_WAIT_FOR(c.lo->quat.x == 1.f, 100);
  }

  void test_DoubleSet()
  {
    Case<test::SimpleReplicated, test::RSimpleReplicated> c;
    TS_WAIT_FOR( c.ro->IsUpdated(), 100 );

    c.ro->seti( 255 );
    c.ro->setd( 256 );
    TS_ASSERT_EQUALS( 255, c.ro->geti() );
    TS_ASSERT_EQUALS( 256, c.ro->getd() );

    c.ro->Commit();
    TS_WAIT_FOR( (c.lo->i == 255 && c.lo->d == 256), 100 );
    TS_ASSERT_EQUALS( 255, c.lo->i );
    TS_ASSERT_EQUALS( 256, c.lo->d );
  }

  void test_CancelTransactionOnDestructor()
  {
    Case<test::SimpleReplicated, test::RSimpleReplicated> c;
    c.ro->get_vi().push_back(1000);
  }

  void test_RollbackVectorOrder()
  {
    Case<test::SimpleReplicated, test::RSimpleReplicated> c;
    TS_WAIT_FOR( c.ro->IsUpdated(), 100 );
      
    c.ro->get_vi().push_back(1000);
    c.ro->get_vi().push_back(2000);
    c.ro->Commit();
    c.Poll();

    c.ro->set_vi( 1, 300 );
    c.ro->get_vi().eraseByIndex(0);

    TS_ASSERT_EQUALS(1, c.ro->get_vi().size());
    TS_ASSERT_EQUALS(300, c.ro->get_vi()[0]);

    c.ro->Rollback();
    TS_ASSERT_EQUALS(2, c.ro->get_vi().size());
    TS_ASSERT_EQUALS(1000, c.ro->get_vi()[0]);
    TS_ASSERT_EQUALS(2000, c.ro->get_vi()[1]);
  }

  void test_RollbackVector()
  {
    Case<test::SimpleReplicated, test::RSimpleReplicated> c;
    TS_WAIT_FOR( c.ro->IsUpdated(), 100 );

    c.ro->get_vi().push_back(255);
    c.ro->Commit();
    c.Poll();
    TS_ASSERT_EQUALS(1, c.lo->vi.size());
    TS_ASSERT_EQUALS(255, c.lo->vi[0]);

    c.ro->set_vi( 0, 2 );
    c.ro->get_vi().push_back(100);

    TS_ASSERT_EQUALS(2, c.ro->get_vi().size());
    TS_ASSERT_EQUALS(2, c.ro->get_vi()[0]);
    TS_ASSERT_EQUALS(100, c.ro->get_vi()[1]);

    c.ro->Rollback();
    TS_ASSERT_EQUALS(1, c.ro->get_vi().size());
    TS_ASSERT_EQUALS(255, c.ro->get_vi()[0]);

    c.Poll();
    TS_ASSERT_EQUALS(1, c.lo->vi.size());
    TS_ASSERT_EQUALS(255, c.lo->vi[0]);

    c.ro->get_vi().push_back(256);
    c.ro->get_vi().push_back(257);
    c.ro->Commit();
    c.Poll();
    TS_ASSERT_EQUALS(3, c.lo->vi.size());
    TS_ASSERT_EQUALS(255, c.lo->vi[0]);     
    TS_ASSERT_EQUALS(256, c.lo->vi[1]);
    TS_ASSERT_EQUALS(257, c.lo->vi[2]);

    c.ro->get_vi().eraseByIndex(0);
    TS_ASSERT_EQUALS(2, c.ro->get_vi().size());
    TS_ASSERT_EQUALS(256, c.ro->get_vi()[0]);     
    TS_ASSERT_EQUALS(257, c.ro->get_vi()[1]);     
    c.ro->get_vi().eraseByIndex(1);
    TS_ASSERT_EQUALS(1, c.ro->get_vi().size());
    TS_ASSERT_EQUALS(256, c.ro->get_vi()[0]);     
    c.ro->Rollback();

    c.Poll();
    TS_ASSERT_EQUALS(3, c.lo->vi.size());
    TS_ASSERT_EQUALS(255, c.lo->vi[0]);     
    TS_ASSERT_EQUALS(256, c.lo->vi[1]);
    TS_ASSERT_EQUALS(257, c.lo->vi[2]);
  }

  void test_Rollback()
  {
    Case<test::SimpleReplicated, test::RSimpleReplicated> c;
    TS_WAIT_FOR( c.ro->IsUpdated(), 100 );

    c.ro->seti( 255 );
    c.ro->setd( 1024 );
    c.ro->sets( 32000 );
    c.ro->set_name( "Yo" );
    c.ro->get_vi().push_back(255);
    c.ro->Commit();
    TS_WAIT_FOR( (c.lo->i == 255), 100 );
    TS_ASSERT_EQUALS(255, c.lo->i);
    TS_ASSERT_EQUALS(1024, c.lo->d);
    TS_ASSERT_EQUALS(32000, c.lo->s);
    assertEquals("Yo", c.lo->name.c_str());
    TS_ASSERT_EQUALS(1, c.lo->vi.size());
    TS_ASSERT_EQUALS(255, c.lo->vi[0]);

    c.ro->seti( 256 );
    c.ro->setd( 1025 );
    c.ro->sets( 32001 );
    c.ro->set_name( "Yo Yo" );
    c.ro->set_vi( 0, 2 );
    c.ro->get_vi().push_back(100);

    TS_ASSERT_EQUALS(256, c.ro->geti());
    TS_ASSERT_EQUALS(1025, c.ro->getd());
    TS_ASSERT_EQUALS(32001, c.ro->gets());
    assertEquals("Yo Yo", c.ro->get_name().c_str());
    TS_ASSERT_EQUALS(2, c.ro->get_vi().size());
    TS_ASSERT_EQUALS(2, c.ro->get_vi()[0]);
    TS_ASSERT_EQUALS(100, c.ro->get_vi()[1]);

    c.ro->Rollback();
    TS_ASSERT_EQUALS( 255, c.ro->geti() );
    TS_ASSERT_EQUALS(1024, c.ro->getd() );
    TS_ASSERT_EQUALS(32000, c.ro->gets() );
    assertEquals("Yo", c.ro->get_name().c_str());
    TS_ASSERT_EQUALS(1, c.ro->get_vi().size());
    TS_ASSERT_EQUALS(255, c.ro->get_vi()[0]);

    c.Poll();
    TS_ASSERT_EQUALS(255, c.lo->i);
    TS_ASSERT_EQUALS(1024, c.lo->d);
    TS_ASSERT_EQUALS(32000, c.lo->s);
    assertEquals("Yo", c.lo->name.c_str());
    TS_ASSERT_EQUALS(1, c.lo->vi.size());
    TS_ASSERT_EQUALS(255, c.lo->vi[0]);
  }

  void test_Replicate()
  {
    OneToManyCase c("root");

    rpc::Gate& gate1 = c.AddConnectedGate("leaf0");
    rpc::Gate& gate2 = c.AddConnectedGate("leaf1");

    rpc::Node* a01 = c.GetNode(c.GetRootGate(), gate1);
    rpc::Node* a02 = c.GetNode(c.GetRootGate(), gate2);
    rpc::Node* a10 = c.GetNode(gate1, c.GetRootGate());
    rpc::Node* a20 = c.GetNode(gate2, c.GetRootGate());
    StrongMT<test::RSimpleReplicated> obj = a01->Create<test::RSimpleReplicated>();
    TS_WAIT_FOR( obj->IsUpdated(), 100 );

    obj->seti( 555 );
    obj->setd( 124 );
    obj->sets( 21 );
    obj->setf( 12.f );
    obj->set_b( 252 );
    obj->set_BoolVar( false );
    obj->set_name( "Nival Network" );
    obj->get_vi().push_back(100);
    obj->get_vi().push_back(101);
    obj->get_vd().push_back(1);
    obj->get_vd().push_back(2);
    obj->get_vd().push_back(3);
    obj->Commit();
    c.Poll();

    test::SimpleReplicated* sobj01 = waitForEntity<test::SimpleReplicated>(a10, 0, c);
    TS_ASSERT_EQUALS(555, sobj01->i);

    c.GetRootGate().Replicate(*obj, *a02);
    c.Poll();
    test::SimpleReplicated* sobj02 = waitForEntity<test::SimpleReplicated>(a20, 0, c);
    TS_ASSERT_EQUALS(555, sobj02->i);
    TS_ASSERT_EQUALS(124, sobj02->d);
    TS_ASSERT_EQUALS(21, sobj02->s);
    TS_ASSERT_EQUALS(12.f, sobj02->f);
    TS_ASSERT_EQUALS(252, sobj02->b);
    TS_ASSERT_EQUALS(false, sobj02->BoolVar);
    assertEquals("Nival Network", sobj02->name.c_str());
    TS_ASSERT_EQUALS(2, sobj02->vi.size());
    TS_ASSERT_EQUALS(100, sobj02->vi[0]);
    TS_ASSERT_EQUALS(101, sobj02->vi[1]);

    TS_ASSERT_EQUALS(3, sobj02->vd.size());
    TS_ASSERT_EQUALS(1, sobj02->vd[0]);
    TS_ASSERT_EQUALS(2, sobj02->vd[1]);
    TS_ASSERT_EQUALS(3, sobj02->vd[2]);
  }

  void test_ReplicateRemotePtr()  
  {
    OneToManyCase c("root");
    rpc::Gate& gate0 = c.AddConnectedGate("leaf0");
    rpc::Node* a01 = c.GetNode(c.GetRootGate(), gate0);
    rpc::Node* a10 = c.GetNode(gate0, c.GetRootGate());
    {
      StrongMT<test::RSimpleReplicated> obj0 = a01->Create<test::RSimpleReplicated>();
      test::SimpleReplicated* lobj0 = waitForEntity<test::SimpleReplicated>(a10, 0, c);
      StrongMT<test::RSimpleReplicated> obj1 = a01->Create<test::RSimpleReplicated>();
      test::SimpleReplicated* lobj1 = waitForEntity<test::SimpleReplicated>(a10, 1, c);

      obj0->set_ptr( obj1 );
      TS_ASSERT_EQUALS(obj1, obj0->get_ptr());
      obj0->Commit();
      TS_WAIT_FOR(lobj0->ptr == lobj1, 100);

      obj0->set_ptr( 0 );
      TS_ASSERT_EQUALS((test::RSimpleReplicated *)0, obj0->get_ptr().Get());
      obj0->Commit();
      TS_WAIT_FOR(lobj0->ptr == 0, 100);

      obj0->set_ptr( obj1 );
      TS_ASSERT_EQUALS(obj1, obj0->get_ptr());
      obj0->Commit();
      TS_WAIT_FOR(lobj0->ptr == lobj1, 100);

      StrongMT<test::RSimpleReplicated> obj2 = a01->Create<test::RSimpleReplicated>();
      test::SimpleReplicated* lobj2 = waitForEntity<test::SimpleReplicated>(a10, 1, c);
      obj0->set_ptr( obj2 );
      TS_ASSERT_EQUALS(obj2, obj0->get_ptr());
      obj0->Commit();
      TS_WAIT_FOR(lobj0->ptr == lobj2, 100);
    }
  }

  void test_DoubleInterfacesInheritancesOnOneLocalEntity()
  {

  }

  void test_PtrUpdateCallback()  
  {
    OneToManyCase c("root");
    rpc::Gate& gate0 = c.AddConnectedGate("leaf0");
    rpc::Node* a01 = c.GetNode(c.GetRootGate(), gate0);
    rpc::Node* a10 = c.GetNode(gate0, c.GetRootGate());
    {
      StrongMT<test::RSimpleReplicated> obj0 = a01->Create<test::RSimpleReplicated>();
      test::SimpleReplicated* lobj0 = waitForEntity<test::SimpleReplicated>(a10, 0, c);
      StrongMT<test::RSimpleReplicated> obj1 = a01->Create<test::RSimpleReplicated>();
      test::SimpleReplicated* lobj1 = waitForEntity<test::SimpleReplicated>(a10, 1, c);

      obj0->set_ptr( obj1 );
      TS_ASSERT_EQUALS(obj1, obj0->get_ptr());
      obj0->Commit();
      TS_WAIT_FOR(lobj0->ptr == lobj1, 100);

      test::UpdateCallback cb;
      obj0->SetUpdateCallback(&cb);
      TS_ASSERT_EQUALS(&cb, obj1->GetUpdateCallback());

      obj1->Update();
      TS_WAIT_FOR(cb.isUpdated == true, 100);
    }
  }

  void test_RemotePtrRollback()  
  {
    OneToManyCase c("root");
    rpc::Gate& gate0 = c.AddConnectedGate("leaf0");
    rpc::Node* a01 = c.GetNode(c.GetRootGate(), gate0);
    rpc::Node* a10 = c.GetNode(gate0, c.GetRootGate());
    StrongMT<test::RSimpleReplicated> obj0 = a01->Create<test::RSimpleReplicated>();
    test::SimpleReplicated* lobj0 = waitForEntity<test::SimpleReplicated>(a10, 0, c);
    StrongMT<test::RSimpleReplicated> obj1 = a01->Create<test::RSimpleReplicated>();
    test::SimpleReplicated* lobj1 = waitForEntity<test::SimpleReplicated>(a10, 1, c);

    obj0->set_ptr( obj1 );
    TS_ASSERT_EQUALS(obj1, obj0->get_ptr());
    obj0->Commit();
    TS_WAIT_FOR(lobj0->ptr == lobj1, 100);

    obj0->set_ptr( 0 );
    TS_ASSERT_EQUALS((test::RSimpleReplicated *)0, obj0->get_ptr().Get());
    obj0->Rollback();
    TS_ASSERT_EQUALS(obj1, obj0->get_ptr());
    c.Poll();
    TS_WAIT_FOR(lobj0->ptr == lobj1, 100);
  }

  void test_RemotePtrRollbackAndMemoryLeak() 
  {
    OneToManyCase c("root");
    rpc::Gate& gate0 = c.AddConnectedGate("leaf0");
    rpc::Node* a01 = c.GetNode(c.GetRootGate(), gate0);
    rpc::Node* a10 = c.GetNode(gate0, c.GetRootGate());
    StrongMT<test::RSimpleReplicated> obj0 = a01->Create<test::RSimpleReplicated>();
    test::SimpleReplicated* lobj0 = waitForEntity<test::SimpleReplicated>(a10, 0, c);
    StrongMT<test::RSimpleReplicated> obj1 = a01->Create<test::RSimpleReplicated>();
    test::SimpleReplicated* lobj1 = waitForEntity<test::SimpleReplicated>(a10, 1, c);
    StrongMT<test::RSimpleReplicated> obj2 = a01->Create<test::RSimpleReplicated>();
    test::SimpleReplicated* lobj2 = waitForEntity<test::SimpleReplicated>(a10, 1, c);

    obj0->set_ptr( obj1 );
    obj0->Commit();

    obj0->set_ptr( obj2 ); // no rollback here, so referenced value should cause mem leak
  }


  void test_SimpleDouble()
  {
    Case<test::SimpleReplicated, test::RSimpleReplicated> c; 
    TS_WAIT_FOR( c.ro->IsUpdated(), 100 );

    c.ro->setd( 256 );
    c.ro->Commit();
    while (c.lo->d != 256) c.Poll();
  }

  void test_SimpleShort()
  {
    Case<test::SimpleReplicated, test::RSimpleReplicated> c;
    TS_WAIT_FOR( c.ro->IsUpdated(), 100 );

    c.ro->sets( 256 );
    c.ro->Commit();
    while (c.lo->s != 256) c.Poll();
  }

  void test_SimpleFloat()
  {
    Case<test::SimpleReplicated, test::RSimpleReplicated> c;
    TS_WAIT_FOR( c.ro->IsUpdated(), 100 );

    c.ro->setf( 1.f );
    c.ro->Commit();
    while (c.lo->f != 1.f) c.Poll();
  }

  void test_SimpleBool()
  {
    Case<test::SimpleReplicated, test::RSimpleReplicated> c;
    TS_WAIT_FOR( c.ro->IsUpdated(), 100 );

    c.ro->set_BoolVar( true );
    c.ro->Commit();
    while (c.lo->BoolVar != true) c.Poll();
  }

  void test_SimpleByte()
  {
    Case<test::SimpleReplicated, test::RSimpleReplicated> c;
    TS_WAIT_FOR( c.ro->IsUpdated(), 100 );

    c.ro->set_b( 125 );
    c.ro->Commit();
    while (c.lo->b != 125) c.Poll();
  }


  void test_SimpleVectorOfDoubles()
  {
    Case<test::SimpleReplicated, test::RSimpleReplicated> c;
    TS_WAIT_FOR( c.ro->IsUpdated(), 100 );

    TS_ASSERT_EQUALS(0, c.lo->vd.size());
    c.ro->get_vd().append(1);
    c.ro->Commit();
    while (c.lo->vd.size() != 1) c.Poll();

    c.ro->set_vd( 0, 2 );
    c.ro->Commit();
    while (c.lo->vd[0] == 1) c.Poll();
  }

  void test_SimpleString()
  {
    Case<test::SimpleReplicated, test::RSimpleReplicated> c;
    TS_WAIT_FOR( c.ro->IsUpdated(), 100 );

    assertEquals("", c.lo->name.c_str());
    c.ro->set_name( "Hello !" );
    c.ro->Commit();
    while (c.lo->name.length() == 0) c.Poll();
    assertEquals("Hello !", c.lo->name.c_str());

    c.ro->set_name( 1, 'E' );
    c.ro->Commit();
    while (c.lo->name[1] == 'e') c.Poll();
    assertEquals("HEllo !", c.lo->name.c_str());
  }

  void test_SimpleWString()
  {
    Case<test::SimpleReplicated, test::RSimpleReplicated> c;
    TS_WAIT_FOR( c.ro->IsUpdated(), 100 );

    assertEquals(L"", c.lo->wname.c_str());
    c.ro->set_wname( L"Hello !" );
    c.ro->Commit();
    while (c.lo->wname.length() == 0) c.Poll();
    assertEquals(L"Hello !", c.lo->wname.c_str());

    c.ro->set_wname( 1, L'E' );
    c.ro->Commit();
    while (c.lo->wname[1] == L'e') c.Poll();
    assertEquals(L"HEllo !", c.lo->wname.c_str());
  }

  struct ChangeHandler
  {
    nstl::Bool<false> is_catched;
    void OnCall()
    {
      is_catched = true;
    }
  };

  void test_ChangeCallback()
  {
    Case<test::SimpleReplicated, test::RSimpleReplicated> c;
    TS_WAIT_FOR( c.ro->IsUpdated(), 100 );

    ChangeHandler handler;
    c.cnode1->SetHandler(c.lo->name, &handler, &ChangeHandler::OnCall);

    c.ro->set_name( "eXtreme" );
    c.ro->Commit();
    while (handler.is_catched == false) c.Poll();

    c.cnode1->RemoveHandler(c.lo->name);
    handler.is_catched = false;
    c.ro->set_name( "Hello!" );
    c.ro->Commit();
    threading::Event e(false, false);
    e.Wait(50);
    TS_ASSERT_EQUALS(false, handler.is_catched);
  }

  void test_Update()
  {
    Case<test::SimpleReplicated, test::RSimpleReplicated> c;
    TS_WAIT_FOR( c.ro->IsUpdated(), 100 );

    c.lo->i = 128;
    c.lo->name = "Nival";
    TS_ASSERT_EQUALS(true, c.ro->IsUpdated());
    c.ro->Update();
    TS_ASSERT_EQUALS(false, c.ro->IsUpdated());
    TS_WAIT_FOR( c.ro->IsUpdated(), 100 );

    TS_ASSERT_EQUALS(128, c.ro->geti());
    assertEquals("Nival", c.ro->get_name().c_str());
  }

  void test_UpdateCallback()
  {
    Case<test::SimpleReplicated, test::RSimpleReplicated> c;
    TS_WAIT_FOR( c.ro->IsUpdated(), 100 );

    c.lo->i = 128;
    c.lo->name = "Nival";

    test::UpdateCallback callback;
    TS_ASSERT_EQUALS(true, c.ro->IsUpdated());
    c.ro->Update(&callback);
    TS_ASSERT_EQUALS(false, c.ro->IsUpdated());
    TS_WAIT_FOR( callback.isUpdated == true, 100 );

    TS_ASSERT_EQUALS(c.ro, callback.entity);
    TS_ASSERT_EQUALS(128, c.ro->geti());
    TS_ASSERT_EQUALS(128, c.ro->geti());
    assertEquals("Nival", c.ro->get_name().c_str());

    callback.isUpdated = false;
    callback.entity = 0;
    c.ro->Update();
    TS_WAIT_FOR( callback.isUpdated == true, 100 );
  }

};

class Test_IDGenerator : public CxxTest::TestSuite
{
public:

  void test_Simple()
  {
    IDGenerator g;
    uint id0 = g.Generate();
    uint id1 = g.Generate();
    TS_ASSERT_DIFFERS(id0, id1);

    g.Release(id1);
    uint id2 = g.Generate();
    TS_ASSERT_EQUALS(id1, id2); // Generate always return lowest id 
  }

  void test_FreeLowestId()
  {
    IDGenerator g;
    uint id0 = g.Generate();
    uint id1 = g.Generate();

    g.Release(id0);
    uint id2 = g.Generate();
    TS_ASSERT_EQUALS(id0, id2); // Generate always return lowest id 

    uint id3 = g.Generate();
    TS_ASSERT_LESS_THAN(id1, id3); // Generate always return lowest id 

    g.Release(id2);
    g.Release(id1);
    g.Release(id3);

    uint id4 = g.Generate();
    TS_ASSERT_EQUALS(id0, id4); // Generate always return lowest id 
  }

  void test_JoinHoles()
  {
    IDGenerator g;
    uint id0 = g.Generate();
    uint id1 = g.Generate();
    uint id2 = g.Generate();
    uint id3 = g.Generate();
    uint id4 = g.Generate();
    uint id5 = g.Generate();

    g.Release(id1);
    g.Release(id3);
    g.Release(id2);

    g.Release(id0);
    g.Release(id5);
    g.Release(id4);
    uint id6 = g.Generate();
    TS_ASSERT_EQUALS(id0, id6); // Generate always return lowest id 
  }

  void test_InexistedValue()
  {
    IDGenerator g;
    uint id0 = g.Generate();
    TS_ASSERT_EQUALS(false, g.Release(10000));

    uint id1 = g.Generate();
    uint id2 = g.Generate();
    TS_ASSERT_EQUALS(true, g.Release(id1));
    TS_ASSERT_EQUALS(false, g.Release(id1));
  }
};

class Test_CompileTimeSubClass : public CxxTest::TestSuite
{
public:
  struct Parent {};
  struct Child : Parent {};
  _interface ISharedParent {};
  struct ComplexChild : ISharedParent, Parent {};
  struct MegaComplexChild : ISharedParent, BaseObjectMT {};
  void test_Simple()
  {
    TS_ASSERT_EQUALS(true, bool(SUPERSUBCLASS(Parent, Child)));
    TS_ASSERT_EQUALS(false, bool(SUPERSUBCLASS(Child, Parent)));
    TS_ASSERT_EQUALS(true, bool(SUPERSUBCLASS(ISharedParent, ComplexChild)));
    TS_ASSERT_EQUALS(true, bool(SUPERSUBCLASS(Parent, ComplexChild)));
    TS_ASSERT_EQUALS(false, bool(SUPERSUBCLASS(Child, ComplexChild)));
    TS_ASSERT_EQUALS(false, bool(SUPERSUBCLASS(Parent, ISharedParent)));
    TS_ASSERT_EQUALS(true, bool(SUPERSUBCLASS(ISharedParent, MegaComplexChild)));
    TS_ASSERT_EQUALS(true, bool(SUPERSUBCLASS(BaseObjectMT, MegaComplexChild)));
  }
};

// посылаем нотификацию: указатель на объект X ушел на ноду Y
//   на O: нельзя удалять объект, делаем на него предварительную ссылку
//   на O: если удаляется объект совсем, то всем живым нодам с которыми была связана сущность рассылается что данный индекс свободен
//   на O: на приходе запроса на подключение, подключаем объект, удаляем предварительную ссылку
// что происходит если Y так и не подключилась ?
//     через некий timeout вырубаем все предварительные ссылки связанные с Y
// что происходит если нотификация об удалении ноды не дошла ?
//     все удаления L объектов происходят через некоторый timeout, и если приходит запрос на объект, но мы его достаем из кэша
//     если приходит объект с ноды и такой индекс в кэше, то удаляем объект из кэша
// что происходит если объект создан, но запрос на link приходит раньше чем запрос на создание ?
// что с потокобезопасностью ?
// освобождение ids

struct DummyLocalEntity : public rpc::ILocalEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(DummyLocalEntity, rpc::ILocalEntity, BaseObjectMT);
public:
  virtual void Publish()
  {
  }
  virtual bool vset(byte memberId, rpc::ArgReader& s) { return true; }
  virtual int GetMemberIndex(const void*) { return 0; }
  virtual void* _Get(uint classId) { return 0; }
  virtual uint GetClassCrc() const { return 0; }
  virtual void Update(rpc::ArgWriter* args) {}
  virtual rpc::CallResult::Enum Call(const rpc::MethodCallHeader& call, rpc::MethodCall& resultCall, rpc::Arguments& args, const byte* paramsData, int _paramsSize) { return rpc::CallResult::OK; }
};

NI_DEFINE_REFCOUNT(DummyLocalEntity);

namespace test
{

template<class T>
inline bool IsValid( WeakMT<T> & p ) { StrongMT<T> s = p.Lock(); return s.Valid(); }

}

class Test_PtrSharing : public CxxTest::TestSuite, RPCMixin   
{
public:

  void test_Simple()
  {
    GUID entityGUID;
    UuidCreate(&entityGUID);

    StrongMT<DummyLocalEntity> entity = new DummyLocalEntity;
    WeakMT<DummyLocalEntity> wentity( entity );
    GUID gateA;
    UuidCreate(&gateA);
    rpc::NodeDescription d;
    rpc::PtrSharing s(d);
    TS_ASSERT_EQUALS(true, test::IsValid(wentity));
    s.RegisterObject(entity, gateA, 0, entityGUID);
    entity = 0;
    TS_ASSERT_EQUALS(true, test::IsValid(wentity));

    s.UnregisterObject(gateA, 0, entityGUID);
    TS_ASSERT_EQUALS(false, test::IsValid(wentity));
  }

  void test_Two()
  {
    GUID entityGUID0;
    UuidCreate(&entityGUID0);
    GUID entityGUID1;
    UuidCreate(&entityGUID1);

    StrongMT<DummyLocalEntity> entity0 = new DummyLocalEntity;
    StrongMT<DummyLocalEntity> entity1 = new DummyLocalEntity;
    WeakMT<DummyLocalEntity> wentity0( entity0 );
    WeakMT<DummyLocalEntity> wentity1( entity1 );
    GUID gateA;
    UuidCreate(&gateA);

    GUID gateB;
    UuidCreate(&gateB);

    rpc::NodeDescription d;
    rpc::PtrSharing s(d);
    s.RegisterObject(entity0, gateA, 0, entityGUID0);
    s.RegisterObject(entity1, gateB, 55, entityGUID1);
    entity0 = 0;
    entity1 = 0;
    TS_ASSERT_EQUALS(true, test::IsValid(wentity0));
    TS_ASSERT_EQUALS(true, test::IsValid(wentity1));

    s.UnregisterObject(gateA, 0, entityGUID0);
    s.UnregisterObject(gateB, 55, entityGUID1);
    TS_ASSERT_EQUALS(false, test::IsValid(wentity0));
    TS_ASSERT_EQUALS(false, test::IsValid(wentity1));
  }

  void test_Transfer()
  {
    GUID entityGUID;
    UuidCreate(&entityGUID);

    StrongMT<DummyLocalEntity> entity = new DummyLocalEntity;
    WeakMT<DummyLocalEntity> wentity( entity );
    GUID gateA;
    UuidCreate(&gateA);
    GUID gateB;
    UuidCreate(&gateB);

    rpc::NodeDescription d;
    rpc::PtrSharing s(d);
    TS_ASSERT_EQUALS(true, test::IsValid(wentity));
    s.RegisterObject(entity, gateA, 0, entityGUID);
    entity = 0;
    TS_ASSERT_EQUALS(true, test::IsValid(wentity));

    s.ShareObject(gateB, entityGUID, false);

    s.UnregisterObject(gateA, 0, entityGUID);
    TS_ASSERT_EQUALS(true, test::IsValid(wentity));

    rpc::ILocalEntity* newE = s.LinkToObject(gateB, 55, entityGUID);
    TS_ASSERT_EQUALS(newE, wentity.Lock().Get());
    TS_ASSERT_EQUALS(true, test::IsValid(wentity));

    s.UnregisterObject(gateB, 55, entityGUID);
    TS_ASSERT_EQUALS(false, test::IsValid(wentity));
  }

  void test_GateRemoving()
  {
    GUID entityGUID;
    UuidCreate(&entityGUID);

    StrongMT<DummyLocalEntity> entity = new DummyLocalEntity;
    WeakMT<DummyLocalEntity> wentity( entity );
    GUID gateA;
    UuidCreate(&gateA);
    GUID gateB;
    UuidCreate(&gateB);

    rpc::NodeDescription d;
    rpc::PtrSharing s(d);
    TS_ASSERT_EQUALS(true, test::IsValid(wentity));
    s.RegisterObject(entity, gateA, 0, entityGUID);
    entity = 0;
    TS_ASSERT_EQUALS(true, test::IsValid(wentity));

    s.ShareObject(gateB, entityGUID, false);

    s.RemoveGate(gateA);
    TS_ASSERT_EQUALS(true, test::IsValid(wentity));
    s.RemoveGate(gateB);
    TS_ASSERT_EQUALS(false, test::IsValid(wentity));
  }

  void test_GateRemovingWhileDoubleLink()
  {
  }

  void test_DoubleSharing()
  {
    GUID entityGUID;
    UuidCreate(&entityGUID);

    StrongMT<DummyLocalEntity> entity = new DummyLocalEntity;
    WeakMT<DummyLocalEntity> wentity( entity );
    GUID gateA;
    UuidCreate(&gateA);
    GUID gateB;
    UuidCreate(&gateB);

    rpc::NodeDescription d;
    rpc::PtrSharing s(d);
    s.RegisterObject(entity, gateA, 0, entityGUID);
    entity = 0;

    s.ShareObject(gateB, entityGUID, false);
    s.ShareObject(gateB, entityGUID, false);

    rpc::ILocalEntity* newE = s.LinkToObject(gateB, 55, entityGUID);
    TS_ASSERT_EQUALS(newE, wentity.Lock().Get());
    TS_ASSERT_EQUALS(true, test::IsValid(wentity));

    s.UnregisterObject(gateA, 0, entityGUID);
    s.UnregisterObject(gateB, 55, entityGUID);
    TS_ASSERT_EQUALS(true, test::IsValid(wentity));
  }

  void test_GetEntityId()
  {
    GUID entityGUID;
    UuidCreate(&entityGUID);

    StrongMT<DummyLocalEntity> entity = new DummyLocalEntity;
    WeakMT<DummyLocalEntity> wentity( entity );
    GUID gateA;
    UuidCreate(&gateA);
    GUID gateB;
    UuidCreate(&gateB);

    rpc::NodeDescription d;
    rpc::PtrSharing s(d);
    s.RegisterObject(entity, gateA, 0, entityGUID);
    TS_ASSERT_EQUALS(0, s.GetEntityId(entityGUID, gateA));

    s.ShareObject(gateB, entityGUID, false);
    TS_ASSERT_EQUALS(INVALID_ENTITY, s.GetEntityId(entityGUID, gateB));

    s.LinkToObject(gateB, 55, entityGUID);
    TS_ASSERT_EQUALS(55, s.GetEntityId(entityGUID, gateB));
  }

  void test_MultipleUnregister()
  {
    GUID entityGUID0;
    UuidCreate(&entityGUID0);
    GUID entityGUID1;
    UuidCreate(&entityGUID1);
    GUID entityGUID2;
    UuidCreate(&entityGUID2);
    StrongMT<DummyLocalEntity> entity0 = new DummyLocalEntity;
    StrongMT<DummyLocalEntity> entity1 = new DummyLocalEntity;
    StrongMT<DummyLocalEntity> entity2 = new DummyLocalEntity;
    WeakMT<DummyLocalEntity> wentity0( entity0 );
    WeakMT<DummyLocalEntity> wentity1( entity1 );
    WeakMT<DummyLocalEntity> wentity2( entity2 );
    GUID gateA;
    UuidCreate(&gateA);
    GUID gateB;
    UuidCreate(&gateB);
    GUID gateC;
    UuidCreate(&gateC);

    rpc::NodeDescription d;
    rpc::PtrSharing s(d);
    s.RegisterObject(entity0, gateA, 0, entityGUID0);
    s.RegisterObject(entity1, gateB, 1, entityGUID1);
    s.RegisterObject(entity2, gateC, 0, entityGUID2);
    entity0 = 0;
    entity1 = 0;
    entity2 = 0;

    s.UnregisterObject(gateA, 0, entityGUID0);
    TS_ASSERT_EQUALS(false, test::IsValid(wentity0));
    TS_ASSERT_EQUALS(true, test::IsValid(wentity1));
    TS_ASSERT_EQUALS(true, test::IsValid(wentity2));

    s.UnregisterObject(gateB, 1, entityGUID1);
    TS_ASSERT_EQUALS(false, test::IsValid(wentity1));
    TS_ASSERT_EQUALS(true, test::IsValid(wentity2));

    s.UnregisterObject(gateC, 0, entityGUID2);
    TS_ASSERT_EQUALS(false, test::IsValid(wentity2));
  }

  void test_DelayedLinking()
  {
    GUID entityGUID;
    UuidCreate(&entityGUID);

    StrongMT<DummyLocalEntity> entity = new DummyLocalEntity;
    WeakMT<DummyLocalEntity> wentity( entity );
    GUID gateA;
    UuidCreate(&gateA);
    GUID gateB;
    UuidCreate(&gateB);
    GUID gateC;
    UuidCreate(&gateC);

    rpc::NodeDescription d;
    rpc::PtrSharing s(d);
    s.RegisterObject(entity, gateA, 0, entityGUID);
    entity = 0;

    TS_ASSERT_EQUALS(true, s.ShareObject(gateC, entityGUID, false));

    TS_ASSERT_EQUALS(true, s.ShareObject(gateB, entityGUID, false));
    {
      rpc::ILocalEntity* newE = s.LinkToObject(gateB, 55, entityGUID);
      TS_ASSERT_EQUALS(newE, wentity.Lock().Get());
      TS_ASSERT_EQUALS(true, test::IsValid(wentity));
    }

    TS_ASSERT_EQUALS(true, s.ShareObject(gateC, entityGUID, false));
    {
      rpc::ILocalEntity* newE = s.LinkToObject(gateC, 66, entityGUID);
      TS_ASSERT_EQUALS(newE, wentity.Lock().Get());
      TS_ASSERT_EQUALS(true, test::IsValid(wentity));
    }
  }

  void test_GetIds()
  {
    GUID entityGUID;
    UuidCreate(&entityGUID);

    StrongMT<DummyLocalEntity> entity = new DummyLocalEntity;
    WeakMT<DummyLocalEntity> wentity( entity );
    GUID gateA;
    UuidCreate(&gateA);
    GUID gateB;
    UuidCreate(&gateB);

    nstl::vector<rpc::EntityGateInfo> guids;
    nstl::vector<rpc::EntityId> entities;

    rpc::NodeDescription d;
    rpc::PtrSharing s(d);
    s.RegisterObject(entity, gateA, 0, entityGUID);
    entity = 0;
    s.ShareObject( gateB, entityGUID, false );
    rpc::ILocalEntity* newE = s.LinkToObject(gateB, 55, entityGUID);

    GUID retrievedEntityGUID;
    s.GetAllGUIDs( wentity.Lock(), guids, retrievedEntityGUID );
    TS_ASSERT_SAME_DATA(&entityGUID, &retrievedEntityGUID, sizeof(GUID));

    TS_ASSERT_EQUALS( guids.size(), 2 );
    TS_ASSERT( (guids[0].gateId == gateB && guids[1].gateId == gateA) || (guids[0].gateId == gateA && guids[1].gateId == gateB) );

    s.UnregisterObject(gateA, 0, entityGUID);
    s.UnregisterObject(gateB, 55, entityGUID);
  }
};

struct Test_MethodCodes : public CxxTest::TestSuite
{
  void test_Simple()
  {
    {
      TS_ASSERT_EQUALS(0, rpc::GetMethodCode(&test::ComplexRabbit::process));
    }
    {
      rpc::ParamTypes signature[] = { rpc::Byte4 };
      TS_ASSERT_EQUALS(GetDirectMethodCode(signature, sizeof(signature)/sizeof(rpc::ParamTypes)), rpc::GetMethodCodeTemp(&test::ComplexRabbit::processInt));
    }
    {
      rpc::ParamTypes signature[] = { rpc::Byte4 };
      TS_ASSERT_EQUALS(GetDirectMethodCode(signature, sizeof(signature)/sizeof(rpc::ParamTypes)), rpc::GetMethodCodeTemp(&test::ComplexRabbit::processFloat));
    }
    {
      rpc::ParamTypes signature[] = { rpc::Byte8 };
      TS_ASSERT_EQUALS(GetDirectMethodCode(signature, sizeof(signature)/sizeof(rpc::ParamTypes)), rpc::GetMethodCodeTemp(&test::ComplexRabbit::processDouble));
    }
    {
      rpc::ParamTypes signature[] = { rpc::Byte4, rpc::Byte4 };
      TS_ASSERT_EQUALS(GetDirectMethodCode(signature, sizeof(signature)/sizeof(rpc::ParamTypes)), rpc::GetMethodCodeTemp(&test::ComplexRabbit::processFloatInt));
    }
    {
      rpc::ParamTypes signature[] = { rpc::String };
      TS_ASSERT_EQUALS(GetDirectMethodCode(signature, sizeof(signature)/sizeof(rpc::ParamTypes)), rpc::GetMethodCodeTemp(&test::ComplexRabbit::processString));
    }
    {
      rpc::ParamTypes signature[] = { rpc::Byte1 };
      TS_ASSERT_EQUALS(GetDirectMethodCode(signature, sizeof(signature)/sizeof(rpc::ParamTypes)), rpc::GetMethodCodeTemp(&test::ComplexRabbit::processBool));
    }
    {
      rpc::ParamTypes signature[] = { rpc::Byte2 };
      TS_ASSERT_EQUALS(GetDirectMethodCode(signature, sizeof(signature)/sizeof(rpc::ParamTypes)), rpc::GetMethodCodeTemp(&test::ComplexRabbit::processShort));
    }
    {
      rpc::ParamTypes signature[] = { rpc::Byte8 };
      TS_ASSERT_EQUALS(GetDirectMethodCode(signature, sizeof(signature)/sizeof(rpc::ParamTypes)), rpc::GetMethodCodeTemp(&test::ComplexRabbit::processLongLong));
    }
    {
      rpc::ParamTypes signature[] = { rpc::Byte8 };
      TS_ASSERT_EQUALS(GetDirectMethodCode(signature, sizeof(signature)/sizeof(rpc::ParamTypes)), rpc::GetMethodCodeTemp(&test::ComplexRabbit::processMyType));
    }
    {
      rpc::ParamTypes signature[] = { rpc::VectorOfScalars };
      TS_ASSERT_EQUALS(GetDirectMethodCode(signature, sizeof(signature)/sizeof(rpc::ParamTypes)), rpc::GetMethodCodeTemp(&test::ComplexRabbit::processVector ));
    }
    {
      rpc::ParamTypes signature[] = { rpc::VectorOfMemoryBlocks };
      TS_ASSERT_EQUALS(GetDirectMethodCode(signature, sizeof(signature)/sizeof(rpc::ParamTypes)), rpc::GetMethodCodeTemp(&test::SimpleRabbit::processMemoryBlockVector));
    }
    {
      rpc::ParamTypes signature[] = { rpc::StlString };
      TS_ASSERT_EQUALS(GetDirectMethodCode(signature, sizeof(signature)/sizeof(rpc::ParamTypes)), rpc::GetMethodCodeTemp(&test::ComplexRabbit::processNSLTString));
    }
    {
      rpc::ParamTypes signature[] = { rpc::FixedVectorOfScalars };
      TS_ASSERT_EQUALS(GetDirectMethodCode(signature, sizeof(signature)/sizeof(rpc::ParamTypes)), rpc::GetMethodCodeTemp(&test::SimpleRabbit::processFixedVector));
    }
    {
      rpc::ParamTypes signature[] = { rpc::MemoryBlockType };
      TS_ASSERT_EQUALS(GetDirectMethodCode(signature, sizeof(signature)/sizeof(rpc::ParamTypes)), rpc::GetMethodCodeTemp(&test::SimpleRabbit::processMemoryBlock));
    }
    {
      rpc::ParamTypes signature[] = { rpc::VectorOfStrings };
      TS_ASSERT_EQUALS(GetDirectMethodCode(signature, sizeof(signature)/sizeof(rpc::ParamTypes)), rpc::GetMethodCodeTemp(&test::SimpleRabbit::processVectorOfStrings));
    }
    {
      rpc::ParamTypes signature[] = { rpc::VectorOfStrings };
      TS_ASSERT_EQUALS(GetDirectMethodCode(signature, sizeof(signature)/sizeof(rpc::ParamTypes)), rpc::GetMethodCodeTemp(&test::SimpleRabbit::processVectorOfWStrings));
    }

    // not implemented
    {
      rpc::ParamTypes signature[] = { rpc::Byte4 };
      //TS_ASSERT_EQUALS(GetDirectMethodCode(signature, sizeof(signature)/sizeof(rpc::ParamTypes)), rpc::GetMethodCodeTemp(&test::ComplexRabbit::processMyEnum));
    }
    {
      rpc::ParamTypes signature[] = { rpc::RemoteEntity };
      //TS_ASSERT_EQUALS(GetDirectMethodCode(signature, sizeof(signature)/sizeof(rpc::ParamTypes)), rpc::GetMethodCodeTemp(&test::SimpleRabbit::processLocalRemoteApi));
    }
    {
      rpc::ParamTypes signature[] = { rpc::Struct };
      //TS_ASSERT_EQUALS(GetDirectMethodCode(signature, sizeof(signature)/sizeof(rpc::ParamTypes)), rpc::GetMethodCodeTemp(&test::SimpleRabbit::processSnapshot));
    }
    {
      rpc::ParamTypes signature[] = { rpc::RawStruct };
      //TS_ASSERT_EQUALS(GetDirectMethodCode(signature, sizeof(signature)/sizeof(rpc::ParamTypes)), rpc::GetMethodCodeTemp(&test::ComplexRabbit::processStruct));
    }
  }
  int GetDirectMethodCode(rpc::ParamTypes* types, int count)
  {
    rpc::MethodCodeCalculator calc;
    for (int i=0;i<count;++i)
    {
      calc.Add(types[i]);
    }
    return calc.GetCode();
  }
};


                              