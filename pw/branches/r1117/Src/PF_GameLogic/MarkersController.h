#pragma once

namespace NWorld
{
  class PFBaseUnit;
}

namespace NGameX
{
  class Minimap;
}


namespace NGameX
{

struct UnitMarker : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( UnitMarker, BaseObjectST );
  UnitMarker( CPtr<NWorld::PFBaseUnit> const& pUnit, float duration, CObj<PF_Core::BasicEffect>& pAttachEffect, NDb::EMinimapEffects minimapEffect, Minimap * _minimap);
  ~UnitMarker();

  CPtr<NWorld::PFBaseUnit> pUnit;
  CObj<PF_Core::BasicEffect> pAttachEffect;
  int minimapEffectIndex;
  float duration;
  NDb::EFaction faction;
  CPtr<Minimap> minimap;
};

class MarkersController : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( MarkersController, BaseObjectST );
public:
  MarkersController( NDb::Ptr<NDb::DBUIData> const& pUIData, Minimap * _minimap, NDb::EFaction faction)
    : pUIData( pUIData )
    , minimap(_minimap)
    , playerFaction(faction){}
  void AddMarker( CPtr<NWorld::PFBaseUnit> const& pUnit, NDb::EFaction faction );
  void AddChatMarker(CPtr<NWorld::PFBaseUnit> const& pUnit);
  void Update( float dt );
  
private:
  void RemoveAdjacentMarkers(CPtr<NWorld::PFBaseUnit> const& pUnit);

  CPtr<Minimap> minimap;
  nstl::list<Strong<UnitMarker>> markers;
  NDb::Ptr<NDb::DBUIData> pUIData;
  NDb::EFaction playerFaction;
};

}
