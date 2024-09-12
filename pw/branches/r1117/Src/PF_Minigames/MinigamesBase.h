#pragma once

#include "MinigameSessionInterface.h"
#include "PF_Core/WorldObject.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace PF_Minigames
{

class MinigamesMain;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class MinigamesBase : public IMinigames, public PF_Core::WorldObjectBase
{
  OBJECT_METHODS( 0xC5739380, MinigamesBase )

public:

  MinigamesBase( NWorld::PFWorld * _pWorld );
	virtual ~MinigamesBase();

  // IMinigames:
  virtual bool    StartMinigame( NWorld::PFMinigamePlace * place );
  virtual void    LeaveMinigame();
  virtual void    SetLocal( bool _isLocal ) { isLocal = _isLocal; };
  virtual bool    IsLocal() const { return isLocal; }

  virtual void    OnStep( float deltaTime );

  virtual IMinigamesMain* GetMain() const;

  virtual IWorldSessionInterface * GetWorldSessionInterface() const { return worldSessInterface; }

  virtual int     MinigamesCount();
  virtual ISingleMinigame * GetMinigame( const char * id );
  virtual ISingleMinigame * GetMinigame( int index );
  virtual const char * GetMinigameId( int index );

  virtual ISingleMinigame * GetCurrentMinigame() { return currentMinigame; }

  void ForceLeaveMinigame();

  virtual void    OnMapLoaded();

  //Client part of IMinigames
  virtual void    UpdateM( float deltaTime );
  virtual void    SetPlacement( const Placement & _placement ) {}
  virtual float   GetMinigamePlaceOpacity() const { return 0; }
  virtual bool    DoFade() const { return false; }

  void            PlaceUnderFogOfWar( bool underFogOfWar ) {}

  void            SetMinigamesMain( MinigamesMain* _main ) { main = _main; }
  MinigamesMain * GetNativeMain() const { return main; }

  void            SetSessionInterface( IWorldSessionInterface * _worldInterface);

  void  PauseMinigame( bool enablePause );
  virtual void InitGames() {}
  virtual void ReinitGames();

  template <class _Minigame>
	_Minigame* GetNativeMinigame( const nstl::string& gameName );

protected:
  MinigamesBase() {};

  void RegisterMinigame( const CObj<ISingleMinigame> & mg, const char * id );

private:
	typedef nstl::hash_map<nstl::string, CObj<ISingleMinigame> > MinigamesList;

  
  CPtr<MinigamesMain> main;
  CPtr<IWorldSessionInterface> worldSessInterface;

  bool isLocal;

  ZDATA
  ZNOPARENT(IMinigames)
  ZNOPARENT(PF_Core::WorldObjectBase)

  CPtr<ISingleMinigame> currentMinigame;
  MinigamesList minigames; 

  bool  paused;

public:
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&currentMinigame); f.Add(3,&minigames); f.Add(4,&paused); return 0; }
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class _Minigame>
inline _Minigame* MinigamesBase::GetNativeMinigame( const nstl::string& gameName )
{
	MinigamesList::iterator it = minigames.find( gameName );

	if ( minigames.end() == it )
		return 0;

	return dynamic_cast<_Minigame*>( it->second.GetPtr() );
}

} // namespace PF_Minigames
