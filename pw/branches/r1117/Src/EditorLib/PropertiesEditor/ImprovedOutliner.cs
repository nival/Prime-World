using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using EditorLib.PropertiesEditor.PropertyPresets;
using libdb.DB;
using libdb.Diagnostics;
using libdb.IO;

namespace EditorLib.PropertiesEditor
{
	public partial class ImprovedOutliner : UserControl
	{
		#region Private Fields

		private const string PLACEHOLDER = "%placeholder%";
		private const int MAX_LIST_SIZE = 100;

		private ImprovedTreeView treeView;
		private IEditorWinApplication application = null;
		private PropertiesEditorConfig config = null;//TODO можно вообще всю работу с конфигом вынести в PE

		private object selectedObject;
		private PropertyPresetConfig.PresetConfigItem selectedPreset;

		private object selectedRefObject = null;

		#endregion

		#region Initialization

		public ImprovedOutliner()
		{
			InitializeComponent();
			treeView.AfterSelect += OnAfterNodeSelect;
			SelectedPreset = null;
		}

		public void Initialize(IEditorWinApplication _application)
		{
			application = _application;
			config = application.Application.Settings.Get<PropertiesEditorConfig>();

			treeView.FullRowSelect = true;
			treeView.HideSelection = false;
			treeView.ImageList = application.Application.Extensions.GetTypesImageList();
			treeView.EnableColoring = config.IsOutlinerColored;
			ApplyColorScheme();
		}

		/// <summary>
		/// ищем ноду замапленную на определенный (dbid) ресурс 
		/// используется для обновления части аутлайнера, а не всего целиком
		/// </summary>
		private TreeNode FindNodeByDbId( DBID _dbId)
		{
			return treeView.FindNodeRecursive(node => (node.Tag is EntityItem) && ((EntityItem) node.Tag).dbId == _dbId);
		}
		
		/// <summary>
		/// ищем ноду замапленную на определенный объект
		/// используется для обновления части аутлайнера, а не всего целиком
		/// </summary>
		private TreeNode FindNodeByObject( TreeNodeCollection _nodes, object _subObject )
		{
			return ImprovedTreeView.FindNodeRecursive(_nodes, 
				node => (node.Tag is EntityItem && ((EntityItem) node.Tag).subObject == _subObject));
		}

		#endregion

		#region Public Properties

		[Browsable(false)]
		public object SelectedObject
		{
			get { return selectedObject; }
			set 
			{
				DateTime dt = DateTime.Now;

				//при смене выбранного объекта очищаем кеш
				treeView.StateContainer.Clear();

				selectedRefObject = null;

				selectedObject = value;
				RefreshView();

				System.Diagnostics.Debug.Print("SelectedObject: [{0}] {1:F3}ms", selectedObject ?? "null", (DateTime.Now - dt).TotalMilliseconds);
			}
		}

		//TODO при изменении настроек пресета, его нужно переселектить, иначе они не применятся тут
		[Browsable(false)]
		public PropertyPresetConfig.PresetConfigItem SelectedPreset
		{
			get { return selectedPreset; }
			set 
			{
				selectedPreset = value;
				//при смене пресета очищаем кеш, т.к. нам нужно привести ноды в соответствие с пресетом
				treeView.StateContainer.Clear();
			}
		}

		[DefaultValue(null)]
		public PropertiesEditorControl LinkedPropertiesEditor { get; set; }

		[DefaultValue(false)]
		public bool EnableColoring 
		{
			get { return treeView.EnableColoring; }
			set 
			{
				treeView.EnableColoring = value; 
				treeView.Refresh();
			}
		}

		#endregion

		#region Public Methods

		public void ApplyColorScheme()
		{
			treeView.LevelColors = config.OutlinerColors.ConvertAll( x => Color.FromArgb( x.A, x.R, x.G, x.B ) ).ToArray();
			treeView.Refresh();
		}

		//обновляет весь outliner, перестраивая все ноды
		public void RefreshView()
		{
			if (this.Visible)
			{
				treeView.StateContainer.SaveScrollPos();

				BuildRootNode();

				if ( selectedRefObject != null )
					treeView.SelectedNode = FindNodeByObject( treeView.Nodes, selectedRefObject );

				treeView.StateContainer.RestoreScrollPos();
			}
		}

		//обновляет outliner, перестраивая иерархию от указанного объекта
		public void RefreshView( object _subObject )
		{
			TreeNode node = FindNodeByObject( treeView.Nodes, _subObject );

			if ( node == null )
				return;//в outliner не загружена нода, соответствующая данному объекту, следовательно обновлять нечего

			if ( node.Parent == null )//самая первая нода, обновляем весь outliner
				RefreshView();
			else
				RefreshView( node.Parent );//обновляем парента, чтобы обновился счетчик вложенных объектов, например если парент - список
		}

		//обновляет outliner, перестраивая иерархию от указанного dbid
		public void RefreshView(DBID _dbid)
		{
			TreeNode node = FindNodeByDbId( _dbid );

			if ( node == null )
				return;//в outliner не загружена нода, соответствующая данному объекту, следовательно обновлять нечего

			RefreshView( node );
		}

		#endregion

		#region Event Handlers

		private void OnAfterNodeSelect(object sender, TreeViewEventArgs e)
		{
			if(e.Node == null)
				return;

			EntityItem entityItem = e.Node.Tag as EntityItem;

			if ( entityItem != null)
			{
				selectedRefObject = entityItem.subObject;
				LinkedPropertiesEditor.SelectedObject = entityItem.subObject;
			}		
		}

		//загружены ли данные в указанную ноду
		private bool IsDataLoaded(TreeNode _root)
		{
			return _root.FirstNode == null || _root.FirstNode.FirstNode == null || _root.FirstNode.FirstNode.Text != PLACEHOLDER;
		}

		private void LoadDataFor( TreeNode root )
		{
			if ( IsDataLoaded( root ) )
				return;

			treeView.BeginUpdate();

			foreach ( TreeNode node in root.Nodes )
			{
				node.Nodes.Clear();

				EntityItem entityItem = node.Tag as EntityItem;

				if ( entityItem == null )
					continue;

				if ( entityItem.subObject is IList && ( (IList)entityItem.subObject ).Count > MAX_LIST_SIZE )
					continue;

				node.Nodes.AddRange( BuildPropertiesNodes( entityItem.subObject, entityItem ) );

				TreeNodeState nodeState = treeView.StateContainer.GetNodeState( node.FullPath );

				if ( nodeState != null )
				{
					if ( nodeState.Expanded )
						node.Expand();
					else
						node.Collapse();
				}
				else if ( entityItem.expanded == PropertyPresetConfig.OutlinerExpandState.Expand ||
									entityItem.expanded == PropertyPresetConfig.OutlinerExpandState.ListExpand )
				{
					node.Expand();
				}
			}

			treeView.EndUpdate();
		}

		private void OnBeforeNodeExpand(object sender, TreeViewCancelEventArgs e)
		{
			LoadDataFor(e.Node);
		}

		private void OnAfterNodeExpand( object sender, TreeViewEventArgs e )
		{
			treeView.StateContainer.SaveNodeState( e.Node );
		}

		private void OnAfterNodeCollapse( object sender, TreeViewEventArgs e )
		{
			treeView.StateContainer.SaveNodeState( e.Node );
		}

		private void OnNodeMouseClick(object sender, MouseEventArgs e)
		{
			if (e.Button == MouseButtons.Right)
			{
				TreeNode node = treeView.GetNodeAt(e.X, e.Y);

				if (node == null)
					return;

				ContextMenu menu = CreateContextMenu(node.Tag as EntityItem);

				menu.MenuItems.Add("-");
				menu.MenuItems.Add(new MenuItem("Collapse All", (_sender, _args) => node.Collapse(false)));

				menu.Show(this, e.Location);
			}
		}

		protected override void OnVisibleChanged( EventArgs e )
		{
			base.OnVisibleChanged( e );
			RefreshView();//TODO это возникает и при свертывании/развертывании окна
		}

		#endregion

		#region Private Members

		//обновляет outliner, перестраивая всю иерархию от указанной ноды
		private void RefreshView( TreeNode node )
		{
			//в outliner не загружена нода, соответствующая данному объекту, следовательно обновлять нечего
			if ( node == null )
				return;

			EntityItem entityItem = node.Tag as EntityItem;

			if ( entityItem == null )
				return;

			treeView.BeginUpdate();

			treeView.StateContainer.SaveScrollPos();
			
			node.Nodes.Clear();
			node.Nodes.AddRange(BuildPropertiesNodes( entityItem.subObject, entityItem ));

			LoadDataFor(node);
      
			if ( selectedRefObject != null )
				treeView.SelectedNode = FindNodeByObject( node.Nodes, selectedRefObject );

			treeView.StateContainer.RestoreScrollPos();

			treeView.EndUpdate();
		}

		private void BuildRootNode()
		{
			if (selectedObject == null)
			{
				treeView.Nodes.Clear();
				return;
			}

			string name = string.Empty;
			if (selectedObject is DBResource)
				name = ((DBResource)selectedObject).DBId.Name;

			int imageIndex = application.Application.Extensions.GetTypeIconIndex(selectedObject.GetType(), true);

			EntityItem rootEntity = new EntityItem(selectedObject, name, null, 0, PropertyPresetConfig.OutlinerExpandState.NA, null);

			var rootNode = new ImprovedTreeNode
			{
				Text = name,
				AdditionalText = selectedObject.GetType().Name,
				Checkable = false,
				Tag = rootEntity,
				ImageIndex = imageIndex,
				SelectedImageIndex = imageIndex
			};

			treeView.BeginUpdate();
			treeView.Nodes.Clear();
			treeView.Nodes.Add(rootNode);
			rootNode.Nodes.AddRange(BuildPropertiesNodes(selectedObject, rootEntity));
			treeView.EndUpdate();

			rootNode.Expand();
		}

		private ImprovedTreeNode[] BuildPropertiesNodes( object _obj, EntityItem _parentEntityItem )
		{
			var result = new List<ImprovedTreeNode>();

			EntityCollector collector = EntityCollector.Create( _obj, _parentEntityItem, SelectedPreset );

			foreach ( EntityItem item in collector.GetCollectedItems() )
			{
				ImprovedTreeNode node = null;

				if ( IsLooped( item ) )
				{
					node = new ImprovedTreeNode
					{
						Text = "LOOP",
						AdditionalText = "it's error",
						Checkable = false
					};

					Log.TraceWarning( "Loop reference detected in \"{0}\"", item.dbId );
				}
				else
				{
					node = CreateNode( item );
				}

				if ( node != null )
					result.Add( node );
			}

			return result.ToArray();
		}

		private bool IsLooped(EntityItem _item)
		{
			EntityItem iter = _item.parent;

			while ( iter != null )
			{
				if ( iter.subObject == _item.subObject )
				{
					return true;
				}

				iter = iter.parent;
			}

			return false;
		}

		private ImprovedTreeNode CreateNode(EntityItem entityItem)
		{
			bool isIndexed = false;
			string nodeText = string.Empty;
			string nodeAdditionalText = string.Empty;

      if (TypeUtils.IsList(entityItem.field.FieldType))
			{
				isIndexed = true;
				if (entityItem.subObject is IList)
					nodeAdditionalText = string.Format("{0} items", ((IList) entityItem.subObject).Count);
			}

      if( entityItem.subObject is DBResource )
      {
        nodeText = entityItem.name;
        DBResource res = (DBResource)entityItem.subObject;
        Type resType = res.GetType();

      	if ( TypeUtils.HasAttribute<IndexFieldAttribute>( resType, true ) )
				{
					string caption = GetCaption( res );

					if ( !string.IsNullOrEmpty( caption ) )
						nodeText = caption;
				}

      	if(isIndexed)
					nodeText = string.Format( "[{0}] {1}", entityItem.sortIndex, nodeText );

        nodeAdditionalText = resType.Name + ", ";
				nodeAdditionalText += res.DBId.IsInlined ? "Inlined" : res.DBId.Name;
      }
      else if(entityItem.subObject != null)
			{
				Type resType = entityItem.subObject.GetType();

				if ( !isIndexed || !TypeUtils.IsList( resType ) )
				{
					if (isIndexed)
						nodeText = string.Format("[{0}] ", entityItem.sortIndex);

					nodeAdditionalText = resType.Name;
				}

				if(isIndexed && TypeUtils.HasAttribute<IndexFieldAttribute>(resType, true))
					nodeText += GetCaption(entityItem.subObject);
				else
					nodeText += entityItem.name;
			}
      else
      {
        return null;
      }

      int imageIndex = application.Application.Extensions.GetTypeIconIndex( entityItem.subObject.GetType(), true );
      
			var result = new ImprovedTreeNode
      {
        Text = nodeText,
        AdditionalText = nodeAdditionalText,
        Checkable = false,
        Tag = entityItem,
        ImageIndex = imageIndex,
        SelectedImageIndex = imageIndex
      };

			//наличие этой ноды идентифицирует о том, что у нас еще не подгружена ветвь
			result.Nodes.Add(PLACEHOLDER);

			return result;
		}

		private static string GetCaption(object _obj)
		{
			object nameValue = _obj;

			while ( nameValue != null )
			{
				Type nameValueType = nameValue.GetType();

				DBPtrBase ptrNameValue = nameValue as DBPtrBase;
				if ( ptrNameValue != null )
				{
					nameValue = ptrNameValue.Get<DBResource>();
					if ( nameValue == null )
						break;
					nameValueType = nameValue.GetType();
				}

				IndexFieldAttribute indexFieldAttr = TypeUtils.GetAttribute<IndexFieldAttribute>( nameValueType, true );
				if ( indexFieldAttr == null )
					break;

				DBFieldInfo field = TypeUtils.GetField( nameValueType, indexFieldAttr.FieldName, true );
				if ( field == null )
					break;

				nameValue = field.GetValue( nameValue );
			}

			return ( nameValue == null ) ? _obj.ToString() : nameValue.ToString();
		}

		private ContextMenu CreateContextMenu(EntityItem _entity)
		{
			if (_entity == null)
				return new ContextMenu();

			DBResource owner = selectedObject as DBResource;

			EntityItem node = _entity;

			while (node != null)
			{
				if (node.subObject is DBResource)
				{
					owner = (DBResource)node.subObject;
					break;
				}
				node = node.parent;
			}

			ContextMenu menu = application.ContextMenu.CreateContextMenu(_entity.subObject, owner);

			if (node != null && node.subObject is DBResource)
			{
				if (application.Application.Extensions.GetEditorsCount(node.subObject.GetType()) > 0)
				{
					menu.MenuItems.Add("-");
					MenuItem itemMenu = new MenuItem("Edit Referred Object", RunEditorForInlined);
					itemMenu.Tag = node.subObject;
					menu.MenuItems.Add(itemMenu);
				}
			}

			return menu;
		}

		private void RunEditorForInlined(object sender, EventArgs e)
		{
			MenuItem menuItem = sender as MenuItem;

			if (menuItem == null)
				return;

			DBResource resource = menuItem.Tag as DBResource;

			if (resource != null)
			{
				application.Application.Extensions.OpenEditor(resource.DBId, application, null, false);
			}
		}

		#endregion

		#region Nested Types

		private class EntityItem
    {
      public readonly string name = string.Empty;
			public readonly object subObject = null;
			public readonly DBFieldInfo field = null;
			public readonly PropertyPresetConfig.OutlinerExpandState expanded = PropertyPresetConfig.OutlinerExpandState.NA;
			public readonly int sortIndex = -1;
			public readonly EntityItem parent;
			public readonly DBID dbId;

			public EntityItem(object _obj, string _name, DBFieldInfo _field, int _index, PropertyPresetConfig.OutlinerExpandState _expanded, EntityItem _parent)
      {
        subObject = _obj;
        name = _name;
        field = _field;
      	sortIndex = _index;
				expanded = _expanded;
				parent = _parent;

				if (_obj is DBResource)
					dbId = ((DBResource) _obj).DBId;
      }
    }

		private class EntityCollector
		{
      private readonly List<EntityItem> items = new List<EntityItem>();
      private readonly List<PropertyPresetConfig.FieldControlItem> typePreset;
			private readonly PropertyPresetConfig.PresetConfigItem allPresets;
      private readonly bool needSorting = false;
			private readonly EntityItem parent;
			private int curIndex = 0;

      public static EntityCollector Create( object _parentObject, EntityItem _parentItem, PropertyPresetConfig.PresetConfigItem _preset )
      {
        FieldsWalker.DepthController depthController = new FieldsWalker.DepthController( 0, FieldsWalker.ObjectType.All, FieldsWalker.ObjectType.All );

        List<PropertyPresetConfig.FieldControlItem> typePreset = new List<PropertyPresetConfig.FieldControlItem>();

        if( _preset != null && _preset.fieldSets.ContainsKey( _parentObject.GetType().Name ) )
          typePreset = _preset.fieldSets[_parentObject.GetType().Name];

        EntityCollector result = new EntityCollector( typePreset, _parentItem, _preset );

        FieldsWalker.VisitFields( _parentObject, _parentItem.field, result.Functor, depthController.Functor );
				
        return result;
      }

			private EntityCollector(List<PropertyPresetConfig.FieldControlItem> _typePreset, EntityItem _parent, PropertyPresetConfig.PresetConfigItem _allPresets)
			{
				typePreset = _typePreset ?? new List<PropertyPresetConfig.FieldControlItem>();
				needSorting = typePreset.Count > 0;
				parent = _parent;
				allPresets = _allPresets;
			}

			public IEnumerable<EntityItem> GetCollectedItems()
			{
				if(needSorting)
					items.Sort((x, y) => x.sortIndex.CompareTo(y.sortIndex));
				
				return items;
			}

			private static bool ShouldSkipType(Type type)
			{
				return type == typeof(SrcFile);
			}

			private bool TryGetItem(object _obj, DBFieldInfo _field, int _idx, out EntityItem _result)
			{
				PropertyPresetConfig.FieldControlItem presetItem = null;
				_result = null;

				int index = 0;

				if (typePreset.Count <= 0)
				{
					index = _idx;
				}
				else
				{
					while (index < typePreset.Count)
					{
						if (typePreset[index].name == _field.Name)
						{
							presetItem = typePreset[index];
							break;
						}

						index++;
					}
				}

				if(presetItem == null || presetItem.visible)
				{
					var expanded = GetExpandState(presetItem);

					if (_obj is DBPtrBase)
					{
						DBResource res = ((DBPtrBase)_obj).Get<DBResource>();
						if (res != null)
							_result = new EntityItem(res, _field.Name, _field, index, expanded, parent);
					}
					else if (!TypeUtils.IsSimpleType(_obj.GetType()))
					{
						_result = new EntityItem(_obj, _field.Name, _field, index, expanded, parent);
					}					
				}

				return (_result != null);
			}

			private PropertyPresetConfig.OutlinerExpandState GetExpandState(PropertyPresetConfig.FieldControlItem _presetItem)
			{
				if ( parent != null )
				{
					if ( parent.expanded == PropertyPresetConfig.OutlinerExpandState.ListExpand )
						return PropertyPresetConfig.OutlinerExpandState.Collapse;

					if ( parent.field != null && TypeUtils.IsList( parent.field.FieldType ) &&
						TypeUtils.IsList( parent.subObject.GetType() ) &&
						parent.expanded == PropertyPresetConfig.OutlinerExpandState.Expand )
						return PropertyPresetConfig.OutlinerExpandState.Expand;		
				}

				if(_presetItem != null)
					return _presetItem.expandInOutliner;

				return PropertyPresetConfig.OutlinerExpandState.NA;
			}

			private bool Functor(ref object _obj, DBFieldInfo _field)
			{
				if (_obj == null)
					return true;

				if (ShouldSkipType(_obj.GetType()))
					return true;

				if (_field.IsDefined(typeof(HideInOutlinerAttribute), true))
					return true;

				if(!HasVisibleProperties(_field))
					return true;

				EntityItem result;

				if(TryGetItem(_obj, _field, curIndex++, out result))
					items.Add(result);


				return true;
			}

			private bool HasVisibleProperties( DBFieldInfo _field )
			{
				if ( allPresets != null && _field != null )
				{
					string fieldName = _field.FieldType.Name;

					if(allPresets.fieldSets.ContainsKey( fieldName ))
					{
						foreach ( PropertyPresetConfig.FieldControlItem fcItem in allPresets.fieldSets[fieldName] )
						{
							if (fcItem.visible)
								return true;
						}

						return false;	
					}
				}
				return true;
			}
		}

		#endregion
	}
}
