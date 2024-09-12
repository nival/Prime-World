using System;
using System.IO;
using System.Windows.Forms;
using EditorLib.Settings;
using Tools.MayaExeInteraction;
using EditorLib;

namespace EditorPlugins.Wizards
{
  public partial class MayaConfigForm : Form
  {
    private readonly IEditorWinApplication application;

    public MayaConfigForm( IEditorWinApplication _application )
    {
      InitializeComponent();
      application = _application;
    }

		private void MayaConfigForm_Load( object sender, EventArgs e )
		{
			MayaProcessConfig conf = application.Application.Settings.Get<MayaProcessConfig>();
			txtPathToMaya.Text = string.IsNullOrEmpty( conf.PathToMaya ) ? @"maya.exe" : conf.PathToMaya;
		}

    private void btnOk_Click( object sender, EventArgs e )
    {
    	MayaProcessConfig conf = application.Application.Settings.Get<MayaProcessConfig>();
    	
			conf.PathToMaya = !string.IsNullOrEmpty(txtPathToMaya.Text) ? txtPathToMaya.Text : "maya.exe";
			
			MayaOperationsUtility.PathToMaya = conf.PathToMaya;
    }

  	private void btnBrowse_Click( object sender, EventArgs e )
		{
			using(OpenFileDialog ofd = new OpenFileDialog())
			{
				if ( !string.IsNullOrEmpty( txtPathToMaya.Text ) )
					ofd.InitialDirectory = Path.GetDirectoryName(txtPathToMaya.Text);
				
				ofd.RestoreDirectory = true;
				ofd.Filter = "Maya|maya.exe|All files (*.*)|*.*";
				
				if(ofd.ShowDialog() == DialogResult.OK)
					txtPathToMaya.Text = ofd.FileName;
			}
		}
  }

  [ConfigObject( true )]
  public class MayaProcessConfig : SimpleConfigObject
  {
  	public string PathToMaya { get; set; }
  }
}
