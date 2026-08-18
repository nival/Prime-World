using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Flash;
using Flash.Controls;
using UnityEngine;

namespace FlashView.Controls
{
  class TrimmedTooltipText: TextField
  {
    protected override void Init()
    {
      base.Init();
      TrimOverflow = true;
      TrimOverflowLength = 3;
      MouseEnabled = true;
      MultiLine = false;
    }

    protected override void OnMouseOver( MouseEvent args )
    {
      base.OnMouseOver( args );

      //Debug.Log( string.Format( "OnMouseOver IsTrimmed {0}, Text {1}", IsTrimmed, Text) );

      ShowTooltip();
    }

    protected override void OnMouseOut( MouseEvent args )
    {
      base.OnMouseOut( args );

      HideTooltip();
    }

    public void ShowTooltip()
    {
      if (IsTrimmed && !string.IsNullOrEmpty(Text))
      {
        DispatchEvent(new SystemTooltipFillEvent(Text));
        DispatchEvent(new VisibilityTooltipEvent(true, this));
      }
    }

    public void HideTooltip()
    {
      if (IsTrimmed && !string.IsNullOrEmpty(Text))
        DispatchEvent(new VisibilityTooltipEvent(false, this));
    }
  }
}
