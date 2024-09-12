using System.Collections.Generic;
using System.ComponentModel;
using libdb.DB;

namespace PF_GameLogic.DBHeroRanks
{
  [Custom("Social")]
  public class Rank
  {
    [Description("Звание соответствует рейтингу героя равному или большему указанного")]
    [Custom( "DBServer" )]
    public int rating = 0;
    public TextRef rankNameA;
    public TextRef rankNameB;

    public TextRef rankGroupNameA;
    public TextRef rankGroupNameB;

    public TextRef rankTooltipA;
    public TextRef rankTooltipB;

    public DBPtr<Render.DBRenderResources.Texture> iconA;
    [Description( "Большая иконка (64*64) (в SeasonRewardWnd и Current/Best Season Results)" )]
    public DBPtr<Render.DBRenderResources.Texture> bigIconA;
    public DBPtr<Render.DBRenderResources.Texture> iconB;
    [Description( "см описание bigIconA" )]
    public DBPtr<Render.DBRenderResources.Texture> bigIconB;

    [Description("рекомендованная моща для звания. Поле нужно для показа предупреждения. Например 140 (а не 1400)")]
    public float recommendedForce = 0;

    [Description("максимально количество талантов за обычную сессию. используется ТОЛЬКО в UI")]
    public int rewardTalentsCountForUI = 0;

  }

  [UseTypeName( "HRANKS" )]
  [Custom( "DBServer", "Social" )]
  [DBVersion( 0 )]
  public class HeroRanks : DBResource
  {
    [Description("Рейтинг, начиная с которого в тамбуре можно выбирать всех героев, которые выше по званию")]
    public int highLevelsMMRating = 2000;

    [Description( "Список соответствий рейтинг-звание" )]
    public List<Rank> ranks;
  }
}
