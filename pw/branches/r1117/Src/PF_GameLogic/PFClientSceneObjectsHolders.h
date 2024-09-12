#pragma once

#include "PFClientLogicObject.h"
#include "../Scene/AnimatedSceneComponent.h"

#include "DBUnit.h"

namespace NGameX
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ISceneObjectsHolder
{
public:
  virtual ~ISceneObjectsHolder() {}
  virtual void SetActive(int index, bool visible) = 0; // 'visible' used in MSO for change SO forced if under fog of war.
  virtual NScene::SceneObjectRef& GetActive() = 0;
  virtual void Enable(bool bEnable = true, bool forced = true) = 0; // 'forced' used in MSO for change scene object without transaction
  virtual void SetVisibility(bool bEnable = true) = 0;
  virtual void Reset() = 0;
  virtual void Update(float dt) = 0;
  virtual NScene::SceneObjectRef& Get(int index) = 0;
  virtual void SetUpdatePriority(NScene::UpdatePriority priority) = 0;
	virtual void Recreate( const Placement& place, const nstl::string& nodeName ) = 0;
  virtual void SetSceneObject( const NDb::DBSceneObject* sceneObjectDesc ) {}
  virtual const NDb::CollisionGeometry* GetCollision() const = 0;
	virtual const NDb::DBSceneObject* GetDBObject() const = 0;
	virtual const nstl::string& GetNodeName() const 
	{ 
		static const nstl::string nodeName = BADNODENAME;
		return nodeName; 
	}
  
  virtual void DropTree( const CVec2& direction, const NDb::Ptr<NDb::TreeObject>& pDBDesc ) { };
  virtual bool NeedUpdateTransactions() const { return false; }

  virtual int GetCount() const = 0;

  template <class F>
  void ForEach(F f)
  {
    for (int i = 0, count = GetCount(); i < count; ++i)
    {
      if (NScene::SceneObjectRef& so = Get(i))
        f(so);
    }
  }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SingleSceneObjectHolder : public ISceneObjectsHolder
{
public:
	SingleSceneObjectHolder( NScene::IScene* pScene, int _worldObjectId, const Placement& place, NDb::Ptr<NDb::DBSceneObject> const& _dbObject, const NDb::Ptr<NDb::CollisionGeometry>& _dbCol, const nstl::string& nodeName );
  
  virtual NScene::SceneObjectRef& GetActive() { return sceneObject; }
  virtual void Enable(bool bEnable, bool forced = true);
  virtual void SetVisibility(bool bEnable = true);
  virtual void SetActive(int index, bool visible) { NI_ALWAYS_ASSERT("SetActive not implemented for SingleSceneObjectHolder!"); }
  virtual void Reset();
  virtual void Update(float dt) {}
  virtual NScene::SceneObjectRef& Get(int index) { return sceneObject; }
  virtual void SetUpdatePriority(NScene::UpdatePriority priority);
  virtual void Recreate( const Placement& place, const nstl::string& nodeName );
  virtual void SetSceneObject( const NDb::DBSceneObject* sceneObjectDesc );
	virtual const NDb::CollisionGeometry* GetCollision() const;
	virtual const NDb::DBSceneObject* GetDBObject() const;
	virtual const nstl::string& GetNodeName() const { return nodeName; }
  virtual int GetCount() const { return 1; }
protected:
  NScene::IScene*         pScene;
  bool                    enabled;
  bool                    visible;
  NScene::UpdatePriority  updatePriority;
  NScene::SceneObjectRef  sceneObject;
  NDb::Ptr<NDb::DBSceneObject> dbObject;
  NDb::Ptr<NDb::CollisionGeometry> dbCollision;
  int worldObjectId;
	nstl::string nodeName;
private:
	SingleSceneObjectHolder& operator=(const SingleSceneObjectHolder&)
	{
		return *this;
	}
};

} //namespace NGameX
