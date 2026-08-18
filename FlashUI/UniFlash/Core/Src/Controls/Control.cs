using System.Collections.Generic;
using UnityEngine;

namespace Flash.Controls
{
	public class Control : MovieClip
	{
		private Rect _mouseBounds;

    //пока контекстное меню по правой кнопке есть мало где
	 /* private List<ContextMenuItem> _contextMenuItems = new List<ContextMenuItem>();

    public void SetContextMenu( List<ContextMenuItem> contextMenu )
    {
      _contextMenuItems = contextMenu;
    }*/

		/// <summary>
		/// Область контрола которая реагирует на мышь
		/// </summary>
		public Rect MouseBounds
		{
			get { return _mouseBounds; }
		}

		protected override void Init()
		{
			base.Init();

			StopChildren();
			ApplyHitTest();
		}

		private void ApplyHitTest()
		{
			InteractiveObject hitTest = GetChildByName<InteractiveObject>( "hit_test" );

			SetMouseBounds( hitTest );

			if ( hitTest == null )
				return;

			hitTest.Alpha = 0;
			MouseEnabled = false;

			foreach ( Frame frame in TimeLine )
			{
				foreach ( DisplayInstance inst in frame )
				{
					if ( inst.DisplayObject == hitTest )//ignore hitTest object
						continue;

					InteractiveObject interactiveObject = inst.DisplayObject as InteractiveObject;

					if ( interactiveObject != null )
					{
						if ( interactiveObject is DisplayObjectContainer )
							( (DisplayObjectContainer)interactiveObject ).MouseChildren = false;

						interactiveObject.MouseEnabled = false;
					}
				}
			}

			//Debug.Log( "HitTest enabled for '" + Parent.Name + "." + Name + "'" );
		}

		private void SetMouseBounds( DisplayObject hitTest )
		{
			_mouseBounds = hitTest == null
													? new Rect( X, Y, Width, Height )
													: new Rect( hitTest.X, hitTest.Y, hitTest.Width, hitTest.Height );
		}

		protected override void OnMouseUp( MouseEvent args )
		{
			base.OnMouseUp( args );

			DispatchEvent( new DropEvent() );
		}


    protected override void OnMouseClick( MouseEvent args )
    {
      /*if ( args.Button == MouseButton.Right && _contextMenuItems.Count != 0 )
      {
        DispatchEvent( new ContextMenuEvent( _contextMenuItems ) );
        return;
      }*/

      base.OnMouseClick( args );
    }
	}
}
