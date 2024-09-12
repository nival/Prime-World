using EditorLib;
using EditorLib.Extensions;
using EditorLib.FieldProcessor;
using libdb;

namespace EditorPlugins.Extensions
{
	[ApplicableForDeriver]
	public class RichListStringConverter : TypedStringConvertor<IRichList>
	{
		public RichListStringConverter( IEditorWinApplication application ) : base( application ) { }

		public override bool SuppressProperties
		{
			get { return false; }
		}

		protected override IRichList ConvertFromStringInternal( System.ComponentModel.ITypeDescriptorContext context, object instance, System.Globalization.CultureInfo culture, string value )
		{
			return null;
		}

		protected override string ConvertToString( System.ComponentModel.ITypeDescriptorContext context, object instance, System.Globalization.CultureInfo culture, IRichList value )
		{
			if ( value == null )
				return "{null}";

			return string.Format( "{0} element(s)", value.Count );
		}
	}

}
