#pragma once
#ifndef _NATUREMAPVISUAL_H_
#define _NATUREMAPVISUAL_H_

#include "NatureMap.h"
#include "../Render/MaterialSpec.h"
#include "../Render/Blur.h"

namespace Terrain {

class NatureMapVisual : public NatureMap, protected Render::DeviceLostHandlerLoadable
{
private :
  struct AttackVisual
  {
    enum Action { ACTION_ATTACK, ACTION_RETREAT };

    AttackVisual() {}
    AttackVisual(Action action_, NatureMapElementId id_, NDb::ENatureType nature_, float delay_, float length_)
      : action(action_), id(id_), nature(nature_), t(-delay_), length(length_) {}

    void Update(float dt) { t += dt; }
    bool IsEnd() const { return t > length; }
    bool GetParams(CVec4 &params, float alpha, bool overburnOnRetreat) const;

    Action action;
    NatureMapElementId id;
    NDb::ENatureType nature;
    float t;
    float length;
  };

  struct Primitive
  {
    static const unsigned NUM_HEXES_SUPPORTED = 20, CONSTANTS_PER_HEX = 2;
    static const unsigned INDICES_PER_ELEMENT = 12; // 3 vertices * 4 triangles

    CVec4 hexConstants[NUM_HEXES_SUPPORTED * CONSTANTS_PER_HEX];
    int hexCount;

    Primitive() : hexCount(0) {}
    bool Add(CVec2 _pos, CVec4 const& _params);
  };

  typedef vector<AttackVisual> attack_elements_container;
protected:
  explicit NatureMapVisual(bool editable_);
public:
  ~NatureMapVisual();

  void RenderDebug();

  void Update();
  void InitializeTerrainMask();
  Render::Texture2DRef GetTerrainMask() { return blurredNatureMap; }
  float GetOverburnScale() const { return overburn[3]; }

public :
  void GetElementVisualBounds(NatureMapElementId id, Render::AABB& aabb) const;
  bool OnRender(); // true if nature was changed

public : // From Render::DeviceLostHandler
  virtual void OnDeviceLost() {}
  virtual void OnDeviceReset();

protected:
  virtual bool OnCreate();

  virtual bool OnLoad( Stream* pStream, int fraction, bool fromRecconect );
  virtual bool OnSave( Stream* pStream, bool fromRecconect ) const;
  virtual bool OnLoadAtRuntime( Stream* pStream, int fraction, bool fromRecconect );
  virtual bool OnSaveAtRuntime( Stream* pStream, bool fromRecconect ) const;

  virtual void OnNatureChanged(int const* pQuadRanges, int numQuadRanges);
  virtual bool Reinit( NDb::ENatureType faction, const NDb::DBNatureMap* pDbNatureMap, bool forceCreate );

private:
  unsigned GetNumVertices() const { return 6 * Primitive::NUM_HEXES_SUPPORTED; }
  unsigned GetNumIndices() const { return Primitive::NUM_HEXES_SUPPORTED * Primitive::INDICES_PER_ELEMENT; }
  bool CreateRenderStructures();
  void FillRenderBuffers();

  void RenderAdd(NatureMapElementId id, CVec4 const& params);

  void RenderElement(NatureMapElementId id, NatureMapElementInfo const& info);
  void RenderElementFX(AttackVisual &attackElem);
  void AddAttackVisual(NatureMapElementId id, NatureMapElementInfo &info);
  void UpdateAttackVisual(float timeElapsed);

  void InitializeParams();

private:
  static const unsigned NUM_PIXELS_PER_TEN_METERS = 16;

  vector<Primitive> primitives;
  DXVertexBufferRef pVertexBuffer;
  DXIndexBufferDynamicRef::Wrapped pIndexBuffer;
  Render::DipDescriptor dipDescriptor;
  DXVertexDeclarationRef pVertexFormat;
  ScopedPtr<Render::BaseMaterial> pMaterial;

  Render::Texture2DRef natureMap, blurredNatureMap;
  Render::Texture2DRef noiseMap;
  Render::Texture2DRef retreatMap;
  Render::Blur9 blurEffect;
  CVec4 mappingCoeff;

  attack_elements_container attackHexes;
  float prevTime;

  CVec4 overburn;

  bool  disabled;
};

} // namespace Terrain

#endif /* _NATUREMAPVISUAL_H_ */
