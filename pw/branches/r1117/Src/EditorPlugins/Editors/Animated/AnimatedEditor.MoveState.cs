using System;
using System.Drawing;
using System.Windows.Forms;
using EditorLib.Binds;
using System.Collections.Generic;

namespace EditorPlugins.Editors.Animated
{
	public partial class AnimatedEditor
	{
		private class MoveState : IState
		{
			private readonly AnimatedEditor owner = null;

			private readonly Bind moveX;
			private readonly Bind moveY;
			private readonly Bind straightMove;
			private readonly Bind sanpToGrid;

			private int x = 0;
			private int y = 0;

			public MoveState( AnimatedEditor owner, BindsManager bindsManager )
			{
				this.owner = owner;
        moveX = bindsManager.RegisterBind( GetType().ToString(), "moveX",
					new BindConfig { mouseAxis = MouseAxis.X, mouseButtons = MouseButtons.Left, deltaSpeed = -1 } );
        moveY = bindsManager.RegisterBind( GetType().ToString(), "moveY",
					new BindConfig { mouseAxis = MouseAxis.Y, mouseButtons = MouseButtons.Left, deltaSpeed = -1 } );
        straightMove = bindsManager.RegisterBind( GetType().ToString(), "straightMove", new BindConfig { keys = new List<Keys>() { Keys.ShiftKey } } );
        sanpToGrid = bindsManager.RegisterBind( GetType().ToString(), "sanpToGrid", new BindConfig { keys = new List<Keys>() { Keys.X } } );
			}

			public IState Activate()
			{
				owner.StoreValuesForSelectedKeys();
				x = 0;
				y = 0;
				return this;
			}

			public void Apply( bool cancel )
			{
				if ( cancel )
					owner.RestoreValuesForSelectedKeys();
			}

			public void Update()
			{
				x += moveX.Delta;
				y += moveY.Delta;

				if ( straightMove.IsActive )
				{
					if ( Math.Abs( x ) > Math.Abs( y ) )
						owner.MoveSelectedKeys( x, 0, sanpToGrid.IsActive);
					else
						owner.MoveSelectedKeys( 0, y, sanpToGrid.IsActive );
				}
				else
				{
          owner.MoveSelectedKeys( x, y, sanpToGrid.IsActive );
				}
			}
		}
	}
}
