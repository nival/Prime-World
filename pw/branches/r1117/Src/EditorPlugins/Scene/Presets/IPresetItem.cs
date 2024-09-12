using EditorNative.SceneElements.SceneObjects;

namespace EditorPlugins.Scene.Presets
{
	public interface IPresetItem
	{
		void SetOwner(ScenePreset _preset);
		EditorSceneObject GetComponentObject();
	}
}
