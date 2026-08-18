using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Assertions;

using FlashAlign = Flash.TextAlignment;

namespace Flash.SDFView
{
  internal class Layout
  {
    protected const float AdditionalLineSpacing = 8f;
    //HACK: Fix original flash layouts to remove that bias (PF-106557)
    protected const float HorizontalSpaceBias = 0.5f;

    protected const int DefaultWordsCapacity = 4;
    protected const int DefaultLinesCapacity = 1;
    protected const int DefaultCharsInWordCapacity = 8;
    protected const int DefaultWordsInLineCapacity = 4;

    protected DisplayObject _target;
    protected FieldMetrics _fieldMetrics;

    protected List<Line> _lines;

    protected bool _dataReady;
    protected bool _layoutReady;

    // Field metrics
    protected Bounds _initialTextBounds;
    protected Bounds _finalControlBounds;
    protected float _initialWidth;
    protected float _initialHeight;
    protected float _maxWidth;
    protected float _maxHeight;
    protected int _maxLinesCount;

    // Results
    protected int r_lastIndex;
    protected char r_lastChar;
    protected TextFieldViewData r_result;

    // State registers
    protected Char s_char;
    protected Word s_word;
    protected Line s_line;
    protected Line s_fLine;

    // State flags
    protected bool b_done; // Drop in collect field
    protected bool b_nextFLineIndented; // Set and drop in collect field
    protected bool b_lastFLine; // Used for word breaking in last line
    protected bool b_lineDone; // Update in Fill line

    // State counters
    protected int c_linesCount;
    protected int c_lineItem;
    protected float c_requiredWidth;
    protected float c_requiredHeight;

    public Layout(DisplayObject target)
    {
      Assert.IsTrue(target != null);
      _target = target;

      _lines = new List<Line>(DefaultLinesCapacity);
    }

    #region Public interface

    public void Init(FieldMetrics fieldMetrics)
    {
      _fieldMetrics = fieldMetrics;
    }

    public void Build()
    {
      if (!_dataReady)
        return;

      LayoutBuild();
      if (!_layoutReady)
        return;

      AlignLines();
      MeshBuild();
    }

    public TextFieldViewData GetFieldData()
    {
      return r_result;
    }

    public void ApplyFinalBounds()
    {
      if (_fieldMetrics.AutoWidth || _fieldMetrics.AutoHeight)
      {
        _target.LocalBounds = new Bounds {
          LeftTop = _finalControlBounds.LeftTop,
          RightBottom = new Vector3(
              _fieldMetrics.AutoWidth ? _finalControlBounds.RightBottom.x : _target.LocalBounds.RightBottom.x,
              _fieldMetrics.AutoHeight ? _finalControlBounds.RightBottom.y : _target.LocalBounds.RightBottom.y
          ),
        };
      }
    }

    #endregion

    #region Overridable interface

    protected virtual void OnBeforeLayout() {}
    protected virtual bool IsNextChar() { return false; }
    protected virtual Char GetNextChar() { return default(Char); }
    protected virtual void OnCharFinalWidth() {}
    protected virtual float GetLineIndent() { return 0f; }
    protected virtual void OnAfterCharAdded() {}
    protected virtual FlashAlign GetLineAlignment() { return FlashAlign.TopLeft; }
    protected virtual FlashAlign GetFieldAlignment() { return FlashAlign.TopLeft; }
    protected virtual bool OnMeshPrepare() { return false; }
    protected virtual bool OnBeforeCharsMesh() { return false; }
    protected virtual bool OnFillCharQuad() { return false; }
    protected virtual void OnAfterCharsMesh() {}
    protected virtual void OnMeshApply() {}

    #endregion

    #region Main layout

    protected void LayoutBuild()
    {
      r_result = default(TextFieldViewData);
      _layoutReady = false;

      if (Mathf.Approximately(_target.LocalBounds.Width, 0f) && !_fieldMetrics.AutoWidth)
        return;

      Vector4 margin = new Vector4
      {
        x = (float)_fieldMetrics.Margin.left,
        y = (float)_fieldMetrics.Margin.top,
        z = (float)_fieldMetrics.Margin.right,
        w = (float)_fieldMetrics.Margin.bottom,
      };

      _initialTextBounds = new Bounds {
        LeftTop = new Vector3(
          _target.LocalBounds.LeftTop.x + margin.x,
          _target.LocalBounds.LeftTop.y + margin.y),
        // HACK: Error in calculation here. Missed left and top margin. Like in legacy text-field.
        RightBottom = new Vector3(
          _target.WorldBounds.Width - margin.z,
          _target.WorldBounds.Height - margin.w),
      };

      _initialWidth = _fieldMetrics.AutoWidth ? 0f : _initialTextBounds.Width;
      _initialHeight = _fieldMetrics.AutoHeight ? _fieldMetrics.MinHeight : _initialTextBounds.Height;
      float maxWidthLimit = _fieldMetrics.MaxWidth > 0f ? _fieldMetrics.MaxWidth : float.MaxValue;
      _maxWidth = _fieldMetrics.AutoWidth ? maxWidthLimit : _initialTextBounds.Width + HorizontalSpaceBias;
      _maxHeight = _fieldMetrics.AutoHeight ? float.MaxValue : _initialTextBounds.Height;
      _maxLinesCount = _fieldMetrics.MultiLine ? (_fieldMetrics.MaxLines > 0 ? _fieldMetrics.MaxLines : int.MaxValue) : 1;

      OnBeforeLayout();
      Cnv_BuildLayout();
      CheckAdditionalLines();

      _finalControlBounds = new Bounds() {
        LeftTop = _target.LocalBounds.LeftTop,
        RightBottom = new Vector3(
          _target.LocalBounds.LeftTop.x + c_requiredWidth + margin.x + margin.z,
          _target.LocalBounds.LeftTop.y + c_requiredHeight + margin.y + margin.w),
      };

      if (_lines.Count == 0)
      {
        r_lastChar = '\0';
        r_lastIndex = -1;
      }
      else
      {
        Line lastLine = _lines[_lines.Count - 1];
        Word lastWord = lastLine.Words[lastLine.Length - 1];
        Char lastChar = lastWord.Chars[lastWord.Length - 1];
        r_lastChar = lastChar.Ch;
        r_lastIndex = lastChar.Index;
      }

      r_result.Width = Mathf.CeilToInt(c_requiredWidth);
      r_result.Height = Mathf.CeilToInt(c_requiredHeight);
      r_result.LinesCount = _lines.Count;
      r_result.ExpectedExtent = 0f;
      r_result.LastCharIndex = r_lastIndex;
      r_result.LastChar = r_lastChar;

      _layoutReady = true;
    }

    private void CheckAdditionalLines()
    {
      if (!_fieldMetrics.AutoHeight || !_fieldMetrics.AutoWidth)
        return;

      float prevWidth = 0f;
      for (int l = 0; l < _lines.Count; l++)
      {
        s_fLine = _lines[l];
        if (l > 0 && s_fLine.Additional)
        {
          // HACK: Additional width hack (works only for variable width containers)
          float requiredWidth = Mathf.Min(_maxWidth, prevWidth + AdditionalLineSpacing + s_fLine.Width);
          if (c_requiredWidth < requiredWidth)
          {
            c_requiredWidth = requiredWidth;
          }

          // HACK: Previous vertical advance hack (works only for variable height containers)
          s_line = _lines[l - 1];
          float deltaHeight = s_fLine.Height - s_line.Height;
          if (deltaHeight > 0f)
          {

            s_line.VerticalAdvance += deltaHeight;
            c_requiredHeight += deltaHeight;
            _lines[l - 1] = s_line;
          }
        }
        else
        {
          prevWidth = s_fLine.Width;
        }
      }
    }

#endregion

    #region Line alignment

    private void AlignLines()
    {
      AlignLinesVertical();
      AlignLinesHorizontal();
    }

    private void AlignLinesVertical()
    {
      float linesHeight = 0f;
      float origin = 0f;
      float fieldHeight = Mathf.Max(c_requiredHeight, _initialHeight);

      foreach (Line line in _lines)
      {
        linesHeight += line.VerticalAdvance;
      }

      Flash.TextAlignment alignment = GetFieldAlignment();
      switch(alignment)
      {
        case FlashAlign.BottomLeft:
        case FlashAlign.BottomCenter:
        case FlashAlign.BottomRight:
          origin = fieldHeight - linesHeight;
          break;
        case FlashAlign.MiddleLeft:
        case FlashAlign.MiddleCenter:
        case FlashAlign.MiddleRight:
          origin = (fieldHeight - linesHeight) / 2f;
          break;
      }

      for (int l = 0; l < _lines.Count; l++)
      {
        s_fLine = _lines[l];
        origin += s_fLine.VerticalAdvance;
        s_fLine.Y = origin - s_fLine.Height;
        _lines[l] = s_fLine;
      }
    }

    private void AlignLinesHorizontal()
    {
      float fieldWidth = Mathf.Max(c_requiredWidth, _initialWidth);

      for (int l = 0; l < _lines.Count; l++)
      {
        s_fLine = _lines[l];

        if (s_fLine.Alignment == FlashAlign.Justify && s_fLine.CanBeJustified)
        {
          AlignLinesJustifyActive(fieldWidth);
        }

        float origin = 0f;

        switch (s_fLine.Alignment) {
          case FlashAlign.TopRight:
          case FlashAlign.MiddleRight:
          case FlashAlign.BottomRight:
            origin = fieldWidth - s_fLine.Width;
            break;
          case FlashAlign.TopCenter:
          case FlashAlign.MiddleCenter:
          case FlashAlign.BottomCenter:
            origin = (fieldWidth - s_fLine.Width) / 2f;
            break;
        }

        origin += s_fLine.FirstLineIndent;
        int linePosition = 0;

        for (int w = 0; w < s_fLine.Words.Count; w++)
        {
          s_word = s_fLine.Words[w];

          bool isGlyph = s_word.Type == CharType.Glyph;
          float offset = 0f;
          for (int c = 0; c < s_word.Chars.Count; c++) {
            s_char = s_word.Chars[c];
            s_char.Y = s_fLine.Y;
            s_char.X = origin + (s_char.FinalWidth - s_char.Width) + offset;
            s_char.LineIndex = l;
            s_char.LinePosition = linePosition;
            s_word.Chars[c] = s_char;
            if (isGlyph)
            {
              origin += s_char.FinalWidth;
            }
            else
            {
              offset += s_char.FinalWidth;
            }
            linePosition++;
          }
          if (!isGlyph)
          {
            origin += s_word.Width;
          }

          s_fLine.Words[w] = s_word;
        }

        _lines[l] = s_fLine;
      }
    }

    private void AlignLinesJustifyActive(float targetWidth)
    {
      if (s_fLine.Spaces < 1 || s_fLine.Width >= targetWidth)
        return;

      float widthDelta = (targetWidth - s_fLine.Width) / (float)s_fLine.Spaces;
      bool bWord = false;

      int iWord = 0, iSpace = 0;
      while (iWord < s_fLine.Length && iSpace < s_fLine.Spaces)
      {
        Word word = s_fLine.Words[iWord];

        if (word.Type == CharType.Glyph)
        {
          bWord = true;
        }

        if (bWord && word.Type == CharType.Space)
        {
          word.Width += widthDelta;
          s_fLine.Words[iWord] = word;
          iSpace++;
        }

        iWord++;
      }
    }

    #endregion

    #region Conveyor

    private void Cnv_BuildLayout()
    {
      _lines.Clear();

      b_done = false;

      c_linesCount = 0;
      c_requiredWidth = 0f;
      c_requiredHeight = 0f;

      CnvWord_Init();
      CnvLine_Init();

      while(!b_done && IsNextChar())
      {
        s_char = GetNextChar();
        CnvWord_Collect();
      }

      if (!b_done)
      {
        CnvWord_Process();
        CnvLine_Process();
      }
    }

    private void CnvWord_Init()
    {
      s_word = new Word {
        Empty = true,
        Chars = new List<Char>(DefaultCharsInWordCapacity),
      };
    }

    private void CnvWord_Collect()
    {
      CharType wordType = s_char.Type;
      if (wordType == CharType.Icon) wordType = CharType.Glyph;
      if (wordType == CharType.Tab) wordType = CharType.Space;

      if (s_word.Length > 0)
      {
        if (wordType != s_word.Type || s_word.Type == CharType.EOL)
        {
          CnvWord_Process();
          s_word.Type = wordType;
        }
      }
      else
      {
        s_word.Type = wordType;
      }

      OnCharFinalWidth();
      s_word.Chars.Add(s_char);
      s_word.Length++;
      s_word.Width += s_char.FinalWidth;
      s_word.Empty = false;
      OnAfterCharAdded();
    }

    private void CnvWord_Process()
    {
      if (s_word.Empty)
        return;
      CnvLine_Collect();
      CnvWord_Init();
    }

    private void CnvLine_Init()
    {
      s_line = new Line {
        Empty = true,
        Words = new List<Word>(DefaultWordsInLineCapacity),
      };
    }

    private void CnvLine_Collect()
    {
      s_line.Words.Add(s_word);
      s_line.Length++;
      s_line.Width += s_word.Width;
      s_line.Empty = false;

      if (s_word.Type == CharType.EOL)
      {
        CnvLine_Process();
      }
    }

    private void CnvLine_Process()
    {
      if (s_line.Empty)
        return;
      s_line.Alignment = GetLineAlignment();
      s_line.FirstLineIndent = GetLineIndent();
      s_line.Width += s_line.FirstLineIndent;
      CnvField_Collect();
      CnvLine_Init();
    }

    private void CnvField_Collect()
    {
      c_lineItem = 0;

      b_nextFLineIndented = true;
      do
      {
        if (!CnvFLine_IsSuitsVerticalCount())
        {
          b_done = true;
          break;
        }

        CnvField_InitFLine();
        b_nextFLineIndented = false;
        b_lastFLine = (c_linesCount + 1 == _maxLinesCount);

        CnvFLine_Fill();

        if (!CnvFLine_IsSuitsVerticalSize())
        {
          b_done = true;
          break;
        }

        if (!b_lineDone)
        {
          s_fLine.CanBeJustified = true;
        }
        CnvField_AppendFLine();
      }
      while (!b_lineDone);
    }

    private void CnvField_InitFLine()
    {
      s_fLine = new Line {
        Words = new List<Word>(DefaultWordsInLineCapacity),
        FirstLine = b_nextFLineIndented,
        FirstLineIndent = b_nextFLineIndented ? s_line.FirstLineIndent : 0f,
        Width = b_nextFLineIndented ? s_line.FirstLineIndent : 0f,
        Alignment = s_line.Alignment,
      };
    }

    private void CnvFLine_Fill()
    {
      bool wasWord = false;
      bool canOverdraw = !_fieldMetrics.MultiLine && _fieldMetrics.Overdraw;
      int spaceSet = 0;
      float spaceWidth = 0f;

      while (c_lineItem < s_line.Length)
      {
        s_word = s_line.Words[c_lineItem];

        if (s_word.Type == CharType.Glyph)
        {
          if (!canOverdraw && (s_word.Width + s_fLine.Width + spaceWidth > _maxWidth))
          {
            if (b_lastFLine)
            {
              float availableWidth = _maxWidth - s_fLine.Width - spaceWidth;
              CnvFLine_WordBreak(availableWidth);
              if (s_word.Empty)
              {
                break;
              }
            }
            else if (s_fLine.Length >= 1)
            {
              break;
            }
          }

          if (!wasWord)
          {
            s_fLine.Spaces += spaceSet;
          }

          s_fLine.Width += s_word.Width + spaceWidth;
          wasWord = true;
          spaceSet = 0;
          spaceWidth = 0f;
        }

        if (s_word.Type == CharType.Space)
        {
          spaceWidth += s_word.Width;
          if (wasWord || spaceSet > 0)
          {
            wasWord = false;
            spaceSet++;
          }
        }

        s_fLine.Words.Add(s_word);
        s_fLine.Length++;

        if (s_word.Type != CharType.EOL || s_fLine.Length == 1)
        {
          if (s_fLine.VerticalAdvance < s_word.VerticalAdvance)
          {
            s_fLine.VerticalAdvance = s_word.VerticalAdvance;
          }
          if (s_fLine.Height < s_word.Height)
          {
            s_fLine.Height = s_word.Height;
            s_fLine.BaseLine = s_word.BaseLine;
          }
        }

        c_lineItem++;
      }

      b_lineDone = !(c_lineItem < s_line.Length);
    }

    private bool CnvFLine_IsSuitsVerticalCount()
    {
      if (c_linesCount == 0)
        return true;
      if (c_linesCount >= _maxLinesCount)
        return false;
      return true;
    }

    private bool CnvFLine_IsSuitsVerticalSize()
    {
      if (c_linesCount == 0)
        return true;
      if (c_linesCount + 1 > _maxLinesCount)
        return false;
      if (_fieldMetrics.Overdraw)
        return true;
      if (c_requiredHeight + s_fLine.VerticalAdvance >= _maxHeight)
        return false;
      return true;
    }

    private void CnvFLine_WordBreak(float availableWidth)
    {
      Word newWord = new Word() {
        Empty = true,
        Chars = new List<Char>(DefaultCharsInWordCapacity),
      };
      newWord.CopyMetricsFrom(ref s_word);
      for (int i = 0; i < s_word.Length; i++)
      {
        Char ch = s_word.Chars[i];
        if (newWord.Width + ch.FinalWidth > availableWidth)
          break;
        newWord.Empty = false;
        newWord.Width += ch.FinalWidth;
        newWord.Chars.Add(ch);
        newWord.Length++;
      }
      s_word = newWord;
    }

    private void CnvField_AppendFLine()
    {
      if (s_fLine.VerticalAdvance == 0f)
      {
        s_fLine.Additional = true;
      }

      _lines.Add(s_fLine);
      c_linesCount++;

      c_requiredHeight += s_fLine.VerticalAdvance;
      if (c_requiredWidth < s_fLine.Width)
      {
        c_requiredWidth = s_fLine.Width;
      }
    }

    #endregion

    #region Mesh building

    private void MeshBuild()
    {
      if (!OnMeshPrepare())
        return;

      MeshEnumerateChars();

      OnMeshApply();
    }

    private void MeshEnumerateChars()
    {
      if (!OnBeforeCharsMesh())
        return;

      for (int l = 0; l < _lines.Count; l++)
      {
        s_fLine = _lines[l];
        for (int w = 0; w < s_fLine.Words.Count; w++)
        {
          s_word = s_fLine.Words[w];
          for (int c = 0; c < s_word.Chars.Count; c++)
          {
            s_char = s_word.Chars[c];
            if (!OnFillCharQuad())
              break;
          }
        }
      }

      OnAfterCharsMesh();
    }

    protected void MeshFillCharQuad(Shape shape, int index, float x, float y, IFontMetrics metric, Color color)
    {
      int quad = index * 4;
      int tri = index * 6;

      Vector2 size = metric.Ext.Size;

      shape.Vertices[quad + 0] = new Vector3(x, y);
      shape.Vertices[quad + 1] = new Vector3(x + size.x, y);
      shape.Vertices[quad + 2] = new Vector3(x + size.x, y + size.y);
      shape.Vertices[quad + 3] = new Vector3(x, y + size.y);

      shape.UVs[quad + 0] = new Vector2(metric.UvMin.x, metric.UvMin.y);
      shape.UVs[quad + 1] = new Vector2(metric.UvMax.x, metric.UvMin.y);
      shape.UVs[quad + 2] = new Vector2(metric.UvMax.x, metric.UvMax.y);
      shape.UVs[quad + 3] = new Vector2(metric.UvMin.x, metric.UvMax.y);

      shape.Colors[quad + 0] = color;
      shape.Colors[quad + 1] = color;
      shape.Colors[quad + 2] = color;
      shape.Colors[quad + 3] = color;

      shape.Tangents[quad + 0] = Vector4.zero;
      shape.Tangents[quad + 1] = Vector4.zero;
      shape.Tangents[quad + 2] = Vector4.zero;
      shape.Tangents[quad + 3] = Vector4.zero;

      shape.Triangles[tri + 0] = quad + 0;
      shape.Triangles[tri + 1] = quad + 1;
      shape.Triangles[tri + 2] = quad + 2;
      shape.Triangles[tri + 3] = quad + 0;
      shape.Triangles[tri + 4] = quad + 2;
      shape.Triangles[tri + 5] = quad + 3;
    }

    protected void MeshClearCharQuad(Shape shape, int index)
    {
      int quad = index * 4;
      int tri = index * 6;

      shape.Vertices[quad + 0] = new Vector3(0f, 0f);
      shape.Vertices[quad + 1] = new Vector3(0f, 0f);
      shape.Vertices[quad + 2] = new Vector3(0f, 0f);
      shape.Vertices[quad + 3] = new Vector3(0f, 0f);

      shape.UVs[quad + 0] = new Vector2(0f,0f);
      shape.UVs[quad + 1] = new Vector2(0f,0f);
      shape.UVs[quad + 2] = new Vector2(0f,0f);
      shape.UVs[quad + 3] = new Vector2(0f,0f);

      shape.Colors[quad + 0] = Color.clear;
      shape.Colors[quad + 1] = Color.clear;
      shape.Colors[quad + 2] = Color.clear;
      shape.Colors[quad + 3] = Color.clear;

      shape.Tangents[quad + 0] = Vector4.zero;
      shape.Tangents[quad + 1] = Vector4.zero;
      shape.Tangents[quad + 2] = Vector4.zero;
      shape.Tangents[quad + 3] = Vector4.zero;

      shape.Triangles[tri + 0] = quad + 0;
      shape.Triangles[tri + 1] = quad + 1;
      shape.Triangles[tri + 2] = quad + 2;
      shape.Triangles[tri + 3] = quad + 0;
      shape.Triangles[tri + 4] = quad + 2;
      shape.Triangles[tri + 5] = quad + 3;
    }

    #endregion

  }
}