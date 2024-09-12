namespace EditorPlugins.Scene.Editors
{
	partial class EditorControl
	{
		private sealed class ObjectAdditionState : EditorControlState
		{
			private AddEntityController controller;

			internal ObjectAdditionState( EditorControl editorControl, AddEntityController controller )
				: base ( editorControl )
			{
				this.controller = controller;
			}

      public override void OnUpdate()
			{
				var pick = EditorControl.pickLeft;
				if ( EditorControl.cancel.IsActive )
				{
					SetMainState();
				}
				else if ( pick.IsDeactivated )
				{
          var result = controller.OnAdd();
          if ( result != null )
          {
            controller = result;
						EditorControl.TileMap.PlaceObjects(controller.SceneObjects);
            SetMainState();
          }
				}
				else
				{
					controller.OnMove();
				}
			}

			protected override void OnDeactivated()
			{
				base.OnDeactivated();
				controller.OnCancel();
			}
		}
	}
}
