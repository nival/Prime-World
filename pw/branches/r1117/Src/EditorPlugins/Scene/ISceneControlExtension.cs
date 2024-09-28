using EditorLib.Binds;
using EditorNative.Manipulators;

namespace EditorPlugins.Scene
{
	public interface ISceneControlExtension
	{
		IObjectTransformControllersProvider TransformControllersProvider { get; }
		void AddBinds();
    BindsManager BindsManager { get; }
    string StatusLabel { set; }
	}
}
