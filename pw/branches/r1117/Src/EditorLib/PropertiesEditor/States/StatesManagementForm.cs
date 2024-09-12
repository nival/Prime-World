using System;
using System.Collections.Generic;
using System.Drawing;
using System.Text.RegularExpressions;
using System.Windows.Forms;
using libdb.DB;

namespace EditorLib.PropertiesEditor.States
{
  public partial class StatesManagementForm : Form
  {
    public class StateChanges
    {
      public List<string> AddedStates = new List<string>();
      public List<string> DeletedStates = new List<string>();
      public Dictionary<string, string> RenamedStates = new Dictionary<string, string>();
    }

    private DBPtr<DBResource> ptr = null;
    public StateChanges Changes = new StateChanges();

    private bool renamingState = false;

    public StatesManagementForm( DBPtr<DBResource> _ptr )
    {
      InitializeComponent();

      ptr = _ptr;

      FillListBox();
    }

    private void FillListBox()
    {
      listBoxStates.Items.Clear();
      List<string> states = ptr.GetStates();

      states.AddRange( Changes.AddedStates );
      foreach ( string item in Changes.DeletedStates )
        states.Remove( item );

      foreach ( string item in states )
      {
        if ( item.Length == 0 )
          continue;

        if ( Changes.RenamedStates.ContainsKey( item ) )
          listBoxStates.Items.Add( Changes.RenamedStates[item] );
        else
          listBoxStates.Items.Add( item );
      }
    }

    private void ShowTextBox()
    {
      textBoxEditName.Visible = true;
      textBoxEditName.Text = listBoxStates.SelectedItem.ToString();
      Rectangle itemRect = listBoxStates.GetItemRectangle( listBoxStates.SelectedIndex );
      textBoxEditName.Top = itemRect.Top + listBoxStates.Top;
      textBoxEditName.Left = itemRect.Left + listBoxStates.Left;
      textBoxEditName.SelectAll();
      textBoxEditName.Focus();
    }

    private void textBoxEditName_KeyPress( object sender, KeyPressEventArgs e )
    {
      if ( e.KeyChar == (char)27 )
      {
        textBoxEditName.Visible = false;
        e.Handled = true;
        if ( !renamingState )
          listBoxStates.Items.Remove( listBoxStates.SelectedItem );

        renamingState = false;
      }
      else if ( e.KeyChar == '\r' )
      {
        listBoxStates.Focus();
      }
    }

    private void textBoxEditName_Leave( object sender, EventArgs e )
    {
      textBoxEditName.Visible = false;
      string stateName = textBoxEditName.Text;
      stateName = stateName.Replace( ' ', '_' );

      if ( !Regex.IsMatch( stateName, "^[_A-Za-z0-9]+$" ) )
      {
        if ( !renamingState )
          listBoxStates.Items.Remove( listBoxStates.SelectedItem );

        renamingState = false;
        return;
      }

      if ( renamingState )
      {
        string oldName = listBoxStates.SelectedItem.ToString();
        if ( Changes.AddedStates.Contains( oldName ) )
        {
          Changes.AddedStates.Remove( oldName );
          Changes.AddedStates.Add( stateName );
        }
        else if ( Changes.RenamedStates.ContainsValue( oldName ) )
        {
          foreach ( var item in Changes.RenamedStates )
          {
            if ( item.Value == oldName )
            {
              Changes.RenamedStates[item.Key] = stateName;
              break;
            }
          }
        }
        else
          Changes.RenamedStates.Add( oldName, stateName );

        listBoxStates.Items[listBoxStates.SelectedIndex] = stateName;
      }
      else
      {
        if ( !Changes.AddedStates.Contains( stateName ) )
        {
          if ( Changes.DeletedStates.Contains( stateName ) )
            Changes.DeletedStates.Remove( stateName );
          else
            Changes.AddedStates.Add( stateName );

          listBoxStates.Items[listBoxStates.SelectedIndex] = stateName;
        }
      }
    }

    private void buttonAdd_Click( object sender, EventArgs e )
    {
      string stateName;
      int stateNumber = 0;
      do
      {
        stateNumber++;
        stateName = "State" + stateNumber;
      } while ( listBoxStates.Items.Contains( stateName ) );


      listBoxStates.Items.Add( stateName );
      listBoxStates.SelectedIndex = listBoxStates.Items.Count - 1;

      ShowTextBox();
    }

    private void buttonDelete_Click( object sender, EventArgs e )
    {
      if ( listBoxStates.SelectedItem == null )
        return;

      string stateName = listBoxStates.SelectedItem.ToString();

      if ( Changes.AddedStates.Contains( stateName ) )
        Changes.AddedStates.Remove( stateName );
      else
      {
        if ( Changes.RenamedStates.ContainsValue( stateName ) )
        {
          foreach ( var item in Changes.RenamedStates )
          {
            if ( item.Value == stateName )
            {
              stateName = item.Key;
              Changes.RenamedStates.Remove( stateName );
              break;
            }
          }
        }

        Changes.DeletedStates.Add( stateName );
      }

      listBoxStates.Items.RemoveAt( listBoxStates.SelectedIndex );
      listBoxStates.SelectedIndex = listBoxStates.Items.Count - 1;
    }

    private void buttonOk_Click( object sender, EventArgs e )
    {
      this.DialogResult = DialogResult.OK;
      // Apply changes
      foreach ( string item in Changes.DeletedStates )
        ptr.RemoveState( item );
      foreach ( string item in Changes.AddedStates )
        ptr.AddState( item );

      foreach ( var item in Changes.RenamedStates )
        ptr.RenameState( item.Key, item.Value );

      Close();
    }

    private void buttonCancel_Click( object sender, EventArgs e )
    {
      this.DialogResult = DialogResult.Cancel;
      Changes = new StateChanges();
      Close();
    }

    private void buttonRename_Click( object sender, EventArgs e )
    {
      if ( listBoxStates.SelectedItem == null )
        return;

      ShowTextBox();
      renamingState = true;
    }
  }
}
