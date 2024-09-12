//#include "DBAdvMap.cs"

using System.Collections.Generic;
using System.ComponentModel;
using libdb.DB;
using PF_GameLogic.DBAdvMap;

namespace PF_GameLogic.DbMapList
{
  [UseTypeName("MAPLST")]
  [Custom("DBServer", "Social")]
  [DBVersion(0)]
  public class MapList : DBResource
  {
    [Description("Список карт и режимов игры")]
    public List<DBPtr<AdvMapDescription>> maps;
  }
}
