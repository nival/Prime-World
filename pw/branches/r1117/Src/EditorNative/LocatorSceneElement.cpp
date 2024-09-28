#include "stdafx.h"
#include "LocatorSceneElement.h"
#include "SimpleEditorScene.h"

using namespace nstl;
using namespace System;
using namespace libdb::DB;
using namespace EditorNative;
using namespace EditorNative::SceneElements::SceneObjects;

static Placement ConvertFromWorldToOffset( NScene::Locator* locator, const Placement& worldPlacement )
{
  Placement attachedPlacement;
  Matrix43 attachedMatrix;

  Matrix43 worldMatrix;

  Placement localPlacement;
  Matrix43 localMatrix;

  locator->MakeAttachementPlacement( attachedPlacement );
  worldPlacement.GetMatrix( &worldMatrix );
  attachedPlacement.GetMatrix( &attachedMatrix );

  localMatrix = attachedMatrix.GetInversed() * worldMatrix;
  localPlacement.FromMatrix( localMatrix );

  return localPlacement;
}

static Placement ConvertFromOffsetToWorld( NScene::Locator* locator, const Placement& offsetPlacement )
{
  Placement attachedPlacement;
  Matrix43 attachedMatrix;

  Matrix43 offsetMatrix;

  Placement worldPlacement;
  Matrix43 worldMatrix;

  locator->MakeAttachementPlacement( attachedPlacement );
  offsetPlacement.GetMatrix( &offsetMatrix );
  attachedPlacement.GetMatrix( &attachedMatrix );

  worldMatrix = attachedMatrix * offsetMatrix;
  worldPlacement.FromMatrix( worldMatrix );

  return worldPlacement;
}

LocatorSceneElement::LocatorSceneElement(EditorSceneComponent^ sc, libdb::UndoRedo::UndoRedoManager^ manager, System::String^ _locator ) 
: sceneComponent(sc)
, undoManager( manager )
{
  placement = new Placement(NULLPLACEMENT);
  locatorName = new nstl::string();
  worldMatrix = new Matrix43();
  locator = 0;

  if ( sceneComponent != nullptr )
  {
    *locatorName = ToMBCS(_locator);

    NScene::Locator const* soLocator = sceneComponent->sceneObject->Object->FindLocator(locatorName->c_str());
    if ( soLocator )
    {
      locator = new NScene::Locator();
      *locator = *soLocator;
      *placement = ConvertFromOffsetToWorld( locator, 
        Placement( soLocator->locator.offset2.GetPlace().pos, 
        soLocator->locator.offset2.GetPlace().rot, 
        soLocator->locator.offset2.GetPlace().scale ) );
    }
  }
}


void LocatorSceneElement::Draw( NScene::IScene& scene )
{
  if ( sceneComponent != nullptr && locator )
  {
    placement->GetMatrix( worldMatrix );
    Render::DebugRenderer::DrawCross3D( *worldMatrix, 1.f, 1.f, Render::Color( 51, 255, 153 ), true );
  }
}

const Placement& LocatorSceneElement::GetPlacement()
{
  return *placement;
}

void LocatorSceneElement::SetPlacement( const Placement& _placement )
{
  *placement = _placement;
}

void LocatorSceneElement::Apply( bool isMoved, bool isRotated, bool isScaled )
{
  if ( !isMoved && !isRotated && !isScaled )
    return;
  if ( sceneComponent != nullptr && locator )
  {
    const NDb::DBID& dbid = locator->pSC->GetDBID();
    libdb::DB::DBPtr<DBTypes::DBSceneComponent^>^ db = libdb::DB::DataBase::Get<DBTypes::DBSceneComponent^>( libdb::DB::DBID::FromString( FromMBCS( NDb::GetFormattedDbId( dbid ) ) ) );
    if ( db->Get()->locatorList->IsValid )
    {
      libdb::IChangeableList<DBTypes::Locator ^> ^locators = db->Get()->locatorList->Get()->locators;
      undoManager->Start( "Change Locator" );
      for ( int i = 0; i < locators->Count; i++ )
      {
        if ( locators[i]->name == FromMBCS( *locatorName ) )
        {
          Placement realpos = ConvertFromWorldToOffset( locator, *placement );

          if ( isMoved )
          {
            locators[i]->offset2->translateX = realpos.pos.x;
            locators[i]->offset2->translateY = realpos.pos.y;
            locators[i]->offset2->translateZ = realpos.pos.z;
          }

          if ( isRotated )
          {
            CVec3 rotation;
            realpos.rot.DecompEulerAngles( &rotation.z, &rotation.y, &rotation.x );
            locators[i]->offset2->rotationX = ToDegree(rotation.x);
            locators[i]->offset2->rotationY = ToDegree(rotation.y);
            locators[i]->offset2->rotationZ = ToDegree(rotation.z);
          }

          if ( isScaled )
          {
            locators[i]->offset2->scaleX = realpos.scale.x;
            locators[i]->offset2->scaleY = realpos.scale.y;
            locators[i]->offset2->scaleZ = realpos.scale.z;
          }

          break;
        }
      }
      undoManager->Commit();
    }
  }
}