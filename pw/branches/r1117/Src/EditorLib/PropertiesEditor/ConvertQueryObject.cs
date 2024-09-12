using libdb.IO;
using System.IO;

namespace EditorLib.PropertiesEditor
{
	internal sealed class ConvertQueryObject : BrowseQueryObject
	{
		private readonly string fileName;
		private readonly string relativePath;

		internal ConvertQueryObject( string _fileName, string _relativePath )
		{
			fileName = _fileName;
			relativePath = _relativePath;
		}

		public override object PerformBrowsing()
		{
			return FileUtils.FixFileName( FileUtils.Combine( relativePath, fileName ) );
		}

		public override string ToString()
		{
			return fileName;
		}
	}
}
