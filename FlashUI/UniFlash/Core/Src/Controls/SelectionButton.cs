using System.Collections.Generic;
using UnityEngine;

namespace Flash.Controls
{
  public class SelectionButton : ToggleButton
  {
    /// <summary>
    /// Контейнер, в рамках которого может быть выбрана только одна кнопка из группы
    /// </summary>
    public DisplayObjectContainer GroupContainer { get; set; }

    protected override void OnMouseClick( MouseEvent args )
    {
      base.OnMouseClick( args );

      if ( !Enabled || args.Button != MouseButton.Left )
        return;

      Frame children = GroupContainer != null ? GroupContainer.Children : Parent.Children;

      SelectRecursive( children );
    }

    private void SelectRecursive( IEnumerable<DisplayInstance> children )
    {
      foreach ( DisplayInstance child in children )
      {
        //NOTE пробегаемся по видимым кнопкам, вроде это не должно нигде повлиять.
        if ( !child.DisplayObject.Visible )
          continue;

        SelectionButton selectionButton = child.DisplayObject as SelectionButton;

        if ( selectionButton != null )
          selectionButton.Checked = ( selectionButton == this ) && selectionButton.Enabled;
        else if ( child.DisplayObject is DisplayObjectContainer )
          SelectRecursive( ( (DisplayObjectContainer)child.DisplayObject ).Children );
      }
    }
  }
}
