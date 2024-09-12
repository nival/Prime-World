using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

namespace EditorPlugins.Editors.TextRef
{
	//TODO: этот контрол надо удалить, он юзается кодом, который тоже надо удалить
	public partial class TextRefEditorControl : UserControl
	{
		private readonly libdb.DB.TextRef text = null;

		public TextRefEditorControl( libdb.DB.TextRef text )
		{
			InitializeComponent();
			this.text = text;
			textBox.Text = text.ToString();
		}

		private void OnTextBoxPreviewKeyDown( object sender, PreviewKeyDownEventArgs e )
		{
			if ( e.KeyCode == Keys.Enter )
				text.FromString( textBox.Text );
		}
	}
}
