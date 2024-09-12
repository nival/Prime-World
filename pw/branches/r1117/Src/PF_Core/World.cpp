#include "stdafx.h"

#include "World.hpp"
#include "WorldObject.h"
#include "ClientObject.h"
#include "../Core/WorldCommand.h"
#include "../System/InlineProfiler.h"
#include "../System/Crc32Calculator.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace
{

class ObjectsStatsCollector
{
  struct TypeStats
  {
    int minSize;
    int maxSize;
    int size;
    int objects;

    TypeStats() : minSize( 0 ), maxSize( 0 ), size( 0 ), objects( 0 ) { }
    
    void Add( int _size )
    {
      size += _size;
      ++objects;
      if ( minSize == 0 || minSize > _size )
        minSize = _size;
      if ( maxSize == 0 || maxSize < _size )
        maxSize = _size;
    }
  };

  int level;
  int size;
  hash_map<string, TypeStats> stats;

public:
  bool IsChecksum() { return false; }

  void OnReset() { level = 0; size = 0; stats.clear(); }

  bool OnStartChunk( const IBinSaver::chunk_id idChunk, int chunkType )
  {
    if ( level == 0 && chunkType == IBinSaver::CHUNK_COBJECTBASE )
      size = 0;
    ++level;
    return true;
  }
	
  void OnFinishChunk()
  {
    --level;
  }
  
  void OnStoreObject( CObjectBase* pObject )
  {
    stats[pObject->GetObjectTypeName()].Add( size );
    size = 0;
  }
  
  void OnStorePointer( CObjectBase* pObject ) { size += sizeof( void* ); }

  void OnDataChunk( const IBinSaver::chunk_id, const void* pData, int nSize ) { size += nSize; }
  void OnDataChunk( const string& data ) { size += data.size(); }
  void OnDataChunk( const wstring& data ) { size += 2 * data.size(); }
  
  template<class TCrc>
  void OnCurrentCrc( const TCrc &crc ) {}

  void DumpStats() const
  {
    for( hash_map<string, TypeStats>::const_iterator it = stats.begin(); it != stats.end(); ++it )
      DebugTrace( "%s; %d; %d; %d; %d; %d", it->first.c_str(), it->second.objects, it->second.size, it->second.minSize, it->second.maxSize, it->second.size / it->second.objects );
  }
};
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace PF_Core
{
static NDebug::DebugVar<int> mainPerf_WOStepped( "Objects stepped", "PerfCnt" );

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
World::World()
  : lastUsedId(PF_Core::INVALID_OBJECT_ID)
  , bInCommandProcessing(false)
  , pCurrentObjectIsBeingStepped(0)
  , m_accounting(NULL)
  , slowdownHint( 1.0f )
  , ignoreSlowdownHint( false )
  , isGamePaused( false )
  , pausedPlayerId( 0 )
  , objectRegistrationLocked( false )
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void World::OnDestroyContents()
{
	// Apply add/remove updates
	ProcessAddRemove(); 

	// Remove all objects
	for(TObjects::iterator it = objects.begin(), end = objects.end(); it != end; ++it)
		if(IsValid(it->second))
			it->second->Die();
	
	// Force destroy removed
	ProcessAddRemove();
  Clear( objectsForStep );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void World::CalcCRC( IBinSaver& f, bool fast )
{
  if ( !fast )
	{
		if ( f.StartChunk( 3, 1, IBinSaver::CHUNK_DATA ) )
		{
			int nSize = objects.size();
			int nBuckets = objects.bucket_count();
			f.Add( 3, &nSize );
			f.Add( 4, &nBuckets );

			vector<int> indices;
			indices.resize( nSize );
			int i = 1;
			for (TObjects::iterator pos = objects.begin(); pos != objects.end(); ++pos, ++i )
				indices[ nSize - i ] = pos->first;
			for ( i = 0; i < nSize; ++i )
			{
				if(!f.IsChecksum() || objects[ indices[i] ]->NeedToSerialize())
				{
					f.Add( 1, &indices[i], i + 1 );
				}
			}
			for ( i = 0; i < nSize; ++i )
			{
				if(!f.IsChecksum() || objects[ indices[i] ]->NeedToSerialize())
				{
					f.Add( 2, &objects[ indices[i] ], i + 1 );
				}
			}
		}

		f.FinishChunk();
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void World::SubscribeObject(WorldObjectBase* pObject)
{
  NI_ASSERT(pObject, "Attempt to subscribe null object!");
	NI_ASSERT(!pObject->ringPart.isLinked(), "Attempt to subscribe object second time!");

	objectsForStep.addLast(pObject);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void World::UnsubscribeObject(WorldObjectBase* pObject)
{
	if (!IsSubscribed(pObject))
		return;

	if (pObject == pCurrentObjectIsBeingStepped)
		pCurrentObjectIsBeingStepped = WorldObjectBase::Ring::next(pCurrentObjectIsBeingStepped);
	WorldObjectBase::Ring::remove(pObject);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool World::IsSubscribed(WorldObjectBase* pObject) const
{
  return pObject && pObject->ringPart.isLinked();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void World::RegisterObject(WorldObjectBase* pObject, int realWObj, bool immediately)
{
  NI_VERIFY_TRACE(pObject, "Must register only real objects!", return; );
  NI_VERIFY_TRACE(!IsObjectRegistrationLocked(), "Attempt to register object, while registration is locked!", return; );

	int curObjectId = pObject->GetObjectId();
  NI_ASSERT_TRACE( curObjectId == INVALID_OBJECT_ID, NStr::StrFmt( "Registering object %s with assigned ID %d. ID reassigned.", pObject->GetObjectTypeName(), curObjectId ) );
  curObjectId = ++lastUsedId;
  pObject->objectId = curObjectId;
	// Add object to main hash map
	if ( realWObj == 1 )
  {
		objects[curObjectId] = pObject;
    objectIds[pObject] = curObjectId;
  }
	else
  {
		weakObjects[curObjectId] = pObject;
    weakObjectIds[pObject] = curObjectId;
  }

	// Remember object
	if (immediately)
	{
		// Subscribe object to step() event, it it wants :)
		if (pObject->NeedToBeStepped())
			SubscribeObject(pObject);
		if ( pObject->NeedToBeStepped() && realWObj != 1 )
			NI_ALWAYS_ASSERT("Try to add stepped fake world object" );
	}
	else
	{
		if ( realWObj == 1 )
			addedObjects.addLast(pObject);
	}

  WORLD_OBJECTS_CHECK_LIST_ADD( pObject );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void World::UnregisterObject(WorldObjectBase* pObject, bool full /*= true*/)
{
  NI_VERIFY_TRACE(pObject, "Unregistration of null object!", return);
  if (IsObjectRegistrationLocked())
  {
    DebugTrace( "Attempt to unregister %s object, while registration is locked!", pObject->GetObjectTypeName() );
    return;
  }

  TObjects::iterator it = objects.find(pObject->GetObjectId());

  if ( it == objects.end() )
  {
    TWeakObjects::iterator wit = weakObjects.find(pObject->GetObjectId());

    if ( wit == weakObjects.end() )
    {
      for (ring::Range<WorldObjectBase::Ring> it(addedObjects); it; ++it)
      {
        if (&(*it) == pObject) // Object was added and removed on the same step
        {
          pObject->objectId = ADDED_THEN_REMOVED_OBJECT_ID;
          break;
        }
      }
      NI_VERIFY_TRACE(pObject->objectId == ADDED_THEN_REMOVED_OBJECT_ID, "Object is not registered!", return; );

      RemoveObject(pObject);
    }
    else if( full )
    {
      weakObjects.erase( wit );

      TObjectIds::iterator id = weakObjectIds.find( pObject );
      if ( id != weakObjectIds.end() )
        weakObjectIds.erase( id );
    }
  }
  else
  {
    NI_VERIFY_TRACE(!full, 
      NStr::StrFmt( "Attempt to make a full unregister of %s object, while it is still in objects list!", 
        pObject->GetObjectTypeName() ), return; );

    // Save real world object in the weak objects list for serrialization needs. 
    // It will be fully unregistred when the object will die.
    weakObjects[pObject->GetObjectId()] = pObject;
    weakObjectIds[pObject] = pObject->GetObjectId();

    RemoveObject(pObject);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void World::OnSerialize( IBinSaver &f )
{
  if (f.IsChecksum())
  {
    int objectIdsCount = objectIds.size();
    int weakObjectIdsCount = weakObjectIds.size();
    f.Add( 100, &objectIdsCount );
    f.Add( 101, &weakObjectIdsCount );
  }
  else if (f.IsReading())
  {
    objectIds.clear();
    weakObjectIds.clear();

    for (TObjects::const_iterator it = objects.begin(); it != objects.end(); ++it)
      objectIds[it->second] = it->first;

    for (TWeakObjects::const_iterator it = weakObjects.begin(); it != weakObjects.end(); ++it)
      weakObjectIds[it->second] = it->first;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void World::RemoveObject(WorldObjectBase* pObject)
{
  NI_VERIFY_TRACE(pObject, "Removing null object!", return);

  CObj<WorldObjectBase> pTempPointerForSafeRingTransfer(pObject);
  UnsubscribeObject(pObject);      // Will remove pObject from any (main or added) ring 
  removedObjects.addLast(pObject); // Add to remove objects ring
  pTempPointerForSafeRingTransfer = 0; 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void World::ExecuteCommand( NCore::WorldCommand* pCommand )
{
  NI_VERIFY( IsValid( pCommand ), "Invalid command", return );
  
  if(bInCommandProcessing)
  {
    pendingCommands.push_back(pCommand);
    return;
  }
      
  bInCommandProcessing = true;

  ExecuteCommandInternal(pCommand);
  
  for(;!pendingCommands.empty();)
  {
    CPtr<NCore::WorldCommand> pCmd = pendingCommands.front();
    pendingCommands.pop_front();

    ExecuteCommandInternal(pCmd);
  }

  bInCommandProcessing = false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void World::ExecuteCommandInternal(NCore::WorldCommand* pCommand)
{
  if ( !pCommand->CanExecute() )
  {
    systemLog( NLogg::LEVEL_DEBUG ) << "Cannot process command " << pCommand->GetObjectTypeName() << endl;
    return;
  }

  pCommand->Execute(this);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int World::GetObjectID( CObjectBase* p )
{
  if ( p == this )
    return PF_Core::WORLD_ID;

  TObjectIds::const_iterator id = objectIds.find( p );

  if ( id == objectIds.end() )
  {
    id = weakObjectIds.find( p );

    if ( id == weakObjectIds.end() )
    {
      if ( p && IsValid(p) )
      {
        if ( WorldObjectBase* wob = dynamic_cast<WorldObjectBase*>(p) )
        {
          int objectId = wob->GetObjectId();
          NI_ALWAYS_ASSERT_TRACE( NStr::StrFmt( "Object not registered! (oid=%d tn=%s)", objectId, p->GetObjectTypeName() ) );
          return objectId;
        }
        else
          NI_ALWAYS_ASSERT_TRACE( NStr::StrFmt( "Not a world object! (tn=%s)", p->GetObjectTypeName() ) );
      }

      return PF_Core::INVALID_OBJECT_ID;
    }
  }

  return id->second;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CObjectBase* World::GetObject ( int nID )
{
  if(PF_Core::INVALID_OBJECT_ID == nID)
    return NULL;

	if ( nID == PF_Core::WORLD_ID )
		return this;
  
  TObjects::iterator object = objects.find(nID);
	if ( objects.end() == object )
	{
		TWeakObjects::iterator wit = weakObjects.find(nID);
		if ( wit == weakObjects.end() )
			return NULL;
		else
			return wit->second;
	}
	else
	  return object->second;
}



int World::GetObjectIdST( BaseObjectST * object )
{
  NI_ALWAYS_ASSERT( "Not implemented" );
  return 0;
}



BaseObjectST * World::GetObjectST( int id )
{
  NI_ALWAYS_ASSERT( "Not implemented" );
  return 0;
}



int World::GetObjectIdMT( BaseObjectMT * pObject )
{
  NI_ALWAYS_ASSERT( "Not implemented" );
  return 0;
}



BaseObjectMT * World::GetObjectMT( int id )
{
  NI_ALWAYS_ASSERT( "Not implemented" );
  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void World::UpdatePlayerStatuses(const NCore::TStatuses & statuses)
{
  NI_ALWAYS_ASSERT( "Not implemented" );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void World::ExecuteCommands(const NCore::TPackedCommands & commands)
{
  NI_ALWAYS_ASSERT( "Not implemented" );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool World::Step(float dtInSeconds, float dtLocal)
{
  NI_PROFILE_FUNCTION

  NI_VERIFY(dtInSeconds > 0, "Stepping World with zero time delta", return true;);
  bool bSuccess = true;

	int numObjects = 0;

	pCurrentObjectIsBeingStepped = objectsForStep.first();
	//WorldObjectBase *pTerm = objectsForStep.last();
	while (pCurrentObjectIsBeingStepped != objectsForStep.last())
	{
		numObjects++;
		
    WorldObjectBase *pCur = pCurrentObjectIsBeingStepped;
    
    NI_ASSERT_TRACE( pCurrentObjectIsBeingStepped->GetObjectId() >= 0, "Error : world object without Id!" )
    pCurrentObjectIsBeingStepped->Step(dtInSeconds);

    if (pCurrentObjectIsBeingStepped == pCur)
    {
      pCurrentObjectIsBeingStepped = WorldObjectBase::Ring::next(pCurrentObjectIsBeingStepped);
    }
    else if (pCurrentObjectIsBeingStepped == objectsForStep.last())
    {
			break;
    }
	}

	mainPerf_WOStepped.SetValue(numObjects);

	pCurrentObjectIsBeingStepped = 0;

	NI_VERIFY(ProcessAddRemove(), "", return false;)
	NI_VERIFY(removedObjects.empty() && addedObjects.empty(), "",  return false; );

  WORLD_OBJECTS_CHECK_LIST_VERIFY

	return bSuccess;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int World::GetStepLength() const
{
  NI_ALWAYS_ASSERT( "Not implemented" );
  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float World::GetStepLengthInSeconds() const
{
  NI_ALWAYS_ASSERT( "Not implemented" );
  return 0.0f;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool World::ProcessAddRemove()
{
  NI_PROFILE_FUNCTION;
  
	if (pCurrentObjectIsBeingStepped)
		return false;

  // apply added objects update
	for (ring::Range<WorldObjectBase::Ring> it(addedObjects); it;)
	{
		WorldObjectBase *pObject = &(*it);
		++it;
		// Remove from added ring
		WorldObjectBase::Ring::remove(pObject);
		// Subscribe object to step() event, it it wants :)
		if (pObject->NeedToBeStepped())
			SubscribeObject(pObject);
	}

	// apply removed objects update
	for (ring::Range<WorldObjectBase::Ring> it(removedObjects); it;)
	{
		WorldObjectBase *pObject = &(*it);
		++it;

		NI_ASSERT_TRACE(WorldObjectBase::Ring::prev(WorldObjectBase::Ring::next(pObject)) == pObject, "Ring consistency check failed!");
		NI_ASSERT_TRACE(WorldObjectBase::Ring::next(WorldObjectBase::Ring::prev(pObject)) == pObject, "Ring consistency check failed!");

		if (pObject->GetObjectId() >= 0)
		{
			TObjects::iterator object = objects.find(pObject->GetObjectId());
			if (objects.end() != object)
				objects.erase( object );

			TObjectIds::iterator id = objectIds.find( pObject );
			if ( id != objectIds.end() )
				objectIds.erase( id );
		}

		NI_ASSERT_TRACE(WorldObjectBase::Ring::prev(WorldObjectBase::Ring::next(pObject)) == pObject, "Ring consistency check failed!");
		NI_ASSERT_TRACE(WorldObjectBase::Ring::next(WorldObjectBase::Ring::prev(pObject)) == pObject, "Ring consistency check failed!");

		WorldObjectBase::Ring::remove(pObject);
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
WorldObjectBase* World::GetObjectById(int id) const
{
	// Do we really need this check?  
	//NI_VERIFY(removedObjects.end() == removedObjects.find(id), "Trying to query removed object!", return NULL; );
  
  TObjects::const_iterator it = objects.find(id);
  if( objects.end() != it )
    return CPtr<WorldObjectBase>(it->second.GetPtr());
	else
	{
		TWeakObjects::const_iterator wit = weakObjects.find(id);
		if ( weakObjects.end() != wit )
			return CPtr<WorldObjectBase>(wit->second.GetPtr());
	}

  return NULL;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void World::SetAccounting( lobby::AccountingGadget * accounting )
{
  m_accounting = accounting;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void World::SetPause( bool paused, int playerId )
{
  if ( !isGamePaused && paused )
  {
    pausedPlayerId = playerId;
    isGamePaused   = true;
  }
  else if ( ( isGamePaused && !paused ) && ( pausedPlayerId == playerId  ) )
  {
    isGamePaused = false;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
lobby::AccountingGadget * World::GetAccounting()
{
  return m_accounting;
}

} // namespace PF_Core
