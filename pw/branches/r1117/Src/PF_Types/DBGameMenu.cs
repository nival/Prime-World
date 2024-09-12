// Author:  Alexander Tveretinov
// Date:    08 Jule 2009

using System.ComponentModel;
using System.Collections.Generic;
using libdb.DB;

namespace PF_GameLogic.DBGameLogic
{
  public enum EMenuItemAction
  {
    GoBack, //GoBack - go back from sub menu or go back to the game from the main menu.
    ContactWithGameMaster,
    OpenSubmenu,  //only open the sub menu if it's not empty.
    GameSettings,
    GraphicSettings,
    SoundSettings,
    ControlSettings,
    GoToTown,
    LeaveTheGame,
    LeaveMinigame, //Not implemented yet
    AbortMinigameLevel
  }

  //==========================================================================================================================  
  public enum EMenuItemType
  {
    ButtonType,
    TextType,
    IconType
  }

  //==========================================================================================================================  
  public class  GameMenuItem
  {
    //[Description("An item icon.")]
    //public ....itemIcon 

    [Description("An item text.")]
    public TextRef itemText = new TextRef();

    [Description("An item type. For example it might be button, text or icon.")]
    public EMenuItemType itemType;

    [Description("An item action after click. Open the sub menu for example, or continue the game, etc.")]
    public EMenuItemAction itemAction;

    [Description("This menu item will only be shown in minigames")]
    public bool minigamesOnly = false;

    //[Description("An item text.")]
    public DBPtr<DBGameMenu> subMenu;
  }  

  //==========================================================================================================================
  [UseTypeName("GM")]
  public class DBGameMenu : DBResource
  {
    [Description("List of menu items.")]
    public List<GameMenuItem> menuItems = new List<GameMenuItem>();
  }

  //==========================================================================================================================  
}//end of namespace