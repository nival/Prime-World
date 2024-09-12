using System;
using System.Collections.Generic;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using EditorLib.IO;
using Win32;

namespace EditorLib.FolderSelector
{
  public partial class FolderSelectorForm : Form
  {
    public string CurrentFolder { get; private set; }

    public FolderSelectorForm()
    {
      InitializeComponent();

      CurrentFolder = ObjectsRootFolder.Root.FullName;

      treeFolders.ImageList = new ImageList();
      treeFolders.ImageList.ColorDepth = ColorDepth.Depth32Bit;
      treeFolders.ImageList.Images.Add( GetFolderIcon() );

      treeFolders.BeforeExpand += OnBeforeNodeExpand;     
    }

    #region Event Handlers

    private void OnBeforeNodeExpand( object sender, TreeViewCancelEventArgs e )
    {
      treeFolders.BeginUpdate();
      foreach( TreeNode node in e.Node.Nodes )
      {
        node.Nodes.AddRange( GetFolderNodes( node.Tag as ObjectsFolder ) );
      }
      treeFolders.EndUpdate();
    }

    private void FolderSelector_FormLoad( object sender, EventArgs e )
    {
      treeFolders.BeginUpdate();
      var rootNode = treeFolders.Nodes.Add( "Root" );
      rootNode.Tag = ObjectsRootFolder.Root;
      rootNode.Nodes.AddRange( GetFolderNodes( ObjectsRootFolder.Root ) );
      rootNode.Expand();
      treeFolders.EndUpdate();
    }
    
    private void btnOpen_Click( object sender, EventArgs e )
    {
      if( treeFolders.SelectedNode != null && treeFolders.SelectedNode.Tag is ObjectsFolder )
      {
        ObjectsFolder selectedFolder = (ObjectsFolder)treeFolders.SelectedNode.Tag;
        CurrentFolder = selectedFolder.FullName;
      }        
    }

    #endregion

    private static Icon GetFolderIcon()
    {
      SHFILEINFO shinfo = new SHFILEINFO();
      Shell.SHGetFileInfo( string.Empty, Kernel.FILE_ATTRIBUTE_DIRECTORY, ref shinfo, Marshal.SizeOf( shinfo ), Shell.SHGFI_ICON | Shell.SHGFI_SMALLICON | Shell.SHGFI_USEFILEATTRIBUTES );
      return Icon.FromHandle( shinfo.hIcon );
    }

    private static TreeNode[] GetFolderNodes( ObjectsFolder _rootFolder )
    {
      List<TreeNode> result = new List<TreeNode>();

      if( _rootFolder == null )
        return result.ToArray();

      foreach(ObjectsFolder folder in _rootFolder.Folders)
      {
        var node = new TreeNode();
        node.Text = folder.Name;
        node.Tag = folder;
        node.ImageIndex = 0;
        node.SelectedImageIndex = 0;

        result.Add(node);
      }

      return result.ToArray();
    }

  }
}
