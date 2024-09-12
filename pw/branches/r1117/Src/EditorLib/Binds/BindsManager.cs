using System.Collections.Generic;
using System.Windows.Forms;

namespace EditorLib.Binds
{
  public sealed class BindsManager
  {
    private readonly IEditorCommonApplication application;

    private readonly List<Bind> binds = new List<Bind>();
    private readonly List<Keys> pressedKeys = new List<Keys>();
    private MouseEventArgs prevMouseMoveEvent;
  	private MouseButtons activedButton = MouseButtons.None;
  	public MouseButtons ActivedButton
  	{
			get { return activedButton; }
  	}

    public BindsManager( IEditorCommonApplication application )
    {
      this.application = application;
    }

    #region Registration functions

    private void SaveBinds( BindsManagerConfig config, string section )
    {
      if ( ReferenceEquals( config, null ) )
        return;

      var configSection = config[section];
      foreach ( Bind bind in binds )
      {
        configSection[bind.Name] = bind.Configs;
      }
      config[section] = configSection;
    }

    private void LoadBinds( BindsManagerConfig config, string section )
    {
      if ( ReferenceEquals( config, null ) )
        return;

      var configSection = config[section];
      foreach ( string bindName in configSection.Keys )
      {
        Bind bind = binds.Find( b => b.Name == bindName && b.Section == section );
        if ( ReferenceEquals( bind, null ) )
        {
          bind = new Bind( section, bindName, configSection[bindName].ToArray() );
          binds.Add( bind );
        }
        else
        {
          bind.Configs = configSection[bindName];
        }
      }
    }

    public Bind RegisterBind( string section, string bindName, params BindConfig[] configs )
    {
      LoadBinds( application.Settings.Get<BindsManagerConfig>(), section );
      Bind bind = binds.Find( b => b.Name == bindName && b.Section == section );
      if ( ReferenceEquals( bind, null ) )
      {
        bind = new Bind( section, bindName, configs );
        binds.Add( bind );
      }
      return bind;
    }

    public Bind AssignBind( string section, string bindName, params BindConfig[] configs )
    {
      Bind bind = binds.Find( b => b.Name == bindName && b.Section == section );
      if ( ReferenceEquals( bind, null ) )
      {
        return RegisterBind( section, bindName, configs );
      }

      bind.Configs.Clear();
      bind.Configs.AddRange( configs );

      SaveBinds( application.Settings.Get<BindsManagerConfig>(), section );
      return bind;
    }

    public void ResetBind( string section, string bindName )
    {
      binds.RemoveAll( b => b.Name == bindName && b.Section == section );
    }

    public void ResetBinds( string section )
    {
      binds.RemoveAll( b => b.Section == section );
    }

    #endregion

    #region Mouse and keyboard handlers

    public void OnMouseMove( MouseEventArgs currentEvent )
    {
      binds.ForEach( bind => bind.OnMouseMove( currentEvent, prevMouseMoveEvent ?? currentEvent, pressedKeys ) );
      prevMouseMoveEvent = currentEvent;
    }

    public void OnMouseDown( MouseEventArgs currentEvent )
    {
    	activedButton = currentEvent.Button;
      binds.ForEach( bind => bind.OnMouseDown( currentEvent, pressedKeys ) );
    }

    public void OnMouseUp( MouseEventArgs currentEvent )
    {
    	activedButton = MouseButtons.None;
      binds.ForEach( bind => bind.OnMouseUp( currentEvent, pressedKeys ) );
    }

    public void OnMouseWheel( MouseEventArgs currentEvent )
    {
      binds.ForEach( bind => bind.OnMouseWheel( currentEvent, pressedKeys ) );
    }

    public void OnKeyDown( KeyEventArgs currentEvent )
    {
      Keys key = currentEvent.KeyData & Keys.KeyCode;
      if ( !pressedKeys.Contains( key ) )
        pressedKeys.Add( key );
      binds.ForEach( bind => bind.OnKeyDown( currentEvent, pressedKeys,this ) );
    }

    public void OnKeyUp( KeyEventArgs currentEvent )
    {
      Keys key = currentEvent.KeyData & Keys.KeyCode;
      if ( pressedKeys.Contains( key ) )
      {
        binds.ForEach( bind => bind.OnKeyUp( currentEvent, pressedKeys,this ) );
        pressedKeys.Remove( key );
      }
    }

    #endregion

    public void Update()
    {
      binds.ForEach( bind => bind.Reset() );
    }

    public void ResetPressedKeys()
    {
      foreach ( var key in pressedKeys )
      {
        KeyEventArgs currentEvent = new KeyEventArgs( key );
        binds.ForEach( bind => bind.OnKeyUp( currentEvent, pressedKeys, this ) );
      }
      pressedKeys.Clear();

      if (activedButton != MouseButtons.None)
      {
        activedButton = MouseButtons.None;
        MouseEventArgs currentEvent = new MouseEventArgs(activedButton, 0, 0, 0, 0);
        binds.ForEach(bind => bind.OnMouseUp(currentEvent, pressedKeys));
      }

    }
  }
}
