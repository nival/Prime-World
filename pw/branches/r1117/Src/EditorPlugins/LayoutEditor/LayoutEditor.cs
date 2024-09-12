using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using DBTypes;
using EditorLib;
using EditorLib.Extensions;
using EditorLib.ToolBox;
using libdb.DB;
using EditorLib.Menu;
using libdb.UndoRedo;
using WeifenLuo.WinFormsUI.Docking;
using Win32;
using EditorLib.PropertiesEditor;
using EditorLib.PropertiesEditor.States;

namespace EditorPlugins.LayoutEditor
{
  [EditorLib.Extensions.EditorAttribute( "Layout", false )]
  [EditorLib.Extensions.ApplicableForDeriver]
  public partial class LayoutEditor : Editor<UILayout>
  {
    private IEditorWinApplication application = null;

    private LayoutEditorStatusPanel editorPanel = new LayoutEditorStatusPanel();
    protected override Control StatusPanel { get { return editorPanel; } }
    private bool initial = true;
    private Timer refreshTimer = new Timer();
    private DBPtr<UILayout> rootLayout = null;
    private bool fillingStatesCombo = false;

    public LayoutEditor()
    {
      InitializeComponent();
      editorControl.editorStatusPanel = editorPanel;
    }

    private void UpdateRulers()
    {
      editorControl.Invalidate();
    }

    private void editorControl_Resize( object sender, EventArgs e )
    {
      UpdateRulers();
    }

    private void LayoutEditor_KeyDown( object sender, KeyEventArgs e )
    {
      if ( ( e.KeyData & Keys.KeyCode ) == Keys.Space || ( e.KeyData & Keys.KeyCode ) == Keys.Escape )
        editorControl.SetSelection( null );
    }

    private void LayoutEditor_VisibleChanged( object sender, EventArgs e )
    {
      if ( initial )
      {
        UpdateRulers();
        initial = false;
      }
    }

    private void LayoutEditor_TreeViewSelection( UILayout win )
    {
      editorControl.SelectWindow( win );
    }

    private void LayoutEditor_ShowContextMenu( Control ctrl, Point at )
    {
      editorControl.ShowContextMenu( ctrl, at );
    }

    private void LayoutEditor_TreeViewChangeParent( UILayout winSrc, int atPosition, UILayout winParent )
    {
      editorControl.ChangeParent( new List<UILayout> { winSrc }, atPosition, winParent );
    }

    private void LayoutEditor_SetWindowVisible( UILayout win, bool visible )
    {
      editorControl.SetWindowVisible( win, visible );
    }

    protected override bool Initialize( DBPtr<UILayout> resource, IEditorWinApplication application )
    {
      this.application = application;
      editorControl.SetApplication( application );
      rootLayout = resource;
      UILayout rootElem = resource.Get();

      editorControl.RootLayout = rootElem;
      this.TabText = "UI: " + System.IO.Path.GetFileName( resource.DBId.Name );

      toolStripButtonShowGrid.Checked = editorControl.Snapper.IsGridVisible;
      toolStripButtonGridSnap.Checked = editorControl.Snapper.IsGridSnapOn;
      toolStripButtonParentSnap.Checked = editorControl.Snapper.IsParentSnapOn;
      toolStripButtonWindowSnap.Checked = editorControl.Snapper.IsObjectSnapOn;
      toolStripTextBoxGridSize.Text = editorControl.Snapper.GridSize.ToString();

      refreshTimer.Interval = 100;
      refreshTimer.Tick += refreshTimer_Tick;
      refreshTimer.Start();

      FillStatesCombo();
      editArea.Focus();

      return true;
    }

    private void FillStatesCombo()
    {
      fillingStatesCombo = true;
      SelectState.Items.Clear();
      List<string> states = rootLayout.GetStates();
      foreach ( string item in states )
      {
        if ( item == string.Empty )
        {
          SelectState.Items.Add( "Default State" );
        }
        else
          SelectState.Items.Add( item );

        if ( rootLayout.DefaultState == item )
          SelectState.SelectedIndex = SelectState.Items.Count - 1;
      }
      SelectState.Items.Add( "Manage..." );
      fillingStatesCombo = false;
    }

    void refreshTimer_Tick( object sender, EventArgs e )
    {
      editorControl.Refresh();
    }

    protected override void OnDeactivateEditor()
    {
      base.OnDeactivateEditor();
      application.Panels.GetSingletonPanel<LayoutTreeView>().ChangeSelectionEvent -= LayoutEditor_TreeViewSelection;
      application.Panels.GetSingletonPanel<LayoutTreeView>().ChangeParentEvent -= LayoutEditor_TreeViewChangeParent;
      application.Panels.GetSingletonPanel<LayoutTreeView>().ShowContextMenuEvent -= LayoutEditor_ShowContextMenu;
      application.Panels.GetSingletonPanel<LayoutTreeView>().SetWindowVisibleEvent -= LayoutEditor_SetWindowVisible;
      application.Panels.GetSingletonPanel<LayoutTreeView>().SetRootElement( null );
      refreshTimer.Stop();
    }

    protected override void OnActivateEditor()
    {
      base.OnActivateEditor();
      application.Panels.GetSingletonPanel<LayoutTreeView>().ChangeSelectionEvent += LayoutEditor_TreeViewSelection;
      application.Panels.GetSingletonPanel<LayoutTreeView>().ChangeParentEvent += LayoutEditor_TreeViewChangeParent;
      application.Panels.GetSingletonPanel<LayoutTreeView>().ShowContextMenuEvent += LayoutEditor_ShowContextMenu;
      application.Panels.GetSingletonPanel<LayoutTreeView>().SetWindowVisibleEvent += LayoutEditor_SetWindowVisible;
      application.Panels.GetSingletonPanel<LayoutTreeView>().SetRootElement( editorControl.RootLayout );
      editorControl.OnActivate();
      refreshTimer.Start();
    }

    protected override void OnClosed( EventArgs e )
    {
      application.Panels.GetSingletonPanel<LayoutTreeView>().OnEditorClosed( editorControl.RootLayout );
      base.OnClosed( e );
      refreshTimer.Stop();
      refreshTimer.Tick -= refreshTimer_Tick;
    }

    protected override IEnumerable<ToolBoxItem> ToolBoxItems
    {
      get
      {
        List<EditorLib.ToolBox.ToolBoxItem> rez = new List<EditorLib.ToolBox.ToolBoxItem>();
        foreach ( Type type in DataBase.KnownTypes )
        {
          if ( TypeUtils.IsSubclassOf( type, typeof( UILayout ) ) || type.Equals( typeof( UILayout ) ) )
          {
            object[] attrs = type.GetCustomAttributes( typeof( ToolBoxItemAttribute ), false );
            if ( attrs != null && attrs.Length > 0 )
            {
              rez.Add( new ToolBoxItem(
                ( attrs[0] as ToolBoxItemAttribute ).category,
                ( attrs[0] as ToolBoxItemAttribute ).name,
                Resource.ResourceManager.GetObject( ( attrs[0] as ToolBoxItemAttribute ).image ) as System.Drawing.Image,
                type
                ) );
            }
            else
            {
              rez.Add( new ToolBoxItem( "General", type.Name, null, type ) );
            }
          }
        }
        return rez;
      }
    }

    public override void OnSelectToolBoxItem( object tag )
    {
      editorControl.NewWindow( tag );
    }

    public override ToolBoxItem GetActiveItem()
    {
      return new ToolBoxItem( "User Controls", rootLayout.DBId.Name, rootLayout.DBId );
    }

    #region ToolStrip

    private void toolStripButtonShowGrid_CheckedChanged( object sender, EventArgs e )
    {
      editorControl.Snapper.IsGridVisible = toolStripButtonShowGrid.Checked;
    }

    private void toolStripButtonGridSnap_CheckedChanged( object sender, EventArgs e )
    {
      editorControl.Snapper.IsGridSnapOn = toolStripButtonGridSnap.Checked;
    }

    private void toolStripButtonParentSnap_CheckedChanged( object sender, EventArgs e )
    {
      editorControl.Snapper.IsParentSnapOn = toolStripButtonParentSnap.Checked;
    }

    private void toolStripButtonWindowSnap_CheckedChanged( object sender, EventArgs e )
    {
      editorControl.Snapper.IsObjectSnapOn = toolStripButtonWindowSnap.Checked;
    }

    private void toolStripTextBoxGridSize_Leave( object sender, EventArgs e )
    {
      int newGridSize = 10;
      try
      {
        newGridSize = int.Parse( toolStripTextBoxGridSize.Text );
      }
      catch ( ArgumentNullException ) { }
      catch ( FormatException ) { }
      catch ( OverflowException ) { }

      editorControl.Snapper.GridSize = Math.Max( 2, Math.Min( newGridSize, 100 ) );
    }

    private void SelectState_SelectedIndexChanged( object sender, EventArgs e )
    {
      if ( fillingStatesCombo )
        return;

      if ( SelectState.SelectedIndex == SelectState.Items.Count - 1 )
      {
        //Manage...
        DBPtr<DBResource> ptr = DataBase.Get<DBResource>( rootLayout.DBId );
        StatesManagementForm form = new StatesManagementForm( rootLayout.GetPtr<DBResource>() );
        form.ShowDialog();
        if ( form.DialogResult == DialogResult.OK )
        {
          FillStatesCombo();

          // Add snot
          using( UndoRedoTransaction trans = new UndoRedoTransaction( "Create snot for a new UI state" ) )
          {
            CreateSnotObjects( form.Changes.AddedStates );
            trans.Commit();
          }

          DataBase.ChangeCallback( rootLayout.DBId );
        }
        else
        {
          SelectState.SelectedIndex = 0;
        }

        return;
      }
      rootLayout.DefaultState = SelectState.SelectedItem.ToString();
      editorControl.RootLayout = rootLayout.Get();
      application.Panels.GetSingletonPanel<LayoutTreeView>().SetRootElement( null );
      application.Panels.GetSingletonPanel<LayoutTreeView>().SetRootElement( editorControl.RootLayout );
    }

    private void CreateSnotObjects( List<string> addedStates )
    {
      foreach ( string stateName in addedStates )
      {
        UILayout newState = rootLayout.Get( stateName );
        if ( null == newState )
          continue;

        CreateSnotChildren( newState );
      }
    }

    private void CreateSnotChildren( UILayout layout )
    {
      foreach ( DBPtr<UILayout> childPtr in layout.subLayouts )
      {
        if ( childPtr.Get() == null || childPtr.DBId.FileName != rootLayout.DBId.FileName && childPtr.DBId.IsInlined )
          continue;

        Type itemType = childPtr.Get().GetType();
        UILayout newChild = TypeUtils.CreateObject( itemType ) as UILayout;

        DBPtr<UILayout> newChildPtr = DataBase.Create<UILayout>( DBID.FromDBID( rootLayout.DBId, true ), newChild );
        newChild = newChildPtr.Get();
        newChild.SetParent( childPtr.Get() );
        childPtr.Set( newChildPtr );

        //Recurse
        CreateSnotChildren( newChild );
      }
    }

    #endregion
  }


  // This is a custom panel control to prevent LayoutEditor from scrolling elsewhere on focus
  public class UnscrollingPanelControl : Panel
  {
    private Point rememberedLocation;

    public UnscrollingPanelControl()
    {
    }

    protected override void OnScroll( ScrollEventArgs se )
    {
      base.OnScroll( se );
      rememberedLocation.X = this.DisplayRectangle.X;
      rememberedLocation.Y = this.DisplayRectangle.Y;
    }

    protected override Point ScrollToControl( Control activeControl )
    {
      return rememberedLocation;
    }
  }

}
