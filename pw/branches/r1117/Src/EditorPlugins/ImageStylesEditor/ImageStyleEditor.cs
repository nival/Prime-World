using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using EditorLib.Extensions;
using DBTypes;
using libdb.DB;
using EditorLib;
using EditorLib.PropertiesEditor;

namespace EditorPlugins.ImageStylesEditor
{
	
	[EditorLib.Extensions.EditorAttribute( "Styles", true )]
  [ApplicableForDeriver]
	public partial class ImageStyleEditor : Editor<BaseUIMaterial>
	{
		protected override Control StatusPanel { get { return null; } }
		public ImageStyleEditor()
		{
			InitializeComponent();
		}
    protected override bool Initialize(DBPtr<BaseUIMaterial> style, IEditorWinApplication application)
		{
			imageSylesEditor.Initialize(style, application);
			return true;
		}

    protected override void OnClosed( EventArgs e )
    {
      imageSylesEditor.UnsubscribeFromEvent();
      base.OnClosed(e);
    }

    protected override void OnActivateEditor()
    {
      imageSylesEditor.Application.Panels.GetSingletonPanel<PropertiesEditorPanel>().SelectedObject = imageSylesEditor.SelectedStyle;
    }
  }
	 
}
