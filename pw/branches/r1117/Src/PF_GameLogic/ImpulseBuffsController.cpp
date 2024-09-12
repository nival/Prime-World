#include "stdafx.h"
#include "ImpulseBuffsController.h"

#include "DBStats.h"
#include "PFUniTarget.h"
#include "PFAbilityData.h"
#include "PFImpulsiveBuffs.h"
#include "AdventureTooltip.h"
#include "../System/NameMap.h"
#include "SessionEventType.h"
#include "AdventureScreen.h"
#include "AdventureFlashInterface.h"
#include "PFHero.h"

#include "FlashFSCommands.h"

#include "../UI/Cursor.h"
#include "../ui/FlashContainer2.h"
#include "../UI/ImageLabel.h"

namespace NGameX
{


ImpulseBuffsController::ImpulseBuffsController( UI::FlashContainer2* flashContainer, UI::ImageLabel * tooltipWnd, AdventureFlashInterface * _flashInterface,
	const NDb::ImpulsiveBuffsParams & _params, NWorld::ImpulsiveBuffsManager * buffsManager, const NWorld::PFBaseHero * _hero)
: params( _params )
, impulseBuffsManager(buffsManager)
, hero(_hero)
, flashInterface(_flashInterface)
, impulse(0)
, lifeTime(0)
, flashWnd(flashContainer)
{
	using namespace FlashFSCommands;

	flashWnd->AddFSListner(ConvertToString(BuyImpulseBuff), this);
	flashWnd->AddFSListner(ConvertToString(ImpulseBuffClose), this);
	flashWnd->AddFSListner(ConvertToString(ImpulseBuffToolTip), this);


	if (IsValid(impulseBuffsManager))
		impulseBuffsManager->SetImpulseBuffsController(this);

	tooltip = new AdventureTooltip( tooltipWnd );

	NI_ASSERT(0.0f < params.minLifeTime && params.minLifeTime <= params.maxLifeTime, "ImpBuffs: Wrong min/max life time parameter in xdb");
}


ImpulseBuffsController::~ImpulseBuffsController()
{
  using namespace FlashFSCommands;

  if (!IsValid(flashWnd))
    return;

  flashWnd->RemoveFSListner(ConvertToString(BuyImpulseBuff));
  flashWnd->RemoveFSListner(ConvertToString(ImpulseBuffClose));
  flashWnd->RemoveFSListner(ConvertToString(ImpulseBuffToolTip));

}


void ImpulseBuffsController::BuyImpulse(bool fromKeyboard)
{
	if( !impulse )
		return;

	//DebugTrace("BuyImpulse");

	if ( IsValid(impulseBuffsManager) )
  {
    impulseBuffsManager->BuyImpulse( impulse, target );
    impulse->SetForced( false );
  }

	impulse = 0;
  //DebugTrace("remove impulse cause of buying it");
	flashInterface->HideImpulseBuff(true, fromKeyboard);
}




void ImpulseBuffsController::Update(float dt, int mouseX, int mouseY)
{
	if ( !dt  || !impulse)
		return;

	
	lifeTime -= dt;
	
	bool shouldRemoveImpulse = lifeTime < 0 || !impulse->IsEnabled( hero, NDb::IMPULSIVEEVENTTYPE_HEROEVENT, target );
	
	if ( shouldRemoveImpulse)
	{
    //DebugTrace("remove impulse due to time or inability, lifetime = %f", lifeTime);
		HideImpulse();
	}

	//tooltip
	if (tooltip->IsVisible())
	{
		tooltip->SetLocation(mouseX , mouseY);
	}
}

void ImpulseBuffsController::HideImpulse()
{
  if ( impulse )
  {
    impulse->SetForced( false );
  }
	impulse = 0;
	flashInterface->HideImpulseBuff(false, false);
}

void ImpulseBuffsController::SuggestImpulse( NWorld::Impulse * _impulse, const NWorld::Target & _target)
{  
	if (impulse && impulse->priority >= _impulse->priority)
		return;
	
	if ( !_impulse || !_impulse->IsEnabled( hero, NDb::IMPULSIVEEVENTTYPE_HEROEVENT, _target ) )
		return;

  //replace if already have something
  bool sholdReplaceImpulse = impulse != 0;

	impulse = _impulse;
	target = _target;
  lifeTime = impulse->isForced ? 0.0f : impulse->offerTime;

  if (lifeTime<=0)
    lifeTime = 10e4;

	CObj<NWorld::PFAbilityData> pAbilityData = new NWorld::PFAbilityData( const_cast<NWorld::PFBaseHero *>(hero.GetPtr()), impulse->buff, NDb::ABILITYTYPEID_IMPULSIVEBUFF, false );

	pAbilityData->SetZZCost( impulse->goldCost );

	if( IsValid( impulse->buff->image ) )
  {
    //DebugTrace("show impulse. suggested new");
    const char * imagePath = impulse->buff->image->textureFileName.c_str();
		
    if (sholdReplaceImpulse)
      flashInterface->ResetImpulsBuff(imagePath); //replace the old one
    else
      flashInterface->ShowImpulseBuff(imagePath); //just show it

    if (AdventureScreen* pAdvScreen = AdventureScreen::Instance())
    {
      StatisticService::RPC::SessionEventInfo params;
      params.intParam1 = impulse->buff->GetDBID().GetHashKey();
      pAdvScreen->LogSessionEvent(hero, SessionEventType::ImpulsiveBuffSuggested, params);
    }
  }

	descTooltip.Init(pAbilityData, impulse->buff->description.GetText());
	descTooltip.MakeText(tooltipText);
}

void ImpulseBuffsController::OnFSCommand( UI::FlashContainer2* _wnd, const char* listenerID, const char* args, const wchar_t * argsW  )
{
	using namespace FlashFSCommands;

	switch (ConvertToFSCommand(listenerID))
	{
	case BuyImpulseBuff:
		{
			//DebugTrace("fscommand::BuyImpulseBuff");
			BuyImpulse( false);
			break;
		}
	case ImpulseBuffClose:
		{
			if (impulse && IsValid(impulseBuffsManager))
      {
        //DebugTrace("RefuseFromImpulse");
        impulseBuffsManager->RefuseFromImpulse(impulse);
      }
      impulse = 0;
			break;
		}
	case ImpulseBuffToolTip:
		{
			//DebugTrace("fscommand::ImpulseBuffToolTip");
			int show;
			sscanf_s(args,"%d",&show);
      tooltip->SetText(tooltipText);
			tooltip->Show(show);
			break;
		}
	}
}


}; //namespace NGameX

NI_DEFINE_REFCOUNT(NGameX::ImpulseBuffsController)
