using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using EditorLib;
using EditorPlugins.ObjectLayers;

namespace EditorPlugins.Forms
{
  public partial class SymmetricalForm : Form
  {
    private bool isSet = false;
    private IEditorWinApplication application = null;

    public SymmetricalForm( IEditorWinApplication app, BindingList<ObjectLayersPreset> presets )
    {
      application = app;
      InitializeComponent();

      if ( presets != null )
      {
        foreach( var preset in presets )
        {
          checkedListBox1.Items.Add( preset.Name );
        }
      }

      comboBox1.SelectedIndex = 0;
    }

    private void checkBox1_CheckedChanged( object sender, EventArgs e )
    {
      for ( int i = 0; i < this.checkedListBox1.Items.Count; i++ )
      {
        CheckState st = isSet ? CheckState.Unchecked : CheckState.Checked;
        checkedListBox1.SetItemCheckState( i, st );
      }
      isSet = !isSet;
    }

    public bool IsTerrainChecked()
    {
      return checkBox3.CheckState == CheckState.Checked;
    }

    public bool IsPointLightsChecked()
    {
      return checkBox2.CheckState == CheckState.Checked;
    }

    public bool IsScriptAreasChecked()
    {
      return checkBox4.CheckState == CheckState.Checked;
    }

    public bool IsRightToLeft()
    {
      return comboBox1.SelectedIndex == 1;
    }

    public List<string> GetCheckedObjectLayers()
    {
      List<string> res = new List<string>();
      for ( int i = 0; i < this.checkedListBox1.Items.Count; i++ )
      {
        if ( checkedListBox1.GetItemCheckState( i ) == CheckState.Checked )
        {
          res.Add( checkedListBox1.Items[i] as string );
        }
      }
      return res;
    }
  }
}
