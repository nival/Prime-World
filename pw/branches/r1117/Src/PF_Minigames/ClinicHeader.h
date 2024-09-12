#pragma once

namespace PF_Minigames
{

class ClinicItem;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//FIMXE: Unused for now...
_interface IClinicBuyUIRequest : public IObjectBase
{
  virtual void RequestBuy(ClinicItem * item) = 0; //ClinicBonus or ClinicPlace
};

} //namespace PF_Minigames
