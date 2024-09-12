using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using libdb.DB;

namespace EditorLib.ObjectsBrowser
{
  public partial class ChangeTypeForm : Form
  {
    private DBID dbid = DBID.Empty;
    private List<Type> allTypes = new List<Type>();

    public ChangeTypeForm( DBID _dbid )
    {
      InitializeComponent();
      dbid = _dbid;

      CollectCompatibleTypes();
      FillTypesList( string.Empty );
    }

    private void CollectCompatibleTypes()
    {
      DBPtr<DBResource> ptr = DataBase.Get<DBResource>( dbid );
      Type originalType = ptr.Get().GetType();
      allTypes.Clear();

      foreach ( Type type in DataBase.KnownResources )
      {
        if ( !TypeUtils.CanCreate( type ) || type == originalType )
          continue;

        bool canAdd = TypeUtils.IsSubclassOf( type, originalType.BaseType );
        if ( originalType.BaseType != null )
        {
          canAdd = canAdd || TypeUtils.IsSubclassOf( type, originalType.BaseType.BaseType );
        }

        if ( canAdd )
          allTypes.Add( type );
      }
    }

    private void FillTypesList( string searchString )
    {
      listBoxTypes.BeginUpdate();
      listBoxTypes.Items.Clear();
      foreach ( Type type in allTypes )
      {
        if ( type.Name.IndexOf( searchString, StringComparison.InvariantCultureIgnoreCase ) != -1 )
          listBoxTypes.Items.Add( type );
      }
      listBoxTypes.EndUpdate();
      CheckEnableOkButton();
    }

    private void buttonOk_Click( object sender, EventArgs e )
    {
      Type target = null;

      if ( listBoxTypes.SelectedItem != null )
        target = listBoxTypes.SelectedItem as Type;
      else if ( listBoxTypes.Items.Count == 1 )
        target = listBoxTypes.Items[0] as Type;

      if ( target != null && AttemptToConvert( target ) )
      {
        DialogResult = DialogResult.OK;
        Close();
      }
    }

    private void listBoxTypes_SelectedIndexChanged( object sender, EventArgs e )
    {
      CheckEnableOkButton();
    }

    private void CheckEnableOkButton()
    {
      bool enabled = false;

      if ( listBoxTypes.Items.Count == 1 || listBoxTypes.SelectedIndex != -1 )
        enabled = true;

      buttonOk.Enabled = enabled;
    }

    private void listBoxTypes_DoubleClick( object sender, EventArgs e )
    {
      if ( AttemptToConvert( listBoxTypes.SelectedItem as Type ) )
      {
        DialogResult = DialogResult.OK;
        Close();
      }
    }

    private bool AttemptToConvert( Type type )
    {
      if ( null == type )
        return false;

      return DBConvertResourceType.ConvertWithoutCheck( dbid, type );
    }

    private void tbSearch_TextChanged( object sender, EventArgs e )
    {
      FillTypesList( tbSearch.Text );
    }

    private void tbSearch_KeyUp( object sender, KeyEventArgs e )
    {
      int indMoveCoeff = 0;
      switch ( e.KeyCode )
      {
        case Keys.Enter:
          if ( buttonOk.Enabled )
            buttonOk_Click( null, null );
          break;
        case Keys.Down:
          indMoveCoeff = 1;
          break;
        case Keys.Up:
          indMoveCoeff = -1;
          break;
      }

      int index = listBoxTypes.SelectedIndex + indMoveCoeff;
      if ( index < 0 )
        index = 0;
      else if ( index >= listBoxTypes.Items.Count )
        index = listBoxTypes.Items.Count - 1;

      if ( listBoxTypes.Items.Count > 0 )
        listBoxTypes.SelectedIndex = index;
      CheckEnableOkButton();
    }

    private void ChangeTypeForm_Shown( object sender, EventArgs e )
    {
      tbSearch.Focus();
    }

    
  }
}
