#pragma once
#ifndef AMBIENCEMAP_H_INCLUDED
#define AMBIENCEMAP_H_INCLUDED

#include "../Render/texture.h"
#include "../System/nhash_map.h"
#include "../System/ScopedArray.h"
#include "../System/Geom.h"

class AmbienceMap
{
public:
  AmbienceMap();
  virtual ~AmbienceMap();

  bool Init(NDb::SoundAmbienceMap const& dbAmbienceMap, CVec2 const& worldSize_, nstl::vector<unsigned int> const& colors);
  
  void UpdateEnvironment(CVec3 const& pos, CVec3 const& dir, bool force = false);

  // Resulting array's length is one more than provided list of colors [1 + colors.size()].
  // The very first entry contains unrecognized pixels count around the listener,
  // you should check that it is zero.
  nstl::vector<float> const& GetEnvironment() const { return environment; }

  void RenderDebug();

protected:
  void InitPalette(nstl::vector<unsigned int> const& colors);
  void Clear();
  bool FillMapFrom(Render::Texture2DRef const& pSource); // may be used for dynamics in future
  void UpdateEnvironment(CVec2 const& pos, CVec2 const& dir, bool force);

private:
  bool valid;
  CVec2 worldSize;
  float radius;
  float directivity;
  Render::Texture2DRef pTexture; // stored only for debug render?

  typedef nstl::vector<unsigned int> Palette;
  typedef nstl::hash_map<unsigned int, unsigned char> UnPalette;
  Palette palette;
  UnPalette unpalette;

  unsigned mapWidth;
  unsigned mapHeight;
  ScopedArray<unsigned char> pMap; // CArray2D is rather heavy and slow

  nstl::vector<float> environment;
  CTRect<int> rect;
};

#endif // AMBIENCEMAP_H_INCLUDED
