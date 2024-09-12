#ifndef LOADINGSCREEN_H_INCLUDED
#define LOADINGSCREEN_H_INCLUDED

#include "HybridServer/Peered.h"
#include "Client/DefaultScreenBase.h"
#include "LoadingScreenLogic.h"

class LoadingProgress;

namespace NGameX
{
  class ChatUiController;
  class IgnoreListStorage;

  _interface IPlayerIdMapper;
}

namespace Peered
{
  enum Status;
  struct ClientSettings;
}

namespace NDb
{
  struct AdvMapDescription;
  struct AdvMapSettings;
  struct DBUIData;
	enum EChatChannel;
	
}


namespace Game
{

  
class LoadingGameContext: public BaseObjectST
{
NI_DECLARE_REFCOUNT_CLASS_1( LoadingGameContext, BaseObjectST );
public:
  LoadingGameContext(const NCore::MapStartInfo& _mapStartInfo) : mapStartInfo(_mapStartInfo) {}

  Weak<NGameX::ChatUiController> chatController;
  NDb::Ptr<NDb::AdvMapDescription> advMapDescription;
  NDb::Ptr<NDb::AdvMapSettings> advMapSettings;
  Weak<NGameX::IgnoreListStorage> ignoreListStorage;
  lobby::SGameParameters params;
  const NCore::MapStartInfo& mapStartInfo;
  TLineUpHeroesInfo  lineup_info;

  int userId; 
};


class LoadingScreen : public NMainLoop::DefaultScreenBase
{
  NI_DECLARE_REFCOUNT_CLASS_1( LoadingScreen, NMainLoop::DefaultScreenBase );

public:
  LoadingScreen( const char * _back, const char * _logo, const bool _isSpectator, const bool _isTutorial );

  //virtual NMainLoop::EScreenLayer::Enum GetScreenLayer() const { return NMainLoop::EScreenLayer::Normal; }
  virtual bool Init( UI::User * uiUser ); 
  virtual void Step( bool bAppActive );

  void Setup (LoadingGameContext * _loadingGameContext  );

  void SetProgress( LoadingProgress * _progress ) { progress = _progress; }

  void SetPlayerProgress( int userId, float pro ) { if ( logic ) logic->SetPlayerProgress( userId, pro ); }
  void SetHeroInfo( int userId, HeroInfo & heroInfo  );
  void OnClientStatusChange( int userId, int newStatus, int step  );

  void ApplyClientSettings(const NCore::ClientSettings & _clientSettings);


  NGameX::IgnoreListStorage* GetIgnoreListStorage() { return ignoreListStorage; }
  NGameX::LoadingStatusHandler * GetLoadingStatusHandler() {return loadingStatusHandler;}

private:
  Strong<LoadingScreenLogic>  logic;
  CObj<LoadingProgress>     progress;

  NCore::ClientSettings clientSettings;
 
  map<int, HeroInfo> heroesInfo;
  
  Weak<NGameX::IgnoreListStorage>     ignoreListStorage;
  
  Strong<LoadingGameContext> loadingGameContext;

  void MsgChatOpenClose();
	bool MsgChatOpenChannel(const NDb::EChatChannel & channelID);
  bool CmdCancel();

  void InitLoadingUI();

  string logo;
  string back;
  const bool isSpectator;
  const bool isTutorial;

  NDb::Ptr<NDb::DBUIData> uiData;
  Strong<NGameX::LoadingStatusHandler>      loadingStatusHandler;

};

} //Game

#endif //LOADINGSCREEN_H_INCLUDED
