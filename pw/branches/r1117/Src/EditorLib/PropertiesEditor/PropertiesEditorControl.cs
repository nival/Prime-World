using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Reflection;
using System.Windows.Forms;
using EditorLib.FieldProcessor;
using EditorLib.ObjectsBrowser;
using EditorLib.PropertiesEditor.States;
using EditorLib.Utils;
using libdb;
using libdb.DB;
using libdb.Diagnostics;
using libdb.UndoRedo;

namespace EditorLib.PropertiesEditor
{
  public partial class PropertiesEditorControl : UserControl
  {
    #region Events

    public class ShortcutEventArgs : EventArgs
    {
      public Shortcut Shortcut { get; private set; }

      public ShortcutEventArgs( Shortcut _shortcut )
      {
        Shortcut = _shortcut;
      }
    }

    public event EventHandler<ShortcutEventArgs> ShortcutPressed;

    private void InvokeShortcutPressed( Shortcut _shortcut )
    {
      InvokeShortcutPressed( new ShortcutEventArgs( _shortcut ) );
    }

    private void InvokeShortcutPressed( ShortcutEventArgs e )
    {
      EventHandler<ShortcutEventArgs> pressed = ShortcutPressed;
      if ( pressed != null )
        pressed( this, e );
    }

    #endregion

    private readonly Control propertyGridView = null;
    private IEditorWinApplication application;

    private int currentListIndex = -1;
    private object currentListTarget = null;
    private object lastSelectedObject = null;

    public PropertiesEditorControl()
    {
      InitializeComponent();
      components = new Container();

      foreach ( Control control in propertyGrid.Controls )
      {
        if ( control.GetType().ToString().Equals( "System.Windows.Forms.PropertyGridInternal.PropertyGridView" ) )
        {
          control.MouseClick += OnClick;
          control.MouseDoubleClick += OnDblClick;
          control.KeyUp += propertyGrid_KeyUp;
          propertyGridView = control;
        }
      }

      ShowMessage( "Properties Editor works only for single object", Color.Blue );
    }

    public ImprovedOutliner ImprovedOutliner { get; set; }

    public object SelectedObject
    {
      get { return lastSelectedObject; }
      set
      {
        SetSelectedObject( value, null );
        RefreshStatesCombo();
      }
    }

    public void SelectProperty( string _propertyName )
    {
      GridItemCollection items = propertyGrid.SelectedGridItem.Parent.GridItems;

      foreach ( GridItem gridItem in items )
      {
        if ( gridItem.PropertyDescriptor.DisplayName == _propertyName )
        {
          propertyGrid.SelectedGridItem = gridItem;
          break;
        }
      }
    }

    public GridItem SelectedGridItem
    {
      get { return propertyGrid.SelectedGridItem; }
    }

    public void Initialize( IEditorWinApplication application )
    {
      this.application = application;
      DataBase.ChangeDBResourceEvent += OnDBResourceChanged;
      cboStates.Visible = false;
    }

    #region States Manager

    private void RefreshStatesCombo()
    {
      try
      {
        cboStates.SelectedIndexChanged -= OnSelectedStateChanged;

        DBResource resource = SelectedObject as DBResource;

        bool showStatesManager = resource != null &&
                                 TypeUtils.HasAttribute<HasStatesAttribute>( resource.GetType(), true );

        cboStates.Items.Clear();
        cboStates.Visible = showStatesManager;

        if ( !showStatesManager )
          return;

        DBPtr<DBResource> ptr = DataBase.Get<DBResource>( resource.DBId );
        cboStates.Tag = ptr;

        List<string> states = ptr.GetStates();
        foreach ( string item in states )
        {
          if ( item == string.Empty )
            cboStates.Items.Add( "Default State" );
          else
            cboStates.Items.Add( item );

          if ( ptr.DefaultState == item )
            cboStates.SelectedIndex = cboStates.Items.Count - 1;
        }
        cboStates.Items.Add( "Manage..." );
      }
      finally
      {
        cboStates.SelectedIndexChanged += OnSelectedStateChanged;
      }
    }

    private void OnSelectedStateChanged( object sender, EventArgs e )
    {
      ToolStripComboBox combo = sender as ToolStripComboBox;

      if ( combo == null )
        return;

      DBPtr<DBResource> ptr = combo.Tag as DBPtr<DBResource>;

      if ( ptr == null )
        return;

      bool needRefresh = false;

      if ( cboStates.SelectedIndex == cboStates.Items.Count - 1 )
      {
        //Manage...
        StatesManagementForm form = new StatesManagementForm( ptr );
        form.ShowDialog();
        needRefresh = true;
      }

      //переселекчиваем объект, чтобы обновить свойства и аутлайнер
      if ( ptr.DefaultState != cboStates.SelectedItem.ToString() )
      {
        ptr.DefaultState = cboStates.SelectedItem.ToString();
        SetSelectedObject( ptr.Get( ptr.DefaultState ), null );
        ImprovedOutliner.SelectedObject = SelectedObject;
      }

      if ( needRefresh )
        RefreshStatesCombo();
    }

    #endregion

    internal void ExpandOneLevel()
    {
      FieldInfo fi = propertyGridView.GetType().GetField( "allGridEntries", BindingFlags.NonPublic | BindingFlags.Instance );
      if ( fi == null )
        return;
      GridItemCollection allItems = (GridItemCollection)fi.GetValue( propertyGridView );
      if ( allItems == null )
        return;

      List<GridItem> toExpand = new List<GridItem>();
      foreach ( GridItem item in allItems )
      {
        if ( item.Expandable && !item.Expanded )
          toExpand.Add( item );
      }
      foreach ( GridItem item in toExpand )
      {
        item.Expanded = true;
      }
    }

    internal void SetSelectedObject( object newSelection, Attribute[] customAttributes )
    {
      if ( lastSelectedObject == newSelection )
        return;

      if ( propertyGrid.IsDisposed )
        return;

      object descriptor = null;
      propertyGrid.SelectedObject = null;
      if ( !ReferenceEquals( newSelection, null ) )
      {
        ShowMessage( string.Empty, Color.Black );
        descriptor = new FullTypeDescriptorWrapper( newSelection, application, customAttributes );
        lastSelectedObject = newSelection;
      }
      else
      {
        ShowMessage( "Properties Editor works only for single object.", Color.Blue );
        lastSelectedObject = null;
      }
      propertyGrid.SelectedObject = descriptor;
      propertyGrid_SelectedGridItemChanged( null, null );
    }

    public MenuItem[] GetInlineMenuItemsForSelectedField()
    {
      if ( propertyGrid == null || propertyGrid.SelectedGridItem == null ||
           propertyGrid.SelectedGridItem.PropertyDescriptor == null ||
           !propertyGrid.SelectedGridItem.PropertyDescriptor.PropertyType.IsSubclassOf( typeof( DBPtrBase ) ) )
        return null;

      Type fieldType = TypeUtils.GetTypeFromPtr( propertyGrid.SelectedGridItem.PropertyDescriptor.PropertyType );
      bool emptyDBPtr = false;

      if ( propertyGrid.SelectedGridItem.Value is DBPtrBase )
      {
        object selectedObject = ( propertyGrid.SelectedGridItem.Value as DBPtrBase ).Get<DBResource>();
        if ( selectedObject == null )
          emptyDBPtr = true;
      }

      if ( fieldType == null || ( propertyGrid.SelectedGridItem.Value != null && !emptyDBPtr ) )
        return null;

      List<Type> types = new List<Type>();
      foreach ( Type type in DataBase.KnownTypes )
      {
        if ( type.IsSubclassOf( fieldType ) || type == fieldType )
        {
          types.Add( type );
        }
      }
      for ( int i = 0, k = 1; i < types.Count - 1; ++i )
      {
        for ( int j = k; j < types.Count; j++ )
        {
          if ( types[j].BaseType == types[i] )
          {
            types.Insert( k++, types[j] );
            types.RemoveAt( j + 1 );
          }
        }
      }
      //проверить терминальные классы
      for ( int i = 0; i < types.Count; ++i )
      {
        if ( !TypeUtils.CanCreate( types[i] ) )
        {
          types.RemoveAt( i-- );
        }
      }


      //временный контейнер для элементов, группирует элементы по первой букве их названия
      var typesDict = new Dictionary<string, List<Type>>();

      foreach ( Type type in types )
      {
        string key = Char.ToUpper( type.Name[0] ).ToString();

        if ( typesDict.ContainsKey( key ) )
          typesDict[key].Add( type );
        else
          typesDict[key] = new List<Type> { type };
      }

      //строим меню
      var mi = new List<MenuItem>();

      foreach ( var item in typesDict )//item'ы отсортированы по key
      {
        //сортируем пункты в меню
        item.Value.Sort( ( x, y ) => String.Compare( x.Name, y.Name, StringComparison.CurrentCultureIgnoreCase ) );

        IList list;

        //если у нас более 40 элементов, то группируем элементы в меню по 3 элемента, начинающихся на одну и ту же букву
        if ( types.Count > 40 && item.Value.Count > 3 )
        {
          //группируем
          var menuItem = new MenuItem( item.Key );
          mi.Add( menuItem );
          list = menuItem.MenuItems;
        }
        else
        {
          //не группируем
          list = mi;
        }

        foreach ( var t in item.Value )
        {
          list.Add( new MenuItem( t.Name, NewItem ) { Tag = t } );
        }
      }

      if ( mi.Count > 0 )
        return mi.ToArray();

      return null;
    }

    internal void RefreshView( bool select )
    {
      if ( select )
      {
        propertyGridView.Select();
      }
      propertyGrid.Refresh();
    }

    internal void GoToErrorState( string message )
    {
      propertyGrid.SelectedObject = null;
      ShowMessage( message, Color.Red );
    }

    public override void Refresh()
    {
      base.Refresh();
      propertyGrid.Refresh();
    }

    private void OnClick( object sender, MouseEventArgs e )
    {
      if ( GridItemClick != null )
      {
        GridItemClick( sender, e );
      }
    }

    private void OnDblClick( object sender, MouseEventArgs e )
    {
      MenuItem[] items = GetInlineMenuItemsForSelectedField();
      if ( e.Button == MouseButtons.Left && items != null )
      {
        ContextMenu menu = new ContextMenu();
        menu.MenuItems.AddRange( items );
        menu.Show( this, new Point( e.X, e.Y ) );
      }
    }

    private void propertyGrid_SelectedGridItemChanged( object sender, SelectedGridItemChangedEventArgs e )
    {
      UpdateListRelatedStuff();
    }

    private void propertyGrid_PropertyValueChanged( object s, PropertyValueChangedEventArgs e )
    {
      UpdateOutlinerItem( e.ChangedItem );

      //при изменении каких-либо свойств объекта в PE, запомнить текущую папку в recent folders
      var browserPanel = application.Panels.GetSingletonPanel<ObjectsBrowserPanel>();
      if ( browserPanel != null )
      {
        var folderBookmarks = application.Application.Settings.Get<FolderBookmarks>();
        if ( folderBookmarks != null )
        {
          folderBookmarks.RegisterRecentFolder( browserPanel.CurrentFolder );
        }
      }
    }

    public event EventHandler<MouseEventArgs> GridItemClick;

    private void UpdateOutlinerAfterListChanged()
    {
      propertyGrid.Refresh();
      UpdateListRelatedStuff();
      UpdateOutlinerItem( propertyGrid.SelectedGridItem );
    }

    private void UpdateOutlinerItem( GridItem _item )
    {
      if ( _item.Parent != null )
      {
        object refObject = _item.Parent.Value;

        if ( _item.Parent.Value is FullTypeDescriptorWrapper )
          refObject = ( (FullTypeDescriptorWrapper)refObject ).GetPropertyOwner();

        if ( refObject is DBPtrBase )
          refObject = ( (DBPtrBase)refObject ).Get<DBResource>();

        ImprovedOutliner.RefreshView( refObject );
      }
      else
      {
        ImprovedOutliner.RefreshView();
      }
    }

    private void ShowMessage( string message, Color color )
    {
      if ( string.IsNullOrEmpty( message ) )
      {
        messageLabel.Visible = false;
        propertyGrid.Visible = true;
      }
      else
      {
        messageLabel.Visible = true;
        propertyGrid.Visible = false;

        messageLabel.Text = message;
        messageLabel.ForeColor = color;
      }
    }

    private void NewItem( object sender, EventArgs e )
    {
      using ( supressOutlinerUpdate.Suppress() )
      {
        MenuItem item = sender as MenuItem;
        if ( item == null )
          return;

        Type type = item.Tag as Type;
        if ( type != null )
        {
          object proposedOwner = propertyGrid.SelectedGridItem.Value;
          if ( proposedOwner is DBPtrBase )
            proposedOwner = ( proposedOwner as DBPtrBase ).GetOwner();
          else if ( proposedOwner is FullTypeDescriptorWrapper )
            proposedOwner = ( proposedOwner as FullTypeDescriptorWrapper ).GetPropertyOwner();

          if ( proposedOwner is DBResource )
          {
            NewItem( type, DBID.FromDBID( ( proposedOwner as DBResource ).DBId, true ) );
          }
          else if ( proposedOwner is IOwnerable )
          {
            NewItem( type, DBID.FromDBID( ( proposedOwner as IOwnerable ).GetOwner().DBId, true ) );
          }
          else
          {
            // Ignore.
          }
        }
      }

      UpdateOutlinerItem( propertyGrid.SelectedGridItem );

      propertyGrid.Refresh();
    }

    private void NewItem( Type type, DBID dbid )
    {
      DBPtr<DBResource> ptr = DataBase.Create<DBResource>( dbid,
                                                           type.GetConstructor( Type.EmptyTypes ).Invoke( new object[0] )
                                                           as DBResource );
      object selectedObject = propertyGrid.SelectedGridItem.Parent.Value;
      if ( selectedObject is FullTypeDescriptorWrapper )
      {
        FullTypeDescriptorWrapper wrapper = selectedObject as FullTypeDescriptorWrapper;
        selectedObject = wrapper.GetPropertyOwner();
      }
      propertyGrid.SelectedGridItem.PropertyDescriptor.SetValue( selectedObject, ptr );
    }

    // KeyDown не ловится, можно не пробовать
    private void propertyGrid_KeyUp( object sender, KeyEventArgs e )
    {
      if ( e.Control && e.KeyCode == Keys.C )
      {
        InvokeShortcutPressed( Shortcut.CtrlC );	//Copy
      }
      else if ( e.Control && e.KeyCode == Keys.V )
      {
        InvokeShortcutPressed( Shortcut.CtrlV );	//Paste
      }
      else if ( e.Control && e.KeyCode == Keys.R )
      {
        InvokeShortcutPressed( Shortcut.CtrlR );	//Reset
      }

      if ( e.KeyCode != Keys.Tab )
        return;
      e.Handled = true;
      e.SuppressKeyPress = true;

      var gridItem = propertyGrid.SelectedGridItem;
      if ( gridItem == null )
        return;

      bool forward = true && !e.Shift;

      GridItem root = gridItem;
      while ( root.GridItemType != GridItemType.Root )
        root = root.Parent;

      List<GridItem> gridItems = new List<GridItem>();
      FindItems( root, gridItems );

      int index = gridItems.IndexOf( gridItem );

      if ( forward )
        gridItems[( ++index == gridItems.Count ) ? 0 : index].Select();
      else
        gridItems[( --index < 0 ) ? gridItems.Count - 1 : index].Select();

      // адский хак. 
      foreach ( Control ctl in propertyGridView.Controls )
      {
        if ( ctl.GetType().Name != "GridViewEdit" )
          continue;
        ctl.Focus();
        var tb = ctl as TextBox;
        if ( tb != null ) tb.SelectAll();
        break;
      }

    }

    private void FindItems( GridItem item, List<GridItem> gridItems )
    {
      switch ( item.GridItemType )
      {
      case GridItemType.Root:
      case GridItemType.Category:
        foreach ( GridItem i in item.GridItems )
        {
          FindItems( i, gridItems );
        }
        break;
      case GridItemType.Property:
        gridItems.Add( item );
        if ( item.Expanded )
        {
          foreach ( GridItem i in item.GridItems )
          {
            FindItems( i, gridItems );
          }
        }
        break;
      case GridItemType.ArrayValue:
        break;
      }
    }

    #region List editing buttons enabling/disabling

    private void UpdateListRelatedStuff()
    {
      currentListTarget = null;
      currentListIndex = -1;

      object selectedItemValue = null;
      object selectedItemParentValue = null;

      if ( propertyGrid.SelectedGridItem != null )
        selectedItemValue = propertyGrid.SelectedGridItem.Value;

      if ( propertyGrid.SelectedGridItem != null && propertyGrid.SelectedGridItem.Parent != null )
        selectedItemParentValue = propertyGrid.SelectedGridItem.Parent.Value;

      if ( selectedItemParentValue is FullTypeDescriptorWrapper )
        selectedItemParentValue = ( (FullTypeDescriptorWrapper)selectedItemParentValue ).GetPropertyOwner();

      Type selectedItemType = ( selectedItemValue != null ) ? selectedItemValue.GetType() : null;

      bool selectList = ( selectedItemValue != null && TypeUtils.IsList( selectedItemType ) );
      bool selectListItem = selectedItemParentValue != null && TypeUtils.IsList( selectedItemParentValue.GetType() );

      FindTargetList( selectedItemValue, selectedItemParentValue, selectList, selectListItem );

      if ( currentListTarget == null )
      {
        DisableListRelatedButtons();
        return;
      }

      if ( selectListItem && selectedItemValue != null )
      {
        PropertyInfo index = propertyGrid.SelectedGridItem.PropertyDescriptor.GetType().GetProperty( "Index" );
        if ( index != null )
          currentListIndex = (int)index.GetValue( propertyGrid.SelectedGridItem.PropertyDescriptor, null );
      }

      UpdateListRelatedButtons();
    }

    private void FindTargetList( object selectedItemValue, object selectedItemParentValue, bool selectList, bool selectListItem )
    {
      if ( !selectList && !selectListItem && null == selectedItemParentValue )
      {
        selectedItemValue = propertyGrid.SelectedObject;
        if ( selectedItemValue is FullTypeDescriptorWrapper )
          selectedItemValue = ( (FullTypeDescriptorWrapper)selectedItemValue ).GetPropertyOwner();

        if ( selectedItemValue != null && TypeUtils.IsList( selectedItemValue.GetType() ) )
          currentListTarget = selectedItemValue;
        selectedItemValue = null;
      }
      else if ( selectList )
      {
        currentListTarget = selectedItemValue;
        selectedItemValue = null;
      }
      else if ( selectListItem )
      {
        currentListTarget = selectedItemParentValue;
      }

      //if( currentListTarget != null)
      //  System.Diagnostics.Debug.Print( "List Type: {0}", currentListTarget.GetType().FullName );
    }

    private void UpdateListRelatedButtons()
    {
      if ( propertyGrid.SelectedGridItem != null && propertyGrid.SelectedGridItem.PropertyDescriptor != null )
      {
        AttributeCollection attributes = propertyGrid.SelectedGridItem.PropertyDescriptor.Attributes;

        foreach ( var attr in attributes )
        {
          if ( attr is ReadOnlyAttribute || attr is FixedList )
          {
            DisableListRelatedButtons();
            return;
          }
        }
      }

      if ( currentListTarget is IRichList )
      {
        IRichList richList = (IRichList)currentListTarget;

        DeleteListItem.Enabled = richList.CanDelete && currentListIndex != -1;
        AddItemLast.Enabled = richList.CanAdd;
        AddListItem.Enabled = richList.CanInsert && currentListIndex != -1;
        ClearList.Enabled = richList.MinCount == 0 && richList.Count > 0;
        btnMoveUpItem.Enabled = richList.CanMoveItems && richList.Count > 0 && currentListIndex > 0;
        btnMoveDownItem.Enabled = richList.CanMoveItems && richList.Count > 0 && currentListIndex >= 0 && currentListIndex < richList.Count - 1;
      }
      else
      {
        PropertyInfo countProperty = currentListTarget.GetType().GetProperty( "Count" );

        if ( null != countProperty )
        {
          int count = (int)countProperty.GetValue( currentListTarget, null );

          DeleteListItem.Enabled = count > 0 && currentListIndex != -1;
          ClearList.Enabled = count > 0;
        }

        AddItemLast.Enabled = true;
        AddListItem.Enabled = currentListIndex != -1;
        btnMoveUpItem.Enabled = currentListIndex > 0;
        btnMoveDownItem.Enabled = true;

        if ( currentListTarget is IList )
        {
          int count = ( (IList)currentListTarget ).Count;
          btnMoveDownItem.Enabled = ( currentListIndex >= 0 ) && ( currentListIndex < count - 1 );
        }
      }
    }

    private void DisableListRelatedButtons()
    {
      ClearList.Enabled = false;
      DeleteListItem.Enabled = false;
      AddListItem.Enabled = false;
      AddItemLast.Enabled = false;
      btnMoveDownItem.Enabled = false;
      btnMoveUpItem.Enabled = false;
    }

    private void AddItemLast_Click( object sender, EventArgs e )
    {
      Type listType = currentListTarget.GetType();
      Type itemType = TypeUtils.GetTypeFromList( listType );

      MethodInfo method = listType.GetMethod( "Add", new Type[1] { itemType } );

      if ( method != null )
      {
        using ( supressOutlinerUpdate.Suppress() )
        {
          method.Invoke( currentListTarget, new object[1] { TypeUtils.CreateInstance( itemType ) } );

          if ( propertyGrid.SelectedGridItem.PropertyDescriptor is ListElementDescriptor )
          {
            int index = propertyGrid.SelectedGridItem.Parent.GridItems.Count - 1;
            propertyGrid.SelectedGridItem = propertyGrid.SelectedGridItem.Parent.GridItems[index];
          }
          else
          {
            int index = propertyGrid.SelectedGridItem.GridItems.Count - 1;

            if ( index >= 0 && index < propertyGrid.SelectedGridItem.GridItems.Count )
            {
              propertyGrid.SelectedGridItem.Expanded = true;
              propertyGrid.SelectedGridItem = propertyGrid.SelectedGridItem.GridItems[index];
            }
          }
        }

        UpdateOutlinerAfterListChanged();
      }
      else
        Log.TraceError( "Can't add new item to list {0}: method \"Add\" did't exist!", currentListTarget.ToString() );
    }

    private void AddListItem_Click( object sender, EventArgs e )
    {
      Type listType = currentListTarget.GetType();
      Type itemType = TypeUtils.GetTypeFromList( listType );
      MethodInfo method = listType.GetMethod( "Insert", new Type[2] { typeof( int ), itemType } );
      if ( method != null )
      {
        int neededIndex = currentListIndex;

        using ( supressOutlinerUpdate.Suppress() )
        {
          method.Invoke( currentListTarget, new object[2] { currentListIndex, TypeUtils.CreateInstance( itemType ) } );

          if ( propertyGrid.SelectedGridItem.PropertyDescriptor is ListElementDescriptor )
          {
            propertyGrid.SelectedGridItem = propertyGrid.SelectedGridItem.Parent.GridItems[neededIndex];
          }
        }

        UpdateOutlinerAfterListChanged();
      }
      else
        Log.TraceError( "Can't Insert new item to list {0}: cannot find the method", currentListTarget.ToString() );
    }

    private void DeleteListItem_Click( object sender, EventArgs e )
    {
      Type listType = currentListTarget.GetType();
      MethodInfo method = listType.GetMethod( "RemoveAt", new Type[1] { typeof( int ) } );
      if ( method != null )
      {
        //запоминаем поселекченный список
        GridItem selectedList = null;

        if ( propertyGrid.SelectedGridItem.Parent != null && propertyGrid.SelectedGridItem.Parent.Value == currentListTarget )
          selectedList = propertyGrid.SelectedGridItem.Parent;

        //вычисляем индекс элемента, который нам нужно будет поселектить
        int neededIndex = currentListIndex;

        using ( supressOutlinerUpdate.Suppress() )
        {
          using ( UndoRedoTransaction trans = new UndoRedoTransaction( "Delete List Item" ) )
          {
            //беклинки актуальны только для объектов из DBTypes, 
            //для всего остального не имеет смысла вызывать этот метод, 
            //т.к. его логика основана на допущениях нашей ресурсной системы (объект не может ссылаться сам на себя иначе как через DBPtr)
            object dbTypesObject = propertyGrid.SelectedGridItem.Value;
            if ( dbTypesObject.GetType().Namespace == "DBTypes" )
              DataBase.RemoveBacklinksTo( dbTypesObject );

            //удаляем поселекченный элемент
            method.Invoke( currentListTarget, new object[1] { currentListIndex } );
            trans.Commit();
          }

          //надо обновить propertyGrid иначе будет считаться, что в нем еще не удалился элемент и возникнет исключение
          propertyGrid.Refresh();

          //после очистки элементов, выбираем список
          if ( selectedList != null )
          {
            propertyGrid.SelectedGridItem = selectedList;
          }

          if ( propertyGrid.SelectedGridItem.PropertyDescriptor is ListElementDescriptor )
          {
            neededIndex = neededIndex == 0 ? 0 : neededIndex - 1;
            propertyGrid.SelectedGridItem = propertyGrid.SelectedGridItem.Parent.GridItems[neededIndex];
          }
          else if ( propertyGrid.SelectedGridItem.Value == currentListTarget && propertyGrid.SelectedGridItem.GridItems.Count > 0 )
          {
            neededIndex = Math.Min( neededIndex, propertyGrid.SelectedGridItem.GridItems.Count - 1 );
            propertyGrid.SelectedGridItem = propertyGrid.SelectedGridItem.GridItems[neededIndex];
          }
        }

        UpdateOutlinerAfterListChanged();
      }
      else
        Log.TraceError( "Can't Remove new item from list {0}: cannot find the method", currentListTarget.ToString() );
    }

    private void ClearList_Click( object sender, EventArgs e )
    {
      Type listType = currentListTarget.GetType();
      MethodInfo method = listType.GetMethod( "Clear" );
      if ( method != null )
      {
        //запоминаем поселекченный список
        GridItem selectedList = null;

        if ( propertyGrid.SelectedGridItem.Parent.Value == currentListTarget )
          selectedList = propertyGrid.SelectedGridItem.Parent;

        using ( supressOutlinerUpdate.Suppress() )
        {
          using ( UndoRedoTransaction trans = new UndoRedoTransaction( "Clear List" ) )
          {
            //удаляем беклинки на удаляемые элементы списка
            foreach ( object listItem in (IEnumerable)currentListTarget )
            {
              DataBase.RemoveBacklinksTo( listItem );
            }

            method.Invoke( currentListTarget, null );

            trans.Commit();
          }

          //после очистки элементов, выбираем список
          if ( selectedList != null )
            propertyGrid.SelectedGridItem = selectedList;
        }

        UpdateOutlinerAfterListChanged();
      }
      else
        Log.TraceError( "Can't Clear items from list {0}: cannot find the method", currentListTarget.ToString() );
    }

    private void MoveUpListItem_Click( object sender, EventArgs e )
    {
      IList list = currentListTarget as IList;

      if ( list == null ) return;

      int index = currentListIndex;

      if ( index <= 0 ) return;

      using ( supressOutlinerUpdate.Suppress() )
      {
        using ( UndoRedoTransaction trans = new UndoRedoTransaction( "Move up list item" ) )
        {
          object tmp = list[index];

          list.RemoveAt( index );
          list.Insert( index - 1, tmp );

          trans.Commit();
        }

        if ( propertyGrid.SelectedGridItem.PropertyDescriptor is ListElementDescriptor )
        {
          propertyGrid.SelectedGridItem = propertyGrid.SelectedGridItem.Parent.GridItems[index - 1];
        }
      }

      UpdateOutlinerAfterListChanged();
    }

    private void MoveDownListItem( object sender, EventArgs e )
    {
      IList list = currentListTarget as IList;

      if ( list == null )
        return;

      int index = currentListIndex;

      if ( ( index < 0 ) || ( index >= list.Count - 1 ) )
        return;

      using ( supressOutlinerUpdate.Suppress() )
      {
        using ( UndoRedoTransaction trans = new UndoRedoTransaction( "Move down list item" ) )
        {
          object tmp = list[index];

          list.RemoveAt( index );
          list.Insert( index + 1, tmp );

          trans.Commit();
        }

        if ( propertyGrid.SelectedGridItem.PropertyDescriptor is ListElementDescriptor )
        {
          propertyGrid.SelectedGridItem = propertyGrid.SelectedGridItem.Parent.GridItems[index + 1];
        }
      }

      UpdateOutlinerAfterListChanged();
    }

    #endregion

    private readonly EventSuppressor supressOutlinerUpdate = new EventSuppressor();

    private void OnDBResourceChanged( DBID dbid )
    {
      if ( supressOutlinerUpdate.IsSuppressed )
        return;

      if ( IsHandleCreated && !IsDisposed )
      {
        ImprovedOutliner.Invoke( (MethodInvoker)( () => ImprovedOutliner.RefreshView( dbid ) ) );
      }
    }

    /// <summary> 
    /// Clean up any resources being used.
    /// </summary>
    /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
    protected override void Dispose( bool disposing )
    {
      if ( disposing && ( components != null ) )
      {
        components.Dispose();
        DataBase.ChangeDBResourceEvent -= OnDBResourceChanged;
      }
      base.Dispose( disposing );
    }
  }
}