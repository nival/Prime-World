#pragma once

#include "WorldObject.h"
#include "ClientObject.h"
#include "../System/ChunklessSaver.h"

namespace NWorld
{
class WorldChecker;
}

namespace NCore
{
  class PackedWorldCommand;
  struct ClientStatus;
}

namespace PF_Core
{

class World : public IWorld, public IPointerHolder
{
	OBJECT_BASIC_METHODS(World);

protected:
	typedef nstl::hash_map<int, CObj<WorldObjectBase> > TObjects;
	typedef nstl::hash_map<int, CPtr<WorldObjectBase> > TWeakObjects;
  typedef nstl::hash_map<CObjectBase*, int, PtrHash>  TObjectIds;
private:
	typedef nstl::list<CPtr<NCore::WorldCommand> >   TCommands;
	void ExecuteCommandInternal(NCore::WorldCommand* pCommand);
  
  lobby::AccountingGadget * m_accounting;
  
  WorldObjectBase       *pCurrentObjectIsBeingStepped;
  float slowdownHint;
  bool ignoreSlowdownHint;
  TObjectIds objectIds;
  TObjectIds weakObjectIds;

  bool objectRegistrationLocked;

  WORLD_OBJECTS_CHECK_LIST;

  ZDATA
  ZNOPARENT( IWorld )
  ZNOPARENT( IPointerHolder )
	TObjects  objects;
	TWeakObjects weakObjects;
	int       lastUsedId;

	TCommands pendingCommands;
	bool      bInCommandProcessing;

	WorldObjectBase::Ring addedObjects;
	WorldObjectBase::Ring removedObjects;

	WorldObjectBase::Ring objectsForStep;

  bool isGamePaused;
  int  pausedPlayerId;

  ZONSERIALIZE  // Must be after objects and weakObjects
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&objects); f.Add(3,&weakObjects); f.Add(4,&lastUsedId); f.Add(5,&pendingCommands); f.Add(6,&bInCommandProcessing); f.Add(7,&addedObjects); f.Add(8,&removedObjects); f.Add(9,&objectsForStep); f.Add(10,&isGamePaused); f.Add(11,&pausedPlayerId); OnSerialize( f ); return 0; }


private:
  void OnSerialize( IBinSaver &f );

protected:
	TObjects&                  GetObjects() { return objects; }
	TWeakObjects&                  GetWeakObjects() { return weakObjects; }
  void RemoveObject(WorldObjectBase* pObject);

public:
	World();

	virtual void               OnDestroyContents();
  
	// IWorld implementation
	virtual void           RegisterObject(WorldObjectBase* pObject, int realWObj, bool immediately); 
	virtual void           UnregisterObject(WorldObjectBase* pObject, bool full = true);

  void SetObjectRegistrationLocked(bool _objectRegistrationLocked) { objectRegistrationLocked = _objectRegistrationLocked; }
  bool IsObjectRegistrationLocked() const { return objectRegistrationLocked; }

	virtual WorldObjectBase* GetObjectById(int id) const;

	void SubscribeObject(WorldObjectBase* pObject);
	void UnsubscribeObject(WorldObjectBase* pObject);
  bool IsSubscribed(WorldObjectBase* pObject) const;

  virtual void SetSlowdownHint( float hintValue ) { slowdownHint = hintValue; }
  virtual float GetSlowdownHint() const { return ignoreSlowdownHint ? 1.f : slowdownHint; }
  virtual void SetIgnoreSlowdownHint( bool ignore ) { ignoreSlowdownHint = ignore; }

	// IWorld implementation
	virtual void               ExecuteCommand( NCore::WorldCommand* pCommand );
	virtual IPointerHolder*    GetPointerSerialization() {return this;}
  virtual void               UpdatePlayerStatuses(const NCore::TStatuses & statuses);
  virtual void               ExecuteCommands(const NCore::TPackedCommands & commands);
	virtual bool               Step(float dtInSeconds, float dtLocal);
  virtual void               CalcCRC( IBinSaver& f, bool fast );
  virtual int                GetStepNumber() const { return 0; }
  virtual int                GetStepLength() const;
  virtual float              GetStepLengthInSeconds() const;

	virtual bool               ProcessAddRemove(); 
  virtual NRandom::RandomGenerator *GetRndGen() {return NULL;}

  virtual void SetPause( bool paused, int playerId );
  virtual bool IsPaused() const { return isGamePaused; }

	// IPointerHolder implementation
	virtual int GetObjectID( CObjectBase *p );
	virtual CObjectBase* GetObject( int nID );

  virtual int GetObjectIdST( BaseObjectST * object );
  virtual BaseObjectST * GetObjectST( int id );
  virtual int GetObjectIdMT( BaseObjectMT * pObject );
	virtual BaseObjectMT * GetObjectMT( int id );

  virtual void SetAccounting( lobby::AccountingGadget * accounting );
  lobby::AccountingGadget * GetAccounting();

	template <class F>
	void ForAllObjectsBeingStepped(F &f) const
	{
		for (ring::Range<WorldObjectBase::Ring> it(objectsForStep); it; ++it)
			f(*it);
	}

  //TODO is there any client objects that are created with this class?
  virtual bool CanCreateClients() { return true;}

	friend NWorld::WorldChecker;
	
	friend void MakeTrueAsyncForTest( World *pWorld );

  virtual void Save() const {};
  virtual void Load() {};

  virtual bool HasProtection() const { return false; }
  virtual bool PollProtectionResult(NCore::ProtectionResult& result) { return false; }
  virtual void SetProtectionUpdateFrequency(const int offset, const int frequency) {}
};

} // namespace PF_Core
