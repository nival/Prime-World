using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace EditorPlugins.Committer
{
  public partial class DualCommitRevertForm : Form
  {
    public bool Success { get; private set; }

    internal DualCommitRevertForm( IEnumerable<ChangeItemInfo> _dataItems, IEnumerable<ChangeItemInfo> _sourceItems )
    {
      InitializeComponent();

      Success = false;

      foreach ( var item in _dataItems )
      {
				listBoxDataFiles.Items.Add( string.Format( "{0} {1}", item.LocalContentStatus, item.FullPath ) );
      }
        

      foreach ( var item in _sourceItems )
      {
				listBoxSourceFiles.Items.Add( string.Format( "{0} {1}", item.LocalContentStatus, item.FullPath ) );
      }
    }

    private void buttonOk_Click( object sender, EventArgs e )
    {
      Success = true;
      Close();
    }

  }
}
