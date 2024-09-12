using System;
using System.Collections.Generic;
using System.Windows.Forms;
using EditorLib.ToolBox;
using libdb.DB;
using WeifenLuo.WinFormsUI.Docking;
using Win32;

namespace EditorLib.Extensions
{
  public class AbstractEditor : DockContent, IMessageFilter
  {
    private static AbstractEditor activeEditor = null;

    private DBID dbid = DBID.Empty;
    public DBID TargetDBID { get { return dbid; } }
    private IEditorWinApplication application = null;

    private readonly IEnumerable<ToolBoxItem> globalToolBoxItems = new List<ToolBoxItem>();

    public AbstractEditor()
    {
      FormBorderStyle = FormBorderStyle.SizableToolWindow;
      ShowHint = DockState.Document;
      ShowIcon = false;
      ShowInTaskbar = false;
    }

    private void InitializeComponent()
    {
      this.SuspendLayout();
      this.ClientSize = new System.Drawing.Size( 292, 273 );
      this.Name = "AbstractEditor";
      this.ResumeLayout( false );
    }

    protected new bool ShowIcon { get { return base.ShowIcon; } set { base.ShowIcon = value; } }
    protected new bool ShowInTaskbar { get { return base.ShowInTaskbar; } set { base.ShowInTaskbar = value; } }
    protected new FormBorderStyle FormBorderStyle { get { return base.FormBorderStyle; } set { base.FormBorderStyle = value; } }

    internal virtual bool InitializeInternal( DBID dbid, IEditorWinApplication application )
    {
      this.dbid = dbid;
      this.application = application;
      EditorsPool.RegisterEditor( dbid, this );
      Application.AddMessageFilter( this );
      return false;
    }

    bool IMessageFilter.PreFilterMessage( ref Message m )
    {
      if ( ( m.Msg == User.WM_USER + 666 ) && this != null && m.HWnd == this.Handle && IsFloat  ) // this!=null не удалять!
        OnEnter( EventArgs.Empty );
      return false;
    }

    protected virtual void OnActivateEditor()
    {
    }

    protected virtual void OnDeactivateEditor()
    {
    }

    public virtual void StoreMap()
    {
    }

    public virtual bool NeedWindow { get { return true; } }

    protected override void OnEnter( EventArgs e )
    {
      base.OnEnter( e );
      if ( activeEditor != this )
      {
        if ( activeEditor != null )
          activeEditor.DeactivatedEditor();
        ActivateEditor();
      }
    }

    private void ActivateEditor()
    {
      if ( activeEditor == this )
        return;

      ToolBoxPanel toolBoxPanel = application.Panels.GetSingletonPanel<ToolBoxPanel>();
      if ( toolBoxPanel != null )
      {
        toolBoxPanel.ActiveEditor = this;

        if ( ToolBoxItems != null )
        {
          foreach ( ToolBoxItem item in ToolBoxItems )
            toolBoxPanel.AddItem( item, false );
        }

        AbstractEditorConfig config = application.Application.Settings.Get<AbstractEditorConfig>();

        foreach (var item in config.GetUserToolBoxItems(this.GetType()))
          toolBoxPanel.AddItem( item, true );

        toolBoxPanel.InitRecentlyUsedToolBoxItems(config.GetRecentlyUsedToolBoxItems(this.GetType()));
      }
 
      activeEditor = this;
      application.StatusPanel = StatusPanel;
      //application.Panels.GetSingletonPanel<ObjectsBrowserPanel>().SelectItem( dbid );
      OnActivateEditor();
    }

    private void DeactivatedEditor()
    {
      if ( activeEditor != this )
        return;

      OnDeactivateEditor();
      application.StatusPanel = null;
      activeEditor = null;

      ToolBoxPanel toolBoxPanel = application.Panels.GetSingletonPanel<ToolBoxPanel>();
      if ( toolBoxPanel != null )
      {
        application.Application.Settings.Get<AbstractEditorConfig>().StoreUserToolBoxItems( this.GetType(), toolBoxPanel.UserToolBoxItems );
        application.Application.Settings.Get<AbstractEditorConfig>().StoreRecentlyUsedToolBoxItems(this.GetType(), toolBoxPanel.RecentlyUsedToolBoxItems);

        if ( toolBoxPanel.ActiveEditor == this )
        {
          toolBoxPanel.ActiveEditor = null;
        }
      }

      GC.Collect();
      GC.WaitForPendingFinalizers();
    }

    protected override void OnLeave( EventArgs e )
    {
      base.OnLeave( e );
      application.StatusPanel = null;
    }

    protected override void OnClosed( EventArgs e )
    {
      base.OnClosed( e );
      EditorsPool.UnregisterEditor( dbid, this );
      Application.RemoveMessageFilter( this );
      DeactivatedEditor();
    }

    protected virtual Control StatusPanel { get { return null; } }

    protected virtual IEnumerable<ToolBoxItem> ToolBoxItems { get { return globalToolBoxItems; } }
    public virtual void OnSelectToolBoxItem( object Tag ) { }
    public virtual ToolBoxItem GetActiveItem() { return null; }
  }
}
