using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Reflection;
using System.Windows.Forms;
using DBTypes;
using EditorLib;
using EditorLib.Extensions;
using EditorLib.IO;
using EditorLib.ObjectsBrowser;
using EditorLib.Operations;
using libdb;
using libdb.DB;
using libdb.Diagnostics;
using libdb.IO;
using libdb.UndoRedo;

namespace EditorPlugins.Templates
{
	public partial class NewObjectTemplateForm : Form
	{
		private class ModifiableProperty
		{
			private readonly string name = string.Empty;
			private readonly List<ModifiablePropertyDescription> fields = new List<ModifiablePropertyDescription>();

			public ModifiableProperty( string name ) { this.name = name; }

			public void AssignField( object instance, DBFieldInfo field ) { fields.Add( new ModifiablePropertyDescription( instance, field ) ); }

			public string Name { get { return name; } }
			public IEnumerable<ModifiablePropertyDescription> Fields { get { return fields; } }
		}

		private sealed class PropertiesTypeDescriptor : ICustomTypeDescriptor
		{
			private readonly PropertyDescriptorCollection properties = null;

			public PropertiesTypeDescriptor( IEditorWinApplication application, IEnumerable<ModifiableProperty> properties )
			{
				List<PropertyDescriptor> result = new List<PropertyDescriptor>();
				foreach ( ModifiableProperty field in properties )
					result.Add( new ResourceInstanceDescriptor( field.Name, field.Fields, application ) );

				this.properties = new PropertyDescriptorCollection( result.ToArray() );
			}

			public AttributeCollection GetAttributes() { return new AttributeCollection(); }
			public string GetClassName() { return typeof( TemplateDefinition ).ToString(); }
			public string GetComponentName() { return TypeDescriptor.GetComponentName( typeof( TemplateDefinition ), true ); }
			public TypeConverter GetConverter() { return TypeDescriptor.GetConverter( typeof( TemplateDefinition ) ); }
			public EventDescriptor GetDefaultEvent() { return null; }
			public PropertyDescriptor GetDefaultProperty() { return null; }
			public object GetEditor( Type editorBaseType ) { return TypeDescriptor.GetEditor( this, editorBaseType, true ); }
			public EventDescriptorCollection GetEvents( Attribute[] attributes ) { return new EventDescriptorCollection( new EventDescriptor[0], true ); }
			public EventDescriptorCollection GetEvents() { return GetEvents( null ); }
			public PropertyDescriptorCollection GetProperties( Attribute[] attributes ) { return properties; }
			public PropertyDescriptorCollection GetProperties() { return properties; }
			public object GetPropertyOwner( PropertyDescriptor pd ) { return properties; }
		}

		private enum SrcFileCopyAction
		{
			Undefined,
			CopyFromTemplate,
			LeaveExisting,
		}

		private sealed class SrcFileField
		{
			private readonly string srcFile = string.Empty;
			private readonly string destFile = string.Empty;
			private readonly SrcFile destSrcFile = null;

			public SrcFileField( string srcFile, SrcFile destSrcFile )
			{
				this.srcFile = srcFile;
				this.destSrcFile = destSrcFile;
				destFile = destSrcFile.FileName;
			}

			public bool Copy( SourceFileSystem sourceFileSystem, ref SrcFileCopyAction copyAction )
			{
				bool destFileExists = sourceFileSystem.IsFileExists( destSrcFile.FileName );
				if ( destFileExists && ( destFile != destSrcFile.FileName || copyAction == SrcFileCopyAction.LeaveExisting ) )
					return true;

				if ( destFileExists && copyAction == SrcFileCopyAction.Undefined )
				{
					switch ( MessageBox.Show( string.Format( "Source file \"{0}\" for new object already exists. Do you want overwrite it with source file from template?", destSrcFile.FileName ), "Source File Already Exists", MessageBoxButtons.YesNoCancel, MessageBoxIcon.Question ) )
					{
					case DialogResult.Yes:
						copyAction = SrcFileCopyAction.CopyFromTemplate;
						break;
					case DialogResult.No:
						copyAction = SrcFileCopyAction.LeaveExisting;
						break;
					default:
						return false;
					}
				}

				if ( copyAction == SrcFileCopyAction.LeaveExisting )
					return true;

				if ( !sourceFileSystem.IsFileExists( srcFile ) )
				{
					Log.TraceError( "Source file \"{0}\" from template is missing", srcFile );
					return false;
				}

				sourceFileSystem.AddFile( destSrcFile.FileName, sourceFileSystem.GetFullFileName( srcFile ), true );
				return true;
			}
		}

		private readonly IEditorWinApplication application = null;
		private readonly TemplateDefinition template = null;
		private DBID resultDbid = DBID.Empty;

		private Dictionary<string, ModifiableProperty> fields = new Dictionary<string, ModifiableProperty>();
		private Dictionary<string, string> fieldNames = new Dictionary<string, string>();
		private Dictionary<string, SrcFileField> srcFileFields = new Dictionary<string, SrcFileField>();
		private List<DBResource> resourceToImport = new List<DBResource>();

		private void TryAddField( string fieldName, object instance, DBFieldInfo field )
		{
			string name = string.Empty;
			if ( !fieldNames.TryGetValue( fieldName, out name ) )
				return;

			ModifiableProperty modifiableField = null;
			if ( fields.TryGetValue( name, out modifiableField ) )
				modifiableField.AssignField( instance, field );
		}

		private void CopySrcFileField( object owner, SrcFile dstSrcFile, SrcFile srcSrcFile )
		{
			DBResource dstResource = owner as DBResource ?? ( owner is IOwnerable ? ( owner as IOwnerable ).GetOwner() : null );
			DBID dstDbid = dstResource == null ? DBID.Empty : dstResource.DBId;

			if ( dstSrcFile != null && srcSrcFile != null && !DBID.IsNullOrEmpty( dstDbid ) )
			{
				string srcSrcFileName = FileUtils.GetFileName( srcSrcFile.FileName );
				string dstScrFileName = FileUtils.Combine( FileUtils.GetParentFolderPath( dstDbid.FileName ), srcSrcFileName );
				dstSrcFile.SetFileName( dstScrFileName );
				if ( !srcFileFields.ContainsKey( srcSrcFile.FileName.ToLower() ) )
					srcFileFields.Add( srcSrcFile.FileName.ToLower(), new SrcFileField( srcSrcFile.FileName, dstSrcFile ) );
			}
		}

		private bool CopyList( string fieldName, object dest, object src, bool hasSrcFileAttribute )
		{
			if ( dest == null || src == null )
				return false;

			Type itemType = TypeUtils.GetTypeFromList( src.GetType() );
			IEnumerable srcList = src as IEnumerable;
			if ( itemType == null || srcList == null )
				return false;

			PropertyInfo countProperty = TypeUtils.GetProperty( dest.GetType(), "Count" );
			PropertyInfo itemProperty = TypeUtils.GetProperty( dest.GetType(), "Item" );
			MethodInfo addMethod = TypeUtils.GetMethod( dest.GetType(), "Add", new Type[1] { itemType } );
			if ( countProperty == null || itemProperty == null || addMethod == null )
				return false;

			int count = (int)countProperty.GetValue( dest, null );
			int index = 0;
			foreach ( object srcItem in srcList )
			{
				string thisFieldName = fieldName + "[" + index.ToString() + "]";
				if ( hasSrcFileAttribute )
				{
					if ( itemType == typeof( SrcFile ) )
					{
						SrcFile dstSrcFile = null;
						if ( index < count )
							dstSrcFile = itemProperty.GetValue( dest, new object[1] { index } ) as SrcFile;
						else
						{
							dstSrcFile = new SrcFile();
							addMethod.Invoke( dest, new object[1] { dstSrcFile } );
						}

						CopySrcFileField( dest, dstSrcFile, srcItem as SrcFile );
					}
				}
				else if ( TypeUtils.IsSimpleType( itemType ) )
				{
					if ( index < count )
						itemProperty.SetValue( dest, srcItem, new object[1] { index } );
					else
						addMethod.Invoke( dest, new object[1] { srcItem } );

					// we have to check fieldName here
				}
				else if ( TypeUtils.IsStruct( itemType ) )
				{
					object destItem = null;
					if ( index < count )
						destItem = itemProperty.GetValue( dest, new object[1] { index } );
					else
					{
						destItem = TypeUtils.CreateInstance( itemType );
						addMethod.Invoke( dest, new object[1] { destItem } );

						count = (int)countProperty.GetValue( dest, null );
						destItem = itemProperty.GetValue( dest, new object[1] { count - 1 } );
					}
					CopyFields( thisFieldName, destItem, srcItem );
				}
				else if ( TypeUtils.IsList( itemType ) )
				{
					object destItem = null;
					if ( index < count )
						destItem = itemProperty.GetValue( dest, new object[1] { index } );
					else
					{
						destItem = TypeUtils.CreateInstance( itemType );
						addMethod.Invoke( dest, new object[1] { destItem } );

						count = (int)countProperty.GetValue( dest, null );
						destItem = itemProperty.GetValue( dest, new object[1] { count - 1 } );
					}
					CopyList( thisFieldName, destItem, srcItem, false );
				}
				else if ( TypeUtils.GetTypeFromPtr( itemType ) != null )
				{
					DBPtrBase destItem = null;
					if ( index < count )
						destItem = itemProperty.GetValue( dest, new object[1] { index } ) as DBPtrBase;
					else
					{
						destItem = TypeUtils.CreateInstance( itemType ) as DBPtrBase;
						addMethod.Invoke( dest, new DBPtrBase[1] { destItem } );

						count = (int)countProperty.GetValue( dest, null );
						destItem = itemProperty.GetValue( dest, new object[1] { count - 1 } ) as DBPtrBase;
					}
					CopyDBPtr( thisFieldName, destItem, srcItem as DBPtrBase );
				}

				++index;
			}

			return true;
		}

		private bool CopyFields( string fieldName, object dest, object src )
		{
			if ( ReferenceEquals( dest, src ) || dest == null || src == null )
				return false;

			var srcFields = new Dictionary<string, DBFieldInfo>();
			Array.ForEach( TypeUtils.GetFields( src.GetType(), true ), field => srcFields.Add( field.Name, field ) );

			var dstFields = TypeUtils.GetFields( dest.GetType(), true );
			foreach ( var dstField in dstFields )
			{
				string thisFieldName = string.IsNullOrEmpty( fieldName ) ? dstField.Name : fieldName + "." + dstField.Name;
				DBFieldInfo srcField;
				if ( srcFields.TryGetValue( dstField.Name, out srcField ) && srcField.CanRead && srcField.FieldType == dstField.FieldType )
				{
					bool hasSrcFileAttribute = TypeUtils.HasAttribute<SrcFileAttribute>( dstField, true ) && dstField.FieldType == typeof( SrcFile );

					if ( hasSrcFileAttribute )
					{
						SrcFile dstSrcFile = dstField.GetValue( dest ) as SrcFile;
						SrcFile srcSrcFile = srcField.GetValue( src ) as SrcFile;

						CopySrcFileField( dest, dstSrcFile, srcSrcFile );
					}
					else if ( TypeUtils.IsSimpleType( dstField.FieldType ) )
					{
						if ( dstField.CanWrite )
							dstField.SetValue( dest, srcField.GetValue( src ) );
					}
					else if ( TypeUtils.IsStruct( dstField.FieldType ) )
						CopyFields( thisFieldName, dstField.GetValue( dest ), srcField.GetValue( src ) );
					else if ( TypeUtils.IsList( dstField.FieldType ) )
						CopyList( thisFieldName, dstField.GetValue( dest ), srcField.GetValue( src ), false );
					else if ( TypeUtils.GetTypeFromPtr( dstField.FieldType ) != null )
						CopyDBPtr( thisFieldName, dstField.GetValue( dest ) as DBPtrBase, srcField.GetValue( src ) as DBPtrBase );

					// we have to check fieldName here
					TryAddField( thisFieldName, dest, dstField );
				}
			}

			return true;
		}

		private bool CopyDBPtr( string fieldName, DBPtrBase dest, DBPtrBase src )
		{
			if ( src == null || src.DBId.IsEmpty || dest == null )
				return false;

			if ( src.DBId.IsInlined )
			{
				DBID destDbid = DBID.FromDBID( dest.GetOwner().DBId, true );
				DBResource resource = TypeUtils.CreateInstance( src.Get<DBResource>().GetType() ) as DBResource;
				DataBase.Create<DBResource>( destDbid, resource );
				dest.Set( destDbid );

				CopyFields( fieldName, resource, src.Get<DBResource>() );
				resourceToImport.Add( resource );
			}
			else
				dest.Set( src.DBId );

			return true;
		}

		public NewObjectTemplateForm( IEditorWinApplication application, DBID templateDbid )
		{
			InitializeComponent();

			this.application = application;
			template = DataBase.Get<TemplateDefinition>( templateDbid, new TemplateDefinition() ).Get();
			textBoxName.Text = string.Format( "{0} ({1})", template.name, template.DBId.Name );
		}

		private void OnCancelClick( object sender, EventArgs e )
		{
			DataBase.Delete( resultDbid );
			Close();
		}

		private bool CopyOperation( IOperationContext context )
		{
			context.Start( true, true );
			context.Progress( "Copy source files ..." );
			int count = 0;
			SrcFileCopyAction copyAction = SrcFileCopyAction.Undefined;
			foreach ( SrcFileField srcFileField in srcFileFields.Values )
			{
				if ( !srcFileField.Copy( application.Application.SourceFileSystem, ref copyAction ) )
					return false;

				context.Progress( "Copy source files ...", 100 * count / srcFileFields.Count );
			}

			return true;
		}

		private void OnCreateClick( object sender, EventArgs e )
		{
      if ( checkBoxAutoImport.Checked )
      {
        List<Executor.OperationHandler> operations = new List<Executor.OperationHandler>();
        operations.Add( CopyOperation );
        foreach ( DBResource resource in resourceToImport )
        {
          if ( !application.Application.Extensions.HasImporter( resource.GetType() ) )
            continue;

          IImporter importer = application.Application.Extensions.CreateImporter( resource.DBId, application.Application, false );
          if ( importer != null )
            operations.Add( importer.Import );
        }

        application.Application.OperationExecutor.Start( operations.ToArray() );
      }

			Close();
		}

		private void OnCommitClick( object sender, EventArgs e )
		{
			string nameWithOutExtension = template.namePattern.Replace( "$", textBoxObject.Text );
      string folder = application.Panels.GetSingletonPanel<ObjectsBrowserPanel>().CurrentFolder;
			string name = FileUtils.GetFileName( nameWithOutExtension );
			Type templateType = template.templateObject.Get().GetType();

			DBID.TryCreateDBID( folder, name, templateType, out resultDbid );

			textBoxObject.Text = resultDbid.Name;
			textBoxObject.Enabled = false;
			buttonCommit.Enabled = false;

			foreach ( var field in template.fields )
			{
				if ( !fields.ContainsKey( field.name ) )
					fields.Add( field.name, new ModifiableProperty( field.name ) );
				fieldNames.Add( field.field, field.name );
			}

      using( UndoRedoTransaction trans = new UndoRedoTransaction( "Create New Object" ) )
      {
        DBResource newResource = TypeUtils.CreateInstance( templateType ) as DBResource;
        DataBase.Create<DBResource>( resultDbid, newResource );
        CopyFields( string.Empty, newResource, template.templateObject.Get() );       
        trans.Commit();
      }
			
      properties.SelectedObject = new PropertiesTypeDescriptor( application, fields.Values );

			buttonCreate.Enabled = true;
			properties.Enabled = true;
			properties.ViewBackColor = System.Drawing.Color.FromKnownColor( KnownColor.Window );

      buttonCancel.Enabled = false;
    }
	}
}
