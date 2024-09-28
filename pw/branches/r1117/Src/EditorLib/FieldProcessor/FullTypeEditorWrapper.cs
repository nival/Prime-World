using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing.Design;
using System.ComponentModel;

namespace EditorLib.FieldProcessor
{
  internal class FullTypeEditorWrapper : UITypeEditor
  {
    private readonly FullTypeDescriptor descriptor = null;
    private readonly UITypeEditor defaultEditor = null;

    # region Initialization

    public FullTypeEditorWrapper( FullTypeDescriptor descriptor )
    {
      this.descriptor = descriptor;
      if ( descriptor.ValueEditor == null )
        defaultEditor = TypeDescriptor.GetEditor( descriptor.Type, typeof( UITypeEditor ) ) as UITypeEditor;
    }

    #endregion

    # region UITypeEditor overriding

    public override bool IsDropDownResizable 
    {
      get 
      {
        if ( descriptor.ValueEditor != null )
          return descriptor.ValueEditor.IsDropDownResizable;
        else if ( defaultEditor != null )
          return defaultEditor.IsDropDownResizable;
        else
          return base.IsDropDownResizable;
      }
    }

    public override bool GetPaintValueSupported( ITypeDescriptorContext context )
    {
      return descriptor.ValuePainter != null;
    }

    public override UITypeEditorEditStyle GetEditStyle( ITypeDescriptorContext context )
    {
      if ( descriptor.ValueEditor != null )
        return descriptor.ValueEditor.EditorEditStyle;
      else if ( defaultEditor != null )
        return defaultEditor.GetEditStyle( context );
      else
        return base.GetEditStyle( context );
    }

    public override object EditValue( ITypeDescriptorContext context, IServiceProvider provider, object value )
    {
      if ( descriptor.ValueEditor != null )
        return descriptor.ValueEditor.EditValue( context, provider, value );
      else if ( defaultEditor != null )
        return defaultEditor.EditValue( context, provider, value );
      else
        return base.EditValue( context, provider, value );
    }

    public override void PaintValue( PaintValueEventArgs arguments )
    {
      if ( descriptor.ValuePainter != null )
        descriptor.ValuePainter.PaintValue( arguments.Context, arguments.Value, arguments.Graphics, arguments.Bounds );
      else if ( defaultEditor != null )
        defaultEditor.PaintValue( arguments );
      else
        base.PaintValue( arguments );
    }

    #endregion
  }
}
