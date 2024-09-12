#pragma once

#include "../System/2Darray.h"
#include "../System/Array2DWrapper.h"

#ifndef VISUAL_CUTTED
#include "../Render/MaterialSpec.h"
#include "ArrayInVRAM.h"
#endif

struct TerrainAttributes
{
	float height;
	float normalX;
	float normalY;
	float reserved;
};

namespace Terrain {

class Terrain;

class TerrainHeightManager
{
public:
  TerrainHeightManager();
  ~TerrainHeightManager();

	void SetOwner(Terrain* owner) { pOwner = owner; }
	void Initialize();
	void Load(const nstl::string& filename);
	void Save(const nstl::string& filename);
	void Update();

	bool GetHeight(float x, float y, float* height, CVec3* normal = NULL) const;
	float GetHeightFast(float x, float y) const;
	Array2DWrapper<TerrainAttributes const> const& GetHeights() const { return heights; }
	CArray2D<float> const& GetHeightsAsFloat() const { return asFloat; }

	static unsigned short FloatAsShort(float x);
	static float ShortAsFloat(unsigned short x);

	unsigned int GetHeightsVersion() const { return version; }
	void MarkAsDirty() { dirty = true; }

private:
	void SyncArrays();

private:
	static const unsigned int BINARY_VERSION = 0x01004D48; // 'HM' + 1
	static const float SHORTHEIGHT_MIN;
	static const float SHORTHEIGHT_MAX;
	static const float SHORTHEIGHT_SCALE;
	static const float SHORTHEIGHT_OFFSET;

	Terrain* pOwner; // smirnov [2008/12/11]: CPtr<> is not possible here

#ifndef VISUAL_CUTTED
  Render::BaseMaterial* renderTargetMaterial;		// need for height map update (in editor)
	ArrayInVRAM<TerrainAttributes> renderTarget;	// need for height map update (in editor)
#endif

  unsigned char* binaryData;

	Array2DWrapper<TerrainAttributes const> heights;
	CArray2D<float> asFloat;

	unsigned int version;
	bool dirty;
};

} // namespace Terrain
