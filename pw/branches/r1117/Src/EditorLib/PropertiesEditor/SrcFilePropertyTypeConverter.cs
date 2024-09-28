using System.Collections.Generic;
using System.ComponentModel;
using System.Globalization;
using System.IO;
using EditorLib.IO;
using libdb;
using libdb.DB;
using libdb.IO;

namespace EditorLib.PropertiesEditor
{
	public sealed class SrcFilePropertyTypeConverter : StringConverter
	{
		private readonly string rootFolder = string.Empty;
		private readonly SrcFileAttribute attribute;
		private readonly SourceFileSystem sourceFileSystem;

		public SrcFilePropertyTypeConverter( object _instance, SrcFileAttribute _attribute, SourceFileSystem _sourceFileSystem )
		{
			if ( !string.IsNullOrEmpty( _attribute.SourceFolder ) )
				rootFolder = FileUtils.FixFolderName( _attribute.SourceFolder );
			else
			{
				DBResource resource = null;
				if ( _instance is DBResource )
					resource = _instance as DBResource;
				else if ( _instance is IOwnerable )
					resource = (_instance as IOwnerable).GetOwner();

				if ( resource != null && resource.DBId != null && !resource.DBId.IsEmpty )
					rootFolder = FileUtils.FixFolderName( Path.GetDirectoryName( resource.DBId.FileName ) );
			}

			attribute = _attribute;
			sourceFileSystem = _sourceFileSystem;
		}

		public override bool GetStandardValuesSupported( ITypeDescriptorContext context )
		{
			return true;
		}

		public override bool GetStandardValuesExclusive( ITypeDescriptorContext context )
		{
			return true;
		}

		public override StandardValuesCollection GetStandardValues( ITypeDescriptorContext context )
		{
			if ( string.IsNullOrEmpty( rootFolder ) )
				return new StandardValuesCollection( new string[0] );

			var values = new List<string>( sourceFileSystem.GetFileNames( rootFolder, attribute.Extensions, SearchOption.TopDirectoryOnly ) ).ConvertAll( fileName => Path.GetFileName( fileName ) );

			values.Add( BrowseQueryObject.BROWSE_STRING );
			return new StandardValuesCollection( values );
		}

		public override object ConvertFrom( ITypeDescriptorContext context, CultureInfo culture, object value )
		{
			if ( !(value is string ) )
				return base.ConvertFrom( context, culture, value );

			string strValue = value.ToString();
			if ( strValue == BrowseQueryObject.BROWSE_STRING )
				return new BrowseSourceFileQueryObject( sourceFileSystem, attribute.Description, attribute.Extensions, rootFolder );
			else
				return new ConvertQueryObject( strValue, rootFolder );
		}
	}
}
