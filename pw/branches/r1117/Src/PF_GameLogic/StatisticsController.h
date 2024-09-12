#pragma once


namespace NWorld
{
  class PFWorld;
}

namespace NGameX
{
class AdventureFlashInterface;

class StatisticsController : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( StatisticsController, BaseObjectST );

public:
  StatisticsController(AdventureFlashInterface * _flashInterface, NWorld::PFWorld * _world);

  void TabPressed(bool pressed);

  void Update();

private:

  struct PlayerScoreParams
  {
    PlayerScoreParams();
    bool operator==(const PlayerScoreParams &other) const;
    int killsCount;
    int assistCount;
    int deathCount;
    int score;
		int primeEarned;
  };

  Weak<AdventureFlashInterface>          flashInterface;
  ConstPtr<NWorld::PFWorld>     world;

  hash_map<int, PlayerScoreParams>  playersParams;
  bool tabPressed;
  float elfDomination;  
  float humanDomination;
  int timeElapsed;
  int timeToCreepSpawn;
};

} //namespace NGameX
