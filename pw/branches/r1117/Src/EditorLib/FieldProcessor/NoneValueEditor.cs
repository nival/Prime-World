using System;
using System.ComponentModel;
using System.Drawing.Design;
using EditorLib.Extensions;

namespace EditorLib.FieldProcessor
{
  [ApplicableForDeriver]
  public sealed class NoneValueEditor : TwoTypedValueEditor<object, SupressValueEditor>
  {
    public NoneValueEditor(IEditorWinApplication application, Attribute attribute) : base(application, attribute)
    {
    }

    public override bool IsDropDownResizable
    {
      get { return false; }
    }

    public override UITypeEditorEditStyle EditorEditStyle
    {
      get { return UITypeEditorEditStyle.None; }
    }

    protected override object EditValue(ITypeDescriptorContext context, object instance, IServiceProvider provider, object value)
    {
      return value;
    }
  }
}