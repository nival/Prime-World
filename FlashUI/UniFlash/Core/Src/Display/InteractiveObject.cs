using System;
using UnityEngine;

namespace Flash
{
  public abstract class InteractiveObject : DisplayObject, IInteractive, IBindable
  {
    private bool _doubleClickEnabled;
    public bool DoubleClickEnabled
    {
      get { return _doubleClickEnabled; }
      set { _doubleClickEnabled = value; }
    }
    private ControlNode _controlNode;
    ControlNode IBindable.ControlNode
    {
      get { return _controlNode; }
      set { _controlNode = value; }
    }
    // Маркер о том ControlNode в ходе биндинга взят с Parent
    private bool _isTakenFromParent;
    bool IBindable.IsTakenFromParent
    {
      get { return _isTakenFromParent; }
      set { _isTakenFromParent = value; }
    }
    private ConstraintAttribute[] _constraints;
    ConstraintAttribute[] IBindable.Constraints
    {
      get { return _constraints; }
      set { _constraints = value; }
    }
    private bool _mouseEnabled = true;
    public bool MouseEnabled
    {
      get { return _mouseEnabled; }
      set { _mouseEnabled = value; }
    }

    public event EventHandler<MouseEvent> MouseDown;
    public event EventHandler<MouseEvent> MouseUp;
    public event EventHandler<MouseEvent> Click;
    public event EventHandler<MouseEvent> DoubleClick;
    public event EventHandler<MouseEvent> MouseOver;
    public event EventHandler<MouseEvent> MouseOut;
    public event EventHandler<MouseEvent> MouseWheel;
    public event EventHandler<MouseEvent> MouseDrag;
    public event EventHandler<MouseEvent> MouseMove;
    public event EventHandler GetFocus;
    public event EventHandler LostFocus;
    public event EventHandler<Event> GetEvent;

    #region NVI
    void IInteractive.StartInternal()
    {
      Start();
    }
    void IInteractive.OnMouseClickInternal(MouseEvent args)
    {
      DispatchEvent(args, OnMouseClick, Click);

      if (CanRiseEvent(args))
        ((IInteractive)Parent).OnMouseClickInternal(args);
    }
    void IInteractive.OnMouseDoubleClickInternal(MouseEvent args)
    {
      DispatchEvent(args, OnMouseDoubleClick, DoubleClick);

      if (CanRiseEvent(args))
        ((IInteractive)Parent).OnMouseDoubleClickInternal(args);
    }
    void IInteractive.OnMouseDownInternal(MouseEvent args)
    {
      DispatchEvent(args, OnMouseDown, MouseDown);

      if (CanRiseEvent(args))
        ((IInteractive)Parent).OnMouseDownInternal(args);
    }
    void IInteractive.OnMouseUpInternal(MouseEvent args, ref InteractiveObject clickObject, ref bool found)
    {
      // if is still searching
      if (!found && FlashInput.MouseDownChain.Contains(this))
      {
        clickObject = this;
        found = true;
      }

      DispatchEvent(args, OnMouseUp, MouseUp);

      if (CanRiseEvent(args))
      {
        ((IInteractive)Parent).OnMouseUpInternal(args, ref clickObject, ref found);
      }
    }
    void IInteractive.OnMouseOverInternal(MouseEvent args, InteractiveObject deepOver)
    {
      if (this != deepOver)
      {
        DispatchEvent(args, OnMouseOver, MouseOver);

        if (CanRiseEvent(args))
          ((IInteractive)Parent).OnMouseOverInternal(args, deepOver);
      }
    }
    void IInteractive.OnMouseOutInternal(MouseEvent args, ref InteractiveObject deepOver)
    {
      if (!FlashInput.MouseFocusChain.Contains(this))
      {
        DispatchEvent(args, OnMouseOut, MouseOut);

        if (CanRiseEvent(args))
          ((IInteractive)Parent).OnMouseOutInternal(args, ref deepOver);
      }
      else
      {
        deepOver = this;
      }
    }
    void IInteractive.OnMouseWheelInternal(MouseEvent args)
    {
      DispatchEvent(args, OnMouseWheel, MouseWheel);

      if (CanRiseEvent(args))
        ((IInteractive)Parent).OnMouseWheelInternal(args);
    }
    void IInteractive.OnMouseDragInternal(MouseEvent args)
    {
      DispatchEvent(args, OnMouseDrag, MouseDrag);

      if (CanRiseEvent(args))
        ((IInteractive)Parent).OnMouseDragInternal(args);
    }
    void IInteractive.OnMouseMoveInternal(MouseEvent args)
    {
      DispatchEvent(args, OnMouseMove, MouseMove);

      if (CanRiseEvent(args))
        ((IInteractive)Parent).OnMouseMoveInternal(args);
    }
    void IInteractive.InitInternal()
    {
      Init();
    }
    void IInteractive.OnGetFocusInternal()
    {
      OnGetFocus();

      if (GetFocus != null)
        GetFocus(this, null);
    }
    void IInteractive.OnLostFocusInternal()
    {
      OnLostFocus();

      if (LostFocus != null)
        LostFocus(this, null);
    }
    void IInteractive.OnGetEventInternal(Event args)
    {
      DispatchEvent(args, OnGetEvent, GetEvent);

      if (CanRiseEvent(args))
        ((IInteractive)Parent).OnGetEventInternal(args);
    }
    void IInteractive.ValidateBinding()
    {
      if (!_isTakenFromParent)
        _controlNode.ValidateBindChildren();
    }
    #endregion

    #region Virtual interface
    protected virtual void OnMouseDown(MouseEvent args)
    {

    }
    protected virtual void OnMouseUp(MouseEvent args)
    {

    }
    protected virtual void OnMouseOver(MouseEvent args)
    {

    }
    protected virtual void OnMouseOut(MouseEvent args)
    {

    }
    protected virtual void OnMouseClick(MouseEvent args)
    {

    }
    protected virtual void OnMouseDoubleClick(MouseEvent args)
    {

    }
    protected virtual void OnMouseWheel(MouseEvent args)
    {
    }
    protected virtual void OnMouseDrag(MouseEvent args)
    {
    }
    protected virtual void OnMouseMove(MouseEvent args)
    {
    }
    protected virtual void OnGetFocus()
    {
    }
    protected virtual void OnLostFocus()
    {
    }
    protected virtual void OnGetEvent(Event e)
    {
    }
    protected virtual void Start()
    {

    }
    public Bounds InitialLocalBounds { get; private set; }
    public Vector3 InitialPosition { get; private set; }
    public float InitialWidth { get; private set; }
    public float InitialHeight { get; private set; }
    protected virtual void Init()
    {
      InitialBounds = new Bounds(WorldBounds.LeftTop, WorldBounds.RightBottom);
      InitialLocalBounds = new Bounds(LocalBounds);
      InitialPosition = Position;
      InitialWidth = Width;
      InitialHeight = Height;
    }
    #endregion

    #region bindings

    // Update<X|Y|Bound|Scale>BindedTo<Right|Bottom|Center|Percent>

    #region pos

    // привязка X/Y к правой/нижней границе парента

    public void UpdateXBindedToRight()
    {
      UpdateXBindedToRight(Parent.InitialLocalBounds.Width);
    }
    public void UpdateXBindedToRight(float pw0)
    {
      X = Parent.LocalBounds.Width - (pw0 - InitialPosition.x);
    }

    public void UpdateYBindedToBottom()
    {
      UpdateYBindedToBottom(Parent.InitialLocalBounds.Height);
    }
    public void UpdateYBindedToBottom(float ph0)
    {
      Y = Parent.LocalBounds.Height - (ph0 - InitialPosition.y);
    }

    // привязка X/Y к правой/нижней границе парента (в %)

    public void UpdateXBindedToPercent()
    {
      X = InitialPosition.x * (Parent.LocalBounds.Width / Parent.InitialLocalBounds.Width);
    }

    public void UpdateRightXBindedToPercent()
    {
      var initialRightX = InitialPosition.x + InitialWidth;
      var rightX = initialRightX * (Parent.LocalBounds.Width / Parent.InitialLocalBounds.Width);
      X = rightX - Width;
    }

    //

    public void UpdateXBindedToCenter()
    {
      X = Parent.LocalBounds.Width / 2f - Width / 2f;
    }

    public void UpdateYBindedToCenter()
    {
      Y = Parent.LocalBounds.Height / 2f - Height / 2f;
    }

    //

    public void UpdateXBindedToXXX()
    {
      var x0 = InitialPosition.x;
      var p_w0 = Parent.InitialLocalBounds.Width;
      var _x = p_w0 - x0;
      _x /= Parent.Scale.x;
      X = Parent.LocalBounds.Width - _x;
    }

    #endregion

    #region bounds

    // привязка правой/нижней границы к правой/нижней границе парента (local bound)

    public void UpdateBoundBindedToRight()
    {
      UpdateBoundBindedToRight(Parent.InitialLocalBounds.Width);
    }
    public void UpdateBoundBindedToRight(float pw0)
    {
      if (Mathf.Abs(Scale.x - 1f) > 0.01f)
        throw new Exception(string.Format("Scale.x != 1: {0}", Scale.x));

      var lb = LocalBounds;
      lb.RightBottom = new Vector3(
        Parent.LocalBounds.Width - (pw0 - InitialWidth),
        lb.RightBottom.y,
        0f);
      LocalBounds = lb;
    }

    public void UpdateBoundBindedToBottom()
    {
      UpdateBoundBindedToBottom(Parent.InitialLocalBounds.Height);
    }
    public void UpdateBoundBindedToBottom(float ph0)
    {
      if (Mathf.Abs(Scale.y - 1f) > 0.01f)
        throw new Exception(string.Format("Scale.y != 1: {0}", Scale.y));

      var lb = LocalBounds;
      lb.RightBottom = new Vector3(
        lb.RightBottom.x,
        Parent.LocalBounds.Height - (ph0 - InitialHeight),
        0f);
      LocalBounds = lb;
    }

    #endregion

    #region scale

    // привязка правой/нижней границы к правой/нижней границе парента (scale)

    public void UpdateScaleBindedToRight()
    {
      UpdateScaleBindedToRight(Parent.InitialLocalBounds.Width);
    }
    public void UpdateScaleBindedToRight(float pw0)
    {
      Width = Parent.LocalBounds.Width - (pw0 - InitialWidth);
    }

    public void UpdateScaleBindedToBottom()
    {
      UpdateScaleBindedToBottom(Parent.InitialLocalBounds.Height);
    }
    public void UpdateScaleBindedToBottom(float ph0)
    {
      Height = Parent.LocalBounds.Height - (ph0 - InitialHeight);
    }

    //

    public void UpdateScaleBindedToPercent()
    {
      Width = InitialWidth * Parent.LocalBounds.Width / Parent.InitialWidth;
    }

    #endregion

    #endregion
  }

  internal interface IInteractive
  {
    void StartInternal();
    void OnMouseClickInternal(MouseEvent args);
    void OnMouseDoubleClickInternal(MouseEvent args);
    void OnMouseDownInternal(MouseEvent args);
    void OnMouseUpInternal(MouseEvent args, ref InteractiveObject clickObject, ref bool found);
    void OnMouseOverInternal(MouseEvent args, InteractiveObject deepOver);
    void OnMouseOutInternal(MouseEvent args, ref InteractiveObject deepOver);
    void OnMouseWheelInternal(MouseEvent args);
    void OnMouseDragInternal(MouseEvent args);
    void OnMouseMoveInternal(MouseEvent args);
    void InitInternal();
    void ValidateBinding();
    void OnGetFocusInternal();
    void OnLostFocusInternal();
    void OnGetEventInternal(Event args);
  }
}
