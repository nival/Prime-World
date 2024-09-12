#pragma once

#include "../UI/Window.h"
#include "../UI/ScreenLogicBase.h"
#include "../Client/ScreenBase.h"
#include "../Scripts/Script.h"
#include "../Scripts/ScriptMacroses.h"

namespace NWorld
{
  class PFBaseUnit;
}

namespace NGameX
{

class FlyText;
class UIFlyTextsLogic;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class UIFlyTexts : public CObjectBase
{
  OBJECT_BASIC_METHODS( UIFlyTexts )
public:
  UIFlyTexts();

  void Init( UI::User * uiUser );
  void AddFlyText( const NWorld::PFBaseUnit * unit, const NDb::FlyOffText * dbDesc, const NNameMap::Map * nmMap, const SHMatrix & sceneToScreen );

  void Update( float deltaTime, const SHMatrix & sceneToScreen );

  void Render();
private:
  void pushFlyOff(FlyText* pText, const SHMatrix & sceneToScreen);

  typedef nstl::vector<CObj<FlyText>> TFlyTexts;

  struct UnitFlyTexts
  {
    ConstPtr<NWorld::PFBaseUnit> unit;
    TFlyTexts flyTexts;
  };

  typedef nstl::vector< UnitFlyTexts > TUnitFlyTextArray;
  Strong<UIFlyTextsLogic> pLogic;
  TUnitFlyTextArray     flyTextsArray;
};

} //namespace NGameX
