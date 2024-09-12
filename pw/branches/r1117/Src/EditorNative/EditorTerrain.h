#pragma once

typedef ::Terrain::Terrain NativeTerrain;

#include "TcvMarker.h"
#include "TerrainElement.h"
#include "TerrainGlobalLayer.h"
#include "TerrainMaterialLayer.h"

namespace EditorNative {
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ref class EditorScene;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Terrain {
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public ref class EditorTerrain sealed
	{
	private:
    EditorScene^ owner;
    bool isVisible;

		bool geometryChanged;

    DBTypes::Terrain^ dbTerrain;
		initonly int elemXCount;
		initonly int elemYCount;
		initonly int tilesPerElement;
		initonly System::String^ tcvFileName;
		initonly System::String^ layerMaskFileName;
		initonly System::String^ bakedTerrainFileName;
		initonly System::String^ heightmapFileName;
		initonly System::String^ solidOriginalGeometryFileName;

		System::Collections::Generic::List<TcvMarker^> markers;
		System::Collections::Generic::List<TerrainElement^> elements;
		System::Collections::Generic::List<Layers::TerrainGlobalLayer^> globalLayers;

		initonly Layers::TerrainMaterialLayer^ localLayer;
		initonly Layers::TerrainMaterialLayer^ holesLayer;

    int currentNatureMap;

    bool isEditable;

    NativeTerrain* pTerrain;

	public:
		EditorTerrain( DBTypes::Terrain^ resource );
    EditorTerrain( DBTypes::Terrain^ resource, bool isScript );
		~EditorTerrain();
		!EditorTerrain();

	public:
    void SymmetricalTerrain( float sizeX, int elemX, int elemY, bool right_to_left );

    void Add( TcvMarker^ marker );
		void Remove( TcvMarker^ marker );

		void Add( Layers::TerrainGlobalLayer^ layer );
		void Remove( Layers::TerrainGlobalLayer^ layer );

		void Add( TerrainElement^ element );
		void Remove( TerrainElement^ element );

		void StoreBinaryData( System::Collections::Generic::IList<TerrainElement^>^ elementsOrder );
		void LoadBinaryData();

		bool TryGetHeight( float x, float y, float% height );
		bool TryGetNormal( float x, float y, Vector3^% normal );

		System::Drawing::Color GetLayerColor( int idx );

		property System::IntPtr NativeTerrain
		{
			System::IntPtr get();
		}

		property bool Changed
		{
			bool get() { return geometryChanged; }
			void set( bool value ) { geometryChanged = value; }
		}

		property bool IsEditable
		{
			bool get() { return isEditable; }
			void set( bool value ) { isEditable = value; }
		}

    property bool IsNatureMapEditable
    {
      bool get();
    }
		property array<TcvMarker^>^ TcvMarkers
		{
			array<TcvMarker^>^ get() { return markers.ToArray(); }
		}

		property array<Layers::TerrainGlobalLayer^>^ GlobalLayers
		{
			array<Layers::TerrainGlobalLayer^>^ get() { return globalLayers.ToArray(); }
		}

		property Layers::TerrainLayer^ LocalLayer
		{
			Layers::TerrainLayer^ get() { return localLayer; }
		}

		property Layers::TerrainLayer^ HolesLayer
		{
			Layers::TerrainLayer^ get() { return holesLayer; }
		}

		property int SizeX
		{
			int get() { return elemXCount; }
		}

		property int SizeY
		{
			int get() { return elemYCount; }
		}

		property int TilesPerElement
		{
			int get() { return tilesPerElement; }
		}

		property array<TerrainElement^>^ Elements
		{
			array<TerrainElement^>^ get() { return elements.ToArray(); }
		}

		property int LayerDisplayMode
		{
			void set(int value);
		}

    property bool IsVisible
    {
      bool get() { return isVisible; }
      void set( bool value ) { isVisible = value; }
    }

		void UpdateHeightsController();
    void RecalculateLighting();
    void WeldVertices();

    void SetNatureMap( int type, bool forceCreate );
    void SetNatureMap( int type ) { SetNatureMap(type, false); }
    int GetFraction( int elementId );
    int GetFraction( float x, float y );

    array<int>^ GetNatureMapElementIdsInCircle(float x, float y, float radius);
    void ChangeFraction( int elementId, int newFraction );
    void ChangeFraction( float x, float y, int newFraction );
    void StepNatureMap();

    void ShowAttackSpace()
    {
      Native->GetNatureMap().ShowAttackSpace();
    }

    property EditorScene^ Owner
    {
      EditorScene^ get() { return owner; }
      void set( EditorScene^ value );
    }

    void TryFullLoad();

  internal:
		property ::Terrain::Terrain* Native
		{
			::Terrain::Terrain* get();
		}

	protected:
		void OnBeforeOwnerChanged();
		void OnOwnerChanged();

	private:
		void Add( SceneElements::SceneElement^ element );
		void Remove( SceneElements::SceneElement^ element );

		property bool IsValid
		{
			bool get() { return !ReferenceEquals( Owner, nullptr ); }
		}
	};
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}	// namespace Terrain
}	// namespace EditorNative
