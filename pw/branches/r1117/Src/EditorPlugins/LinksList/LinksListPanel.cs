using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using EditorLib.Panels;
using libdb.DB;
using EditorLib;
using libdb.Diagnostics;
using EditorLib.ObjectsBrowser;

namespace EditorPlugins.LinksList
{
  public partial class LinksListPanel : EditorPanel
  {
#region EditorPanel members
    public LinksListPanel()
    {
      InitializeComponent();
    }

    protected override bool Initialize( IEditorWinApplication app )
    {
      TabText = "File Links";
      listView.ListViewItemSorter = new ItemComparer( 0 );

      levelsCount = 1;
      levelsCountText.Text = levelsCount.ToString();
      lessLevelsButton.Enabled = false;

      app.Panels.GetSingletonPanel<ObjectsBrowserPanel>().ChangeSelectedItemEvent += OnChangeSelectedItem;
      return true;
    }

    protected override void OnVisibleChanged( EventArgs e )
    {
      base.OnVisibleChanged( e );
      if ( Visible )
        UpdateLevels( 1 );
    }

#endregion

#region Core methods 
    private void UpdateLevels(int newLevelsCount)
    {
      if ( levelsCountText.TextBox == null )
        return;
      levelsCountText.Text = newLevelsCount.ToString();
      lessLevelsButton.Enabled = newLevelsCount > 1;
      if ( !DBID.IsNullOrEmpty( currentObject ) )
      {
        listView.Items.Clear();
        for ( int l = levelsCount + 1; l <= newLevelsCount; ++l )
          AppendFilesForLevel( l );
        FillView( newLevelsCount );
        levelsCount = newLevelsCount;
      }
      
    }

    private void AppendFilesForLevel( int level )
    {
      if ( files.Count <= 0 )
        AppendChildren( currentObject, level, null );
      else
      {
        List<DBID> toCollect = new List<DBID>();
        foreach ( var k in files )
        {
          if ( k.Value.hierLevel == level - 1 )
            toCollect.Add( new DBID( k.Key, Guid.Empty ) );
        }
        foreach (var dbid in toCollect)
        {
          AppendChildren( dbid, level, files[dbid.FileName].children );
        }
      }
    }

    private void FillView( int levels )
    {
      listView.BeginUpdate();
      foreach( var k in files )
      {
        if ( k.Value.hierLevel > levels )
          continue;
        ListViewItem it = new ListViewItem( new[] { k.Value.hierLevel.ToString(), k.Key, k.Value.fileType } );
        it.Tag = k.Key;
        it.Name = k.Key;
        it.SubItems[1].Tag = "tt";
        listView.Items.Add( it );
      }
      listView.EndUpdate();
    }

    private void AppendChildren( DBID dbid, int level, List<String> collected )
    {
      DBPtr<DBResource> ptr = new DBPtr<DBResource>(dbid,null);
      if ( ptr.Get() == null )
      {
        Log.TraceError("Referenced file {0} not in DB!", new object[] { dbid.FileName } );
        return;
      }

      FieldsWalker.DepthController depthController = new FieldsWalker.DepthController( 0, FieldsWalker.ObjectType.DBPtrUninlined, FieldsWalker.ObjectType.All );
      DBPtrBase[] links = FieldsWalker.CollectDBPtrs( ptr.Get<DBResource>(), depthController.Functor );

      foreach ( var link in links )
      {
        if ( link.DBId.IsInlined )
          continue;
        string fileName = link.DBId.FileName;
        if ( fileName.Length <= 0 )
          continue;

        if ( collected != null )
        {
          if ( !collected.Contains( fileName ) )
            collected.Add( fileName );
        }

        LinkedFile lf;
        if ( files.TryGetValue(fileName, out lf) )
        {
          lf.hierLevel = Math.Min( lf.hierLevel, level );
          if ( !lf.referrers.Contains( dbid.FileName ) )
            lf.referrers.Add( dbid.FileName );
        }
        else
        {
          lf = new LinkedFile();
          lf.hierLevel = level;
          DBResource res = link.Get<DBResource>();
          if ( res != null )
            lf.fileType = res.GetType().Name;
          else
            lf.fileType = "???";
          lf.referrers.Add( dbid.FileName );
          files[fileName] = lf;
        }
      }
    }
    #endregion

#region private data 

    class ItemComparer : System.Collections.IComparer
    {
        private int col;

        public ItemComparer(int column)
        {
            col = column;
        }
        public int Compare(object x, object y)
        {
            return String.Compare(((ListViewItem)x).SubItems[col].Text, ((ListViewItem)y).SubItems[col].Text);
        }
    }

    private class LinkedFile
    {
      public int hierLevel;
      public string fileType;
      public List<string> referrers;
      public List<String> children;
      public LinkedFile()
      {
        hierLevel = 0;
        referrers = new List<string>();
        children = new List<string>();
      }
    }

    private Dictionary<string,LinkedFile> files = new Dictionary<string,LinkedFile>();
    private DBID currentObject = null;
    private int levelsCount;
#endregion

#region event handlers 
    private void OnChangeSelectedItem( ObjectsBrowserPanel panel, DBID dbid )
    {
      if ( lockFileNameButton.Checked )
        return;

      if ( DBID.IsNullOrEmpty( dbid ) || currentObject == dbid )
        return;

      currentObject = dbid;
      fileNameText.Text = currentObject.FileName;

      files.Clear();
      levelsCount = 0;
      if ( Visible )
        UpdateLevels( 1 );
    }

    private void moreLevelsButton_Click( object sender, EventArgs e )
    {
      UpdateLevels( levelsCount + 1 );

    }

    private void lessLevelsButton_Click( object sender, EventArgs e )
    {
      UpdateLevels( levelsCount - 1 );
    }

    private void allLevelsButton_Click( object sender, EventArgs e )
    {
      int prevFiles;
      do 
      {
        prevFiles = files.Count;
        levelsCount = levelsCount + 1;
        AppendFilesForLevel( levelsCount );
      } while ( prevFiles != files.Count );
      UpdateLevels( levelsCount - 1 );
    }
#endregion

#region Menus
    private void listView_ColumnClick( object sender, ColumnClickEventArgs e )
    {
      listView.ListViewItemSorter = new ItemComparer( e.Column );
    }

    private void listView_MouseClick( object sender, MouseEventArgs e )
    {
      if ( e.Button == MouseButtons.Right )
      {
        var fileName = (string)listView.SelectedItems[0].Tag;
        DBResource resource = DataBase.Get<DBResource>( new DBID( fileName, Guid.Empty ) ).Get();
        if ( ReferenceEquals( resource, null ) )
          return;

        ContextMenu menu = application.ContextMenu.CreateContextMenu( resource, null );
        menu.Show( this, e.Location );
      }
      else if ( e.Button == MouseButtons.Left )
      {
        var fileName = (string)listView.SelectedItems[0].Tag;
        var fileInfo = files[fileName];

        ContextMenu menu = new ContextMenu();
        menu.MenuItems.Add( new MenuItem("Referenced from") );
        foreach ( var f in fileInfo.referrers )
          menu.MenuItems.Add( new MenuItem( f, OnReferrerMenuItemClick ) );

        if ( fileInfo.children.Count > 0 )
        {
          menu.MenuItems.Add( new MenuItem( "-" ) );
          menu.MenuItems.Add( new MenuItem( "Referencing" ) );
          foreach ( var f in fileInfo.children )
            menu.MenuItems.Add( new MenuItem( f, OnReferrerMenuItemClick ) );
        }
        menu.Show( this, e.Location );
      }
    }
    private void OnReferrerMenuItemClick( object sender, EventArgs e )
    {
      var item = (MenuItem)sender;
      var fileName = item.Text;
      int idx = listView.Items.IndexOfKey( fileName );
      if ( idx >= 0 )
      {
        listView.SelectedIndices.Clear();
        listView.SelectedIndices.Add( idx );
        listView.EnsureVisible( idx );
      }
    }
#endregion
  }
}
