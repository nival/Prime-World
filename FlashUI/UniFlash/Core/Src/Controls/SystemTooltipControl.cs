using System;

namespace Flash.Controls
{
  /// <summary>
  /// temp class for system tooltips
  /// </summary>
  public class SystemTooltipControl : Control
  {
    public string TooltipText
    {
      get { return _tooltipText; }
      set
      {
        var isTooltipChanged = _tooltipText != value;

        _tooltipText = value;

        if ( !_isMouseOver || !isTooltipChanged )
          return;

        if ( !String.IsNullOrEmpty( _tooltipText ) )
        {
          ShowTooltip();
        }
        else
          HideTooltip();
      }
    }

    private TooltipPosition _tooltipPosition = TooltipPosition.Default;
    private string _tooltipText;
    private bool _isMouseOver;

    public TooltipPosition TooltipPosition
    {
      private get { return _tooltipPosition; }
      set { _tooltipPosition = value; }
    }

    protected override void OnMouseOver( Flash.MouseEvent args )
    {
      _isMouseOver = true;
      base.OnMouseOver( args );

      if ( String.IsNullOrEmpty( TooltipText ) )
        return;

      ShowTooltip();
    }

    private void ShowTooltip()
    {
      DispatchEvent( new SystemTooltipFillEvent( TooltipText ) );
      DispatchEvent( new VisibilityTooltipEvent( true, this, TooltipPosition ) );
    }

    private void HideTooltip()
    {
      DispatchEvent( new VisibilityTooltipEvent( false, this, TooltipPosition ) );
    }

    protected override void OnMouseOut( Flash.MouseEvent args )
    {
      _isMouseOver = false;
      base.OnMouseOut(args);

      if (String.IsNullOrEmpty(TooltipText))
        return;

      HideTooltip();
    }
  }
}
