#pragma once

#include "../PF_Core/WorldObject.h"

#include "DBEasel.h"
#include "Random.h"

namespace NDb
{
  struct EPaintStatistics;
  enum EColor;
}

namespace PF_Minigames
{

class  PaintLogic;
class  EaselNotifier;
class  LuxBallChain;

// chain generator based on statistics
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class LuxChainGenerator : public PF_Core::WorldObjectBase
{
  OBJECT_METHODS( 0x9A6CE4C4, LuxChainGenerator )
public:
  LuxChainGenerator( PF_Core::IWorld* _pWorld );
  ~LuxChainGenerator();

  bool Init(EaselNotifier* _notifier,
            int _seed);

  // generate new chain by provided statistics and parameters
  // returns false on fail
  bool Generate( LuxBallChain* newChain, const NDb::DBEaselChains* _params, PaintLogic* _paintLogic );

private:
  LuxChainGenerator() {}

  void ChooseColorsForUsage(const NDb::EPaintStatistics& stats);

  void GenerateOneColorChunks( const NDb::DBEaselChains* _params );
  void RearrangeColorsInChain( const NDb::DBEaselChains* _params );

  void FillChainWithBalls( LuxBallChain* newChain );

  NDb::EColor chain[100]; //TODO remove this temporary buffer

  NDb::EColor usedColors[ NDb::KnownEnum<NDb::EColor>::sizeOf ];
  NDb::EColor paintColors[ NDb::KnownEnum<NDb::EColor>::sizeOf ];
  int colorUseCount[ NDb::KnownEnum<NDb::EColor>::sizeOf ];

  ZDATA_(PF_Core::WorldObjectBase)

  RandomGenerator generator;

  int numBallColors;
  int numBallsGenerated;
  int numPaintColors;

  CPtr<EaselNotifier> notifier;

public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PF_Core::WorldObjectBase*)this); f.Add(2,&generator); f.Add(3,&numBallColors); f.Add(4,&numBallsGenerated); f.Add(5,&numPaintColors); f.Add(6,&notifier); return 0; }
};

} // PF_Minigames