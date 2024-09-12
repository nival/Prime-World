#pragma once

#include "../Scripts/LuaSubclass.h"

#include "../Client/ScreenUILogicBase.h"
#include "PrecompiledTooltips.h"
#include "UnitNameMap.h"

#include "ObjectInfoHelper.h"

namespace NWorld
{ 
  class PFAIWorld; 
  class PFBaseUnit; 
  class PFChest;
  class PFBaseHero;
}


namespace UI
{
  class Window;
  class ImageLabel;
  class ProgressBar;
}


namespace NGameX
{

class ObjectsInfo2dLogic : public UI::ClientScreenUILogicBase
{
  NI_DECLARE_REFCOUNT_CLASS_1( ObjectsInfo2dLogic, UI::ClientScreenUILogicBase );

public:
  explicit ObjectsInfo2dLogic( int );

  void Init( UI::User * uiUser );
  void SetTooltipParams( const NDb::AdventureTooltipParams* settings );
  void Update( float deltaTime, const SHMatrix & projectionMatrix );
  void SetLocalHero(const NWorld::PFBaseHero* const _hero);

  void ShowHealthBars( bool show ) { showHealthBars = show; }
  void ToggleShowHealthBars() { showHealthBars = !showHealthBars; }

  void UpdateObject( const PF_Core::WorldObjectBase * object, bool selected, bool picked );

  void SetSpectatorMode(const bool value);

  static void SetLevelHighlighting( const NWorld::PFBaseHero* pHero, bool show );

private:

  struct SOvertip;
  struct SOvertipWindow;
  struct SOvertipCustomEnergy;

  class Presentation;
  class FactionPresentation;
  class FriendOrFoePresentation;

  friend class Presentation;
  friend class FactionPresentation;
  friend class FriendOrFoePresentation;

  typedef multimap< string, SOvertipWindow > WindowsPool;
  typedef hash_map< int, SOvertip > Tooltips;

  ////data////
  NDb::Ptr<NDb::AdventureTooltipParams>  settings;

  int  idCounter;
  bool  showHealthBars;
  Tooltips tooltips;
  WindowsPool windowsPool;

  ConstPtr<NWorld::PFBaseHero> localHero;

  ScopedPtr<class Presentation> presentation;

  DI_WEAK(ObjectInfoHelper) objectInfoHelper;

  static ConstPtr<NWorld::PFBaseHero> s_pHighlightLevelHero;
  static bool s_bShowLevelHighlighting;

  /////code/////
  const NDb::AdventureTooltipSettings * GetTooltipSettings( const PF_Core::WorldObjectBase * object ) const;

  template<class T>
  void UpdateOvertipTextImpl( SOvertip & overtip, const T * object, const bool showText );
  void UpdateOvertipText( const ObjectInfo& info, SOvertip & overtip, const bool showText );
  void SetupOvertip( SOvertip & overtip, const SOvertipCustomEnergy& customEnergy );
  void UpdateOvertip( const ObjectInfo& info, SOvertip & overtip );
  void UpdateTooltipUI( const ObjectInfo& info, SOvertip & overtip, const SHMatrix & projectionMatrix );

  void GetWindowFromPool( const WindowsPool::key_type &key, WindowsPool::mapped_type &window );
  void AddWindowToPool( const WindowsPool::mapped_type &window );
};

} // namespace NGameX
