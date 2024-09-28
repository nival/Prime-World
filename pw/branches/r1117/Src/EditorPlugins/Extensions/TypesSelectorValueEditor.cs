using System;
using System.Collections.Generic;
using System.Drawing.Design;
using System.Windows.Forms;
using DBTypes;
using EditorLib;
using EditorLib.Extensions;
using EditorLib.FieldProcessor;
using EditorLib.ObjectsBrowser;
using libdb.DB;

namespace EditorPlugins.Extensions
{
  [ApplicableForDeriver]
  public sealed class TypesSelectorValueEditor : TwoTypedValueEditor<List<Type>, TypesSelectorAttribute>
  {
    private readonly List<Type> types = null;
    public TypesSelectorValueEditor( IEditorWinApplication application, Attribute attribute ) : base( application, attribute )
    {
      types = new List<Type>();

      foreach ( Type t in DataBase.KnownResources )
      {
        if ( t == typeof( GameObject ) || TypeUtils.IsSubclassOf( t, typeof( GameObject ) ) )
          types.Add( t );
      }
    }

    public override bool IsDropDownResizable
    {
      get { return false; }
    }

    public override UITypeEditorEditStyle EditorEditStyle
    {
      get { return UITypeEditorEditStyle.Modal; }
    }

    protected override List<Type> EditValue( System.ComponentModel.ITypeDescriptorContext context, object instance, IServiceProvider provider, List<Type> value )
    {
      ItemSelectorForm<Type> form = new ItemSelectorForm<Type>( types, value );
      form.Text = "Select Types";
      form.StartPosition = FormStartPosition.CenterParent;
      form.DisplayMember = "Name";

      if ( form.ShowDialog() == DialogResult.OK )
      {
        return form.SelectedItems;
      }

      return value;
    }
  }
}
