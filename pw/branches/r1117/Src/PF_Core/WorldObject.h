#pragma once

#include "../System/Ring.h"
#include "World.h"
#include "ClientObject.h"

namespace NScene
{
  class SceneObject;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define WORLD_OBJECT_CLIENT( clientClassName )                              \
  public:                                                                   \
  typedef clientClassName TClientObject;                                    \
  TClientObject* ClientObject() const;                                      \
  private:

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define WORLD_OBJECT_FUNCTIONS_NM( className, nsp )                         \
  nsp::className::TClientObject* nsp::className::ClientObject() const       \
  {                                                                         \
    return RetrieveClientObject<nsp::className::TClientObject>();           \
  } 

#ifndef _SHIPPING

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define WORLD_OBJECT_DUMMY_METHOD_DECLARE                                   \
  virtual bool isRegisteredInFactory() const;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define WORLD_OBJECT_DUMMY_METHOD_DEFINE( className )                       \
  bool className::isRegisteredInFactory() const { return true; }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define WORLD_OBJECT_DUMMY_METHOD_DEFINE_NM( className, nsp )               \
  bool nsp::className::isRegisteredInFactory() const { return true; }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define WORLD_OBJECTS_CHECK_LIST                                            \
  list<CPtr<WorldObjectBase> > newWorldObjects;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define WORLD_OBJECTS_CHECK_LIST_VERIFY                                     \
  for (list<CPtr<WorldObjectBase> >::iterator it = newWorldObjects.begin(); \
        it != newWorldObjects.end(); ++it)                                  \
  {                                                                         \
    if (IsValid(*it))                                                       \
    {                                                                       \
      NI_ASSERT( NObjectFactory::GetObjectTypeID( *it ) != -1,              \
        NStr::StrFmt( "Object %s isn't properly registered!",               \
          (*it)->GetObjectTypeName()) );                                    \
    }                                                                       \
  }                                                                         \
  newWorldObjects.clear();

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define WORLD_OBJECTS_CHECK_LIST_ADD( obj )                                 \
  newWorldObjects.push_back( obj );

#else // #ifndef _SHIPPING

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define WORLD_OBJECT_DUMMY_METHOD_DECLARE

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define WORLD_OBJECT_DUMMY_METHOD_DEFINE( className )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define WORLD_OBJECT_DUMMY_METHOD_DEFINE_NM( className, nsp )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define WORLD_OBJECTS_CHECK_LIST

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define WORLD_OBJECTS_CHECK_LIST_VERIFY

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define WORLD_OBJECTS_CHECK_LIST_ADD( obj )

#endif // #ifndef _SHIPPING

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Debug version of macro contains dummy method just for compilation error if
// appropriate use of REGISTER_WORLD_OBJECT_NM macro in cpp file is forgotten
#define WORLD_OBJECT_METHODS( N, className )                                \
  OBJECT_METHODS( N, className );                                           \
  WORLD_OBJECT_DUMMY_METHOD_DECLARE;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define WORLD_OBJECT_METHODS_WITH_CLIENT( N, className, clientClassName )   \
  WORLD_OBJECT_METHODS( N, className )                                      \
  WORLD_OBJECT_CLIENT( clientClassName )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define REGISTER_WORLD_OBJECT( className )                                  \
  REGISTER_SAVELOAD_CLASS( className );                                     \
  WORLD_OBJECT_DUMMY_METHOD_DEFINE( className );

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define REGISTER_WORLD_OBJECT_NM( className, nsp )                          \
  REGISTER_SAVELOAD_CLASS_NM( className, nsp );                             \
  WORLD_OBJECT_DUMMY_METHOD_DEFINE_NM( className, nsp );

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define REGISTER_WORLD_OBJECT_WITH_CLIENT_NM( className, nsp )              \
  REGISTER_WORLD_OBJECT_NM( className, nsp )                                \
  WORLD_OBJECT_FUNCTIONS_NM( className, nsp ) 


#define CALL_CLIENT( callFunction ) \
{ \
  if (IsValid( ClientObject() ) ) \
  ClientObject()->callFunction(); \
}

#define CALL_CLIENT_1ARGS( callFunction, arg ) \
{ \
  if (IsValid( ClientObject() ) ) \
  ClientObject()->callFunction(arg); \
}

#define CALL_CLIENT_2ARGS(callFunction, arg1, arg2) \
{ \
  if (IsValid( ClientObject() ) ) \
  ClientObject()->callFunction(arg1, arg2); \
}

#define CALL_CLIENT_3ARGS( callFunction, arg1, arg2, arg3 ) \
{ \
  if (IsValid( ClientObject() ) ) \
  ClientObject()->callFunction(arg1, arg2, arg3); \
}

#define CALL_CLIENT_5ARGS( callFunction, arg1, arg2, arg3, arg4, arg5 ) \
{ \
  if (IsValid( ClientObject() ) ) \
  ClientObject()->callFunction(arg1, arg2, arg3, arg4, arg5); \
}

#define CALL_CLIENT_6ARGS( callFunction, arg1, arg2, arg3, arg4, arg5, arg6 ) \
{ \
  if (IsValid( ClientObject() ) ) \
  ClientObject()->callFunction(arg1, arg2, arg3, arg4, arg5, arg6); \
}


namespace PF_Core
{
  _interface IWorld;

  class World;

  enum 
  { 
    INVALID_OBJECT_ID = -1,
    ADDED_THEN_REMOVED_OBJECT_ID = -2,
    WORLD_ID = -3,
    FORCE_CHEAT_ID = -4,
  };

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class WorldObjectBase : public CObjectBase
  {
    DONOT_REGISTER_SAVELOAD_CLASS
    OBJECT_METHODS( 0x1E76D400, WorldObjectBase );
  public:

    explicit WorldObjectBase(IWorld* pWorld, int _realWObj, bool immediately = false)
      : pWorld(pWorld)
      , objectId(INVALID_OBJECT_ID)
      , isDead(false)
      , isMapObject(false)
      , realWObj(_realWObj)
      , bWasReset(false)
    {
      if(pWorld)
        pWorld->RegisterObject(this, realWObj, immediately);
    }

    void SetMapObject( bool _isMapObject ) { isMapObject = _isMapObject; }
    bool IsMapObject() const { return isMapObject; }

    bool IsObjectDead()const
    {
      return isDead;
    }

    bool IsRealWorldObject() const
    {
      return realWObj != 0;
    }

    virtual int  GetObjectId() const {return objectId;}

    virtual bool Init(IClientObject* pClient)
    {
      pClientObject = pClient;
      return true; //@BVS@TODO Refactor -- to void
    }

    virtual bool Step(float /*dtInSeconds*/)
    {
      return true;
    }

    IWorld* GetWorld() const {return pWorld;}

    seDECLARE_COBJRING_CLASS(WorldObjectBase, ringPart, Ring);

    //const CObj<IClientObject>& GetClientObject() const { return pClientObject; }

    bool IsWorldObjWorldLinked()
    {
      return ringPart.isLinked();
    }

    NScene::SceneObject * GetClientSceneObject() {return IsValid(pClientObject)? pClientObject->GetSceneObject(): 0;}

    virtual void RemoveClientObject()
    {
      if ( IsValid(pClientObject) )
      {
        pClientObject->OnWorldObjectDie();
        pClientObject->Unsubscribe();
        pClientObject = 0;
      }
    }
  
    void DoReset()
    {
      if ( bWasReset )
        return;

      Reset();
      OnAfterReset();

      bWasReset = true;
    }
  
protected:
    virtual void Reset()
    {
      RemoveClientObject();
    }

    virtual void OnAfterReset() {}

    explicit WorldObjectBase()
      : pWorld(NULL)
      , objectId(INVALID_OBJECT_ID)
      , isDead(true)
      , isMapObject(false)
      , realWObj(0)
      , bWasReset(false)
    {
    }

    template <class T> 
    T* RetrieveClientObject() const
    {
      // @BVS@TODO HACKED!
      if (pClientObject.GetPtr() == 0)
        return 0;

      NI_ASSERT(dynamic_cast<T*>(pClientObject.GetPtr()), "A bug in client object type");
      return static_cast<T*>(pClientObject.GetPtr());
    }

    template <class T> 
    void CreateClientObject()
    {
      if (!isDead && pWorld->CanCreateClients())
        pClientObject = new T(WorldObjectRef(this));
    }

    template <class T, class PAR> 
    void CreateClientObject(const PAR &par)
    {
      if (!isDead && pWorld->CanCreateClients())
        pClientObject = new T(WorldObjectRef(this), par);
    }

    template <class T, class PAR1, class PAR2> 
    void CreateClientObject(const PAR1 &par1, const PAR2 &par2)
    {
      if (!isDead && pWorld->CanCreateClients())
        pClientObject = new T(WorldObjectRef(this), par1, par2);
    }

    template <class T, class PAR1, class PAR2, class PAR3> 
    void CreateClientObject(const PAR1 &par1, const PAR2 &par2, const PAR3 &par3)
    {
      if (!isDead && pWorld->CanCreateClients())
        pClientObject = new T(WorldObjectRef(this), par1, par2, par3);
    }

    virtual void OnDestroyContents() 
    {
      //DebugTrace("On OnDestroyContents for object %d, pointer %X", objectId, this);
      Unregister(true);
      RemoveClientObject();
    }
    virtual void OnDie() {}
    virtual bool NeedToSerialize() { return true; }
    virtual bool NeedToBeStepped() { return true; }

    //////////////////////////////////////////////////////////////////////////
    virtual void Die()
    {
      OnDie();
      Unregister(false);
      if ( IsValid(pClientObject) ) 
        pClientObject->OnWorldObjectDie();
      isDead = true;
    }

    //////////////////////////////////////////////////////////////////////////
    Ring::Part          ringPart; // Ring of objects to be stepped

    ZDATA
      ZNOPARENT(CObjectBase)
      ZONSERIALIZE
      CPtr<IWorld> pWorld;
    int          objectId;
    bool				 isDead;
    int          realWObj;
    bool         isMapObject;
  public:
    ZEND int operator&( IBinSaver &f ) { OnSerialize( f ); f.Add(2,&pWorld); f.Add(3,&objectId); f.Add(4,&isDead); f.Add(5,&realWObj); f.Add(6,&isMapObject); return 0; }
    enum { OBJECT_ID_CHUNK_NUM = 3 };

  private:
    CObj<IClientObject> pClientObject;

    bool         bWasReset;

    void Unregister(bool full)
    {
      if (IsValid(pWorld))
      {
        pWorld->UnregisterObject(this, full);
        //pWorld = NULL;
      }
    }

    void OnSerialize( IBinSaver&f )
    {
      if( !IsInvalidRef() && !f.IsReading() )
      {
        NI_ASSERT( objectId >= 0, NStr::StrFmt( "Object %s (dead = %s) has invalid id %d ", GetObjectTypeName(), isDead ? "true" : "false", objectId ) );
      }
    }

    friend World;
  };

  typedef CPtr<WorldObjectBase> WorldObjectRef;

} // namespace PF_Core 
