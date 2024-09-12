#include "stdafx.h"

#include "AdventureScreen.h"
#include "ObjectsInfo2d.h"
#include "PFBuildings.h"
#include "PFAIWorld.h"
#include "PFSummoned.h"
#include "PFClientBaseUnit.h"
#include "PFChest.h"
#include "PFGlyph.h"
#include "UI/Resolution.h"
#include "UI/ImageLabel.h"
#include "UI/ProgressBar.h"
#include "UI/HealthBar.h"

#include "ui/DebugDraw.h"
#include "Render/DebugRenderer.h"

#include "System/InlineProfiler.h"

#include "ObjectInfoMapper.hpp"


namespace NGameX
{

namespace
{
  bool s_drawTooltipBoxes = false;

  REGISTER_DEV_VAR( "show_3d_tooltips_boxes", s_drawTooltipBoxes, STORAGE_NONE );
}

namespace WindowCaps
{
  typedef unsigned ValueType;

  namespace Index
  {
    enum
    {
      Main,
      Text,
      HealthBack,
      Health,
      ManaBack,
      Mana,
      ChannelingBack,
      Channeling,
      Level,
      LevelFrame,
      Glow,
      Last,
    };
  }

#define _CAP(x) x = (1 << Index::x)

  enum Type
  {
    _CAP(Main),
    _CAP(Text),
    _CAP(HealthBack),
    _CAP(Health),
    _CAP(ManaBack),
    _CAP(Mana),
    _CAP(ChannelingBack),
    _CAP(Channeling),
    _CAP(Level),
    _CAP(LevelFrame),
    _CAP(Glow),
  };

#undef _CAP

  enum
  {
    HealthBar = HealthBack | Health,
    ManaBar = ManaBack | Mana,
    ChannelingBar = ChannelingBack | Channeling,
    AnyText = Text | Level,
  };

  template <typename T>
  static inline void UpdateCap(const Weak<T>& p, ValueType& caps, const ValueType cap)
  {
    if (IsValid(p))
      caps |= cap;
  }
}

namespace
{
  class WindowzBottom
  {
    UI::LinearCoord top;
  public:
    WindowzBottom() : top( 0 ) {}
    operator int () const { return top; }
    WindowzBottom & operator << ( UI::Window * wnd )
    {
      if ( wnd )
        if ( wnd->IsVisible() )
          top = Max( top, wnd->GetPos().y + wnd->GetSize().y );
      return *this;
    }
  };

  static inline float GetShiled(const NWorld::PFBaseUnit* const unit)
  {
    if (!unit)
      return 0.f;

    return ceil(unit->GetShield());
  }
}

struct ObjectsInfo2dLogic::SOvertipCustomEnergy
{
  bool                  enabled;
  bool                  needMaterial;
  string                stateName;

  static inline bool IsEqual(const SOvertipCustomEnergy& lhs, const SOvertipCustomEnergy& rhs)
  {
    if (lhs.enabled && rhs.enabled)
    {
      if (lhs.stateName.empty() != rhs.stateName.empty())
        return true;

      return (lhs.stateName == rhs.stateName);
    }

    return (lhs.enabled == rhs.enabled);
  }

  SOvertipCustomEnergy()
    : enabled(false)
    , needMaterial(false)
    , stateName()
  {

  }

  bool operator==(const SOvertipCustomEnergy& rhs) const
  {
    return IsEqual(*this, rhs);
  }

  bool operator!=(const SOvertipCustomEnergy& rhs) const
  {
    return !IsEqual(*this, rhs);
  }
};

struct ObjectsInfo2dLogic::SOvertipWindow
{
  WindowCaps::ValueType caps;

  Weak<UI::Window>      wndMain;
  Weak<UI::ImageLabel>  wndText;
  Weak<UI::Window>      wndHealthBack;
  Weak<UI::HealthBar>   wndHealth;
  Weak<UI::Window>      wndManaBack;
  Weak<UI::ProgressBar> wndMana;
  Weak<UI::Window>      wndChannelingBack;
  Weak<UI::ProgressBar> wndChanneling;
  Weak<UI::ImageLabel>  wndLevel;
  Weak<UI::ImageLabel>  wndLevelFrame;
  Weak<UI::ImageLabel>  wndGlow;;

  wstring               levelTextMarkup;

  SOvertipCustomEnergy  customEnergy;

  SOvertipWindow()
    : caps(0)
    , wndMain()
    , wndText()
    , wndHealthBack()
    , wndHealth()
    , wndManaBack()
    , wndMana()
    , wndChannelingBack()
    , wndChanneling()
    , wndLevel()
    , wndLevelFrame()
    , wndGlow()
    , levelTextMarkup()
    , customEnergy()
  {
  }

  bool HasCustomEnergyState() const
  {
    return customEnergy.enabled && !customEnergy.stateName.empty();
  }

  bool NeedCustomEnergyMaterial() const
  {
    return customEnergy.enabled && customEnergy.needMaterial;
  }

  void OnCustomEnergyMaterialSet()
  {
    customEnergy.needMaterial = false;
  }
};

struct ObjectsInfo2dLogic::SOvertip : SOvertipWindow
{
  NDb::Ptr<NDb::AdventureTooltipSettings> db;

  ConstPtr<PF_Core::WorldObjectBase>      worldObject;

  bool          valid;
  bool          selected;
  bool          picked;
  bool          showText;

  CVec3         worldPosition;
  float         worldSize;
  int           screenSize;
  Render::AABB  aabb;
  float         healthMax;
  float         health;
  float         shield;
  float         manaPercent;
  float         channelingPercent;
  bool          showMana;
  bool          showStripes;
  bool          showShield;

  SOvertip()
    : valid( false )
    , selected( false )
    , picked( false )
    , showText( false )
    , worldPosition( VNULL3 )
    , worldSize( 1.0f )
    , screenSize( 0 )
    , aabb( VNULL3, VNULL3 )
    , healthMax( 0.f )
    , health( 0.f )
    , shield( 0.f )
    , manaPercent( 0.f )
    , channelingPercent( 0.f )
    , showMana(false)
    , showStripes(false)
    , showShield(false)
  {
  }

  bool NeedWindow() const
  {
    if (!::IsValid(wndMain))
      return true;

    return (wndMain->GetState() != db->uiState);
  }

  bool IsValid() const
  {
    NI_VERIFY(::IsValid(db), "Tooltip settings must be defined!", return false);
    NI_VERIFY(::IsValid(wndMain), "Tooltip window must exist!", return false);

    NI_VERIFY(caps & WindowCaps::Main, "Tooltip must have valid caps!", return false);

    return true;
  }

  bool UpdateDesc(const NDb::AdventureTooltipSettings* const _db)
  {
    if (!!db && !!_db)
    {
      if (db->GetDBID() == _db->GetDBID())
        return false;
    }

    db = _db;

    NI_VERIFY(::IsValid(db), "Invalid tooltip desc!", return false);

    return true;
  }

  bool NeedUpdateCustomEnergy(const SOvertipCustomEnergy& _customEnergy) const
  {
    return customEnergy != _customEnergy;
  }

  const char* GetWorldObjectTypeName() const
  {
    return ::IsValid(worldObject) ? worldObject->GetObjectTypeName() : "n/a";
  }
};

class ConditionalNameMap : public NNameMap::Map
{
  NAMEMAP_DECLARE;
public:
  explicit ConditionalNameMap(const NWorld::PFBaseHero* const _pObject)
    : pObject(_pObject)
  {
  }
protected:
  virtual NNameMap::Variant * ResolveVariant( const char * name, int length, const char * args, int argsLength, void* prms, bool readonly );
private:
  ConditionalNameMap();
  ConditionalNameMap(const ConditionalNameMap&);
  ConditionalNameMap& operator=(const ConditionalNameMap&);

  const NWorld::PFBaseHero* const pObject;
};

UNITINFOTUPLEUNIT(ConditionalNameMap)

namespace
{
  template <typename T = NDb::AdventureTooltipSettings>
  struct PointerSelector
  {
    typedef const T* Ptr;

    static inline Ptr Select(Ptr a)
    {
      if (a) return a;
      return 0;
    }

    static inline Ptr Select(Ptr a, Ptr b)
    {
      if (a) return a;
      if (b) return b;
      return 0;
    }

    static inline Ptr Select(Ptr a, Ptr b, Ptr c)
    {
      if (a) return a;
      if (b) return b;
      if (c) return c;
      return 0;
    }

    static inline Ptr Select(Ptr a, Ptr b, Ptr c, Ptr d)
    {
      if (a) return a;
      if (b) return b;
      if (c) return c;
      if (d) return d;
      return 0;
    }
  };

  template <typename T>
  static inline bool CheckKnownEnum(const T value, const int minimum = 0)
  {
    typedef NDb::KnownEnum<T> KnownEnumType;

    if (value < minimum)
      return false;
    if (value >= KnownEnumType::sizeOf)
      return false;

    return true;
  }
}

// TODO: cache UIRoot?

class ObjectsInfo2dLogic::Presentation : public NonCopyable
{
public:
  virtual ~Presentation()
  {
  }

  virtual const NDb::AdventureTooltipSettings* GetTooltipSettings(const ObjectInfo& info) const = 0;

  virtual void UpdateHealthStripes(const NDb::UIHealthStripes& stripes, const ObjectInfo& info, const SOvertip& overtip) const
  {
    if (info.faction == GetFaction())
    {
      overtip.wndHealth->SetStripes(stripes, false);
    }
    else
    {
      overtip.wndHealth->SetStripes(stripes, true);
    }
  }
protected:
  explicit Presentation(ObjectsInfo2dLogic& logic)
    : logic(logic)
  {
  }

  inline NDb::EFaction GetFaction() const
  {
    if (!IsValid(logic.localHero))
      return NDb::FACTION_NEUTRAL;

    return logic.localHero->GetFaction();
  }

  inline bool IsLocalHero(const ObjectInfo& info) const
  {
    return (info.kind == EObjectKind::LocalHero);
  }

  inline bool IsLocalHeroSlave(const ObjectInfo& info) const
  {
    const NWorld::PFBaseUnit* const unit = GetObject<NWorld::PFBaseUnit>(info);

    if (!unit)
      return false;

    const NWorld::PFSummonBehaviour* const behaviour = dynamic_cast<const NWorld::PFSummonBehaviour*>(unit->GetBehaviour());

    if (!behaviour)
      return false;
    if (!behaviour->IsEssentialSummon())
      return false;

    if (!IsValid(behaviour->GetMaster()))
      return false;

    return (behaviour->GetMaster().GetPtr() == logic.localHero.GetPtr());
  }

  ObjectsInfo2dLogic& logic;
private:
  Presentation();
};

class ObjectsInfo2dLogic::FactionPresentation : public Presentation
{
public:
  explicit FactionPresentation(ObjectsInfo2dLogic& logic)
    : Presentation(logic)
  {
  }

  virtual const NDb::AdventureTooltipSettings* GetTooltipSettings(const ObjectInfo& info) const
  {
    typedef PointerSelector<> SS;

    if (!IsValid(info.logicObject))
      return NULL;

    NI_VERIFY(CheckKnownEnum(info.unitType), "Invariant", return NULL);

    const NDb::UnitOvertipSettings& unitSettings = logic.settings->units[info.unitType];

    const bool vulnerable = info.logicObject->IsVulnerable();

    switch (info.faction)
    {
    case NDb::FACTION_NEUTRAL:
      return SS::Select(unitSettings.neutral, unitSettings.ally);
    case NDb::FACTION_FREEZE:
      if (vulnerable)
        return SS::Select(unitSettings.ally);
      else
        return SS::Select(unitSettings.invulnerableAlly, unitSettings.ally);
    case NDb::FACTION_BURN:
      if (vulnerable)
        return SS::Select(unitSettings.enemy, unitSettings.ally);
      else
        return SS::Select(unitSettings.invulnerableEnemy, unitSettings.enemy, unitSettings.ally);
    }

    NI_ALWAYS_ASSERT("Shouldn't get here");

    return NULL;
  }

  virtual void UpdateHealthStripes(const NDb::UIHealthStripes& stripes, const ObjectInfo& info, const SOvertip& overtip) const
  {
    switch (info.faction)
    {
    case NDb::FACTION_FREEZE:
      overtip.wndHealth->SetStripes(stripes, false);
      break;
    case NDb::FACTION_BURN:
      overtip.wndHealth->SetStripes(stripes, true);
      break;
    default:
      break;
    }
  }
};

class ObjectsInfo2dLogic::FriendOrFoePresentation : public Presentation
{
public:
  explicit FriendOrFoePresentation(ObjectsInfo2dLogic& logic)
    : Presentation(logic)
  {
  }

  virtual const NDb::AdventureTooltipSettings* GetTooltipSettings(const ObjectInfo& info) const
  {
    typedef PointerSelector<> SS;

    if (!IsValid(info.logicObject))
      return NULL;

    NI_VERIFY(CheckKnownEnum(info.unitType), "Invariant", return NULL);

    const NDb::UnitOvertipSettings& unitSettings = logic.settings->units[info.unitType];

    const bool vulnerable = info.logicObject->IsVulnerable();

    if (IsLocalHero(info))
    {
      if (vulnerable)
        return SS::Select(unitSettings.localHero, unitSettings.ally);
      else
        return SS::Select(unitSettings.invulnerableLocalHero, unitSettings.invulnerableAlly, unitSettings.localHero, unitSettings.ally);
    }

    if (IsLocalHeroSlave(info))
    {
      if (vulnerable)
        return SS::Select(unitSettings.localHeroSlave, unitSettings.ally);
      else
        return SS::Select(unitSettings.invulnerableLocalHeroSlave, unitSettings.invulnerableAlly, unitSettings.localHeroSlave, unitSettings.ally);
    }

    if (info.faction == NDb::FACTION_NEUTRAL)
      return SS::Select(unitSettings.neutral, unitSettings.ally);

    if (info.faction == GetFaction())
    {
      if (vulnerable)
        return SS::Select(unitSettings.ally);
      else
        return SS::Select(unitSettings.invulnerableAlly, unitSettings.ally);
    }
    else
    {
      if (vulnerable)
        return SS::Select(unitSettings.enemy, unitSettings.ally);
      else
        return SS::Select(unitSettings.invulnerableEnemy, unitSettings.enemy, unitSettings.ally);
    }
  }
};

template <class T, const bool = boost::is_base_of<NWorld::PFBaseHero, T>::value>
struct ObjectNameMap
  : public NonCopyable
{
  // NOTE: необходимость подмены типов обусловлена особенностями NameMap'а для PFBaseHero.
  // а именно, в нем нет submap'а под именем unit, который нужен для получения левела.
  // тем не менее, эту проблему определенно следует решать другим способом.

  typedef NWorld::PFBaseUnit ObjectType;

  typedef typename NMeta::MakeTypeList<ObjectType, ConditionalNameMap, PlayerData>::Result MyNameMapTypeList;
  typedef UnitInfoNameMap<MyNameMapTypeList> MyNameMap;

  explicit ObjectNameMap(const T* const object)
    : nameMap()
    , conditionalNameMap(object)
  {
    NI_VERIFY(!!AdventureScreen::Instance(), "AdventureScreen must exist!", return);

    Field<ObjectType>(nameMap).pObject          = object;
    Field<ConditionalNameMap>(nameMap).pObject  = &(conditionalNameMap);

    if (PlayerDataManager* const playerDataManager = AdventureScreen::Instance()->GetPlayerDataMan())
      Field<PlayerData>(nameMap).pObject        = &(playerDataManager->GetPlayerData(object->GetPlayerId()));
    else
      Field<PlayerData>(nameMap).pObject        = NULL;
  }

  operator const NNameMap::Map*() const
  {
    return &nameMap;
  }
private:
  ObjectNameMap();

  MyNameMap nameMap;
  ConditionalNameMap conditionalNameMap;
};

template <class T>
struct ObjectNameMap<T, false>
  : public NonCopyable
{
  typedef T ObjectType;

  typedef typename NMeta::MakeTypeList<ObjectType, ConditionalNameMap, PlayerData>::Result MyNameMapTypeList;
  typedef UnitInfoNameMap<MyNameMapTypeList> MyNameMap;

  explicit ObjectNameMap(const T* const object)
    : nameMap()
    , conditionalNameMap(NULL)
  {
    Field<ObjectType>(nameMap).pObject         = object;
    Field<ConditionalNameMap>(nameMap).pObject = &conditionalNameMap;
    Field<PlayerData>(nameMap).pObject         = NULL;
  }

  operator const NNameMap::Map*() const
  {
    return &nameMap;
  }
private:
  MyNameMap nameMap;
  ConditionalNameMap conditionalNameMap;
};


template <class T>
void ObjectsInfo2dLogic::UpdateOvertipTextImpl( SOvertip & overtip, const T * object, const bool showText )
{
  overtip.showText = showText;

  if (!overtip.IsValid())
    return;

  const bool updateText = (overtip.caps & WindowCaps::Text) && (overtip.showText);
  const bool updateLevelText = (overtip.caps & WindowCaps::Level);

  if (updateText || updateLevelText)
    ;
  else
    return;

  const ObjectNameMap<T> nameMap(object);

  //Поскольку nameMap не постоянно привязан к контролу, данные в 
  //окне пропадают после того как контролл решает их обновить. 
  //Поэтому здесь, в качестве костыля, напрямую устанавливается текст 

  PrecompiledTooltip pctt;

  if (updateLevelText)
  {
    if (overtip.levelTextMarkup.empty())
      overtip.levelTextMarkup = overtip.wndLevel->GetCaptionTextW();

    wstring text;

    pctt.Parse(overtip.levelTextMarkup);
    pctt.ResolveVariants(nameMap);
    pctt.MakeText(text);

    overtip.wndLevel->SetCaptionTextW(text);
  }

  if (updateText)
  {
    wstring text;

    pctt.Parse(overtip.db->text.GetText());
    pctt.ResolveVariants(nameMap);
    pctt.MakeText(text);

    overtip.wndText->SetCaptionTextW(text);
    overtip.wndText->FixWidthToFitCaption(-1, 2);
  }
}

ObjectsInfo2dLogic::ObjectsInfo2dLogic(int)
  : idCounter( 0 )
  , showHealthBars( true )
{
  SetSpectatorMode(false);
}

void ObjectsInfo2dLogic::Init( UI::User * uiUser )
{
  SetUser( uiUser );
  LoadScreenLayout( "ObjectsInfo2d" );
  SetTooltipParams( NDb::Get<NDb::AdventureTooltipParams>(NDb::DBID("UI/Content/_.UITP.xdb")) );
}

void ObjectsInfo2dLogic::SetTooltipParams( const NDb::AdventureTooltipParams* _settings )
{
  if ( !_settings ) 
    return;

  settings = _settings;
  if ( !settings->GetDBID().IsInlined() )
    NDb::Precache<NDb::AdventureTooltipParams>( settings->GetDBID(), 20 );
}

void ObjectsInfo2dLogic::SetLocalHero(const NWorld::PFBaseHero* const _hero)
{
  localHero = _hero;
}

void ObjectsInfo2dLogic::GetWindowFromPool( const WindowsPool::key_type &key, WindowsPool::mapped_type &window )
{
  const WindowsPool::key_type& effectiveKey = window.HasCustomEnergyState()
    ? window.customEnergy.stateName
    : key;

  const WindowsPool::iterator it = windowsPool.find( effectiveKey );

  if (it != windowsPool.end())
  {
    window = it->second;
    windowsPool.erase(it);
    return;
  }
  
  NI_PROFILE_BLOCK("Tooltip window create");
  
  char szNamBuffer[32] = "";
  sprintf_s( szNamBuffer, "%d", ++idCounter );

  window.caps = 0U;
  window.wndMain = pBaseWindow->CreateChild( szNamBuffer, "tooltip", 0, 0, 0, 0, NDb::UIELEMENTHALIGN_LEFT, NDb::UIELEMENTVALIGN_TOP );

  NI_VERIFY( window.wndMain, "Unable to create child window", return );

  if ( !key.empty() )
    window.wndMain->SetState( key.c_str() );

  // text
  window.wndText = UI::GetChildChecked<UI::ImageLabel>( window.wndMain, "Text", false );

  const bool hideText =
    (window.wndText && !window.wndText->IsVisible());

  if (hideText)
  {
    window.wndText = NULL;
  }

  // level
  window.wndLevel = UI::GetChildChecked<UI::ImageLabel>( window.wndMain, "char_level", true );
  window.wndLevelFrame = UI::GetChildChecked<UI::ImageLabel>( window.wndMain, "lvl_back", true );

  const bool hideLevelText =
    (window.wndLevel && !window.wndLevel->IsVisible()) ||
    (window.wndLevelFrame && !window.wndLevelFrame->IsVisible());

  if (hideLevelText)
  {
    window.wndLevel = NULL;
    window.wndLevelFrame = NULL;
  }

  //Health bar
  window.wndHealthBack = window.wndMain->GetChild( "HealthBack" );
  window.wndHealth = UI::GetChildChecked<UI::HealthBar>( window.wndMain, "Health", true );

  if (window.wndHealthBack && !window.wndHealthBack->IsVisible())
  {
    window.wndHealth = NULL;
    window.wndHealthBack = NULL;
  }

  //Mana bar
  window.wndManaBack = window.wndMain->GetChild( "ManaBack" );
  window.wndMana = UI::GetChildChecked<UI::ProgressBar>( window.wndMain, "Mana", true );

  if (window.wndManaBack && !window.wndManaBack->IsVisible())
  {
    window.wndMana = NULL;
    window.wndManaBack = NULL;
  }

  //Channeling bar
  window.wndChannelingBack = window.wndMain->GetChild( "ChannelingBack" );
  window.wndChanneling = UI::GetChildChecked<UI::ProgressBar>( window.wndMain, "Channeling", true );

  //Glow
  window.wndGlow = UI::GetChildChecked<UI::ImageLabel>(window.wndMain, "Glow", true);

  if (window.wndGlow && !window.wndGlow->IsVisible())
  {
    window.wndGlow = NULL;
  }

/*
  // TODO: ?
  if (window.wndChannelingBack && !window.wndChannelingBack->IsVisible())
  {
    window.wndChanneling = NULL;
    window.wndChannelingBack = NULL;
  }
*/

  WindowCaps::UpdateCap(window.wndMain, window.caps, WindowCaps::Main);
  WindowCaps::UpdateCap(window.wndText, window.caps, WindowCaps::Text);
  WindowCaps::UpdateCap(window.wndHealth, window.caps, WindowCaps::Health);
  WindowCaps::UpdateCap(window.wndHealthBack, window.caps, WindowCaps::HealthBack);
  WindowCaps::UpdateCap(window.wndManaBack, window.caps, WindowCaps::ManaBack);
  WindowCaps::UpdateCap(window.wndMana, window.caps, WindowCaps::Mana);
  WindowCaps::UpdateCap(window.wndChannelingBack, window.caps, WindowCaps::ChannelingBack);
  WindowCaps::UpdateCap(window.wndChanneling, window.caps, WindowCaps::Channeling);
  WindowCaps::UpdateCap(window.wndLevel, window.caps, WindowCaps::Level);
  WindowCaps::UpdateCap(window.wndLevelFrame, window.caps, WindowCaps::LevelFrame);
  WindowCaps::UpdateCap(window.wndGlow, window.caps, WindowCaps::Glow);
}

void ObjectsInfo2dLogic::AddWindowToPool( const WindowsPool::mapped_type &window )
{
  if (!IsValid(window.wndMain))
    return;

  const WindowsPool::key_type& effectiveKey = window.HasCustomEnergyState()
    ? window.customEnergy.stateName
    : window.wndMain->GetState();

  windowsPool.insert( WindowsPool::value_type(effectiveKey, window) );

  window.wndMain->Show(false);
}

void ObjectsInfo2dLogic::SetupOvertip( SOvertip & overtip, const SOvertipCustomEnergy& customEnergy )
{
  struct Local
  {
    static void ApplyCustomEnergyMaterial(const ObjectInfo& info, SOvertip& overtip)
    {
      if (overtip.NeedCustomEnergyMaterial())
      {
        NI_VERIFY(EObjectKind::IsHero(info.kind), "Invalid object info!", return);

        const NWorld::PFBaseHero* const hero = GetObject<NWorld::PFBaseHero>(info);

        NI_VERIFY(!!hero, "Invalid hero!", return);

		const NDb::BaseHero* const dbHero = hero->GetDbHero();

		// NUM_TASK Дополнительные проверки на наличие uniqueResource
		NI_VERIFY(!!dbHero, "Invalid DB hero!", return);

		if (dbHero->uniqueResource != NULL && !dbHero->uniqueResource.IsEmpty())
		{
			const NDb::HeroResource* const uniqueResource = dbHero->uniqueResource.GetPtr();

			if (uniqueResource->overtipManaProgressMaterial != NULL && !uniqueResource->overtipManaProgressMaterial.IsEmpty())
			{
				overtip.wndMana->SetProgressMaterial(hero->GetDbHero()->uniqueResource->overtipManaProgressMaterial);

				DevTrace("<+> Replaced overtip mana bar progress material (%d)", hero->GetObjectId());

				overtip.OnCustomEnergyMaterialSet();
			}
		}
      }
      else
      {
        // TODO: вернуть оригинальный материал?
      }
    }
  };

  NI_PROFILE_FUNCTION;

  //Main tooltip window
  // TODO: избавиться от двойной проверки. NeedUpdateCustomEnergy() вызывается уровнем выше.
  if (overtip.NeedWindow() || overtip.NeedUpdateCustomEnergy(customEnergy))
  {
    AddWindowToPool(overtip);

    overtip.customEnergy = customEnergy;

    GetWindowFromPool(overtip.db->uiState, overtip);
  }

  NI_VERIFY( overtip.wndMain, "Unable to create child window", return );

  if (overtip.caps & WindowCaps::Text)
  {
    overtip.wndText->Show( overtip.showText );
    overtip.wndText->SetCaptionWordWrap( false );
  }

  if (overtip.caps & WindowCaps::ManaBar)
  {
    Local::ApplyCustomEnergyMaterial(objectInfoHelper->GetObjectInfo(overtip.worldObject), overtip);
  }
}

void ObjectsInfo2dLogic::UpdateTooltipUI( const ObjectInfo& info, SOvertip & overtip, const SHMatrix & projectionMatrix )
{
  if (!overtip.IsValid())
    return;

  //project unit on screen
  UI::Point screenPoint;
  UI::LinearCoord screenSize = 0;
  float depth = UI::GetWindowPlacement( &screenPoint, &screenSize, overtip.worldPosition, overtip.worldSize, projectionMatrix );
  bool infront = ( depth > 1e-3f );

  if ( screenSize > UI::GetUIScreenResolution().x * 2 )
    infront = false;

  if ( overtip.db->stretch == NDb::ADVENTURETOOLTIPSTRETCHMODE_DYNAMIC )
  {
    screenSize = Clamp( screenSize, (UI::LinearCoord)10, UI::GetUIScreenResolution().x );
    overtip.screenSize = screenSize; //Override every frame
  }

  overtip.wndMain->Show( infront );

  if ( s_drawTooltipBoxes )
    Render::DebugRenderer::DrawAABB( overtip.aabb, Render::Color( 255, 255, 0 ), false );

  if ( !infront )
    return;

  overtip.wndMain->SetSortOrder( -depth ); //Inverse order: near objects have to be placed at the end of the list

  //Update UI elements
  if (overtip.caps & WindowCaps::Text)
  {
    overtip.wndText->Show( overtip.showText );
  }

  if (overtip.caps & WindowCaps::HealthBar)
  {
    overtip.wndHealthBack->Show( true );

    overtip.wndHealth->SetHealthMax( overtip.healthMax );
    overtip.wndHealth->SetHealthValue( overtip.health );
    overtip.wndHealth->SetShieldValue( overtip.shield );
  }

  if (overtip.caps & WindowCaps::ManaBar)
  {
    overtip.wndManaBack->Show( overtip.showMana );
    overtip.wndMana->SetProgressValue( overtip.manaPercent );
  }

  if (overtip.caps & WindowCaps::ChannelingBar)
  {
    overtip.wndChannelingBack->Show( overtip.channelingPercent > 0 );
    overtip.wndChanneling->SetProgressValue( overtip.channelingPercent );
  }

  if (overtip.caps & WindowCaps::Glow)
  {
    overtip.wndGlow->Show(overtip.picked);
  }

  overtip.showText = false;

  if ( overtip.db->stretch != NDb::ADVENTURETOOLTIPSTRETCHMODE_NONE )
  {
    if (overtip.caps & WindowCaps::HealthBack)
      overtip.wndHealthBack->SetSize( overtip.screenSize, -1, false );
    if (overtip.caps & WindowCaps::ManaBack)
      overtip.wndManaBack->SetSize( overtip.screenSize, -1, false );
    if (overtip.caps & WindowCaps::ChannelingBack)
      overtip.wndChannelingBack->SetSize( overtip.screenSize, -1, false );
  }

  //place window into the right coordinates
  WindowzBottom bottom;

  bottom << overtip.wndText;
  bottom << overtip.wndHealthBack;
  bottom << overtip.wndManaBack;
  bottom << overtip.wndChannelingBack;

  const UI::LinearCoord x = floor(screenPoint.x - overtip.wndMain->GetSize().x / 2.f) + 0.5f;
  const UI::LinearCoord y = floor(screenPoint.y - bottom) + 0.5f;

  overtip.wndMain->SetLocation( x, y );

  if (overtip.showStripes)
  {
    const NDb::UIHealthStripes& stripes = UI::GetUIRoot()->healthStripes;

    presentation->UpdateHealthStripes(stripes, info, overtip);
  }

  // Hero level highlighting
  if (overtip.caps & WindowCaps::LevelFrame)
  {
    if ( s_bShowLevelHighlighting && IsValid( s_pHighlightLevelHero ) && overtip.worldObject.GetPtr() == s_pHighlightLevelHero.GetPtr() )
    {
      if ( AdventureScreen* advScreen = AdventureScreen::Instance() )
      {
        const UI::Point& framePos = overtip.wndLevelFrame->LocalToScreen( UI::Point() );
        const UI::Point& frameSize = overtip.wndLevelFrame->GetSize();

        advScreen->ShowTutorialOvertipLevelHighlight( true, framePos.x + frameSize.x * 0.5f, framePos.y + frameSize.y * 0.5f );
      }
    }
  }
}

void ObjectsInfo2dLogic::Update( float deltaTime, const SHMatrix & projectionMatrix )
{
  NI_PROFILE_FUNCTION;

  for (Tooltips::iterator it = tooltips.begin(); it != tooltips.end(); )
  {
    SOvertip& overtip = it->second;

    if (!overtip.valid)
    {
      AddWindowToPool(overtip);

      Tooltips::iterator it_erase(it);

      ++it;

      tooltips.erase(it_erase);
    }
    else
    {
      NI_VERIFY(IsValid(objectInfoHelper), "ObjectInfoHelper must exist!", return);

      NI_VERIFY(!!presentation, "Presentation must exist!", return);

      const ObjectInfo& info = objectInfoHelper->GetObjectInfo(overtip.worldObject);

      UpdateOvertip(info, overtip);
      UpdateTooltipUI(info, overtip, projectionMatrix);

      overtip.valid = false;

      ++it;
    }
  }

  StepWindows(deltaTime);
}



void ObjectsInfo2dLogic::UpdateObject( const PF_Core::WorldObjectBase * object, bool selected, bool picked )
{
  struct Local
  {
    static bool ShouldHideOvertip(const ObjectInfo& info)
    {
      const bool isHero = info.logicObject->IsHero();

      // Don't show overtip if unit is not a hero and it is a mount 
      if (!isHero && info.logicObject->IsMount())
        return true;

      // Don't show overtip if ForbidPick flag is set and unit is mounted on hero or not mounted at all
      if (!info.logicObject->CheckFlagType(NDb::UNITFLAGTYPE_FORBIDPICK))
        return false;

      if (!info.logicObject->IsMounted())
        return true;

      if (!isHero)
        return true;

      const NWorld::PFBaseHero* const hero = GetObject<NWorld::PFBaseHero>(info);

      NI_ASSERT(!!hero, "Invalid hero!");

      if (IsValid(hero->GetMount()))
        return hero->GetMount()->IsHero();

      return true;
    }

    static bool IsPrimaryCreep(const ObjectInfo& info, const ConstPtr<NWorld::PFBaseHero>& localHero)
    {
      const NWorld::PFBaseUnit* const unit = GetObject<NWorld::PFBaseUnit>(info);

      NI_ASSERT(!!unit, "Invalid unit!");

      const NWorld::PFSummonBehaviour* const behaviour = dynamic_cast<const NWorld::PFSummonBehaviour*>(unit->GetBehaviour());

      if (!behaviour)
        return false;
      if (!behaviour->IsEssentialSummon())
        return false;

      if (!IsValid(behaviour->GetMaster()))
        return false;

      return (behaviour->GetMaster().GetPtr() == localHero.GetPtr());
    }
  };

  NI_PROFILE_FUNCTION

  if (!object)
    return;

  NI_VERIFY(IsValid(objectInfoHelper), "ObjectInfoHelper must exist!", return);

  const ObjectInfo& info = objectInfoHelper->UpdateObjectInfo(object);

  if (info.kind == EObjectKind::Unknown)
    return;

  if (info.logicObject->IsVulnerable() && info.logicObject->IsDead() || Local::ShouldHideOvertip(info))
    return;

  bool showOvertip = showHealthBars || selected || picked;

  //Heroes always have their health bars with them
  if (!showOvertip && info.logicObject->IsHero())
    showOvertip = true;

  if (!showOvertip && Local::IsPrimaryCreep(info, localHero))
    showOvertip = true;

  if (!showOvertip)
    return;

  Tooltips::iterator it = tooltips.find(object->GetObjectId());

  if (it == tooltips.end())
  {
    SOvertip& overtip = tooltips[object->GetObjectId()];

    overtip.worldObject = object;
    overtip.valid = true;
    overtip.selected = selected;
    overtip.picked = picked;
  }
  else
  {
    SOvertip& overtip = it->second;

    overtip.valid = true;
    overtip.selected = selected;
    overtip.picked = picked;
  }
}

void ObjectsInfo2dLogic::UpdateOvertip( const ObjectInfo& info, SOvertip & overtip )
{
  NI_PROFILE_FUNCTION;

  const NDb::AdventureTooltipSettings* const db_tooltip = presentation->GetTooltipSettings(info);

  NI_VERIFY(!!db_tooltip, "Invalid tooltip settings!", return);

  const NWorld::PFBaseHero* const baseHero = GetObject<NWorld::PFBaseHero>(info);
  const NWorld::PFBaseUnit* const baseUnit = baseHero ? baseHero : GetObject<NWorld::PFBaseUnit>(info);
  const NWorld::PFLogicObject* const logicObject = baseUnit ? baseUnit : GetObject<NWorld::PFLogicObject>(info);

  const bool isHero = EObjectKind::IsHero(info.kind);

  SOvertipCustomEnergy customEnergy;

  if (isHero && baseHero->HasCustomEnergy())
  {
    {
      customEnergy.enabled = true;
    }

    if (overtip.customEnergy.enabled)
    {

    }
    else
    {
      customEnergy.needMaterial = true;
      customEnergy.stateName.clear();

      customEnergy.stateName += db_tooltip->uiState;
      customEnergy.stateName += "-";
      customEnergy.stateName += baseHero->GetDbHero()->persistentId;
    }
  }

  if (overtip.UpdateDesc(db_tooltip) || overtip.NeedUpdateCustomEnergy(customEnergy))
  {
    SetupOvertip(overtip, customEnergy);
  }

  NI_VERIFY(overtip.IsValid(), NStr::StrFmt("Tooltip for object of type '%s' is invalid!", overtip.GetWorldObjectTypeName()), return);

  const NGameX::PFClientLogicObject* const clientObject = logicObject ? logicObject->ClientObject() : 0;

  //Let's try to get to collision
  if ( !!clientObject )
  {
    if ( clientObject->GetCollisionHull() )
    {
      overtip.worldPosition = clientObject->GetPosition().pos; 
      overtip.worldPosition.z = clientObject->GetCollisionHull()->GetBounds().s.ptCenter.z;
      overtip.worldPosition.z += clientObject->GetCollisionHull()->GetBounds().s.fRadius / sqrtf( 3.0f );
    }
    else if ( clientObject->GetSceneObject() )
    {
      overtip.aabb = clientObject->GetSceneObject()->GetRootComponent()->GetWorldAABB();
      overtip.worldPosition = overtip.aabb.center;
      overtip.worldPosition.z += overtip.aabb.halfSize.z;
    }
  }

  const NGameX::PFClientBaseUnit* const clientUnit = !!baseUnit ? baseUnit->ClientObject() : NULL;

  if ( !!clientUnit )
  {
    overtip.worldSize = clientUnit->UiBarsWorldSize();
    overtip.screenSize = clientUnit->UiBarsScreenSize();
  }
  else
  {
    overtip.worldSize = 10.0f;
    overtip.screenSize = 256;
  }

  if (overtip.caps & WindowCaps::Health)
  {
    const bool canShowStripes = overtip.wndHealth->CanShowStripes();
    const bool canShowShield = overtip.wndHealth->CanShowShield();

    overtip.showStripes = canShowStripes && isHero;
    overtip.showShield = canShowShield;
  }
  else
  {
    overtip.showStripes = false;
    overtip.showShield = false;
  }

  //Params from Units
  if ( !!baseUnit )
  {
    overtip.health        = baseUnit->GetHealth();
    overtip.healthMax     = baseUnit->GetMaxHealth();

    if (customEnergy.enabled)
    {
      const float value = baseHero->GetCustomEnergyValue();
      const float maximum = baseHero->GetCustomEnergyMaximum();

      if (maximum > EPS_VALUE)
      {
        overtip.manaPercent = value / maximum;
        overtip.showMana = true;
      }
      else
      {
        overtip.manaPercent = 0.f;
        overtip.showMana = false;
      }
    }
    else
    {
      overtip.manaPercent   = baseUnit->GetManaPercent();
      overtip.showMana      = baseUnit->HasMana();
    }

    overtip.worldPosition.z += baseUnit->DbUnitDesc()->overtipVerticalOffset;
  }

  if (overtip.showShield)
    overtip.shield = GetShiled(baseUnit);
  else
    overtip.shield = 0.f;

  //Overtip text
  bool showText = false;

  if ( overtip.db->showDesc )
  {
    //We can show text for selected/highlighted objects OR heroes 
    showText =
      overtip.selected ||
      overtip.picked ||
      isHero;
  }

  if ( !!baseUnit )
  {
    if (baseUnit->IsDead())
      showText = false;
  }

  UpdateOvertipText(info, overtip, showText );

  //Channeling
  
  if ( !!baseUnit && baseUnit->IsInChannelling() )
    overtip.channelingPercent = baseUnit->GetChannellingProgress();
  else if ( !!baseHero && baseHero->HasScriptControlledProgressValue() )
    overtip.channelingPercent = baseHero->GetScriptControlledProgressValue();
  else
    overtip.channelingPercent = 0.0f;

  //Debug draw
  if ( s_drawTooltipBoxes && clientObject && clientObject->GetCollisionHull() )
  {
    const NScene::CollisionGeometry * geo = clientObject->GetCollisionHull()->GetGeometry();
    for ( int ei = 0; ei < geo->GetEdges().size(); ++ei )
    {
      const NScene::CollisionGeometry::Edge & e = geo->GetEdges()[ei];
      const CVec3 & from = geo->GetPoints()[e.start], & to = geo->GetPoints()[e.finish];
      Render::DebugRenderer::DrawLine3D( overtip.worldPosition + from, overtip.worldPosition + to, Render::Color( 0, 255, 255 ), Render::Color( 0, 255, 255 ), false );
    }
  }
}

void ObjectsInfo2dLogic::UpdateOvertipText( const ObjectInfo& info, SOvertip & overtip, const bool showText )
{
  NI_PROFILE_FUNCTION;

  switch (info.kind)
  {
  case EObjectKind::Unit:
    UpdateOvertipTextImpl(overtip, GetObjectUnchecked<NWorld::PFBaseUnit>(info), showText);
    return;
  case EObjectKind::Hero:
  case EObjectKind::LocalHero:
    UpdateOvertipTextImpl(overtip, GetObjectUnchecked<NWorld::PFBaseHero>(info), showText);
    return;
  case EObjectKind::Glyph:
    UpdateOvertipTextImpl(overtip, GetObjectUnchecked<NWorld::PFGlyph>(info), showText);
    return;
  case EObjectKind::NatureGlyph:
    UpdateOvertipTextImpl(overtip, GetObjectUnchecked<NWorld::PFNatureGlyph>(info), showText);
    return;
  case EObjectKind::Consumable:
    UpdateOvertipTextImpl(overtip, GetObjectUnchecked<NWorld::PFConsumableChest>(info), showText);
    return;
  }

  NI_ALWAYS_ASSERT(NStr::StrFmt("Unknown object type '%s' in overtip!", overtip.GetWorldObjectTypeName()));
}

void ObjectsInfo2dLogic::SetSpectatorMode(const bool value)
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

ConstPtr<NWorld::PFBaseHero> ObjectsInfo2dLogic::s_pHighlightLevelHero;
bool ObjectsInfo2dLogic::s_bShowLevelHighlighting = false;

void ObjectsInfo2dLogic::SetLevelHighlighting( const NWorld::PFBaseHero* pHero, bool show )
{
  if ( s_bShowLevelHighlighting == show )
    return;

  if ( !show )
  {
    if ( AdventureScreen* advScreen = AdventureScreen::Instance() )
    {
      advScreen->ShowTutorialOvertipLevelHighlight( false, 0, 0 );
    }

    s_pHighlightLevelHero = 0;
    s_bShowLevelHighlighting = false;
  }
  else
  {
    s_pHighlightLevelHero = pHero;
    s_bShowLevelHighlighting = true;
  }
}




namespace
{
  class ObjectInfoBoolFormulaVariant
    : public NonCopyable
    , public NNameMap::Variant
  {
  public:
    ObjectInfoBoolFormulaVariant(const NWorld::PFBaseHero* const hero, const ExecutableBoolString& formula)
      : hero(hero)
      , formula(formula)
    {
    }

    virtual bool GetBool() const
    {
      return formula(hero, AdventureScreen::Instance()->GetHero(), NULL, false);
    }

    virtual NNameMap::VariantType::Enum GetType() const
    {
      return NNameMap::VariantType::Bool;
    }

    virtual bool IsReadonly() const
    {
      return true;
    }
  private:
    ObjectInfoBoolFormulaVariant();

    const NWorld::PFBaseHero* const hero;
    const ExecutableBoolString& formula;
  };

  NNameMap::Variant * ResolveVariantInternal(NWorld::PFBaseHero const *pObject, const char * name, int length, const char * args, int argsLength, void* prms, bool readonly )
  {
    NWorld::PFWorld* pWorld = AdventureScreen::Instance()->GetWorld();

    NI_VERIFY( pWorld && pWorld->GetAIWorld(), "ConditionsResolver : World is invalid!", return NULL; );
    
    const NDb::AILogicParameters& aiParams = pWorld->GetAIWorld()->GetAIParameters();

    for ( vector<NDb::Ptr<NDb::ConditionFormula>>::const_iterator iCond = aiParams.conditionFormulas.begin(), iEnd = aiParams.conditionFormulas.end(); iCond != iEnd; ++iCond )
      if ( (*iCond)->name == name )
        return new ObjectInfoBoolFormulaVariant( pObject, (*iCond)->condition );

    NI_ALWAYS_ASSERT( NStr::StrFmt("Condition '%s' not found in vector 'conditionFormulas' in GameLogic/AILogic.AIPL!", name) );

    return NULL;
  }
} //namespace




NNameMap::Variant * ConditionalNameMap::ResolveVariant( const char * name, int length, const char * args, int argsLength, void* prms, bool readonly )
{
  return ResolveVariantInternal(pObject, name, length, args, argsLength, prms, readonly);
}



NAMEMAP_BEGIN(ConditionalNameMap)
NAMEMAP_END



NAMEMAP_BEGIN(TupleUnit<ConditionalNameMap>)
  NAMEMAP_CUSTOM_SUBMAP(if, const_cast<ConditionalNameMap*>(pObject), pObject)
NAMEMAP_END


} // namespace NGameX

NI_DEFINE_REFCOUNT( NGameX::ObjectsInfo2dLogic )
