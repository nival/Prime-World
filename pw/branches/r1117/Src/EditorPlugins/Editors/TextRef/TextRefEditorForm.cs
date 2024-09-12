using System;
using System.ComponentModel;
using System.Windows.Forms;
using EditorLib;
using EditorLib.Settings;
using libdb.DB;

namespace EditorPlugins.Editors.TextRef
{
	public partial class TextRefEditorForm : Form
	{
		[ConfigObject( true )]
		public class TextRefEditorFormConfig : SimpleConfigObject
		{
			public int LocationX = 100;
			public int LocationY = 100;
			public int Width = 300;
			public int Height = 200;
			public bool WordWrap = true;
		}

		private IEditorWinApplication application;
		public readonly libdb.DB.TextRef Value = null;
		private string originalText;

		public TextRefEditorForm(libdb.DB.TextRef value, IEditorWinApplication application)
		{
			InitializeComponent();
			Value = value;
			originalText = tbMain.Text = value.ToString();
			this.Text = value.GetOwner().DBId.FileName;
			this.application = application;
		}

		private void cbWrap_CheckedChanged(object sender, EventArgs e)
		{
            if (cbWordWrap.Checked)
            {
                tbMain.LineWrapping.Mode = ScintillaNET.LineWrappingMode.Word;
            }
            else 
            {
                tbMain.LineWrapping.Mode = ScintillaNET.LineWrappingMode.None;
            }
		}

		private void btnCancel_Click(object sender, EventArgs e)
		{
			Close();
		}

		private void btnOk_Click( object sender, EventArgs e )
		{
			// Проверим, а жив ли еще наш textref и не удалили ли его из базы
			if ( Value.GetOwner() != null && !DataBase.IsExists( Value.GetOwner().DBId ) )
			{
				DialogResult res = MessageBox.Show((IWin32Window) this, "Оbject is deleted from database," +
				                                     " saving unavialible. Do you want to continue editing?", "Error",
				                MessageBoxButtons.YesNo, MessageBoxIcon.Error, MessageBoxDefaultButton.Button1);
				if ( res == DialogResult.No ) 
					Close();
				
				return;
			}
			// Проверим не изменился ли текст извне
			if( originalText != Value.ToString())
			{
				DialogResult res = MessageBox.Show((IWin32Window) this, "Text has been modified outside of this editor" +
				                                                        " \r\n Do you want to overwrite that changes with your text?",
				                                   "Warning", MessageBoxButtons.YesNoCancel,
				                                   MessageBoxIcon.Warning, MessageBoxDefaultButton.Button3);
				switch ( res )
				{
					case DialogResult.No:
						Close();
						return;
					case DialogResult.Cancel:
						return;
				}
			}
			Value.FromString(tbMain.Text);
			Close();
		}

		private void TextRefEditorForm_Load( object sender, EventArgs e )
		{
			var c= application.Application.Settings.Get<TextRefEditorFormConfig>();
			this.SetBounds(c.LocationX, c.LocationY, c.Width, c.Height);
			cbWordWrap.Checked = c.WordWrap;
		}

		private void TextRefEditorForm_FormClosing( object sender, FormClosingEventArgs e )
		{
			var c = application.Application.Settings.Get<TextRefEditorFormConfig>();
			c.LocationX = Location.X;
			c.LocationY=Location.Y;
			c.Width=Width;
			c.Height = Height;
			c.WordWrap = cbWordWrap.Checked;
		}

	}

	
}
