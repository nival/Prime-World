using System.Collections.Generic;
using Flash.Render;
using SDFFonts;
using UnityEngine;

using SimpleMetrics = System.Collections.Generic.List<Flash.IFontMetrics>;

namespace Flash.SDFView
{
  internal class SimpleLayout : Layout
  {
    protected TextMetrics _textMetrics;
    protected string _data;
    protected SimpleMetrics _dataMetrics;
    protected int _dataLength;

    protected int _dataIndex;
    protected int _meshCharIndex;

    protected Shape _shape;
    protected Mesh _mesh;

    public SimpleLayout(DisplayObject target) : base(target) {}

    public void Init(FieldMetrics fieldMetrics, TextMetrics textMetrics)
    {
      base.Init(fieldMetrics);
      _textMetrics = textMetrics;
    }

    public void SetData(string data, SimpleMetrics dataMetrics)
    {
      if (data == null || dataMetrics == null || data.Length != dataMetrics.Count)
      {
        _data = null;
        _dataMetrics = null;
        _dataReady = false;
        return;
      }

      _layoutReady = (_data == data);
      _data = data;
      _dataMetrics = dataMetrics;
      _layoutReady = false;
      _dataReady = true;
    }

    public void FillCharInfo(List<CharInfo> charInfos)
    {
      charInfos.Clear();
      CharInfo ci = default(CharInfo);

      // Positions before chars
      for (int l = 0; l < _lines.Count; l++)
      {
        s_fLine = _lines[l];
        for (int w = 0; w < s_fLine.Length; w++)
        {
          s_word = s_fLine.Words[w];
          for (int c = 0; c < s_word.Length; c++)
          {
            s_char = s_word.Chars[c];
            ci = new CharInfo {
              X = s_char.X + 1f, //HACK: Better caret position for text field controller
              Y = s_char.Y + s_char.Metric.Ext.Advance.y,
              Width = Mathf.RoundToInt(s_char.FinalWidth),
              LineNumb = s_char.LineIndex + 1,
              PositionInLine = s_char.LinePosition + 1,
            };
            charInfos.Add(ci);
          }
        }
      }

      // Position after last char
      if (_dataLength > 0)
      {
        ci = new CharInfo
        {
          X = s_char.X + s_char.FinalWidth + 1f, //HACK: Better caret position for text field controller
          Y = s_char.Y + s_char.Metric.Ext.Advance.y,
          Width = 0,
          LineNumb = s_char.LineIndex + 1,
          PositionInLine = s_char.LinePosition + 2,
        };
        charInfos.Add(ci);
      }
    }

    public int GetLastIndex()
    {
      if (!_dataReady)
        return -1;

      LayoutBuild();

      return r_lastIndex < _dataLength - 1 ? r_lastIndex : -1;
    }

    #region Layout implementation

    protected override void OnBeforeLayout()
    {
      _dataLength = _data.Length;
      _dataIndex = 0;
    }

    protected override bool IsNextChar()
    {
      return _dataIndex < _dataLength;
    }

    protected override Char GetNextChar()
    {
      IFontMetrics metric = _dataMetrics[_dataIndex];
      char ch = _data[_dataIndex];

      Char charData = new Char {
        Index = _dataIndex,
        Metric = metric,
        Ch = ch,
      };

      if (ch == ' ')
      {
        charData.Type = CharType.Space;
        charData.Width = _textMetrics.WordSpacing;
      }
      else if (ch == '\t')
      {
        charData.Type = CharType.Tab;
        charData.Width = _textMetrics.TabSpacing;
      }
      else if (ch == '\n')
      {
        charData.Type = CharType.EOL;
      }
      else
      {
        charData.Type = CharType.Glyph;
        charData.Width = metric.Ext.Advance.x;
      }

      _dataIndex++;

      return charData;
    }

    protected override void OnCharFinalWidth()
    {
      s_char.FinalWidth = s_char.Width;
      if (_textMetrics.UseKerning)
      {
        s_char.FinalWidth += s_char.Metric.Ext.Kerning;
      }
      if (s_word.Type == CharType.Glyph && s_word.Length > 0)
      {
        s_char.FinalWidth += _textMetrics.LetterSpacing;
      }
    }

    protected override float GetLineIndent()
    {
      return _textMetrics.FirstIndent;
    }

    protected override void OnAfterCharAdded()
    {
      if (s_word.Height == 0f)
      {
        s_word.Height = s_char.Metric.Ext.LineHeight;
        if (FontManager.IsLegacyLineSpacing)
        {
          s_word.VerticalAdvance = _textMetrics.LineSpacing;
        }
        else
        {
          s_word.VerticalAdvance = s_char.Metric.Ext.Advance.y;
        }
      }
    }

    protected override TextAlignment GetLineAlignment()
    {
      return _fieldMetrics.Alignment;
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

      // Find DO's shapeElement
      ShapeElement shapeElement;
      if (_target.Shapes.Count == 0)
      {
        shapeElement = new ShapeElement {
          FillMaterial = new FlashTextMaterial("Flash/TextSDF"),
          FillMesh = new Mesh(),
        };
        _target.Shapes.Add(shapeElement);
      }
      else
      {
        shapeElement = _target.Shapes[0] as ShapeElement;
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

      // Prepare and clear unity mesh
      _mesh = shapeElement.FillMesh;
      if (_mesh == null)
      {
        _mesh = new Mesh();
        shapeElement.FillMesh = _mesh;
      }
      _mesh.Clear();

      // No mesh building for empty text field
      if (_dataLength == 0)
        return false;

      Texture2D texture = _dataMetrics[0].Tex;
      shapeElement.FillMaterial.RenderMaterial.SetTexture("_FillTex", texture);

      if (_shape == null)
      {
        _shape = new Shape {
          IsIcon = false,
          Texture = texture,
        };
      }

      // Setup shape size
      int count = _dataLength;
      if (_shape.ItemsCount != count)
      {
        int quads = count * 4;
        int tris = count * 6;
        _shape.ItemsCount = count;
        _shape.Vertices = new Vector3[quads];
        _shape.UVs = new Vector2[quads];
        _shape.Colors = new Color[quads];
        _shape.Tangents = new Vector4[quads];
        _shape.Triangles = new int[tris];
      }

      _shape.Item = 0;

      return true;
    }

    protected override bool OnBeforeCharsMesh()
    {
      _meshCharIndex = 0;
      return true;
    }

    protected override bool OnFillCharQuad()
    {
      if (s_char.Type != CharType.Glyph)
        return true;

      IFontMetrics metrics = s_char.Metric;
      float x = s_char.X + metrics.Ext.Offset.x;
      float y = s_char.Y + metrics.Ext.Offset.y;
      MeshFillCharQuad(_shape, _meshCharIndex, x, y, metrics, _textMetrics.Color);
      _meshCharIndex++;
      return true;
    }

    protected override void OnAfterCharsMesh()
    {
      for (int i = _meshCharIndex; i < _shape.ItemsCount; i++)
      {
        MeshClearCharQuad(_shape, i);
      }
    }

    protected override void OnMeshApply()
    {
      _mesh.vertices = _shape.Vertices;
      _mesh.uv = _shape.UVs;
      _mesh.tangents = _shape.Tangents;
      _mesh.colors = _shape.Colors;
      _mesh.triangles = _shape.Triangles;
      _mesh = null;
    }

    #endregion
  }
}