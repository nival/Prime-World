using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using EditorLib.FieldProcessor;
using EditorLib.FolderSelector;
using EditorLib.IO;
using libdb.DB;

namespace EditorLib.Wizards.TableDataEditing
{
  public partial class TableDataPresetsForm : Form
	{
		#region Nested Types

		private class DataItem
		{
			public List<Type> SelectedTypes { get; private set; }
			public DBFieldInfo Field { get; private set; }
			public string Filter { get; set; }

			public DataItem(DBFieldInfo _field)
				: this(_field, new Type[0]){}

			public DataItem(DBFieldInfo _field, IEnumerable<Type> _selectedTypes)
			{
				Field = _field;
				SelectedTypes = new List<Type>( _selectedTypes );
			}

			public string GetTypesString()
			{
				return string.Join(", ", SelectedTypes.ConvertAll(x => x.Name).ToArray());
			}
		}

		#endregion

		private const string PLACEHOLDER = "%placeholder%";
    private readonly IEditorWinApplication application;
  	private readonly List<TableDataPreset> modifiedPresets = new List<TableDataPreset>();

    public TableDataPresetsForm(IEditorWinApplication _app, TableDataPreset _selectedPreset)
    {
      InitializeComponent();
      application = _app;
			treeProperties.PathSeparator = ".";

			BindPresetTypes();

    	TableDataPresetConfig presetsConfig = application.Application.Settings.Get<TableDataPresetConfig>();

    	foreach(TableDataPreset p in presetsConfig.Presets)
    	{
    		TableDataPreset copy = p.Clone();
				modifiedPresets.Add( copy );

				if ( p == _selectedPreset )
					_selectedPreset = copy;
    	}

			lstPresets.Items.AddRange(modifiedPresets.ToArray());
			lstPresets.DisplayMember = "Name";

    	if(_selectedPreset != null)
    		lstPresets.SelectedItem = _selectedPreset;
    	else if(lstPresets.Items.Count > 0)
    		lstPresets.SelectedIndex = 0;
    	else
    		HidePresetsEditor(true);
    }

  	private void BindPresetTypes()
  	{
  		cboType.AutoCompleteMode = AutoCompleteMode.Append;
  		cboType.AutoCompleteSource = AutoCompleteSource.ListItems;
  		cboType.DisplayMember = "Name";
  		cboType.DataSource = DataBase.KnownTypes;
  	}

  	public TableDataPreset SelectedPreset { get; private set; }

		#region Event Handlers

    private void OnRootFolderClick( object sender, EventArgs e )
    {
      var folderSelector = new FolderSelectorForm();

      if( folderSelector.ShowDialog() == DialogResult.OK )
      {
        txtRootFolder.Text = folderSelector.CurrentFolder;
      }
    }

    private void OnTypeChanged( object sender, EventArgs e )
    {
			ChangePresetType( cboType.SelectedItem as Type );
    }

  	private void OnBeforeNodeExpand( object sender, TreeViewCancelEventArgs e )
    {
    	LoadSubnodes(e.Node);
    }

		private void OnAddPresetClick( object sender, EventArgs e )
		{
			TableDataPreset preset = new TableDataPreset
			{
				Name = GeneratePresetName(),
				RootFolder = ObjectsRootFolder.Root.FullName
			};

			AddPreset(preset);

			lstPresets.SelectedItem = preset;

			treeProperties.Nodes.Clear();
			cboType.SelectedIndex = 0;
			ChangePresetType( cboType.SelectedItem as Type );
		}

		private void OnDeletePresetClick(object sender, EventArgs e)
		{
			int index = lstPresets.SelectedIndex;		
			RemovePreset( lstPresets.SelectedItem as TableDataPreset );

			if ( index == 0 && lstPresets.Items.Count > 0 )
				lstPresets.SelectedIndex = 0;
			else if ( index > 0 && index <= lstPresets.Items.Count )
				lstPresets.SelectedIndex = index - 1;
		}

		private void OnPresetSelected(object sender, EventArgs e)
		{
			TableDataPreset preset = lstPresets.SelectedItem as TableDataPreset;
			FillControls(preset);
			HidePresetsEditor( lstPresets.SelectedIndex < 0 );
		}

		private void OnLeavePreset( object sender, EventArgs e )
		{
			List<TableDataProperty> properties = GetCheckedProperties();

			if ( properties.Count == 0 )
			{
				MessageBox.Show( "No properties checked.\nPlease check properties.", "Table Data", MessageBoxButtons.OK, MessageBoxIcon.Exclamation );
				treeProperties.Focus();
				return;
			}

			FillPreset( lstPresets.SelectedItem as TableDataPreset );
		}

  	private void OnSaveClick( object sender, EventArgs e )
		{
			TableDataPresetConfig presetsConfig = application.Application.Settings.Get<TableDataPresetConfig>();
			presetsConfig.Presets = new List<TableDataPreset>( modifiedPresets );
  		SelectedPreset = lstPresets.SelectedItem as TableDataPreset;
			DialogResult = DialogResult.OK;
		}

    #endregion

    #region Array Types Selector

    private void OnNodeMouseClick( object sender, TreeNodeMouseClickEventArgs e )
    {
      if( e.Button == MouseButtons.Right )
      {
        DataItem info = e.Node.Tag as DataItem;

				if(info == null)
					return;

        if(TypeUtils.IsList( info.Field.FieldType ) )
        {
          Type baseType = TypeUtils.GetTypeFromList( info.Field.FieldType );

          ShowTypeSelectorMenu( e.Node, baseType, info.SelectedTypes );
        }
        else
        {
					var filterForm = new PropertyFilterForm();
					filterForm.Location = Cursor.Position;
        	filterForm.Filter = info.Filter;

					if ( filterForm.ShowDialog() == DialogResult.OK )
					{
						info.Filter = filterForm.Filter;
						ImprovedTreeNode node = e.Node as ImprovedTreeNode;

						if(node != null)
						{
							AddFilterToNode(node, info.Filter);
							node.Checked = true;
						}
							
					}
        }
      }
    }

  	private void AddFilterToNode(ImprovedTreeNode _node, string _filter)
  	{
			if(!_node.Checkable)
				return;

			if(string.IsNullOrEmpty(_filter))
			{
				_node.AdditionalText = string.Empty;
			}
			else
			{
				_node.AdditionalText = "Filter: " + _filter;
				_node.AdditionalFontColor = Color.Green;
				_node.AdditionalFont = new Font(treeProperties.AdditionalTextFont, FontStyle.Bold);	
			}			
  	}

  	#endregion

    #region Helper Methods

		private string GeneratePresetName()
		{
			string result = "New Preset";
			int num = 0;

			for ( int i = 0; i < modifiedPresets.Count; i++ )
			{
				if ( modifiedPresets[i].Name == result )
				{
					result = "New Preset " + num;
					++num;
					i = 0;
				}
			}

			return result;
		}

    private static bool IsSubnodesLoaded(TreeNode _node)
    {
      return _node.FirstNode == null || _node.FirstNode.Text != PLACEHOLDER;
    }

    private void LoadSubnodes( TreeNode node )
    {
      if( !IsSubnodesLoaded( node ) )
      {
        node.Nodes.Clear();

        DataItem info = node.Tag as DataItem;

        if( info != null )
        {
          Type tmpType;

          if( TypeUtils.IsList( info.Field.FieldType ) )
            tmpType = TypeUtils.GetTypeFromList( info.Field.FieldType );
          else
            tmpType = info.Field.FieldType;

          node.Nodes.AddRange( BuildNodes( tmpType ) );
        }
      }
    }

    private ImprovedTreeNode[] BuildNodes( Type _type )
    {
      List<ImprovedTreeNode> result = new List<ImprovedTreeNode>();

      Type tmpType = TypeUtils.IsDBPtr( _type ) ? TypeUtils.GetTypeFromPtr( _type ) : _type;

      foreach( DBFieldInfo field in TypeUtils.GetFields( tmpType, true ) )
      {
        ImprovedTreeNode node = new ImprovedTreeNode();
        node.Text = field.Name;

        if( TypeUtils.IsList( field.FieldType ) )
        {
          Type itemType = TypeUtils.GetTypeFromList( field.FieldType );

          if( TypeUtils.IsDBPtr( itemType ) )
            itemType = TypeUtils.GetTypeFromPtr( itemType );

          node.AdditionalText = itemType.Name;
          node.Tag = new DataItem( field, new List<Type>{itemType} );
          node.Checkable = false;
        }
        else
        {
          node.Tag = new DataItem( field );
        }

				if ( !SupressProperties( field.FieldType ) && !TypeUtils.IsSimpleType( field.FieldType ) && TypeUtils.GetFields( field.FieldType, true ).Length > 0 )
        {
          node.Nodes.Add( PLACEHOLDER );
        }

        result.Add( node );
      }

      return result.ToArray();
    }

  	private bool SupressProperties(Type _type)
  	{
  		IStringConvertor sc = application.Application.Extensions.CreateStringConverter( _type, application );

  		if ( sc != null )
  		{
  			return sc.SuppressProperties;
  		}

  		return false;
  	}

  	private ImprovedTreeNode[] BuildArrayNodes( Type[] _types )
    {
      List<ImprovedTreeNode> result = new List<ImprovedTreeNode>();

      foreach(Type type in _types)
      {
        foreach(ImprovedTreeNode node in BuildNodes( type ))
        {
          if(!result.Exists(n => n.Text == node.Text))
          {
            result.Add( node );
          }
        }
      }

      return result.ToArray();
    }

    private void ShowTypeSelectorMenu( TreeNode _node, Type _baseType, List<Type> _selectedTypes )
    {
      if( TypeUtils.IsSubclassOf( _baseType, typeof( DBPtr<> ) ) )
        _baseType = TypeUtils.GetTypeFromPtr( _baseType );

      CheckedMenu menu = new CheckedMenu( GetDerivedTypes( _baseType ), _selectedTypes.ToArray() );
      menu.Location = Cursor.Position;

			if (menu.ShowDialog() == DialogResult.OK)
			{
				Type[] types = menu.GetSelectedTypes();
				ApplayArrayTypes(_node, types);
			}
    }

    private void ApplayArrayTypes( TreeNode _node, Type[] _chekedTypes )
    {
      if( _node == null || _chekedTypes.Length <= 0 )
        return;

      DataItem dataItem = _node.Tag as DataItem;

      if( dataItem == null )
        return;

      if( CollectionUtils.ArrayEquals( _chekedTypes, dataItem.SelectedTypes.ToArray() ) )
        return;

      dataItem.SelectedTypes.Clear();
      dataItem.SelectedTypes.AddRange( _chekedTypes );
      ( (ImprovedTreeNode)_node ).AdditionalText = dataItem.GetTypesString();

      _node.Nodes.Clear();
      _node.Nodes.AddRange( BuildArrayNodes( _chekedTypes ) );
    }

    private static Type[] GetDerivedTypes( Type _baseType )
    {
      List<Type> result = new List<Type>();

      foreach( Type type in DataBase.KnownTypes )
      {
        if( TypeUtils.IsSubclassOf( type, _baseType ) )
          result.Add( type );
      }

      return result.ToArray();
    }

		private static int propertyIndex = 0;
    
		private List<TableDataProperty> GetCheckedProperties()
		{
			if ( treeProperties.Nodes.Count == 0 )
				return new List<TableDataProperty>();

			propertyIndex = 0;

			TableDataProperty root =  GetPropertiesInternal( treeProperties.Nodes[0] );

			if ( root != null )
				return root.Properties;

			return new List<TableDataProperty>();
		}
		
		private static TableDataProperty GetPropertiesInternal(TreeNode root)
		{
			TableDataProperty result = null;
			DataItem dataItem = root.Tag as DataItem;
      Type propertyType = typeof( object );
		  List < Type > arrayTypes = new List<Type>();
			string propertyFilter = string.Empty;

      if(dataItem != null)
      {
        propertyType =  dataItem.Field.FieldType;
        arrayTypes.AddRange( dataItem.SelectedTypes );
      	propertyFilter = dataItem.Filter;
      }

			if(root.Checked)
				result = new TableDataProperty( root.Text, propertyType, root.FullPath, propertyIndex++, propertyFilter );

			foreach (TreeNode node in root.Nodes)
			{
				TableDataProperty p = GetPropertiesInternal(node);
				
				if(p != null)
				{
					if(result == null)
					{
						result = new TableDataProperty(root.Text, propertyType, root.FullPath, -1);
				    result.ArrayTypes = arrayTypes;
					}

					result.Properties.Add(p);
				}
			}

			return result;
		}

		private void CheckNodesFromPreset( IEnumerable<TableDataProperty> properties )
    {
      foreach( TableDataProperty property in properties )
      {
        ImprovedTreeNode node = treeProperties.FindNodeByPath( property.Path ) as ImprovedTreeNode;
      	       
				if( node != null )
        {
        	((DataItem) node.Tag).Filter = property.Filter;

          if( property.Properties.Count > 0 )
          {
						LoadSubnodes(node);//приходится делать так, т.к. Expand происходит не сразу

            if(property.ArrayTypes.Count > 0)
              ApplayArrayTypes( node, property.ArrayTypes.ToArray() );
            
            node.Expand();
            CheckNodesFromPreset( property.Properties );
          }

					node.Checked = property.Index >= 0;
					
					if (!string.IsNullOrEmpty(property.Filter))
						AddFilterToNode( node, property.Filter );
        }
      }
    }

	  #endregion

		private void HidePresetsEditor( bool _hide )
		{
			grPreset.Visible = !_hide;
			label3.Visible = _hide;
		}

		private void ChangePresetType( Type _type )
		{
			treeProperties.Nodes.Clear();

			if ( _type == null )
				return;

			var rootNode = new ImprovedTreeNode
			{
				Text = _type.Name,
				Checkable = false
			};

			rootNode.Nodes.AddRange( BuildNodes( _type ) );

			treeProperties.Nodes.Add( rootNode );
			rootNode.Expand();
		}

		private void FillPreset( TableDataPreset _preset )
		{
			if (_preset == null) return;

			bool needUpdateName = _preset.Name != txtPresetName.Text;
			
			_preset.Name = txtPresetName.Text;
			_preset.RootFolder = txtRootFolder.Text;
			_preset.BaseType = (Type) cboType.SelectedItem;
			_preset.Properties = GetCheckedProperties();

			if (needUpdateName)
				UpdatePresetName();
		}

  	private void FillControls( TableDataPreset _preset )
		{
			if(_preset == null) return;

			txtPresetName.Text = _preset.Name;
			txtRootFolder.Text = _preset.RootFolder;

			if(_preset.BaseType != null)
				cboType.SelectedItem = _preset.BaseType;
			else
				cboType.SelectedIndex = 0;


			ChangePresetType(cboType.SelectedItem as Type);
			CheckNodesFromPreset( _preset.Properties );
		}

		private void AddPreset( TableDataPreset _preset )
		{
			modifiedPresets.Add(_preset);
			lstPresets.Items.Add(_preset);
		}

		private void RemovePreset( TableDataPreset _preset )
		{
			modifiedPresets.Remove(_preset);
			lstPresets.Items.Remove(_preset);
		}

  	private void UpdatePresetName()
  	{
  		int index = lstPresets.SelectedIndex;
  		TableDataPreset selectedPreset = lstPresets.SelectedItem as TableDataPreset;

  		if(selectedPreset != null)
  		{
  			selectedPreset.Name = txtPresetName.Text;
  			lstPresets.Items.RemoveAt(index);
  			lstPresets.Items.Insert(index, selectedPreset);
  			lstPresets.SelectedIndex = index;
  		}
  	}

		private void txtRootFolder_Leave( object sender, EventArgs e )
		{
			if ( string.IsNullOrEmpty( txtRootFolder.Text ) )
				txtRootFolder.Text = ObjectsRootFolder.Root.FullName;

			if ( !ObjectsRootFolder.Root.IsPathExists( txtRootFolder.Text ) )
			{
				MessageBox.Show( "Incorrect name of RootFolder", "RootFolder not set", MessageBoxButtons.OK, MessageBoxIcon.Exclamation );
				txtRootFolder.Focus();
			}
		}

		private void txtPresetName_Leave( object sender, EventArgs e )
		{
			if ( string.IsNullOrEmpty( txtPresetName.Text ) || txtPresetName.Text.Trim() == string.Empty )
			{
				TableDataPreset currentPreset = lstPresets.SelectedItem as TableDataPreset;

				if ( currentPreset != null )
					txtPresetName.Text = currentPreset.Name;
			}
		}

	}
}

