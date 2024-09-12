using System;
using System.ComponentModel;
using System.Drawing.Design;
using System.Windows.Forms;
using EditorLib;
using EditorLib.Extensions;
using EditorLib.FieldProcessor;
using EditorLib.FolderSelector;
using EditorPlugins.ObjectLayers;
using libdb.DB;

namespace EditorPlugins.Extensions
{
  [ApplicableForDeriver]
  public sealed class FolderSelectorValueEditor : TwoTypedValueEditor<ObjectLayersPath, FolderSelectorAttribute>
  {
    public FolderSelectorValueEditor(IEditorWinApplication application, Attribute attribute) 
      : base(application, attribute)
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

    protected override ObjectLayersPath EditValue(ITypeDescriptorContext context, object instance, IServiceProvider provider, ObjectLayersPath value)
    {
      FolderSelectorForm form = new FolderSelectorForm();

      if ( form.ShowDialog() == DialogResult.OK )
      {
        value.Path = form.CurrentFolder;
      }

      return value;
    }
  }
}
