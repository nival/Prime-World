#pragma once

#include "SceneElement.h"

namespace EditorNative {
namespace Terrain {
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public ref class TcvMarker : SceneElements::SceneElement
	{
	private:
		int row;
		int column;
    System::Drawing::Color color;
    float widthInPixels;
    float heightInPixels;

	protected:
		TcvMarker( int row, int column );

	public:
    property System::Drawing::Color Color
    {
      System::Drawing::Color get() { return color; }
      void set( System::Drawing::Color value ) { color = value; }
    }

		void Update();
    virtual void Draw() override;

	internal:
		void OnTCVChanged();
    bool TryPick( NScene::ICamera& camera, const CVec2& cursorPosition, CVec3& pickCoordinate );

	protected:
		virtual void OnBeforeOwnerChanged() override sealed;
		virtual void OnOwnerChanged() override sealed;

		virtual void OnSelectionChanged() override sealed;
		virtual void OnPositionChanged() override sealed;
		virtual void OnManipulatorChanged() override sealed;

    virtual void Draw( const CVec2& projectedLocation );

    property float WidthInPixels
    {
      float get() { return widthInPixels; }
      void set( float value ) { widthInPixels = value; }
    }

    property float HeightInPixels
    {
      float get() { return heightInPixels; }
      void set( float value ) { heightInPixels = value; }
    }

	};
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}	// namespace Terrain
}	// namespace EditorNative
