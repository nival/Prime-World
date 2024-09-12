using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing.Design;
using System.ComponentModel;
using libdb.Diagnostics;

namespace EditorLib.FieldProcessor
{
  public interface IValueEditor
  {
    bool IsDropDownResizable { get; }

    /// <summary>
    /// Returns edit style of editor for this type or field. Return UITypeEditorEditStyle.None if no editors for this type or field
    /// </summary>
    UITypeEditorEditStyle EditorEditStyle { get; }

    /// <summary>
    /// Edits the context
    /// </summary>
    object EditValue( ITypeDescriptorContext context, IServiceProvider provider, object value );

    IEditorWinApplication Application { get; }
  }

  public abstract class TypedValueEditor<T> : IValueEditor
  {
    private IEditorWinApplication application = null;
    public IEditorWinApplication Application { get { return application; } }

    public TypedValueEditor( IEditorWinApplication application ) { this.application = application; }

    public abstract bool IsDropDownResizable { get; }
    public abstract UITypeEditorEditStyle EditorEditStyle { get; }

    protected abstract T EditValue( ITypeDescriptorContext context, object instance, IServiceProvider provider, T value );
    public object EditValue( ITypeDescriptorContext context, IServiceProvider provider, object value )
    {
			object instance = ( null == context ) ? null : FullTypePropertyDescriptor.GetInstanceFromContext( context );
      return EditValue( context, instance, provider, (T)value );
    }
  }

  public abstract class TwoTypedValueEditor<T, A> : IValueEditor where A : Attribute
  {
    private A attribute = null;
    public A Attribute { get { return attribute; } }

    private IEditorWinApplication application = null;
    public IEditorWinApplication Application { get { return application; } }

    protected TwoTypedValueEditor( IEditorWinApplication application, Attribute attribute ) { this.attribute = attribute as A; this.application = application; }

    public abstract bool IsDropDownResizable { get; }
    public abstract UITypeEditorEditStyle EditorEditStyle { get; }

    protected abstract T EditValue( ITypeDescriptorContext context, object instance, IServiceProvider provider, T value );
    public object EditValue( ITypeDescriptorContext context, IServiceProvider provider, object value )
    {
			object instance = ( null == context ) ? null : FullTypePropertyDescriptor.GetInstanceFromContext( context );
      return EditValue( context, instance, provider, (T)value );
    }
  }
}
