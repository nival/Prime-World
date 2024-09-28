#pragma once

/////////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "../PF_Core/ClientObject.h"

#include "PFClientObjectBase.h"

#include "../Scene/RenderableScene.h"
#include "../Render/RenderInterface.h"
#include "../Render/Renderer.h"
#include "../Render/batch.h"
#include "../Render/texture.h"
#include "../Render/Blur.h"

#include "WarFog.h"
#include "TileMap.h"

namespace NScene
{
  class Scene;
}

namespace NWorld
{
  class PFWorld;
}

namespace NGameX
{

/////////////////////////////////////////////////////////////////////////////////
// Classes
/////////////////////////////////////////////////////////////////////////////////

  namespace EVisMapMode
  {
    enum Type
    {
      Undefined = -1,
      FactionN = NDb::FACTION_NEUTRAL,
      FactionA = NDb::FACTION_FREEZE,
      FactionB = NDb::FACTION_BURN,
      Everything,
      Combined,
      Last,
    };

    inline bool IsFaction(const Type value)
    {
      switch (value)
      {
      case FactionN:
      case FactionA:
      case FactionB:
        return true;
      default:
        return false;
      }
    }

    inline uint GetFogOfWarTeam(const Type value)
    {
      switch (value)
      {
      case FactionN:
      case FactionA:
      case FactionB:
        return static_cast<uint>(value);
      default:
        return static_cast<uint>(-1);
      }
    }

    inline NDb::EFaction ToFaction(const Type value)
    {
      switch (value)
      {
      case FactionN:
        return NDb::FACTION_NEUTRAL;
      case FactionA:
        return NDb::FACTION_FREEZE;
      case FactionB:
        return NDb::FACTION_BURN;
      default:
        return NDb::FACTION_NEUTRAL;
      }
    }

    inline Type FromFaction(const NDb::EFaction faction)
    {
      switch (faction)
      {
      case NDb::FACTION_NEUTRAL:
        return FactionN;
      case NDb::FACTION_FREEZE:
        return FactionA;
      case NDb::FACTION_BURN:
        return FactionB;
      default:
        return Undefined;
      }
    }

    inline bool IsValid(const Type value)
    {
      switch (value)
      {
      case FactionN:
      case FactionA:
      case FactionB:
      case Everything:
      case Combined:
        return true;
      default:
        return false;
      }
    }
  }

  namespace Detail
  {
    class VisMapClientController : public NonCopyable
    {
    public:
      virtual ~VisMapClientController()
      {
      }

      EVisMapMode::Type GetMode() const { return mode; }

      virtual const NWorld::FogOfWar::VisMap& GetVisMap() const = 0;
      virtual const NWorld::FogOfWar::VisMapMask& GetVisMapMask() const = 0;

      virtual bool GetCombine(const NDb::EFaction faction) const { return false; }

      virtual void SetMode(const EVisMapMode::Type value) { mode = value; }
      virtual void SetCombine(const NDb::EFaction faction, const bool combine) {}

      virtual void Update() {}

      virtual bool IsPointVisible(const CVec2& pos) const;
    protected:
      VisMapClientController()
        : mode(EVisMapMode::Undefined)
        , fogOfWar()
        , tileMap()
      {
      }

      EVisMapMode::Type mode;

      DI_WEAK(NWorld::FogOfWar) fogOfWar;
      DI_WEAK(NWorld::TileMap) tileMap;
    };

    class RegularVisMapClientController : public VisMapClientController
    {
    public:
      RegularVisMapClientController();
      virtual ~RegularVisMapClientController();

      virtual const NWorld::FogOfWar::VisMap& GetVisMap() const;
      virtual const NWorld::FogOfWar::VisMapMask& GetVisMapMask() const;

      virtual void SetMode(const EVisMapMode::Type value);

      virtual bool IsPointVisible(const CVec2& pos) const;
    };

    class DeveloperVisMapClientController : public VisMapClientController
    {
    public:
      DeveloperVisMapClientController();
      virtual ~DeveloperVisMapClientController();

      virtual const NWorld::FogOfWar::VisMap& GetVisMap() const;
      virtual const NWorld::FogOfWar::VisMapMask& GetVisMapMask() const;

      virtual void SetMode(const EVisMapMode::Type value);

      virtual bool IsPointVisible(const CVec2& pos) const;
    };

    class SpectatorVisMapClientController : public VisMapClientController
    {
    public:
      SpectatorVisMapClientController();
      virtual ~SpectatorVisMapClientController();

      virtual const NWorld::FogOfWar::VisMap& GetVisMap() const;
      virtual const NWorld::FogOfWar::VisMapMask& GetVisMapMask() const;

      virtual bool GetCombine(const NDb::EFaction faction) const;

      virtual void SetMode(const EVisMapMode::Type value);
      virtual void SetCombine(const NDb::EFaction faction, const bool combine);

      virtual void Update();

      virtual bool IsPointVisible(const CVec2& pos) const;
    private:
      void Combine();

      bool IsPointVisibleOnCombinedMapImpl(const CVec2& pos) const;

      NWorld::FogOfWar::VisMap combinedVisMap;
      NWorld::FogOfWar::VisMapMask combinedVisMapMask;

      unsigned combineFactionsMask;
      unsigned combineRevision;

      EVisMapMode::Type combineFallbackMode;
    };
  }

class VisibilityMapClient
  : public CObjectBase
  , public Render::DeviceLostHandler
  , public DI::SelfProvider<VisibilityMapClient>
{
  OBJECT_METHODS( 0x8B7A4380, VisibilityMapClient );

public:
  typedef Render::DeviceLostWrapper<VisibilityMapClient> Wrapped;

  static bool SetVisMapMode(int visMapMode);
  static int GetVisMapMode();
  static int GetVisMapAllMode();

  virtual void                  Update(float timeDelta);
  
  static int GetStepCountDelay() { return 4; } //возвращаем номер степа, на котором варфог уже полностью сформирован - подобран эмпирическим путем.
  const Render::Texture2DRef&   GetTextureSrc()     { return m_texSource; }
  const Render::Texture2DRef&   GetTexture()        { return m_texBlended; }
  const Render::Texture2DRef&   GetTexture(int i)   { return m_texStep[i == m_texIndex]; }
  float                      GetMiniMapAlphaScale();

  void OnRender();

  void SetSpectatorMode(const bool value);

  bool IsPointVisible( const CVec2& pos) const
  {
    NI_VERIFY(!!controller, "Controller must be set!", return false);

    return controller->IsPointVisible(pos);
  }

  EVisMapMode::Type GetMode() const
  {
    NI_VERIFY(!!controller, "Controller must be set!", return EVisMapMode::Undefined);

    return controller->GetMode();
  }

  void SetMode(const EVisMapMode::Type mode) const
  {
    NI_VERIFY(!!controller, "Controller must be set!", return);

    controller->SetMode(mode);
  }

  bool IsSharedVisionMode() const
  {
    return (GetMode() == EVisMapMode::Combined);
  }

  bool IsSharedVisionFaction(const NDb::EFaction faction) const
  {
    NI_VERIFY(!!controller, "Controller must be set!", return false);

    return controller->GetCombine(faction);
  }

  // From Render::DeviceLostHandler
  virtual void OnDeviceLost()  { m_initialized = false; m_disabled = true; }
  virtual void OnDeviceReset() {}

protected:
  VisibilityMapClient() : m_warfogParams() {}
  explicit VisibilityMapClient(NWorld::PFWorld * _world);

  ~VisibilityMapClient();
private:

  enum FillStage { FS_INIT, FS_STEP, FS_END };

  CPtr<NWorld::PFWorld>   world;
  int currentworldStep;

  Render::Texture2DRef    m_texSource;        // Result blended texture
  Render::Texture2DRef    m_texStep[2];       // Textures, received on Step's
  Render::Texture2DRef    m_texBlended;       // Result blended texture
  float                   m_ratio;
  int                     m_texIndex;
  int                     m_stepNumber;           // To know which texture from [2] should be modified

  CVec4                   m_warfogMapping;        // Shader parameters for WarFog

  struct WarFogParams* const m_warfogParams;         // Shader parameters for WarFog

  bool                    m_created;
  bool                    m_disabled;
  bool                    m_initialized;
  bool                    m_doBlur;

  NDb::Ptr<NDb::LightEnvironment> lightEnvironment;

  static const int FILTER_SIDE = 3;
  CVec4 filterKernel[1 + FILTER_SIDE * FILTER_SIDE / 2];
  Render::Blur9 blurEffect;

  int                     numUpdatesBetweenSteps; // Number of updates between 2 steps
  int                     indexUpdateCur;         // Index of current update

  typedef AutoPtr<Detail::VisMapClientController> ControllerPtr;

  ControllerPtr           controller;

  DI_WEAK(NWorld::FogOfWar) fogOfWar;

  void InitRenderResources();
  void OnStep();
  bool OnCreate(int texSideX, int texSideY, NScene::IScene * scene);
  void ClearTextures();
  void FillTexture(Render::Texture2DRef const& pTexture, FillStage stage = FS_STEP);
  void BlendTextures();

  void OnLightingEnvironmentChanged( const string& );
};

}
