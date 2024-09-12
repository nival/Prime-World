#pragma once

#include "IUpdateable.h"

#define CLIENT_OBJECT_WORLD( className, worldClassName )                                    \
	public:																																										\
	const worldClassName* WorldObject() const { return RetrieveWorldObject<worldClassName>(); }     \
	static bool Initialize(className* pObject, worldClassName* pWorldObject) {return true;}   \
	private:

#define CLIENT_OBJECT_METHODS( N, className, worldClassName )                               \
	OBJECT_METHODS( N, className )                                                            \
	CLIENT_OBJECT_WORLD( className, worldClassName )

namespace NScene
{
	class SceneObject;
}

namespace Render
{
	class HDRColor;
}

namespace PF_Core
{
  class WorldObjectBase;
  class ColorModificationChannel;
	class BasicEffectAttached;
  enum  ColorModificationPriority;

  class PureClientObjectBase : public IUpdateable
  {
  protected:
    virtual void OnDestroyContents() { }

    virtual void Update( float timeDelta ) { }

    PureClientObjectBase() { }
  public:
    virtual PF_Core::ColorModificationChannel* CreateColorModificationChannel( PF_Core::ColorModificationPriority priority )
      { return NULL; }
    virtual void RemoveColorModificationChannel( PF_Core::ColorModificationChannel* pChannel ) { }

    virtual void OnEffectAttach( BasicEffectAttached* pEffect ) { }

    virtual void MultiplyTemporaryScale( float scale ) { }

    virtual void MultiplyAnimSpeed( float scale ) { }

    virtual NScene::SceneObject* GetSceneObject() const { return 0; }

    virtual void EnableById( string id, bool bEnable ) { }
    virtual void ProcessExternalEvent( const char* externalEvent ) { }
  };

  _interface IClientObject : public IUpdateable
  {   
		IClientObject() : IUpdateable() {}
		virtual void SetWorldObject(WorldObjectBase* pWorldObject) = 0;
    virtual void OnWorldObjectDie()                            = 0;
    virtual void OnBecameActive(bool /*bActive*/)              = 0; 
    
    //Moved from the ClientObjectBase. 
    // For effects! @BVS@TODO Subject for refactoring
    virtual NScene::SceneObject* GetSceneObject() const = 0;
  };
  
	class ClientObjectBase : public IClientObject
  {
    CPtr<WorldObjectBase> pWorldObject;

	protected:
    const CPtr<WorldObjectBase>& GetWorldObject() {return pWorldObject;}

		template <class T> 
		T* RetrieveWorldObject() const 
		{ 
			NI_ASSERT(dynamic_cast<T*>(pWorldObject.GetPtr()), "A bug in world object type");
			return static_cast<T*>(pWorldObject.GetPtr());
		}

		virtual void OnDestroyContents() {}
		virtual void SetWorldObject(WorldObjectBase* pObject) { pWorldObject = pObject; }
		virtual void OnWorldObjectDie() { Unsubscribe(); }

    virtual void OnBecameActive(bool /*bActive*/) {}

		// Inherited from NScene::IUpdateable
		virtual void Update(float /*timeDelta*/) {}
  public:
    explicit ClientObjectBase(){}
		ClientObjectBase(const CPtr<WorldObjectBase> &pWO) : pWorldObject(pWO) {}
    
    virtual PF_Core::ColorModificationChannel* CreateColorModificationChannel(PF_Core::ColorModificationPriority /*priority*/, bool fullRecolor = false ) { return NULL; }
    virtual void                               RemoveColorModificationChannel(PF_Core::ColorModificationChannel* /*pChannel*/) { }

    virtual void UpdateColor() {}

		virtual void OnEffectAttach(BasicEffectAttached * /*pEffect*/) {}
    
    virtual void MultiplyTemporaryScale( float /*scale*/ ) { }

    virtual void MultiplyAnimSpeed( float /*scale*/ ) { }

    virtual NScene::SceneObject* GetSceneObject() const { return 0; }

    virtual void EnableById( string id, bool bEnable ) { }
    virtual void ProcessExternalEvent( const char* externalEvent ) { }

    static bool Initialize(ClientObjectBase* pObject, WorldObjectBase* pWorldObject)
    {
      return true;
    }
  };
} // namespace PF_Core 
