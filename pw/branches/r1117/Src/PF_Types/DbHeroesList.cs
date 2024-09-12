//#include "DbHero.cs"

using System.Collections.Generic;
using libdb.DB;
using PF_GameLogic.DBGameLogic;
using PF_GameLogic.DBUnit;
using System;

namespace PF_GameLogic.DBHeroesList
{
  [UseTypeName("HRDB")]
  [DBVersion(1)]
  [Custom("DBServer", "Social")]
  public class HeroesDB : DBResource
  {
    public List<DBPtr<Hero>> heroes = new List<DBPtr<Hero>>();
  }
}
