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
using DBTypes;
using EditorLib.ObjectsBrowser;
using EditorLib;

namespace EditorPlugins.Templates
{
	public partial class DefineTemplateForm : Form
	{
		private readonly IEditorWinApplication application = null;
		private Dictionary<string, TemplateModifiableProperty> modifiers = new Dictionary<string, TemplateModifiableProperty>();

		private int CompareTemplateModifiableProperty( TemplateModifiableProperty a, TemplateModifiableProperty b )
		{
			return string.Compare( a.name, b.name );
		}

		public DefineTemplateForm( IEditorWinApplication application )
		{
			InitializeComponent();
			this.application = application;
		}

		private void AnalyzeLinks( DBID patternDbid )
		{
			if ( !DataBase.IsExists( patternDbid ) )
				return;

			if ( string.IsNullOrEmpty( textBoxObjectNamePattern.Text ) )
			{
				string patternFileName = FileUtils.GetFileName( patternDbid.FileName );
				if ( patternFileName.StartsWith( "_." ) )
					textBoxObjectNamePattern.Text = FileUtils.GetParentFolderPath( FileUtils.GetParentFolderPath( patternDbid.FileName ) ) + FileUtils.PathSeparatorChar + "$" + FileUtils.PathSeparatorChar + "_";
				else
					textBoxObjectNamePattern.Text = FileUtils.GetParentFolderPath( patternDbid.FileName ) + FileUtils.PathSeparatorChar + "$";
			}

			if ( string.IsNullOrEmpty( textBoxName.Text ) )
			{
				string patternFileName = FileUtils.GetFileName( patternDbid.FileName );
				string templateName = string.Empty;
				if ( patternFileName.StartsWith( "_." ) )
					templateName = FileUtils.GetParentFolderName( FileUtils.GetParentFolderPath( patternDbid.FileName ) );
				else
					templateName = FileUtils.GetParentFolderName( patternDbid.FileName );

				if ( templateName.EndsWith( "s", StringComparison.InvariantCultureIgnoreCase ) )
					templateName = templateName.Substring( 0, templateName.Length - 1 );
				if ( templateName.StartsWith( FileUtils.PathSeparatorChar.ToString() ) )
					templateName = templateName.Substring( 1 );
				textBoxName.Text = templateName;
			}

			DBResource resource = DataBase.Get<DBResource>( patternDbid ).Get();
			properties.SelectedObject = new TemplateTypeDescriptor( resource );
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
			Close();
		}

		private void OnCreateClick( object sender, EventArgs e )
		{
			DBID dbid = DBID.GenerateUnique( "Templates", textBoxName.Text, typeof( TemplateDefinition ) );
			TemplateDefinition template = DataBase.Create<TemplateDefinition>( dbid, new TemplateDefinition() ).Get();
			template.name = textBoxName.Text;
			template.templateObject = DataBase.Get<DBResource>( DBID.FromString( textBoxObject.Text ) );
			template.namePattern = textBoxObjectNamePattern.Text;
			foreach( TemplateModifiableProperty property in modifiers.Values )
				template.fields.Add( property );

			TemplateUtils.UpdateTemplatesMenu( application.MainMenu );
		}

		private void OnTextBoxObjectTextChanged( object sender, EventArgs e )
		{
			AnalyzeLinks( DBID.FromString( textBoxObject.Text ) );
		}

		private void UpdateSelectedItem( TemplatePropertyDescriptor property )
		{
			if ( property == null )
				return;

			if ( property.Modifiable == TemplateModifiable.None )
			{
				if ( modifiers.ContainsKey( property.FieldName ) )
					modifiers.Remove( property.FieldName );

				textBoxFieldName.Enabled = false;
				textBoxFieldName.Text = property.FieldName;
				return;
			}

			TemplateModifiableProperty modifier = null;
			if ( modifiers.TryGetValue( property.FieldName, out modifier ) )
				modifier.modifiable = property.Modifiable;
			else
			{
				modifier = new TemplateModifiableProperty();
				modifier.field = property.FieldName;
				modifier.modifiable = property.Modifiable;
				modifier.name = property.FieldName;
				modifiers.Add( property.FieldName, modifier );
			}

			textBoxFieldName.Text = modifier.name;
			textBoxFieldName.Enabled = true;
		}

		private void OnSelectedGridItemChanged( object sender, SelectedGridItemChangedEventArgs e )
		{
			if ( e.NewSelection == null )
				return;

			UpdateSelectedItem( e.NewSelection.PropertyDescriptor as TemplatePropertyDescriptor );
		}

		private void OnPropertyValueChanged( object s, PropertyValueChangedEventArgs e )
		{
			UpdateSelectedItem( e.ChangedItem.PropertyDescriptor as TemplatePropertyDescriptor );
		}

		private void OnFieldNameTextChanged( object sender, EventArgs e )
		{
			TemplatePropertyDescriptor property = properties.SelectedGridItem.PropertyDescriptor as TemplatePropertyDescriptor;
			if ( property == null )
				return;
			
			TemplateModifiableProperty modifier = null;
			if ( !modifiers.TryGetValue( property.FieldName, out modifier ) )
				return;
			
			if ( modifier.name == textBoxFieldName.Text )
				return;

			modifier.name = textBoxFieldName.Text;
		}
	}
}
