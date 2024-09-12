using System;
using System.ComponentModel;
using System.Drawing.Design;
using EditorLib.FieldProcessor;
using EditorPlugins.Editors.FileRef;
using libdb.DB;
using EditorLib;

namespace EditorPlugins.PropertiesEditor
{
  public sealed class FileRefEditor : TwoTypedValueEditor<string, FileRefAttribute>
	{
		public FileRefEditor( IEditorWinApplication application, Attribute attribute ) 
      : base( application, attribute ) { }

		public override bool IsDropDownResizable { get { return false; } }
		public override UITypeEditorEditStyle EditorEditStyle { get { return UITypeEditorEditStyle.Modal; } }

    protected override string EditValue( ITypeDescriptorContext context, object instance, IServiceProvider provider, string value )
    {
      return FileRefHelper.GetFile( instance, value, Attribute.filenameExtension );
    }
	}
}
