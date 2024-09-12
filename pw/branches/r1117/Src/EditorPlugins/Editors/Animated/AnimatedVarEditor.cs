using System;
using System.ComponentModel;
using EditorLib.Extensions;
using EditorPlugins.Editors.AnimatedCurves;
using libdb.Animated;
using EditorLib.FieldProcessor;
using System.Drawing.Design;
using EditorLib;

namespace EditorPlugins.Editors.Animated
{
	[ApplicableForDeriver]
	public sealed class AnimatedVarEditor : TypedValueEditor<IAnimated>
	{
		public AnimatedVarEditor( IEditorWinApplication application ) : base( application ) { }

		protected override IAnimated EditValue( ITypeDescriptorContext context, object instance, IServiceProvider provider, IAnimated value )
		{
			new AnimatedEditorDialog( Application, value ).ShowDialog();
			return value;
		}

		public override bool IsDropDownResizable { get { return false; } }
		public override UITypeEditorEditStyle EditorEditStyle { get { return UITypeEditorEditStyle.Modal; } }
	}
}
