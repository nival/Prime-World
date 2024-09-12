using System;
using System.Collections.Generic;
using System.Windows.Forms;
using EditorNative.DebugVars;
using System.Drawing;

namespace EditorPlugins.Scene
{
	public partial class DebugVarsFilterForm : Form
	{
    private enum EditorDebugVarLevel
    {
      DontShow,
      UserLevel,
      CommonLevel,
    }

    private class EditorDebugVarWrapper
    {
      private readonly string name = string.Empty;

      public EditorDebugVarWrapper( string name ) { this.name = name; }

      public string Name { get { return name; } }
      public EditorDebugVarLevel Level = EditorDebugVarLevel.DontShow;

      public static int Compare( EditorDebugVarWrapper x, EditorDebugVarWrapper y )
      {
        return string.Compare( x.Name, y.Name );
      }
    }

    private readonly DebugVarsFilterConfig config;
    private readonly Dictionary<string, EditorDebugVarWrapper> wrappers = new Dictionary<string, EditorDebugVarWrapper>();
    private readonly List<EditorDebugVarWrapper> sortedWrappers = new List<EditorDebugVarWrapper>();

		public DebugVarsFilterForm( DebugVarsFilterConfig config )
		{
      this.config = config;
			InitializeComponent();

      List<string> vars = EditorDebugVar.GetDebugVars();
      foreach ( var var in vars )
      {
        if ( wrappers.ContainsKey( var ) )
          continue;

        EditorDebugVarWrapper wrapper = new EditorDebugVarWrapper( var );
        wrappers.Add( var, wrapper );
        sortedWrappers.Add( wrapper );
      }
      sortedWrappers.Sort( EditorDebugVarWrapper.Compare );

      foreach ( var var in config.UserDebugVars )
			{
				EditorDebugVarWrapper wrapper;
				if ( wrappers.TryGetValue( var, out wrapper ) )
					wrapper.Level = EditorDebugVarLevel.UserLevel;
			}
      foreach ( var var in config.CommonDebugVars )
			{
				EditorDebugVarWrapper wrapper;
				if ( wrappers.TryGetValue( var, out wrapper ) )
					wrapper.Level = EditorDebugVarLevel.CommonLevel;
			}
			RebuildList();
    }

    private void RebuildList()
    {
      EditorDebugVarWrapper selected = debugVarsListBox.SelectedItem as EditorDebugVarWrapper;
      int selectedIndex = -1;
      debugVarsListBox.BeginUpdate();
      debugVarsListBox.Items.Clear();
      foreach( var var in sortedWrappers )
      {
        if ( var.Name.IndexOf( filterTextBox.Text, StringComparison.InvariantCultureIgnoreCase ) >= 0 )
        {
          int index = debugVarsListBox.Items.Add( var );
          if ( selected == var )
            selectedIndex = index;
        }
      }
      if ( selectedIndex >= 0 )
        debugVarsListBox.SelectedIndex = selectedIndex;
      debugVarsListBox.EndUpdate();
      debugVarsListBox.Invalidate();
    }

    private void OnDebugVarsListBoxDrawItem( object sender, DrawItemEventArgs e )
    {
      bool selected = ( e.State | DrawItemState.Selected ) == DrawItemState.Selected;
      bool focused = ( e.State | DrawItemState.Focus ) == DrawItemState.Focus;
      if ( selected )
        e.Graphics.FillRectangle( new SolidBrush( Color.FromKnownColor( KnownColor.Highlight ) ), e.Bounds );
      else
        e.Graphics.FillRectangle( new SolidBrush( e.BackColor ), e.Bounds );

      EditorDebugVarWrapper wrapper = debugVarsListBox.Items[e.Index] as EditorDebugVarWrapper;

      TextRenderer.DrawText( e.Graphics, wrapper.Name, Font, new Point( e.Bounds.X + 12, e.Bounds.Y ), selected ? Color.FromKnownColor( KnownColor.HighlightText ) : e.ForeColor );
      string mode = string.Empty;
      if ( wrapper.Level == EditorDebugVarLevel.UserLevel )
        mode = "U";
      else if ( wrapper.Level == EditorDebugVarLevel.CommonLevel )
        mode = "A";

      if ( !string.IsNullOrEmpty( mode ) )
        TextRenderer.DrawText( e.Graphics, mode, new Font( Font, FontStyle.Bold ), e.Bounds.Location, selected ? Color.FromKnownColor( KnownColor.HighlightText ) : e.ForeColor );

      if ( focused )
        e.DrawFocusRectangle();
    }

    private void OnFilterTextBoxTextChanged( object sender, EventArgs e )
    {
      RebuildList();
    }

    private void OnFilterTextBoxKeyPress( object sender, KeyPressEventArgs e )
    {
      e.Handled = true;
      if ( e.KeyChar == 13 )
        RebuildList();
      else if ( e.KeyChar == 27 )
        filterTextBox.Text = string.Empty;
      else
        e.Handled = false;
    }

    private void OnDebugVarsListBoxDoubleClick( object sender, EventArgs e )
    {
      EditorDebugVarWrapper wrapper = debugVarsListBox.SelectedItem as EditorDebugVarWrapper;
      if ( wrapper == null )
        return;

      if ( wrapper.Level == EditorDebugVarLevel.DontShow )
        wrapper.Level = EditorDebugVarLevel.UserLevel;
      else if ( wrapper.Level == EditorDebugVarLevel.UserLevel )
        wrapper.Level = EditorDebugVarLevel.CommonLevel;
      else if ( wrapper.Level == EditorDebugVarLevel.CommonLevel )
        wrapper.Level = EditorDebugVarLevel.DontShow;

      debugVarsListBox.Invalidate();
    }

    private void OnOkButtonClick( object sender, EventArgs e )
    {
      config.CommonDebugVars.Clear();
      config.UserDebugVars.Clear();
      foreach ( var var in sortedWrappers )
      {
        EditorDebugVarWrapper wrapper = var as EditorDebugVarWrapper;
        if ( wrapper.Level == EditorDebugVarLevel.UserLevel )
          config.UserDebugVars.Add( wrapper.Name );
        if ( wrapper.Level == EditorDebugVarLevel.CommonLevel )
          config.CommonDebugVars.Add( wrapper.Name );
      }

      Close();
    }
	}
}
