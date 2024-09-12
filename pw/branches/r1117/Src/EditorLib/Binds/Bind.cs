using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace EditorLib.Binds
{
	public sealed class Bind : IBind
	{
    private readonly string section;
		private readonly string name;
    private List<BindConfig> configs;

		private bool active = false;
		private bool activated = false;
		private bool deactivated = false;
		private float delta = 0;

		public Bind( string section, string name, params BindConfig[] configs )
		{
      this.section = section;
			this.name = name;
			this.configs = new List<BindConfig>( configs );
		}

    private void Activate( bool _active )
    {
      if ( _active == active )
        return;

      active = _active;
			if ( active && !activated && Activated != null )
			{
				Activated();
			}
    	activated |= active;

      if ( !active && !deactivated && Deactivated != null )
        Deactivated();
      deactivated |= !active;
    }

    private void UpdateDelta( float _delta )
    {
      if ( _delta == 0.0f )
        return;

      delta += _delta;
      if ( DeltaChanged != null )
        DeltaChanged();
    }

    private void OnKeyAction( KeyEventArgs currentEvent, List<Keys> pressedKeys, bool down ,BindsManager manager)
    {
      foreach ( var config in configs )
      {
        if ( config.badKeys.Contains( currentEvent.KeyData & Keys.KeyCode ) && down )
        {
          Activate( false );
          continue;
        }

        if ( !config.keys.Contains( currentEvent.KeyData & Keys.KeyCode ) )
          continue;

        if ( !TestKeys(pressedKeys, config ) )
          continue;

				if ( !TestButtons( config.mouseButtons, manager.ActivedButton ) )
					continue;
				
        Activate( config.invertKey != down );

        if ( config.mouseButtons == MouseButtons.None && config.mouseAxis == MouseAxis.None )
          UpdateDelta( config.deltaSpeed );

        break;
      }
    }

    private void OnMouseButtonAction( MouseEventArgs currentEvent, List<Keys> pressedKeys, bool down )
    {
      foreach ( var config in configs )
      {
        if ( TestButtonsAndKeys( currentEvent, pressedKeys, config ) )
        {
          Activate( config.invertMouse != down );
          break;
        }
      }
    }

    private bool TestButtonsAndKeys( MouseEventArgs currentEvent, List<Keys> pressedKeys, BindConfig config )
    {
				return TestButtons(config.mouseButtons, currentEvent.Button) && TestKeys(pressedKeys, config);
    }

    private bool TestButtons( MouseButtons buttonsToTest, MouseButtons validButtonsSet )
    {
      return buttonsToTest == validButtonsSet || ( buttonsToTest != MouseButtons.None && ( buttonsToTest & validButtonsSet ) == buttonsToTest );
    }

    private bool TestKeys( List<Keys> pressedKeys, BindConfig config )
    {
			foreach ( Keys key in config.keys )
      {
        if ( !pressedKeys.Contains( key ) )
          return false;
      }

			if ( pressedKeys.Count > 0 && config.keys.Count == 0 && !config.ignoreKeys )
        return false;

      foreach ( Keys key in pressedKeys )
      {
        if ( config.badKeys.Contains( key ) )
        {
          return false;
        }
      }

      return true;
    }

		#region Internal methods

		internal void OnMouseMove( MouseEventArgs currentEvent, MouseEventArgs prevEvent, List<Keys> pressedKeys )
		{
			foreach ( var config in configs )
			{
				if ( TestButtonsAndKeys( currentEvent, pressedKeys, config ) )
				{
					if ( ( config.mouseAxis & MouseAxis.X ) == MouseAxis.X )
            UpdateDelta( -config.deltaSpeed * ( currentEvent.X - prevEvent.X ) );
          if ( ( config.mouseAxis & MouseAxis.Y ) == MouseAxis.Y )
            UpdateDelta( -config.deltaSpeed * ( currentEvent.Y - prevEvent.Y ) );
				}
			}
		}

		internal void OnMouseWheel( MouseEventArgs currentEvent, List<Keys> pressedKeys )
		{
			foreach ( var config in configs )
			{
        if ( TestKeys( pressedKeys, config ) && config.mouseAxis == MouseAxis.Wheel )
          UpdateDelta( config.deltaSpeed * ( currentEvent.Delta / 120 ) );
			}
		}

		internal void OnKeyDown( KeyEventArgs currentEvent, List<Keys> pressedKeys,BindsManager manager )
		{
			OnKeyAction( currentEvent, pressedKeys, true, manager );
		}

		internal void OnKeyUp( KeyEventArgs currentEvent, List<Keys> pressedKeys, BindsManager manager )
		{
			OnKeyAction( currentEvent, pressedKeys, false, manager );
		}

		internal void OnMouseDown( MouseEventArgs currentEvent, List<Keys> pressedKeys )
		{
			OnMouseButtonAction( currentEvent, pressedKeys, true );
		}

		internal void OnMouseUp( MouseEventArgs currentEvent, List<Keys> pressedKeys )
		{
			OnMouseButtonAction( currentEvent, pressedKeys, false );
		}

    internal void Reset()
    {
      delta = 0.0f;
      activated = false;
      deactivated = false;
    }

    internal List<BindConfig> Configs
    {
      get { return configs; }
      set { configs = value; }
    }

		#endregion

		#region Public properties and events

		public bool IsActive { get { return active; } set { active = value; } }
		public bool IsActivated { get { return activated; } }
		public bool IsDeactivated	{	get { return deactivated; } }
    public int Delta { get { return (int)Math.Round( delta ); } }

    public event Operation Activated;
    public event Operation Deactivated;
    public event Operation DeltaChanged;

    public string Name { get { return name; } }
    public string Section { get { return section; } }

    #endregion
	}
}
