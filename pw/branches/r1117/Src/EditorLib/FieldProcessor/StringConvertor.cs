using System;
using System.ComponentModel;
using System.Globalization;
using libdb.DB;

namespace EditorLib.FieldProcessor
{
  public interface IStringConvertor
  {
    /// <summary>
    /// This implementation of StringConvertor hides properties
    /// </summary>
    bool SuppressProperties { get; }

    /// <summary>
    /// Convert string to the type of this descriptor
    /// </summary>
    object ConvertFromString( ITypeDescriptorContext context, CultureInfo culture, string value );

    /// <summary>
    /// Convert context of type or field to string
    /// </summary>
    string ConvertToString( ITypeDescriptorContext context, CultureInfo culture, object value );

    IEditorWinApplication Application { get; }
  }

  public abstract class TypedStringConvertor<T> : IStringConvertor
  {
    private readonly IEditorWinApplication application = null;
    protected TypedStringConvertor( IEditorWinApplication application ) { this.application = application; }

    public IEditorWinApplication Application { get { return application; } }
    public abstract bool SuppressProperties { get; }

    protected abstract T ConvertFromStringInternal( ITypeDescriptorContext context, object instance, CultureInfo culture, string value );
    public object ConvertFromString( ITypeDescriptorContext context, CultureInfo culture, string value )
    {
      object instance = (context == null) ? null : FullTypePropertyDescriptor.GetInstanceFromContext(context);
      T result = ConvertFromStringInternal( context, instance, culture, value );
      return result;
    }

    protected abstract string ConvertToString( ITypeDescriptorContext context, object instance, CultureInfo culture, T value );
    public string ConvertToString( ITypeDescriptorContext context, CultureInfo culture, object value )
    {
			object instance = ( null == context ) ? null : FullTypePropertyDescriptor.GetInstanceFromContext( context );
      return ConvertToString( context, instance, culture, ( T )value );
    }
  }

  public abstract class TwoTypedStringConvertor<T, A> : IStringConvertor 
    where A : System.Attribute
  {
    private readonly IEditorWinApplication application = null;
    private readonly A attribute = null;
    protected A Attribute { get { return attribute; } }

    protected TwoTypedStringConvertor( IEditorWinApplication _application, Attribute _attribute )
    {
      this.application = _application;
      this.attribute = _attribute as A;
    }

    public IEditorWinApplication Application { get { return application; } }
    public abstract bool SuppressProperties { get; }

    protected abstract T ConvertFromStringInternal( ITypeDescriptorContext context, object instance, CultureInfo culture, string value );
    public object ConvertFromString( ITypeDescriptorContext context, CultureInfo culture, string value )
    {
      object instance = ( context == null ) ? null : FullTypePropertyDescriptor.GetInstanceFromContext( context );
      T result = ConvertFromStringInternal( context, instance, culture, value );
      return result;
    }

    protected abstract string ConvertToString( ITypeDescriptorContext context, object instance, CultureInfo culture, T value );
    public string ConvertToString( ITypeDescriptorContext context, CultureInfo culture, object value )
    {
      object instance = ( null == context ) ? null : FullTypePropertyDescriptor.GetInstanceFromContext( context );
      return ConvertToString( context, instance, culture, (T)value );
    }
  }
}
