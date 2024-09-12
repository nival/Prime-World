using System;
using System.Collections.Generic;
using System.Windows.Forms;
using DBTypes;
using EditorLib.ObjectSelector;
using libdb.DB;

namespace PF_Editor.Map.Wizard
{
	internal sealed partial class MapCreationDialog : Form
	{
	  private MapCreationInfo mapInfo = null;

    internal MapCreationInfo MapCreationInformation 
    { 
      get{ return mapInfo; }
    }

		internal MapCreationDialog()
		{
			InitializeComponent();
		}

		#region Event handlers.

    private void btnCreate_Click( object sender, EventArgs e )
    {
      if(string.IsNullOrEmpty(txtName.Text))
      {
        MessageBox.Show( "MapName can't be empty. Please fill Name.", "Error", MessageBoxButtons.OK,
                         MessageBoxIcon.Error );
        txtName.Focus();
        return;
      }

      FillMapInfo();

      if( !IsNameCorrect() )
      {
        MessageBox.Show( "Map with same Name exist or Name is incorrect. Please change map name.", "Error",
          MessageBoxButtons.OK, MessageBoxIcon.Error );
        txtName.Focus();
        return;
      }

      DialogResult = DialogResult.OK;
    }

    private void btnLightEnvironment_Click( object sender, EventArgs e )
    {
      SelectObjectReference( txtLightEnvironment.Text, typeof( LightEnvironment ), txtLightEnvironment );
    }

		#endregion

    private bool IsNameCorrect()
    {
      DBID dbid;
      return DBID.TryCreateDBID( mapInfo.Path, mapInfo.Name, typeof( AdvMap ), out dbid );
    }

    private void FillMapInfo()
    {
      mapInfo = new MapCreationInfo();
      mapInfo.Name = txtName.Text;
      mapInfo.EditableNatureMap = cbEditableNatureMap.Checked;
      mapInfo.Width = (int)numWidth.Value;
      mapInfo.Height = (int)numHeight.Value;
      mapInfo.Resolution = (int)numResolution.Value;
      mapInfo.LightEnvironmentId = CalculateId( txtLightEnvironment.Text );

      // TODO: night light environment
    }

		#region Private helper methods.

		private static DBID CalculateId( string text )
		{
			if ( string.IsNullOrEmpty( text ) )
			{
				return DBID.Empty;
			}

    	return DBID.FromFileName( text, false );
		}

		private static void SelectObjectReference( string currentFile, Type objectType, TextBox textBoxToPutValue )
		{
      DBID initialId = DBID.FromFileName( currentFile, false );
      ObjectSelectorForm selector = new ObjectSelectorForm( initialId, objectType );
			
      if ( selector.ShowDialog() == DialogResult.OK )
			{
				var dbId = selector.SelectedObject;
				if ( !DBID.IsNullOrEmpty( dbId ) && DataBase.IsExists( dbId ) )
				{
					textBoxToPutValue.Text = dbId.Name;
				}
				else
				{
					textBoxToPutValue.Text = string.Empty;
				}
			}
		}

		#endregion

	}

  internal class MapCreationInfo
  {
    private const string MAPS_PATH = @"\Maps\";
    private const string INITIAL_PATCH = @"/Terrain/Elements/Plain.STAT";
    
    public string Path 
    {
      get { return MAPS_PATH + Name; }
    }

    public string Name { get; set; }

    public bool EditableNatureMap { get; set; }
    
    public int Width { get; set; }
    
    public int Height { get; set; }
    
    public int Resolution { get; set; }

    public DBID LightEnvironmentId { get; set; }
    public DBID NightLightEnvironmentId { get; set; }
    
    public DBID InitialPatchTypeId 
    {
      get { return DBID.FromFileName( INITIAL_PATCH, false ); }
    }
  }
}
