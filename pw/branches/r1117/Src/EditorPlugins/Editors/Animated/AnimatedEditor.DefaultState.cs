using System.Collections.Generic;
using System.Windows.Forms;
using EditorLib.Binds;

namespace EditorPlugins.Editors.Animated
{
	public partial class AnimatedEditor
	{
		private class DefaultState : IState
		{
			private readonly AnimatedEditor owner = null;

			private readonly Bind panX;
			private readonly Bind panY;
			private readonly Bind zoom;

			public DefaultState( AnimatedEditor owner, BindsManager bindsManager )
			{
				this.owner = owner;

        panX = bindsManager.RegisterBind( GetType().ToString(), "panX",
					new BindConfig { mouseAxis = MouseAxis.X, mouseButtons = MouseButtons.Middle, keys = new List<Keys>() { Keys.Menu }, deltaSpeed = 1 } );

        panY = bindsManager.RegisterBind( GetType().ToString(), "panY",
					new BindConfig { mouseAxis = MouseAxis.Y, mouseButtons = MouseButtons.Middle, keys = new List<Keys>() { Keys.Menu }, deltaSpeed = -1 } );

        zoom = bindsManager.RegisterBind( GetType().ToString(), "zoom",
					new BindConfig { mouseAxis = MouseAxis.X, mouseButtons = MouseButtons.Right, keys = new List<Keys>() { Keys.Menu }, deltaSpeed = 1 },
					new BindConfig { mouseAxis = MouseAxis.Wheel, deltaSpeed = 20 } );
			}

			public void Apply( bool cancel )
			{
			}

			public void Update()
			{
				owner.Pan( panX.Delta, panY.Delta );
        owner.Zoom( ( zoom.Delta < 0 ) ? ( 1.0f / ( 1.0f + zoom.Delta * 0.005f ) ) : ( 1.0f - zoom.Delta * 0.005f ) );
			}
		}
	}
}
