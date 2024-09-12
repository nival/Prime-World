using System;
using System.ComponentModel;
using System.Drawing.Design;
using System.Windows.Forms.Design;
using EditorLib.Extensions;
using EditorLib.FieldProcessor;
using EditorLib.Settings;
using EditorPlugins.Editors.TextRef;
using libdb.DB;
using EditorLib;
using System.Windows.Forms;

namespace EditorPlugins.Extensions
{
	[ApplicableForDeriver]
	public sealed class TextRefEditor : TypedValueEditor<TextRef>
	{
		private IEditorWinApplication application;
		public TextRefEditor( IEditorWinApplication application ) : base( application ) 
		{
			this.application = application; 
		}
		public override bool IsDropDownResizable { get { return true; } }
		public override UITypeEditorEditStyle EditorEditStyle { get { return UITypeEditorEditStyle.Modal; } }

		protected override TextRef EditValue( ITypeDescriptorContext context, object instance, IServiceProvider provider, TextRef value )
		{
			IWindowsFormsEditorService formEditor = provider.GetService( typeof( IWindowsFormsEditorService ) ) as IWindowsFormsEditorService;
			
			foreach ( Form f in System.Windows.Forms.Application.OpenForms )
			{
				if ( ( f is TextRefEditorForm ) && object.ReferenceEquals( ( f as TextRefEditorForm ).Value, value ) )
				{
					f.Activate();
					if ( f.WindowState == FormWindowState.Minimized )
						f.WindowState = FormWindowState.Normal; 
					
					return value;
				}
			}
			TextRefEditorForm form = new TextRefEditorForm( value,application );
			form.Show( (IWin32Window)formEditor );
			return value;
		}
	}
}