using System;
using ViewModel.Utils;

namespace Flash.Controls
{
  public class ContextMenuItem
  {
    public string ItemName;
    public Action ItemAction;
    public bool ShowCurrencyIcon;
    private bool _enabled = true;

    public event Action Changed;

    public bool Enabled
    {
      get { return _enabled; }
      set { _enabled = value; }
    }

    public bool IsNegative { get; private set; }

    public ContextMenuItem( string itemName ) :
      this( null, itemName, false, false )
    {
    }

    public ContextMenuItem(Action itemAction, string itemName):
      this(itemAction, itemName, false, false)
    {
    }

    public ContextMenuItem(Action itemAction, string itemName, bool isNegative):
      this(itemAction, itemName, isNegative, false)
    {
    }

    public ContextMenuItem(Action itemAction, string itemName, bool isNegative, bool showCurrencyIcon) 
    {
      ItemName = itemName;
      ItemAction = itemAction;
      IsNegative = isNegative;
      ShowCurrencyIcon = showCurrencyIcon;
    }

    public void FireChanged()
    {
      EventHelper.Invoke( Changed );
    }
  }
}