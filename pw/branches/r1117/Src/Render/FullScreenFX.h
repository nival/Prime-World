#pragma once

#include "texture.h"
#include "SceneConstants.h"
#include "Bloom.h"

namespace Render {

class FullScreenFX
{
  ScopedPtr<Bloom> pBloom;
  DXVertexDeclarationRef pVDecl;

public:
  struct Params
  {
    Params();
    Params(NDb::FullScreenFXParams const *db);

    // RGB levels
    CVec4 InMin;
    CVec4 InMax;
    CVec4 OutMin;
    CVec4 OutMax;
    CVec4 Gamma;

    // color cast
    CVec4 Color;
    float ColorCastCoef;

    // sharp
    float SharpPixelSize;
    float SharpCoef;
  };


  FullScreenFX();
  ~FullScreenFX();

  bool PrepareBloom(Texture2DRef const& pTexture) { return pBloom->Prepare(pTexture); } // returns true if blending enabled
  void Apply(const SceneConstants &viewSceneConsts, Texture2D *pTexture, TextureVtx *pCoeffTexture,
             bool doColorCorrect, bool doSharp, float colorSaturation, Texture2D *pDepthTexture, Params const *params,
             const CVec4& satColor, bool useSatColor );
};

inline FullScreenFX::Params::Params(NDb::FullScreenFXParams const *db)
{
  InMin.Set(db->InMin / 255.f, 0.f);
  InMax.Set(db->InMax / 255.f, 0.f);
  OutMin.Set(db->OutMin / 255.f, 0.f);
  OutMax.Set(db->OutMax / 255.f, 0.f);
  Gamma.Set(db->Gamma, 0.f);

  // color cast
  Color.Set(db->Color.R / 255.f, db->Color.G / 255.f, db->Color.B / 255.f, db->Color.A / 255.f);
  ColorCastCoef = db->ColorCastCoef;

  // sharp
  SharpPixelSize = db->SharpPixelSize;
  SharpCoef = db->SharpCoef;
}

} // namespace Render
