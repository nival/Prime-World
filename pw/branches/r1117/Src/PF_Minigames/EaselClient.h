#pragma once 

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace PF_Core
{
  class BasicEffect;
  class BasicEffectStandalone;
  class BasicEffectAttached;
  class LightningEffect;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NDb
{
  struct BasicEffectStandalone;
  struct BasicEffectAttached;
  struct LightningEffect;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace PF_Minigames
{

class MinigameClientObject;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class stores and updates all client objects for esel minigame
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class EaselClient
{
public:
	EaselClient();

	// drop all client objects
	void Reset( bool allObjects );

	void AddObject( MinigameClientObject* object, bool permanent );
	void ReleaseObject( MinigameClientObject* object );


  //Either next functions can easely return 0 !
  CObj<PF_Core::BasicEffectStandalone> CreateStandaloneEffect( const NDb::BasicEffectStandalone * dbEffect, bool trackLifetime );
  CObj<PF_Core::BasicEffectAttached> CreateAttachedEffect( const NDb::BasicEffectAttached * dbEffect, bool trackLifetime );
  CObj<PF_Core::LightningEffect> CreateLightningEffect( const NDb::LightningEffect * dbEffect, bool trackLifetime );
  void ReleaseEffect( PF_Core::BasicEffect * effect, bool immediate = false );

  void ReleaseAll();

  void Step( float deltaTime );
	void Update( float deltaTime, bool gameOnPause );

  void ShowAll( bool show );

private:
  typedef nstl::map<CObj<MinigameClientObject>, bool > TClientObjects; // ( pointer, permanent flag )
  typedef set<CObj<PF_Core::BasicEffect> > TEffects;

  TClientObjects clientObjects;
  TEffects usedEffects;

  bool showAll;
};

} // PF_Minigames
