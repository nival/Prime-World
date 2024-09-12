using System.ComponentModel;
using libdb.DB;

namespace SocialTypes.DBTypes
{
  public class CastleCutscene : DBResource
  {
    [Description( "Строковый идентефикатор кат сцены для фракции A." )]
    public string CutsceneScriptNameA;
    [Description( "Строковый идентефикатор кат сцены для фракции B." )]
    public string CutsceneScriptNameB;
  }
}