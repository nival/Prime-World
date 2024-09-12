using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using EditorLib.Settings;

namespace EditorLib.PropertiesEditor.PropertyPresets
{
  public partial class PresetConfigManager : Form
  {
    private IEditorWinApplication application;
    private PropertyPresetConfig config;
    private bool addingNewPreset = false;
    private int copyingPreset = -1;

    public PresetConfigManager( IEditorWinApplication application )
    {
      InitializeComponent();

      this.application = application;
      config = application.Application.Settings.Get<PropertyPresetConfig>();

      foreach ( var presetItem in config.configPresets )
      {
        listBoxPresets.Items.Add( presetItem.name );
      }

    }

    private void buttonClose_Click( object sender, EventArgs e )
    {
      Close();
    }

    private void buttonAdd_Click( object sender, EventArgs e )
    {
      listBoxPresets.Items.Add( "New Preset" );
      listBoxPresets.SelectedIndex = listBoxPresets.Items.Count - 1;

      ShowTextBox();
      addingNewPreset = true;
    }

    private void buttonDelete_Click( object sender, EventArgs e )
    {
      if ( listBoxPresets.SelectedItem == null )
        return;

      //TODO: warning dialog

      config.configPresets.RemoveAt( listBoxPresets.SelectedIndex );
      listBoxPresets.Items.RemoveAt( listBoxPresets.SelectedIndex );
    }

    private void buttonRename_Click( object sender, EventArgs e )
    {
      if ( listBoxPresets.SelectedItem == null )
        return;

      addingNewPreset = false;
      ShowTextBox();
    }

    internal void ShowTextBox()
    {
      textBoxEditName.Visible = true;
      textBoxEditName.Text = listBoxPresets.SelectedItem.ToString();
      Rectangle itemRect = listBoxPresets.GetItemRectangle( listBoxPresets.SelectedIndex );
      textBoxEditName.Top = itemRect.Top + listBoxPresets.Top;
      textBoxEditName.Left = itemRect.Left + listBoxPresets.Left;
      textBoxEditName.SelectAll();
      textBoxEditName.Focus();
    }

    private void textBoxEditName_Leave( object sender, EventArgs e )
    {
      textBoxEditName.Visible = false;

      listBoxPresets.Items[listBoxPresets.SelectedIndex] = textBoxEditName.Text;

      if ( addingNewPreset )
      {
        addingNewPreset = false;
        if ( copyingPreset >= 0 )
        {
          config.configPresets.Add( config.configPresets[copyingPreset].Clone() );
          copyingPreset = -1;
        }
        else
          config.configPresets.Add( new PropertyPresetConfig.PresetConfigItem() );
      }
      config.configPresets[listBoxPresets.SelectedIndex].name = textBoxEditName.Text;
    }

    private void textBoxEditName_KeyPress( object sender, KeyPressEventArgs e )
    {
      if ( e.KeyChar == (char)27 )
      {
        textBoxEditName.Visible = false;
        e.Handled = true;

        if ( addingNewPreset )
        {
          listBoxPresets.Items.Remove( listBoxPresets.SelectedItem );
        }
      }
      else if ( e.KeyChar == '\r' )
      {
        listBoxPresets.Focus();
      }
    }

    private void listBoxPresets_SelectedIndexChanged( object sender, EventArgs e )
    {
      if ( listBoxPresets.SelectedItem != null )
      {
        buttonDelete.Enabled = true;
        buttonRename.Enabled = true;
        buttonEdit.Enabled = true;
        buttonCopy.Enabled = true;
      }
      else
      {
        buttonDelete.Enabled = false;
        buttonRename.Enabled = false;
        buttonEdit.Enabled = false;
        buttonCopy.Enabled = false;
      }

    }

    private void buttonEdit_Click( object sender, EventArgs e )
    {
      if ( listBoxPresets.SelectedItem == null )
        return;

      EditorConfigEditForm editConfig = new EditorConfigEditForm( application, listBoxPresets.SelectedIndex );
      editConfig.ShowDialog();
    }

    private void listBoxPresets_MouseDoubleClick( object sender, MouseEventArgs e )
    {
      if ( listBoxPresets.SelectedItem == null )
        return;

      EditorConfigEditForm editConfig = new EditorConfigEditForm( application, listBoxPresets.SelectedIndex );
      editConfig.ShowDialog();
    }

    private void buttonCopy_Click( object sender, EventArgs e )
    {
      if ( listBoxPresets.SelectedItem == null )
        return;

      copyingPreset = listBoxPresets.SelectedIndex;
      listBoxPresets.Items.Add( listBoxPresets.SelectedItem.ToString() + " copy" );
      listBoxPresets.SelectedIndex = listBoxPresets.Items.Count - 1;

      ShowTextBox();
      addingNewPreset = true;
    }
  }
}
