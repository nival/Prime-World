using System;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel;

namespace EditorLib.FieldProcessor
{
  public interface IStandardValuesProvider
  {
    /// <summary>
    /// Returns is type's or field's standard values are exclusive
    /// </summary>
    bool IsStandardValuesExclusive( ITypeDescriptorContext context );

    /// <summary>
    /// Returns list of available values for type or field
    /// </summary>
    TypeConverter.StandardValuesCollection GetStandardValues( ITypeDescriptorContext context );

    /// <summary>
    /// Returns is type of field has converter for standard values. GetStandardValuesType should return type of standard values
    /// </summary>
    bool HasStandardValuesConvertor( ITypeDescriptorContext context );

    /// <summary>
    /// Returns type of standard values. Used only if HasStandardValuesConvertor returns true
    /// </summary>
    Type GetStandardValuesType( ITypeDescriptorContext context );

    /// <summary>
    /// Convert standard value to the type for this descriptor
    /// </summary>
    object ConvertFromStandardValue( ITypeDescriptorContext context, object value );

    IEditorWinApplication Application { get; }
  }

  public abstract class TypedStandardValuesProvider<T> : IStandardValuesProvider
  {
    private IEditorWinApplication application = null;
    public IEditorWinApplication Application { get { return application; } }

    protected TypedStandardValuesProvider( IEditorWinApplication application ) { this.application = application; }

    public abstract bool IsStandardValuesExclusive( ITypeDescriptorContext context );
    public abstract TypeConverter.StandardValuesCollection GetStandardValues( ITypeDescriptorContext context );
    public abstract bool HasStandardValuesConvertor( ITypeDescriptorContext context );
    public abstract Type GetStandardValuesType( ITypeDescriptorContext context );

    protected abstract T ConvertFromStandardValueInternal( ITypeDescriptorContext context, object instance, object value );
    public object ConvertFromStandardValue( ITypeDescriptorContext context, object value )
    {
			object instance = ( null == context ) ? null : FullTypePropertyDescriptor.GetInstanceFromContext( context );
      return ConvertFromStandardValueInternal( context, instance, value );
    }
  }

  public abstract class TwoTypedStandardValuesProvider<T, A> : IStandardValuesProvider where A : Attribute
  {
    private A attribute = null;
    protected A Attribute { get { return attribute; } }

    private IEditorWinApplication application = null;
    public IEditorWinApplication Application { get { return application; } }

    protected TwoTypedStandardValuesProvider( IEditorWinApplication application, Attribute attribute ) { this.attribute = attribute as A; this.application = application; }

    public abstract bool IsStandardValuesExclusive( ITypeDescriptorContext context );
    public abstract TypeConverter.StandardValuesCollection GetStandardValues( ITypeDescriptorContext context );
    public abstract bool HasStandardValuesConvertor( ITypeDescriptorContext context );
    public abstract Type GetStandardValuesType( ITypeDescriptorContext context );

    protected abstract T ConvertFromStandardValueInternal( ITypeDescriptorContext context, object instance, object value );
    public object ConvertFromStandardValue( ITypeDescriptorContext context, object value )
    {
			object instance = ( null == context ) ? null : FullTypePropertyDescriptor.GetInstanceFromContext( context );
      return ConvertFromStandardValueInternal( context, instance, value );
    }
  }
}
