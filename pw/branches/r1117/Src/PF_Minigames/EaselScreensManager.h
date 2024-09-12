#pragma once

namespace NMainLoop
{
  _interface IScreenBase;
}

namespace PF_Minigames
{

// forward declarations
class Easel;
class EaselMinigame;
class EaselScreenLobby;
class EaselScreen;
class EaselScreenLogic;
class EaselScreenLogicLobby;
class EaselScreenResults;
class EaselScreenLogicResults;
class EaselFailScreen;
class EaselFailScreenLogic;

//////////////////////////////////////////////////////////////////////////
//
// screens manager is responsible for transferring all
// requests considering screens operations
//
//////////////////////////////////////////////////////////////////////////
class EaselScreenManager
{
public:
  EaselScreenManager();
  virtual ~EaselScreenManager();

  // getters
  EaselScreenLobby *  GetLobbyScreen() { return IsValid( lobbyScreen ) ? lobbyScreen : 0; }
  EaselScreen*        GetMainScreen()      { return IsValid( easelScreen ) ? easelScreen : 0; };

  EaselScreenLogic * GetMainScreenLogic();
  EaselScreenLogicLobby * GetLobbyScreenLogic();
  EaselScreenLogicResults * GetResultsScreenLogic();
  EaselFailScreenLogic * GetFailureScreenLogic();

  bool Init( EaselMinigame * _minigame );
  void Uninit();

  // easel specific screen operations
  void PushEaselScreen();

  void PopEaselScreen();
  void PopLobbyScreen();
  void PopFailureScreen();
  void PopResultsScreen();

  EaselScreenLobby * CreateLobbyScreen();
  void CreateResultsScreen();
  void CreateFailureScreen();

private:
  // raw push/pop methods
  void PushScreen(NMainLoop::IScreenBase *_pScreen);
  void PopScreen(NMainLoop::IScreenBase *_pScreen);

  bool initailized;

  Weak<EaselScreenLobby>    lobbyScreen;
  Weak<EaselScreen>         easelScreen;
  Weak<EaselScreenResults>  resultsScreen;
  Weak<EaselFailScreen>     failureScreen;

  // common minigame object
  CPtr<EaselMinigame> minigame;

protected:

};

}