#pragma once

#include "MinigameWorldObject.h"


namespace PF_Minigames
{

class Clinic;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ClinicItem : public MinigameWorldObject
{
	OBJECT_METHODS( 0x9A678C01, ClinicItem )

public:
  ClinicItem() : isBought(true), isInRoute(false) {}
  virtual ~ClinicItem() {}

	void SetClinic(Clinic * _clinic) { clinic = _clinic; }

  virtual const NDb::BaseUIMaterial* GetIconMaterial() const { return 0; };
  virtual int GetCost() const { return 0; }
	virtual int GetAccessibility() const { return 0; }

	void SetBought( bool _isBought ) { isBought = _isBought; }
	bool IsBought() const { return isBought; }

  bool IsInRoute() const { return isInRoute; }
  void ClearInRoute() { isInRoute = false; }
  void SetInRoute() { isInRoute = true; }

  // from MinigameWorldObject
	virtual bool OnClick();
  virtual void OnBuyCommand();

protected:
	CPtr<Clinic> clinic;

private:
  ZDATA_(MinigameWorldObject)
	bool isBought;
  bool isInRoute;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(MinigameWorldObject*)this); f.Add(2,&isBought); f.Add(3,&isInRoute); return 0; }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace PF_Minigames

