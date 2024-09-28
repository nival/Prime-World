using System.ComponentModel;
using System.Runtime.InteropServices;
using EditorLib.Extensions;
using EditorPlugins.Editors.TextRef;
using libdb.DB;
using System.Drawing.Design;
using System;
using System.Windows.Forms.Design;
using System.Windows.Forms;
using EditorLib;

namespace EditorPlugins.PropertiesEditor
{
	public class TextRefEditor : TypePropertyEditor<TextRef>
	{
		public override bool IsDropDownResizable { get { return true; } }
		public override UITypeEditorEditStyle GetEditStyle( ITypeDescriptorContext context ) { return UITypeEditorEditStyle.DropDown; }

		protected override TextRef OpenDialog( TextRef value, ITypeDescriptorContext context, IServiceProvider provider, IEditorWinApplication application )
		{
			IWindowsFormsEditorService formEditor = provider.GetService( typeof( IWindowsFormsEditorService ) ) as IWindowsFormsEditorService;
			formEditor.DropDownControl( new TextRefEditorControl( value ) );
			return value;
		}
	}
}
