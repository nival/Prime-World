using System;
using System.Collections.Generic;
using System.Text;
using PF_GameLogic.DBUnit;
using SocialTypes.DBTypes;
using PF_GameLogic.DBTalent;
using libdb.DB;

namespace SocialTypes.Quests
{
  [NonTerminal]
  public class HighlightAction : ClientQuestAction
  {
  }

  public class HighlightHeroAction : HighlightAction
  {
    public DBPtr<Hero> hero;
  }

  public class HighlightContructionAction : HighlightAction
  {
    public DBPtr<Constructon> construction;
  }

  public class HighlightContructionInPocketAction : HighlightAction
  {
    public DBPtr<Constructon> construction;
  }
  public class HighlightTalentAction : HighlightAction
  {
    public DBPtr<Talent> talent;
  }

  public class HighlightAndOpenBuildingUpgradeAction : HighlightAction
  {
    public string windowName;
  }

  public class HighlightAndOpenBoostButton : HighlightAction
  {
    public string windowName;
  }

  public class HighlightAndOpenBathSlot : HighlightAction
  {
    //public string windowName;
  }

  public class HighlightAndOpenFriendSlot : HighlightAction
  {
    public string windowName;
  }

  public class HighlightAndOpenTransmutationSlot : HighlightAction
  {
    //public string windowName;
  }

  public enum MapType
  {
    Tutorial,
    CTF,
    PVP,
    PVE
  }
  
  public class HighlightMapTypeAction : HighlightAction
  {
    public MapType mapType = MapType.Tutorial;
  }

  public enum HightlightItemType
  {
    UnsoulboundButton,
    SellTalentButton,
    PlayGameButton,
    UpgradeButton,
  }

  public class HighlightItemAction : HighlightAction
  {
    public HightlightItemType itemToHighlight = HightlightItemType.UnsoulboundButton;
  }

}
