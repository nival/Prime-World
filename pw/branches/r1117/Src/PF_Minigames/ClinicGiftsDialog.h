#pragma once

#include "../Client/MessageDialog.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace PF_Minigames
{
	class ClinicPlace;
};



namespace UI
{

class ClinicGiftsDialog : public NMainLoop::IMessageScreenCallback, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( ClinicGiftsDialog, NMainLoop::IMessageScreenCallback, BaseObjectST );

public:
  ClinicGiftsDialog() {}

  void ResetGifts() { giftedPlaces.clear(); }

  void AddGift(PF_Minigames::ClinicPlace * place) { giftedPlaces.insert(place); }

  void PopUp();

protected:
  //IMessageScreenCallback
  virtual void SetupMessageWindow(UI::Window * pScreenBaseWindow);
  virtual void OnYesButton();
  virtual void OnNoButton() {}
  virtual bool OnEscapeKey();

private:
  typedef nstl::set<CPtr<PF_Minigames::ClinicPlace> > PlacesSet;

  PlacesSet                         giftedPlaces;
};

}; //namespace UI
