using System;
using System.ComponentModel;
using System.Drawing.Design;
using System.Globalization;
using System.Runtime.InteropServices; // DllImport
using System.Text;
using System.Threading;
using System.Windows.Forms;
using DBTypes;
using EditorLib;
using EditorLib.Extensions;
using EditorLib.FieldProcessor;
using libdb.DB;
using libdb.Diagnostics;

namespace PF_Editor.Extensions
{
	[ApplicableForDeriver]
	public class BaseExecutableStringExtension : TypedStringConvertor<BaseExecutableString>
	{
    [DllImport("FormulaBuilder.dll", CallingConvention = CallingConvention.StdCall)]
    public static extern int BuildFormula(string cpFormula, [MarshalAs(UnmanagedType.LPStr)] StringBuilder buf, int nMaxCount, string cpReturnType, int altSecond);

		public BaseExecutableStringExtension( IEditorWinApplication application ) : base( application ) { }

    public override bool SuppressProperties { get { return true; } }

		protected override BaseExecutableString ConvertFromStringInternal( ITypeDescriptorContext context, object instance, CultureInfo culture, string value )
    {
			int nSize = 4096 * 2;
			StringBuilder sb = new StringBuilder( nSize );
			BaseExecutableString estr = TypeUtils.CreateInstance( context.PropertyDescriptor.PropertyType ) as BaseExecutableString;

			if ( estr == null )
			{
				Log.TraceWarning( "Can't create formula importer for \"{0}\"", context.PropertyDescriptor.PropertyType );
				return null;
			}

      int altSecond = 0;
      string returnType = estr.returnType;
      if (returnType == "boolean")
      {
        altSecond = 1;
        returnType = "bool";
      }

      while (0 == BuildFormula(value, sb, sb.Capacity, returnType, altSecond))
			{
				nSize *= 2;
				sb = new StringBuilder( nSize );
			}
			estr.compiledString = sb.ToString();
			estr.sString = value;
			if ( estr.compiledString.Length > 0 )
			{
				Log.TraceMessage( "Formula importer \"{0}\" with string \"{1}\" succeeded.", this.GetType().ToString(), value );
			}
			else
			{
				Log.TraceError( "Formula importer \"{0}\" with string \"{1}\" failed.", this.GetType().ToString(), value );
			}
			return estr;
    }

		protected override string ConvertToString(ITypeDescriptorContext context, object instance, CultureInfo culture, BaseExecutableString value)
		{
      if ( value == null )
        return null;

			return value.sString;
		}
	}

	[ApplicableForDeriver]
	public sealed class BaseExecutableStringValueEditor : TypedValueEditor<BaseExecutableString>
	{
		public BaseExecutableStringValueEditor( IEditorWinApplication application )
			: base( application )
		{
		}

		public override bool IsDropDownResizable
		{
			get { return false; }
		}

		public override UITypeEditorEditStyle EditorEditStyle
		{
			get { return UITypeEditorEditStyle.Modal; }
		}

		protected override BaseExecutableString EditValue( ITypeDescriptorContext context, object instance, IServiceProvider provider, BaseExecutableString value )
		{
      if ( value == null )
        return null;

      BaseExecutableStringEditor editor = new BaseExecutableStringEditor(Application, value.sString);
			
			if(editor.ShowDialog() == DialogResult.OK)
			{
				BaseExecutableStringExtension ext = new BaseExecutableStringExtension(Application);
				BaseExecutableString result = (BaseExecutableString)ext.ConvertFromString( context, Thread.CurrentThread.CurrentCulture, editor.Formula );

				return result;
			}

			return value;
		}
	}
}
