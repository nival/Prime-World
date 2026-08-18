using System.Collections.Generic;
using Flash.Render;
using SDFFonts;
using UnityEngine;

using FormattedMetrics = System.Collections.Generic.List<System.Collections.Generic.KeyValuePair<object, System.Collections.Generic.List<Flash.IFontMetrics>>>;
using FlashAlign = Flash.TextAlignment;
using UnityAlign = UnityEngine.TextAlignment;
using Flash;

namespace Flash.SDFView
{
  internal class FormattedLayout : Layout
  {
    protected const char ImageChar = '\u0080';

    protected FormatedText _data;
    protected FormattedMetrics _dataMetrics;
    protected int _dataLength;

    protected Shape _iconShape;
    protected Dictionary<Texture2D, Shape> _glyphShapes = new Dictionary<Texture2D, Shape>(1);

    protected int _s_dataIndex;
    protected int _s_fragmentLength;
    protected int _s_fragmentIndex;
    protected FormatEntry _s_fragment;
    protected List<IFontMetrics> _s_fragmentMetrics;
    protected bool _s_fragmentIcon;
    protected string _s_fragmentData;
    protected int _s_glyphIndex;

    public FormattedLayout(DisplayObject target) : base(target) {}

    public void SetData(FormatedText data, FormattedMetrics dataMetrics)
    {
      if (data == null || dataMetrics == null || data.Count != dataMetrics.Count)
      {
        _data = null;
        _dataMetrics = null;
        _dataReady = false;
        return;
      }

      _data = data;
      _dataMetrics = dataMetrics;
      _layoutReady = false;
      _dataReady = true;
    }

    #region Layout implementation

    protected override void OnBeforeLayout()
    {
      _dataLength = _data.Count;
      _s_dataIndex = 0;
      _s_glyphIndex = 0;
      _iconShape = null;
      _glyphShapes.Clear();
    }

    protected override bool IsNextChar()
    {
      return _s_dataIndex < _dataLength;
    }

    protected override Char GetNextChar()
    {
      SetupActiveFragment();

      IFontMetrics metrics = _s_fragmentMetrics[_s_fragmentIndex];
      Style style = _s_fragment.Style;

      Char charData = new Char {
        Index = _s_glyphIndex,
        Metric = metrics,
        Style = style,
      };

      if (_s_fragmentIcon)
      {
        charData.Type = CharType.Icon;
        charData.Ch = ImageChar;
        charData.Width = metrics.Ext.Advance.x;
      }
      else
      {
        char ch = _s_fragmentData[_s_fragmentIndex];
        charData.Ch = ch;

        if (ch == ' ')
        {
          charData.Type = CharType.Space;
          charData.Width = style.WordSpacingValue;
        }
        else if (ch == '\t')
        {
          charData.Type = CharType.Space;
          charData.Width = style.TabSpacingValue;
        }
        else if (ch == '\n')
        {
          charData.Type = CharType.EOL;
        }
        else
        {
          charData.Type = CharType.Glyph;
          charData.Width = metrics.Ext.Advance.x;
        }
      }

      _s_glyphIndex++;
      _s_fragmentIndex++;

      if (_s_fragmentIndex >= _s_fragmentLength)
      {
        _s_dataIndex++;
        _s_fragment = null;
      }

      return charData;
    }

    protected override void OnCharFinalWidth()
    {
      s_char.FinalWidth = s_char.Width + s_char.Metric.Ext.Kerning;
      if (s_word.Type == CharType.Glyph && s_word.Length > 0)
      {
        s_char.FinalWidth += s_char.Style.LetterSpacingValue;
      }
    }

    protected override float GetLineIndent()
    {
      return s_line.Words[0].Chars[0].Style.LineIndentValue;
    }

    protected override void OnAfterCharAdded()
    {
      float vAdv = FontManager.IsLegacyLineSpacing ? s_char.Style.LineSpacingValue : s_char.Metric.Ext.Advance.y;
      if (s_word.VerticalAdvance < vAdv)
      {
          s_word.VerticalAdvance = vAdv;
      }
      if (s_word.Height < s_char.Metric.Ext.LineHeight)
      {
        s_word.Height = s_char.Metric.Ext.LineHeight;
        s_word.BaseLine = s_char.Metric.Ext.BaseLine;
      }

      FillShape(s_char);
    }

    protected override FlashAlign GetLineAlignment()
    {
      if (s_line.Length > 0)
      {
        return ConvertAlign(s_line.Words[0].Chars[0].Style.Align);
      }
      else
      {
        return _fieldMetrics.Alignment;
      }
    }

    protected override TextAlignment GetFieldAlignment()
    {
      return _fieldMetrics.Alignment;
    }

    protected override bool OnMeshPrepare()
    {
      if (_target.Shapes == null)
      {
        _target.Shapes = new List<RenderableElement>(1);
      }

      // Clean excess shapes
      for (int i = 1; i < _target.Shapes.Count; i++)
      {
        Mesh mesh = _target.Shapes[i].FillMesh;
        if (mesh != null)
        {
          mesh.Clear();
        }
      }

      if (_dataLength == 0)
        return false;

      PrepareShapes();

      return true;
    }

    protected override bool OnBeforeCharsMesh()
    {
      return true;
    }

    protected override bool OnFillCharQuad()
    {
      IFontMetrics metric = s_char.Metric;
      Texture2D tex = metric.Tex;

      Shape shape;
      Color color = Color.white;
      if (s_char.Type == CharType.Glyph)
      {
        shape = _glyphShapes[tex];
        color = s_char.Style.Color;
      }
      else if (s_char.Type == CharType.Icon)
      {
        shape = _iconShape;
      }
      else
      {
        return true;
      }

      float x = s_char.X + metric.Ext.Offset.x;
      float y = s_char.Y + metric.Ext.Offset.y + (s_fLine.BaseLine - metric.Ext.BaseLine);
      MeshFillCharQuad(shape, shape.Item, x, y, metric, color);
      shape.Item++;

      return true;
    }

    protected override void OnMeshApply()
    {
      int incIdx = 0;
      foreach (var kvp in _glyphShapes)
      {
        Shape shape = kvp.Value;
        AddShapeElement(incIdx, ref shape);
        incIdx++;
      }
      if (_iconShape != null)
      {
        AddShapeElement(incIdx, ref _iconShape);
        incIdx++;
      }
    }

    #endregion

    private void SetupActiveFragment()
    {
      if (_s_fragment != null)
        return;

      _s_fragment = _data[_s_dataIndex];
      _s_fragmentMetrics = _dataMetrics[_s_dataIndex].Value;
      _s_fragmentData = _s_fragment.Data as string;
      if (_s_fragmentData != null)
      {
        _s_fragmentIcon = false;
        _s_fragmentLength = _s_fragmentData.Length;
      }
      else
      {
        _s_fragmentIcon = true;
        _s_fragmentLength = 1;
      }
      _s_fragmentIndex = 0;
    }

    private FlashAlign ConvertAlign(UnityAlign unityAlign)
    {
      switch (unityAlign)
      {
        case UnityAlign.Center:
          return FlashAlign.TopCenter;
        case UnityAlign.Right:
          return FlashAlign.TopRight;
        default:
          return FlashAlign.TopLeft;
      }
    }

    private void FillShape(Char charData)
    {
      Texture2D tex = charData.Metric.Tex;

      if (charData.Type == CharType.Icon)
      {
        if (_iconShape == null)
        {
          _iconShape = new Shape {
            IsIcon = true,
            Texture = tex,
          };
        }
        _iconShape.ItemsCount++;
      }
      else if (charData.Type == CharType.Glyph)
      {
        Shape shape;
        if (!_glyphShapes.TryGetValue(tex, out shape))
        {
          shape = new Shape {
            IsIcon = false,
            Texture = tex,
          };
          _glyphShapes[tex] = shape;
        }
        shape.ItemsCount++;
      }
    }

    private void PrepareShapes()
    {
      if (_iconShape != null)
      {
        PrepareShape(ref _iconShape);
      }
      foreach (var kvp in _glyphShapes)
      {
        Shape shape = kvp.Value;
        PrepareShape(ref shape);
      }
    }

    private void PrepareShape(ref Shape shape)
    {
      int count = shape.ItemsCount;
      if (count == 0)
        return;
      int quads = count * 4;
      int tris = count * 6;
      shape.Vertices = new Vector3[quads];
      shape.UVs = new Vector2[quads];
      shape.Colors = new Color[quads];
      shape.Tangents = new Vector4[quads];
      shape.Triangles = new int[tris];
      shape.Item = 0;
    }

    private void AddShapeElement(int index, ref Shape shape)
    {
      ShapeElement shapeElement;
      if (_target.Shapes.Count < index+1)
      {
        shapeElement = new ShapeElement
        {
          FillMaterial = new FlashTextMaterial("Flash/TextSDF"),
          FillMesh = new Mesh(),
        };
        _target.Shapes.Add(shapeElement);
      }
      else
      {
        shapeElement = _target.Shapes[index] as ShapeElement;
      }

      if (shape.IsIcon && shapeElement.FillMaterial.Kind != 0)
      {
        shapeElement.FillMaterial = new FlashTextMaterial();
      }
      else if (!shape.IsIcon && shapeElement.FillMaterial.Kind != 1)
      {
        shapeElement.FillMaterial = new FlashTextMaterial("Flash/TextSDF");
      }

      shapeElement.FillMaterial.RenderMaterial.SetTexture("_FillTex", shape.Texture);

      Mesh mesh = shapeElement.FillMesh;
      if (mesh == null)
      {
        mesh = new Mesh();
        shapeElement.FillMesh = mesh;
      }
      mesh.Clear();

      mesh.vertices = shape.Vertices;
      mesh.uv = shape.UVs;
      mesh.tangents = shape.Tangents;
      mesh.colors = shape.Colors;
      mesh.triangles = shape.Triangles;
    }
  }
}