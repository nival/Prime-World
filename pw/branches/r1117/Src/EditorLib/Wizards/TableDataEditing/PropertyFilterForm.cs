using System.Windows.Forms;

namespace EditorLib.Wizards.TableDataEditing
{
	public partial class PropertyFilterForm : Form
	{
		public string Filter 
		{
			get { return txtFilter.Text; }
			set { txtFilter.Text = value; }
		}

		public PropertyFilterForm()
		{
			InitializeComponent();
		}

		private void OnKeyUp( object sender, KeyEventArgs e )
		{
			if(e.KeyCode == Keys.Escape)
				this.Close();
		}
	}
}
