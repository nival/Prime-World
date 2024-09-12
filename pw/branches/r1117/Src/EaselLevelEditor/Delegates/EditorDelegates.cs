using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Collections;

using EaselLevelEditor.Layers;

namespace EaselLevelEditor
{
  /// <summary>
  /// draw event arguments class
  /// for DrawEditorData delegate
  /// </summary>
  public class DrawEventArgs : EventArgs
  {
    public Graphics graphics;
  }

  public delegate void DrawEditorData(object source, DrawEventArgs args);   // common draw delegate

  /// <summary>
  /// Update element data arguments class
  /// for UpdateEditorData delegate
  /// </summary>
  public class UpdateEventArgs : EventArgs
  {
    public EaselSpline spline;
    public EaselScaler scaler;
  }

  public delegate void UpdateEditorData(object source, UpdateEventArgs args); // common update delegate

  /// <summary>
  /// Resize element data arguments class
  /// for ResizeEditor delegate
  /// </summary>
  public class ResizeEditorArgs : EventArgs
  {
    public EaselLevelEditor editor;
  }

  // resize delegates
  public delegate void ResizeEditorBegin(object source, ResizeEditorArgs args);
  public delegate void ResizeEditor(object source, ResizeEditorArgs args);
  public delegate void ResizeEditorEnd(object source, ResizeEditorArgs args);

  // mouse delegates
  public delegate void EditorMouseDblClick(object source, MouseEventArgs args);
  public delegate void EditorMouseClick(object source, MouseEventArgs args);
  public delegate void EditorMouseBtnDown(object source, MouseEventArgs args);
  public delegate void EditorMouseBtnUp(object source, MouseEventArgs args);
  public delegate void EditorMouseMove(object source, MouseEventArgs args);

}