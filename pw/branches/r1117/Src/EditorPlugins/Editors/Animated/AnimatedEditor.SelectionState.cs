using System;
using System.Drawing;
using System.Windows.Forms;
using EditorLib.Binds;
using System.Collections.Generic;

namespace EditorPlugins.Editors.Animated
{
	public partial class AnimatedEditor
	{
		private class SelectionState : IState
		{
			private readonly AnimatedEditor owner = null;

			private readonly Bind moveX;
			private readonly Bind moveY;
			private readonly Bind addSelection;
			private readonly Bind invertSelection;

			private int x0 = 0;
			private int y0 = 0;

			private int width = 0;
			private int height = 0;

			public SelectionState( AnimatedEditor owner, BindsManager bindsManager )
			{
				this.owner = owner;
        
        moveX = bindsManager.RegisterBind( GetType().ToString(), "moveX",
					new BindConfig { mouseAxis = MouseAxis.X, mouseButtons = MouseButtons.Left, deltaSpeed = -1 } );
        
        moveY = bindsManager.RegisterBind( GetType().ToString(), "moveY",
					new BindConfig { mouseAxis = MouseAxis.Y, mouseButtons = MouseButtons.Left, deltaSpeed = -1 } );
        
        addSelection = bindsManager.RegisterBind( GetType().ToString(), "addSelection", 
          new BindConfig { keys = new List<Keys> { Keys.ShiftKey } } );

        invertSelection = bindsManager.RegisterBind( GetType().ToString(), "invertSelection", 
          new BindConfig { keys = new List<Keys> { Keys.ControlKey } } );
			}

			public IState Activate( int x, int y )
			{
				x0 = x;
				y0 = y;

				width = 0;
				height = 0;

				return this;
			}

			public void Apply( bool cancel )
			{
				if ( !cancel )
				{
				  ApplySelectionAction action;
          
          if(addSelection.IsActive)
            action = ApplySelectionAction.Add;
          else if(invertSelection.IsActive)
            action = ApplySelectionAction.Invert;
          else
            action = ApplySelectionAction.Replace;
          
          owner.ApplySelection( action );
				}			

				owner.SelectionArea = new Rectangle();
			}

			public void Update()
			{
				width += moveX.Delta;
				height += moveY.Delta;

				int x = x0 + width;
				int y = y0 + height;

				// limit selection with visible area
				//@Ivn@TODO: play with realWidth, realHeight here
				//x = x < owner.VisibleArea.Left ? owner.VisibleArea.Left : ( x > owner.VisibleArea.Right ? owner.VisibleArea.Right : x );
				//y = y < owner.VisibleArea.Top ? owner.VisibleArea.Top : ( y > owner.VisibleArea.Bottom ? owner.VisibleArea.Bottom : y );

				//owner.SelectionArea = new RectangleF( x0, y0, realWidth, realHeight );
				owner.SelectionArea = new Rectangle( Math.Min( x0, x ), Math.Min( y0, y ), Math.Abs( width ), Math.Abs( height ) );
			}

			public bool HasModifiers 
      { 
        get 
        { 
          return addSelection.IsActive || invertSelection.IsActive; 
        } 
      }
		}
	}
}
