#pragma once

#include "Render/dipdescriptor.h"
#include "Render/DxIntrusivePtr.h"
#include "Render/dxutils.h"
#include "Render/renderstates.h"
#include "Render/texture.h"
#include "Render/material.h"


#include "PFAICommon.h"
#include "DBPFEffect.h"
#include "UI/ImageLabel.h"

#include "ObjectInfoHelper.h"

namespace NDb
{
  struct DBUIData;
  struct MinimapImages;
}

namespace UI
{
  class FlashContainer2;
}

namespace NWorld
{
  class PFBaseUnit;
  class PFBaseHero;
}

namespace NGameX
{

  class AdventureFlashInterface;

  class Minimap
    : public CObjectBase
    , public DI::SelfProvider<Minimap>
  {
    OBJECT_BASIC_METHODS( Minimap );

    enum
    {
      DefaultUnitIcon = 0x80000DEF
    };

  public :
    Minimap();
    Minimap( UI::FlashContainer2 * _flashWnd, AdventureFlashInterface * _flashInterface );
    ~Minimap();

    void SetSpectatorMode(const bool value);

    void InitAndSetImages( const NDb::DBMinimap * _minimapData, const NDb::MinimapImages * _images );

    //IMinimapControl:
    void SetWorldSize( const CVec2 & worldSize );
    void SetMinimapRotation( float angle );
    void SetLocalHero(const NWorld::PFBaseHero* const _hero);
    void SetCameraPosition( const CVec3 & newPos ) { m_cameraPos = newPos; } //@todo Oleg stub method
    void SetOver( bool over ) { m_over = over; }
    bool IsOver() { return m_over; }

    void SetCursorPosition( float x, float y ) { m_cursorPosition.Set(x, y); }
    const CVec2& GetCursotPosition() { return m_cursorPosition; }


    bool BeginUpdate( float deltaTime );
    void AddObject( NDb::EUnitType unitType, NDb::EFaction faction, const CVec3 & pos, int icon );
    void AddObject( const NWorld::PFBaseUnit* const unit, const int icon = DefaultUnitIcon, const CVec3& offset = VNULL3);
    void AddObject( const NWorld::PFLogicObject* const logicObject, const int icon, const CVec3& offset = VNULL3);
    int  AddHeroIcon( const NDb::Texture * icon );
    bool EndUpdate();

    //Numerous conversions
    void Ui2World( float x, float y, CVec3 & result ) const;
    void World2Ui( const CVec3 & world, CVec2 & result ) const;

    void AddSignal( const CVec3 & worldPos, NDb::EFaction faction);
    void AddSignal( const CVec3 & worldPos, NDb::EFaction faction, float lifeTime );

    void Render();
    void OnRenderModeChange() { InitializeMinimapTexture(); }

    void SetMinimapEffect( int index, NDb::EMinimapEffects effect );
    void UpdateMinimapEffect( int index, const CVec3& pos );
    int  AddMinimapEffect( NDb::EMinimapEffects effect );

    void SetTargetZoneDisplay(const bool value)
    {
      targetZoneDisplay = value;
    }

    void SetTargetZoneRange(const float value)
    {
      targetZoneRange = value;
    }

  private:
    struct Vertex;
    struct Quad;

    struct Signal
    {
      Render::Color color;
      float lifeTime;
      CVec2 pos;
    };

    class Presentation;
    class FactionPresentation;
    class FriendOrFoePresentation;

    friend class Presentation;
    friend class FactionPresentation;
    friend class FriendOrFoePresentation;

    ScopedPtr<Presentation>       presentation;

    NDb::Ptr<NDb::DBMinimap>      minimapData;
    NDb::Ptr<NDb::MinimapImages>  minimapImages;

    Weak<UI::FlashContainer2>     flashWnd;
    Weak<AdventureFlashInterface> flashInterface;

    Vertex*         m_vertices;
    int             m_lastIndex;
    int             m_numTriangles;

    CVec2           m_cursorPosition;
    CVec2           m_worldSize;
    CVec2           m_worldToLocal;
    CVec2           m_localToWorld;
    float           m_mapRotation;
    float           m_mapRotationSin;
    float           m_mapRotationCos;
    CTPoint<float>  m_natureMapPolygon[4];
    CVec2           m_offset;
    float           m_scale;

    bool            m_updated;
    bool            m_over;

    ConstPtr<NWorld::PFBaseHero>  localHero;

    // Render
    Render::DipDescriptor     m_cameraDip;

    DXVertexBufferDynamicRef::Wrapped  m_vb;
    DXVertexBufferDynamicRef::Wrapped  m_cameraVB;

    DXVertexDeclarationRef    m_vertexDeclaration;

    Render::RenderState       m_renderState;

    Render::SamplerState      m_minimapSampler;
    Render::Texture2DRef      m_minimapTexture;
    Render::Texture2DRef      m_targetTexture;

    Render::SamplerState      m_natureSampler;
    Render::TextureRef        m_natureTextureA;
    Render::TextureRef        m_natureTextureB;
    Render::TextureRef        m_natureTextureN;

    int textureWidth;
    int textureHeight;

    CVec2 invTargetSize;

    struct IconDesc
    {
      Render::Texture2DRef texture;
      CVec2 uv1;
      CVec2 uv2;
    };

    struct HeroIconDesc: public IconDesc
    {
      NDb::DBID originTextureId;
    };

    nstl::vector<IconDesc> icons;
    nstl::vector<HeroIconDesc> heroIcons;
    IconDesc whiteIcon; 
    IconDesc enemyFrameIcon;
    IconDesc allyFrameIcon;
    IconDesc selfFrameIcon;

    struct Object
    {
      NDb::EUnitType unitType;
      NDb::EFaction faction;
      CVec2 pos;
      int icon;
    };

    typedef nstl::vector<Object> Layer;

    struct RenderChunk
    {
      Render::Texture2DRef texture;
      Render::DipDescriptor dip;

      RenderChunk() : dip( Render::RENDERPRIMITIVE_TRIANGLELIST, 0, 0, 0, 0, 0 ) {}
    };

    typedef nstl::vector<RenderChunk> Queue; 

    Queue queue;

    Render::UIRenderMaterial  renderMaterial;
    Render::UIRenderMaterial  cameraMaterial;

    // Camera
    CVec3                     m_cameraPos;

    // Target Zone
    bool                      targetZoneDisplay;
    float                     targetZoneRange;

    vector<Signal>            signalsToAdd;

    DI_WEAK(ObjectInfoHelper) objectInfoHelper;

    void ClearAll();
    void SetupViewParameters();

    //internal conversions
    void LocalToWorld( CVec2 mmap, CVec3 & result ) const;
    void WorldToLocal( CVec3 world, CVec2 & result ) const;
    CVec3 LocalToWorld(const CVec2& p) const;
    CVec2 WorldToLocal(const CVec3& p) const;

    void UpdateSignals(float timeLeft );

    void _AddRect( float _x, float _y, Render::Color color, const Render::Texture2DRef& texture, const CVec2& uv1, const CVec2& uv2 );
    void _AddCameraFrame( Vertex * pBuffer );

    void _RenderMinimap();
    void _RenderNatureMap();

    void AddSignalInternal( const CVec2 & pos, NDb::EFaction faction, float lifeTime );

    void InitSpecialTextures();
    void PrepareObjectsForRender();
    void PushChunk( const Render::Texture2DRef& texture );

    const Render::Texture2DRef& GetTargetTexture() { return m_targetTexture; }
    void InitNatureMapParams( const NDb::MinimapImages * _images );
    void InitializeMinimapTexture();

    void SetPresentation(Presentation* const p);

    bool ShouldDisplayTargetZone() const;
    void UpdateTargetZone();

    bool IsValidIcon(const int index) const
    {
      if (index < 1)
        return false;
      if (index >= icons.size())
        return false;

      if (!icons[index].texture)
        return false;

      return true;
    }

    bool IsValidHeroIcon(const int index) const
    {
      if (index < 0)
        return false;
      if (index >= heroIcons.size())
        return false;

      if (!heroIcons[index].texture)
        return false;

      return true;
    }

    static int s_MinimapEffectIndex;
  };

} //namespace NGameX
