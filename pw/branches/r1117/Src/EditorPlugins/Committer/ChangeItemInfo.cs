using System;
using SharpSvn;

namespace EditorPlugins.Committer
{
	internal class ChangeItemInfo
	{
		public readonly string File = string.Empty;
		public readonly string FullPath = string.Empty;
		public readonly string Path = string.Empty;
		public readonly Uri Uri = null;
		public readonly SvnStatus LocalContentStatus = SvnStatus.NotVersioned;
		public readonly long LastChangeRevision = -1;

		public ChangeItemInfo( string _file, SvnStatusEventArgs _status )
		{
			File = _file;
			FullPath = _status.FullPath;
			Path = _status.Path;
			Uri = _status.Uri;
			LocalContentStatus = _status.LocalContentStatus;
			LastChangeRevision = _status.WorkingCopyInfo != null ? _status.LastChangeRevision : -1;
		}

		public ChangeItemInfo( string _file, string _fullPath )
		{
			File = _file;
			FullPath = _fullPath;
			Path = _fullPath;
		}
	}
}
