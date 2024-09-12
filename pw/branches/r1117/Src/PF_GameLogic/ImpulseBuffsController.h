#pragma  once

#include "../UI/FSCommandListner.h"


#include "PrecompiledTooltips.h"
#include "PFImpulsiveBuffs.h"

#include "../System/Heap.h"
//#include <set>


namespace UI            
{ 
	class FlashContainer2; 
	class ImageLabel;
}

namespace NWorld
{
	class ImpulsiveBuffsManager;
	class PFBaseHero;
}

namespace NGameX
{
	class AdventureTooltip;
	class AdventureFlashInterface;
}

namespace NGameX
{
class ImpulseBuffsController : public UI::IFSCommandListner, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( ImpulseBuffsController, UI::IFSCommandListner, BaseObjectST );

public:
	ImpulseBuffsController( UI::FlashContainer2* flashContainer, UI::ImageLabel * tooltipWnd, AdventureFlashInterface * _flashInterface,
		const NDb::ImpulsiveBuffsParams & _params, NWorld::ImpulsiveBuffsManager * buffsManager, const NWorld::PFBaseHero * _hero);
  ~ImpulseBuffsController();

	void Update(float dt, int mouseX, int mouseY);

	void SuggestImpulse( NWorld::Impulse * _impulse, const NWorld::Target & _target );

	void BuyImpulse(bool fromKeyboard);

	// from UI::IFSCommandListner
	virtual void OnFSCommand( UI::FlashContainer2* _wnd, const char* listenerID,  const char* args, const wchar_t * argsW  );

private:

	void HideImpulse();

  Weak<UI::FlashContainer2> flashWnd;

	// Params
	NDb::ImpulsiveBuffsParams params;

	NWorld::Impulse *	impulse;
	float				lifeTime;
	NWorld::Target		target;


	CPtr<NWorld::ImpulsiveBuffsManager> impulseBuffsManager;
	ConstPtr<NWorld::PFBaseHero> hero;

	PrecompiledTooltip        nameTooltip;
	PrecompiledTooltip        descTooltip;

	CObj<AdventureTooltip>    tooltip;
  wstring                   tooltipText;
			
	Weak<AdventureFlashInterface>      flashInterface;

};

};//namespace NGameX

