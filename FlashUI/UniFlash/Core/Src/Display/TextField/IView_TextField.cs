using System.Collections.Generic;
using UnityEngine;

namespace Flash
{
  internal interface IView_TextField
  {
    int GetLastCharIndexInsideBounds(
        string text, List<IFontMetrics> charSet, int wordSpacing, int tabSpacing,
        int letterSpacing, int fontSize, float lineSpacing,
        bool autoWidth, int autoSizeMaxWidth, bool autoHeight,
        Margin margin, bool multiLine, int linesLimit, bool kerning);

    TextFieldViewData RenderString(
        string text, List<IFontMetrics> charSet, int fontSize, Color color, int wordSpacing,
        int tabSpacing, float lineSpacing, int paragraph, bool multiLine, TextAlignment align, int letterSpacing,
        Margin margin, bool autoWidth, bool autoHeight, float minHeight, int autoSizeMaxWidth, List<CharInfo> charInfos,
        bool kerning, bool isOverBoundsAllowed);

    TextFieldViewData RenderFormatedString(
        FormatedText formatedText,
        List<KeyValuePair<object, List<IFontMetrics>>> formatedCharSet,
        bool multiLine, TextAlignment align, Margin margin,
        bool autoWidth, bool autoHeight, float minHeight, int autoSizeMaxWidth);
  }}