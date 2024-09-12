#pragma once

#include "Parser.h"
#include "Calls.h"
#include "IEntityMap.h"
#include "Transaction.h"
#include "Types.h"


namespace rpc 
{

class Transaction;
class MultiPacketPipe;

class Args : NonCopyable
{
public:
  Args() {}
  Args( IEntityMap * _entityMap, TLogTrace _logTrace );

  ~Args()
  { 
    StopDataTransaction();
  }

  void SetEntityId( EntityId id )
  {
    entityId = id;
  }

  void ReadOnly( bool val )
  {
    isReadOnly = val;
  }
  bool IsReadOnly() const 
  {
    return isReadOnly;
  }

  template <typename T0> void Set(IRemoteEntity* entity, byte memberId, const T0& new_value, T0& old_value) 
  { 
    if ( IsReadOnly() )
      return;
    StrongMT<rpc::IEntityMap> sentityMap = entityMap.Lock();
    if (!sentityMap)
    {
      return;
    }
    TransactionHandler h = sentityMap->GetActiveDataTransaction();
    if (h)
    {
      h->Register(entity);
    }
    if (old_value != new_value && StartDataTransaction())
    {
      Push(datatransaction, memberId);
      Set(datatransaction, new_value);
      ArgWriter& args = datatransaction->GetRollbackArgs();
      int offset = args.size();
      args.Push(memberId);
      args.Push(false);
      args.Push(old_value);
      datatransaction->AddParam(offset, args.size()-offset);
      old_value = new_value;
    }
  }
  template <typename T0> void Set(IRemoteEntity* entity, byte memberId, T0* newValue, StrongMT<T0>& oldValue) 
  {
    if ( IsReadOnly() )
      return;
    StrongMT<rpc::IEntityMap> sentityMap = entityMap.Lock();
    if (!sentityMap)
    {
      return;
    }
    TransactionHandler h = sentityMap->GetActiveDataTransaction();
    if (h)
    {
      h->Register(entity);
    }
    if (newValue != oldValue && StartDataTransaction())
    {
      if (newValue) newValue->SetParent(entity);
      Push(datatransaction, memberId);
      StrongMT<T0> tmp = newValue;
      datatransaction->GetArgs().Push(tmp); 
      ArgWriter& args = datatransaction->GetRollbackArgs();
      int offset = args.size();
      args.Push(memberId);
      args.Push(false);
      args.PushRaw<bool>(true);
      args.PushRef(oldValue);
      datatransaction->AddParam(offset, args.size()-offset);
      oldValue = newValue;
    }
  }

  void Set(IRemoteEntity* entity, byte memberId, IRemoteEntity* newValue, IRemoteEntity*& oldValue) 
  {
    if ( IsReadOnly() )
      return;
    StrongMT<rpc::IEntityMap> sentityMap = entityMap.Lock();
    if (!sentityMap)
    {
      return;
    }
    TransactionHandler h = sentityMap->GetActiveDataTransaction();
    if (h)
    {
      h->Register(entity);
    }
    if (newValue != oldValue && StartDataTransaction())
    {
      if (newValue) newValue->SetParent(entity);
      Push(datatransaction, memberId);
      StrongMT<IRemoteEntity> tmp = newValue;
      datatransaction->GetArgs().PushRemoteEntity(tmp, true); 
      ArgWriter& args = datatransaction->GetRollbackArgs();
      int offset = args.size();
      args.Push(memberId);
      args.PushRemoteEntity(oldValue, true);
      datatransaction->AddParam(offset, args.size()-offset);
      oldValue = newValue;
    }
  }

  void Set(IRemoteEntity* entity, byte memberId, void* new_value, void* old_value, int size)
  { 
    if ( IsReadOnly() )
      return;
    StrongMT<rpc::IEntityMap> sentityMap = entityMap.Lock();
    if (!sentityMap)
    {
      return;
    }
    TransactionHandler h = sentityMap->GetActiveDataTransaction();
    if (h)
    {
      h->Register(entity);
    }
    if (old_value != new_value && StartDataTransaction())
    {
      Push(datatransaction, memberId);
      Push(datatransaction, new_value, size);
      ArgWriter& args = datatransaction->GetRollbackArgs();
      int offset = args.size();
      args.Push(memberId);
      args.Push(false);
      args.Push(old_value, size);
      datatransaction->AddParam(offset, args.size()-offset);
      //old_value = new_value;
    }
  }

  // set
  template <typename T1> void SetMember(IRemoteEntity* entity, byte memberId, const ContainerOperationInfo& info, const T1& newValue, const T1& oldValue) 
  { 
    if ( IsReadOnly() )
      return;
    StrongMT<rpc::IEntityMap> sentityMap = entityMap.Lock();
    if (!sentityMap)
    {
      return;
    }
    TransactionHandler h = sentityMap->GetActiveDataTransaction();
    if (h)
    {
      h->Register(entity);
    }
    if (StartDataTransaction())
    {
      Push(datatransaction, memberId);
      PushRaw<bool>(datatransaction, true);
      Push(datatransaction, info);
      PushArrayMember(datatransaction, newValue);
      ArgWriter& args = datatransaction->GetRollbackArgs();
      int offset = args.size();
      args.Push(memberId);
      args.Push(true);
      args.PushRaw<bool>(true);
      args.Push(info);
      args.PushRef(oldValue);
      datatransaction->AddParam(offset, args.size()-offset);
    }
  }

  void SetMember(IRemoteEntity* entity, byte memberId, const ContainerOperationInfo& info, void* new_value, void* old_value, unsigned int size) 
  { 
    if ( IsReadOnly() )
      return;
    StrongMT<rpc::IEntityMap> sentityMap = entityMap.Lock();
    if (!sentityMap)
    {
      return;
    }
    TransactionHandler h = sentityMap->GetActiveDataTransaction();
    if (h)
    {
      h->Register(entity);
    }
    if (StartDataTransaction())
    {
      Push(datatransaction, memberId);
      PushRaw<bool>(datatransaction, true);
      Push(datatransaction, info);
      Push(datatransaction, new_value, size);
      ArgWriter& args = datatransaction->GetRollbackArgs();
      int offset = args.size();
      args.Push(memberId);
      args.Push(true);
      args.PushRaw<bool>(true);
      args.Push(info);
      args.Push(old_value, size);
      datatransaction->AddParam(offset, args.size()-offset);
    }
  }

  template <typename T1> void SetMember(IRemoteEntity* entity, byte memberId, const ContainerOperationInfo& info, const StrongMT<T1>& newValue, const StrongMT<T1>& oldValue) 
  { 
    if ( IsReadOnly() )
      return;
    StrongMT<rpc::IEntityMap> sentityMap = entityMap.Lock();
    if (!sentityMap)
    {
      return;
    }
    TransactionHandler h = sentityMap->GetActiveDataTransaction();
    if (h)
    {
      h->Register(entity);
    }
    if (StartDataTransaction())
    {
      Push(datatransaction, memberId);
      PushRaw<bool>(datatransaction, true);
      Push(datatransaction, info);
      if (SUPERSUBCLASS( rpc::IRemoteEntity, T1 ))
      {
        if (newValue) newValue->SetParent(entity);
      }
      Push(datatransaction, newValue); 
      ArgWriter& args = datatransaction->GetRollbackArgs();
      int offset = args.size();
      args.Push(memberId);
      args.Push(true);
      args.PushRaw<bool>(true);
      args.Push(info);
      args.PushRef(oldValue);
      datatransaction->AddParam(offset, args.size()-offset);
    }
  }

  template <typename T1> void EraseMember(IRemoteEntity* entity, byte memberId, const ContainerOperationInfo& info, const T1& oldValue) 
  { 
    if ( IsReadOnly() )
      return;
    StrongMT<rpc::IEntityMap> sentityMap = entityMap.Lock();
    if (!sentityMap)
    {
      return;
    }
    TransactionHandler h = sentityMap->GetActiveDataTransaction();
    if (h)
    {
      h->Register(entity);
    }
    if (StartDataTransaction())
    {
      Push(datatransaction, memberId);
      PushRaw<bool>(datatransaction, true);
      Push(datatransaction, info);
      ArgWriter& args = datatransaction->GetRollbackArgs();
      int offset = args.size();
      args.Push(memberId);
      args.Push(true);
      args.PushRaw<bool>(true);
      args.Push(info);
      args.PushRef(oldValue);
      datatransaction->AddParam(offset, args.size()-offset);
    }
  }

  rpc::Transaction* StartDataTransaction(uint methodId=rpc::NoMethod, bool isReady=true) { if (!datatransaction) datatransaction = StartTransaction(methodId, isReady);  return datatransaction; }

  rpc::ECallResult::Enum DoDataTransaction(IPacketPipe * pipe) { return DoTransaction(pipe, datatransaction); }
  void StopDataTransaction() { StopTransaction(datatransaction); }
  // push
  bool Push(rpc::Transaction* transaction, int value)  { return transaction?transaction->GetArgs().Push(value):false; }
  bool Push(rpc::Transaction* transaction, uint value)  { return transaction?transaction->GetArgs().Push(value):false; }
  bool Push(rpc::Transaction* transaction, ushort value)  { if (transaction) { return transaction->GetArgs().Push(short(value)); } return false; }
  bool Push(rpc::Transaction* transaction, char value) { return transaction?transaction->GetArgs().Push(value):false; }
  bool Push(rpc::Transaction* transaction, unsigned char value) { return transaction?transaction->GetArgs().Push(value):false; }
  bool Push(rpc::Transaction* transaction, bool value) { return transaction?transaction->GetArgs().Push(value):false; }
  bool Push(rpc::Transaction* transaction, float value) { return transaction?transaction->GetArgs().Push(value):false; }
  bool Push(rpc::Transaction* transaction, short value) { return transaction?transaction->GetArgs().Push(value):false; }
  bool Push(rpc::Transaction* transaction, double value) { return transaction?transaction->GetArgs().Push(value):false; }
  bool Push(rpc::Transaction* transaction, long long value) { return transaction?transaction->GetArgs().Push(value):false; }
  bool Push(rpc::Transaction* transaction, unsigned long long value) { return transaction?transaction->GetArgs().Push(value):false; }
  bool Push(rpc::Transaction* transaction, const char* value) { return transaction?transaction->GetArgs().Push(value):false; }
  bool Push(rpc::Transaction* transaction, const wchar_t* value) { return transaction?transaction->GetArgs().Push(value):false; }
  bool Push(rpc::Transaction* transaction, const nstl::string& value) { return transaction?transaction->GetArgs().Push(value):false; }
  bool Push(rpc::Transaction* transaction, const nstl::wstring& value) { return transaction?transaction->GetArgs().Push(value):false; }
  bool Push(rpc::Transaction* transaction, const ContainerOperationInfo& value) { return transaction?transaction->GetArgs().Push(value):false; }
  bool Push(rpc::Transaction* transaction, const rpc::MemoryBlock& value) { return transaction?transaction->GetArgs().Push(value):false; }
  template <typename T> bool Push(rpc::Transaction* transaction, const nstl::vector<T>& value) { return transaction?transaction->GetArgs().Push(value):false; }
  template <typename T, unsigned int capacity> bool Push(rpc::Transaction* transaction, const FixedVector<T, capacity>& value) { return transaction?transaction->GetArgs().Push(value):false; }

  template <typename T> bool Push(rpc::Transaction* transaction, T* value) 
  { 
    if (transaction)
    {
      transaction->GetArgs().SetPipe(multiPipe);
      return transaction->GetArgs().Push(value);
    }
    return false;
  }

  template <typename T> bool Push(rpc::Transaction* transaction, const T& value) 
  { 
    if (transaction)
    {
      transaction->GetArgs().SetPipe(multiPipe);
      return transaction->GetArgs().Push( value ); 
    }
    return false;
  }

  bool PushArrayMember(rpc::Transaction* transaction, const IRemoteEntity* value) { return transaction?transaction->GetArgs().Push(value):false; }
  bool PushArrayMember(rpc::Transaction* transaction, IRemoteEntity* value) { return transaction?transaction->GetArgs().Push(value):false; }
  bool PushArrayMember(rpc::Transaction* transaction, const char* value) { return transaction?transaction->GetArgs().Push(value):false; }
  bool PushArrayMember(rpc::Transaction* transaction, const wchar_t* value) { return transaction?transaction->GetArgs().Push(value):false; }
  bool PushArrayMember(rpc::Transaction* transaction, const nstl::string& value) { return transaction?transaction->GetArgs().Push(value):false; }
  bool PushArrayMember(rpc::Transaction* transaction, const nstl::wstring& value) { if (transaction) { return transaction->GetArgs().Push(value); } return false ; }
  bool PushArrayMember(rpc::Transaction* transaction, char value) { return transaction?transaction->GetArgs().Push(value):false; }
  bool PushArrayMember(rpc::Transaction* transaction, wchar_t value) { return transaction?transaction->GetArgs().Push(value):false; }

  template <typename T> bool PushArrayMember(rpc::Transaction* transaction, const T& value) 
  { 
    if (transaction)
    {
      transaction->GetArgs().SetPipe(multiPipe);
      if ( SUPERSUBCLASS( rpc::Data, T ) ) 
        return transaction->GetArgs().Push( value ); 
      else 
        return transaction->GetArgs().PushSimpleStructWithoutSize( value );
    }
    return false;
  }

  bool Push(rpc::Transaction* transaction,  void* val, uint size )
  {
    if (transaction) 
    {
      return transaction->GetArgs().Push( val, size );
    }
    return false;
  }            
  template <typename T>    
  bool PushRaw(rpc::Transaction* transaction, const T& value) { if (transaction) { return transaction->GetArgs().PushRaw(value);} return false; }
  virtual int ConnectToNodes(rpc::IEntityMap* _entityMap) { return 0; }
  rpc::Transaction* StartTransaction( uint methodId=rpc::NoMethod, bool isReady=true);
  WeakMT<rpc::IEntityMap>& GetEntityMap() { return entityMap; }
protected:
  rpc::ECallResult::Enum DoTransaction(IPacketPipe * pipe, rpc::Transaction* & transaction);
  void StopTransaction(rpc::Transaction* & transaction);
private:
// set
template <typename T> void Set(rpc::Transaction* transaction, const T& newValue) { Push(transaction, newValue); }

protected:
  EntityId entityId;
  rpc::Transaction* datatransaction;
  WeakMT<rpc::IEntityMap> entityMap;
  StrongMT<MultiPacketPipe> multiPipe;
  union
  {
    byte data;
    struct  
    {
      byte reserved: 1; 
      byte isConstructed : 1;
      byte isFailed : 1;
      byte reserved0: 1;
      byte isUpdated : 1;
      byte isShared : 1;
      byte isConnected : 1;
      byte isReadOnly : 1;      
    };
  };
  TLogTrace logTrace;
  MethodCallInfo creationInfo;
}; //class Args

} // rpc
