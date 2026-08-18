using Unity.Components.SoundsManager;

namespace Flash.Controls
{
  [FramesCountConstraint( 4 )]
  public class Button : SystemTooltipControl
  {
    protected enum ButtonState
    {
      Up = 1,
      Over = 2,
      Down = 3,
      Disabled = 4,
    }

    private ButtonState _currentState = ButtonState.Up;

    private string _clickSound = Sound.Click;
    public string ClickSound
    {
      get { return _clickSound; }
      set { _clickSound = value; }
    }

    public virtual bool Enabled
    {
      get { return _currentState != ButtonState.Disabled; }
      set
      {
        if ( value && _currentState != ButtonState.Disabled )
          return;

        if ( !value && _currentState == ButtonState.Disabled )
          return;

        SetState( value ? ButtonState.Up : ButtonState.Disabled );
      }
    }

    public bool AllowMouseWheel { get; set; }
    public bool AllowRightClicks { get; set; }
    
    #region Overrided

    protected override void OnMouseClick( MouseEvent args )
    {
      base.OnMouseClick( args );

      //кнопки нажимаются только если они Enabled или по левому клику (если не разрешены правые клики)
      if ( Enabled && ( AllowRightClicks || args.Button == MouseButton.Left ) )
        return;
      
      args.StopPropagation();
    }

    protected override void OnMouseWheel( MouseEvent args )
    {
      base.OnMouseWheel( args );

      if ( !Enabled && !AllowMouseWheel )
        args.StopPropagation();
    }

    protected override void OnMouseUp( MouseEvent args )
    {
      base.OnMouseUp( args );
      SetStateAndHold( ButtonState.Over, args );
    }

    protected override void OnMouseDown( MouseEvent args )
    {
      base.OnMouseDown( args );

      if ( args.Button == MouseButton.Left || AllowRightClicks )
      {
        SetStateAndHold( ButtonState.Down, args );

        if ( string.IsNullOrEmpty( ClickSound ) || !Enabled )
          return;

        Sound.PlayUI( ClickSound );
      }
    }

    protected override void OnMouseOver( MouseEvent args )
    {
      base.OnMouseOver( args );
      SetStateAndHold( ButtonState.Over, args );
    }

    protected override void OnMouseOut( MouseEvent args )
    {
      base.OnMouseOut( args );
      SetStateAndHold( ButtonState.Up, args );
    }

    #endregion

    protected void UpdateButtonState()
    {
      SetState( _currentState );
    }

    private void SetState( ButtonState state )
    {
      //UnityEngine.Debug.Log( "## STATE: " + state );
      _currentState = state;
      int frame = GetFrame( _currentState );
      GotoAndStop( frame );
    }

    protected virtual int GetFrame( ButtonState state )
    {
      return (int)state;
    }

    /// <summary>
    /// Если кнопка Enabled, то меняет ее визуальный стейт. 
    /// В противном случае подавляет возбуждение собятия и выходит, отсавляя стейт прежним.
    /// </summary>
    /// <param name="state"></param>
    /// <param name="args"></param>
    private void SetStateAndHold( ButtonState state, MouseEvent args )
    {
      if ( Enabled )
        SetState( state );
      //else
      //  args.StopPropagation(); //останавливаем возникновение события
    }
  }
}
