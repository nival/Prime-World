#include "stdafx.h"

#include "MinigameClientObject.h"

#include "../Scene/CollisionGeometry.h"
#include "../Scene/CollisionHull.h"
#include "../Scene/GeometryBuilders.h"
#include "../Scene/SceneObject.h"
#include "../Scene/SceneObjectUtils.h"
#include "../Scene/SceneObjectCreation.h"
#include "../Scene/AnimatedSceneComponent.h"
#include "../PF_Core/BasicEffect.h"

#include "MinigameWorldObject.h"

namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MinigameClientObject::MinigameClientObject() :	
	sceneObject(NULL),
	collisionHull(0),
  tmpAABB( CVec3(0, 0, 0), CVec3(0, 0, 0) ),
  tmpAABBCenterOffset(0, 0, 0),
  tmpWorldMatrix( CVec3(0, 0, 0) ),
  commonSenseVisibility( true ), overridenVisibility( true ),
  overtips(NULL), overtipId(Overtips::InvalidId),
  scaleFactor( 1.f )
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MinigameClientObject::~MinigameClientObject()
{
	if ( IsValid( collisionHull ) && IsValid( scene ) )
	{
		scene->GetCollisionMap()->RemoveHull( collisionHull );
		collisionHull = 0;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigameClientObject::CreateSceneObject( const NDb::DBSceneObject* dbSceneObject )
{
  InitSceneObject( dbSceneObject, scene, sceneObject );
  PostInitSceneObject( Get( sceneObject ), scene, collisionHull, IsVisibleAfterAll() );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NScene::SceneObject* MinigameClientObject::Init( MinigameWorldObject* _worldObject, NScene::IScene* _scene, const NDb::DBSceneObject* _DBSceneObject, const Placement& _placement, bool collidable )
{
  SetWorldObject( _worldObject );
	scene = _scene;

	Placement finalPlacement = FixPlacement( _placement );

  CreateSceneObject( _DBSceneObject );

  tmpAABBCenterOffset = sceneObject->GetWorldAABB().center - sceneObject->GetPosition().pos;

	sceneObject->SetPlacement( finalPlacement );
  tmpAABB = sceneObject->GetWorldAABB();

	return Get( sceneObject );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigameClientObject::InitSceneObject( const NDb::DBSceneObject* _DBSceneObject, NScene::IScene* _scene, NScene::SceneObjectRef& _sceneObject )
{
  _sceneObject = NScene::SceneObjectsPool::Get()->Retrieve(_scene, _DBSceneObject, BADNODENAME);
  _sceneObject->SetPlacement(NULLPLACEMENT);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigameClientObject::PostInitSceneObject( NScene::SceneObject* _sceneObject, NScene::IScene* _scene, CPtr<NScene::CollisionHull>& _collisionHull, bool addToScene  )
{
  _sceneObject->UpdateForced();

  if ( addToScene )
    _sceneObject->AddToScene( _scene );

  NScene::CollisionMap* pCollMap = _scene->GetCollisionMap();
  if ( _sceneObject && pCollMap )
  {
    _sceneObject->UpdateForced();
    SBound bound;	
    _sceneObject->GetBound(bound);
    bound.s.ptCenter -= VNULL3;

    // Create collision hull
    vector<CVec3> pnts;
    vector<NScene::CollisionGeometry::Triangle> tris;
    NScene::CollisionGeometry* pCollisionGeometry = NScene::CreatePyramid( bound, 0.9f, true, pnts, tris );
    if( IsValid(pCollisionGeometry) )
      _collisionHull = pCollMap->CreateHull( _sceneObject, 0, pCollisionGeometry, IDENTITY_MATRIX, 0 );
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigameClientObject::SetPosition( const CVec3& _pos )
{
  Placement placement = sceneObject->GetPosition();
  placement.pos = _pos;
  sceneObject->SetPlacement( placement );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const CVec3& MinigameClientObject::GetPosition()
{
  return sceneObject->GetPosition().pos;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigameClientObject::SetPlacement( const Placement& _placement, bool doNotFixScale )
{
  sceneObject->SetPlacement( doNotFixScale ? _placement : FixPlacement( _placement ) );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Placement& MinigameClientObject::GetPlacement()
{
	return sceneObject->GetPosition();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Render::AABB & MinigameClientObject::GetWorldAABB() const
{
  tmpAABB.center = sceneObject->GetPosition().pos + tmpAABBCenterOffset;
  return tmpAABB;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float MinigameClientObject::GetSize() const
{
  return tmpAABB.halfSize.Length() * 2.0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const SHMatrix & MinigameClientObject::GetWorldMatrix() const
{
  //TODO: iA: Optimize
  tmpWorldMatrix.Set(sceneObject->GetPosition().pos, sceneObject->GetPosition().rot);
	return tmpWorldMatrix;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigameClientObject::SetMulColor( const Render::HDRColor & _mul )
{
	NScene::ModifySceneObjectColors( *sceneObject, _mul, Render::HDRColor() );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigameClientObject::SetOpacity(float _opacity)
{
  NScene::ModifySceneObjectOpacity(*sceneObject,_opacity);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigameClientObject::SetComponentMulColor(const nstl::string &_componentID, const Render::HDRColor & _mul)
{
  NScene::ModifySceneComponentColors(*sceneObject,_componentID, _mul, Render::HDRColor() );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MinigameClientObject::SetComponentAddColor(const nstl::string &_componentID, const Render::HDRColor & _add)
{
  NScene::ModifySceneComponentColors(*sceneObject,_componentID, Render::HDRColor(), _add );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigameClientObject::SetComponentAddMulColor( const string & _componentID, const Render::HDRColor & _add, const Render::HDRColor & _mul )
{
  NScene::ModifySceneComponentColors(*sceneObject, _componentID, _mul, _add );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigameClientObject::EnableComponent( const char * _componentID, bool _enable )
{
  if ( !sceneObject )
    return;

  //// setting traverser
  struct Func : public NScene::TraverserById
  {
    bool fEnable;
    Func(const char *id,bool _enable) : TraverserById(id), fEnable(_enable) {};
    void operator()(NScene::SceneComponent *pSC)
    {
      pSC->EnableWeak(fEnable);
    }
  } func( _componentID, _enable );

  // applying traverser
  sceneObject->Traverse(func);

  // Irakly <neko.lich> Archangelsky:workaround aabb recalculation problem
  sceneObject->SetPlacement(GetPlacement());
  if(sceneObject->GetScene() != 0)
    sceneObject->MarkAsVisible();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigameClientObject::HideComponent( const char * _componentID, bool _hide )
{
  if ( !sceneObject )
    return;

  //// setting traverser
  struct Func : public NScene::TraverserById
  {
    bool hide;
    Func( const char *id, bool _hide ) : TraverserById(id), hide(_hide) {};
    void operator()(NScene::SceneComponent *pSC)
    {
      pSC->SetHide( hide );
    }
  } func( _componentID, _hide );

  // applying traverser
  sceneObject->Traverse(func);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigameClientObject::SetComponentPosition( const char * _componentID, const CVec3& _pos )
{
  if ( !sceneObject )
    return;

  struct Func : public NScene::TraverserById
  {
    const CVec3& pos;

    Func(const char *id, const CVec3& _pos ) : TraverserById(id), pos(_pos) {};

    void operator()(NScene::SceneComponent *pSC)
    {
      Placement placement = pSC->GetPlacement();
      placement.pos = pos;
      pSC->SetPlacement( placement );
    }

  } func( _componentID, _pos );

  sceneObject->Traverse( func );

  // Irakly <neko.lich> Archangelsky: workaround aabb recalculation problem
  sceneObject->SetPlacement(GetPlacement());
  if(sceneObject->GetScene() != 0)
    sceneObject->MarkAsVisible();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigameClientObject::PlayAnimation(const nstl::string& _name,bool _fCyclic)
{
  //
  // UNDONE !!! реализовать ....
  //
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigameClientObject::SetVisible( NScene::IScene* _scene, NScene::SceneObject* _sceneObject, bool _visible )
{
  if ( !_sceneObject )
    return;

  if ( _visible )
  {
    if ( !IsValid( _sceneObject->GetScene() ) )
      _sceneObject->AddToScene( _scene );
  }
  else
    _sceneObject->RemoveFromScene();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigameClientObject::SetVisible( bool _visible )
{
  commonSenseVisibility = _visible;
  SetVisible( scene, Get( sceneObject ), IsVisibleAfterAll() );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigameClientObject::OverrideVisible( bool _visible )
{
  overridenVisibility = _visible;
  SetVisible( scene, Get( sceneObject ), IsVisibleAfterAll() );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MinigameClientObject::IsVisible() 
{ 
	return IsValid( sceneObject->GetScene() );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigameClientObject::MoveSceneObject( const Placement& _placement, NScene::SceneObject* _sceneObject, NScene::CollisionHull* _collisionHull )
{
  _sceneObject->SetPlacement( _placement );

  // Update collision hull
  if ( IsValid( _collisionHull ) )
  {
    Matrix43 matrix;
    _placement.GetMatrix( &matrix );
    _collisionHull->SetPosition( matrix, 0 );
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigameClientObject::OnMouseEnter()
{
  CPtr<MinigameWorldObject> worldObject = GetWorldObject();

  if ( !IsValid( worldObject ) )
    return;

  if ( NeedHighlight() )// EClinicGameMode::Shop != worldObject->GetClinic()->GetGameMode())
  {
    SetMulColor( GetHighlightColor() );
  }

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigameClientObject::OnMouseLeave()
{
  CPtr<MinigameWorldObject> worldObject = GetWorldObject();

  if ( !IsValid( worldObject ) )
    return;

  if ( NeedHighlight() )
  {
    SetMulColor( Render::HDRColor(1.f, 1.f, 1.f, 1.f) );
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Render::HDRColor& MinigameClientObject::GetHighlightColor() const
{
  static Render::HDRColor defaultColor(1.f, 1.f, 1.f, 1.f);
  return defaultColor;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigameClientObject::Step( float deltaTime )
{
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigameClientObject::Update( float deltaTime, bool gameOnPause )
{
  if ( IsValid( worldObject ) )
    MoveSceneObject( FixPlacement( worldObject->GetPlacement() ), Get( sceneObject ), collisionHull );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigameClientObject::CreateOvertip(Overtips::IManager * pOvertips, const NDb::UIObjectOvertips * pDesc)
{
  if(!pDesc)
    return;

  NI_ASSERT(pOvertips, "");

  if(overtipId != Overtips::InvalidId && IsValid(overtips))
    overtips->RemoveOvertip(overtipId);
  overtipId = Overtips::InvalidId;

  overtips = pOvertips;
  overtips->CreateOvertip(pDesc, this);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigameClientObject::RemoveOvertip()
{
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MinigameClientObject::AttachEffect(const CObj<PF_Core::BasicEffectAttached>& effect)
{
  NI_VERIFY(IsValid(effect), "MinigameClientObject: effect attach failed. Effect is invalid", return);
  NI_VERIFY(sceneObject, "MinigameClientObject: effect attach failed. Scene object is invalid", return);

  effect->Attach(Get(sceneObject));
}

} // namespace PF_Minigames

BASIC_REGISTER_CLASS(PF_Minigames::MinigameClientObject)
