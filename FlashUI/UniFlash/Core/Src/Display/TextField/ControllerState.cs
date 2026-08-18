using System.Collections.Generic;
using UnityEngine;

namespace Flash
{
  internal class Controller_FSM
  {
    public const string TYPE_STATE = "type";
    public const string SELECT_STATE = "select";
    public const string HAS_SELECTION_STATE = "hasSelectionState";
    public const string HAS_SELECTION_UNFOCUSED_STATE = "hasSelectionUnfocusedState";

    private readonly Controller_TextField _controller;
    private Dictionary<string, ControllerState> _states = new Dictionary<string, ControllerState>();
    private ControllerState _currentState;
    private string _previousState;
    public string PreviousState
    {
      get { return _previousState; }
    }
    public Controller_FSM( Controller_TextField controller )
    {
      _controller = controller;
      _states.Add( TYPE_STATE, new TypeState( _controller, TYPE_STATE, this ) );
      _states.Add( SELECT_STATE, new SelectState( _controller, SELECT_STATE, this ) );
      _states.Add( HAS_SELECTION_STATE, new HasSelectionState( _controller, HAS_SELECTION_STATE, this ) );
      _states.Add( HAS_SELECTION_UNFOCUSED_STATE, new HasSelectionUnfocused( _controller, HAS_SELECTION_UNFOCUSED_STATE, this ) );
      GoToState( TYPE_STATE, null );
    }
    public void GoToState( string stateName, Event e )
    {
      ControllerState state = _states[stateName];
      if ( state == _currentState )
        return;

      // Transitions
      if ( _currentState != null )
        if ( state.Name == HAS_SELECTION_UNFOCUSED_STATE && _currentState.Name != HAS_SELECTION_STATE )
          return;

      if ( _currentState != null )
        _currentState.OnExit( e );

      _previousState = _currentState != null ? _currentState.Name : string.Empty;
      _currentState = state;

      if ( _currentState != null )
        _currentState.OnEnter( e );
    }

    public void ProcessEvent( Event e )
    {
      _currentState.OnUpdate( e );
    }
  }

  internal class HasSelectionUnfocused : ControllerState
  {
    public HasSelectionUnfocused( Controller_TextField controller, string name, Controller_FSM stateMachine )
      : base( controller, name, stateMachine )
    {
    }

    public override void OnEnter( Event e )
    {
      if ( _controller.SelectTextOnFocus )
        _controller.ResetSelection();
    }
  }

  internal class HasSelectionState : ControllerState
  {
    public HasSelectionState( Controller_TextField controller, string name, Controller_FSM stateMachine )
      : base( controller, name, stateMachine )
    {
    }
    public override void OnUpdate( Event e )
    {
      if ( e.UnityEvent == null )
        return;

      if ( _controller.TextField.TextFieldType == TextFieldType.ReadOnly )
      {
        if ( e.UnityEvent.keyCode == KeyCode.C && e.UnityEvent.control )
          _controller.PushToClipBoard();
        return;
      }

      switch ( e.UnityEvent.keyCode )
      {
      case KeyCode.Backspace:
        _controller.RemoveSelected();
        _stateMachine.GoToState( Controller_FSM.TYPE_STATE, e );
        break;
      case KeyCode.Delete:
        _controller.RemoveSelected();
        _stateMachine.GoToState( Controller_FSM.TYPE_STATE, e );
        break;
      case KeyCode.Home:
        _controller.ResetSelection();
        _controller.CarriagePosToHome();
        _stateMachine.GoToState( Controller_FSM.TYPE_STATE, e );
        break;
      case KeyCode.End:
        _controller.ResetSelection();
        _controller.CarriagePosToEnd();
        _stateMachine.GoToState( Controller_FSM.TYPE_STATE, e );
        break;
      case KeyCode.C:
        if ( e.UnityEvent.control )
          _controller.PushToClipBoard();
        break;
      case KeyCode.V:
        if ( e.UnityEvent.control )
        {
          _controller.RemoveSelected();
          _controller.PopFromClipBoard();
          _stateMachine.GoToState( Controller_FSM.TYPE_STATE, e );
        }
        break;
      case KeyCode.X:
        if ( e.UnityEvent.control )
        {
          _controller.PushToClipBoard();
          _controller.RemoveSelected();
          _stateMachine.GoToState( Controller_FSM.TYPE_STATE, e );
        }
        break;
      default:
        if ( e.UnityEvent.character != '\0' )
        {
          _controller.RemoveSelected();
          _controller.Text = _controller.Text.Insert( _controller.CarriagePos, new string( e.UnityEvent.character, 1 ) );
          _controller.CarriagePos++;
          _stateMachine.GoToState( Controller_FSM.TYPE_STATE, e );
          break;
        }

        if ( e.UnityEvent.keyCode == KeyCode.LeftArrow ||
          e.UnityEvent.keyCode == KeyCode.RightArrow ||
          e.UnityEvent.keyCode == KeyCode.UpArrow ||
          e.UnityEvent.keyCode == KeyCode.DownArrow )
        {
          _controller.ResetSelection();
          _stateMachine.GoToState( Controller_FSM.TYPE_STATE, e );
          break;
        }
        break;
      }
    }
  }

  internal class SelectState : ControllerState
  {
    public SelectState( Controller_TextField controller, string name, Controller_FSM stateMachine ) : base( controller, name, stateMachine ) { }
    public override void OnEnter( Event e )
    {
      base.OnEnter( e );
      MouseEvent mouseEvent = e as MouseEvent;
      if ( mouseEvent != null )
        _controller.SaveStartSelectPos( mouseEvent.Local );
      else
        _controller.SaveStartSelectPos( _controller.CarriagePos );
    }
    public override void OnExit( Event e )
    {
      base.OnExit( e );
      MouseEvent mouseEvent = e as MouseEvent;
      if ( mouseEvent != null )
      {
        _controller.SaveEndSelectPos( mouseEvent.Local );
        _controller.CarriagePos = _controller.GetCarriagePosition( mouseEvent.Local );
      }
    }
    public override void OnUpdate( Event e )
    {
      MouseEvent mouseEvent = e as MouseEvent;
      if ( mouseEvent != null )
      {
        _controller.SaveEndSelectPos( mouseEvent.Local );
        _controller.CarriagePos = _controller.GetCarriagePosition( mouseEvent.Local );
      }
      else if ( e.UnityEvent != null )
      {
        if ( !e.UnityEvent.shift )
        {
          _stateMachine.GoToState( Controller_FSM.HAS_SELECTION_STATE, e );
          _stateMachine.ProcessEvent( e );
          return;
        }

        switch ( e.UnityEvent.keyCode )
        {
        case KeyCode.LeftArrow:
          _controller.CarriagePos--;
          _controller.SaveEndSelectPos( _controller.CarriagePos );
          break;
        case KeyCode.RightArrow:
          _controller.CarriagePos++;
          _controller.SaveEndSelectPos( _controller.CarriagePos );
          break;
        case KeyCode.DownArrow:
          _controller.DownCarriage();
          _controller.SaveEndSelectPos( _controller.CarriagePos );
          break;
        case KeyCode.UpArrow:
          _controller.UpCarriage();
          _controller.SaveEndSelectPos( _controller.CarriagePos );
          break;
        }
      }
    }
  }

  internal class TypeState : ControllerState
  {
    public TypeState( Controller_TextField controller, string name, Controller_FSM stateMachine ) : base( controller, name, stateMachine ) { }
    private bool _preventEvent = false;

    public override void OnEnter( Event e )
    {
      bool returnedFromEditing = !string.IsNullOrEmpty( _stateMachine.PreviousState ) &&
                                 _stateMachine.PreviousState == Controller_FSM.HAS_SELECTION_STATE;
      if ( !returnedFromEditing && _controller.SelectTextOnFocus )
      {
        _controller.SelectAll();
        _preventEvent = true;
      }
    }

    public override void OnUpdate( Event e )
    {
      if ( _preventEvent && e.EventType != EventType.GET_FOCUS )
      {
        _preventEvent = false;
        return;
      }

      if ( e.EventType == EventType.GET_FOCUS )
        if ( _controller.SelectTextOnFocus )
        {
          _controller.SelectAll();
          _preventEvent = true;
        }

      // Double click);
      if ( e.EventType == EventType.DOUBLE_CLICK )
      {
        MouseEvent mouseEvent = (MouseEvent)e;
        _controller.CarriagePos = _controller.GetCarriagePosition( mouseEvent.Local );
        _controller.SelectAll();
        return;
      }

      // Carriage position
      if ( e.EventType == EventType.MOUSE_DOWN )
      {
        MouseEvent mouseEvent = (MouseEvent)e;
        _controller.CarriagePos = _controller.GetCarriagePosition( mouseEvent.Local );
        _controller.ResetSelection();
        return;
      }

      if ( e.UnityEvent == null )
        return;

      if ( _controller.TextField.TextFieldType == TextFieldType.ReadOnly )
        return;

      switch ( e.UnityEvent.keyCode )
      {
      case KeyCode.Backspace:
        if ( _controller.CarriagePos > 0 )
        {
          _controller.Text = _controller.Text.Remove( _controller.CarriagePos - 1, 1 );
          if ( _controller.CarriagePos < _controller.CharInfos.Count - 1 )
            _controller.CarriagePos--;

          // Offset);
          if ( !_controller.MultiLine )
          {
            Matrix4x4 preTransform = _controller.TextField.PreTransform;
            if ( preTransform[0, 3] < 0 )
            {
              preTransform[0, 3] += _controller.CharInfos[_controller.CarriagePos - 1].X - _controller.CharInfos[_controller.CarriagePos - 2].X;
              _controller.TextField.PreTransform = preTransform;
            }
          }
        }
        break;
      case KeyCode.Delete:
        if ( _controller.CarriagePos < _controller.Text.Length )
          _controller.Text = _controller.Text.Remove( _controller.CarriagePos, 1 );
        break;
      case KeyCode.LeftArrow:
        _controller.CarriagePos--;
        break;
      case KeyCode.RightArrow:
        _controller.CarriagePos++;
        break;
      case KeyCode.DownArrow:
        _controller.DownCarriage();
        break;
      case KeyCode.UpArrow:
        _controller.UpCarriage();
        break;
      case KeyCode.Home:
        _controller.CarriagePosToHome();
        break;
      case KeyCode.End:
        _controller.CarriagePosToEnd();
        break;
      case KeyCode.V:
        if ( e.UnityEvent.control )
          _controller.PopFromClipBoard();
        break;
      default:
        if ( e.UnityEvent.character != '\0' )
        {
          _controller.Text = _controller.Text.Insert( _controller.CarriagePos, new string( e.UnityEvent.character, 1 ) );
          _controller.CarriagePos++;
        }
        break;
      }
    }
  }

  internal class ControllerState
  {
    protected Controller_TextField _controller;
    protected string _name;
    public string Name { get { return _name; } }
    protected Controller_FSM _stateMachine;

    public ControllerState( Controller_TextField controller, string name, Controller_FSM stateMachine )
    {
      _controller = controller;
      _name = name;
      _stateMachine = stateMachine;
    }
    public virtual void OnEnter( Event e )
    {
    }
    public virtual void OnExit( Event e )
    {
    }
    public virtual void OnUpdate( Event e )
    {
    }
  }
}

