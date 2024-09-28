using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using EditorLib.Panels;
using EditorLib;
using DBTypes;
using libdb.DB;
using EditorLib.Extensions;


namespace EditorPlugins.LayoutEditor
{
	public partial class LayoutPropertiesEditorPanel : EditorPanel
	{
		public LayoutPropertiesEditorPanel()
		{
			InitializeComponent();
		}
		protected override bool Initialize( IEditorWinApplication application )
		{
			return true;
		}
		
		public void RefreshView()
		{
			propertyGrid.Refresh();
		}

		internal Window[] SelectedObjects
		{
			get { return null; }
			set
			{
				if ( value != null )
				{
					List<LayoutPropertiesEditorObject> objs = new List<LayoutPropertiesEditorObject>();
					
					foreach( Window wnd in value )
					{
						if ( wnd.Layout != null )
						{
							objs.Add( new LayoutPropertiesEditorObject( wnd ) );
						}
					}
					propertyGrid.SelectedObjects = objs.ToArray();
				}
				else
					propertyGrid.SelectedObjects = null;
			}
		}
	}
}
