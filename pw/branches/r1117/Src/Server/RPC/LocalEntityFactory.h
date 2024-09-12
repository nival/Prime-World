#pragma once

#include "Base.h"

namespace rpc
{

_interface ILocalEntityCreator
{
  virtual ~ILocalEntityCreator()=0;
  virtual rpc::ILocalEntity* Create(void* value, rpc::IEntityMap* entityMap)=0;
};

inline ILocalEntityCreator::~ILocalEntityCreator() {}

template <typename L, typename O>
class LocalEntityCreator : public ILocalEntityCreator
{
  virtual rpc::ILocalEntity* Create(void* value, rpc::IEntityMap* entityMap)
  {
    return new L(value?(O*)value:new O, entityMap, 0);
  }
};

template <typename L, typename O>
class LocalEntityAttachCreator : public ILocalEntityCreator
{
  virtual rpc::ILocalEntity* Create(void* value, rpc::IEntityMap* entityMap)
  {
    return new L((O*)value, entityMap, 0);
  }
};

struct LocalEntityFactory : rpc::ILocalEntityFactory, NonCopyable
{
  typedef nstl::hash_map<uint, ILocalEntityCreator*> EntityConstructors;

  LocalEntityFactory( rpc::Gate * _cache ) :
  cache( _cache )
  {
  }

  ~LocalEntityFactory()
  {
    for (EntityConstructors::iterator it=constructors.begin();it!=constructors.end();++it)
    {
      delete it->second;
    }
  }

  template <typename O, typename L> void Register()
  {
    StrongMT<rpc::Gate> lcache = cache.Lock();
    if (lcache)
    {
      constructors.insertUnique(rpc::GetId<O>(), new LocalEntityCreator<L, O>());
      lcache->RegisterFactory<O>(*this);
    }
  }

  template <typename O, typename L> void RegisterAttach()
  {
    StrongMT<rpc::Gate> lcache = cache.Lock();
    if (lcache)
    {
      constructors.insertUnique(rpc::GetId<O>(), new LocalEntityAttachCreator<L, O>());
      lcache->RegisterFactory<O>(*this);
    }
  }

  virtual rpc::ILocalEntity* Create(const rpc::LocalEntityCreationInfo& entityInfo, rpc::Arguments&, rpc::IEntityMap* entityMap)
  {
    EntityConstructors::iterator it = constructors.find(entityInfo.classId);
    if (it != constructors.end())
    {
      return it->second->Create(0, entityMap);
    }
    return 0;
  }

  virtual rpc::ILocalEntity* Create(uint classId, void* value, rpc::IEntityMap* entityMap) 
  { 
    EntityConstructors::iterator it = constructors.find(classId);
    if (it != constructors.end())
    {
      return it->second->Create(value, entityMap);
    }
    return 0; 
  }
  virtual void Destroy( rpc::ILocalEntity* /*entity*/ ) {}

  EntityConstructors constructors;
  WeakMT<rpc::Gate> cache;
};

} // rpc
