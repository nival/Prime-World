#pragma once

#include "DBEasel.h"

namespace NDb
{
  enum EBoostType;
}

namespace PF_Minigames
{

class LuxBoost;
class EaselNotifier;
_interface IPriestessProxy;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class LuxBoostsFactory
{
public:
  explicit LuxBoostsFactory( Easel * easel );
  virtual ~LuxBoostsFactory();

  // factory methods
  LuxBoost* CreateBoost( NDb::EBoostType _type, const NDb::Ptr<NDb::DBEaselData>& _pData );

private:
  CPtr<Easel> easel;
  
  // factory methods
  LuxBoost* CreatePaintBlastBoost( NDb::EBoostUsage _usage, const NDb::Ptr<NDb::DBEaselData>& pData );
  LuxBoost* CreateJokerBoost( NDb::EBoostUsage _usage, const NDb::Ptr<NDb::DBEaselData>& pData );
  LuxBoost* CreateFreezeBoost( NDb::EBoostUsage _usage, const NDb::Ptr<NDb::DBEaselData>& pData );
  LuxBoost* CreateSorterBoost( NDb::EBoostUsage _usage, const NDb::Ptr<NDb::DBEaselData>& pData );  
  LuxBoost* CreateMagnetBoost( NDb::EBoostUsage _usage, const NDb::Ptr<NDb::DBEaselData>& pData );
  LuxBoost* CreateAlchemistBoost( NDb::EBoostUsage _usage, const NDb::Ptr<NDb::DBEaselData>& pData );
  
protected:

};


}
