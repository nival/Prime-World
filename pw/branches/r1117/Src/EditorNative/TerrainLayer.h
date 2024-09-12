#pragma once

namespace EditorNative {
namespace Terrain {
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ref class EditorTerrain;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Layers {
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public ref class TerrainLayer abstract
	{
	private:
		EditorTerrain^ terrain;

	internal:
		TerrainLayer();

	public:
		property virtual System::Byte default[int, int]
		{
			virtual System::Byte get( int x, int y ) abstract;
			virtual void set( int x, int y, System::Byte value ) abstract;
		}

	internal:
		property EditorTerrain^ Owner
		{
			EditorTerrain^ get() { return terrain; }
			void set( EditorTerrain^ value );
		}

		property virtual bool IsValid
		{
			virtual bool get() { return !ReferenceEquals( terrain, nullptr ); }
		}

	protected:
		virtual void OnBeforeOwnerChanged() {}
		virtual void OnOwnerChanged() {}
	};
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}	// namespace Layers
}	// namespace Terrain
}	// namespace EditorNative
