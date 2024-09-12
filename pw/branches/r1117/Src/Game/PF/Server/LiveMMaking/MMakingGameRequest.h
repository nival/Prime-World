#pragma once

#include "MMakingDraftGame.h"

namespace mmaking
{

class GameRequest : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( GameRequest, BaseObjectMT )

public:
  GameRequest( lobby::TGameId _gameId );

  bool Init( const NDb::MapMMakingSettings * _dbSettings, int _teamSize, const SGame & _gameData, IHeroesTable * _heroes, IRankTable * _ranks, const GeoTable & _locales, const GeoTable & _geolocations, Loger * _loger );

  lobby::TGameId GameId() const { return gameId; }
  const MMakingDraftGame & Draft() const { return draft; }
  MMakingDraftGame & GetDraft() { return draft; }

  void SetStartTime( timer::Time _now );

private:
  MMakingDraftGame  draft;
  lobby::TGameId    gameId;
};

} //namespace mmaking
