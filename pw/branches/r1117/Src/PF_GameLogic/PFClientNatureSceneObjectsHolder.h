#pragma once
#include "PFClientSceneObjectsHolders.h"


namespace NGameX
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Nature Scene Objects Holder with Nature Transactions
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class NatureTransaction;

//////////////////////////////////////////////////////////////////////////
class NatureSceneObjectsHolder
  : public ISceneObjectsHolder
  , public NonCopyable
{
  static void InitInstance(NatureSceneObjectsHolder* const instance, const NDb::MultiStateObject* const mso);
public:
  static NatureSceneObjectsHolder* Create(NScene::IScene* const pScene, NScene::ISceneObjectUpdateHook* const pHook, const Placement& place, const int worldObjectId, const NDb::MultiStateObject* const mso);
  static NatureSceneObjectsHolder* CreateWithTreeStubs(NScene::IScene* const pScene, NScene::ISceneObjectUpdateHook* const pHook, const Placement& place, const int worldObjectId, const NDb::TreeObject* const mso);

  virtual ~NatureSceneObjectsHolder();

  virtual void SetActive(int index, bool visible /*= true*/);

  // unsafe!
  virtual NScene::SceneObjectRef& GetActive()
  {
    return entries[activeObjectInternal].sceneObject;
  }

  virtual void Enable(bool bEnable = true, bool forced = true);
  virtual void SetVisibility(bool bEnable = true) { Enable(bEnable); }
  virtual void Reset();
  virtual void Update(float dt);
  
  virtual void DropTree( const CVec2& direction, const NDb::Ptr<NDb::TreeObject>& pDBDesc );
  virtual bool NeedUpdateTransactions() const;
  
  virtual NScene::SceneObjectRef& Get(int index)
  {
    NI_VERIFY( index >= 0, "Wrong index!", return GetDummySceneObject() );
    NI_VERIFY( index < GetCount(), "Wrong index!", return GetDummySceneObject() );

    return GetSceneObject(index);
  }

  virtual void SetUpdatePriority(NScene::UpdatePriority priority) {}
  virtual void Recreate( const Placement& place, const nstl::string& nodeName ) {};
	virtual const NDb::CollisionGeometry* GetCollision() const { return 0; }
	virtual const NDb::DBSceneObject* GetDBObject() const { return 0; }

  virtual int GetCount() const { return entries.capacity(); }
private:
  NatureSceneObjectsHolder(NScene::IScene* const pScene, const bool distinct, const float fadeInOffset, const float dropTime);

  NatureSceneObjectsHolder(); // absent

  NDb::Ptr<NDb::EffectBase> const& GetTransEffect( int natureIndex, bool fadeInEffect );
  float GetTransFadeInTime() const;
  float GetTransFadeOutTime() const;

  NScene::SceneObjectRef& GetDummySceneObject()
  {
    static NScene::SceneObjectRef l_dummy;
    return l_dummy;
  }

  NScene::SceneObjectRef& GetSceneObject(const int index)
  {
    return entries[index].sceneObject;
  }

  void InternalSelectActiveObject();

  enum
  {
    // один набор для "дневных" объектов + один набор для "ночных"
    // NOTE: значение должно быть больше 0
    SceneObjectCount = NDb::KnownEnum<NDb::ENatureType>::sizeOf * 2,
  };

  struct Entry
  {
    NDb::Ptr<NDb::EffectBase> dbEffectIn;
    NDb::Ptr<NDb::EffectBase> dbEffectOut;

    NScene::SceneObjectRef sceneObject;

    Entry()
      : dbEffectIn()
      , dbEffectOut()
      , sceneObject()
    {
    }
  };

  typedef StaticArray< Entry, SceneObjectCount > Entries;

  NScene::IScene* const pScene;

  const bool      distinct;
  const float     fadeInOffset;
  const float     dropTime;

  bool            enabled;

  AutoPtr<NatureTransaction> fadeInTrans;
  AutoPtr<NatureTransaction> fadeOutTrans;

  Entries         entries;
  int             activeObject;

  int             activeObjectInternal;
};

} //namespace NGameX