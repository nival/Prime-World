using System;
using System.IO;
using System.Windows.Forms;
using libdb.IO;

namespace libdb.DB
{
	public partial class UninlineFileAsker : Form
	{
    private bool filenameGenerated = false;
    private DBID ownerDBID;
    private DBID generatedDBID;
    private Type type;

    public string FileName { get { return generatedDBID.GetFullFileName(); } }

		public UninlineFileAsker( DBID _ownerDBID, Type _type )
		{
			InitializeComponent();

      ownerDBID = _ownerDBID;
      type = _type;
			dir.Text = Path.GetDirectoryName( ownerDBID.FileName );
			if(dir.Text.Length > 0 )
			{
				dir.Text += "\\";
			}

      generatedDBID = DBID.GenerateUnique( dir.Text, "New", type );
      labelExt.Text = Path.GetExtension( generatedDBID.FileName );
    }

		private void ok_Click( object sender, EventArgs e )
		{
      generatedDBID = DBID.GenerateUnique( dir.Text, filename.Text, type );

      DialogResult = DialogResult.OK;
		}

		private void cancel_Click( object sender, EventArgs e )
		{
			DialogResult = DialogResult.Cancel;
    }

    private void filename_Enter(object sender, EventArgs e)
    {
      if ( !filenameGenerated )
      {
        filename.Text = FileUtils.GetFileNameWithoutExtension( generatedDBID.FileName );
        filenameGenerated = true;
      }
      
      ok.Enabled = true;
    }
	}
}
