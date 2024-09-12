#include "stdafx.h"
#include "../EditorNative/StringUtils.h"
#include "../System/ChunklessSaver.h"
#include "../Scene/BitMap.h"
#include "WaterMap.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace PF_EditorNative
{
void WaterMap::StoreAdvMapWaterZone( System::IntPtr data, float mapSizeX, float mapSizeY, int maskSize, System::String^ fileName )
{
	NScene::BitMap::Store( (char*)data.ToPointer(), mapSizeX, mapSizeY, maskSize, EditorNative::ToMBCS( fileName ) );
}
} // namespace PF_EditorNative
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

