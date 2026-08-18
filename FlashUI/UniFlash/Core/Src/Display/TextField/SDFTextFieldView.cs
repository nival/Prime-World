using System.Collections.Generic;
using Flash.SDFView;
using SDFFonts;
using UnityEngine;

using SimpleMetrics = System.Collections.Generic.List<Flash.IFontMetrics>;
using FormattedMetrics = System.Collections.Generic.List<System.Collections.Generic.KeyValuePair<object, System.Collections.Generic.List<Flash.IFontMetrics>>>;
using Align = Flash.TextAlignment;

namespace Flash
{
  internal class SDFTextFieldView : IView_TextField
  {
    private DisplayObject _target;
    private Layout _layout;

    public SDFTextFieldView(DisplayObject target)
    {
      _target = target;
    }

    #region IView_TextField

    public int GetLastCharIndexInsideBounds(string text, SimpleMetrics charSet, int wordSpacing, int tabSpacing,
        int letterSpacing, int fontSize, float lineSpacing, bool autoWidth, int autoSizeMaxWidth, bool autoHeight,
        Margin margin, bool multiLine, int linesLimit, bool kerning)
    {
      FieldMetrics fieldMetrics = new FieldMetrics {
        MultiLine = multiLine,
        AutoWidth = autoWidth,
        AutoHeight = autoHeight,
        MaxWidth = (float)autoSizeMaxWidth,
        MinHeight = 0f,
        Alignment = Align.TopLeft,
        Overdraw = false,
        Margin = margin,
        MaxLines = 0,
      };

      TextMetrics textMetrics = new TextMetrics {
        FontSize = fontSize,
        LetterSpacing = (float)fontSize * FontManager.OverrideLetterSpacing,
        WordSpacing = (float)wordSpacing,
        TabSpacing = (float)tabSpacing,
        FirstIndent = 0f,
        LineSpacing = lineSpacing,
        UseKerning = true,
        Color = Color.white,
      };

      SimpleLayout layout = _layout as SimpleLayout;
      if (layout == null)
      {
        layout = new SimpleLayout(_target);
        _layout = layout;
      }
      layout.Init(fieldMetrics, textMetrics);
      layout.SetData(text, charSet);
      return layout.GetLastIndex();
    }

    public TextFieldViewData RenderString(string text, SimpleMetrics charSet, int fontSize, Color color,
        int wordSpacing, int tabSpacing, float lineSpacing, int paragraph, bool multiLine, Align align,
        int letterSpacing, Margin margin, bool autoWidth, bool autoHeight, float minHeight, int autoSizeMaxWidth,
        List<CharInfo> charInfos, bool kerning, bool isOverBoundsAllowed)
    {
      FieldMetrics fieldMetrics = new FieldMetrics {
        MultiLine = multiLine,
        AutoWidth = autoWidth,
        AutoHeight = autoHeight,
        MaxWidth = (float)autoSizeMaxWidth,
        MinHeight = minHeight,
        Alignment = align,
        Overdraw = isOverBoundsAllowed,
        Margin = margin,
        MaxLines = 0,
      };

      TextMetrics textMetrics = new TextMetrics {
        FontSize = fontSize,
        LetterSpacing = (float)fontSize * FontManager.OverrideLetterSpacing,
        WordSpacing = (float)wordSpacing,
        TabSpacing = (float)tabSpacing,
        FirstIndent = paragraph,
        LineSpacing = lineSpacing * (float)fontSize,
        UseKerning = true,
        Color = color,
      };

      SimpleLayout layout = _layout as SimpleLayout;
      if (layout == null)
      {
        layout = new SimpleLayout(_target);
        _layout = layout;
      }
      layout.Init(fieldMetrics, textMetrics);
      layout.SetData(text, charSet);
      layout.Build();
      layout.FillCharInfo(charInfos);
      layout.ApplyFinalBounds();
      return layout.GetFieldData();
    }

    public TextFieldViewData RenderFormatedString(FormatedText formatedText, FormattedMetrics formatedCharSet,
        bool multiLine, Align align, Margin margin, bool autoWidth, bool autoHeight, float minHeight, int autoSizeMaxWidth)
    {
      FieldMetrics fieldMetrics = new FieldMetrics {
        MultiLine = multiLine,
        AutoWidth = autoWidth,
        AutoHeight = autoHeight,
        MaxWidth = (float)autoSizeMaxWidth,
        MinHeight = minHeight,
        Alignment = Align.TopLeft,
        Overdraw = false,
        Margin = margin,
        MaxLines = 0,
      };

      FormattedLayout layout = _layout as FormattedLayout;
      if (layout == null)
      {
        layout = new FormattedLayout(_target);
        _layout = layout;
      }
      layout.Init(fieldMetrics);
      layout.SetData(formatedText, formatedCharSet);
      layout.Build();
      layout.ApplyFinalBounds();
      return layout.GetFieldData();
    }

    #endregion
  }
}