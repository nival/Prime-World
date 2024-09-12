using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Windows.Forms;
using EditorLib.IO;
using EditorLib.Operations;
using EditorLib.Utils;
using libdb;
using libdb.DB;

namespace EditorLib.Extensions
{

  public partial class ImportRecursive : Form
  {
    private readonly DBResource singleTarget = null;
    private readonly ObjectsFolder targetFolder = null;
		private readonly ListViewColumnSorter lvwColumnSorter = new ListViewColumnSorter();

    private Dictionary<object, int> targets = new Dictionary<object, int>();
    private Dictionary<object, int> extraTargets = new Dictionary<object, int>();
    private Dictionary<object, int> targetsBackup = null;

    public ImportRecursive( DBResource targetObject )
    {
      InitializeComponent();

      listViewObjects.SmallImageList = EditorCommonApplication.ApplicationSingleton.Extensions.GetTypesImageList();
			listViewObjects.ListViewItemSorter = lvwColumnSorter;

      checkBoxShowExternal.Visible = false;
      singleTarget = targetObject;
      backgroundWorkerSearch.RunWorkerAsync();
    }

    public ImportRecursive( ObjectsFolder _targetFolder )
    {
      targetFolder = _targetFolder;
      InitializeComponent();

      listViewObjects.SmallImageList = EditorCommonApplication.ApplicationSingleton.Extensions.GetTypesImageList();

      backgroundWorkerSearch.RunWorkerAsync();
    }

    #region Entity Collector - gets objects and structs from an object

    private class EntityCollector
    {
      public Dictionary<object, bool> Objects = new Dictionary<object,bool>();

      public bool Functor( ref object obj, DBFieldInfo field )
      {
        if ( null == obj )
          return true;

        if ( obj is DBPtrBase )
        {
          DBResource res = ( obj as DBPtrBase ).Get<DBResource>();
          if ( res != null && EditorCommonApplication.ApplicationSingleton.Extensions.HasImporter( res.GetType() ) )
          {
            if ( !Objects.ContainsKey( res ) )
              Objects[res] = true;
          }
        }
        else if ( obj is IOwnerable )
        {
          IOwnerable strObj = obj as IOwnerable;
          if ( strObj.GetOwner() != null )
          {
            Type ownerType = strObj.GetOwner().GetType();
            if ( EditorCommonApplication.ApplicationSingleton.Extensions.HasImporter( ownerType, strObj.GetType() ) )
            {
              if ( !Objects.ContainsKey( obj ) )
                Objects[obj] = true;
            }
          }
        }

        return true;
      }
    }

    #endregion


    private void CollectFromSingle( DBResource targetRes )
    {
      FieldsWalker.DepthController depthController = new FieldsWalker.DepthController( -1, FieldsWalker.ObjectType.All, FieldsWalker.ObjectType.All );
      EntityCollector collector = new EntityCollector();
      FieldsWalker.VisitFields( targetRes, collector.Functor, depthController.Functor );

      if ( EditorCommonApplication.ApplicationSingleton.Extensions.HasImporter( targetRes.GetType() ) )
        CheckAddTarget( targetRes );
      foreach ( object res in collector.Objects.Keys )
      {
        CheckAddTarget( res );
      }
    }

    private void CollectFromFolder( ObjectsFolder srcFolder )
    {
      string folderName = srcFolder.FullName;
      List<ObjectsFolder> foldersToCheck = new List<ObjectsFolder>();
      foldersToCheck.Add( srcFolder );
      List<ObjectsFolder> targetFolders = new List<ObjectsFolder>();

      while ( foldersToCheck.Count > 0 )
      {
        ObjectsFolder folder = foldersToCheck[0];
        foldersToCheck.RemoveAt( 0 );
        targetFolders.Add( folder );
        foldersToCheck.AddRange( folder.Folders );
      }
      foreach ( ObjectsFolder folder in targetFolders )
      {
        foreach ( DBID objId in folder.Items )
        {
          DBResource res = DataBase.Get<DBResource>( objId );
          if ( res == null )
            continue;

          FieldsWalker.DepthController depthController = new FieldsWalker.DepthController( -1, FieldsWalker.ObjectType.All, FieldsWalker.ObjectType.All );
          EntityCollector collector = new EntityCollector();
          FieldsWalker.VisitFields( res, collector.Functor, depthController.Functor );

          if ( EditorCommonApplication.ApplicationSingleton.Extensions.HasImporter( res.GetType() ) )
            CheckAddTarget( res );
          foreach ( object obj in collector.Objects.Keys )
          {
            if ( obj is DBResource )
            {
              DBResource resource = obj as DBResource;
              if ( resource.DBId.GetFullFileName().StartsWith( folderName ) )
                CheckAddTarget( resource );
              else
              {
                if ( extraTargets.ContainsKey( resource ) )
                  continue;

                extraTargets[resource] = -1;
              }
            }
            else if ( obj is IOwnerable )
            {
              IOwnerable strObj = obj as IOwnerable;
              DBResource resource = strObj.GetOwner();
              if ( null == resource )
                continue;

              if ( resource.DBId.GetFullFileName().StartsWith( folderName ) )
                CheckAddTarget( obj );
              else
              {
                if ( extraTargets.ContainsKey( obj ) )
                  continue;

                extraTargets[obj] = -1;
              }
            }
          }
        }
      }
    }

    private void CheckAddTarget( object obj )
    {
      if ( obj == null )
        return;

      if ( targets.ContainsKey( obj ) )
        return;

      targets[obj] = -1;
    }

    private void backgroundWorkerSearch_RunWorkerCompleted( object sender, RunWorkerCompletedEventArgs e )
    {
      progressBarImport.Visible = false;
      if ( targets.Count > 0 )
        buttonImport.Enabled = true;
      listViewObjects.Enabled = true;
      this.Text = "Recursive Import";

      PopulateList();
    }

    private void PopulateList()
    {
      listViewObjects.Items.Clear();
      int index = 0;
      Dictionary<object, int> targetIndices = new Dictionary<object, int>();
      foreach ( object obj in targets.Keys )
      {
        bool itemChecked = true;
        string resLine = "(" + obj.GetType().Name + ") ";
        if ( obj is DBResource )
        {
          DBResource res = obj as DBResource;
          if ( res.DBId.IsInlined )
            resLine += "inlined in " + res.DBId.FileName;
          else
            resLine += res.DBId.Name;
        }
        else if ( obj is IOwnerable )
        {
          IOwnerable strObj = obj as IOwnerable;
          DBResource owner = strObj.GetOwner();
          resLine += "part of (" + owner.GetType().Name + ") ";
          if ( owner.DBId.IsInlined )
            resLine += "inlined in " + owner.DBId.FileName;
          else
            resLine += owner.DBId.Name;

          if ( targets.ContainsKey( owner ) )
            itemChecked = false;
        }
        else
          continue;
        targetIndices[obj] = index;
        ListViewItem newItem = new ListViewItem( resLine );
        newItem.Checked = itemChecked;
        newItem.ImageIndex = EditorCommonApplication.ApplicationSingleton.Extensions.GetTypeIconIndex( obj.GetType(), true );
        listViewObjects.Items.Add( newItem );
      	newItem.SubItems.Add(Path.GetExtension(resLine).Trim('.'));
        ++index;
      }
      targets = targetIndices;
      listViewObjects.Columns[0].AutoResize( ColumnHeaderAutoResizeStyle.None );
			listViewObjects.Columns[1].AutoResize( ColumnHeaderAutoResizeStyle.HeaderSize );
    }

    private void backgroundWorkerSearch_DoWork( object sender, DoWorkEventArgs e )
    {
      if ( singleTarget != null )
        CollectFromSingle( singleTarget );
      else if ( targetFolder != null )
        CollectFromFolder( targetFolder );
    }

    private void buttonImport_Click( object sender, EventArgs e )
    {
      List<Executor.OperationHandler> ops = new List<Executor.OperationHandler>();
      foreach ( object obj in targets.Keys )
      {
        int index = targets[obj];
        if ( index < 0 || index >= listViewObjects.Items.Count )
          continue;

        if ( !listViewObjects.Items[index].Checked )
          continue;

        if ( obj is DBResource )
        {
          DBResource res = obj as DBResource;
          IImporter importer = EditorCommonApplication.ApplicationSingleton.Extensions.CreateImporter( res.DBId, EditorCommonApplication.ApplicationSingleton, false );
          ops.Add( importer.Import );
        }
        else if ( obj is IOwnerable )
        {
          IOwnerable strObj = obj as IOwnerable;
          DBResource owner = strObj.GetOwner();
          IStructImporter importer = EditorCommonApplication.ApplicationSingleton.Extensions.CreateImporter( strObj, EditorCommonApplication.ApplicationSingleton, false );
          ops.Add( importer.Import );
        }
        else
          continue;
      }
      EditorCommonApplication.ApplicationSingleton.OperationExecutor.Start( ops.ToArray() );
      Close();
    }

    private void checkBoxShowExternal_CheckedChanged( object sender, EventArgs e )
    {
      if ( checkBoxShowExternal.Checked )
      {
        targetsBackup = new Dictionary<object, int>( targets );
        foreach ( object obj in extraTargets.Keys )
          targets[obj] = -1;

        PopulateList();
      }
      else
      {
        targets = targetsBackup;
        targetsBackup = null;
        PopulateList();
      }
      buttonImport.Enabled = ( targets.Count > 0 );
    }

		private void OnHeaderClick( object sender, ColumnClickEventArgs e )
		{
		  // Determine if clicked column is already the column that is being sorted.
		  if ( e.Column == lvwColumnSorter.SortColumn )
		  {
		    // Reverse the current sort direction for this column.
		    if ( lvwColumnSorter.Order == SortOrder.Ascending )
		    {
		      lvwColumnSorter.Order = SortOrder.Descending;
		    }
		    else
		    {
		      lvwColumnSorter.Order = SortOrder.Ascending;
		    }
		  }
		  else
		  {
		    // Set the column number that is to be sorted; default to ascending.
		    lvwColumnSorter.SortColumn = e.Column;
		    lvwColumnSorter.Order = SortOrder.Ascending;
		  }

			ListViewSortIconExtension.SetSortIcon( listViewObjects, e.Column, lvwColumnSorter.Order );

		  // Perform the sort with these new sort options.
		  listViewObjects.Sort();
		}
  }
}
