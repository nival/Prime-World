#pragma once

#include "../UI/FSCommandListner.h"

namespace NWorld
{
  class PFBaseUnit;
  class PFBaseApplicator;
  class PFApplStatus;
  class PFApplStatMod;
}

namespace UI            
{ 
  class FlashContainer2; 
  class ImageLabel;
}

namespace BuffsOwner
{
  enum EBuffsOwner
  {
    OurHero,
    Selection
  };
}

namespace NGameX
{
  class AdventureFlashInterface;
  class AdventureTooltip;

  class BuffsController : public UI::IFSCommandListner, public BaseObjectST
  {
    NI_DECLARE_REFCOUNT_CLASS_2( BuffsController, UI::IFSCommandListner, BaseObjectST );

  public:
    BuffsController(UI::FlashContainer2* flashContainer, UI::ImageLabel * tooltipWnd, AdventureFlashInterface * _flashInterface, BuffsOwner::EBuffsOwner _buffsOwner);

    void SetUnit(const NWorld::PFBaseUnit * _unit);

    void Update(int mouseX, int mouseY);

     void operator()( NWorld::PFBaseApplicator const* applicator );

    // from UI::IFSCommandListner
    virtual void OnFSCommand( UI::FlashContainer2* _wnd, const char* listenerID,  const char* args, const wchar_t * argsW  );

  private:

    struct Status
    {
      NWorld::PFApplStatus const* applicator;
      NWorld::PFApplStatus const* maxDurationApplicator;
      vector<NWorld::PFApplStatMod const*> statModsContainer;
      int count;

      Status(): applicator(0), maxDurationApplicator(0), count(-1) {}
      Status( NWorld::PFApplStatus const *applicator_ );
    };

    struct BuffStatus
    {
      BuffStatus();
      string image;
      float cooldown;
      int  count;
      wstring tooltip;
      bool isPositive;
      NWorld::PFApplStatus const *applicator;
      vector<NWorld::PFApplStatMod const*> statModsContainer;
    };

    void FillBuffStatus(int index, BuffStatus &buff, const Status * status);

    void ApplyStatuses();
    bool IsPositiveBuff( NWorld::PFApplStatus const* applicator );
    
    BuffsOwner::EBuffsOwner buffsOwner;
    
    ConstPtr<NWorld::PFBaseUnit>   unit;

    CObj<AdventureTooltip>        tooltip;
    Weak<AdventureFlashInterface>          flashInterface;

    vector<Status>      statuses;
    vector<BuffStatus>  buffStatuses;
    int lastBuffsCount;
    int ttIndex;
   
  };

} //namespace NGameX
