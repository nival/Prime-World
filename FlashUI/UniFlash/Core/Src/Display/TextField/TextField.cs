using System;
using Flash.Controls;
using Flash.Render;
using Flash.Utils;
using UnityEngine;

namespace Flash
{
  public class TextField : InteractiveObject, IScrollableItem
  {
    public virtual string Text
    {
      get { return _controller.Text; }
      set
      {
        _controller.Text = value;
        OnTextSetted(value);
      }
    }

    protected virtual void OnTextSetted(string settedText)
    {
    }

    /// <summary>
    /// Specifies how much lines could be rendered in text field before trimming. 
    /// Also limited by bounds height.
    /// </summary>
    public int TrimLinesLimit
    {
      get { return _controller.TrimLinesLimit; }
      set { _controller.TrimLinesLimit = value; }
    }

    /// <summary>
    /// If true - text will be trimmed with '.' symbol on overflowing
    /// If false - overflowing will be rendered
    /// </summary>
    public bool TrimOverflow
    {
      get { return _controller.TrimOverflow; }
      set { _controller.TrimOverflow = value; }
    }

    private bool _trimOverflowForInput;
    /// <summary>
    /// Если true - удаляются лишние символы при вводе, при выходы за пределы поля ввода
    /// Если false - текст выходит за пределы поля
    /// </summary>
    public bool TrimOverflowForInput
    {
      get { return _trimOverflowForInput; }
      set
      {
        if (TextFieldType == TextFieldType.Input)
        {
          _trimOverflowForInput = value;
          TrimOverflow = value;
        }
      }
    }

    /// <summary>
    /// Specifies quantity of symbols at the end of text, 
    /// which will be replaced by '.' by trim operation
    /// <see cref="TrimOverflow"/>
    /// </summary>
    public int TrimOverflowLength
    {
      get { return _controller.TrimOverflowLength; }
      set { _controller.TrimOverflowLength = value; }
    }

    public bool SelectTextOnFocus
    {
      get { return _controller.SelectTextOnFocus; }
      set { _controller.SelectTextOnFocus = value; }
    }

    public bool IsTrimmed
    {
      get { return _controller.IsTrimmed; }
    }

    protected override void SetupMaterialProperty(FlashMaterial material, RenderableElement element)
    {
      base.SetupMaterialProperty(material, element);

      if (material.GlowColor != Transform.GlowColor)
      {
        material.RenderMaterial.SetColor("_GlowColor", Transform.GlowColor);
      }
    }

    public void SetFormatedText(string value, bool forced)
    {
      if (_textFieldType == TextFieldType.Input)
      {
        Debug.LogWarning("Set Text into Input TextField is impossible!");
        return;
      }

      _controller.SetFormatedText(value, forced);
    }

    public void SetFormatedText(string value)
    {
      SetFormatedText(value, false);
    }

    public Color TextColor
    {
      get { return _controller.TextColor; }
      set { _controller.TextColor = value; }
    }

    public Color OutlineColor
    {
      get { return Transform.GlowColor; }
      set { Transform.GlowColor = value; }
    }

    public bool AutoSize
    {
      set
      {
        AutoWidth = value;
        AutoHeight = value;
      }
    }

    public bool MultiLine
    {
      get { return _controller.MultiLine; }
      set { _controller.MultiLine = value; }
    }

    public TextAlignment Align
    {
      get { return _controller.Align; }
      set { _controller.Align = value; }
    }

    public FontStyle FontStyle
    {
      get { return _controller.FontStyle; }
      set { _controller.FontStyle = value; }
    }

    public float LineSpacing
    {
      get { return _controller.LineSpacing; }
      set { _controller.LineSpacing = value; }
    }

    public Font Font
    {
      get { return _controller.Font; }
      set { _controller.Font = value; }
    }

    public int FontSize
    {
      get { return _controller.FontSize; }
      set { _controller.FontSize = value; }
    }

    public bool AutoWidth
    {
      get { return _controller.AutoWidth; }
      set { _controller.AutoWidth = value; }
    }

    public bool AutoHeight
    {
      get { return _controller.AutoHeight; }
      set { _controller.AutoHeight = value; }
    }

    public float MinHeight
    {
      get { return _controller.MinHeight; }
      set { _controller.MinHeight = value; }
    }

    public int AutoSizeMaxWidth
    {
      get { return _controller.AutoSizeMaxWidth; }
      set { _controller.AutoSizeMaxWidth = value; }
    }

    public bool IsPassword
    {
      get { return _controller.IsPassword; }
      set { _controller.IsPassword = value; }
    }

    public int LineCount
    {
      get { return _controller.TextFieldViewData.LinesCount; }
    }

    private TextFieldType _textFieldType = TextFieldType.Dynamic;

    public TextFieldType TextFieldType
    {
      get { return _textFieldType; }
      set
      {
        if (_textFieldType == value)
          return;

        if (_controller.IsFormated && value == TextFieldType.Input)
        {
          Debug.LogWarning("Formated Text can't be an Input!");
          return;
        }

        // renew;
        if (_textFieldType == TextFieldType.Dynamic && value == TextFieldType.Input)
          Text = Text;

        _textFieldType = value;

        if (_textFieldType == TextFieldType.Dynamic || _textFieldType == TextFieldType.ReadOnly)
        {
          _controller.HideCarriage();
          PreTransform = Matrix4x4.identity;
        }
        else if (Stage.Focus == this)
          _controller.ShowCarriage();

        if (_textFieldType == TextFieldType.Input)
        {
          Render += OnRender;
        }
        else
        {
          Render -= OnRender;
        }
      }
    }

    private readonly Controller_TextField _controller;

    public override Bounds WorldBounds
    {
      get
      {
        if (_dirtyBounds)
        {
          _worldBounds = Transform.WorldMatrix*LocalBounds;
        }
        _dirtyBounds = false;
        return _worldBounds;
      }
    }

    public Color CarriageColor
    {
      set { _controller.CarriageColor = value; }
    }

    public Color SelectionionColor
    {
      get { return _controller.SelectionionColor; }
      set { _controller.SelectionionColor = value; }
    }

    public Color SelectionColorUnfocused
    {
      get { return _controller.SelectionColorUnfocused; }
      set { _controller.SelectionColorUnfocused = value; }
    }

    public TextFieldViewData TextFieldViewData
    {
      get { return _controller.TextFieldViewData; }
    }

    public override float Width
    {
      get { return LocalBounds.Width; }
      set
      {
        Bounds bounds = LocalBounds;
        Vector3 rb = bounds.RightBottom;
        rb.x = value;
        bounds.RightBottom = rb;
        LocalBounds = bounds;
      }
    }

    public int CarriagePos
    {
      get { return _controller.CarriagePos; }
      set { _controller.CarriagePos = value; }
    }

    private int _maxLenght;

    public int MaxLenght
    {
      get { return _maxLenght; }
      set { _maxLenght = value; }
    }

    public int WordSpacing
    {
      get { return _controller.WordSpacing; }
      set { _controller.WordSpacing = value; }
    }

    public event Action<Vector2> OnCarriagePositionChanged;
    private Vector2 _lastCarriagePos = Vector2.zero;
    

    public TextField()
    {
      _controller = new Controller_TextField(this);
      FontStorage.FontsDataWasReseted += ReRenderText;
    }

    public void ReRenderText()
    {
      if (!string.IsNullOrEmpty(Text))
      {
        string temp = Text;
        Text = string.Empty;
        Text = temp;
      }
    }

    public override void Push(UniBaseTag character)
    {
      var textTag = (UniDefineEditTextTag) character;

      base.Push(textTag);
      if (!textTag.ReadOnly)
        TextFieldType = TextFieldType.Input;
      _controller.AutoUpdateView = false;
      _controller.Align = textTag.Align;
      _controller.TextColor = textTag.TextColor;
      _controller.LineSpacing = textTag.LineSpacing;
      _controller.LetterSpacing = textTag.LetterSpacing;
      _maxLenght = textTag.MaxLenght;

      if (textTag.FontId > 0)
      {
        try
        {
          _controller.Font = FontStorage.FontsMap[textTag.FontId];
        }
        catch
        {
          _controller.Font = FontStorage.DefaultFont;
        }
      }
      else
        _controller.Font = FontStorage.DefaultFont;

      _controller.FontSize = textTag.FontSize;
      _controller.FontStyle = FontStyle.Normal;
      _controller.Text = textTag.Text;
      _controller.AutoUpdateView = true;
    }

    public override void PreRender()
    {
      _controller.DrawSelection();
      Vector2 carriagePos = _controller.CalculateCarriage();
      base.PreRender();
      _controller.DrawCarriage(carriagePos);

      if (_lastCarriagePos != carriagePos)
      {
        EventHelper.Invoke(OnCarriagePositionChanged, carriagePos);
        _lastCarriagePos = carriagePos;
      }
    }

    public Vector2 CalculateCarriagePos()
    {
      return _controller.CalculateCarriage();
    }

    /// <summary>
    /// Height of carriage vertical line in pixels
    /// </summary>
    public int CarriageHeight
    {
      get { return _controller.DownOffset() + _controller.UpOffset(); }
    }

    public void SelectText()
    {
      if (_textFieldType != TextFieldType.Input)
        return;

      Stage.Focus = this;
      _controller.SelectAll();
      _controller.StateMachine.GoToState(Controller_FSM.HAS_SELECTION_STATE, new Event(EventType.EMPTY, false));
    }

    //---
    protected override void OnGetEvent(Event e)
    {
      if (_textFieldType == TextFieldType.Dynamic)
        return;

      if (e.UnityEvent.isKey && e.UnityEvent.type == UnityEngine.EventType.KeyDown)
      {
        _controller.ProcessEvent(e);
        e.StopImmediatePropagation();
        e.StopPropagation();
      }

      if (e.UnityEvent.type == UnityEngine.EventType.KeyUp)
      {
        e.StopImmediatePropagation();
        e.StopPropagation();
      }
    }

    protected override void OnGetFocus()
    {
      if (_textFieldType == TextFieldType.Input || _textFieldType == TextFieldType.ReadOnly)
      {
        _controller.ProcessEvent(new Event(EventType.GET_FOCUS, false, null));

        if (_textFieldType == TextFieldType.Input)
          _controller.ShowCarriage();
      }
    }

    protected override void OnLostFocus()
    {
      _controller.HideCarriage();
      PreTransform = Matrix4x4.identity;
      _controller.ProcessEvent(new Event(EventType.LOST_FOCUS, false, null));
    }

    protected override void OnMouseDown(MouseEvent args)
    {
      if (_textFieldType == TextFieldType.Dynamic)
        return;

      _controller.ProcessEvent(args);
    }

    protected override void OnMouseDoubleClick(MouseEvent args)
    {
      if (_textFieldType == TextFieldType.Dynamic)
        return;

      _controller.ProcessEvent(args);
    }

    protected override void OnMouseUp(MouseEvent args)
    {
      if (_textFieldType == TextFieldType.Dynamic)
        return;

      _controller.ProcessEvent(args);
    }

    protected override void OnMouseMove(MouseEvent args)
    {
      if (_textFieldType == TextFieldType.Dynamic)
        return;

      _controller.ProcessEvent(args);
    }

    protected override void OnMouseDrag(MouseEvent args)
    {
      if (_textFieldType == TextFieldType.Dynamic)
        return;

      _controller.ProcessEvent(args);
    }

    private void OnRender(object sender, Event e)
    {
      if (Stage.Focus == this && FlashInput.Input.Event.type == UnityEngine.EventType.MouseUp)
      {
        _controller.ProcessEvent(new Event(EventType.MOUSE_UP, false));
      }
    }

    public InteractiveObject InteractiveObject
    {
      get { return this; }
    }

    public float LeftTopY
    {
      get { return LocalBounds.LeftTop.y; }
    }

    public float ScrollableHeight
    {
      get { return Height; }
    }
  }

  public enum TextAlignment
  {
    TopLeft,
    TopCenter,
    TopRight,
    MiddleLeft,
    MiddleCenter,
    MiddleRight,
    BottomLeft,
    BottomCenter,
    BottomRight,
    Justify
  }

  public enum TextFieldType
  {
    Dynamic,
    Input,
    ReadOnly
  }

  public struct TextFieldViewData
  {
    public int LinesCount { get; set; }
    public int Width { get; set; }
    public int Height { get; set; }
    public int _lastCharIndex;

    public int LastCharIndex
    {
      get { return _lastCharIndex; }
      set { _lastCharIndex = value; }
    }

    public char LastChar { get; set; }
    public float ExpectedExtent { get; set; }

    public override string ToString()
    {
      return string.Format("LinesCount = {0}  Width = {1}  LastChar = {2}  LastChar = {3}", LinesCount, Width,
        LastCharIndex, LastChar);
    }
  }
}
