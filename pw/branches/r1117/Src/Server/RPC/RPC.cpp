#include "stdafx.h"
////////*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "RPC.h"
#include "System/Commands.h"
#include "System/Crc32Checksum.h"

namespace rpc
{

typedef pair<const char *, const  char *> BegEndPair;



inline void RevSkipTo( const char *pBeg, const char *&pCur, char ch )
{
  while( pCur != pBeg && *pCur != ch ) 
    --pCur;
}
 
inline void RevSkipWhile( const char *pBeg, const char *&pCur, char ch )
{
  while( pCur != pBeg && *pCur == ch ) 
    --pCur;
} 

inline const char *RevFindBefore( const char *pBeg, const char *pEnd, char ch )
{
  const char *pCur = pEnd;

  for( ;; )
  {
    if( pCur == pBeg )
      return pBeg;
      
    --pCur;
      
    if( *pCur == ch )
      return pCur + 1;  
  }
} 
 
BegEndPair FindClassName( const char *rawName )
{
  //В качестве className может быть передано либо имя 
  //функции в следующих форматах (результат макроса BOOST_CURRENT_FUNCTION)
  //MSVC: const char *__cdecl A::B::C::func(void)
  //GCC:  static const char* A::B::C::func()
  //Шаблоны:
  //MSVC: const char *__cdecl A::B::C<int>::func(void)
  //GCC: static const char* A::B::C<T>::func() [with T = int]
  //либо, непосредственно, имя класса 
  const char * pBeg = rawName;
  const char * pEnd = pBeg + strlen(rawName);
  
  if( pBeg == pEnd )
  {
    NI_ALWAYS_ASSERT( "Empty class name ");
    return BegEndPair(pBeg, pEnd);
  }

  const char *pCur = pEnd - 1;
  
  if( *pCur != ')' && *pCur != ']' )
      return BegEndPair(pBeg, pEnd);

  BegEndPair res;

  RevSkipTo( pBeg, pCur, ':' );
  RevSkipWhile( pBeg, pCur, ':' );
  res.second = pCur + 1; 
  RevSkipTo( pBeg, pCur, ' ' );
  res.first = pCur + 1;
  
  NI_ASSERT( res.first != res.second, "Raw class name format error" );
  
  return res;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint _GetId(const char* _className, IdType idType)
{
  typedef nstl::hash_map<const char*, uint> Id2Hash;
  
  static Id2Hash idHash;
  Id2Hash::const_iterator it = idHash.find(_className);
  
  if (it == idHash.end())
  {
    Crc32Checksum s;

    if (idType != GeneratedType)
    {
      BegEndPair cls = FindClassName( _className );
      
      if (idType != RemoteType)
      {
        s.Add( cls.first, cls.second - cls.first );
      }
      else
      {
        //Должны пропустить первую букву R в названии класса
        const char *pCur = RevFindBefore( cls.first, cls.second, ':' );
      
        s.Add( cls.first, pCur - cls.first );
        
        if( *pCur == 'R' )
          ++pCur;
         
        s.Add( pCur, cls.second - pCur );
      }
    }
    else
    {
      s.AddString(_className);
    }
    
    
    it = idHash.insert( Id2Hash::value_type(_className, s.Get()) ).first;   
  }
  
  return it->second;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EntityFactoriesContainer& GetGlobalFactoryContainer()
{
  static EntityFactoriesContainer entityFactory;
  return entityFactory;
}

EntityFactoriesContainer& GetGlobalRemoteFactoryContainer()
{
  static EntityFactoriesContainer remoteEntityFactory;
  return remoteEntityFactory;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void* EntityFactoriesContainer::_GetFactory( uint classId )
{
  EntityFactoryMap::iterator it = entityTypes.find(classId);

  if(it != entityTypes.end())
    return it->second;

  EntityFactoryMap& globalTypes = GetGlobalFactoryContainer().getFactoryMap();
  it = globalTypes.find(classId);

  if(it != globalTypes.end())
    return it->second;

  return 0;
}
void EntityFactoriesContainer::_RegisterFactory( uint classId, void* factory )
{
  NI_ASSERT(entityTypes.find(classId) == entityTypes.end(), "Class already registered");
  entityTypes[classId] = factory;
}

void EntityFactoriesContainer::UnregisterFactory( uint classId )
{
  EntityFactoryMap::iterator it = entityTypes.find(classId);
  NI_VERIFY(it != entityTypes.end() && entityTypes.size() != 0, "Class not found", return;);
  entityTypes.erase(it);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RegisterFactory(uint classId, rpc::ILocalEntityFactory& factory)
{
  EntityFactoriesContainer& gFactory = GetGlobalFactoryContainer();
  return gFactory.RegisterFactory( classId, factory );
}
void UnregisterFactory(uint classId)
{
  EntityFactoriesContainer& gFactory = GetGlobalFactoryContainer();
  return gFactory.UnregisterFactory( classId );
}

void RegisterRemoteFactory(uint classId, rpc::IRemoteEntityFactory& factory)
{
  EntityFactoriesContainer& factoryContainer = GetGlobalRemoteFactoryContainer();
  return factoryContainer.RegisterFactory( classId, factory );
}
void UnregisterRemoteFactory(uint classId)
{
  EntityFactoriesContainer& factoryContainer = GetGlobalRemoteFactoryContainer();
  return factoryContainer.UnregisterFactory( classId );
}



class LocalRemoteEntity : public IRemoteEntity, BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(LocalRemoteEntity, IRemoteEntity, BaseObjectMT);
public:
  LocalRemoteEntity()
  {
    linfo.classId = 0xFFFFFFFF;
    linfo.instance = 0;
  }
  LocalRemoteEntity(void* instance, IBaseInterfaceMT* object, uint classId, const char* _gateName)
  {
    linfo.classId = classId;
    linfo.instance = instance;
    linfo.object = object;
    if (_gateName)
    {
      linfo.gateName = _gateName;
    }
  }

  virtual RemoteEntityInfo GetInfo() const { return info; }
  virtual const LocalInstanceInfo* GetLocalInstanceInfo() const { return &linfo; }
  virtual rpc::IUpdateCallback* GetUpdateCallback() { return 0; }
  virtual void SetParent(rpc::IRemoteEntity* _parent) {}
  virtual rpc::Status GetStatus() { return Connected; }
  RemoteEntityInfo info;
  LocalInstanceInfo linfo;
};

IRemoteEntity* CreateLocalRemoteWrapper(void* instance, IBaseInterfaceMT* object, uint classId, const char* gateName)
{
  return new LocalRemoteEntity(instance, object, classId, gateName);
}

void* GetLocalPtr(const rpc::IRemoteEntity* value)
{
  const LocalRemoteEntity * pLocalRemoteEntity = dynamic_cast<const LocalRemoteEntity*>(value);
  return (pLocalRemoteEntity)?(pLocalRemoteEntity->linfo.instance):(0);
}

static int rpcLogLevel = 0;
REGISTER_VAR( "rpc_log_level", rpcLogLevel, STORAGE_NONE );

static int rpcReportFreq = 0;
REGISTER_VAR( "rpc_report_freq", rpcReportFreq, STORAGE_NONE );

bool IsLogging()
{
  return rpcLogLevel != 0;
}

void EnableLog(int logLevel)
{
  rpcLogLevel = logLevel;
}

int GetLogLevel()
{
  return rpcLogLevel;
}

int GetReportFreq()
{
  return rpcReportFreq;
}


const char * CallStatusToString( CallStatus _st )
{
  switch( _st )
  {
    case CallPending:       return "Pending";
    case CallSuccessful:    return "Successful";
    case CallTimedOut:      return "TimedOut";
    case PipeDisconnected:  return "Disconnected";
    default:                return "Unknown";
  }
}


LocalEntityInfo::LocalEntityInfo(rpc::ILocalEntity* entity, const GUID& _entityGUID, uint classId, unsigned long _password):
entity(entity),
classId(classId),
password(_password),
entityGUID(_entityGUID)
{
}

} //namespace rpc


NI_DEFINE_REFCOUNT( rpc::ILocalEntity );
NI_DEFINE_REFCOUNT( rpc::IRemoteEntity );
