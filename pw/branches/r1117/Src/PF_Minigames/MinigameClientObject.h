#pragma once

#include "../Render/aabb.h"
#include "../Client/Overtips.h"
#include "../Scene/SceneObject.h"

namespace NScene
{
	_interface IScene;
	class SceneObject;
	class CollisionHull;
}

namespace NDb
{
	struct DBSceneObject;
}

namespace PF_Core
{
  class BasicEffectAttached;
}

namespace PF_Minigames
{

class MinigameWorldObject;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class MinigameClientObject : public Overtips::ITarget, public CObjectBase
{
	OBJECT_BASIC_METHODS( MinigameClientObject )

public:
	MinigameClientObject();
	virtual ~MinigameClientObject();
	
	virtual NScene::SceneObject* Init( MinigameWorldObject* _worldObject, NScene::IScene* _scene, const NDb::DBSceneObject* _DBSceneObject, const Placement& _placement, bool collidable );

  virtual void OnLevelStarted() {}
  virtual void OnLevelFinished() {}

  void SetWorldObject( MinigameWorldObject* _worldObject ) { worldObject = _worldObject; }
  MinigameWorldObject* GetWorldObject() { return worldObject; }

	void SetPosition( const CVec3& _pos );
	const CVec3& GetPosition();

  void SetPlacement( const Placement& _placement, bool doNotFixScale = false );
  const Placement& GetPlacement();

  const Render::AABB & GetWorldAABB() const;
	float GetSize() const;
  const SHMatrix & GetWorldMatrix() const;

  void SetMulColor( const Render::HDRColor & _mul );
  void SetOpacity(float _opacity);

  // @Pavel<GnoM>Cherniavski@TODO  has to be moved somewhere else
  
  void SetComponentMulColor(const nstl::string &_componentID, const Render::HDRColor & _mul);
  void SetComponentAddColor(const nstl::string &_componentID, const Render::HDRColor & _add);
  void SetComponentAddMulColor( const string & _componentID, const Render::HDRColor & _add, const Render::HDRColor & _mul );

  void EnableComponent( const char * _componentID, bool _enable );
  void HideComponent( const char * _componentID, bool _hide );
  void SetComponentPosition( const char * _componentID, const CVec3& _pos );

  void PlayAnimation(const nstl::string& _name,bool _fCyclic);

  bool IsVisibleAfterAll() const { return overridenVisibility && commonSenseVisibility; }

  //////////////////////////////////////////////////////////////////////////

  virtual void SetVisible( bool _visible );
  virtual void OverrideVisible( bool _visible ); //FXIME: Подпорка чото бы например спрятать всю миниигру, не конфликтуая с SetVisible()
	virtual bool IsVisible();

  virtual void Update( float deltaTime, bool gameOnPause );
  virtual void Step( float deltaTime );

  virtual MinigameClientObject * RedirectMouseOver() { return this; }
  virtual void OnMouseEnter();
  virtual void OnMouseLeave();

  virtual bool NeedHighlight() const { return false; }
  virtual const Render::HDRColor& GetHighlightColor() const;

  //FIXME: нужен ли этот функционал для всех миниигр или только для клиники?
  //TODO: iA: move these to Clinic-specific client object
  void CreateOvertip( Overtips::IManager * pOvertips, const NDb::UIObjectOvertips * pDesc );
  void RemoveOvertip();

  void AttachEffect(const CObj<PF_Core::BasicEffectAttached>& effect);

  NScene::SceneObject * GetSceneObject() { return Get( sceneObject ); }

protected:
  //Overtips::ITarget
  virtual bool IsOvertipVisible() const { return true; }
  virtual void SetupOvertipLayout(UI::Window * pWindow, const Overtips::SOvertipId & overtipId) {}
  virtual void UpdateOvertipLayout(UI::Window * pWindow, const Overtips::SOvertipId & overtipId) {}
  virtual const Render::AABB & GetOvertipAabb() const { return GetWorldAABB(); }
  virtual const SHMatrix & GetOvertipWorldPosition() const { return GetWorldMatrix(); }
  virtual void OnOvertipRemoval() {}

  virtual void CreateSceneObject( const NDb::DBSceneObject* dbSceneObject );

  static void InitSceneObject( const NDb::DBSceneObject* _DBSceneObject, NScene::IScene* _scene, NScene::SceneObjectRef& _sceneObject );
  static void PostInitSceneObject( NScene::SceneObject* _sceneObject, NScene::IScene* _scene, CPtr<NScene::CollisionHull>& _collisionHull, bool addToScene );
  static void MoveSceneObject( const Placement& _placement, NScene::SceneObject* _sceneObject, NScene::CollisionHull* _collisionHull );
  static void SetVisible( NScene::IScene* _scene, NScene::SceneObject* _sceneObject, bool _visible );

  void SetScaleFactor( float s ) { scaleFactor = s; }
  float GetScaleFactor() const { return scaleFactor; }

  inline Placement FixPlacement( const Placement & p ) const { Placement tmp( p ); tmp.scale *= scaleFactor; return tmp; }

	NScene::SceneObjectRef sceneObject;
	CPtr<NScene::IScene> scene;

	CPtr<NScene::CollisionHull> collisionHull;

  //TODO: проблема в том, что  мы не можем вернуть AABB от scene obejct, так как он "гуляет" вместе с анимацией
  //И за этой же анимацией начинают "гулять" и овертипы над объектом
  //Поэтому приходится конструировать какой-то свой бокс с фиксированным размером
  //Так как при этом все методы Get - константные, отсюда и mutable
	mutable Render::AABB tmpAABB;
  CVec3 tmpAABBCenterOffset;
  mutable SHMatrix tmpWorldMatrix;
  CPtr<MinigameWorldObject> worldObject;

  bool commonSenseVisibility;
  bool overridenVisibility;

  //FIXME: переместить этот код, а так же CreateOvertip() в некий объект ClinicClientObject
  //TODO: iA: move these to Clinic-specific client object
  template <class TUIElem>
  void CheckControlOut(Weak<TUIElem> * pControlPtr, UI::Window * pParent, const char * controlName)
  {
    TUIElem * pCtrl = UI::GetChildChecked<TUIElem>(pParent, controlName, true);
    if(pCtrl)
      *pControlPtr = pCtrl;
  }

private:
  Weak<Overtips::IManager> overtips;
  int overtipId;

  float scaleFactor;
};

} // namespace PF_Minigames

