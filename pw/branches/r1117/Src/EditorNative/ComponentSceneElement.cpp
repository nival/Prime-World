#include "stdafx.h"
#include "ComponentSceneElement.h"
#include "SimpleEditorScene.h"

using namespace nstl;
using namespace System;
using namespace libdb::DB;
using namespace EditorNative;
using namespace EditorNative::SceneElements::SceneObjects;

ComponentSceneElement::ComponentSceneElement(EditorSceneComponent^ sc, libdb::UndoRedo::UndoRedoManager^ manager) 
: sceneComponent(sc)
, undoManager( manager )
{
  placement = new Placement(NULLPLACEMENT);
  offset = new Placement(NULLPLACEMENT);
  dbPlacement = new Placement(NULLPLACEMENT);

  if ( sceneComponent != nullptr )
  {
    *offset = sc->sceneComponent->GetWorldPlacement()-sc->sceneComponent->GetPlacement();
    *dbPlacement = sc->sceneComponent->GetPlacement();
  }
}


void ComponentSceneElement::Draw( NScene::IScene& scene )
{
}

const Placement& ComponentSceneElement::GetPlacement()
{
  return *placement;
}

void ComponentSceneElement::SetPlacement( const Placement& _placement )
{
  *placement = _placement;
  if ( sceneComponent != nullptr )
  {
    Placement pl = ConvertFromWorldToOffset( *offset, *placement );
    sceneComponent->sceneComponent->SetPlacement( pl );
  }
}

void EditorNative::SceneElements::SceneObjects::ComponentSceneElement::InitPlacement( DBTypes::Placement^ from )
{
  if ( sceneComponent != nullptr )
  {
    convertPlacement( from, placement );
    *placement = ConvertFromOffsetToWorld( *offset, *placement );
  }
}

DBTypes::Placement^ EditorNative::SceneElements::SceneObjects::ComponentSceneElement::GetInitPlacement()
{
  DBTypes::Placement^ to = gcnew DBTypes::Placement();
  Placement from = ConvertFromWorldToOffset( *offset, *placement );
  convertPlacement( &from, to );
  return to;
}

void EditorNative::SceneElements::SceneObjects::ComponentSceneElement::Apply( bool isMoved, bool isRotated, bool isScaled )
{
}

DBTypes::Placement^ EditorNative::SceneElements::SceneObjects::ComponentSceneElement::GetDBPlacement()
{
  DBTypes::Placement^ to = gcnew DBTypes::Placement();
  Placement from = *dbPlacement;
  convertPlacement( &from, to );
  return to;
}