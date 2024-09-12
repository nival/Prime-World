using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using EditorLib.ObjectSelector;
using libdb.DB;
using libdb.IO;

namespace EditorLib.Templates
{
	public partial class DefineTemplateForm : Form
	{
		public DefineTemplateForm()
		{
			InitializeComponent();
		}

		private void AnalyzeLinks( DBID patternDbid )
		{
			if ( !DataBase.IsExists( patternDbid ) )
				return;

			DBResource resource = DataBase.Get<DBResource>( patternDbid ).Get();
			properties.SelectedObject = new TemplateStructTypeDescriptor( resource );
		}

		private void OnBackClick( object sender, EventArgs e )
		{

		}

		private void OnBrowseClick( object sender, EventArgs e )
		{
			ObjectSelectorForm selector = new ObjectSelectorForm( DBID.Empty, typeof( DBResource ) );
			if ( selector.ShowDialog() == DialogResult.OK )
			{
				DBID dbId = selector.SelectedObject;
				if ( !DBID.IsNullOrEmpty( dbId ) && DataBase.IsExists( dbId ) )
					textBoxObject.Text = dbId.Name;
				else
					textBoxObject.Text = string.Empty;
			}
		}

		private void OnCancelClick( object sender, EventArgs e )
		{

		}

		private void OnNextClick( object sender, EventArgs e ) 
		{

		}

		private void OnTextBoxObjectTextChanged( object sender, EventArgs e )
		{
			AnalyzeLinks( DBID.FromString( textBoxObject.Text ) );
		}
	}
}
