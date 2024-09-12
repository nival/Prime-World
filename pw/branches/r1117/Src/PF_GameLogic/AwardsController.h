#pragma once

#include "../UI/FSCommandListner.h"
#include "Server/LobbyPvx/CommonTypes.h"
#include "Server/Roll/RollTypes.h"

namespace NWorld
{
  class PFResourcesCollection;
}

namespace UI            
{ 
  class FlashContainer2; 
  class ImageLabel;
}

namespace NDb
{
  enum EFaction;
  struct DBUIData;
	struct FWODVisualInfo;
}



namespace NGameX
{
  class AdventureFlashInterface;
  class AdventureTooltip;
	class HeroRankCalculator;
	class PlayerDataManager;

	typedef int UserId;


  struct AwardData
  {
    roll::EAwardType::Enum  type;
    int               id;  // crc32 from persistentId in xdb data, GetWorld()->GetResourcesCollection()
    string            customCurrencyId;
    float             count;
    uint              vendorCost;
    bool              isOwnedByPlayer;
		bool							isTasty;
		UserId            giverUser;
#ifndef _SHIPPING
    string            persistentId;
#endif
  };



  class AwardsController : public UI::IFSCommandListner, public BaseObjectST
  {
    NI_DECLARE_REFCOUNT_CLASS_2( AwardsController, UI::IFSCommandListner, BaseObjectST );

  public:
    AwardsController( UI::FlashContainer2* flashContainer, NDb::AILogicParameters const& _dbLogic,   const NDb::DBUIData * _uiData, UI::ImageLabel * tooltipWnd, AdventureFlashInterface * _flashInterface, const NWorld::PFResourcesCollection * _resources, NDb::EFaction _faction, int _experience, int _rating, HeroRankCalculator * _rankCalculator, const PlayerDataManager* playersData_ );
    ~AwardsController();

    void Update(int mouseX, int mouseY);

    void AwardUser(const nstl::vector<AwardData> & _awards);

		void SetFirstWinInfo(NDb::FWODVisualInfo * fwodInfo_) { fwodInfo = fwodInfo_; }

    // from UI::IFSCommandListner
    virtual void OnFSCommand( UI::FlashContainer2* _wnd, const char* listenerID,  const char* args, const wchar_t * argsW  );

  private:

    struct Award
    {
			roll::EAwardType::Enum  type;//for sorting
      string image;
      wstring tooltip;
      float count;
      int vendorConst;
			bool isTasty; //значит мы получили эту награду благодоря FWOD или еще какой фигне
			UserId giverUser;
    };

    const NDb::EResourceType GetResourceTypeByType( const roll::EAwardType::Enum type ) const;
    const NDb::EClanWarsResourceType GetCWResourceTypeByAwardType( const roll::EAwardType::Enum type ) const;

    void FillResourceAward( Award &award, const NDb::EResourceType resourceType, NDb::EFaction faction );
    void FillResourceAward(Award &award, const NDb::ResourceDescription &resource, NDb::EFaction faction);

    template<typename T>
    const NDb::ResourceDescription &GetResource(const nstl::vector<NDb::ResourceDescription>& resources, T resourceType) const
    {
      return resources[resourceType];
    }

    ConstPtr<NWorld::PFResourcesCollection> resources;
    NDb::Ptr<NDb::DBUIData>         uiData;
    NDb::AILogicParameters const&   dbLogic;
		Strong<HeroRankCalculator> rankCalculator ;
		ConstPtr<PlayerDataManager> playersData;

    Weak<UI::FlashContainer2> flashWnd;
    CObj<AdventureTooltip>        tooltip;
    Weak<AdventureFlashInterface> flashInterface;
    NDb::EFaction faction;

		NDb::Ptr<NDb::FWODVisualInfo> fwodInfo;

    int experience;
    int rating;
    

    vector<Award> awards;
  };

} //namespace NGameX
