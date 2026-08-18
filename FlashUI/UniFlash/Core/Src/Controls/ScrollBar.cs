using System;
using Flash.Tweens;
using UnityEngine;

namespace Flash.Controls
{
  internal interface IScrollBar
  {
    void ScrollToBegin();
    void ScrollToEnd();
    void EnsureVisiblePart( float pos, float height );
    void Update();
  }

  public interface IScrollableItem
  {
    float LeftTopY { get; }
    float Y { get; set; }
    float ScrollableHeight { get; }
    DisplayObject Mask { get; }
    InteractiveObject InteractiveObject { get; }
  }

  public class ScrollBar : Control, IScrollBar
  {
    #region Nested Types

    private struct ScrollState
    {
      public bool IsScrolling;
      public bool UpPressed;
      public bool DownPressed;
      public float Time;

      public void Reset()
      {
        IsScrolling = false;
        UpPressed = false;
        DownPressed = false;
        Time = 0;
      }
    }

    private struct ScrollInterval
    {
      public float To;
      public float From;
    }

    #endregion

    public event EventHandler ScrollAboveBegin;
    public event EventHandler ScrollBelowEnd;

    private const float LONG_PRESS_DELAY = 0.5f; //sec
    private const int LARGE_CHANGE = 1;
    private const float ANIMATION_DURATION = 0.1f;

    #region Bindings

    [Bind( "up_btn" )]
    private readonly Button _btnUp = new Button();
    [Bind( "down_btn" )]
    private readonly Button _btnDown = new Button();
    [Bind( "slider_btn" )]
    private readonly Button _btnSlider = new Button();
    [Bind( "sliderPath_mc" )]
    private readonly MovieClip _sliderPath = new MovieClip();

    #endregion

    private ScrollState _state; //состояние прокрутки
    private ScrollInterval _interval; //интервал прокрутки
    private bool _isDisabled;

    public bool IsEnabled { get { return !_isDisabled; } }

    private float _lastMouseY = -1;
    private float _scaleCoeff = 1;

    private float _scrollableItemStartY;
    private float _scrollableItemCurrentPos;

    private Tween<InteractiveObject> _tween;

    private int _lineHeight;
    public int LineHeight
    {
      get { return _lineHeight; }
      set
      {
        _lineHeight = value;
        if ( _lineHeight <= 0 )
          _lineHeight = 1;
      }
    }

    private IScrollableItem _scrollableItem;
    public IScrollableItem ScrollableItem
    {
      get { return _scrollableItem; }
      set
      {
        if ( _scrollableItem != null )
          _scrollableItem.InteractiveObject.MouseWheel -= OnScrollableIemWheel;

        _scrollableItem = value;

        if ( _scrollableItem == null )
          return;

        //Init scroll area
        _btnSlider.Y = 0;
        _scrollableItemStartY = _scrollableItem.Y;

        _cachedHeight = CalculatedHeight;
        _scrollableItem.InteractiveObject.MouseWheel += OnScrollableIemWheel;

        if ( _tween != null )
        {
          _tween.Stop();
          _tween = null;
        }

        _tween = new Tween<InteractiveObject>(_scrollableItem.InteractiveObject, p => p.Y, Easing.EaseInOut,
          EasingType.Linear) {Duration = ANIMATION_DURATION};
        _scrollableItemCurrentPos = _scrollableItemStartY;
        //Debug.Log(string.Format("ScrollableItem setter curPos = {0}, startY = {1}", _scrollableItemCurrentPos, _scrollableItemStartY));
        Update();
      }
    }

    public ScrollBar()
    {
      _btnSlider.MouseDown += OnMouseDown;

      _btnUp.MouseDown += OnUp;
      _btnDown.MouseDown += OnDown;

      Render += OnRender;

      LineHeight = 1;
    }


    protected override void Init()
    {
      base.Init();

      float upH = _btnUp.Height;
      float downH = _btnDown.Height;

      _btnUp.Width = _btnUp.Width / Scale.x;
      _btnUp.Height = _btnUp.Height / Scale.y;

      _btnDown.Width = _btnDown.Width / Scale.x;
      _btnDown.Height = _btnDown.Height / Scale.y;

      float delta = upH - _btnUp.Height + downH - _btnDown.Height;


      //_sliderPath.Width = _sliderPath.Width / Scale.x;
      _sliderPath.Height += delta;
      _sliderPath.Y -= ( upH - _btnUp.Height ) / Scale.y;
    }

    /// <summary>
    /// Equel to call ScrollToBegin( true )
    /// </summary>
    public void ScrollToBegin()
    {
      ScrollToBegin( true );
    }

    /// <summary>
    /// Scrolls ScrollableItem to initial position
    /// <remarks>Move with tween must be disabled for height changing cases.</remarks>
    /// </summary>
    /// <param name="moveWithTween"></param>
    public void ScrollToBegin( bool moveWithTween )
    {
      if ( _scrollableItem == null )
        return;

      MoveScrollableItem( _scrollableItemStartY - _scrollableItem.Y, moveWithTween );
    }

    public void ScrollToEnd()
    {
      MoveScrollableItem( _interval.To - _scrollableItem.Y, false );
    }

    /// <summary>
    /// Attempts to scroll ScrollableItem to cover fragment from y posStart to posEnd
    /// </summary>
    /// <param name="posStart">Fragment start Y position in local coordinate system</param>
    /// <param name="posEnd">Fragment end Y position in local coordinate system</param>
    public void ScrollToCoverFragment( float posStart, float posEnd )
    {
      //Calculating start/end of visible area in local(for ScrollableItem) coordinate system
      float start = _scrollableItemStartY - _scrollableItem.Y;
      float end = start + _scrollableItem.Mask.Height;
      //Checks that from posStart to posEnd fragment inside visible bounds
      bool isOutsideTop = posStart <= start;
      bool isOutsideBottom = posEnd >= end;
      //Calculating scroll delta from current ScrollableItem position
      float delta = 0;
      if ( isOutsideTop )
        delta = start - posStart;
      else
        if ( isOutsideBottom )
          delta = end - posEnd;
        else
          return;

      if ( isOutsideTop || isOutsideBottom )
        MoveScrollableItem( delta, false );
    }

    public void EnsureVisiblePart( float pos, float height )
    {
      pos += _scrollableItem.Y;

      float maskH = _scrollableItem.Mask.Height;
      float maskY = _scrollableItem.Mask.Y;
      //Debug.Log( string.Format( "EnsureVisiblePart pos = {0}, height = {1}, maskY = {2}, maskH = {3}", pos, height, maskY, maskH ) );
      //еслу у нас нереально большой кусман скроллим в его начало или мы не видим начала нашего куска);)
      if ( height > maskH || pos < maskY )
      {
        MoveScrollableItem( maskY - pos, true );
        //Debug.Log( "Scroll to the top for " + ( maskY - pos ) );
        return;
      }
      // тут мы знаем что либо кусок полностью видим или его надо чуть подвинуть наверх
      // если видим целиком кусок то ничо не делаем
      if ( pos + height <= maskY + maskH )
      {
        //Debug.Log( "DoNothing" );
        return;
      }
      //теперь надо подвинуть верх кусок таким образом чтобы мы видели низ.
      float hiddenPart = pos + height - maskY - maskH;
      //Debug.Log( "Scroll up for hiddenPart = " + hiddenPart );
      //двигаем на скрытую часть
      MoveScrollableItem( -hiddenPart, true );
    }


    #region implementation

    //приходится делать так, чтобы при автоматическом расширении ScrollableItem в отрицательные координаты, скролл работал правильно
    private float CalculatedHeight
    {
      get
      {
        float top = _scrollableItem.LeftTopY;

        if ( top < 0 )
          return _scrollableItem.ScrollableHeight + top;

        return _scrollableItem.ScrollableHeight;
      }
    }

    public void Update()
    {
      if ( _scrollableItem == null || _scrollableItem.Mask == null || _btnSlider.Parent == null )
      {
        NivalCLI.CLI.Warning( "Scrollbar assembled incorrectly in SWF" );
        return;
      }

      //максимальное расстояние, на сколько может уйти прокручиваемый айтем.
      _interval.To = ScrollableItem.Mask.Height - ScrollableItem.ScrollableHeight + _scrollableItemStartY;
      _interval.From = _scrollableItemStartY;

      if ( _scrollableItem.Mask.Height >= CalculatedHeight )
      {
        EnableScroll( false );
        _interval.To = _interval.From;
        if ( _scrollableItem.Y != _scrollableItemStartY )
          ScrollToBegin();
        return;
      }

      EnableScroll( true );

      float scrollZone = _sliderPath.Height;

      if ( CalculatedHeight != 0 )
        _scaleCoeff = scrollZone / _scrollableItem.ScrollableHeight;

      _btnSlider.Height = _scrollableItem.Mask.Height * _scaleCoeff;
      //just update scrollbar position
      MoveScrollableItem( 0, false );
    }

    private void EnableScroll( bool enabled )
    {
      _btnSlider.Visible = enabled;
      _btnUp.Enabled = enabled;
      _btnDown.Enabled = enabled;

      _isDisabled = !enabled;
    }

    private void MoveScrollableItem( float delta, bool withTween )
    {
      if ( ScrollableItem == null )
        return;

      float newY = _scrollableItemCurrentPos + delta;

      newY = Mathf.Clamp( newY, _interval.To, _interval.From );

      _btnUp.Enabled = newY != _interval.From;
      _btnDown.Enabled = newY != _interval.To;

      if (!_btnUp.Enabled && delta > 0.0 && ScrollAboveBegin != null)
        ScrollAboveBegin(this, new EventArgs());
      if (!_btnDown.Enabled && delta < 0.0 && ScrollBelowEnd != null)
        ScrollBelowEnd(this, new EventArgs());

      //_sliderPath.Y already devided by Scale.y in init function
      float sliderY = -1 * ( newY - _interval.From ) * _scaleCoeff / Scale.y + _sliderPath.Y;

      _btnSlider.Y = sliderY;

      if ( withTween && _tween != null )
      {
        _tween.Stop();
        _tween.Begin = ScrollableItem.Y;
        _tween.End = newY;
        _tween.Start();
      }
      else
      {
        ScrollableItem.Y = newY;
      }
      _scrollableItemCurrentPos = newY;

      //Debug.Log( string.Format( "MoveScrollableItem for delta = {0}, curPos = {1} maskY = {2}",
      //  delta, _scrollableItemCurrentPos, _scrollableItem.Mask.Y ) );
    }

    private void ArrangeByLine()
    {
      var height = ScrollableItem.Y - _scrollableItemStartY;

      var delta = height - ( (int)( height / LineHeight ) * LineHeight );

      if ( Math.Abs( delta ) > LineHeight / 2f )
        delta = LineHeight - Math.Abs( delta );

      MoveScrollableItem( -delta, true );
    }

    #region EventHandlers

    private void OnUp( object sender, MouseEvent e )
    {
      if ( _isDisabled || !_btnUp.Enabled )
        return;

      MoveScrollableItem( LineHeight, true );

      _state.Time = Time.time;
      _state.UpPressed = true;
    }

    private void OnDown( object sender, MouseEvent e )
    {
      if ( _isDisabled || !_btnDown.Enabled )
        return;

      MoveScrollableItem( -LineHeight, true );

      _state.Time = Time.time;
      _state.DownPressed = true;
    }

    private void OnMouseDown( object sender, MouseEvent mouseEvent )
    {
      _state.IsScrolling = true;
    }

    protected override void OnMouseWheel( MouseEvent args )
    {
      base.OnMouseWheel( args );
      ScrollOnDelta( args.Delta );
    }

    public void ScrollOnDelta( float delta )
    {
      if ( !_isDisabled )
      {
        if ( delta < 0 )
          MoveScrollableItem( LineHeight * LARGE_CHANGE, true );
        else
          MoveScrollableItem( -LineHeight * LARGE_CHANGE, true );
      }
    }

    private void OnScrollableIemWheel( object sender, MouseEvent e )
    {
      if ( _isDisabled )
        return;

      if ( e.Delta < 0 )
        MoveScrollableItem( LineHeight * LARGE_CHANGE, true );
      else
        MoveScrollableItem( -LineHeight * LARGE_CHANGE, true );
    }

    private float _cachedHeight;

    private void OnRender( object sender, Event evt )
    {
      if ( _scrollableItem == null )
        return;

      //Size change detection);
      if ( Math.Abs( _cachedHeight - CalculatedHeight ) > 0.01 )
      {
        //Debug.Log(string.Format("##Update ScrollHeight cached = {0}, current = {1}", _cachedHeight, _scrollableItem.Height));
        Update();
        _cachedHeight = CalculatedHeight;
      }

      //TODO subscribe to this from stage
      if (FlashInput.CurrentEvent != null && FlashInput.CurrentEvent.type == UnityEngine.EventType.MouseUp)
      {
        if ( _state.IsScrolling )
          ArrangeByLine();

        _lastMouseY = -1;
        _state.Reset();
      }

      bool longPress = Time.time - _state.Time > LONG_PRESS_DELAY;

      if ( _state.UpPressed && longPress )
      {
        MoveScrollableItem( LineHeight * Time.deltaTime * 100, true );
      }
      else if ( _state.DownPressed && longPress )
      {
        MoveScrollableItem( -LineHeight * Time.deltaTime * 100, true );
      }
      else
      {
        if ( _state.IsScrolling )
        {
          //TODO this is framework specific code. move to framework :)
          //NOTE same goes for FlashDragObject
          Vector2 localMousePos = Parent.GlobalToLocal( FlashInput.MousePosition );

          float delta = 0;

          if ( _lastMouseY != -1 )
            delta = localMousePos.y - _lastMouseY;

          _lastMouseY = localMousePos.y;

          MoveScrollableItem( -delta / _scaleCoeff, false );
        }
      }
    }
    #endregion

    #endregion


  }
}