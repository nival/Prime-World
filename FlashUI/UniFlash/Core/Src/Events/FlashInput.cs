#define USING_CUSTOM_CURSOR

using System.Collections.Generic;
using Flash.Utils;
using FlashView.Utils;
using Native;
using UnityEngine;
using ViewModel.Utils;

namespace Flash
{
  public static class FlashInput
  {
    private const string CURSOR_NAME = "normal";
    
    /// Using for modifiers keys (e.g. Shift) cache    
    private static KeyCode _modifierCode = KeyCode.None;
    private static UnityEngine.EventType _modifierType = UnityEngine.EventType.KeyDown;

    private static bool _enabled = true;
    public static bool Enabled
    {
      get { return _enabled; }
      set { _enabled = value; }
    }
    private static Vector2 _mousePosition;
    public static Vector2 MousePosition
    {
      get
      {
        //Profiler.BeginSample("GET_MOUSE_POSITION");
          /*
        if ( Application.platform == RuntimePlatform.WindowsPlayer || Application.platform == RuntimePlatform.OSXPlayer )
        {
          NativeCode.GetClientMousePosition( ref _point );
          _mousePosition = _point;
        }
        else*/
        {
          _mousePosition.x = UnityEngine.Input.mousePosition.x / UniFlashPlayer.Scale;
          _mousePosition.y = (Screen.height - UnityEngine.Input.mousePosition.y) / UniFlashPlayer.Scale;
        }

        //Profiler.EndSample();

        return _mousePosition;
      }
    }
    private static List<InteractiveObject> _mouseFocusChain = new List<InteractiveObject>();
    public static List<InteractiveObject> MouseFocusChain
    {
      get { return _mouseFocusChain; }
    }
    private static List<InteractiveObject> _mouseDownChain = new List<InteractiveObject>();
    public static List<InteractiveObject> MouseDownChain
    {
      get { return _mouseDownChain; }
    }
    private static InteractiveObject _clickObject = UniFlashPlayer.MainStage;
    private static InteractiveObject _mouseFocus = UniFlashPlayer.MainStage;
    public static InteractiveObject MouseFocus
    {
      get { return _mouseFocus; }
      set { _mouseFocus = value; }
    }
    private static InteractiveObject _mouseFocusPrev = UniFlashPlayer.MainStage;
    private static DisplayObject _topmostObject;
    public static DisplayObject TopmostObject
    {
      get { return _topmostObject; }
      set { _topmostObject = value; }
    }
    public static bool IsCursorOverControl
    {
      get { return _topmostObject != null; }
    }
    private static UnityEngine.Event _currentEvent = new UnityEngine.Event();
    public static UnityEngine.Event CurrentEvent
    {
      get { return _currentEvent; }
    }
    private static CursorState _cursorState;
    private static string _cursor = EnumUtils.GetEnumDescription( CursorType.Normal );
    private static bool _curFullscreen = Screen.fullScreen;


    public static void SetCursor( string cursor )
    {
      _cursor = cursor;
      //if ( Application.platform != RuntimePlatform.WindowsPlayer && Application.platform != RuntimePlatform.OSXPlayer )
        //return;
      //Screen.showCursor = false;
      //Cursor.SetCursor(null, Vector2.zero, CursorMode.Auto);
      //NativeCode.SetCastleCursor( _cursor );
      if (Application.isEditor) return;
      CursorsManager.SetCastleCursor(_cursor);
      //Debug.Log("Setting cursor = " + _cursor);
    }

    public static void Update()
    {
#if USING_CUSTOM_CURSOR
      CursorUpdate();
#endif

      #region Modifier keys cache
      /// http://answers.unity3d.com/questions/252563/why-is-this-script-showing-all-keycodes-except-shi.html
      if ( UnityEngine.Input.GetKeyDown( KeyCode.LeftShift ) )
      {
        _modifierType = UnityEngine.EventType.KeyDown;
        _modifierCode = KeyCode.LeftShift;
      }
      if ( UnityEngine.Input.GetKeyDown( KeyCode.RightShift ) )
      {
        _modifierType = UnityEngine.EventType.KeyDown;
        _modifierCode = KeyCode.RightShift;
      }

      if ( UnityEngine.Input.GetKeyUp( KeyCode.LeftShift ) )
      {
        _modifierType = UnityEngine.EventType.KeyUp;
        _modifierCode = KeyCode.LeftShift;
      }
      if ( UnityEngine.Input.GetKeyUp( KeyCode.RightShift ) )
      {
        _modifierType = UnityEngine.EventType.KeyUp;
        _modifierCode = KeyCode.RightShift;
      }
      #endregion

      Input.Reset();

      if (UnityUI.DeployUtils.UIRoot != null)
        UnityUI.DeployUtils.UIRoot.UpdateInput(_mouseFocus == UniFlashPlayer.MainStage);

      if ( _currentEvent == null || _currentEvent.type == UnityEngine.EventType.Ignore || !_enabled )
        return;
      
      // OUT + OVER
      if ( _mouseFocus != _mouseFocusPrev )
      {
        // update focus chain
        _mouseFocusChain.Clear();
        InteractiveObject current = _mouseFocus;
        while ( current != null )
        {
          _mouseFocusChain.Add( current );
          current = current.Parent;
        }
        
        InteractiveObject deepOver = null;
        // out
        if ( _mouseFocusPrev != null )
          ( (IInteractive)_mouseFocusPrev ).OnMouseOutInternal( CreateMouseEvent( MouseButton.None, _mouseFocusPrev, EventType.MOUSE_OUT ), ref deepOver );
        // over
        ( (IInteractive)_mouseFocus ).OnMouseOverInternal( CreateMouseEvent( MouseButton.None, _mouseFocus, EventType.MOUSE_OVER ), deepOver );
      }

      // DOWN 
      bool buttonDown = false;
      MouseButton button = MouseButton.None;
      if ( UnityEngine.Input.GetMouseButtonDown( 0 ) )
      {
        buttonDown = true;
        button = MouseButton.Left;
      }
      else if ( UnityEngine.Input.GetMouseButtonDown( 1 ) )
      {
        buttonDown = true;
        button = MouseButton.Right;
      }
      else if ( UnityEngine.Input.GetMouseButtonDown( 2 ) )
      {
        buttonDown = true;
        button = MouseButton.Middle;
      }
      // ---
      if ( buttonDown )
      {
        // update down chain
        _mouseDownChain.Clear();
        InteractiveObject current = _mouseFocus;
        while ( current != null )
        {
          _mouseDownChain.Add( current );
          current = current.Parent;
        }

        // Focus
        UniFlashPlayer.MainStage.Focus = _mouseFocus;

        if (_currentEvent.clickCount == 2)
        {
          ((IInteractive) _mouseFocus).OnMouseDoubleClickInternal(CreateMouseEvent(button, _mouseFocus,
            EventType.DOUBLE_CLICK));
        }
        else
        {
          ((IInteractive)_mouseFocus).OnMouseDownInternal(CreateMouseEvent(button, _mouseFocus, EventType.MOUSE_DOWN));
        }
      }

      // UP
      bool buttonUp = false;
      button = MouseButton.None;
      if ( UnityEngine.Input.GetMouseButtonUp( 0 ) )
      {
        buttonUp = true;
        button = MouseButton.Left;
      }
      else if ( UnityEngine.Input.GetMouseButtonUp( 1 ) )
      {
        buttonUp = true;
        button = MouseButton.Right;
      }
      else if ( UnityEngine.Input.GetMouseButtonUp( 2 ) )
      {
        buttonUp = true;
        button = MouseButton.Middle;
      }
      // ---
      if ( buttonUp )
      {
        bool found = false;
        ( (IInteractive)_mouseFocus ).OnMouseUpInternal( CreateMouseEvent( button, _mouseFocus, EventType.MOUSE_UP ), ref _clickObject, ref found );

        // click
        if ( found )
        {
          ( (IInteractive)_clickObject ).OnMouseClickInternal( CreateMouseEvent( button, _clickObject, EventType.CLICK ) );
        }
        _clickObject = UniFlashPlayer.MainStage;

        _mouseDownChain.Clear();
      }

      // WHEEL
      if ( _currentEvent.type == UnityEngine.EventType.ScrollWheel )
      {
        ( (IInteractive)_mouseFocus ).OnMouseWheelInternal( CreateMouseEvent( MouseButton.None, _mouseFocus, EventType.MOUSE_WHEEL ) );
      }

      // MOVE
      if ( _currentEvent.type == UnityEngine.EventType.MouseMove )
      {
        ( (IInteractive)_mouseFocus ).OnMouseMoveInternal( CreateMouseEvent( MouseButton.None, _mouseFocus, EventType.MOUSE_MOVE ) );
      }

      // DRAG
      if ( _currentEvent.type == UnityEngine.EventType.MouseDrag )
      {
        ( (IInteractive)_mouseFocus ).OnMouseDragInternal( CreateMouseEvent( MouseButton.None, _mouseFocus,
                                                                          EventType.MOUSE_DRAG ) );
      }
    }
    public static void Reset()
    {
      if ( !_enabled )
        return;

      if ( _mouseDownChain.Count > 0 && _mouseDownChain[0] != UniFlashPlayer.MainStage )
      {
        Input.CloseInpuAxes();
      }

      _mouseFocusPrev = _mouseFocus;
      _mouseFocus = UniFlashPlayer.MainStage;
      _topmostObject = null;
    }

    public static void OnGUI()
    {
      if ( !_enabled )
        return;

      _currentEvent = UnityEngine.Event.current.Clone();

      /// Checks modifier keys cache
      if(_modifierCode != KeyCode.None)
      {
        _currentEvent.keyCode = _modifierCode;
        _currentEvent.type = _modifierType;

        /// Reset modifiers cache
        _modifierCode = KeyCode.None;
      }

      if (_currentEvent.type == UnityEngine.EventType.Layout ||
          _currentEvent.type == UnityEngine.EventType.Repaint ||
          _currentEvent.type == UnityEngine.EventType.Ignore)
      {
        return;
      }

      //Focus Input
      if ( _currentEvent.type == UnityEngine.EventType.KeyDown )
      {
        ( (IInteractive)UniFlashPlayer.MainStage.Focus ).OnGetEventInternal( new Event( EventType.KEY_DOWN, true, _currentEvent ) );
      }
      if ( _currentEvent.type == UnityEngine.EventType.KeyUp )
      {
        ( (IInteractive)UniFlashPlayer.MainStage.Focus ).OnGetEventInternal( new Event( EventType.KEY_UP, true, _currentEvent ) );
      }

      // Discard all events if we take the event
      if ( _currentEvent.type == UnityEngine.EventType.Used )
        UnityEngine.Event.current.Use();

      // Принудительный вызов, чтобы не пропустить важные события
      if (_currentEvent.type == UnityEngine.EventType.MouseDrag)
      {
        ((IInteractive)_mouseFocus).OnMouseDragInternal(CreateMouseEvent(MouseButton.None, _mouseFocus,
                                                                          EventType.MOUSE_DRAG));
      }

      if (_currentEvent.type == UnityEngine.EventType.MouseMove)
      {
        Debug.Log("SSSSFDKFQWEKFL");
        ((IInteractive)_mouseFocus).OnMouseMoveInternal(CreateMouseEvent(MouseButton.None, _mouseFocus, EventType.MOUSE_MOVE));
      }

    }
    public static void InvalidateCursorState()
    {
      _cursorState = CursorState.Outbound;
    }

    private static void CursorUpdate()
    {
      if ( Application.platform != RuntimePlatform.WindowsPlayer && Application.platform != RuntimePlatform.OSXPlayer )
        return;


      if ( Input.mousePosition.x < 0 || Input.mousePosition.x > Screen.width
        || Input.mousePosition.y < 0 || Input.mousePosition.y > Screen.height )
      {
        /// Cursor out of screen
        if (Lobby.Configs.Config.cursor_mode == 0 && _cursorState == CursorState.Inbound)
            CursorsManager.SetCastleCursor(null);
        _cursorState = CursorState.Outbound;
      }
      else
      {
        // Cursor inside screen
        if (Lobby.Configs.Config.cursor_mode == 0)// && _cursorState == CursorState.Outbound)
          NativeCode.SetCastleCursor(_cursor);
        if ( _curFullscreen != Screen.fullScreen )
          _curFullscreen = Screen.fullScreen;
        _cursorState = CursorState.Inbound;
      }
    }
    private static MouseEvent CreateMouseEvent( MouseButton button, InteractiveObject focus, string type )
    {
      float delta = 0;

      if ( _currentEvent.type == UnityEngine.EventType.ScrollWheel )
        delta = _currentEvent.delta.y;
      Vector2 localPos = Vector2.zero;
      if ( focus != null )
        localPos = focus.GlobalToLocal( _mousePosition );

      MouseEvent result = new MouseEvent( button, delta, localPos, _mousePosition, type );

      return result;
    }

    /// <summary>
    /// Custom flash input
    /// </summary>
    public static class Input
    {
      public static UnityEngine.Event Event
      {
        get { return _currentEvent; }
      }
      public static Vector3 mousePosition
      {
        get { return UnityEngine.Input.mousePosition; }
      }
      public static bool anyKey
      {
        get { return UnityEngine.Input.anyKey; }
      }
      public static bool anyKeyDown
      {
        get { return UnityEngine.Input.anyKeyDown; }
      }
      public static string inputString
      {
        get { return UnityEngine.Input.inputString; }
      }
      private static bool _closed;
      public static bool Closed
      {
        get { return _closed; }
      }

      public static float GetAxis( string axisName )
      {
        return !_closed ? UnityEngine.Input.GetAxis( axisName ) : 0;
      }
      public static float GetAxisRaw( string axisName )
      {
        return !_closed ? UnityEngine.Input.GetAxisRaw( axisName ) : 0;
      }
      public static bool GetButton( string buttonName )
      {
        return !_closed ? UnityEngine.Input.GetButton( buttonName ) : false;
      }
      public static bool GetButtonDown( string buttonName )
      {
        return !_closed ? UnityEngine.Input.GetButtonDown( buttonName ) : false;
      }
      public static bool GetButtonUp( string buttonName )
      {
        return !_closed ? UnityEngine.Input.GetButtonUp( buttonName ) : false;
      }
      public static bool GetKey( string name )
      {
        return !_closed ? UnityEngine.Input.GetKey( name ) : false;
      }
      public static bool GetKey( KeyCode key )
      {
        return !_closed ? UnityEngine.Input.GetKey( key ) : false;
      }
      public static bool GetKeyDown( string name )
      {
        return !_closed ? UnityEngine.Input.GetKeyDown( name ) : false;
      }
      public static bool GetKeyDown( KeyCode key )
      {
        return !_closed ? UnityEngine.Input.GetKeyDown( key ) : false;
      }
      public static bool GetKeyUp( string name )
      {
        return !_closed ? UnityEngine.Input.GetKeyUp( name ) : false;
      }
      public static bool GetKeyUp( KeyCode key )
      {
        return !_closed ? UnityEngine.Input.GetKeyUp( key ) : false;
      }
      public static bool GetMouseButton( int button )
      {
        return !_closed ? UnityEngine.Input.GetMouseButton( button ) : false;
      }
      public static bool GetMouseButtonDown( int button )
      {
        return !_closed ? UnityEngine.Input.GetMouseButtonDown( button ) : false;
      }
      public static bool GetMouseButtonUp( int button )
      {
        return !_closed ? UnityEngine.Input.GetMouseButtonUp( button ) : false;
      }
      public static void ResetInputAxes()
      {
        UnityEngine.Input.ResetInputAxes();
      }
      public static void Reset()
      {
        _closed = false;
      }
      public static void CloseInpuAxes()
      {
        _closed = true;
      }
    }
  }

  public enum MouseButton
  {
    Left,
    Right,
    Middle,
    None
  }

  public enum MouseCursorType
  {
    Arrow,
    Text
  }

  public enum CursorState
  {
    Outbound,
    Inbound
  }
}
