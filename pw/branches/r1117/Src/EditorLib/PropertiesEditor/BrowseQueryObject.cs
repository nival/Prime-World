using System.IO;
using System.Windows.Forms;
using EditorLib.IO;

namespace EditorLib.PropertiesEditor
{
	public abstract class BrowseQueryObject
	{
		public const string BROWSE_STRING = "<Browse...>";

		public abstract object PerformBrowsing();
	}
}
