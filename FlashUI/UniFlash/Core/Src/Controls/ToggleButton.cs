using System;
using Flash.Utils;

namespace Flash.Controls
{
	[FramesCountConstraint(8)]
	public class ToggleButton : Button
	{
		// у ToggleButton 8 кадров
		// 1. Up								=		ButtonState.Up + !Cheked
		// 2. Over							=		ButtonState.Over + !Cheked
		// 3. Down							=		ButtonState.Down + !Cheked
		// 4. Disabled					=		ButtonState.Disabled + !Cheked
		// 5. UpSelected				=		ButtonState.Up + Checked
		// 6. OverSelected			=		ButtonState.Over + Checked
		// 7. DownSelected			=		ButtonState.Down + Checked
		// 8. DisabledSelected	=		ButtonState.Disabled + Checked

		public event EventHandler<EventArgs> CheckedChanged;

		private bool _checked;
		public virtual bool Checked
		{
			get { return Enabled && _checked; }
			set 
			{ 
          if (_checked == value)
            return;
					
          _checked = value;
					UpdateButtonState();
          EventHelper.Invoke( CheckedChanged, this );
      }
		}

		public bool AutoCheck { get; set; }

		public ToggleButton()
		{
			AutoCheck = true;
		}

	  public void Switch(MouseEvent args)
    {
      OnMouseClick(args);
	  }

	  public void OnnMouseOver(MouseEvent args)
	  {
	    OnMouseOver(args);
	  }

	  public void OnnMouseOut(MouseEvent args)
	  {
      OnMouseOut(args);
	  }

	  public void OnnMouseUp(MouseEvent args)
	  {
	    OnMouseUp(args);
	  }

	  public void OnnMouseDown(MouseEvent args)
	  {
	    OnMouseDown(args);
	  }

    #region Overrided

    protected override void OnMouseClick( MouseEvent args )
		{
			base.OnMouseClick( args );

			if (!Enabled || args.Button != MouseButton.Left)
				return;

      if (AutoCheck)
			  Checked = !Checked;
		}

		protected override int GetFrame( ButtonState state )
		{
			return Enabled && Checked ? (int)state + 4 : (int)state;
		}

		#endregion
	}
}
