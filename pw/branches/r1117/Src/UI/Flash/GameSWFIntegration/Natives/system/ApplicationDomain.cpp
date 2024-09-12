#include "TamarinPCH.h"

#include "ApplicationDomain.h"
#include "../../FlashMovie.h"

namespace avmplus
{


bool ApplicationDomainObject::hasDefinition( AvmString name )
{
  ScriptEnv * objectEnv;
  Traits * objectTraits = FindTraits(name, objectEnv);

  return objectTraits;
}


Traits * ApplicationDomainObject::FindTraits( AvmString name, ScriptEnv* & outEnv )
{
  flash::Movie * flashMovie = FlashCore()->GetMovie();
  flash::PoolDataByFrame & poolDataByFrame = flashMovie->GetPoolData();

  flash::PoolDataByFrame::iterator poolDataIter = poolDataByFrame.begin();
  for (; poolDataIter != poolDataByFrame.end(); poolDataIter++)
  {
    Traits * objectTraits = FlashCore()->FindTraitsInPool(name, poolDataIter->second->Get()->pool);
    if (objectTraits)
    {
      outEnv = poolDataIter->second->Get()->scriptEnv;
      return objectTraits;
    }
  }

  return 0;
}

avmplus::AvmBox ApplicationDomainObject::getDefinition( AvmString name )
{
  ScriptEnv * objectEnv;
  Traits * objectTraits = FindTraits(name, objectEnv);

  if (!objectTraits) return 0;
  
  ClassClosure * objectClass = FlashCore()->GetClassByTraits(objectTraits, objectEnv);

  return objectClass->atom();
}
} 