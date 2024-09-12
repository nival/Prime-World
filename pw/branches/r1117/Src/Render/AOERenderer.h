#pragma once
#ifndef AOERENDERER_H_INCLUDED
#define AOERENDERER_H_INCLUDED

#include "primitive.h"
#include "Material.h"

namespace Render
{
class BaseMaterial;

// TODO: This class needs a new name. From the begining it used not only for AOE, 
// but also for any abilty range limitation rendering. Now it also shows direction hint arrow.
class AOERenderer
{
public:
  enum AreaType
  {
    AREA_DISK,
    AREA_SECTOR,
    AREA_LINE,
    AREA_WALL,
    _NUM_AREA_TYPES
  };

  // decided to not implement overcomplicated system and predefine two usages according to the design
  enum ChannelType
  {
    CHANNEL_RANGE,  //< used to show range of the ability to be applied
    CHANNEL_TARGET, //< used to show area affected by the ability
    CHANNEL_DIRECTION, //< used to show direction hint arrow
    CHANNEL_RANGE2, //<used to show alternative range
    CHANNEL_UNIT_RANGE1,
    CHANNEL_UNIT_RANGE2,
    _NUM_CHANNELS
  };

public:
  AOERenderer();
  ~AOERenderer();

  static void Init();
  static void Term();
  static AOERenderer* Get();

  void SetSaturation( float _saturation, const CVec4& _satColor, bool _saturate ) { saturation = _saturation; saturate = _saturate; satColor = _satColor; }

  void SetAreaParams(ChannelType channelId, AreaType type, NDb::Material const* pMaterial, float radius, float span);
  void SetAreaRadius(ChannelType channelId, float radius);
  void SetAreaPosition(ChannelType channelId, CVec3 const& pos, CVec3 const& dir, bool usePrimaryColor, float interpolateColor = -1.0f);
  void ResetArea(ChannelType channelId);
  void ResetAll();

  bool IsActive(ChannelType channelId);

  void Render();

private:
  bool CreateQuad();
  bool CreateFan();
  void PrepareFan(float angle);
  bool CreateStrip();
  void PrepareStrip(ChannelType channelId, float len, float base);

private:
  static AOERenderer* s_pInstance;
  bool bInit;
  Primitive quad; //< used for disk rendering
  Primitive fan;  //< used for sector rendering
  Primitive strip;//< used for line rendering

  struct AreaChannel
  {
    AreaType type;
    ScopedPtr<BaseMaterial> pMaterial;
    HDRColor color;
    float radius;
    float span; // either angle (for sector) or length (for line)
    SHMatrix xform;
    bool enabled;
  };
  AreaChannel channels[_NUM_CHANNELS];

  static const int NUM_FAN_PARAMS = 7;
  CVec4 fanParams[NUM_FAN_PARAMS]; // x, y, u, v

  static const int NUM_STRIP_PARAMS = 4;
  CVec4 stripParams[_NUM_CHANNELS][NUM_STRIP_PARAMS]; // x, y, u, v

  float saturation;
  CVec4 satColor;
  bool saturate;
};

inline AOERenderer* GetAOERenderer() { return AOERenderer::Get(); }

} // namespace Render

#endif // AOERENDERER_H_INCLUDED
