//#include "DBAdvMap.cs"

using System;
using System.Text;
using System.ComponentModel;
using System.Collections.Generic;
using libdb.DB;


namespace PF_GameLogic.DBAdvMap
{
  [UseTypeName("ADMPSTTN")]
  public class DbAdvMapCTESettings : AdvMapSettings
  {
    [Description("скриптовое имя алтаря за доктов")]
    public string altarName_A = string.Empty;

    [Description("скриптовое имя алтаря за адорнийцев")]
    public string altarName_B = string.Empty;

    [Description("скриптовое имя спавнера дракона")]
    public string dragonSpawnerName = string.Empty;

    [Description("имя переменной в алтаре куда пишется дамаг")]
    public string damageVariableName = string.Empty;

    [Description("таблица для анимирования дамага по алтарю, нулевой элемент стартовая точка (0), дальше градации входящего дамага в секунду")]
    public List<float> damageAnimationTable = new List<float>();
  }
}
