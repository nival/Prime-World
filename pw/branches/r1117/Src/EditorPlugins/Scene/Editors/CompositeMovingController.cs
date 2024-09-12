using System.Collections;
using System.Collections.Generic;
using System.Drawing;
using EditorNative;
namespace EditorPlugins.Scene.Editors
{
	internal sealed class CompositeMovingController
	{
    private class ControllerDesc
    {
      public readonly IMovingController controller;
      public readonly Vector2 offset;

      public ControllerDesc( IMovingController controller, Vector2 offset )
      {
        this.controller = controller;
        this.offset = offset;
      }
    }

    private readonly List<ControllerDesc> descs;

		internal CompositeMovingController( Vector2 initial, IEnumerable<IMovingController> controllers)
		{
      descs = new List<ControllerDesc>();
			foreach (var controller in controllers)
				descs.Add(new ControllerDesc(controller, controller.TileCoordinates - initial));
		}
		

		internal void Move( bool nonTile )
		{
      foreach ( var desc in descs )
      {
        desc.controller.Move( desc.offset.X, desc.offset.Y, nonTile );
      }
		}
	}
}
