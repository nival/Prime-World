using libdb.IO;
using System.IO;

namespace libdb.DB
{
	public delegate string ValueGenerator();

	public sealed class FileRef
	{
		private readonly ValueGenerator generateValue;
		private string value = string.Empty;
		
		public FileRef( ValueGenerator generateValue )
		{
			this.generateValue = generateValue;
		}

		public string Value
		{
			get { return value; }
		}

		public static implicit operator string( FileRef fileRef )
		{
			return fileRef.value;
		}

		public void Rename()
		{
			string oldValue = value;
			value = generateValue();

			if ( oldValue != value )
			{
				var fileSystem = DataBase.FileSystem;
				if ( fileSystem.GetFileInfo( oldValue ).IsFileExists )
				{
					FileUtils.CopyFile( fileSystem, oldValue, value );
					fileSystem.DeleteFile( oldValue );
				}
			}
		}

	}
}
