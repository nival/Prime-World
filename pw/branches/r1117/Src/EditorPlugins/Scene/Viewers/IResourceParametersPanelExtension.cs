using System.Collections.Generic;
using libdb.DB;

namespace EditorPlugins.Scene.Viewers
{
	public interface IResourceParametersPanelExtension<TListItem>
	{
		DBID ResourceId { get; }
		IList<TListItem> Items { get; }
	}
}
