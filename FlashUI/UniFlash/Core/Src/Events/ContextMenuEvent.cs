using System;
using System.Collections.Generic;
using Flash.Controls;

namespace Flash
{
  public class ContextMenuEvent : Event
  {
    
    public const string ID = "ContextMenuEvent";
    
    public List<ContextMenuItem> ContextMenuList { get; private set; }
    public Action CloseContextMenuAction;

    public ContextMenuEvent(List<ContextMenuItem> contextMenuList)
      : this(contextMenuList, null)
    {}


    public ContextMenuEvent(List<ContextMenuItem> contextMenuList,Action closeContextMenuAction)
      : base( ID, true )
    {
      ContextMenuList = contextMenuList;
      CloseContextMenuAction = closeContextMenuAction;
    }
  }
}