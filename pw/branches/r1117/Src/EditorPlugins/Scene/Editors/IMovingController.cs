using EditorNative;

namespace EditorPlugins.Scene.Editors
{
	public interface IMovingController
	{
		Vector2 TileCoordinates { get; }
		void Move( float offsetX, float offsetY, bool nonTile );
	}
}
