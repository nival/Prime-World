#ifndef RDPTESTSVGAME_H_INCLUDED
#define RDPTESTSVGAME_H_INCLUDED

#include "RdpTestBase.h"
#include <list>
#include <map>

class TestClientContext;

class TestGame : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( TestGame, BaseObjectMT );
public:
  TestGame( int _id, timer::Time _now, int _gameDuration );

  int Id() const { return id; }
  const size_t FullSize() const { return newPlayers.size() + players.size(); }

  void AddPlayer( TestClientContext * _ctx );
  void OnClientStep( int _uid, int _step );

  bool Poll( timer::Time _now );

private:
  struct Player
  {
    WeakMT<TestClientContext> ctx;
    bool stepAcked;

    Player() : stepAcked( false ) {}
  };

  typedef std::list<WeakMT<TestClientContext>>  PlayerList;
  typedef std::map<int, Player> Players;

  const int         id;
  threading::Mutex  mutex;
  timer::Time       now;
  PlayerList        newPlayers;
  Players           players;
  int               currentStep;
  int               gameDuration;
  timer::Time       nextStepTime;

  void Step( timer::Time _now );

  void FinishGame();
  int CountStepMisses();
};

#endif //RDPTESTSVGAME_H_INCLUDED
