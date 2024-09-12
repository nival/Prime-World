#pragma once

#include "../Client/MessageDialog.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace PF_Minigames
{
	class Clinic;
	class ClinicItem;
};



namespace UI
{

class ClinigBuyDialog : public NMainLoop::IMessageScreenCallback, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( ClinigBuyDialog, NMainLoop::IMessageScreenCallback, BaseObjectST );

public:
  ClinigBuyDialog() : isItemAffordable(false), itemPrice(0) {}

  void Set(PF_Minigames::Clinic * _clinic) { clinic = _clinic; }

  void Popup(PF_Minigames::ClinicItem * pItem);

protected:
  //IMessageScreenCallback
  virtual void SetupMessageWindow(UI::Window * pScreenBaseWindow);
  virtual void OnYesButton();
  virtual void OnNoButton();
  virtual bool OnEscapeKey();

private:
  void ResetData();

  CPtr<PF_Minigames::Clinic>        clinic;
  CPtr<PF_Minigames::ClinicItem>    item2Buy;

  bool                              isItemAffordable;
  int                               itemPrice;
  wstring                           itemName;
  wstring                           itemDesc;
};

}; //namespace UI
