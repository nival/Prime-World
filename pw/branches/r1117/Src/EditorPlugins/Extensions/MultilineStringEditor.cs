using System;
using System.Windows.Forms;
using EditorLib;
using EditorLib.Extensions;
using EditorLib.FieldProcessor;
using libdb.DB;

namespace EditorPlugins.Extensions
{
    [ApplicableForDeriver]
    public sealed class MultilineStringEditor : TwoTypedValueEditor<string, MultilineAttribute>
    {
        public MultilineStringEditor(IEditorWinApplication application, Attribute attribute) : base(application, attribute) { }

        public override bool IsDropDownResizable
        {
            get { return false; }
        }

        public override System.Drawing.Design.UITypeEditorEditStyle EditorEditStyle
        {
            get { return System.Drawing.Design.UITypeEditorEditStyle.Modal; }
        }

        protected override string EditValue(System.ComponentModel.ITypeDescriptorContext context, object instance, System.IServiceProvider provider, string value)
        {
            MultilineStringEditorForm editor = new MultilineStringEditorForm(value);

            if (editor.ShowDialog() == DialogResult.OK)
            {
                return editor.Code;
            }

            return value;
        }
    }
}
