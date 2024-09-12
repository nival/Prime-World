using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using EditorLib;
using EditorLib.Panels;
using EditorNative.DebugVars;
using EditorPlugins.Forms;

namespace EditorPlugins.Scene
{
  public partial class DebugVarsPanel : EditorPanel
  {
    private class EditorDebugVarWrapper
    {
      private readonly EditorDebugVar var;
      private readonly Color foreColor = Color.Black;
      private Color color = Color.Black;
      private float t = 0.0f;

      public EditorDebugVarWrapper( EditorDebugVar var, Color foreColor ) { this.var = var; this.foreColor = foreColor; this.color = foreColor; }

      public void Update( TimeSpan dt )
      {
        var.Update();
        if ( var.IsWarning )
          t = 1.0f;
        else if ( t > 0.0f )
          t -= Math.Max( 0.0f, (float)dt.TotalMilliseconds / 1000.0f );

        color = FormUtils.MixColors( foreColor, Color.Red, t );
      }

      public Color Color { get { return color; } }
      public string Value { get { return var.Value; } }
      public string Name { get { return var.Name; } }
    }

    private DateTime lastUpdateTime = DateTime.Now;
    private DebugVarsFilterConfig config = null;

    public DebugVarsPanel()
    {
      InitializeComponent();
    }

    protected override bool Initialize( IEditorWinApplication application )
    {
      config = application.Application.Settings.Get<DebugVarsFilterConfig>();
      ReloadDebugVars();
      return true;
    }

    public void ReloadDebugVars()
    {
      debugVarsList.BeginUpdate();
      debugVarsList.Items.Clear();
      Dictionary<string, bool> exists = new Dictionary<string, bool>();
      foreach ( var name in config.CommonDebugVars )
      {
        if ( exists.ContainsKey( name ) )
          continue;
        exists.Add( name, true );
        EditorDebugVar var = EditorDebugVar.FindDebugVar( name );
        if ( var != null )
          debugVarsList.Items.Add( new EditorDebugVarWrapper( var, ForeColor ) );
      }

      foreach ( var name in config.UserDebugVars )
      {
        if ( exists.ContainsKey( name ) )
          continue;
        exists.Add( name, true );
        EditorDebugVar var = EditorDebugVar.FindDebugVar( name );
        if ( var != null )
          debugVarsList.Items.Add( new EditorDebugVarWrapper( var, ForeColor ) );
      }
      debugVarsList.EndUpdate();
    }

    private void OnDebugVarsListDrawItem( object sender, DrawItemEventArgs e )
    {
      EditorDebugVarWrapper var = e.Index >= 0 && e.Index < debugVarsList.Items.Count ? debugVarsList.Items[e.Index] as EditorDebugVarWrapper : null;
      e.Graphics.FillRectangle( new SolidBrush( BackColor ), new Rectangle( e.Bounds.X, e.Bounds.Y, e.Bounds.Width + 1, e.Bounds.Height + 1 ) );
      if ( var == null )
        return;

      int valueWidth = Math.Min( TextRenderer.MeasureText( var.Value, Font ).Width, debugVarsList.ClientSize.Width - 30 );
      TextRenderer.DrawText( e.Graphics, var.Name, Font, new Rectangle( e.Bounds.X, e.Bounds.Y - 1, debugVarsList.ClientSize.Width - valueWidth - 5, e.Bounds.Height ), var.Color, TextFormatFlags.EndEllipsis );
      TextRenderer.DrawText( e.Graphics, var.Value, Font, new Point( debugVarsList.ClientSize.Width - valueWidth, e.Bounds.Y - 1 ), var.Color );
    }

    private void OnConfigureLinkLabelClicked( object sender, LinkLabelLinkClickedEventArgs e )
    {
      new DebugVarsFilterForm( config ).ShowDialog();
      ReloadDebugVars();
    }

    private void OnRefreshTimerTick( object sender, EventArgs e )
    {
      DateTime now = DateTime.Now;
      TimeSpan dt = lastUpdateTime - now;
      lastUpdateTime = now;

      foreach ( object obj in debugVarsList.Items )
      {
        EditorDebugVarWrapper var = obj as EditorDebugVarWrapper;
        if ( var != null )
          var.Update( dt );
      }
      debugVarsList.Invalidate();
    }
  }
}
