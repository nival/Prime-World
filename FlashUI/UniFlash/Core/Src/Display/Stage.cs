
namespace Flash
{
  public class Stage : DisplayObjectContainer
  {
    private InteractiveObject _focusPrev;
    private InteractiveObject _focus;
    public InteractiveObject Focus
    {
      get { return _focus ?? (_focus = this); }
      set
      {
        _focusPrev = _focus;

        if (value != null)
          _focus = value;
        else
          _focus = this;

        if (_focus != _focusPrev)
        {
          if (_focusPrev != null)
            ((IInteractive)_focusPrev).OnLostFocusInternal();
          if (_focus != null)
            ((IInteractive)_focus).OnGetFocusInternal();
        }
      }
    }

    public Stage()
    {
      Children = new Frame();
      TimeLine.Add(Children);
      Transform = new Transform();
    }
    public override void PreRender()
    {
      _currentMaskDepth = 1;
      _banDoRender = false;

      OnRenderInternal(null);

      RenderChildren();
    }
  }
}
