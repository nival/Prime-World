#include "stdafx.h"
#include "Minimap.h"
#include "AdventureScreen.h"
#include "PFClientVisibilityMap.h"
#include "PFClientNatureMap.h"
#include "AdventureFlashInterface.h"

#include "UI/SkinStyles.h"
#include "UI/FlashContainer2.h"
#include "UI/Resolution.h"

#include "Render/dxutils.h"
#include "Render/renderer.h" 
#include "Render/smartrenderer.h"
#include "Render/vertexformatdescriptor.h"
#include "Render/renderresourcemanager.h"
#include "Render/uirenderer.h"
#include "Render/UITextureCacheInterface.h"

#include "Sound/EventScene.h"

#include "Render/ImmediateRenderer.h"

#include "ClientVisibilityHelper.h"

namespace
{
  DECLARE_NULL_RENDER_FLAG

  DEV_VAR_STATIC bool g_showCameraBox = false;
  REGISTER_DEV_VAR( "show_camera_box", g_showCameraBox, STORAGE_NONE );

  static bool g_showAllSignalsInSharedVision = false;
  REGISTER_VAR("show_all_signals_in_shared_vision", g_showAllSignalsInSharedVision, STORAGE_NONE);
}

namespace
{
  const Render::Color WHITE(0xFF, 0xFF, 0xFF, 0xFF);
}

namespace NGameX
{
  class Minimap::Presentation : public NonCopyable
  {
  public:
    virtual ~Presentation()
    {
    }

    virtual void Clear() = 0;

    virtual Minimap::Object& AddObject(const int layerIndex) = 0;

    virtual void PushObjects() const = 0;
    virtual void PushObject(const int layerIndex, const Minimap::Object& object) const = 0;

    virtual bool ShouldDisplaySignal(const NDb::EFaction faction) const = 0;
    virtual void PrepareSignal(const NDb::EFaction faction, Minimap::Signal& signal) const {}

    virtual int GetObjectLayerIndex(const NDb::EUnitType unitType, const NDb::EFaction faction, const int icon) const = 0;
    virtual int GetObjectLayerIndex(const ObjectInfo& objectInfo, const int icon) const = 0;
  protected:
    explicit Presentation(Minimap& minimap)
      : minimap(minimap)
    {
    }

    template <int LayerCount>
    static Minimap::Object& AddObjectImpl(Minimap::Layer (&layers)[LayerCount], const int layerIndex)
    {
      static Minimap::Object dummy;

      NI_VERIFY(layerIndex >= 0, "Invalid layer index!", return dummy);
      NI_VERIFY(layerIndex < LayerCount, "Invalid layer index!", return dummy);

      return layers[layerIndex].push_back();
    }

    template <int LayerCount>
    void PushObjectsImpl(const Minimap::Layer (&layers)[LayerCount]) const
    {
      for (int layerIndex = 0; layerIndex < LayerCount; ++layerIndex)
      {
        const Minimap::Layer& layer = layers[layerIndex];

        Minimap::Layer::const_iterator it = layer.begin();
        Minimap::Layer::const_iterator it_end = layer.end();
        for (; it != it_end; ++it)
        {
          PushObject(layerIndex, *it);
        }
      }
    }

    template <int LayerCount>
    static void ClearImpl(Minimap::Layer (&layers)[LayerCount])
    {
      for (int layerIndex = 0; layerIndex < LayerCount; ++layerIndex)
      {
        Minimap::Layer& layer = layers[layerIndex];

        layer.clear();
      }
    }

    void PushObjectImpl(const CVec2& pos, const Render::Color& color, const Minimap::IconDesc& icon) const
    {
      minimap._AddRect(pos.x, pos.y, color, icon.texture, icon.uv1, icon.uv2);
    }

    NDb::EFaction GetFaction() const
    {
      if (!IsValid(minimap.localHero))
        return NDb::FACTION_NEUTRAL;

      return minimap.localHero->GetFaction();
    }

    Minimap& minimap;
  private:
    Presentation();
  };

  class Minimap::FactionPresentation : public Presentation
  {
    struct ELayerIndex
    {
      enum
      {
        Default,
        Icon,
        Goal,
        FreezeHero,
        BurnHero,
        Last,
      };
    };
  public:
    explicit FactionPresentation(Minimap& minimap)
      : Presentation(minimap)
      , freezeHeroFrame(minimap.allyFrameIcon)
      , burnHeroFrame(minimap.enemyFrameIcon)
      , localHeroFrame(minimap.selfFrameIcon)
    {
      for (int layerIndex = 0; layerIndex < ELayerIndex::Last; ++layerIndex)
      {
        Minimap::Layer& layer = layers[layerIndex];

        switch (layerIndex)
        {
        case ELayerIndex::Default:
        case ELayerIndex::Icon:
          layer.reserve(128);
          break;
        case ELayerIndex::Goal:
          layer.reserve(32);
          break;
        case ELayerIndex::FreezeHero:
        case ELayerIndex::BurnHero:
          layer.reserve(5);
          break;
        }
      }
    }

    virtual Minimap::Object& AddObject(const int layerIndex)
    {
      return AddObjectImpl(layers, layerIndex);
    }

    virtual void PushObjects() const
    {
      PushObjectsImpl(layers);
    }

    virtual void PushObject(const int layerIndex, const Minimap::Object& object) const
    {
      switch (object.unitType)
      {
      case NDb::UNITTYPE_HEROMALE:
      case NDb::UNITTYPE_HEROFEMALE:
        if (!minimap.IsValidHeroIcon(object.icon))
          break;

        switch (layerIndex)
        {
        case ELayerIndex::FreezeHero:
          PushObjectImpl(object.pos, WHITE, freezeHeroFrame);
          break;
        case ELayerIndex::BurnHero:
          PushObjectImpl(object.pos, WHITE, burnHeroFrame);
          break;
        default:
          break;
        }

        PushObjectImpl(object.pos, WHITE, minimap.heroIcons[object.icon]);

        return;
      default:
        if (!minimap.IsValidIcon(object.icon))
          break;

        PushObjectImpl(object.pos, WHITE, minimap.icons[object.icon]);

        return;
      }

      switch (object.faction)
      {
      case NDb::FACTION_NEUTRAL:
        PushObjectImpl(object.pos, minimap.minimapData->neutralColor, minimap.whiteIcon);
        break;
      case NDb::FACTION_FREEZE:
        PushObjectImpl(object.pos, minimap.minimapData->allyColor, minimap.whiteIcon);
        break;
      case NDb::FACTION_BURN:
        PushObjectImpl(object.pos, minimap.minimapData->enemyColor, minimap.whiteIcon);
        break;
      }
    }

    virtual bool ShouldDisplaySignal(const NDb::EFaction faction) const
    {
      if (!g_showAllSignalsInSharedVision || !ClientVisibilityHelper::IsSharedVisionMode())
      {
        return (faction == GetFaction());
      }

      switch (faction)
      {
      case NDb::FACTION_FREEZE:
      case NDb::FACTION_BURN:
        return true;
      default:
        return false;
      }
    }

    virtual void PrepareSignal(const NDb::EFaction faction, Minimap::Signal& signal) const
    {
      if (!g_showAllSignalsInSharedVision || !ClientVisibilityHelper::IsSharedVisionMode())
      {
        return;
      }

      switch (faction)
      {
      case NDb::FACTION_FREEZE:
        signal.color = minimap.minimapData->allyColor;
        break;
      case NDb::FACTION_BURN:
        signal.color = minimap.minimapData->enemyColor;
        break;
      default:
        break;
      }
    }

    virtual int GetObjectLayerIndex(const NDb::EUnitType unitType, const NDb::EFaction faction, const int icon) const
    {
      switch (unitType)
      {
      case NDb::UNITTYPE_HEROMALE:
      case NDb::UNITTYPE_HEROFEMALE:
        switch (faction)
        {
        case NDb::FACTION_FREEZE:
          return ELayerIndex::FreezeHero;
        case NDb::FACTION_BURN:
          return ELayerIndex::BurnHero;
        default:
          return ELayerIndex::Icon;
        }
      case NDb::UNITTYPE_TOWER:
      case NDb::UNITTYPE_BUILDING:
      case NDb::UNITTYPE_MAINBUILDING:
      case NDb::UNITTYPE_SHOP:
        return ELayerIndex::Icon;
      case NDb::UNITTYPE_PICKUPABLE:
        return ELayerIndex::Goal;
      case NDb::UNITTYPE_MINIGAMEPLACE:
        return ELayerIndex::Icon;
      default:
        if (icon > 0)
          return ELayerIndex::Icon;
        else
          return ELayerIndex::Default;
      }
    }

    virtual int GetObjectLayerIndex(const ObjectInfo& objectInfo, const int icon) const
    {
      switch (objectInfo.kind)
      {
      case EObjectKind::Hero:
      case EObjectKind::LocalHero:
        switch (objectInfo.faction)
        {
        case NDb::FACTION_FREEZE:
          return ELayerIndex::FreezeHero;
        case NDb::FACTION_BURN:
          return ELayerIndex::BurnHero;
        default:
          return ELayerIndex::Icon;
        }
      case EObjectKind::Glyph:
      case EObjectKind::NatureGlyph:
      case EObjectKind::Consumable:
        return ELayerIndex::Goal;
      default:
        if (icon > 0)
          return ELayerIndex::Icon;
        else
          return ELayerIndex::Default;
      }
    }

    virtual void Clear()
    {
      ClearImpl(layers);
    }
  private:
    Minimap::Layer layers[ELayerIndex::Last];

    Minimap::IconDesc& freezeHeroFrame;
    Minimap::IconDesc& burnHeroFrame;
    Minimap::IconDesc& localHeroFrame;
  };

  class Minimap::FriendOrFoePresentation : public Presentation
  {
    struct ELayerIndex
    {
      enum
      {
        Default,
        Icon,
        Goal,
        EnemyHero,
        AllyHero,
        LocalHero,
        Last,
      };
    };
  public:
    explicit FriendOrFoePresentation(Minimap& minimap)
      : Presentation(minimap)
      , allyHeroFrame(minimap.allyFrameIcon)
      , enemyHeroFrame(minimap.enemyFrameIcon)
      , localHeroFrame(minimap.selfFrameIcon)
    {
      for (int layerIndex = 0; layerIndex < ELayerIndex::Last; ++layerIndex)
      {
        Minimap::Layer& layer = layers[layerIndex];

        switch (layerIndex)
        {
        case ELayerIndex::Default:
        case ELayerIndex::Icon:
          layer.reserve(128);
          break;
        case ELayerIndex::Goal:
          layer.reserve(32);
          break;
        case ELayerIndex::EnemyHero:
        case ELayerIndex::AllyHero:
          layer.reserve(5);
          break;
        case ELayerIndex::LocalHero:
          layer.reserve(1);
          break;
        }
      }
    }

    virtual Minimap::Object& AddObject(const int layerIndex)
    {
      return AddObjectImpl(layers, layerIndex);
    }

    virtual void PushObjects() const
    {
      PushObjectsImpl(layers);
    }

    virtual void PushObject(const int layerIndex, const Minimap::Object& object) const
    {
      switch (object.unitType)
      {
      case NDb::UNITTYPE_HEROMALE:
      case NDb::UNITTYPE_HEROFEMALE:
        if (!minimap.IsValidHeroIcon(object.icon))
          break;

        switch (layerIndex)
        {
        case ELayerIndex::EnemyHero:
          PushObjectImpl(object.pos, WHITE, enemyHeroFrame);
          break;
        case ELayerIndex::AllyHero:
          PushObjectImpl(object.pos, WHITE, allyHeroFrame);
          break;
        case ELayerIndex::LocalHero:
          PushObjectImpl(object.pos, WHITE, localHeroFrame);
          break;
        default:
          break;
        }

        PushObjectImpl(object.pos, WHITE, minimap.heroIcons[object.icon]);

        return;
      default:
        if (!minimap.IsValidIcon(object.icon))
          break;

        PushObjectImpl(object.pos, WHITE, minimap.icons[object.icon]);

        return;
      }

      if (object.faction == NDb::FACTION_NEUTRAL)
      {
        PushObjectImpl(object.pos, minimap.minimapData->neutralColor, minimap.whiteIcon);
      }
      else
      {
        if (object.faction == GetFaction())
          PushObjectImpl(object.pos, minimap.minimapData->allyColor, minimap.whiteIcon);
        else
          PushObjectImpl(object.pos, minimap.minimapData->enemyColor, minimap.whiteIcon);
      }
    }

    virtual bool ShouldDisplaySignal(const NDb::EFaction faction) const
    {
      switch (faction)
      {
      case NDb::FACTION_FREEZE:
      case NDb::FACTION_BURN:
        return (faction == GetFaction());
      default:
        return false;
      }
    }

    virtual int GetObjectLayerIndex(const NDb::EUnitType unitType, const NDb::EFaction faction, const int icon) const
    {
      switch (unitType)
      {
      case NDb::UNITTYPE_HEROMALE:
      case NDb::UNITTYPE_HEROFEMALE:
        if (faction == GetFaction())
          return ELayerIndex::AllyHero;
        else
          return ELayerIndex::EnemyHero;
      case NDb::UNITTYPE_TOWER:
      case NDb::UNITTYPE_BUILDING:
      case NDb::UNITTYPE_MAINBUILDING:
      case NDb::UNITTYPE_SHOP:
        return ELayerIndex::Icon;
      case NDb::UNITTYPE_PICKUPABLE:
        return ELayerIndex::Goal;
      case NDb::UNITTYPE_MINIGAMEPLACE:
        return ELayerIndex::Icon;
      default:
        if (icon > 0)
          return ELayerIndex::Icon;
        else
          return ELayerIndex::Default;
      }
    }

    virtual int GetObjectLayerIndex(const ObjectInfo& objectInfo, const int icon) const
    {
      switch (objectInfo.kind)
      {
      case EObjectKind::LocalHero:
        return ELayerIndex::LocalHero;
      case EObjectKind::Hero:
        if (objectInfo.faction == GetFaction())
          return ELayerIndex::AllyHero;
        else
          return ELayerIndex::EnemyHero;
      case EObjectKind::Glyph:
      case EObjectKind::NatureGlyph:
      case EObjectKind::Consumable:
        return ELayerIndex::Goal;
      default:
        if (icon > 0)
          return ELayerIndex::Icon;
        else
          return ELayerIndex::Default;
      }
    }

    virtual void Clear()
    {
      ClearImpl(layers);
    }
  private:
    Minimap::Layer layers[ELayerIndex::Last];

    Minimap::IconDesc& allyHeroFrame;
    Minimap::IconDesc& enemyHeroFrame;
    Minimap::IconDesc& localHeroFrame;
  };
}

namespace NGameX
{
#pragma pack(push, 1)

struct Minimap::Vertex
{
  float x;
  float y;
  float u;
  float v;
  Render::Color color;
};

struct Minimap::Quad
{
  Vertex v0;
  Vertex v1;
  Vertex v2;
  Vertex v3;
  Vertex v4;
  Vertex v5;
};

#pragma pack(pop)

// Maximum number of render elements
enum
{
  MaxTriangles = 1024
};

Minimap::Minimap()
  : textureWidth(256)
  , textureHeight(256)
  , targetZoneDisplay(false)
  , targetZoneRange(0.f)
{
  ClearAll();

  queue.reserve( 64 );
}



Minimap::Minimap( UI::FlashContainer2 * _flashWnd, AdventureFlashInterface* _flashInterface )
  : flashWnd(_flashWnd)
  , flashInterface(_flashInterface)
  , textureWidth(256)
  , textureHeight(256)
  , localHero()
  , targetZoneDisplay(false)
  , targetZoneRange(0.f)
{
  PushDXPoolGuard dxPool("UI");

  queue.reserve( 64 );

  ClearAll();

  // Check if compiler made any padding
  NI_STATIC_ASSERT( sizeof(Vertex) == 20, VertexStride_size_wrong );

  if(RENDER_DISABLED)
    return;

  // Initialize vertex format
  {
    Render::VertexFormatDescriptor formatDescriptor;
    formatDescriptor.AddVertexElement( Render::VertexElementDescriptor( 0, 0, Render::VERTEXELEMENTTYPE_FLOAT2, Render::VERETEXELEMENTUSAGE_POSITION, 0 ) );
    formatDescriptor.AddVertexElement( Render::VertexElementDescriptor( 0, 8, Render::VERTEXELEMENTTYPE_FLOAT2, Render::VERETEXELEMENTUSAGE_TEXCOORD, 0 ) );
    formatDescriptor.AddVertexElement( Render::VertexElementDescriptor( 0, 16, Render::VERTEXELEMENTTYPE_D3DCOLOR, Render::VERETEXELEMENTUSAGE_COLOR, 0 ) );

    m_vertexDeclaration = Render::SmartRenderer::GetVertexFormatDeclaration( formatDescriptor );

    m_cameraDip.primitiveType            = Render::RENDERPRIMITIVE_LINESTRIP;
    m_cameraDip.numVertices              = 10;
    m_cameraDip.primitiveCount           = 9;
    m_cameraDip.startIndex               = 0;
    m_cameraDip.baseVertexIndex          = 0;
    m_cameraDip.minIndex                 = 0;
  }

  m_cameraVB.Resize( 10 * sizeof(Vertex) );
  NI_VERIFY(::Get(m_cameraVB), "Minimap: Failed to create vertex buffer!", return );

  // Create vertex buffer
  m_vb.Resize( 3 * MaxTriangles * sizeof(Vertex) );
  NI_VERIFY(::Get(m_vb), "Minimap: Failed to create vertex buffer!",	return );

  m_renderState.SetBlendMode( NDb::BLENDMODE_LERPBYALPHA );
  m_renderState.SetAlphaTest( NDb::ONOFFSTATE_OFF );

  //m_mapSize = mapSize;
  m_minimapSampler.SetAddressU( NDb::TEXTUREADDRESSTYPE_CLAMP );
  m_minimapSampler.SetAddressV( NDb::TEXTUREADDRESSTYPE_CLAMP );
  m_minimapSampler.SetMinFilter( NDb::MINFILTERTYPE_LINEAR );
  m_minimapSampler.SetMagFilter( NDb::MAGFILTERTYPE_LINEAR );
  m_minimapSampler.SetMipFilter( NDb::MIPFILTERTYPE_NONE );

  m_minimapTexture = Render::Load2DTextureFromFile( "UI/Textures_default/AdvMap/minimap_icons.dds" ); 

  InitializeMinimapTexture();

  NDb::SamplerState sampleState;
  sampleState.mipFilter = NDb::MIPFILTERTYPE_NONE;
  sampleState.magFilter = NDb::MAGFILTERTYPE_POINT;
  sampleState.minFilter = NDb::MINFILTERTYPE_POINT;

  renderMaterial.CreateDefaultMaterial();
  renderMaterial.GetRenderMaterial()->GetDiffuseMap()->SetTexture( m_minimapTexture );
  renderMaterial.GetRenderMaterial()->GetDiffuseMap()->SetSamplerState( sampleState );
  renderMaterial.GetRenderMaterial()->SetUseDiffuse( NDb::BOOLEANPIN_PRESENT );
  renderMaterial.GetRenderMaterial()->ModifyColor( Render::HDRColor(1.f, 1.f, 1.f, 1.f), Render::HDRColor(1.f, 1.f, 1.f, 1.f) );

  cameraMaterial.CreateDefaultMaterial();
  cameraMaterial.GetRenderMaterial()->ModifyColor( Render::HDRColor(1.f, 1.f, 1.f, 1.f), Render::HDRColor(1.f, 1.f, 1.f, 1.f) );

  heroIcons.reserve(10);  // Reserve place for standard amount of heroes (do we have a constant for this?)
}


Minimap::~Minimap()
{

}


void Minimap::InitializeMinimapTexture()
{
  if ( IsValid( flashWnd ) )
  {
    int x, y;
    flashWnd->GetDisplayObjectSize( "miniMap_mc.miniMapAnim_mc.roundFrame", textureWidth, textureHeight, x, y );
    UI::Point screenSize = UI::ConvertToScreen( UI::Point( textureWidth, textureHeight ) );
    textureWidth = screenSize.x; 
    textureHeight = screenSize.y;
  }

  m_targetTexture  = Render::CreateRenderTexture2D( textureWidth, textureHeight, Render::FORMAT_A8R8G8B8 );

  invTargetSize.x = 1.f / static_cast<float>(m_targetTexture->GetWidth());
  invTargetSize.y = 1.f / static_cast<float>(m_targetTexture->GetHeight());

  if ( IsValid( flashWnd ) )
  {
    flashWnd->ChangeTexture( "miniMap_mc.miniMapAnim_mc.mapImage", GetTargetTexture() );
    flashWnd->SetTextureSmooth( "miniMap_mc.miniMapAnim_mc.mapImage", false );
    flashWnd->CallMethod0( "miniMap_mc.miniMapAnim_mc", "correctSize" );
  }

  if ( renderMaterial.GetRenderMaterial() )
    renderMaterial.GetRenderMaterial()->GetDiffuseMap()->SetTexture( m_minimapTexture );
}


void Minimap::ClearAll()
{
  m_updated = false;
  m_over = false;
 
  m_vertices = 0;
  m_lastIndex = 0;
  m_numTriangles = 0;
  localHero = 0;

  m_worldSize = CVec2( 0, 0 );
  m_mapRotation = ToRadian( 0.0f );
  m_worldToLocal = CVec2( 0.0f, 0.0f );
  m_localToWorld = CVec2( 0.0f, 0.0f );
  m_mapRotationSin = 0.0f;
  m_mapRotationCos = 0.0f;
  m_offset = CVec2( 0.0f, 0.0f );
  m_scale  = 1.0f;

  for ( int i = 0; i < 4; ++i )
    m_natureMapPolygon[i].Set(0.0f, 0.0f);

  SetSpectatorMode(false);
}

void Minimap::InitSpecialTextures()
{
  Weak<Render::IUITextureCache> cache = Render::GetUIRenderer()->GetTextureCache();

  unsigned char whiteData[64];
  memset( whiteData, 255, 64 );

  whiteIcon.texture = cache->PlaceImageToAtlas( whiteData, 4, 4, whiteIcon.uv1, whiteIcon.uv2, false );

  Render::Texture2DRef textureEnemy = Render::LoadTexture2D( *minimapData->enemyHeroFrame );
  Render::Texture2DRef textureAlly = Render::LoadTexture2D( *minimapData->allyHeroFrame );
  Render::Texture2DRef textureSelf;

  if (IsValid(minimapData->localHeroFrame))
    textureSelf = Render::LoadTexture2D(*minimapData->localHeroFrame);
  else
    textureSelf = textureAlly;

  enemyFrameIcon.texture = cache->PlaceTextureToAtlas( textureEnemy, enemyFrameIcon.uv1, enemyFrameIcon.uv2 );
  allyFrameIcon.texture = cache->PlaceTextureToAtlas( textureAlly, allyFrameIcon.uv1, allyFrameIcon.uv2 );
  selfFrameIcon.texture = cache->PlaceTextureToAtlas(textureSelf, selfFrameIcon.uv1, selfFrameIcon.uv2);
}

void Minimap::InitAndSetImages( const NDb::DBMinimap * _minimapData, const NDb::MinimapImages * _images )
{
  if(RENDER_DISABLED)
    return;

  minimapData = _minimapData;
  minimapImages = _images;
  NI_VERIFY( minimapData, "Minimap images are null", return );

  Weak<Render::IUITextureCache> cache = Render::GetUIRenderer()->GetTextureCache();

  InitNatureMapParams( _images );
  InitSpecialTextures();

  const int iconCount = NDb::KnownEnum<NDb::EMinimapIcons>::SizeOf();

  icons.resize(iconCount);

  for ( int i = 0; i < iconCount; ++i )
  {
    NDb::Ptr<NDb::Texture> icon = minimapData->icons[i];

    if (!icon)
      continue;

    Render::Texture2DRef texture = Render::LoadTexture2D(*icon);

    IconDesc& desc = icons[i];

    desc.texture = cache->PlaceTextureToAtlas(texture, desc.uv1, desc.uv2 );
  }

  if (IsValid(flashInterface))
  {
    flashInterface->SetMinimapTargetZoneColor(minimapData->targetZoneColor.Dummy);
    flashInterface->SetMinimapTargetZoneThickness(Max(0, minimapData->targetZoneLineThickness));
  }
}



void Minimap::SetWorldSize( const CVec2 & size )
{
  m_worldSize = size;

  SetupViewParameters();
}



void Minimap::SetMinimapRotation( float angle )
{
  m_mapRotation = angle;

  SetupViewParameters();
}


void Minimap::SetLocalHero(const NWorld::PFBaseHero* const _hero)
{
  localHero = _hero;
}


/*
rotto := { c, -s, 0; s, c, 0; 0, 0, 1 };
rotfrom := { c, s, 0; -s, c, 0; 0, 0, 1 };
toworld := { wx, 0, 0; 0, wy, 0; 0, 0, 1 };
fromworld := { 1/wx, 0,  0; 0, 1/wy, 0; 0, 0, 1 };
tocenter := { 1, 0, -0.5; 0, 1, -0.5; 0, 0, 1 };
fromcenter := { 1, 0, +0.5; 0, 1, +0.5; 0, 0, 1 };
tominimap := fromcenter * rotfrom * tocenter * fromworld;
fromminimap := toworld * fromcenter * rotto * tocenter;
*/


void Minimap::SetupViewParameters()
{
  if (m_worldSize.x <= 0.0f || m_worldSize.y <= 0.0f)
    return;

  // Get scale and offset. 
  // If dbImages isn't set, the default will be used, which set by ClearAll
  if ( minimapImages )
  {
    // Ignore uninitialized or wrong offset
    if (minimapImages->centerOffset.x < m_worldSize.x && m_worldSize.x > -m_worldSize.x
        && minimapImages->centerOffset.y < m_worldSize.y && m_worldSize.y > -m_worldSize.y)
    {
      m_offset = minimapImages->centerOffset;
    }

    m_scale  = Clamp<float>(minimapImages->scaleFactor, 0.5f, 2.0f);
  }

  // Store frequently used cos and sin values
  m_mapRotationSin = sin(m_mapRotation);
  m_mapRotationCos = cos(m_mapRotation);

  // Setup world to minimap and minimap to world translation vectors
  m_worldToLocal.x = 2.0f / m_worldSize.x;
  m_worldToLocal.y = 2.0f / m_worldSize.y;
  m_localToWorld.x = m_worldSize.x / 2.0f;
  m_localToWorld.y = m_worldSize.y / 2.0f;

  // Calculate offset for minimap texture polygon calculation
  float sinAngle = sin(-m_mapRotation);
  float cosAngle = cos(-m_mapRotation);
  float offsetX = m_offset.x * m_worldToLocal.x;
  float offsetY = m_offset.y * m_worldToLocal.y;
  CVec2 offset = CVec2(offsetX*cosAngle - offsetY*sinAngle, offsetX*sinAngle + offsetY*cosAngle);

  // Setup polygon for minimap texture rendering
  for ( int i = 0; i < 4; ++i )
  {
    const float a = -m_mapRotation + FP_PI4 + i * FP_PI2;
    m_natureMapPolygon[i].Set( m_scale * (SQRT_2 * cosf( a ) + offset.x), m_scale * (SQRT_2 * sinf( a ) + offset.y) );
  }
}


void Minimap::Ui2World( float x, float y, CVec3 & result ) const
{
  y = 1.0f - y;
  x = Clamp<float>(x, 0.0f, 1.0f);
  y = Clamp<float>(y, 0.0f, 1.0f);
  CVec2 mmap (x * 2.0f, y * 2.0f);

  LocalToWorld( mmap, result );  
}


void Minimap::World2Ui( const CVec3 & world, CVec2 & result ) const
{
  WorldToLocal( world, result );

  result /= 2.0f;
  result.y = 1.0f - result.y;
}


void Minimap::LocalToWorld( CVec2 p, CVec3 & result ) const
{
  // Put minimap center at (0,0)
  p.x -= 1.0f;
  p.y -= 1.0f;

  // Remove scaling
  p /= m_scale;

  // Rotate to zero angle and put center back to (1,1)
  result.x = p.x * m_mapRotationCos - p.y * m_mapRotationSin + 1.0f;
  result.y = p.x * m_mapRotationSin + p.y * m_mapRotationCos + 1.0f;

  // Translate to world coordinates
  result.x *= m_localToWorld.x;
  result.y *= m_localToWorld.y;

  // Remove offset
  result.x -= m_offset.x;
  result.y -= m_offset.y;
}

CVec3 Minimap::LocalToWorld(const CVec2& p) const
{
  CVec3 q;

  LocalToWorld(p, q);

  return q;
}


void Minimap::WorldToLocal( CVec3 p, CVec2 & result ) const
{
  // Apply offset
  p.x += m_offset.x;
  p.y += m_offset.y;

  // Translate to minimap coordinates with center at (0,0)
  float worldX = p.x * m_worldToLocal.x - 1.0f;
  float worldY = 2.0f - p.y * m_worldToLocal.y - 1.0f;

  // Rotate to minimap view angle
  result.x = worldX * m_mapRotationCos - worldY * m_mapRotationSin;
  result.y = worldX * m_mapRotationSin + worldY * m_mapRotationCos;

  // Scale the coordinates
  result *= m_scale;

  // Put center back to (1,1)
  result.x += 1.0f;
  result.y += 1.0f;
}

CVec2 Minimap::WorldToLocal(const CVec3& p) const
{
  CVec2 q;

  WorldToLocal(p, q);

  return q;
}


bool Minimap::BeginUpdate( float deltaTime )
{
  NI_PROFILE_FUNCTION;

  NI_ASSERT(!!presentation, "Presentation must be defined!");

  UpdateSignals( deltaTime );
  UpdateTargetZone();

  presentation->Clear();

  queue.clear();

  return true;
}

template <typename T>
struct VertexBufferLock
{
  explicit VertexBufferLock(DXVertexBufferDynamicRef::Wrapped& vb, const unsigned flags = D3DLOCK_DISCARD, const int size = 0)
    : vb(vb)
    , data(0)
  {
    data = Render::LockVB<T>(::Get(vb), flags, size);
  }

  ~VertexBufferLock()
  {
    vb->Unlock();
  }

  operator T*()
  {
    return data;
  }

  operator T*() const
  {
    return data;
  }
private:
  VertexBufferLock();
  VertexBufferLock(const VertexBufferLock&);
  VertexBufferLock& operator=(const VertexBufferLock&);

  DXVertexBufferDynamicRef::Wrapped& vb;

  T* data;
};

bool Minimap::EndUpdate()
{
  NI_PROFILE_FUNCTION

  if ( !Render::GetRenderer()->DeviceIsLost() )
  {
    {
      const VertexBufferLock<Vertex> _lock1(m_vb);

      m_numTriangles = 0;
      m_lastIndex    = 0;
      m_vertices     = _lock1;
      m_updated      = false;

      if ( m_vertices )
        PrepareObjectsForRender();
    }
    

    {
      const VertexBufferLock<Vertex> _lock2(m_cameraVB);

      if (!!_lock2)
        _AddCameraFrame(_lock2);
    }
  }

  m_vertices = NULL;
  m_updated = true;

  return true;
}

void Minimap::PushChunk( const Render::Texture2DRef& texture )
{
  NI_ASSERT(texture, "Icon texture missing");

  if (queue.empty())
  {
    /* placeholder */
  }
  else
  {
    if (queue.back().texture == texture)
      return;
  }

  RenderChunk& chunk = queue.push_back();

  chunk.texture = texture;
  chunk.dip.startIndex = m_numTriangles * 3;
}

void Minimap::_AddRect(float _x, float _y, Render::Color color, const Render::Texture2DRef& texture, const CVec2& uv1, const CVec2& uv2)
{
  PushChunk(texture);

  NI_VERIFY(MaxTriangles - m_numTriangles >= 2, "Too many triangles", return);

  const CVec2& texelSize = invTargetSize;

  RenderChunk& chunk = queue.back();

  const float x = texelSize.x * (floor(_x / texelSize.x));
  const float y = texelSize.y * (floor(_y / texelSize.y));
  const float w = texelSize.x * (uv2.x - uv1.x) * float(texture->GetWidth());
  const float h = texelSize.y * (uv2.y - uv1.y) * float(texture->GetHeight());

  const float dx = texelSize.x * 0.5f;
  const float dy = texelSize.y * 0.5f;

  Quad& quad = *reinterpret_cast<Quad*>(m_vertices);

  quad.v0.x = x - w - dx;
  quad.v0.y = y - h - dy;
  quad.v0.u = uv1.u;
  quad.v0.v = uv1.v;
  quad.v0.color = color;

  quad.v1.x = x - w - dx;
  quad.v1.y = y + h - dy;
  quad.v1.u = uv1.u;
  quad.v1.v = uv2.v;
  quad.v1.color = color;

  quad.v2.x = x + w - dx;
  quad.v2.y = y + h - dy;
  quad.v2.u = uv2.u;
  quad.v2.v = uv2.v;
  quad.v2.color = color;

  quad.v3 = quad.v0;

  quad.v4 = quad.v2;

  quad.v5.x = x + w - dx;
  quad.v5.y = y - h - dy;
  quad.v5.u = uv2.u;
  quad.v5.v = uv1.v;
  quad.v5.color = color;

  m_vertices     += 6;
  m_numTriangles += 2;

  chunk.dip.numVertices     += 6;
  chunk.dip.primitiveCount  += 2;
}

void Minimap::_AddCameraFrame( Vertex * pBuffer )
{
  // @BVS@TODO Need normal access to renderable scene (or world)
  NGameX::AdventureScreen * screen = NGameX::AdventureScreen::Instance();
  NWorld::PFWorld * world = screen->GetWorld();

  const FrustumIntersection & fi = world->GetScene()->GetRenderScene()->GetCameraFrustumIntersection();
  const Render::AABB & fAABB = world->GetScene()->GetRenderScene()->GetFrustumAABB();

  int id = 0;
  
  for (; id < 4; ++id)
  {
    CVec2 v;
    WorldToLocal( CVec3( fi.points[id].x, fi.points[id].y, 0 ), v );

    pBuffer[id].x = v.x;
    pBuffer[id].y = v.y;
    pBuffer[id].color.Dummy = 0xFFFFFFFFUL;
  }

  pBuffer[id++] = pBuffer[0];

  if ( g_showCameraBox )
  {
    CVec2 v;

    WorldToLocal( CVec3( fAABB.center.x - fAABB.halfSize.x, fAABB.center.y - fAABB.halfSize.y, 0 ), v );
    pBuffer[id  ].x = v.x; pBuffer[id++].y = v.y;

    WorldToLocal( CVec3( fAABB.center.x + fAABB.halfSize.x, fAABB.center.y - fAABB.halfSize.y, 0 ), v );
    pBuffer[id  ].x = v.x; pBuffer[id++].y = v.y;

    WorldToLocal( CVec3( fAABB.center.x + fAABB.halfSize.x, fAABB.center.y + fAABB.halfSize.y, 0 ), v );
    pBuffer[id  ].x = v.x; pBuffer[id++].y = v.y;

    WorldToLocal( CVec3( fAABB.center.x - fAABB.halfSize.x, fAABB.center.y + fAABB.halfSize.y, 0 ), v );
    pBuffer[id  ].x = v.x; pBuffer[id++].y = v.y;
    
    WorldToLocal( CVec3( fAABB.center.x - fAABB.halfSize.x, fAABB.center.y - fAABB.halfSize.y, 0 ), v );
    pBuffer[id  ].x = v.x; pBuffer[id++].y = v.y;
  }
  else
  {
    for (; id < 10; ++id )
    {
      pBuffer[id] = pBuffer[0];
    }
  }
}

void Minimap::AddObject( NDb::EUnitType unitType, NDb::EFaction faction, const CVec3 & pos, int icon )
{
  NI_VERIFY(!!presentation, "Presentation must be defined!", return);

  if (icon == NDb::MINIMAPICONS_NONE)
    return;

  const int layerIndex = presentation->GetObjectLayerIndex(unitType, faction, icon);

  Object& object = presentation->AddObject(layerIndex);

  object.unitType = unitType;
  object.faction = faction;
  object.pos = WorldToLocal(pos);
  object.icon = icon;
}

void Minimap::AddObject(const NWorld::PFLogicObject* const logicObject, const int icon, const CVec3& offset /*= VNULL3*/)
{
  NI_VERIFY(!!presentation, "Presentation must be defined!", return);

  if (!logicObject)
    return;

  if (icon == NDb::MINIMAPICONS_NONE)
    return;

  NI_VERIFY(IsValid(objectInfoHelper), "ObjectInfoHelper must exist!", return);

  const ObjectInfo& info = objectInfoHelper->UpdateObjectInfo(logicObject);

  const int layerIndex = presentation->GetObjectLayerIndex(info, icon);

  Object& object = presentation->AddObject(layerIndex);

  object.unitType = info.unitType;
  object.faction = info.faction;
  object.pos = WorldToLocal(logicObject->GetPosition() + offset);
  object.icon = icon;
}

void Minimap::AddObject(const NWorld::PFBaseUnit* const unit, const int icon /*= DefaultUnitIcon*/, const CVec3& offset /*= VNULL3*/)
{
  NI_VERIFY(!!presentation, "Presentation must be defined!", return);

  if (!unit)
    return;

  if (icon == NDb::MINIMAPICONS_NONE)
    return;

  NI_VERIFY(IsValid(objectInfoHelper), "ObjectInfoHelper must exist!", return);

  const ObjectInfo& info = objectInfoHelper->UpdateObjectInfo(unit);

  const int actualIcon = (icon == DefaultUnitIcon) ? unit->GetMinimapIcon() : icon;
  const int layerIndex = presentation->GetObjectLayerIndex(info, actualIcon);

  Object& object = presentation->AddObject(layerIndex);

  object.unitType = info.unitType;
  object.faction = info.faction;
  object.pos = WorldToLocal(unit->GetPosition() + offset);
  object.icon = actualIcon;
}

void Minimap::PrepareObjectsForRender()
{
  NI_VERIFY(!!presentation, "Presentation must be defined!", return);

  presentation->PushObjects();
}

int  Minimap::AddHeroIcon( const NDb::Texture * icon )
{
  if (RENDER_DISABLED)
    return -1;
  if (!icon)
    return -1;

  //Во время реконнека идентификатор возвращаемый из данной функции никак не освобождается
  //и, что хуже, непонятно как вытаскивать текстуру после того, как она оказалась в IUITextureCache
  //или освобождать весь IUITextureCache, поэтому будем просто возвращать старый идентификатор
  for (int i = 0; i < heroIcons.size(); ++i)
  {
    HeroIconDesc const& desc = heroIcons[i];

    if (icon->GetDBID() == desc.originTextureId)
      return i;
  }

  Weak<Render::IUITextureCache> cache = Render::GetUIRenderer()->GetTextureCache();

  Render::Texture2DRef texture = Render::LoadTexture2D(*icon);

  HeroIconDesc& desc = heroIcons.push_back();

  desc.texture = cache->PlaceTextureToAtlas(texture, desc.uv1, desc.uv2);
  desc.originTextureId = icon->GetDBID();

  return (heroIcons.size() - 1);
}


void Minimap::_RenderMinimap()
{
  NGameX::AdventureScreen     *screen = NGameX::AdventureScreen::Instance();
  NWorld::PFWorld             *world  = screen->GetWorld();

  Render::RenderStatesManager& rsManager = *Render::GetStatesManager();

  rsManager.SetState(m_renderState);
  rsManager.SetStateDirect(D3DRS_ZENABLE, 0);

  Render::SmartRenderer::BindRenderTarget(m_targetTexture);

  _RenderNatureMap(); // Instead of clear =)

  Render::SmartRenderer::BindVertexDeclaration( m_vertexDeclaration );

  rsManager.SetSamplerState(0, m_minimapSampler);

  const CVec4 resolutionCoefs( 1.0f, 1.0f, 0.0f, 0.0f );
  Render::GetRenderer()->SetPixelShaderConstantsVector4( PSHADER_LOCALCONST3, resolutionCoefs );
  Render::GetRenderer()->SetVertexShaderConstantsVector4( VSHADER_LOCALCONST3, resolutionCoefs );
  //Clean combined transform matrix

  Render::GetRenderer()->SetVertexShaderConstantsMatrix( WORLD, SHMatrix( CVec3( -invTargetSize.x, +invTargetSize.y, 0.f ) ) );
  Render::GetRenderer()->SetVertexShaderConstantsFloat( VSHADER_LOCALCONST5, 0.0f );
  Render::GetRenderer()->SetVertexShaderConstantsFloat( VSHADER_LOCALCONST6, 1.0f );

  rsManager.SetStateDirect( D3DRS_ZENABLE, 0 );
  rsManager.SetStateDirect( D3DRS_ZWRITEENABLE, 0 );
  rsManager.SetStateDirect( D3DRS_ZFUNC, D3DCMP_LESSEQUAL );
  rsManager.SetStateDirect( D3DRS_SEPARATEALPHABLENDENABLE, TRUE );
  rsManager.SetStateDirect( D3DRS_SRCBLENDALPHA, D3DBLEND_ZERO );
  rsManager.SetStateDirect( D3DRS_DESTBLENDALPHA, D3DBLEND_ONE );

  // пока варфог еще полностью не сформирован, не будем рисовать объекты миникарты (иконки, камеру и тп)
  if (world->GetStepNumber() < NGameX::VisibilityMapClient::GetStepCountDelay())
  {
    /* placeholder */
  }
  else
  {
    // Render Camera Frame
    cameraMaterial.GetRenderMaterial()->PrepareRenderer();

    Render::SmartRenderer::BindVertexBuffer( 0, ::Get( m_cameraVB ), sizeof( Vertex ) );
    Render::SmartRenderer::DrawPrimitive(m_cameraDip);

    Render::SmartRenderer::BindVertexBuffer( 0, ::Get( m_vb ), sizeof( Vertex ) );

    Queue::iterator it = queue.begin();
    Queue::iterator it_end = queue.end();
    for (; it != it_end; ++it )
    {
      Queue::const_reference chunk = *it;

      renderMaterial.GetRenderMaterial()->GetDiffuseMap()->SetTexture( chunk.texture );
      renderMaterial.GetRenderMaterial()->PrepareRenderer();
      rsManager.SetState( m_renderState );

      Render::SmartRenderer::DrawPrimitive( chunk.dip );
    }
  }

  rsManager.SetStateDirect( D3DRS_SEPARATEALPHABLENDENABLE, FALSE );
}



void Minimap::_RenderNatureMap()
{
  // @BVS@TODO Ask Vlad to move this code to his system
  NGameX::AdventureScreen     *screen = NGameX::AdventureScreen::Instance();
  NWorld::PFWorld             *world  = screen->GetWorld();
  NWorld::PFWorldNatureMap    *natMap = world->GetNatureMap();
  NGameX::PFClientNatureMap   *natMapClient = (NGameX::PFClientNatureMap*)natMap->ClientObject();
  NGameX::VisibilityMapClient *visMapClient = screen->GetClientVisibilityMap();

  Render::RenderStatesManager &rsManager = *Render::GetStatesManager();
  rsManager.SetState( Render::RenderState::NoBlendNoTest() );
  rsManager.SetStateDirect( D3DRS_ZENABLE, 0 );
  rsManager.SetStateDirect( D3DRS_SEPARATEALPHABLENDENABLE, FALSE );

  rsManager.SetSampler( 0, m_natureSampler, m_natureTextureA );
  rsManager.SetSampler( 1, m_natureSampler, m_natureTextureB );
  rsManager.SetSampler( 2, m_natureSampler, m_natureTextureN );
  rsManager.SetSampler( 3, m_natureSampler, natMapClient->GetTexture() );
  // пока варфог еще полностью не сформирован, используем исходную текстуру, на которой по началу вся карта под варфогом
  if (world->GetStepNumber() < NGameX::VisibilityMapClient::GetStepCountDelay())
    rsManager.SetSampler( 4, m_natureSampler, visMapClient->GetTextureSrc() );
  else  
    rsManager.SetSampler( 4, m_natureSampler, visMapClient->GetTexture() );

  //Render::GetRenderer()->SetPixelShaderConstantsHDRColor( PSHADER_LOCALCONST0, Render::HDRColor( 0.0f, 0.0f, 0.0f, 0.75f ) );
  Render::GetRenderer()->SetPixelShaderConstantsFloat( PSHADER_LOCALCONST0, visMapClient->GetMiniMapAlphaScale() );

  Render::GetImmRenderer()->RenderScreenQuad( m_natureMapPolygon, Render::ImmRenderer::Params( "NatureMap" ) );
}



void Minimap::Render()
{
  if (!m_updated)
    return;

  Render::LogMarker("Minimap");

  _RenderMinimap();
}

void Minimap::AddSignalInternal( const CVec2 & pos, NDb::EFaction faction, float lifeTime )
{
  NI_VERIFY(!!presentation, "Presentation must be defined!", return);

  if (!presentation->ShouldDisplaySignal(faction))
    return;

  const Render::Color& color = IsValid(minimapData)
    ? minimapData->signalDefaultColor
    : WHITE;

  Signal& signal = signalsToAdd.push_back();

  signal.color = color;
  signal.lifeTime = lifeTime;
  signal.pos = pos;

  presentation->PrepareSignal(faction, signal);
}


void Minimap::AddSignal(const CVec3 & worldPos, NDb::EFaction faction)
{
  const float lifeTime = IsValid(minimapData)
    ? minimapData->signalLifeTime
    : 0.f;

  AddSignal(worldPos, faction, lifeTime);
}


void Minimap::AddSignal( const CVec3 & worldPos, NDb::EFaction faction, float lifeTime )
{
  CVec2 pos;
  World2Ui( worldPos, pos );
  AddSignalInternal( pos, faction, lifeTime );
}

void Minimap::UpdateSignals(float deltaTime)
{
  vector<Signal> signals;

  signalsToAdd.swap(signals);

  if (!IsValid(flashInterface))
    return;

  vector<Signal>::const_iterator it = signals.begin();
  vector<Signal>::const_iterator it_end = signals.end();
  for (; it != it_end; ++it)
  {
    Signal const& signal = *it;

    flashInterface->AddSignal(signal.pos.x, 1 - signal.pos.y, signal.color.Dummy, signal.lifeTime);
  }
}

void Minimap::InitNatureMapParams( const NDb::MinimapImages * _images )
{
  if ( !_images )
    return;

  // Set sampler
  m_natureSampler = Render::SamplerState::PRESET_WRAP_BILINEAR();

  if ( _images->firstMap )
    m_natureTextureA = _images->firstMap->Load();
  if ( _images->secondMap )
    m_natureTextureB = _images->secondMap->Load();
  if ( _images->neutralMap )
    m_natureTextureN = _images->neutralMap->Load();
}

void Minimap::SetMinimapEffect( int index, NDb::EMinimapEffects effect )
{
  if (IsValid(flashInterface))
    flashInterface->SetMinimapEffect( index, effect );
}

void Minimap::UpdateMinimapEffect( int index, const CVec3& pos )
{
  CVec2 uiPos( 0.0f, 0.0f );
  World2Ui( pos, uiPos );
  if (IsValid(flashInterface))
    flashInterface->UpdateMinimapEffect( index, uiPos.x, 1 - uiPos.y );
}

int Minimap::AddMinimapEffect( NDb::EMinimapEffects effect )
{
  SetMinimapEffect( s_MinimapEffectIndex, effect );
  return s_MinimapEffectIndex++;
}

void Minimap::SetSpectatorMode(const bool value)
{
  if (value)
  {
    Reset(presentation, new FactionPresentation(*this));
  }
  else
  {
    Reset(presentation, new FriendOrFoePresentation(*this));
  }
}

bool Minimap::ShouldDisplayTargetZone() const
{
  if (!IsValid(flashInterface))
    return false;
  if (!IsValid(localHero))
    return false;

  if (!targetZoneDisplay)
    return false;

  if (targetZoneRange < EPS_VALUE)
    return false;

  return true;
}

void Minimap::UpdateTargetZone()
{
  if (ShouldDisplayTargetZone())
  {
    CVec2 position;

    World2Ui(localHero->GetPosition(), position);

    position.y = 1.f - position.y;

    const float radius = targetZoneRange / fabs(m_worldSize);

    flashInterface->ShowMinimapTargetZone(position.x, position.y, radius);
  }
  else
  {
    flashInterface->HideMinimapTargetZone();
  }
}

int Minimap::s_MinimapEffectIndex = 0;

} //namespace NGameX
