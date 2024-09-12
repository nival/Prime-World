using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using libdb.DB;

namespace EditorLib.PropertiesEditor.PropertyPresets
{
  public partial class EditorConfigEditForm : Form
  {
    private class ItemInfo
    {
      public bool isVisible = false;
      public bool isEditable = false;
      public bool isList = false;
      public PropertyPresetConfig.OutlinerExpandState expand = PropertyPresetConfig.OutlinerExpandState.Collapse;
      public ItemInfo( bool v, bool e, bool l, PropertyPresetConfig.OutlinerExpandState x )
      {
        isVisible = v;
        isEditable = e;
        expand = x;
        isList = l;
      }
    }

    IEditorWinApplication application;
    PropertyPresetConfig.PresetConfigItem config;
    PropertyPresetConfig configSet;
    int configIndex;
    int typeIndex = -1;
    Type type = null;
    bool rightSideModified;

    // Call for a type (select properties) or for an enum (select values)
    public EditorConfigEditForm( IEditorWinApplication _application, Type objectType )
    {
      InitializeComponent();

      this.application = _application;
      configSet = application.Application.Settings.Get<PropertyPresetConfig>();
      if ( configSet.selectedPreset >= 0 && configSet.selectedPreset < configSet.configPresets.Count )
      {
        configIndex = configSet.selectedPreset;
        config = configSet.configPresets[configSet.selectedPreset].Clone();
      }
      else
      {
        this.DialogResult = DialogResult.Abort;
        this.Close();
        return;
      }
      this.Text = this.Text + config.name;

      PopulateLeftList( objectType );

      PopulateRightList();
    }

    public EditorConfigEditForm( IEditorWinApplication _application, int _configIndex )
    {
      InitializeComponent();

      this.application = _application;
      configSet = application.Application.Settings.Get<PropertyPresetConfig>();
      configIndex = _configIndex;
      config = configSet.configPresets[configIndex].Clone();
      this.Text = this.Text + config.name;

      PopulateLeftList( null );
    }

    private void PopulateLeftList( Type lookForType )
    {
      ListViewGroup newGroupC = new ListViewGroup( "Classes" );
      ListViewGroup newGroupE = new ListViewGroup( "Enums" );
      listViewAll.Groups.Add( newGroupC );
      listViewAll.Groups.Add( newGroupE );
      ListViewItem newListItem = null;
      Type itemType = null;

      List<string> nameList = new List<string>( config.fieldSets.Keys );
      nameList.Sort();
      foreach ( string item in nameList )
      {
        newListItem = new ListViewItem( item, newGroupC );
        if ( DataBase.TryGetType( item, out itemType ) )
        {
          newListItem.Tag = itemType;
          listViewAll.Items.Add( newListItem );
          if ( itemType == lookForType )
          {
            type = lookForType;
            newListItem.Selected = true;
          }
        }
      }

      nameList = new List<string>( config.hiddenEnumValues.Keys );
      nameList.Sort();
      foreach ( string item in nameList )
      {
        newListItem = new ListViewItem( item, newGroupE );
        if ( DataBase.TryGetType( item, out itemType ) )
        {
          newListItem.Tag = itemType;
          listViewAll.Items.Add( newListItem );
          if ( itemType == lookForType )
          {
            type = lookForType;
            newListItem.Selected = true;
          }
        }
      }

      // Not found, add new
      if ( lookForType != null && type == null )
      {
        type = lookForType;
        if ( type.IsEnum )
          newListItem = new ListViewItem( type.Name, newGroupE );
        else
          newListItem = new ListViewItem( type.Name, newGroupC );
        newListItem.Tag = type;
        listViewAll.Items.Add( newListItem );
        newListItem.Selected = true;
      }
    }

    private void PopulateRightList()
    {
      rightSideModified = false;
      listViewSelected.Items.Clear();
      buttonMoveUp.Enabled = false;
      buttonMoveDown.Enabled = false;
      if ( type == null )
        return;

      if ( type.IsEnum )
        PopulateRightListEnum();
      else
        PopulateRightListProperties();
    }

    private void AddRightItem( bool vis, bool edit, bool isList, PropertyPresetConfig.OutlinerExpandState exp, string name )
    {
      ListViewItem newItem = new ListViewItem();
      newItem.Tag = new ItemInfo( vis, edit, isList, exp );
      newItem.SubItems.Add( new ListViewItem.ListViewSubItem( newItem, "" ) );
      newItem.SubItems.Add( new ListViewItem.ListViewSubItem( newItem, "" ) );
      newItem.SubItems.Add( new ListViewItem.ListViewSubItem( newItem, name ) );
      listViewSelected.Items.Add( newItem );
    }

    private void PopulateRightListProperties()
    {
      labelRight.Text = "Properties availability:";
      bool newFieldSet = false;
      List<PropertyPresetConfig.FieldControlItem> fieldSet = null;
      if ( !config.fieldSets.ContainsKey( type.Name ) )
      {
        fieldSet = new List<PropertyPresetConfig.FieldControlItem>();
        newFieldSet = true;
      }
      else
        fieldSet = config.fieldSets[type.Name];

      List<DBFieldInfo> fields = new List<DBFieldInfo>( TypeUtils.GetFields( type, true ) );
      if ( fields.Count > 0 )
      {
        if ( newFieldSet )
        {
          foreach ( DBFieldInfo field in fields )
          {
            PropertyPresetConfig.OutlinerExpandState exp = TypeUtils.IsSimpleType( field.FieldType ) ?
              PropertyPresetConfig.OutlinerExpandState.NA : PropertyPresetConfig.OutlinerExpandState.Collapse;
            AddRightItem( true, true, TypeUtils.IsList( field.FieldType ), exp, field.Name );
          }

        }
        else
        {
          foreach ( PropertyPresetConfig.FieldControlItem item in fieldSet )
          {
            foreach ( DBFieldInfo field in fields )
            {
              if ( item.name == field.Name )
              {
                PropertyPresetConfig.OutlinerExpandState exp = item.expandInOutliner;
                if ( TypeUtils.IsSimpleType( field.FieldType ) )
                  exp = PropertyPresetConfig.OutlinerExpandState.NA;
                else if ( exp == PropertyPresetConfig.OutlinerExpandState.NA )
                  exp = PropertyPresetConfig.OutlinerExpandState.Collapse;
                AddRightItem( item.visible, item.visible && item.canEdit, TypeUtils.IsList( field.FieldType ), exp, item.name );
                fields.Remove( field );
                break;
              }
            }
          }

          foreach ( DBFieldInfo field in fields )
          {
            PropertyPresetConfig.OutlinerExpandState exp = TypeUtils.IsSimpleType( field.FieldType ) ?
              PropertyPresetConfig.OutlinerExpandState.NA : PropertyPresetConfig.OutlinerExpandState.Collapse;
            AddRightItem( true, true, TypeUtils.IsList( field.FieldType ), exp, field.Name );
          }
        }
      }
    }

    private void PopulateRightListEnum()
    {
      labelRight.Text = "Enum values availability:";
      List<string> visEnumSet;
      bool newEnumSet = false;
      if ( !config.hiddenEnumValues.ContainsKey( type.Name ) )
      {
        visEnumSet = new List<string>();
        newEnumSet = true;
      }
      else
        visEnumSet = config.hiddenEnumValues[type.Name];


      foreach ( object item in Enum.GetValues( type ) )
      {
        bool isVisible = true;
        if ( !newEnumSet && visEnumSet.Contains( item.ToString() ) )
          isVisible = false;
        AddRightItem( isVisible, false, false, PropertyPresetConfig.OutlinerExpandState.NA, item.ToString() );
      }
    }

    private void StoreRightSideModificationsProperties()
    {
      List<PropertyPresetConfig.FieldControlItem> visList = new List<PropertyPresetConfig.FieldControlItem>();
      foreach ( ListViewItem item in listViewSelected.Items )
      {
        ItemInfo info = item.Tag as ItemInfo;
        PropertyPresetConfig.FieldControlItem settings = new PropertyPresetConfig.FieldControlItem( item.SubItems[3].Text, info.isVisible, info.isEditable );
        settings.expandInOutliner = info.expand;
        visList.Add( settings );
      }
      config.fieldSets[type.Name] = visList;
    }

    private void StoreRightSideModificationsEnum()
    {
      List<string> invisList = new List<string>();
      foreach ( ListViewItem item in listViewSelected.Items )
      {
        ItemInfo info = item.Tag as ItemInfo;
        if ( !info.isVisible )
          invisList.Add( item.SubItems[3].Text );
      }
      config.hiddenEnumValues[type.Name] = invisList;
    }

    private void listViewAll_SelectedIndexChanged( object sender, EventArgs e )
    {
      if ( type != null )
      {
        if ( rightSideModified )
        {
          ListViewItem li = listViewAll.Items[typeIndex];
          li.ForeColor = listViewAll.ForeColor;

          if ( type.IsEnum )
            StoreRightSideModificationsEnum();
          else
            StoreRightSideModificationsProperties();
        }

        type = null;
        typeIndex = -1;
      }
      if ( listViewAll.SelectedItems.Count == 1 )
      {
        type = listViewAll.SelectedItems[0].Tag as Type;
        typeIndex = listViewAll.SelectedIndices[0];
      }

      PopulateRightList();
    }

    private void listViewSelected_DrawSubItem( object sender, DrawListViewSubItemEventArgs e )
    {
      if ( e.ColumnIndex == 3 )
      {
        e.DrawDefault = true;
        return;
      }
      ItemInfo info = e.Item.Tag as ItemInfo;
      if ( e.ColumnIndex == 0 && info.isVisible )
      {
        e.Graphics.DrawImageUnscaledAndClipped( EditorLibResources.ElementVisible, e.Bounds );
      }
      if ( e.ColumnIndex == 1 && info.isVisible && info.isEditable )
      {
        e.Graphics.DrawImageUnscaledAndClipped( EditorLibResources.ElementEditable, e.Bounds );
      }
      if ( e.ColumnIndex == 2 && info.isVisible && info.expand != PropertyPresetConfig.OutlinerExpandState.NA )
      {
        if ( info.expand == PropertyPresetConfig.OutlinerExpandState.Expand )
          e.Graphics.DrawImageUnscaledAndClipped( EditorLibResources.ElementExpand, e.Bounds );
        else if ( info.expand == PropertyPresetConfig.OutlinerExpandState.Collapse )
          e.Graphics.DrawImageUnscaledAndClipped( EditorLibResources.ElementCollapse, e.Bounds );
        else if ( info.expand == PropertyPresetConfig.OutlinerExpandState.ListExpand )
          e.Graphics.DrawImageUnscaledAndClipped( EditorLibResources.ElementListExpand, e.Bounds );
      }
    }

    private void buttonCancel_Click( object sender, EventArgs e )
    {
      this.DialogResult = DialogResult.Cancel;
      this.Close();
    }

    private void buttonOk_Click( object sender, EventArgs e )
    {
      if ( type != null )
      {
        if ( rightSideModified )
        {
          if ( type.IsEnum )
            StoreRightSideModificationsEnum();
          else
            StoreRightSideModificationsProperties();
        }
      }
      //Apply
      configSet.configPresets[configIndex] = config;

      this.DialogResult = DialogResult.OK;
      this.Close();
    }

    private void buttonMoveUp_Click( object sender, EventArgs e )
    {
      if ( listViewSelected.SelectedItems.Count != 1 || listViewSelected.SelectedIndices[0] <= 0 )
        return;

      rightSideModified = true;
      ListViewItem item = listViewSelected.SelectedItems[0];
      int oldIndex = listViewSelected.SelectedIndices[0];
      listViewSelected.Items.RemoveAt( oldIndex );
      listViewSelected.Items.Insert( oldIndex - 1, item );
      listViewSelected.Select();
    }

    private void buttonMoveDown_Click( object sender, EventArgs e )
    {
      if ( listViewSelected.SelectedItems.Count != 1
        || listViewSelected.SelectedIndices[0] >= listViewSelected.Items.Count - 1 )
        return;

      rightSideModified = true;
      ListViewItem item = listViewSelected.SelectedItems[0];
      int oldIndex = listViewSelected.SelectedIndices[0];
      listViewSelected.Items.RemoveAt( oldIndex );
      listViewSelected.Items.Insert( oldIndex + 1, item );
      listViewSelected.Select();
    }

    private void listViewSelected_SelectedIndexChanged( object sender, EventArgs e )
    {
      if ( type.IsEnum )
        return;

      if ( listViewSelected.SelectedItems.Count != 1 )
      {
        buttonMoveUp.Enabled = false;
        buttonMoveDown.Enabled = false;
      }
      else
      {
        if ( listViewSelected.Items.Count > 1 )
        {
          if ( listViewSelected.SelectedIndices[0] > 0 )
            buttonMoveUp.Enabled = true;
          else
            buttonMoveUp.Enabled = false;

          if ( listViewSelected.SelectedIndices[0] < listViewSelected.Items.Count - 1 )
            buttonMoveDown.Enabled = true;
          else
            buttonMoveDown.Enabled = false;
        }
      }
    }

    private void listViewSelected_MouseUp( object sender, MouseEventArgs e )
    {
      ListView lv = sender as ListView;
      if ( lv == null )
        return;
      ListViewItem li = lv.GetItemAt( e.X, e.Y );
      if ( li == null )
        return;
      int border1 = lv.Columns[0].Width;
      int border2 = border1 + lv.Columns[1].Width;
      int border3 = border2 + lv.Columns[2].Width;

      ItemInfo info = li.Tag as ItemInfo;
      if ( e.X < border1 )
      {
        info.isVisible = !info.isVisible;
        rightSideModified = true;
        if ( info.isVisible && !type.IsEnum )
        {
          info.isEditable = true;
        }
      }
      else if ( e.X < border2 && !type.IsEnum )
      {
        rightSideModified = true;
        info.isEditable = !info.isEditable;
      }
      else if ( e.X < border3 && info.expand != PropertyPresetConfig.OutlinerExpandState.NA  )
      {
        rightSideModified = true;

        if ( info.expand == PropertyPresetConfig.OutlinerExpandState.Collapse )
          info.expand = PropertyPresetConfig.OutlinerExpandState.Expand;
        else if ( info.expand == PropertyPresetConfig.OutlinerExpandState.ListExpand )
          info.expand = PropertyPresetConfig.OutlinerExpandState.Collapse;
        else if ( info.expand == PropertyPresetConfig.OutlinerExpandState.Expand )
          info.expand = info.isList ? PropertyPresetConfig.OutlinerExpandState.ListExpand 
            : PropertyPresetConfig.OutlinerExpandState.Collapse;
      }
      lv.Invalidate( li.Bounds );
    }

    private void buttonReset_Click( object sender, EventArgs e )
    {
      foreach ( ListViewItem item in listViewAll.SelectedItems )
      {
        Type itemType = item.Tag as Type;

        if ( itemType.IsEnum )
          config.hiddenEnumValues.Remove( itemType.Name );
        else
          config.fieldSets.Remove( itemType.Name );

        item.ForeColor = SystemColors.GrayText;
      }
      PopulateRightList();
      listViewAll.Invalidate();
    }

    private void checkBoxShowAll_CheckedChanged( object sender, EventArgs e )
    {
      if ( checkBoxShowAll.Checked )
      {
        listViewAll.Items.Clear();
        listViewAll.Groups.Clear();
        ListViewGroup newGroupC = new ListViewGroup( "Classes" );
        ListViewGroup newGroupE = new ListViewGroup( "Enums" );
        listViewAll.Groups.Add( newGroupC );
        listViewAll.Groups.Add( newGroupE );
        ListViewItem newListItem = null;
        ListViewItem rememberedSelection = null;
        foreach ( Type item in DataBase.KnownTypes )
        {
          bool itemInConfig = false;
          if ( item.IsEnum )
          {
            newListItem = new ListViewItem( item.Name, newGroupE );
            newListItem.Tag = item;
            if ( config.hiddenEnumValues.ContainsKey( item.Name ) )
              itemInConfig = true;
          }
          else
          {
            newListItem = new ListViewItem( item.Name, newGroupC );
            newListItem.Tag = item;
            if ( config.fieldSets.ContainsKey( item.Name ) )
              itemInConfig = true;
          }

          if ( !itemInConfig )
            newListItem.ForeColor = SystemColors.GrayText;
          listViewAll.Items.Add( newListItem );

          if ( type != null && item == type )
            rememberedSelection = newListItem;
        }

        if ( rememberedSelection != null )
        {
          rememberedSelection.Selected = true;
          typeIndex = listViewAll.Items.IndexOf( rememberedSelection );
        }
      }
      else
      {
        Type rememberedSelected = type;
        type = null;
        listViewAll.Items.Clear();
        listViewAll.Groups.Clear();
        PopulateLeftList( rememberedSelected );
        PopulateRightList();
      }
    }

  }
}
