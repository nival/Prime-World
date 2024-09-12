using System;
using System.Collections.Generic;
using System.IO;
using System.Windows.Forms;
using EditorLib;
using EditorLib.Extensions;
using EditorLib.ObjectsBrowser;
using libdb.DB;
using libdb.Diagnostics;
using libdb.IO;
using SharpSvn;

namespace EditorPlugins.Committer
{
  public partial class DualCommitForm
  {
    private readonly IEditorWinApplication application = null;
    private readonly ImageList typeImageList = null;

    private readonly DualCommitData data = null;

  	public int SelectedCount 
		{ 
			get { return GetSelectedCountRecursive(treeViewAssets.Nodes); }
		}

		private static int GetSelectedCountRecursive(TreeNodeCollection _nodes)
		{
			int result = 0;

			foreach(TreeNode node in _nodes)
			{
				if(node.Tag is AssetInfo)
				{
					if(((AssetInfo)node.Tag).SelectedForCommit)
					{
						++result;
					}
				}

				result += GetSelectedCountRecursive( node.Nodes );
			}

			return result;
		}

    public DualCommitForm( IEditorWinApplication _application )
    {
      InitializeComponent();
      splitContainer1.Panel2MinSize = 250;     // circumvent the .net bug (really)

      application = _application;

      DataTargets = new List<string>();
      SourceTargets = new List<string>();
      SourceAddTargets = new List<string>();

			data = new DualCommitData( application );
      typeImageList = application.Application.Extensions.GetTypesImageList();
      imageListTypeIcons.Images.Add( new System.Drawing.Bitmap( 16, 16 ) );
      imageListTypeIcons.Images.Add( ":Folder", EditorPluginResources.Folder );
      imageListTypeIcons.Images.Add( ":Deleted", EditorPluginResources.Delete2 );
    }

    protected override void OnLoad( EventArgs e )
    {
      base.OnLoad( e );

      data.GetInfoFinished += OnGetInfoFinished;
      data.StartGetInfo();
      splitContainer1.Panel2Collapsed = true;
    }

    #region Filling the form

    private void OnGetInfoFinished( bool success )
    {
      if ( !success )
      {
        labelStatus.Text = "Failed to get SVN information";
        Text += " - FAILED";
        return;
      }

      splitContainer1.Panel2Collapsed = false;
      splitContainer1.SplitterDistance = splitContainer1.Height / 2;
      labelStatus.Text = "Modifications found:";

      FillAssetTree();
    }

    private void FillAssetTree()
    {
    	try
    	{
				treeViewAssets.BeginUpdate();

				foreach ( var item in data.Assets )
				{
					AddAssetToTree( item.Key, item.Value );
				}

				treeViewAssets.ExpandAll();
    	}
    	finally 
    	{
				treeViewAssets.EndUpdate();
    	}     
    }

		private void AddAssetToTree( string path, AssetInfo assetInfo )
		{
			string fileName = Path.GetFileNameWithoutExtension( path );
			if ( assetInfo.SourceFiles.Count > 0 )
				fileName += string.Format( " ({0} data, {1} source)", assetInfo.DataFiles.Count, assetInfo.SourceFiles.Count );
			else
				fileName += string.Format( " ({0} data)", assetInfo.DataFiles.Count );

			TreeNode resNode = new TreeNode( fileName );
			resNode.Checked = false;
			resNode.Tag = assetInfo;

			string imageKey = string.Empty;

			if ( assetInfo.DataFiles.Count > 0 && assetInfo.DataFiles[0].File == path
				&& assetInfo.DataFiles[0].LocalContentStatus == SvnStatus.Deleted )
			{
				imageKey = ":Deleted";
			}
			else
			{
				DBResource res = DataBase.Get<DBResource>( DBID.FromFileName( path, false ) ).Get();
				if ( res != null )
				{
					imageKey = res.GetType().Name;
					if ( !imageListTypeIcons.Images.ContainsKey( imageKey ) )
					{
						int imgIndex = application.Application.Extensions.GetTypeIconIndex( res.GetType(), true );
						if ( imgIndex < 0 )
							imgIndex = 0;   // Empty image
						imageListTypeIcons.Images.Add( imageKey, typeImageList.Images[imgIndex] );
					}
				}
			}

			resNode.ImageKey = imageKey;
			resNode.SelectedImageKey = imageKey;

			TreeNode parentNode = GetOrCreateParentNode( path );

			if ( parentNode != null )
				parentNode.Nodes.Add( resNode );
			else
				treeViewAssets.Nodes.Add( resNode );
		}

    private TreeNode GetOrCreateParentNode( string path )
    {
      string[] parts = path.Split( FileUtils.pathSeparatorChars );

      if ( parts.Length <= 2 )
        return null;

      TreeNode result = null;

      foreach ( TreeNode item in treeViewAssets.Nodes )
      {
        if ( item.Name == parts[1] )
        {
          result = item;
          break;
        }
      }

      if ( result == null )
      {
      	TreeNode folderNode = CreateFolderNode(parts[1]);
      	treeViewAssets.Nodes.Add( folderNode );
				result = folderNode;
      }
        

      for ( int i = 2; i < parts.Length - 1; ++i )
      {
        bool found = false;
        foreach ( TreeNode item in result.Nodes )
        {
          if ( item.Name == parts[i] )
          {
            result = item;
            found = true;
            break;
          }
        }

        if ( !found )
        {
					TreeNode folderNode = CreateFolderNode( parts[i] );
					result.Nodes.Add( folderNode );
					result = folderNode;
        }
          
      }
      
      return result;
    }

		private static TreeNode CreateFolderNode( string _name )
		{
			return new TreeNode
			{
				Text = _name,
				Name = _name, 
				ImageKey = ":Folder", 
				SelectedImageKey = ":Folder"
			};
		}

    #endregion

    #region Selection and checking logic

    private void treeViewAssets_AfterSelect( object sender, TreeViewEventArgs e )
    {
      listBoxResourceItems.Items.Clear();

      if ( e.Node == null || e.Node.Tag == null )
        return;

      AssetInfo assetInfo = (AssetInfo)e.Node.Tag;

      listBoxResourceItems.Items.Add( "Data:" );

      foreach ( var item in assetInfo.DataFiles )
      {
        string line = string.Format( "  {0}: {1}", item.LocalContentStatus, item.File );
        listBoxResourceItems.Items.Add( line );
      }
      
			if ( assetInfo.SourceFiles.Count > 0 )
      {
        listBoxResourceItems.Items.Add( "Sources:" );
      
				foreach ( var item in assetInfo.SourceFiles )
        {
          string line = string.Format( "  {0}: {1}", item.LocalContentStatus, item.File );
          listBoxResourceItems.Items.Add( line );
        }
      }
    }

    private bool processingNodeCheck = false;
    private void treeViewAssets_AfterCheck( object sender, TreeViewEventArgs e )
    {
      if ( processingNodeCheck )
        return;

      processingNodeCheck = true;

      TreeNode node = e.Node;
      bool checkedState = node.Checked;

      SetCheckedState( node, checkedState, true );

      processingNodeCheck = false;
    }

    private void SetCheckedState( TreeNode node, bool checkedState, bool passToChildren )
    {
      if ( node.Checked != checkedState )
        node.Checked = checkedState;

      if ( node.Tag != null )
      {
				AssetInfo assetInfo = (AssetInfo)node.Tag;

        if ( checkedState != assetInfo.SelectedForCommit )
        {
          assetInfo.SelectedForCommit = checkedState;
          UpdateCommitButtonAndText();
        }
      }
      else if ( passToChildren )
      {
        foreach ( TreeNode child in node.Nodes )
        {
					SetCheckedState( child, checkedState, true );	
        }
      }

      if ( !checkedState && node.Parent != null )
        SetCheckedState( node.Parent, false, false );
    }

    #endregion

    #region Mouse events

    private void treeViewAssets_MouseDoubleClick( object sender, MouseEventArgs e )
    {
      if ( treeViewAssets.SelectedNode == null
        || treeViewAssets.SelectedNode.Tag == null
        || !( treeViewAssets.SelectedNode.Tag is AssetInfo ) )
        return;

      AssetInfo assetInfo = treeViewAssets.SelectedNode.Tag as AssetInfo;
      if ( assetInfo == null || assetInfo.DataFiles.Count == 0 )
        return;

      if ( !assetInfo.DataFiles[0].File.Contains( "xdb" )
        || assetInfo.DataFiles[0].LocalContentStatus == SvnStatus.Added
        || assetInfo.DataFiles[0].LocalContentStatus == SvnStatus.Deleted )
      {
        MessageBox.Show( "Main file unchanged or deleted" );
        return;
      }

      ShowDiff( assetInfo.DataFiles[0] );
    }

    private void treeViewAssets_MouseClick( object sender, MouseEventArgs e )
    {
      if ( e.Button != MouseButtons.Right )
        return;

      TreeNode node = treeViewAssets.GetNodeAt( e.Location );

      if ( node == null )
        return;

      ContextMenu menu = new ContextMenu();
      MenuItem diffItem = new MenuItem( "Diff", DiffItemEventHandler );

      AssetInfo assetInfo = node.Tag as AssetInfo;
      if ( assetInfo == null || assetInfo.DataFiles.Count == 0 )
      {
        diffItem.Enabled = false;
      }
      else
      {
        ChangeItemInfo info = assetInfo.DataFiles[0];
        if ( !info.File.Contains( "xdb" ) || info.LocalContentStatus == SvnStatus.Added || info.LocalContentStatus == SvnStatus.Deleted )
          diffItem.Enabled = false;
        else
          diffItem.Tag = info;
      }
      menu.MenuItems.Add( diffItem );

      MenuItem revertItem = new MenuItem( "Revert", RevertItemEventHandler );
      if ( assetInfo != null )
      {
        revertItem.Tag = assetInfo;
      }
      else
      {
        List<AssetInfo> assetList = new List<AssetInfo>();
        CollectAssetsFromSubnodes( node, assetList );

        if ( assetList.Count > 0 )
        {
          revertItem.Text = string.Format( "Revert {0} asset(s)", assetList.Count );
          revertItem.Tag = assetList;
        }
        else
          revertItem.Enabled = false;
      }

      if ( EditorsPool.Count > 0 )
        revertItem.Enabled = false;

      menu.MenuItems.Add( revertItem );

      menu.Show( this, e.Location );
    }

    private void CollectAssetsFromSubnodes( TreeNode node, List<AssetInfo> assetList )
    {
      if ( node.Tag != null )
      {
        AssetInfo assetInfo = node.Tag as AssetInfo;
        if ( assetInfo != null )
          assetList.Add( assetInfo );
      }

      foreach ( TreeNode subNode in node.Nodes )
      {
				CollectAssetsFromSubnodes( subNode, assetList );
      }
    }

    private void DiffItemEventHandler( object sender, EventArgs e )
    {
      MenuItem item = sender as MenuItem;

			if(item == null) 
				return;

      ChangeItemInfo status = item.Tag as ChangeItemInfo;
      
			if ( status == null)
        return;

      ShowDiff( status );
    }

    private void RevertItemEventHandler( object sender, EventArgs e )
    {
      MenuItem menuItem = sender as MenuItem;

			if(menuItem == null)
				return;

      List<ChangeItemInfo> dataItems = new List<ChangeItemInfo>();
      List<ChangeItemInfo> sourceItems = new List<ChangeItemInfo>();
      List<AssetInfo> assetsToRevert = null;

      if ( menuItem.Tag is List<AssetInfo> )
      {
        assetsToRevert = (List<AssetInfo>)menuItem.Tag;
        GatherAllFilesForRevertFromList( assetsToRevert, out dataItems, out sourceItems );
        RemoveUsedFilesMarkedForRevert( dataItems, sourceItems, assetsToRevert );
      }
      else
      {
        AssetInfo info = menuItem.Tag as AssetInfo;
        if ( info == null )
          return;

        dataItems.AddRange( info.DataFiles );
        sourceItems.AddRange( info.SourceFiles );

        assetsToRevert = new List<AssetInfo>();
        assetsToRevert.Add( info );
        RemoveUsedFilesMarkedForRevert( dataItems, sourceItems, assetsToRevert );
      }

      DualCommitRevertForm form = new DualCommitRevertForm( dataItems, sourceItems );
      form.ShowDialog();
      if ( !form.Success )
        return;

      if ( !DoRevertAssets( dataItems, sourceItems ) )
        return;

      foreach ( var item in data.Assets )
      {
        if ( assetsToRevert.Contains( item.Value ) )
        {
          data.Assets.Remove( item.Key );
          break;
        }
      }

      RemoveRevertedTreeItems( treeViewAssets.Nodes, assetsToRevert );

      listBoxResourceItems.Items.Clear();
      textBoxCommitMessage.Text = string.Empty;
      checkBoxCustomText.Checked = false;
    }

    private void RemoveRevertedTreeItems( TreeNodeCollection treeNodeCollection, List<AssetInfo> removedAssets )
    {
      if ( treeNodeCollection.Count == 0 )
        return;

      List<TreeNode> toRemove = new List<TreeNode>();
      foreach ( TreeNode node in treeNodeCollection )
      {
        RemoveRevertedTreeItems( node.Nodes, removedAssets );

        if ( node.Tag == null )
        {
          if ( node.Nodes.Count == 0 )
            toRemove.Add( node );

          continue;
        }
        if ( removedAssets.Contains( node.Tag as AssetInfo ) )
          toRemove.Add( node );
      }

      foreach ( TreeNode node in toRemove )
      {
        treeNodeCollection.Remove( node );
      }
    }

    #endregion

    #region Commit button and commit message

    private bool updatingMessageAndCheckbox = false;
    private void UpdateCommitButtonAndText()
    {
			buttonCommit.Enabled = ( SelectedCount > 0 ) && ( !checkBoxCustomText.Checked || textBoxCommitMessage.Text.Length > 0 );
			linkLabelRevert.Visible = ( SelectedCount > 0 );

      if ( checkBoxCustomText.Checked )
        return;

      updatingMessageAndCheckbox = true;

			if ( SelectedCount == 0 )
			{
				textBoxCommitMessage.Text = string.Empty;
			}
      else
      {
				string result = string.Format( "BGB Automated Resource Commit: {0} asset(s)", SelectedCount ) + Environment.NewLine;
        foreach ( var item in data.Assets )
        {
          if ( !item.Value.SelectedForCommit )
            continue;

          string suffix = string.Empty;
          if ( item.Value.SourceFiles.Count > 0 )
            suffix = string.Format( " ({0} data, {1} source)", item.Value.DataFiles.Count, item.Value.SourceFiles.Count );
          else
            suffix = string.Format( " ({0} data)", item.Value.DataFiles.Count );

          result += Environment.NewLine + FileUtils.GetParentFolderPath( item.Key ) + Path.GetFileNameWithoutExtension( item.Key ) + suffix;
        }
      	textBoxCommitMessage.Text = result;
      }

      updatingMessageAndCheckbox = false;
    }

    private void textBoxCommitMessage_TextChanged( object sender, EventArgs e )
    {
      if ( updatingMessageAndCheckbox )
        return;

      checkBoxCustomText.Checked = true;
      checkBoxCustomText.Enabled = true;
    }

    private void checkBoxCustomText_CheckedChanged( object sender, EventArgs e )
    {
      if ( updatingMessageAndCheckbox )
        return;

      if ( !checkBoxCustomText.Checked )
      {
        UpdateCommitButtonAndText();
        checkBoxCustomText.Enabled = false;
      }
    }

    private void textBoxCommitMessage_KeyDown( object sender, KeyEventArgs e )
    {
      if ( e.Control && !e.Alt && !e.Shift && e.KeyCode == Keys.A )
      {
        textBoxCommitMessage.Select( 0, textBoxCommitMessage.Text.Length );
        e.Handled = true;
      }
    }

    #endregion

    #region Commit and cancel actions

    public bool Success { get; private set; }
    public List<string> DataTargets { get; private set; }
    public List<string> SourceTargets { get; private set; }
    public List<string> SourceAddTargets { get; private set; }
    public string LogMessage { get; private set; }

    private void buttonCommit_Click( object sender, EventArgs e )
    {
      if ( !RunChecks() )
      {
        Log.TraceWarning( "Checkers failed, commit aborted." );
        Success = false;
        Close();
        return;
      }
      Log.TraceMessage( "Checks successful. Committing." );

      FormCommitLists( DataTargets, SourceTargets );
      LogMessage = textBoxCommitMessage.Text;

      Success = true;
      Close();
    }

    private bool RunChecks()
    {
      foreach ( var item in data.Assets )
      {
        if ( !item.Value.SelectedForCommit )
          continue;

        // No checks for deletions
        if ( item.Value.DataFiles[0].File == item.Key && item.Value.DataFiles[0].LocalContentStatus == SvnStatus.Deleted )
          continue;

        DBID dbid = DBID.FromFileName( item.Key, false );
        DBResource res = DataBase.Get<DBResource>( dbid ).Get();

        if ( null == res )
        {
          Log.TraceError( "Unable to get resource: {0}", item.Key );
          return false;
        }

        if ( !application.Application.Extensions.CheckImmediate( dbid, application.Application, true ) )
          return false;
      }

      return true;
    }

    private void FormCommitLists( List<string> dataTargets, List<string> sourceTargets )
    {
      foreach ( var item in data.Assets )
      {
        if ( !item.Value.SelectedForCommit )
          continue;

        foreach ( var target in item.Value.DataFiles )
        {
          string path = FileUtils.Combine( application.Application.FileSystem.RootPath, target.File );
          if ( !dataTargets.Contains( path ) )
            dataTargets.Add( path );
        }

        foreach ( var target in item.Value.SourceFiles )
        {
          string path = FileUtils.Combine( application.Application.SourceFileSystem.RootPath, target.File );
          if ( !sourceTargets.Contains( path ) )
          {
            sourceTargets.Add( path );
            if ( target.LocalContentStatus == SvnStatus.NotVersioned )
              SourceAddTargets.Add( path );
          }
        }
      }
    }

    private void buttonCancel_Click( object sender, EventArgs e )
    {
      data.Halt();
      Success = false;
      Close();
    }

    #endregion

    #region Revert

    private void linkLabelRevert_LinkClicked( object sender, LinkLabelLinkClickedEventArgs e )
    {
      List<ChangeItemInfo> dataItems;
      List<ChangeItemInfo> sourceItems;

      if ( EditorsPool.Count > 0 )
      {
        MessageBox.Show( "Reverting can affect open editors. Close all active editors first.", "Warning", MessageBoxButtons.OK, MessageBoxIcon.Exclamation );
        return;
      }

      GatherAllFilesForRevert( out dataItems, out sourceItems );

      RemoveUsedFilesMarkedForRevert( dataItems, sourceItems );

      DualCommitRevertForm form = new DualCommitRevertForm( dataItems, sourceItems );
      form.ShowDialog();
      if ( !form.Success )
        return;

      if ( !DoRevertAssets( dataItems, sourceItems ) )
        return;

      List<string> keysToDelete = new List<string>();
      foreach ( var item in data.Assets )
      {
        if ( item.Value.SelectedForCommit )
          keysToDelete.Add( item.Key );
      }

      List<AssetInfo> removedAssets = new List<AssetInfo>();
      foreach ( string item in keysToDelete )
      {
        removedAssets.Add( data.Assets[item] );
        data.Assets.Remove( item );
      }

      RemoveRevertedTreeItems( treeViewAssets.Nodes, removedAssets );
      listBoxResourceItems.Items.Clear();
      textBoxCommitMessage.Text = string.Empty;
      checkBoxCustomText.Checked = false;
    }

    private void GatherAllFilesForRevert( out List<ChangeItemInfo> dataItems, out List<ChangeItemInfo> sourceItems )
    {
      dataItems = new List<ChangeItemInfo>();
      sourceItems = new List<ChangeItemInfo>();
      foreach ( var item in data.Assets )
      {
        if ( !item.Value.SelectedForCommit )
          continue;

        foreach ( ChangeItemInfo file in item.Value.DataFiles )
        {
          if ( !dataItems.Contains( file ) )
            dataItems.Add( file );
        }

        foreach ( ChangeItemInfo file in item.Value.SourceFiles )
        {
          if ( !sourceItems.Contains( file ) )
            sourceItems.Add( file );
        }
      }
    }

    private void GatherAllFilesForRevertFromList( List<AssetInfo> assetList, out List<ChangeItemInfo> dataItems, out List<ChangeItemInfo> sourceItems )
    {
      dataItems = new List<ChangeItemInfo>();
      sourceItems = new List<ChangeItemInfo>();
      foreach ( var item in assetList )
      {
        foreach ( ChangeItemInfo file in item.DataFiles )
        {
          if ( !dataItems.Contains( file ) )
            dataItems.Add( file );
        }

        foreach ( ChangeItemInfo file in item.SourceFiles )
        {
          if ( !sourceItems.Contains( file ) )
            sourceItems.Add( file );
        }
      }
    }

    private void RemoveUsedFilesMarkedForRevert( List<ChangeItemInfo> dataItems, List<ChangeItemInfo> sourceItems )
    {
      // Remove files that are used in other assets
      List<ChangeItemInfo> toRemove = new List<ChangeItemInfo>();
      foreach ( var item in dataItems )
      {
        foreach ( var asset in data.Assets )
        {
          if ( asset.Value.SelectedForCommit )    // Skip those that we added above
            continue;

          foreach ( ChangeItemInfo file in asset.Value.DataFiles )
          {
            if ( file == item )
              toRemove.Add( item );
          }
        }
      }
      foreach ( var item in toRemove )
        dataItems.Remove( item );

      toRemove.Clear();
      foreach ( var item in sourceItems )
      {
        foreach ( var asset in data.Assets )
        {
          if ( asset.Value.SelectedForCommit )    // Skip those that we added above
            continue;

          foreach ( ChangeItemInfo file in asset.Value.SourceFiles )
          {
            if ( file == item )
              toRemove.Add( item );
          }
        }
      }
      foreach ( var item in toRemove )
        sourceItems.Remove( item );
    }

    private void RemoveUsedFilesMarkedForRevert( List<ChangeItemInfo> dataItems, List<ChangeItemInfo> sourceItems, List<AssetInfo> ignore )
    {
      // Remove files that are used in other assets
      List<ChangeItemInfo> toRemove = new List<ChangeItemInfo>();
      foreach ( var item in dataItems )
      {
        foreach ( var asset in data.Assets )
        {
          if ( ignore.Contains( asset.Value ) ) 
            continue;

          foreach ( ChangeItemInfo file in asset.Value.DataFiles )
          {
            if ( file == item )
              toRemove.Add( item );
          }
        }
      }
      foreach ( var item in toRemove )
        dataItems.Remove( item );

      toRemove.Clear();
      foreach ( var item in sourceItems )
      {
        foreach ( var asset in data.Assets )
        {
          if ( ignore.Contains( asset.Value ) )
            continue;

          foreach ( ChangeItemInfo file in asset.Value.SourceFiles )
          {
            if ( file == item )
              toRemove.Add( item );
          }
        }
      }
      foreach ( var item in toRemove )
        sourceItems.Remove( item );
    }

    private bool DoRevertAssets( List<ChangeItemInfo> dataItems, List<ChangeItemInfo> sourceItems )
    {
      SvnClient client = new SvnClient();

      List<string> targets = new List<string>();
      if ( sourceItems.Count > 0 )
      {
        foreach ( var item in sourceItems )
        {
          targets.Add( item.Path );
        }
        try
        {
          client.Revert( targets );
        }
        catch ( System.Exception ex )
        {
          Log.TraceError( "Art Sources Revert failed: {0}", ex );
          return false;
        }
        Log.TraceMessage( "Art Sources Revert successful: {0} items", sourceItems.Count );

        targets.Clear();
      }

      List<string> addedTargetsToDelete = new List<string>();
      foreach ( var item in dataItems )
      {
        targets.Add( item.Path );
        if ( item.LocalContentStatus == SvnStatus.Added && File.Exists( item.FullPath ) )
          addedTargetsToDelete.Add( item.Path );
      }
      try
      {
        client.Revert( targets );

        foreach ( string t in addedTargetsToDelete )
          File.Delete( t );
      }
      catch ( Exception ex )
      {
        Log.TraceError( "Data Revert failed:", ex );
        return false;
      }
      Log.TraceMessage( "Data Revert successful: {0} items", dataItems.Count );

      if ( addedTargetsToDelete.Count > 0 )
      {
        ObjectsBrowserPanel ob = application.Panels.GetSingletonPanel<ObjectsBrowserPanel>();
        ob.Reset();
      }

      return true;
    }

    #endregion

  }
}
