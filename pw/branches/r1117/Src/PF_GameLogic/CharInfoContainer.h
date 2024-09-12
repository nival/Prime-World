#pragma once

#include "../UI/FSCommandListner.h"

namespace NWorld  
{ 
  class PFBaseUnit;
  class PFBaseHero;
}

namespace NDb { struct DBUIData;}

namespace UI            
{ 
  class FlashContainer2; 
  class ImageLabel;
}

namespace NGameX
{
  class AdventureFlashInterface;
  class CharInfoController;
  _interface IUIEventHandler;
}

namespace NGameX
{
  class CharInfoContainer : public UI::IFSCommandListner, public BaseObjectST
  {
    NI_DECLARE_REFCOUNT_CLASS_2( CharInfoContainer, UI::IFSCommandListner, BaseObjectST );

  public:
    CharInfoContainer( UI::FlashContainer2* flashContainer, UI::ImageLabel* _tooltipWnd, NDb::Ptr<NDb::DBUIData> _uiData, AdventureFlashInterface* _flashInterface, IUIEventHandler * _eventHandler);
    ~CharInfoContainer();
    
    void Update( int mouseX, int mouseY );

    void SetOurHero( const NWorld::PFBaseHero* _hero );

    void AddHero( const NWorld::PFBaseHero* _hero );
    void SetSelectionUnit( const NWorld::PFBaseUnit* _unit );

    // from UI::IFSCommandListner
    virtual void OnFSCommand( UI::FlashContainer2* _wnd, const char* listenerID,  const char* args, const wchar_t * argsW  );

  private:
    void UpdateController( CharInfoController* controller, int mouseX, int mouseY );
    
    NDb::Ptr<NDb::DBUIData>       uiData;
    Weak<UI::FlashContainer2>     flashWnd;
    Weak<AdventureFlashInterface> flashInterface;
    Weak<UI::ImageLabel>          tooltipWnd;
    
    ConstPtr<NWorld::PFBaseHero> ourHero;
    ConstPtr<NWorld::PFBaseUnit> selectionUnit;
  
    typedef map<int, Strong<CharInfoController>> HeroControllers;
    HeroControllers heroControllers;

    //our hero
    Strong<CharInfoController> charInfoController;
    //for selection
    Strong<CharInfoController> selectionCharInfoController;
    //current char info
    Weak<CharInfoController> currentCharInfoController;

    Weak<IUIEventHandler>         eventHandler;
    //current char info for talents
    Weak<CharInfoController> currentTalentsController;
  };
}
