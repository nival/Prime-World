using DBTypes;
using EditorNative.SceneElements.SceneObjects;
namespace EditorPlugins.Scene.Viewers
{
	public interface ISceneHierarchyPanelExtension
		: IResourceParametersPanelExtension<EditorSceneComponent>
	{
    void ShowComponent( EditorSceneComponent component, bool isManipulatorOff );
		void SelectLocator( Locator locator );
		void ApplyTrack( SceneObjectTrack _track );
    void SelectAABB();
    void SetQuat( Quat _quat );
	}
}
