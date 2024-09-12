using System.Collections.Generic;

namespace EditorPlugins.Committer
{
	internal class AssetInfo
	{
		public bool SelectedForCommit = false;
		public List<ChangeItemInfo> DataFiles = new List<ChangeItemInfo>();
		public List<ChangeItemInfo> SourceFiles = new List<ChangeItemInfo>();
	}
}
