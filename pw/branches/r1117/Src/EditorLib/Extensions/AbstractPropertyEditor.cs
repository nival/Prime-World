using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using libdb.DB;
using System.ComponentModel;
using System.Drawing.Design;

namespace EditorLib.Extensions
{
	public abstract class AbstractPropertyEditor : UITypeEditor
	{
		private IEditorWinApplication application = null;

		public override UITypeEditorEditStyle GetEditStyle( ITypeDescriptorContext context ) { return UITypeEditorEditStyle.Modal; }

		internal void SetApplication( IEditorWinApplication application ) { this.application = application; }
		protected IEditorWinApplication Application { get { return application; } }
	}

	public abstract class TypePropertyEditor<T> : AbstractPropertyEditor
	{
		public sealed override object EditValue( ITypeDescriptorContext context, IServiceProvider provider, object value )
		{
			string tempCurrentDirectory = Environment.CurrentDirectory;
			object result = OpenDialog( (T)value, context, provider, Application );
			Environment.CurrentDirectory = tempCurrentDirectory;
		
			return result;
		}

		protected abstract T OpenDialog( T value, ITypeDescriptorContext context, IServiceProvider provider, IEditorWinApplication application );
	}

	public abstract class AttributePropertyEditor<T, TAttribute> : AbstractPropertyEditor
		where TAttribute : Attribute
	{
		public sealed override object EditValue( ITypeDescriptorContext context, IServiceProvider provider, object value )
		{
			List<Attribute> attrs = new List<Attribute>();
			foreach ( Attribute attr in context.PropertyDescriptor.Attributes )
				attrs.Add( attr );
			attrs.AddRange( TypeUtils.GetAttributes<Attribute>( value.GetType(), true ) );

			foreach ( Attribute attr in attrs )
			{
				if ( attr.GetType() == typeof( TAttribute ) )
				{
					string tempCurrentDirectory = Environment.CurrentDirectory;
					object result = OpenDialog( (T)value, (TAttribute)attr, context, provider, Application );
					Environment.CurrentDirectory = tempCurrentDirectory;

					return result;
				}
			}

			return value;
		}

		protected abstract T OpenDialog( T value, TAttribute attribute, ITypeDescriptorContext context, IServiceProvider provider, IEditorWinApplication application );
	}

	public abstract class DBResourcePropertyEditor<T> : AbstractPropertyEditor
		where T : DBResource
	{
		public sealed override object EditValue( ITypeDescriptorContext context, IServiceProvider provider, object value )
		{
			T resource = value as T;

			string tempCurrentDirectory = Environment.CurrentDirectory;
			object result = OpenDialog( resource, context, provider, Application );
			Environment.CurrentDirectory = tempCurrentDirectory;
			
			return result;
		}

		protected abstract T OpenDialog( T value, ITypeDescriptorContext context, IServiceProvider provider, IEditorWinApplication application );
	}
}
