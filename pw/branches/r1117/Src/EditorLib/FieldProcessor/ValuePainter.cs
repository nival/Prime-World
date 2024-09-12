using System;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel;
using System.Drawing;

namespace EditorLib.FieldProcessor
{
  public interface IValuePainter
  {
    /// <summary>
    /// Paints a representation of the context
    /// </summary>
    /// 
    void PaintValue( ITypeDescriptorContext context, object value, Graphics graphics, Rectangle bounds );

    IEditorWinApplication Application { get; set; }
  }

  public abstract class TypedValuePainter<T> : IValuePainter
  {
    private IEditorWinApplication application = null;
    public IEditorWinApplication Application { get { return application; } set { application = value; } }
    protected TypedValuePainter( IEditorWinApplication application ) { this.application = application; }

    protected abstract void PaintValue( ITypeDescriptorContext context, object instance, T value, Graphics graphics, Rectangle bounds );
    public void PaintValue( ITypeDescriptorContext context, object value, Graphics graphics, Rectangle bounds )
    {
			object instance = ( null == context ) ? null : FullTypePropertyDescriptor.GetInstanceFromContext( context );
      PaintValue( context, instance, ( T )value, graphics, bounds );
    }
  }

  public abstract class TwoTypedPainter<T, A> : IValuePainter where A : Attribute
  {
    private A attribute = null;
    public A Attribute { set { attribute = value; } get { return attribute; } }

    private IEditorWinApplication application = null;
    public IEditorWinApplication Application { get { return application; } set { application = value; } }

    protected TwoTypedPainter( IEditorWinApplication application, Attribute attribute ) { this.application = application; this.attribute = attribute as A; }

    protected abstract T PaintValue( ITypeDescriptorContext context, object instance, object value, Graphics graphics, Rectangle bounds );
    public void PaintValue( ITypeDescriptorContext context, object value, Graphics graphics, Rectangle bounds )
    {
			object instance = ( null == context ) ? null : FullTypePropertyDescriptor.GetInstanceFromContext( context );
      PaintValue( context, instance, ( T )value, graphics, bounds );
    }
  }
}
