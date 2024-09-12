using System.Collections.Generic;
using DBTypes;
using EditorNative.SceneElements;
using libdb.DB;

namespace EditorPlugins.Scene.Editors
{
	public interface IEditorControlExtension
	{
		void TryRemove( SceneElement obj );

    void TryCopy();
    void TryPaste();

		void OnObjectSelected( SceneElement obj );

		string ConfigSection { get; }
		bool ObjectsSelectable { set; }

		string GetMenuItemNameBy( SceneElement element );

    DBPtr<LightEnvironment> DayLighting { get; }
    DBPtr<LightEnvironment> NightLighting { get; }
		IEnumerable<PointLightInfo> PointLights { get; }
    BakedLighting bakedLighting { get; }
    DBPtr<AdvMap> Resource { get; }
	}
}
