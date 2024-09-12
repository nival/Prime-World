using EditorNative;

namespace EditorPlugins.Scene.Editors
{
	public interface IDrawingController
	{
		void Draw( PickResult pickResult );
		void Erase( PickResult pickResult );
	}
}
