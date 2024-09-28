using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Drawing;

namespace EaselLevelEditor
{
  /// <summary>
  /// base layer class
  /// is responsible for delegate methods transportation
  /// to its derivatives based on isActive param
  /// </summary>
  class EaselEditorLayer
  {
    public bool Enabled
    {
      get { return isEnabled; }
      set 
      { 
        isEnabled = value;
        vEnableDisable(isEnabled);
      }
    }

    private bool isEnabled; 
    
    public EaselEditorLayer()
    {
      isEnabled = true;
    }

    #region event handlers
    public void DrawHandler(object source, DrawEventArgs args)
    {
      if ( isEnabled  )
        vDraw(args.graphics);
    }

    public void UpdateHandler(object source, UpdateEventArgs args)
    {
      //if ( isEnabled  )
        vUpdate(args.spline, args.scaler);
    }

    public void ResizeBeginHandler(object source, ResizeEditorArgs args)
    {
      if ( isEnabled  )
        vResizeBegin(args.editor);
    }

    public void ResizeHandler(object source, ResizeEditorArgs args)
    {
      if ( isEnabled  )
        vResize(args.editor);
    }

    public void ResizeEndHandler(object source, ResizeEditorArgs args)
    {
      if ( isEnabled  )
        vResizeEnd(args.editor);
    }

    public void EditorMouseDblClickHandler(object source, MouseEventArgs args)
    {
      if ( isEnabled  )
        vDblClick(args);
    }

    public void EditorMouseClickHandler(object source, MouseEventArgs args)
    {
      if ( isEnabled  )
        vClick(args);
    }

    public void EditorMouseBtnDownHandler(object source, MouseEventArgs args)
    {
      if ( isEnabled  )
        vMouseDown(args);
    }

    public void EditorMouseBtnUpHandler(object source, MouseEventArgs args)
    {
      if ( isEnabled  )
        vMouseUp(args);
    }

    public void EditorMouseMoveHandler(object source, MouseEventArgs args)
    {
      if ( isEnabled  )
        vMouseMove(args);
    }

    #endregion

    #region internal event handlers
    
    protected virtual void vDraw(Graphics _graphics) {}
    protected virtual void vUpdate(EaselSpline _spline, EaselScaler _scaler) {}
    protected virtual void vResizeBegin(EaselLevelEditor _editor) { }
    protected virtual void vResize(EaselLevelEditor _editor) { }
    protected virtual void vResizeEnd(EaselLevelEditor _editor) { }
    protected virtual void vDblClick(MouseEventArgs _args) { }
    protected virtual void vClick(MouseEventArgs _args) { }
    protected virtual void vMouseDown(MouseEventArgs _args) { }
    protected virtual void vMouseUp(MouseEventArgs _args) { }
    protected virtual void vMouseMove(MouseEventArgs _args) { }
    protected virtual void vEnableDisable(bool fEnable) { }
    
    #endregion

  }
}
