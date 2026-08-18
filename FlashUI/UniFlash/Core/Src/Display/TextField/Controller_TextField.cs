using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using FlashView.Utils.FormatParser;
using NivalCLI;
using UnityEngine;

namespace Flash
{
  internal class Controller_TextField
  {
    private const char DOT_LITERAL = '\u2022';
    private const char POINT_LITERAL = '\u002E';
    private const char SURROGATE_REPLACE = '?';

    private const uint LATIN_MASK = ~((uint)0xFF);
    private const uint EXTEND_LATIN_MASK = ~((uint)0x17F);
    private const uint CYRILLIC_MASK = ~((uint)0x47F);
    private const uint PUNCTUATION_MASK = ~((uint)0x203F);

    private static Controller_TextField _hasSelection;

    private static Controller_TextField HasSelection
    {
      get { return _hasSelection; }
      set
      {
        if (_hasSelection == value)
          return;

        if (_hasSelection != null)
          _hasSelection.ResetSelection();

        _hasSelection = value;
      }
    }

    private readonly TextField _textField;

    public TextField TextField
    {
      get { return _textField; }
    }

    private readonly IView_TextField _view;
    private readonly IModel_TextField _model;
    private Controller_FSM _stateMachine;

    public Controller_FSM StateMachine
    {
      get
      {
        if (_stateMachine == null)
          _stateMachine = new Controller_FSM(this);

        return _stateMachine;
      }
    }

    public bool SelectTextOnFocus { get; set; }

    public bool TrimOverflow { get; set; }

    private int _trimLinesLimit = -1;

    public int TrimLinesLimit
    {
      get { return _trimLinesLimit; }
      set { _trimLinesLimit = value; }
    }

    private int _trimOverflowLength = 3;

    public int TrimOverflowLength
    {
      get { return _trimOverflowLength; }
      set { _trimOverflowLength = value; }
    }

    private bool _isTrimmed = false;

    public bool IsTrimmed
    {
      get { return _isTrimmed; }
    }

    private bool _isFormated;

    public bool IsFormated
    {
      get { return _isFormated; }
    }

    private bool _isPassword;

    public bool IsPassword
    {
      get { return _isPassword; }
      set
      {
        if (_isPassword != value)
        {
          _isPassword = value;
          Apply();
        }
      }
    }

    private string _formatedPlainText = String.Empty;

    public string FormatedPlainText
    {
      get { return _formatedPlainText; }
    }

    public string Text
    {
      get { return _model.GetText(); }
      set
      {
        if (!_isFormated && _model.GetText() == value)
          return;

        if (value == null)
        {
          return;
        }
        
        var text = ReplaceSurrotateAndFilter(value);

        if (!_isFormated && _model.GetText() == text)
          return;

        if (!String.IsNullOrEmpty(text) && _textField.MaxLenght != 0 && text.Length > _textField.MaxLenght)
          text = text.Substring(0, _textField.MaxLenght);

        _isFormated = false;
        _model.SetText(text, _font, _fontSize, _fontStyle);

        try
        {
          Apply();
        }
        catch (Exception ex)
        {
          _model.SetText(string.Empty, _font, _fontSize, _fontStyle);
          CLI.Error("ControllerTextField apply text error. Text: \"{0}\", error:\"{1}\"", value, ex.Message);
        }

        CarriagePosInternal = CarriagePos;
      }
    }

    public void SetFormatedText(string value)
    {
      SetFormatedText(value, false);
    }

    public void SetFormatedText(string value, bool forced)
    {
      if (!forced && _isFormated && _formatedPlainText == value)
        return;
      SetFormatedTextInternal(value);
    }

    // PF-101523 заменяем суррогатные пары на читабельный символ
    public static string ReplaceSurrotateAndFilter(string value)
    {
      if (string.IsNullOrEmpty(value))
      {
        return string.Empty;
      }

      var characters = new char[value.Length];
      var countCharacters = 0;
      foreach (var c in value)
      {
        if (!Char.IsSurrogate(c))
        {
          if ((c & LATIN_MASK) == 0 || (c & CYRILLIC_MASK) == 0 || (c & EXTEND_LATIN_MASK) == 0 || (c & PUNCTUATION_MASK) == 0)
          {
            characters[countCharacters] = c;
          }
          else
          {
            characters[countCharacters] = SURROGATE_REPLACE;
          }
          countCharacters++;
        }
        else if (Char.IsHighSurrogate(c))
        {
          characters[countCharacters] = SURROGATE_REPLACE;
          countCharacters++;
        }
      }

      return new string(characters, 0, countCharacters);
    }

    private void SetFormatedTextInternal(string value)
    {
      _formatedPlainText = ReplaceSurrotateAndFilter(value);
      _isFormated = true;

      var parser = new FormatParser();

      //Debug.Log(string.Format("##SetFormatedText LineSpacing float = {0}, text = {1}", LineSpacing, value));
      //NOTE тут лайн спейсинг (int) (LineSpacing*100), почему-то спейсинг в стиле инт. похоже надо просто нормальный спейсинг на 100 умножить
      var textFieldStyle = new Style(Font, FontSize, FontStyle, TextColor, _textField.OutlineColor, Align.ToUnityAlign(),
        false, LetterSpacing,
        WordSpacing, (int) (LineSpacing*100), TabSpacing, Paragraph);

      _model.SetFormatedText(parser.Parse(_formatedPlainText, textFieldStyle));
      Apply();
    }

    private bool _autoUpdateView = true;

    public bool AutoUpdateView
    {
      get { return _autoUpdateView; }
      set
      {
        if (_autoUpdateView != value)
        {
          _autoUpdateView = value;
          if (_autoUpdateView)
            Apply();
        }
      }
    }

    private Color _textColor = Color.black;

    public Color TextColor
    {
      get { return _textColor; }
      set
      {
        if (_textColor != value)
        {
          _textColor = value;
          Apply();
        }
      }
    }

    private int _fontSize = 12;

    public int FontSize
    {
      get { return _fontSize; }
      set
      {
        if (_fontSize != value)
        {
          _fontSize = value;
          _model.SetText(_model.GetText(), _font, _fontSize, _fontStyle);
          Apply();
        }
      }
    }

    private int _wordSpacing = 30; // % font size

    public int WordSpacing
    {
      get { return _wordSpacing; }
      set
      {
        if (_wordSpacing != value)
        {
          _wordSpacing = value;
          Apply();
        }
      }
    }

    public int WordSpacingPixels
    {
      get { return PercentToPixels(_wordSpacing) + LetterSpacingPixels; }
    }

    private int _tabSpacing = 20;

    public int TabSpacing
    {
      get { return _tabSpacing; }
      set
      {
        if (_tabSpacing != value)
        {
          _tabSpacing = value;
          Apply();
        }
      }
    }

    private float _lineSpacing = 1;

    public float LineSpacing
    {
      get { return _lineSpacing; }
      set
      {
        if (_lineSpacing != value)
        {
          _lineSpacing = value;
          Apply();
        }
      }
    }

    private int _paragraph;

    public int Paragraph
    {
      get { return _paragraph; }
      set
      {
        if (_paragraph != value)
        {
          _paragraph = value;
          Apply();
        }
      }
    }

    private int _letterSpacing = 0;

    public int LetterSpacing
    {
      get { return _letterSpacing; }
      set
      {
        if (_letterSpacing != value)
        {
          _letterSpacing = value;
          Apply();
        }
      }
    }

    public int LetterSpacingPixels
    {
      get { return _letterSpacing + /*TODO Взыть из EM метриш шрифта*/ (int) (_fontSize*0.13F); }
    }

    private int _leftMargin = 10;

    /// <summary>
    /// % font size
    /// </summary>
    public int LeftMargin
    {
      get { return _leftMargin; }
      set
      {
        if (_leftMargin != value)
        {
          _leftMargin = value;
          Apply();
        }
      }
    }

    public int LeftMarginPixels
    {
      get { return PercentToPixels(_leftMargin) + FlashProp.DjvuSideMarginBias; }
    }

    private int _rightMargin = 10;

    /// <summary>
    /// % font size
    /// </summary>
    public int RightMargin
    {
      get { return _rightMargin; }
      set
      {
        if (_rightMargin != value)
        {
          _rightMargin = value;
          Apply();
        }
      }
    }

    public int RightMarginPixels
    {
      get { return PercentToPixels(_rightMargin) + FlashProp.DjvuSideMarginBias; }
    }

    private int _topMargin = 15;

    /// <summary>
    /// % font size
    /// </summary>
    public int TopMargin
    {
      get { return _topMargin; }
      set
      {
        if (_topMargin != value)
        {
          _topMargin = value;
          Apply();
        }
      }
    }

    public int TopMarginPixels
    {
      get { return PercentToPixels(_topMargin) + FlashProp.DjvuTopMarginBias; }
    }

    private int _bottomMargin;

    /// <summary>
    /// % font size
    /// </summary>
    public int BottomMargin
    {
      get { return _bottomMargin; }
      set
      {
        if (_bottomMargin != value)
        {
          _bottomMargin = value;
          Apply();
        }
      }
    }

    public int BottomMarginPixels
    {
      get { return PercentToPixels(_bottomMargin); }
    }

    private bool _multiLine = true;

    public bool MultiLine
    {
      get { return _multiLine; }
      set
      {
        if (_multiLine != value)
        {
          _multiLine = value;
          Apply();
          _textField.PreTransform = Matrix4x4.identity;
        }
      }
    }

    private TextAlignment _align = TextAlignment.TopLeft;

    public TextAlignment Align
    {
      get { return _align; }
      set
      {
        if (_align != value)
        {
          _align = value;
          Apply();
        }
      }
    }

    private FontStyle _fontStyle = FontStyle.Normal;

    public FontStyle FontStyle
    {
      get { return _fontStyle; }
      set
      {
        if (_fontStyle != value)
        {
          _fontStyle = value;
          _model.SetText(_model.GetText(), _font, _fontSize, _fontStyle);
          Apply();
        }
      }
    }

    private Font _font = FontStorage.DefaultFont;

    public Font Font
    {
      get { return _font; }
      set
      {
        if (_font != value)
        {
          _font = value;
          _model.SetText(_model.GetText(), _font, _fontSize, _fontStyle);
          Apply();
        }
      }
    }

    private bool _autoWidth;

    public bool AutoWidth
    {
      get { return _autoWidth; }
      set
      {
        if (_autoWidth != value)
        {
          _autoWidth = value;
          Apply();
        }
      }
    }

    private bool _autoHeight;

    public bool AutoHeight
    {
      get { return _autoHeight; }
      set
      {
        if (_autoHeight != value)
        {
          _autoHeight = value;
          Apply();
        }
      }
    }

    private int _autoSizeMaxWidth = int.MaxValue;

    public int AutoSizeMaxWidth
    {
      get { return _autoSizeMaxWidth; }
      set
      {
        if (_autoSizeMaxWidth != value)
        {
          _autoSizeMaxWidth = value;
          Apply();
        }
      }
    }

    private float _minHeight = -1;

    /// <summary>
    /// Вызывать перед AutoHeight=true;
    /// </summary>
    public float MinHeight
    {
      get { return _minHeight; }
      set
      {
        if (_minHeight != value)
        {
          _minHeight = value;
          Apply();
        }
      }
    }

    private bool _kerning = true;

    public bool Kerning
    {
      get { return _kerning; }
      set
      {
        if (_kerning != value)
        {
          _kerning = value;
          Apply();
        }
      }
    }

    // Carriage
    private bool _isCarriageVisible;
    private float _carriageAlpha = 1;
    private int _carriagePosInLine;
    private int _carriagePos;
    private int _selectionStart;
    private int _selectionEnd;

    public int CarriagePos
    {
      get { return _carriagePos; }
      set
      {
        CarriagePosInternal = value;

        if (_charInfos.Count > 0)
          _carriagePosInLine = _charInfos[CarriagePos].PositionInLine;
        else
          _carriagePosInLine = 0;

        _carriageAlpha = 1;
      }
    }

    public int CarriagePosInternal
    {
      get { return CarriagePos; }
      set
      {
        if (_charInfos.Count > 0)
        {
          _carriagePos = Mathf.Clamp(value, 0, _charInfos.Count - 1);
        }
        else
        {
          _carriagePos = 0;
        }
      }
    }

    private Color _carriageColor = Color.black;

    public Color CarriageColor
    {
      set { _carriageColor = value; }
    }

    private Color _selectionColor = new Color(7f/255, 86f/255, 82f/255);

    public Color SelectionionColor
    {
      get { return _selectionColor; }
      set { _selectionColor = value; }
    }

    private Color _selectionColorUnfocused = new Color(7f/255, 86f/255, 82f/255);

    public Color SelectionColorUnfocused
    {
      get { return _selectionColorUnfocused; }
      set { _selectionColorUnfocused = value; }
    }

    private readonly List<CharInfo> _charInfos = new List<CharInfo>();

    public List<CharInfo> CharInfos
    {
      get { return _charInfos; }
    }

    private TextFieldViewData _textFieldViewData;

    public TextFieldViewData TextFieldViewData
    {
      get { return _textFieldViewData; }
    }

    public Controller_TextField(TextField field)
    {
      TrimOverflow = false;
      SelectTextOnFocus = false;
      _textField = field;
      _model = new Model_TextField();
#if SDFFONT
      _view = new SDFTextFieldView(_textField);
#else
      _view = new View_TextField(_textField);
#endif
    }

    public Controller_TextField(TextField field, Controller_TextField source)
      : this(field)
    {
      FieldInfo[] fields = GetType().GetFields(BindingFlags.Instance | BindingFlags.NonPublic | BindingFlags.Public);

      foreach (FieldInfo fieldInfo in fields)
      {
        if (!fieldInfo.IsInitOnly)
        {
          fieldInfo.SetValue(this, fieldInfo.GetValue(source));
        }
      }

      //resubmit text
      _model.SetText(source._model.GetText(), _font, _fontSize, _fontStyle);
      Apply();
    }

    public void ProcessEvent(Event e)
    {
      if (e.EventType == EventType.MOUSE_DRAG && _textField.Stage.Focus == _textField)
      {
        StateMachine.GoToState(Controller_FSM.SELECT_STATE, e);
      }
      else if (e.UnityEvent != null
               && e.UnityEvent.shift
               && e.UnityEvent.type == UnityEngine.EventType.KeyDown
               &&
               (e.UnityEvent.keyCode == KeyCode.LeftArrow ||
                e.UnityEvent.keyCode == KeyCode.UpArrow ||
                e.UnityEvent.keyCode == KeyCode.RightArrow ||
                e.UnityEvent.keyCode == KeyCode.DownArrow)
        )
      {
        StateMachine.GoToState(Controller_FSM.SELECT_STATE, e);
      }
      else if (e.EventType == EventType.MOUSE_UP)
      {
        if (_selectionStart != _selectionEnd)
          StateMachine.GoToState(Controller_FSM.HAS_SELECTION_STATE, e);
        else
          StateMachine.GoToState(Controller_FSM.TYPE_STATE, e);
      }
      else if (e.EventType == EventType.MOUSE_DOWN)
      {
        StateMachine.GoToState(Controller_FSM.TYPE_STATE, e);
      }
      else if (e.EventType == EventType.LOST_FOCUS)
      {
        StateMachine.GoToState(Controller_FSM.HAS_SELECTION_UNFOCUSED_STATE, e);
      }

      StateMachine.ProcessEvent(e);
    }

    public void ShowCarriage()
    {
      _isCarriageVisible = true;
      Timer.HalfSecTick += OnTick;
    }

    public void HideCarriage()
    {
      _isCarriageVisible = false;
      Timer.HalfSecTick -= OnTick;
    }

    public Vector2 CalculateCarriage()
    {
      if (!_isCarriageVisible)
        return Vector2.zero;
      // Current Char position
      Vector2 charPos = Vector2.zero;
      Vector2 charPosTemp = Vector2.zero;
      if (_charInfos.Count > 0)
      {
        charPos = new Vector2(_charInfos[CarriagePos].X, _charInfos[CarriagePos].Y);

        // precalc
        if (!_multiLine)
          charPosTemp = _textField.PreTransform.MultiplyPoint(charPos);
      }
      else
      {
        charPos.x = _paragraph;
        charPos.y = (int) (_fontSize*_lineSpacing);
        charPos.x += LeftMarginPixels;
        charPos.y += TopMarginPixels + _textField.LocalBounds.LeftTop.y;
      }

      if (!_multiLine)
      {
        Matrix4x4 preTransform = _textField.PreTransform;

        // Offset
        if (CarriagePos == 0 || _carriagePosInLine == 0)
        {
          _textField.PreTransform = Matrix4x4.identity;
        }
        else if (charPosTemp.x > _textField.LocalBounds.RightBottom.x - RightMarginPixels)
        {
          preTransform[0, 3] = (_textField.LocalBounds.RightBottom.x - RightMarginPixels) - _charInfos[CarriagePos].X;
          _textField.PreTransform = preTransform;
        }
        else if (charPosTemp.x <= _textField.LocalBounds.LeftTop.x + LeftMarginPixels)
        {
          preTransform[0, 3] = (_textField.LocalBounds.LeftTop.x + LeftMarginPixels) - _charInfos[CarriagePos].X;
          _textField.PreTransform = preTransform;
        }

        // Escape
        if (preTransform[0, 3] > 0)
          _textField.PreTransform = Matrix4x4.identity;
      }

      if (!_multiLine)
        charPos = _textField.PreTransform.MultiplyPoint(charPos);

      return charPos;
    }

    public void DrawCarriage(Vector2 charPos)
    {
      if (!_isCarriageVisible)
        return;

      // Align to pixel border so as no antialiasing applied
      // To world with no rotate and scale
      Vector3 pos = Vector3.zero;
      pos.x = charPos.x + _textField.Transform.WorldMatrix[0, 3];
      pos.y = charPos.y + _textField.Transform.WorldMatrix[1, 3];

      pos.x = Mathf.Floor(pos.x) - (_textField.Transform.GlowColor == Color.clear ? 1.5F : 0.5F);
      pos.y = Mathf.Floor(pos.y) + 0.5F;

      Vector2 p1 = pos + new Vector3(0, -DownOffset());
      Vector2 p2 = pos + new Vector3(0, UpOffset());

      //Checks that carriage will drawn in visible Mask area
      if (_textField.Mask != null
          && !_textField.Mask.WorldBounds.Contains(p1)
          && !_textField.Mask.WorldBounds.Contains(p2)
        )
        return;

      GL.PushMatrix();
      UniFlashPlayer.FlashDebug.DrawMaterial.SetPass(0);
      GL.LoadProjectionMatrix(GL.GetGPUProjectionMatrix(UniFlashPlayer.Camera.projectionMatrix, false));
      _carriageColor.a = _carriageAlpha;
      GL.Begin(GL.QUADS);
      GL.Color(_carriageColor); // new Color(1, 1, 1, 1));
      GL.Vertex(pos + new Vector3(0, -DownOffset()));
      GL.Vertex(pos + new Vector3(1, -DownOffset()));
      GL.Vertex(pos + new Vector3(1, UpOffset()));
      GL.Vertex(pos + new Vector3(0, UpOffset()));
      GL.End();
      GL.PopMatrix();
    }

    public void DrawSelection()
    {
      //return;
      if (_selectionStart == _selectionEnd)
        return;

      int start = GetStart();
      int end = GetEnd();

      if (_textField.Mask != null)
      {
        if (UniFlashPlayer.FlashDebug.MiscMaterial)
        {
          UniFlashPlayer.FlashDebug.MiscMaterial.SetFloat("_currentMaskDepth", _textField.MaskDepth);
          UniFlashPlayer.FlashDebug.MiscMaterial.SetPass(2);
        }
        //Debug.Log("UniFlashPlayer.MiscMaterial.DrawMaterial");
      }
      else
      {
        UniFlashPlayer.FlashDebug.DrawMaterial.SetPass(0);
        //Debug.Log("UniFlashPlayer.FlashDebug.DrawMaterial");
      }

      GL.LoadProjectionMatrix(GL.GetGPUProjectionMatrix(UniFlashPlayer.Camera.projectionMatrix, false));

      //GL.Color(Color.red);
      GL.Begin(GL.QUADS);
      GL.Color(_textField.Stage.Focus != _textField ? _selectionColorUnfocused : _selectionColor);

      for (int i = start; i < end; ++i)
      {
        Vector2 startPos = new Vector2(_charInfos[i].X, _charInfos[i].Y);
        Vector2 endPos = new Vector2(_charInfos[i].X + _charInfos[i].Width, _charInfos[i].Y);

        if (!_multiLine)
        {
          startPos = _textField.PreTransform.MultiplyPoint(startPos);
          endPos = _textField.PreTransform.MultiplyPoint(endPos);
        }

        startPos.x += _textField.Transform.WorldMatrix[0, 3] - LetterSpacingPixels;
        startPos.y += _textField.Transform.WorldMatrix[1, 3];
        endPos.x += _textField.Transform.WorldMatrix[0, 3];
        endPos.y += _textField.Transform.WorldMatrix[1, 3];

        // Anti - antialiasing =)
        startPos.x = Mathf.FloorToInt(startPos.x) - 0.5F;
        startPos.y = Mathf.FloorToInt(startPos.y) + 0.5F;
        endPos.x = Mathf.FloorToInt(endPos.x) - 0.5F;
        endPos.y = Mathf.FloorToInt(endPos.y) + 0.5F;

        GL.Vertex(new Vector2(startPos.x, startPos.y + UpOffset()));
        GL.Vertex(new Vector2(endPos.x, endPos.y + UpOffset()));
        GL.Vertex(new Vector2(endPos.x, endPos.y - DownOffset()));
        GL.Vertex(new Vector2(startPos.x, startPos.y - DownOffset()));
      }

      GL.End();
    }

    public void ResetSelection()
    {
      _selectionStart = 0;
      _selectionEnd = 0;
    }

    public void SelectAll()
    {
      HasSelection = this;
      _selectionStart = 0;
      _selectionEnd = _charInfos.Count - 1;
    }

    public void DownCarriage()
    {
      if (_charInfos.Count > 0)
      {
        int newPos = GetCarriagePos(_charInfos[CarriagePos].LineNumb + 1, _carriagePosInLine);
        if (newPos != -1)
          CarriagePosInternal = newPos;
      }
    }

    public void UpCarriage()
    {
      if (_charInfos.Count > 0)
      {
        int newPos = GetCarriagePos((int) _charInfos[CarriagePos].LineNumb - 1, _carriagePosInLine);
        if (newPos != -1)
          CarriagePosInternal = newPos;
      }
    }

    public void SaveStartSelectPos(Vector2 localPosition)
    {
      HasSelection = this;
      _selectionStart = GetCarriagePosition(localPosition);
      _selectionEnd = _selectionStart;
    }

    public void SaveStartSelectPos(int carriagePos)
    {
      HasSelection = this;
      _selectionStart = carriagePos;
      _selectionEnd = _selectionStart;
    }

    public void SaveEndSelectPos(Vector2 localPosition)
    {
      HasSelection = this;
      _selectionEnd = GetCarriagePosition(localPosition);
    }

    public void SaveEndSelectPos(int carriagePos)
    {
      HasSelection = this;
      _selectionEnd = carriagePos;
    }

    public int GetCarriagePosition(Vector2 localPosition)
    {
      int result = 0;

      float lendth = float.MaxValue;
      for (int i = 0; i < _charInfos.Count; ++i)
      {
        Vector2 pos = new Vector2(_charInfos[i].X + _textField.PreTransform[0, 3], _charInfos[i].Y - _fontSize);

        float l = (pos - localPosition).magnitude;
        if (l <= lendth)
        {
          lendth = l;
          result = i;
        }
      }

      if (_charInfos.Count > 0 && localPosition.x > _charInfos[result].X)
      {
        result += 1;
        result = Mathf.Clamp(result, 0, _charInfos.Count - 1);
      }

      return result;
    }

    public void RemoveSelected()
    {
      if (_selectionStart != _selectionEnd)
      {
        int start = GetStart();
        int end = GetEnd();
        CarriagePos = start;
        if ((end - start) >= 0)
            Text = Text.Remove(start, end - start);
      }
      ResetSelection();
    }

    public void CarriagePosToHome()
    {
      int offset = _charInfos[CarriagePos].PositionInLine - 1;
      if (CarriagePos == _charInfos.Count - 1)
        offset++;
      CarriagePos = CarriagePos - offset;
    }

    public void CarriagePosToEnd()
    {
      var currentPos = new Vector2(_charInfos[CarriagePos].X, _charInfos[CarriagePos].Y);
      for (int i = 0; i < _charInfos.Count; ++i)
      {
        if (_charInfos[i].Y > currentPos.y)
        {
          CarriagePos = i - 1;
          return;
        }
      }
      CarriagePos = _charInfos.Count - 1;
    }

    public void PushToClipBoard()
    {
      if (_selectionStart != _selectionEnd)
      {
        int start = GetStart();
        int end = GetEnd();
        int width = end - start;

        string text = Text.Substring(start, width);
        ClipboardHelper.clipBoard = text;
      }
    }

    public void PopFromClipBoard()
    {
      string text = ClipboardHelper.clipBoard;

      if (text != null)
      {
        if (!MultiLine)
        {
          text = text.Replace("\r", string.Empty);
          text = text.Replace("\n", string.Empty);
        }

        Text = Text.Insert(CarriagePos, text);
        CarriagePos += text.Length;
      }
    }

    private void Apply()
    {
      if (!_autoUpdateView)
        return;

      _isTrimmed = false;
      var margin = new Margin(TopMarginPixels, RightMarginPixels, BottomMarginPixels, LeftMarginPixels);
      if (_isFormated)
      {
        _textFieldViewData = _view.RenderFormatedString(_model.GetFormatedText(), _model.FormatedCharSet, _multiLine,
          _align, margin, _autoWidth, _autoHeight, _minHeight, _autoSizeMaxWidth);
        return;
      }

      //Not formatted text
      string text = _model.GetText();
      List<IFontMetrics> metrics = _model.CharSet;

      // Password dots
      if (_textField.TextFieldType == TextFieldType.Input && _isPassword)
      {
        text = new string(DOT_LITERAL, text.Length);
        IFontMetrics metric = Model_TextField.GetMetric(DOT_LITERAL, _font, _fontSize, _fontStyle);
        metrics = new List<IFontMetrics>(text.Length);
        for (int i = 0; i < text.Length; ++i)
          metrics.Add(metric);
      }

      if (metrics != null && text != null && text.Length != metrics.Count)
        Debug.LogError("Text length != metrics length");

      if (metrics != null && text != null && TrimOverflow)
      {
        int lastVisibleIndex = _view.GetLastCharIndexInsideBounds(text, metrics, WordSpacingPixels, _tabSpacing,
          LetterSpacingPixels, _fontSize, _lineSpacing,
          _autoWidth, _autoSizeMaxWidth, _autoHeight, margin, _multiLine, _trimLinesLimit, _kerning);

        if (lastVisibleIndex != -1)
        {
          int upper = Math.Min(metrics.Count, lastVisibleIndex + 1);
          metrics = new List<IFontMetrics>(metrics.GetRange(0, upper));

          if (_textField.TextFieldType != TextFieldType.Input)
          {
            IFontMetrics pointMetric = Model_TextField.GetMetric(POINT_LITERAL, _font, _fontSize, _fontStyle);

            var trimmedWidth = pointMetric.FWidth * (float)_trimOverflowLength;
            var metricWidth = 0f;
            var lastIndex = metrics.Count - 1;

            for (int i = metrics.Count - 1; i >= 0; i--)
            {
              if (metricWidth > trimmedWidth)
              {
                lastIndex = i;
                break;
              }

              metricWidth += metrics[i].FWidth;
            }

            text = text.Substring(0, lastIndex + 1) + new string(POINT_LITERAL, _trimOverflowLength);
            upper = Math.Min(metrics.Count, lastIndex + 1);
            metrics = new List<IFontMetrics>(metrics.GetRange(0, upper));

            for (int i = 0; i < _trimOverflowLength; i++)
              metrics.Add(pointMetric);
          }
          else if (_textField.TrimOverflowForInput)
          {
            // если поле ввода, то просто обрезаем, не добавляя точки
            text = text.Substring(0, metrics.Count + 1);
          }

          _isTrimmed = true;
        }
      }

      _textFieldViewData = _view.RenderString(text, metrics, _fontSize, _textColor,
        WordSpacingPixels, _tabSpacing, _lineSpacing, _paragraph,
        _multiLine, _align, LetterSpacingPixels, margin, _autoWidth, _autoHeight, _minHeight,
        _autoSizeMaxWidth, _charInfos, _kerning, _textField.TextFieldType == TextFieldType.Input);

      ResetSelection();
    }

    private void OnTick(object sender, EventArgs args)
    {
      _carriageAlpha -= 1;
      _carriageAlpha = Mathf.Abs(_carriageAlpha);
    }

    private int GetCarriagePos(int line, int posInLine)
    {
      // Search up
      if (_charInfos[CarriagePos].LineNumb > line)
      {
        for (int i = CarriagePos; i > -1; --i)
        {
          if (_charInfos[i].LineNumb == line && _charInfos[i].PositionInLine == posInLine)
            return i;

          // Stop searching
          if (_charInfos[i].LineNumb < line)
            return Mathf.Clamp(i, 0, _charInfos.Count - 1);

          // First line
          if (_charInfos[i].LineNumb == line && _charInfos[i].PositionInLine < posInLine)
            return i;
        }
      }
      // Search down
      if (_charInfos[CarriagePos].LineNumb < line)
      {
        for (int i = CarriagePos; i < _charInfos.Count; ++i)
        {
          if (_charInfos[i].LineNumb == line && _charInfos[i].PositionInLine == posInLine)
            return i;

          // Stop searching
          if (_charInfos[i].LineNumb > line)
            return Mathf.Clamp(i, 0, _charInfos.Count - 1);

          // Last line
          if (_charInfos[i].LineNumb == line && i == _charInfos.Count - 1)
            return i;
        }
      }

      return -1;
    }

    private int PercentToPixels(int percent)
    {
      return (int) ((percent/100.0F)*_fontSize);
    }

    private int GetStart()
    {
      return Mathf.Clamp(_selectionStart < _selectionEnd ? _selectionStart : _selectionEnd, 0, _charInfos.Count - 1);
    }

    private int GetEnd()
    {
      return Mathf.Clamp(_selectionStart < _selectionEnd ? _selectionEnd : _selectionStart, 0, _charInfos.Count - 1);
    }

    public int UpOffset()
    {
      return -2; // =)
    }

    public int DownOffset()
    {
      return (int) (_fontSize*_lineSpacing) + 2;
    }
  }

  public struct CharInfo
  {
    public float X;
    public float Y;
    public int LineNumb;
    public int PositionInLine;
    public int Width;

    public CharInfo(int x, int y, int lineNumb, int posInLine, int width)
    {
      X = x;
      Y = y;
      LineNumb = lineNumb;
      PositionInLine = posInLine;
      Width = width;
    }
  }

  internal static class AlignConverterHelper
  {
    public static UnityEngine.TextAlignment ToUnityAlign(this TextAlignment align)
    {
      switch (align)
      {
        case TextAlignment.BottomCenter:
        case TextAlignment.MiddleCenter:
        case TextAlignment.TopCenter:
          return UnityEngine.TextAlignment.Center;

        case TextAlignment.BottomLeft:
        case TextAlignment.TopLeft:
        case TextAlignment.MiddleLeft:
          return UnityEngine.TextAlignment.Left;

        case TextAlignment.BottomRight:
        case TextAlignment.TopRight:
        case TextAlignment.MiddleRight:
          return UnityEngine.TextAlignment.Right;
      }

      return UnityEngine.TextAlignment.Left;
    }
  }
}
