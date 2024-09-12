using EditorLib.Settings;
using libdb.IO;

namespace EditorLib.IO
{
  [ConfigObject( true )]
  public sealed class SourceFileSystemConfig : SimpleConfigObject
	{
		public string RootPath;

		protected override void OnAfterDeserialize()
		{
			RootPath = FileUtils.FixFileName( RootPath );
		}
	}
}
