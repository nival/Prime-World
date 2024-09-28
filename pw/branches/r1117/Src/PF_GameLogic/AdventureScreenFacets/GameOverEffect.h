#ifndef GAMEOVEREFFECT_H_0CEBD1A4_0C79_4
#define GAMEOVEREFFECT_H_0CEBD1A4_0C79_4

#include "./../../System/TimeHelpers.h"
#include "./../PF_Core/DBEffect.h"

namespace PF_Core
{
  class BasicEffectStandalone;
}

namespace NWorld
{
  class PFAIWorld;
}

namespace NGameX 
{ 

class AdventureScreen;

namespace AdventureScreenFacets
{
class GameOverEffect
{
public:
  explicit GameOverEffect( AdventureScreen *pAdvScreen );
  void Update( float dt );
  void Start( NDb::EFaction failedFaction );
  void PrecacheEffects();
  void setCameraCanBeMoved( bool val ) { cameraCanBeMoved = val; }
  void UpdateBuildingsInfo( NWorld::PFAIWorld* pWorld );
     
private:
  typedef nstl::map<NDb::EFaction, CVec3> FactionToPos;
  class BuildingCollector;
  
private:  
  SimpleTimer startEffectTimer;
  AdventureScreen *pAdvScreen;
  NDb::Ptr<NDb::BasicEffectStandalone> effectId;
  CVec3 targetPos;
  CObj<PF_Core::BasicEffectStandalone > effectPtr;
  bool cameraCanBeMoved;   
  
  //ѕосле уведомлении о том, что игра завершилась здание уже уничтожено и
  //получить его координаты не получаетс€. ѕоэтому будем их сохран€ть пока 
  //здание ещЄ живо
  FactionToPos factionToPos;
};

}}

#endif //#define GAMEOVEREFFECT_H_0CEBD1A4_0C79_4