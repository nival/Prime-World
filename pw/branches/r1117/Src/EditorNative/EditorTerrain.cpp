#include "stdafx.h"
#include "Utility.h"
#include "EditorScene.h"
#include "EditorTerrain.h"
#include "../Scene/LightingScene.h"

typedef Terrain::TerrainLayerManager TerrainLayerManager;
typedef Terrain::Terrain TerrainManager;

using namespace System;
using namespace System::Diagnostics;

using namespace EditorNative;
using namespace EditorNative::SceneElements;
using namespace EditorNative::Terrain;
using namespace EditorNative::Terrain::Layers;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EditorTerrain::EditorTerrain( DBTypes::Terrain^ resource )
: dbTerrain( resource )
, elemXCount( resource->elemXCount )
, elemYCount( resource->elemYCount )
, tilesPerElement( resource->tilesPerElement )
,	tcvFileName( resource->geometry->TCVFileName )
,	layerMaskFileName( resource->layerMaskFile )
,	bakedTerrainFileName( resource->geometry->bakedTerrainFileName )
,	heightmapFileName( resource->geometry->heightmapFileName )
,	localLayer( gcnew TerrainMaterialLayer( TerrainLayerManager::LOCAL_LAYER ) )
,	holesLayer( gcnew TerrainMaterialLayer( TerrainLayerManager::HOLES_LAYER ) )
, isVisible( true )
, isEditable( false )
{
}

EditorTerrain::EditorTerrain( DBTypes::Terrain^ resource, bool isScript )
: dbTerrain( resource )
, elemXCount( resource->elemXCount )
, elemYCount( resource->elemYCount )
, tilesPerElement( resource->tilesPerElement )
,	tcvFileName( resource->geometry->TCVFileName )
,	layerMaskFileName( resource->layerMaskFile )
,	bakedTerrainFileName( resource->geometry->bakedTerrainFileName )
,	heightmapFileName( resource->geometry->heightmapFileName )
,	localLayer( gcnew TerrainMaterialLayer( TerrainLayerManager::LOCAL_LAYER ) )
,	holesLayer( gcnew TerrainMaterialLayer( TerrainLayerManager::HOLES_LAYER ) )
, isVisible( true )
, isEditable( true )
{
  pTerrain = new ::Terrain::Terrain( true );
  pTerrain->LoadTerrain( NDb::Get<NDb::Terrain>(NDb::DBID(ToMBCS(dbTerrain->DBId->Name))) );
}

void EditorTerrain::SymmetricalTerrain( float sizeX, int elemX, int elemY, bool right_to_left )
{
	pTerrain->LoadTCV( ToMBCS( tcvFileName ), true );
  pTerrain->LoadLayerMask( ToMBCS( layerMaskFileName ) );

  int startX = 0;
  int stopX = 0;
  int startY = 0;
  int stopY = 0;

  int maxX = elemX;
  int maxY = elemY;

  if ( !right_to_left )
  {
    startX = 0;
    stopX = elemX;
    startY = 0;
    stopY = elemY;

    startX = stopX/2;
    if ( stopX % 2 == 1 )
      startX++;
  }
  else
  {
    startX = 0;
    stopX = elemX/2;
    startY = 0;
    stopY = elemY;
  }
  
  for ( int i = startX; i < stopX; i++ )
  {
    for( int k = startY; k < stopY; k++ )
    {
	    Matrix43 matrix = pTerrain->GetTCV( maxX-i-1, maxY-k-1 );

	    CVec3 translation;
	    CQuat rotation;
	    CVec3 scale;
      DecomposeMatrix( matrix, translation, rotation, scale );

      translation.x = 10.0f*i;
      translation.y = 10.0f*k;
    
      ComposeMatrix( matrix, translation, Quaternion::Identity->Native, Vector3::Ones->Native );
  		pTerrain->SetTCV( i, k, matrix );
    }
  }

  maxX = pTerrain->GetLayerManager().GetLayerMask().GetSizeX();
  maxY = pTerrain->GetLayerManager().GetLayerMask().GetSizeY();

  if ( !right_to_left )
  {
    stopX = maxX;
    stopY = maxY;

    startX = stopX/2;
    if ( stopX % 2 == 1 )
      startX++;
  }
  else
  {
    stopX = maxX/2;
    stopY = maxY;

    startX = 0;
    startY = 0;
  }

  for ( int i = startX; i < stopX; i++ )
  {
    for ( int k = startY; k < stopY; k++ )
    {
		  unsigned char byte = pTerrain->GetLayerManager().ReadLayerValue( maxY-k-1, maxX-i-1 );
		  pTerrain->GetLayerManager().WriteLayerValue( byte, k, i );
    }
  }

  pTerrain->SaveLayerMask( ToMBCS( layerMaskFileName ) );
  pTerrain->SaveTCV( ToMBCS( tcvFileName ) );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EditorTerrain::~EditorTerrain()
{
	this->!EditorTerrain();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EditorTerrain::!EditorTerrain()
{
	Owner = nullptr;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorTerrain::Add( TcvMarker ^marker )
{
	if ( !markers.Contains( marker ) )
	{
		markers.Add( marker );
		Add( (SceneElement^)marker );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorTerrain::Remove( TcvMarker ^marker )
{
	if ( markers.Contains( marker ) )
	{
		markers.Remove( marker );
		Remove( (SceneElement^)marker );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorTerrain::Add( TerrainGlobalLayer^ layer )
{
	if ( !globalLayers.Contains( layer ) )
	{
		globalLayers.Add( layer );
		if ( IsValid )
		{
			layer->Owner = this;
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorTerrain::Remove( TerrainGlobalLayer^ layer )
{
	if ( globalLayers.Contains( layer ) )
	{
		globalLayers.Remove( layer );
		if ( IsValid )
		{
			layer->Owner = nullptr;
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorTerrain::Add( TerrainElement^ element )
{
	if ( !elements.Contains( element ) )
	{
		elements.Add( element );
		Add( (SceneElement^)element );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorTerrain::Remove( TerrainElement^ element )
{
	if ( elements.Contains( element ) )
	{
		elements.Remove( element );
		Remove( (SceneElement^)element );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorTerrain::Add( SceneElement^ element )
{
	if ( IsValid )
	{
		Owner->Add( element );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorTerrain::Remove( SceneElement^ element )
{
	if ( IsValid )
	{
		Owner->Remove( element );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorTerrain::StoreBinaryData( System::Collections::Generic::IList<TerrainElement^>^ elementsOrder )
{
  if ( IsValid )
  {
    int lastNatureMap = currentNatureMap;
    SetNatureMap(0, true);
    Owner->UpdateAllMSO();

    Native->SaveLayerMask( ToMBCS( layerMaskFileName ) );

    if ( elementsOrder->Count != elements.Count )
    {
      Trace::TraceError( "Cannot bake terrain elements: invalid elements order." );
    }
    else
    {
      if ( true/*geometryChanged*/ ) // smirnov [2008/11/28]: the flag doesn't always work
      {
        Owner->NativeScene->GetTerrain()->SaveTCV( ToMBCS( tcvFileName ) );

        vector<TerrainElementId> elementIds( elementsOrder->Count );
        for ( int i = 0; i < elementsOrder->Count; ++i )
        {
          elementIds[i] = elementsOrder[i]->ElementId;
        }

        Owner->NativeScene->GetTerrain()->SaveHeightmap(ToMBCS(heightmapFileName));

        Owner->NativeScene->GetTerrain()->SaveNatureMap(ToMBCS(dbTerrain->natureMap->natureMapFile));

        Owner->NativeScene->GetTerrain()->BakeTerrainGeometry(
          elementIds,
          ToMBCS( bakedTerrainFileName )
          );
        geometryChanged = false;
      }
    }
    SetNatureMap( lastNatureMap );
    Owner->UpdateAllMSO();
  }

  MessageTrace( "EditorTerrain::StoreBinaryData done" );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorTerrain::LoadBinaryData()
{
	if ( IsValid )
	{
		if ( FileExists( layerMaskFileName ) )
			Native->LoadLayerMask( ToMBCS( layerMaskFileName ) );

		if ( FileExists( tcvFileName ) )
		{
			const bool applyInstantly = true;
			Owner->NativeScene->GetTerrain()->LoadTCV( ToMBCS( tcvFileName ), applyInstantly );

			for each ( TcvMarker^ marker in markers )
			{
				marker->OnTCVChanged();
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EditorTerrain::TryGetHeight( float x, float y, float% height )
{
	if ( IsValid )
	{
		float h;
		bool result = Owner->NativeScene->GetTerrain()->GetHeight( x, y, &h );
		height = h;
		return result;
	}
	else
	{
		return false;
	}
}

bool EditorTerrain::TryGetNormal( float x, float y, Vector3^% normal )
{
	if ( IsValid )
	{
		float h;
		CVec3 nativeNormal;

		bool result = Owner->NativeScene->GetTerrain()->GetHeight( x, y, &h, &nativeNormal );

		if(result)
		normal = gcnew Vector3(nativeNormal);

		return result;
	}
	else
	{
		return false;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
System::Drawing::Color EditorTerrain::GetLayerColor( int idx )
{
	if ( IsValid )
	{
		CVec4 const& c = Owner->NativeScene->GetTerrain()->GetLayerManager().GetLayerDebugColor(idx);
		return System::Drawing::Color::FromArgb((int)(c.r * 255), (int)(c.g * 255), (int)(c.b * 255));
	}
	else
	{
		return System::Drawing::Color::FromKnownColor(System::Drawing::KnownColor::Black);
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorTerrain::LayerDisplayMode::set(int value)
{
	if (IsValid)
		Owner->NativeScene->GetTerrain()->SetLayerDisplayMode(value);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IntPtr EditorTerrain::NativeTerrain::get()
{
	if ( IsValid )
	{
		return IntPtr( Owner->NativeScene->GetTerrain() );
	}
	else
	{
		return IntPtr::Zero;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool EditorTerrain::IsNatureMapEditable::get()
{
  if ( Native != nullptr )
  {
    ::Terrain::NatureMap& nmap = Native->GetNatureMap();
    return nmap.GetDB().editableNatureMap;
  }
  else
  {
    return false;
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NativeTerrain* EditorTerrain::Native::get()
{
	return IsValid ? Owner->NativeScene->GetTerrain() : nullptr;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void EditorTerrain::Owner::set( EditorScene^ value )
{
  if ( !ReferenceEquals( owner, value ) )
  {
    OnBeforeOwnerChanged();
    owner = value;
    OnOwnerChanged();
  }
}

void EditorTerrain::OnBeforeOwnerChanged()
{
	if ( !ReferenceEquals( Owner, nullptr ) )
	{
		for each( TcvMarker^ marker in markers )
		{
			Owner->Remove( marker );
		}

		for each( TerrainElement^ element in elements )
		{
			Owner->Remove( element );
		}

		for each ( TerrainGlobalLayer^ layer in globalLayers )
		{
			layer->Owner = nullptr;
		}

		holesLayer->Owner = nullptr;
		localLayer->Owner = nullptr;

		Native->InvalidateLayers();
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorTerrain::OnOwnerChanged()
{
	if ( !ReferenceEquals( Owner, nullptr ) )
	{
    if ( !isEditable )
      Owner->NativeScene->LoadTerrain( NDb::Get<NDb::Terrain>(NDb::DBID(ToMBCS(dbTerrain->DBId->Name))) );
    else
    {
		  Owner->NativeScene->CreateTerrain( ToMBCS(dbTerrain->DBId->Name) );

		  for each( TcvMarker^ marker in markers )
		  {
			  Owner->Add( marker );
		  }

		  for each( TerrainElement^ element in elements )
		  {
			  Owner->Add( element );
		  }

		  holesLayer->Owner = this;
		  localLayer->Owner = this;

		  for each ( TerrainGlobalLayer^ layer in globalLayers )
		  {
			  layer->Owner = this;
		  }

      Native->InitNatureMapParams();
		  Native->InvalidateLayers();
    }
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void EditorTerrain::UpdateHeightsController()
{
	if ( !ReferenceEquals( Owner, nullptr ) )
	{
		Owner->NativeScene->UpdateHeightsController();
	}
}

void EditorTerrain::RecalculateLighting()
{
  Native->RecalculateLighting();
}

void EditorTerrain::WeldVertices()
{
  Native->WeldVertices();
}

void EditorTerrain::SetNatureMap( int type, bool forceCreate )
{
	if ( !Native )
		return;

  NDb::ENatureType faction[] = {
    static_cast<NDb::ENatureType>(-1), NDb::NATURETYPE_N, NDb::NATURETYPE_A, NDb::NATURETYPE_B };

  NI_ASSERT(uint(type) < ARRAY_SIZE(faction), "type out of bounds");

  currentNatureMap = type;
  NDb::Ptr<NDb::Terrain> pTerrain = NDb::Get<NDb::Terrain>(NDb::DBID(ToMBCS(dbTerrain->DBId->Name)));
  Native->GetNatureMap().Reinit( faction[type], &(pTerrain->natureMap), forceCreate );
}

int EditorNative::Terrain::EditorTerrain::GetFraction( int elementId )
{
  ::Terrain::NatureMap& nmap = Native->GetNatureMap();
  return nmap.GetNature( elementId );
}

int EditorTerrain::GetFraction( float x, float y )
{
  ::Terrain::NatureMap& nmap = Native->GetNatureMap();
  return nmap.GetNature( x, y );
}

namespace
{
  struct ElementCollector
  {
  public :
    ElementCollector(::Terrain::NatureMap& nmap )
      : nmap(nmap) {}
    void operator()(const CVec2& elemPos, ::Terrain::NatureMapElementId id, ::Terrain::NatureMapElementInfo const& info)
    {  res.push_back( id );  }

    ::Terrain::NatureMap& nmap;
    ::nstl::vector<int> res;
  }; 

}

array<int>^ EditorNative::Terrain::EditorTerrain::GetNatureMapElementIdsInCircle(float x, float y, float radius)
{
  ::Terrain::NatureMap& nmap = Native->GetNatureMap();
  ElementCollector func(nmap );

  nmap.ForAllElementsInCircle( func, CVec2(x, y), radius );

  if ( func.res.empty() )
  {
    int singleId = nmap.LocateElement( x, y );
    if ( singleId >= 0 )
      func.res.push_back( singleId );
  }

  array<int>^ res = gcnew array<int>(func.res.size());
  for( int i = 0; i < func.res.size(); ++i )
    res[i] = func.res[i];
  return res;
}

void EditorNative::Terrain::EditorTerrain::ChangeFraction( int elementId, int newFraction )
{
  ::Terrain::NatureMap& nmap = Native->GetNatureMap();
  nmap.EditNature( elementId, (NDb::ENatureType)newFraction );
}

void EditorNative::Terrain::EditorTerrain::ChangeFraction( float x, float y, int newFraction )
{
  ::Terrain::NatureMap& nmap = Native->GetNatureMap();
  int elementId = nmap.LocateElement( x, y );

  if ( elementId < 0 )
    return;
  nmap.EditNature( elementId, (NDb::ENatureType)newFraction );
}

void EditorNative::Terrain::EditorTerrain::StepNatureMap()
{
  ::Terrain::NatureMap& nmap = Native->GetNatureMap();
  nmap.OnStep(0.1f);
}


void EditorTerrain::TryFullLoad()
{
  if ( isEditable )
  {
    SetNatureMap( currentNatureMap, true ); // force nature map update - just to visualize changes
    return;
  }

  if ( Owner == nullptr )
    return;

  isEditable = true;
  MessageTrace( "### TryFullLoad start ###" );
  
  NHPTimer::FTime startTime = NHPTimer::GetScalarTime(); 
  OnOwnerChanged();
  NHPTimer::FTime finishTime = NHPTimer::GetScalarTime();
  MessageTrace( NStr::StrFmt("OnOwnerChanged time: %f s", (finishTime - startTime)) );
  
  startTime = NHPTimer::GetScalarTime(); 
  LoadBinaryData();
  finishTime = NHPTimer::GetScalarTime();
  MessageTrace( NStr::StrFmt("LoadBinaryData time: %f s", (finishTime - startTime)) );
       
  
  startTime = NHPTimer::GetScalarTime(); 
  SetNatureMap( currentNatureMap );
  finishTime = NHPTimer::GetScalarTime();
  MessageTrace( NStr::StrFmt("SetNatureMap time: %f s", (finishTime - startTime)) );

  startTime = NHPTimer::GetScalarTime();
  Owner->Draw( Owner->GetHWnd(), 0.0f, 0.0f );
  finishTime = NHPTimer::GetScalarTime();
  MessageTrace( NStr::StrFmt("Owner->Draw time: %f s", (finishTime - startTime)) );

  startTime = NHPTimer::GetScalarTime();
  WeldVertices();
  finishTime = NHPTimer::GetScalarTime();
  MessageTrace( NStr::StrFmt("WeldVertices time: %f s", (finishTime - startTime)) );

  startTime = NHPTimer::GetScalarTime();
  Owner->GetLightScene()->ResetTerrain();
  finishTime = NHPTimer::GetScalarTime();
  MessageTrace( NStr::StrFmt("Owner->GetLightScene()->ResetTerrain() time: %f s", (finishTime - startTime)) );
  
  startTime = NHPTimer::GetScalarTime();
  Owner->CalculateLighting();
  finishTime = NHPTimer::GetScalarTime();
  MessageTrace( NStr::StrFmt("Owner->CalculateLighting() time: %f s", (finishTime - startTime)) );
  
  MessageTrace( "### TryFullLoad end ###" );
}
