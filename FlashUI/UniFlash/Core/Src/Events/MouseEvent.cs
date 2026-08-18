using UnityEngine;

namespace Flash
{
  public class MouseEvent : Event
  {
    private MouseButton _button = MouseButton.None;
    public MouseButton Button
    {
      get { return _button; }
    }
    private float _delta;
    public float Delta
    {
      get { return _delta; }
    }
    private Vector2 _local;
    public Vector2 Local
    {
      get { return _local; }
    }
    private Vector2 _stage;
    public Vector2 Stage
    {
      get { return _stage; }
    }

    public MouseEvent(MouseButton button, float delta, Vector2 local, Vector2 stage, string type)
      : base(type, true)
    {
      _button = button;
      _delta = delta;
      _local = local;
      _stage = stage;
    }
    public new string ToString()
    {
      return _button + " " + _delta + " " + _local + " " + _stage + " " + _eventType;
    }
  }
}
