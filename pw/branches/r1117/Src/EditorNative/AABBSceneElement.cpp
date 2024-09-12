#include "stdafx.h"
#include "AABBSceneElement.h"
#include "SimpleEditorScene.h"

using namespace nstl;
using namespace System;
using namespace libdb::DB;
using namespace EditorNative;
using namespace EditorNative::SceneElements::SceneObjects;

#pragma managed(push, off)
static Render::AABB* GetAABB( NScene::ParticleSceneComponent* psc )
{
  Render::AABB* localAABB = new Render::AABB();
  *localAABB = psc->GetLocalAABB();
  psc->GetParticleAABB( *localAABB );
  return localAABB;
}

static void SetNativeAABB( const Placement* placement, Render::AABB* nativeAABB, const NDb::AABB& aabb )
{
  // Make matrix
  Matrix43 matrix;
  Placement place( *placement );
  place.pos.Set( 0.f, 0.f, 0.f );
  place.scale.Set( 1.f, 1.f, 1.f );
  place.GetMatrix( &matrix );

  Render::AABB newAabb;
  newAabb.Set(aabb);

  // Update world AABB & grow object AABB
  newAabb.Transform(matrix, newAabb);

  nativeAABB->Assign( newAabb.center, newAabb.halfSize );
}
#pragma managed(pop)

static bool IsValid( DBTypes::AABB^ aabb )
{
  if ( aabb->maxX < aabb->minX 
    || aabb->maxY < aabb->minY 
    || aabb->maxZ < aabb->minZ)
  {
    return false;
  }
  return true;
}

AABBSceneElement::AABBSceneElement(EditorSceneComponent^ sc, libdb::UndoRedo::UndoRedoManager^ manager) 
: sceneComponent(sc)
, undoManager( manager )
{
  placement = new Placement(NULLPLACEMENT);
  placementToDraw = new Placement(NULLPLACEMENT);
  offset = new Placement(NULLPLACEMENT);
  nativeAABB = new Render::AABB();
  nativeAABBtoDraw = new Render::AABB();

  if ( sceneComponent != nullptr )
  {
    *offset = sc->sceneComponent->GetWorldPlacement();
		offset->rot = QNULL;
    const NDb::DBID& dbid = sceneComponent->sceneComponent->GetDBID();

    const Render::AABB& localAABB = sceneComponent->sceneComponent->GetLocalAABB();
    *placement = ConvertFromOffsetToWorld( *offset, Placement( localAABB.center, QNULL, 
      CVec3( localAABB.halfSize*2.0f ) ) );

    NScene::AnimatedSceneComponent* asc = dynamic_cast<NScene::AnimatedSceneComponent*>( sceneComponent->sceneComponent );
    if ( asc )
    {
      libdb::DB::DBPtr<DBTypes::DBAnimatedSceneComponent^>^ db = libdb::DB::DataBase::Get<DBTypes::DBAnimatedSceneComponent^>( libdb::DB::DBID::FromString( FromMBCS( NDb::GetFormattedDbId( dbid ) ) ) );
      if ( IsValid(db->Get()->aabb) )
      {
        InitPlacement( db->Get()->aabb );
      }
    }
    NScene::ParticleSceneComponent* psc = dynamic_cast<NScene::ParticleSceneComponent*>( sceneComponent->sceneComponent );
    if ( psc )
    {
      libdb::DB::DBPtr<DBTypes::DBParticleSceneComponent^>^ db = libdb::DB::DataBase::Get<DBTypes::DBParticleSceneComponent^>( libdb::DB::DBID::FromString( FromMBCS( NDb::GetFormattedDbId( dbid ) ) ) );
      if ( IsValid(db->Get()->aabb) )
      {
        InitPlacement( db->Get()->aabb );
      }
      else
      {
        *placement = ConvertFromOffsetToWorld( *offset, Placement( GetAABB(psc)->center, QNULL, 
          CVec3( GetAABB(psc)->halfSize*2.0f ) ) );
      }
    }
    NScene::StaticSceneComponent* ssc = dynamic_cast<NScene::StaticSceneComponent*>( sceneComponent->sceneComponent );
    if ( ssc )
    {
      libdb::DB::DBPtr<DBTypes::DBStaticSceneComponent^>^ db = libdb::DB::DataBase::Get<DBTypes::DBStaticSceneComponent^>( libdb::DB::DBID::FromString( FromMBCS( NDb::GetFormattedDbId( dbid ) ) ) );
      if ( IsValid(db->Get()->aabb) )
      {
        InitPlacement( db->Get()->aabb );
      }
    }
  }
  *placementToDraw = *placement;
}


void AABBSceneElement::Draw( NScene::IScene& scene )
{
  if ( sceneComponent != nullptr )
  {
    *placementToDraw = ConvertFromWorldToOffset( *offset, *placement );
    *offset = sceneComponent->sceneComponent->GetWorldPlacement();
    *placementToDraw = ConvertFromOffsetToWorld( *offset, *placementToDraw );

    Render::Color redColor( 255, 0, 0 );
    NDb::AABB aabb;
    aabb.maxX = placementToDraw->pos.x + placementToDraw->scale.x - (placementToDraw->scale.x/2.0f);
    aabb.minX = aabb.maxX - placementToDraw->scale.x;
    aabb.maxY = placementToDraw->pos.y + placementToDraw->scale.y - (placementToDraw->scale.y/2.0f);
    aabb.minY = aabb.maxY - placementToDraw->scale.y;
    aabb.maxZ = placementToDraw->pos.z + placementToDraw->scale.z - (placementToDraw->scale.z/2.0f);
    aabb.minZ = aabb.maxZ - placementToDraw->scale.z;

    SetNativeAABB( offset, nativeAABB, aabb );

    //Placement temppl = *offset;
    //temppl.scale = CVec3(1.0f,1.0f,1.0f);
    //temppl.pos = CVec3(0.0f,0.0f,0.0f);
    //Matrix43 transformAABB;
    //temppl.GetMatrix(&transformAABB);
    //nativeAABBtoDraw->Transform( transformAABB, *nativeAABB );

    Render::DebugRenderer::DrawAABB( *nativeAABB, redColor, true );
    
    *placementToDraw = *placement;
  }
}

const Placement& AABBSceneElement::GetPlacement()
{
  return *placement;
}

void AABBSceneElement::SetPlacement( const Placement& _placement )
{
  *placement = _placement;
}

void AABBSceneElement::SetPlacementRot(  float x, float y, float z, float w  )
{
  (*placement).rot.x = x;
  (*placement).rot.y = y;
  (*placement).rot.z = z;
  (*placement).rot.w = w;
}

void AABBSceneElement::Apply( bool isMoved, bool isRotated, bool isScaled )
{
  if ( !isMoved && !isRotated && !isScaled )
    return;
  if ( sceneComponent != nullptr )
  {
    const NDb::DBID& dbid = sceneComponent->sceneComponent->GetDBID();
    NScene::AnimatedSceneComponent* asc = dynamic_cast<NScene::AnimatedSceneComponent*>( sceneComponent->sceneComponent );
    if ( asc )
    {
      libdb::DB::DBPtr<DBTypes::DBAnimatedSceneComponent^>^ db = libdb::DB::DataBase::Get<DBTypes::DBAnimatedSceneComponent^>( libdb::DB::DBID::FromString( FromMBCS( NDb::GetFormattedDbId( dbid ) ) ) );
      undoManager->Start( "Change AABB" );
      DBTypes::AABB^ aabb = gcnew DBTypes::AABB(db->Get()->aabb->GetOwner());
      FillAABB( aabb );
      db->Get()->aabb = aabb;
      undoManager->Commit();
    }
    NScene::ParticleSceneComponent* psc = dynamic_cast<NScene::ParticleSceneComponent*>( sceneComponent->sceneComponent );
    if ( psc )
    {
      libdb::DB::DBPtr<DBTypes::DBParticleSceneComponent^>^ db = libdb::DB::DataBase::Get<DBTypes::DBParticleSceneComponent^>( libdb::DB::DBID::FromString( FromMBCS( NDb::GetFormattedDbId( dbid ) ) ) );
      undoManager->Start( "Change AABB" );
      DBTypes::AABB^ aabb = gcnew DBTypes::AABB(db->Get()->aabb->GetOwner());
      FillAABB( aabb );
      db->Get()->aabb = aabb;
      undoManager->Commit();
    }
    NScene::StaticSceneComponent* ssc = dynamic_cast<NScene::StaticSceneComponent*>( sceneComponent->sceneComponent );
    if ( ssc )
    {
      libdb::DB::DBPtr<DBTypes::DBStaticSceneComponent^>^ db = libdb::DB::DataBase::Get<DBTypes::DBStaticSceneComponent^>( libdb::DB::DBID::FromString( FromMBCS( NDb::GetFormattedDbId( dbid ) ) ) );
      undoManager->Start( "Change AABB" );
      DBTypes::AABB^ aabb = gcnew DBTypes::AABB(db->Get()->aabb->GetOwner());
      FillAABB( aabb );
      db->Get()->aabb = aabb;
      undoManager->Commit();
    }
  }
}

void AABBSceneElement::InitPlacement( DBTypes::AABB^ aabb )
{
  *placement = ConvertFromOffsetToWorld( *offset,
    Placement( CVec3((aabb->maxX + aabb->minX)/2.0f, 
    (aabb->maxY + aabb->minY)/2.0f, 
    (aabb->maxZ + aabb->minZ)/2.0f ), 
    QNULL, 
    CVec3(aabb->maxX - aabb->minX, 
    aabb->maxY - aabb->minY, 
    aabb->maxZ - aabb->minZ ) ) );
}

void AABBSceneElement::FillAABB( DBTypes::AABB^ aabb )
{
  *placement = ConvertFromWorldToOffset( *offset, *placement );
  aabb->maxX = placement->pos.x + placement->scale.x - (placement->scale.x/2.0f);
  aabb->minX = aabb->maxX - placement->scale.x;
  aabb->maxY = placement->pos.y + placement->scale.y - (placement->scale.y/2.0f);
  aabb->minY = aabb->maxY - placement->scale.y;
  aabb->maxZ = placement->pos.z + placement->scale.z - (placement->scale.z/2.0f);
  aabb->minZ = aabb->maxZ - placement->scale.z;
}