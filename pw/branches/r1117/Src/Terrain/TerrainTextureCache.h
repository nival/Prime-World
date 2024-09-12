#pragma once

namespace Render {
  class BatchQueue;
}

namespace Terrain {

class INTERMODULE_EXPORT TerrainTextureCache
{
protected:
  TerrainTextureCache() {}

public:
  static TerrainTextureCache* Create(UINT _size, UINT _tileSize);
  virtual ~TerrainTextureCache() {}

  virtual bool IsValid() = 0;
  virtual void OnNatureAttack() = 0;
  virtual void OnRender(Render::BatchQueue& _queue) = 0;
  virtual void RestoreQueue(Render::BatchQueue& _queue) = 0;
  virtual void OnFillStart(Render::BatchQueue *_pQueue) = 0;
  virtual void OnFillEnd(Render::BatchQueue *_pQueue) = 0;
  // Get cache texture ptr. Returns NULL for patches not cached yet. NULL arg means we need the pointer anyway
  virtual const Render::Texture2D* GetTexture(const CVec2 *_pCenter) const = 0;
  virtual const Render::AABB& GetAABB() const = 0;
};

} // namespace Terrain