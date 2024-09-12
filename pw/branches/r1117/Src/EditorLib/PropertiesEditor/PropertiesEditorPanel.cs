using System;
using System.Collections;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using EditorLib.FieldProcessor;
using EditorLib.Panels;
using EditorLib.PropertiesEditor.PropertyPresets;
using libdb;
using libdb.DB;
using libdb.Diagnostics;
using WeifenLuo.WinFormsUI.Docking;

namespace EditorLib.PropertiesEditor
{
	public partial class PropertiesEditorPanel : EditorPanel
	{
		private PropertyPresetConfig config;
		private bool isPrimary = false;
		private bool lockSelection = false;

		#region Initialization.

		public PropertiesEditorPanel()
		{
			InitializeComponent();

			propertiesEditorControl.GridItemClick += propertiesEditorControl_GridItemClick;
			propertiesEditorControl.ShortcutPressed += propertiesEditorControl_ShortcutPressed;
		}

		public PropertiesEditorPanel(object selectedObject, IEditorWinApplication application)
			: this()
		{
			this.application = application;
			application.Panels.Add( this, DockState.Float );

			InitializePropertyEditor();
			SelectedObject = selectedObject;
		}

		private void InitializePropertyEditor()
		{     
			tsbOutlinerColours.Checked = application.Application.Settings.Get<PropertiesEditorConfig>().IsOutlinerColored;
      toolStripButtonShowOutliner.Checked = application.Application.Settings.Get<PropertiesEditorConfig>().showOutliner;

			improvedOutliner1.Initialize(application);
			improvedOutliner1.EnableColoring = tsbOutlinerColours.Checked;

			// Populate Configuration Selector
			config = application.Application.Settings.Get<PropertyPresetConfig>();
			PopulatePresetCombo();

			propertiesEditorControl.Initialize( application );
		}

		protected override bool Initialize(IEditorWinApplication application)
		{
			InitializePropertyEditor();

			isPrimary = true;
			EnablePinButton = isPrimary;
			SelectConfiguration.Enabled = isPrimary;

      DataBase.ChangeDBResourceEvent += OnDbResourceChanged;

			float outlinerPanelSize = application.Application.Settings.Get<PropertiesEditorConfig>().outlinerRelSize;
			if ( outlinerPanelSize > 0.0f )
				splitContainer1.SplitterDistance = (int) (outlinerPanelSize * Width);


			splitContainer1.Panel1Collapsed = !toolStripButtonShowOutliner.Checked;

			if ( splitContainer1.Panel1Collapsed )
			{
				splitContainer1.Panel1.Controls.Remove( propertyPanelToolStrip );
				splitContainer1.Panel2.Controls.Add( propertyPanelToolStrip );
			}


			return true;
		}

    public override void Terminate( IEditorWinApplication application )
    {
      base.Terminate( application );
      DataBase.ChangeDBResourceEvent -= OnDbResourceChanged;
    }

		#endregion

		#region Event handlers.

		private void propertiesEditorControl_GridItemClick(object sender, MouseEventArgs e)
		{
			if ( e.Button != MouseButtons.Right )
				return;

			object selectedObject = propertiesEditorControl.SelectedObject;
			
			if ( selectedObject is FullTypeDescriptorWrapper )
				selectedObject = ( (FullTypeDescriptorWrapper)selectedObject ).GetPropertyOwner( null );
			
			GridItem selectedItem = propertiesEditorControl.SelectedGridItem;

			if ( application == null || selectedObject == null || selectedItem == null ||
			     selectedItem.PropertyDescriptor == null || selectedItem.Value == null )
				return;

			ContextMenu menu = application.ContextMenu.CreateContextMenu( selectedItem.Value, selectedObject as DBResource );
			if ( menu.MenuItems.Count > 0 )
				menu.MenuItems.Add( "-" );

			var inlineItems = propertiesEditorControl.GetInlineMenuItemsForSelectedField();
			if ( inlineItems != null )
				menu.MenuItems.Add( "Create inlined" ).MenuItems.AddRange( inlineItems );

			CreateResetMenu( menu, selectedItem, selectedObject );

			MenuItem itemMenu = new MenuItem( "Copy", OnCopyClick, Shortcut.CtrlC );
			menu.MenuItems.Add( itemMenu );

			itemMenu = new MenuItem( "Paste", OnPasteClick, Shortcut.CtrlV );
			menu.MenuItems.Add( itemMenu );
			
			itemMenu.Enabled = CanBePasted();

			if ( selectedItem.PropertyDescriptor.PropertyType.IsSubclassOf( typeof (DBPtrBase) ) )
			{
				DBResource res = ((DBPtrBase)selectedItem.Value).Get<DBResource>();
				if ( res != null && application.Application.Extensions.GetEditorsCount( res.GetType() ) > 0 )
				{
					menu.MenuItems.Add( "-" );
					itemMenu = new MenuItem( "Edit Referred Object", RunEditorForInlined ) {Tag = res};
					menu.MenuItems.Add( itemMenu );
				}
			}

			PropertyPresetConfig configSet = application.Application.Settings.Get<PropertyPresetConfig>();

			if ( configSet.selectedPreset >= 0 )
			{
				menu.MenuItems.Add( "-" );
				if ( selectedItem.PropertyDescriptor.PropertyType.IsEnum )
				{
					itemMenu = new MenuItem( "Configure Enum " + selectedItem.PropertyDescriptor.PropertyType.Name, ConfigureEnumSet );
					itemMenu.Tag = selectedItem.PropertyDescriptor.PropertyType;
					menu.MenuItems.Add( itemMenu );
				}
				var cyclingItem = selectedItem;
				if ( !cyclingItem.Expandable || (cyclingItem.Value is IEnumerable) )
					cyclingItem = cyclingItem.Parent;

				do
				{
					if ( cyclingItem.Value is IEnumerable )
					{
						cyclingItem = cyclingItem.Parent;
						continue;
					}
					else if ( cyclingItem.Value is DBPtrBase )
					{
						DBPtrBase selectedDBPtr = cyclingItem.Value as DBPtrBase;
						DBResource res = selectedDBPtr.Get<DBResource>();
						if ( res == null )
						{
							cyclingItem = cyclingItem.Parent;
							continue;
						}
						itemMenu = new MenuItem( "Configure " + res.GetType().Name, ConfigurePropertySet );
						itemMenu.Tag = res.GetType();
					}
					else if ( cyclingItem.Value is FullTypeDescriptorWrapper )
					{
						FullTypeDescriptorWrapper item = cyclingItem.Value as FullTypeDescriptorWrapper;
						itemMenu = new MenuItem( "Configure " + item.GetPropertyOwner().GetType().Name, ConfigurePropertySet );
						itemMenu.Tag = item.GetPropertyOwner().GetType();
					}
					else
					{
						itemMenu = new MenuItem( "Configure " + cyclingItem.Value.GetType().Name, ConfigurePropertySet );
						itemMenu.Tag = cyclingItem.Value.GetType();
					}
					menu.MenuItems.Add( itemMenu );

					cyclingItem = cyclingItem.Parent;
				} while ( cyclingItem != null );
			}

			menu.Show( this, new Point( e.X + splitContainer1.Panel1.Width, e.Y + splitContainer1.Location.Y ) );
		}

		private void propertiesEditorControl_ShortcutPressed( object sender, PropertiesEditorControl.ShortcutEventArgs e )
		{
			switch (e.Shortcut)
			{
				case Shortcut.CtrlC:
					Copy();
					break;

				case Shortcut.CtrlV:
						Paste();
						break;

				case Shortcut.CtrlR:

						object selectedObject = propertiesEditorControl.SelectedObject;

						if ( selectedObject is FullTypeDescriptorWrapper )
							selectedObject = ( (FullTypeDescriptorWrapper)selectedObject ).GetPropertyOwner( null );

						GridItem selectedItem = propertiesEditorControl.SelectedGridItem;

						if ( application == null || selectedObject == null || selectedItem == null ||
								 selectedItem.PropertyDescriptor == null || selectedItem.Value == null )
							return;

						Reset(GetResetInfo(selectedItem, selectedObject));
						break;
			}
		}

		private void CreateResetMenu(ContextMenu menu, GridItem selectedItem, object selectedObject)
		{
			ResetInfo info = GetResetInfo(selectedItem, selectedObject);

			if (info == null) return;

			MenuItem itemMenu = new MenuItem( "Reset", ResetPropertyValue, Shortcut.CtrlR );
			itemMenu.Tag = info;
			menu.MenuItems.Add( itemMenu );
			menu.MenuItems.Add( "-" );
		}

		private object GetPropertyOwner( GridItem selectedItem, object selectedObject )
		{
			object propertyOwner = selectedObject;

			if ( selectedItem.Parent != null )
				propertyOwner = selectedItem.Parent.Value;

			if ( propertyOwner is FullTypeDescriptorWrapper )
				propertyOwner = ( (FullTypeDescriptorWrapper)propertyOwner ).GetPropertyOwner();

			if ( propertyOwner is DBPtrBase )
				propertyOwner = ( (DBPtrBase)propertyOwner ).Get<DBResource>();

			return propertyOwner;
		}

		private ResetInfo GetResetInfo( GridItem selectedItem, object selectedObject )
		{
			object propertyOwner = GetPropertyOwner(selectedItem, selectedObject);

			ResetInfo info = new ResetInfo();

			if ( propertyOwner is IRichList )
			{
				info.ownerList = (IRichList)propertyOwner;

				if ((selectedItem.PropertyDescriptor is ListElementDescriptor))
				{
					info.index = ((ListElementDescriptor) selectedItem.PropertyDescriptor).Index;

					if (!info.ownerList.IsElementDerivedFromParent(info.index))
						return info;
				}
			}
			else if (propertyOwner is ICompositeDBValue)
			{
				info.ownerStruct = (ICompositeDBValue) propertyOwner;
				info.fieldName = selectedItem.PropertyDescriptor.Name;

				if (!info.ownerStruct.IsFieldDerivedFromParent(info.fieldName))
					return info;
			}

			return null;
		}

		private void ResetPropertyValue(object sender, EventArgs e)
		{
			if (sender is MenuItem)
			{
				MenuItem item = sender as MenuItem;
				Reset(item.Tag as ResetInfo);
			}
		}

		private void Reset( ResetInfo _resetInfo )
		{		
			if ( _resetInfo == null )
				return;

			if ( _resetInfo.ownerList != null && _resetInfo.index != -1 )
			{
				_resetInfo.ownerList.ResetElement( _resetInfo.index );
			}
			else if ( _resetInfo.ownerStruct != null && _resetInfo.fieldName.Length > 0 )
			{
				_resetInfo.ownerStruct.ResetField( _resetInfo.fieldName );
			}

			RefreshView( true );
		}

		private void RunEditorForInlined(object sender, EventArgs e)
		{
			if ( !(sender is MenuItem) )
				return;
			MenuItem item = sender as MenuItem;
			application.Application.Extensions.OpenEditor( (item.Tag as DBResource).DBId, application, null, false );
		}

		private void ConfigureEnumSet(object sender, EventArgs e)
		{
			if ( !(sender is MenuItem) )
				return;
			MenuItem item = sender as MenuItem;
			EditorConfigEditForm form = new EditorConfigEditForm( application, item.Tag as Type );
			form.ShowDialog();
		}

		private void ConfigurePropertySet(object sender, EventArgs e)
		{
			if ( !(sender is MenuItem) )
				return;
			MenuItem item = sender as MenuItem;
			EditorConfigEditForm form = new EditorConfigEditForm( application, item.Tag as Type );
			if ( form.ShowDialog() == DialogResult.OK )
			{
				improvedOutliner1.SelectedPreset = config.configPresets[config.selectedPreset];
				RefreshView( true );
			}
		}

		private void OnCopyClick(object sender, EventArgs e)
		{
			Copy();
		}

		private void OnPasteClick( object sender, EventArgs e )
		{
			Paste();
		}

		private void Copy()
		{
			if(propertiesEditorControl.SelectedGridItem == null) 
				return;

			H6Clipboard.Copy( propertiesEditorControl.SelectedGridItem.Value );
		}

		private void Paste()
		{
			if ( CanBePasted() )
			{
				object srcItem = H6Clipboard.CopiedObjects[0];
				GridItem dstGridItem = propertiesEditorControl.SelectedGridItem;

				if(srcItem.GetType() != dstGridItem.Value.GetType())
				{
					Log.TraceWarning( "Can't copy various types objects" );
					return;
				}

				if ( srcItem.GetType().IsValueType || srcItem is string )//value types & strings
				{
					object parent = dstGridItem.Parent.Value;
					Log.Assert(parent != null);

					if ( parent is FullTypeDescriptorWrapper )
						parent = ( (FullTypeDescriptorWrapper)parent ).GetPropertyOwner();

					if(!dstGridItem.PropertyDescriptor.IsReadOnly)
						dstGridItem.PropertyDescriptor.SetValue(parent, srcItem);
					else
						Log.TraceWarning("Can't copy readonly field");
				}
				else//reference types
				{				
					List<Attribute> attributes = new List<Attribute>();

					foreach(Attribute item in dstGridItem.PropertyDescriptor.Attributes)
					{
						attributes.Add(item);
					}

					PropertiesEditorCopy.Copy(dstGridItem.Value, srcItem, attributes);
				}

				propertiesEditorControl.Refresh();
			}
		}

		private static bool CanBePasted()
		{
			return H6Clipboard.CopiedObjects.Length > 0;
		}

    public void SelectProperty( string _propertyName )
    {
      propertiesEditorControl.SelectProperty( _propertyName );
    }

		private void OnChangeDBResourceEvent(DBID dbid)
		{
			if ( IsHandleCreated )
				propertiesEditorControl.Refresh();
		}

		private void PopulatePresetCombo()
		{
			SelectConfiguration.Items.Clear();

			foreach (PropertyPresetConfig.PresetConfigItem presetItem in config.configPresets)
			{
				if ( presetItem.name == null )
					presetItem.name = "Unnamed Preset";
				SelectConfiguration.Items.Add( presetItem.name );
			}
			SelectConfiguration.Items.Add( "Manager..." );
			if ( config.selectedPreset >= 0 && config.selectedPreset < config.configPresets.Count )
				SelectConfiguration.SelectedIndex = config.selectedPreset;
			else
				SelectConfiguration.SelectedItem = null;
		}

		private void SelectConfiguration_SelectedIndexChanged(object sender, EventArgs e)
		{
			if ( SelectConfiguration.SelectedIndex == SelectConfiguration.Items.Count - 1 )
			{
				// Run Configuration Manager
				PresetConfigManager dialogPresets = new PresetConfigManager( application );
				dialogPresets.ShowDialog();
				PopulatePresetCombo();
			}
			else
			{
				config.selectedPreset = SelectConfiguration.SelectedIndex;

				improvedOutliner1.SelectedPreset = config.configPresets[config.selectedPreset];

				RefreshView( true );
			}
		}

		private class ResetInfo
		{
			public string fieldName = string.Empty;
			public int index = -1;
			public IRichList ownerList = null;
			public ICompositeDBValue ownerStruct = null;
		}

		#endregion

		#region Overrides.

		protected override string GetPersistString()
		{
			if ( isPrimary )
				return GetType().ToString();
			else
			{
				if ( propertiesEditorControl.SelectedObject is DBResource )
					return GetType().ToString() + ":" + (propertiesEditorControl.SelectedObject as DBResource).DBId.Name;
			}
			return "";
		}

		#endregion

		#region Public methods and properties.

		public bool EnablePinButton
		{
			get { return PinProperties.Enabled; }
			set { PinProperties.Enabled = value; }
		}

		public object SelectedObject
		{
			get { return propertiesEditorControl.SelectedObject; }
			set
			{
				if ( lockSelection )
					return;

				if ( value == null )
				{
					propertiesEditorControl.SelectedObject = null;
					improvedOutliner1.SelectedObject = null;
					nameLabel.Text = "No object selected";
				}
				else
				{
					if ( value is DBResource )
						nameLabel.Text = string.Format( "{0} ({1})", (value as DBResource).DBId.Name, value.GetType().Name );
					else
					{
						string objectName = "???";
						IndexFieldAttribute indexFieldAttr = TypeUtils.GetAttribute<IndexFieldAttribute>( value.GetType(), true );
						if ( indexFieldAttr != null )
						{
							DBFieldInfo field = TypeUtils.GetField( value.GetType(), indexFieldAttr.FieldName, true );
							if ( field != null && field.GetValue( value ) != null )
							{
								objectName = field.GetValue( value ).ToString();
							}
						}

					  nameLabel.Text = objectName + string.Format( " ({0})", value.GetType().Name );
					}
					propertiesEditorControl.SelectedObject = value;
					improvedOutliner1.SelectedObject = value;
				}
			}
		}

		public void RefreshView( bool select )
		{
			propertiesEditorControl.RefreshView( select );
			if ( select )
			{
				improvedOutliner1.RefreshView();
			}
		}

		#endregion

		#region Private helper methods.

	  private void OnDbResourceChanged(DBID dbid)
	  {
      if ( IsHandleCreated )
        Invoke( new DataBase.ChangeDBResourceEventHandler( OnChangeDBResourceEvent ), new object[] { dbid } );
	  }

	  #endregion

		private void nameLabel_MouseClick( object sender, MouseEventArgs e )
		{
			if ( e.Button != MouseButtons.Right )
			{
				return;
			}
			object selectedObject = SelectedObject;
			if ( selectedObject is FullTypeDescriptorWrapper )
				selectedObject = (selectedObject as FullTypeDescriptorWrapper).GetPropertyOwner( null );
			if ( application != null && selectedObject != null )
			{
				ContextMenu menu = application.ContextMenu.CreateContextMenu( selectedObject, selectedObject as DBResource );

				PropertyPresetConfig configSet = application.Application.Settings.Get<PropertyPresetConfig>();
				if ( configSet.selectedPreset >= 0 )
				{
					if ( menu.MenuItems.Count > 0 )
						menu.MenuItems.Add( "-" );
					MenuItem itemMenu = new MenuItem( "Configure " + selectedObject.GetType().Name, ConfigurePropertySet );
					itemMenu.Tag = selectedObject.GetType();
					menu.MenuItems.Add( itemMenu );
				}

				menu.Show( this, new Point( e.X, e.Y ) );
			}
		}

		private void PinProperties_Click(object sender, EventArgs e)
		{
			if ( application != null && SelectedObject != null )
			{
				new PropertiesEditorPanel( SelectedObject, application );
			}
		}

		private void toolStripButtonShowOutliner_CheckStateChanged(object sender, EventArgs e)
		{
			splitContainer1.Panel1Collapsed = !toolStripButtonShowOutliner.Checked;
			application.Application.Settings.Get<PropertiesEditorConfig>().showOutliner = toolStripButtonShowOutliner.Checked;

			if ( splitContainer1.Panel1Collapsed )
			{
				splitContainer1.Panel1.Controls.Remove( propertyPanelToolStrip );
				splitContainer1.Panel2.Controls.Add( propertyPanelToolStrip );
			}
			else
			{
				splitContainer1.Panel2.Controls.Remove( propertyPanelToolStrip );
				splitContainer1.Panel1.Controls.Add( propertyPanelToolStrip );
			}
		}

		private void splitContainer1_SplitterMoved(object sender, SplitterEventArgs e)
		{
			application.Application.Settings.Get<PropertiesEditorConfig>().outlinerRelSize = splitContainer1.SplitterDistance *
			                                                                                 1.0f / Width;
		}

		private void tsbLockSelection_CheckStateChanged(object sender, EventArgs e)
		{
			lockSelection = tsbLockSelection.Checked;
		}

    private void tsbOutlinerColours_CheckedChanged( object sender, EventArgs e )
    {
      application.Application.Settings.Get<PropertiesEditorConfig>().IsOutlinerColored = tsbOutlinerColours.Checked;
    	improvedOutliner1.EnableColoring = tsbOutlinerColours.Checked;
    }

    private void tsbOutlinerColours_MouseDown( object sender, MouseEventArgs e )
    {
      if ( e.Button != MouseButtons.Right )
        return;

      ContextMenu menu = new ContextMenu();

      menu.MenuItems.Add( "Edit Outliner colours...", OnEditOutlinerColours );
      Point p = e.Location;
      p.Offset( tsbOutlinerColours.Bounds.Location );
      menu.Show( this, p );
    }

    private void OnEditOutlinerColours( object sender, EventArgs e )
    {
      FastOutlinerColoursForm form = new FastOutlinerColoursForm( application );
      form.ShowDialog();
			improvedOutliner1.ApplyColorScheme();
    }

    public void ExpandOneLevel()
    {
      propertiesEditorControl.ExpandOneLevel();
    }
  }
}