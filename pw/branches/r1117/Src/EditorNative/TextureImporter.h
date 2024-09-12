#pragma once

namespace EditorNative {
namespace TextureImporter {
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public ref class TextureImporter sealed
{
public:
  static bool Import( System::Drawing::Bitmap^ source, System::IO::Stream^ output, 
    DBTypes::EPixelFormat format, bool normal, bool noMipmaps, int startMipmapLevel, array<int>^ passes,
    int fType, float fParam1, float fParam2, float fParam3 );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}	// namespace DebugVars
}	// namespace EditorNative
