using System;
using System.Collections.Generic;
using Flash.Render;
using UnityEngine;

namespace Flash
{
  internal class View_TextField : IView_TextField
  {
    private const char IMAGE_LITERAL = '\x001F';
    //---
    private readonly DisplayObject _target;

    private bool _isOSX
    {
      get
      {
        return (Application.platform == RuntimePlatform.OSXPlayer || Application.platform == RuntimePlatform.OSXEditor);
      }
    }

    public View_TextField(DisplayObject target)
    {
      _target = target;
    }

    /// <summary>
    /// Calculates last char in string index, that can be rendered in specified width.
    /// for auto width limitations is <see cref="autoSizeMaxWidth"/>
    /// for fixed size is bounds width
    /// </summary>
    public int GetLastCharIndexInsideBounds(string text, List<IFontMetrics> charSet, int wordSpacing, int tabSpacing,
      int letterSpacing, int fontSize, float lineSpacing,
      bool autoWidth, int autoSizeMaxWidth, bool autoHeight,
      Margin margin, bool multiLine, int linesLimit, bool kerning)
    {
      int inPixels;
      return GetLastCharIndexInsideBounds(text, charSet, wordSpacing, tabSpacing,
        letterSpacing, fontSize, lineSpacing,
        autoWidth, autoSizeMaxWidth, autoHeight,
        margin, multiLine, linesLimit, kerning, out inPixels);
    }

    /// <summary>
    /// Same as <see>
    ///     <cref>GetLastCharIndexInsideBounds</cref>
    ///   </see>
    ///   except 
    /// ref lengthInPixels argument, that using by renderer to 
    /// precalculate bounds.
    /// </summary>
    public int GetLastCharIndexInsideBounds(string text, List<IFontMetrics> charSet, int wordSpacing, int tabSpacing,
      int letterSpacing, int fontSize, float lineSpacing,
      bool autoWidth, int autoSizeMaxWidth, bool autoHeight,
      Margin margin, bool multiLine, int linesLimit, bool kerning, out int lengthInPixels)
    {
      lengthInPixels = 0;
      int lastSymbolIndex = -1;
      if (string.IsNullOrEmpty(text) || charSet == null)
        return lastSymbolIndex;
      string bigString = text;
      if (multiLine)
      {
        String[] paragraphs = text.Split(new[] {'\n'}, StringSplitOptions.RemoveEmptyEntries);
        bigString = String.Empty;
        for (int i = 0; i < paragraphs.Length; ++i)
          if (bigString.Length < paragraphs[i].Length)
            bigString = paragraphs[i];
      }

      int startOffset = text.IndexOf(bigString, StringComparison.Ordinal);

      bool newWord = false;
      int linesCount = 0;
      var bounds = GetBounds(_target, margin);
      int x = 0;
      for (int i = 0; i < bigString.Length; i++)
      {
        int pos = i + startOffset;

        char c = text[pos];
        if (c == IMAGE_LITERAL)
          continue;
        IFontMetrics metric = charSet[pos];
        if (metric == null)
        {
          return lastSymbolIndex;
        }

        if (kerning)
          x += metric.Kern;

        if (c == ' ')
        {
          x += wordSpacing;
          newWord = true;
        }
        else if (c == '\t')
        {
          x += tabSpacing;
          newWord = true;
        }
        else
        {
          x += metric.Width + letterSpacing;
          if (_isOSX)
            x -= FontStorage.OSX_AA_PIXEL_OFFSET;
        }

        if (!multiLine)
        {
          //Auto width
          if ((autoWidth && x >= autoSizeMaxWidth) ||
              //Fixed Width
              (!autoWidth && x >= bounds.Width))
          {
            lastSymbolIndex = i - 1;
            break;
          }
        }
        else
        {
          //Out of bounds
          if (x + 2*letterSpacing + metric.Width > bounds.Width)
            newWord = true;

          // multiLine
          if (newWord)
          {
            newWord = false;
            int endOfWord = text.IndexOfAny(FontStorage.FormatSymbols.ToArray(), i);
            if (endOfWord == -1)
              endOfWord = text.Length;
            string word = text.Substring(i, endOfWord - i);

            var textTillThatIndex = i > 0 ? text.Substring(0, i - 1) : string.Empty;
            var startOfWord = textTillThatIndex.Length > 0
              ? textTillThatIndex.LastIndexOfAny(FontStorage.FormatSymbols.ToArray(), 0)
              : 0;
            if (startOfWord == -1)
              startOfWord = 0;

            // new line

            int lastSymbolInLine = 0;
            bool lastSymbolInLineReached = false;
            // word lendth
            int wordLength = 0;
            for (int j = 0; j < word.Length; ++j)
            {
              wordLength += (charSet[i + j].Width + letterSpacing);
              if (_isOSX)
                wordLength -= FontStorage.OSX_AA_PIXEL_OFFSET;

              if (!lastSymbolInLineReached && x + wordLength > bounds.Width)
              {
                lastSymbolInLine = i + j;
                lastSymbolInLineReached = true;
              }
            }
            wordLength += letterSpacing;

            string fullWord = text.Substring(startOfWord, endOfWord - i);
            var fullWordLength = 0;
            for (int j = 0; j < fullWord.Length; ++j)
            {
              fullWordLength += (charSet[i + j].Width + letterSpacing);
              if (_isOSX)
                fullWordLength -= FontStorage.OSX_AA_PIXEL_OFFSET;
            }
            fullWordLength += letterSpacing;

            // new line
            if ((x + wordLength > bounds.Width && fullWordLength <= bounds.Width) ||
                (x + 2*letterSpacing + metric.Width > bounds.Width && fullWordLength > bounds.Width))
            {
              linesCount++;

              // Moving i to new line start.
              if (wordLength < bounds.Width)
              {
                // if new line created this way:
                // short and
                // verybigword
                i = Math.Max(0, endOfWord);
                x = wordLength;
              }
              else
              {
                // if new line created this way:
                // short and veryb
                // igword
                i = Math.Max(0, lastSymbolInLine - 1);
                x = 0;
              }

              // Trimming by lines limit);)
              if (linesLimit != -1 && linesCount >= linesLimit)
              {
                lastSymbolIndex = lastSymbolInLine > 1 ? lastSymbolInLine - 1 : 0;
                break;
              }

              // Trimming by bounds height
              int y = GetY(linesCount, fontSize, lineSpacing);
              if (!autoHeight && y > bounds.Height)
              {
                lastSymbolIndex = lastSymbolInLine > 1 ? lastSymbolInLine - 1 : 0;
                break;
              }
            }
          }
        }
      }
      lengthInPixels = x;
      return lastSymbolIndex;
    }

    private Bounds GetBounds(DisplayObject target, Margin margin)
    {
      var bounds = new Bounds
      {
        LeftTop = new Vector3(target.LocalBounds.LeftTop.x + margin.left, target.LocalBounds.LeftTop.y + margin.top)
      };
      float rbwidth = target.WorldBounds.Width;
      float rbheight = target.WorldBounds.Height;

      //Alias: WB - WorldBounds; LB - LocalBounds; IB - InitialBounds; TF - TextField;
      //Initial case: WB -> 0, because update local bounds on empty container called.
      //Rendering text: get WB size to check that text will be rendered inside of TF
      //In render process LB updating -> set dirty -> next call to WB it will be recalculated
      //So: WB inside render updates before it real size calculated
      //if ( rbwidth  < _target.InitialBounds.Width )
      //  rbwidth = _target.LocalBounds.Width;
      //if ( rbheight < _target.InitialBounds.Height )
      //  rbheight = _target.LocalBounds.Height;

      bounds.RightBottom = new Vector3(rbwidth - margin.right, rbheight - margin.bottom);
      return bounds;
    }

    // TODO Переделать рендер под стейт машину
    public TextFieldViewData RenderString(string text, List<IFontMetrics> charSet, int fontSize, Color color, int wordSpacing,
      int tabSpacing, float lineSpacing, int paragraph, bool multiLine, TextAlignment align, int letterSpacing,
      Margin margin, bool autoWidth, bool autoHeight, float minHeight, int autoSizeMaxWidth, List<CharInfo> charInfos,
      bool kerning, bool isOverBoundsAllowed)
    {
      if (string.IsNullOrEmpty(text))
        text = new string(IMAGE_LITERAL, 1);

      var result = new TextFieldViewData {LastCharIndex = -1};

      //TODO copypaste c RenderFormattedString

      #region MESH

      ShapeElement textShape;
      if (_target.Shapes != null && _target.Shapes.Count > 0)
        textShape = (ShapeElement) _target.Shapes[0];
      else
      {
        textShape = new ShapeElement {FillMaterial = new FlashTextMaterial(), FillMesh = new Mesh()};
        _target.Shapes = new List<RenderableElement>(1) {textShape};
      }

      #endregion

      if (textShape.FillMesh == null)
        return result;

      textShape.FillMesh.Clear();
      charInfos.Clear();

      const float TOLERANCE = 0.001f;
      if (Math.Abs(_target.LocalBounds.Width) < TOLERANCE)
        return result;

      #region AUTO WIDTH

      if (autoWidth)
      {
        int length;
        GetLastCharIndexInsideBounds(text, charSet, wordSpacing, tabSpacing,
          letterSpacing, fontSize, lineSpacing,
          true, autoSizeMaxWidth, autoHeight,
          margin, false, -1, kerning, out length);
        length += letterSpacing*2;
        length = Mathf.Clamp(length, 0, autoSizeMaxWidth);

        var newbounds = new Bounds
        {
          LeftTop = _target.LocalBounds.LeftTop,
          RightBottom = new Vector3(_target.LocalBounds.LeftTop.x + margin.left + margin.right + length,
            _target.LocalBounds.RightBottom.y)
        };
        _target.LocalBounds = newbounds;
      }

      #endregion

      #region BOUNDS

      var bounds = GetBounds(_target, margin);

      #endregion

      #region GENERATE MESHES

      int x = paragraph;
      int y = fontSize;
      bool newWord = false;
      int lineNumb = 1;
      int charPosInLine = 0;
      var vertexList = new Vector3[(text.Length*4)];
      var uvList = new Vector2[(text.Length*4)];
      var colorList = new Color[(text.Length*4)];
      var tangentList = new Vector4[(text.Length*4)];
      int symbolsPassed = 0;

      var triangleList = new int[(text.Length*6)];
      int triangleOffset = 0;
      var lines = new List<Vector4>(1); // x : symbols in line, y : rightmost X ;
      var vertexMap = new int[(text.Length)];
      const int EXTENT = 1; // << Extention for outlines
      for (int i = 0; i < text.Length; ++i)
      {
        vertexMap[i] = -1;
        charPosInLine++;

        char c = text[i];
        if (c == IMAGE_LITERAL)
          continue;

        if (charSet.Count == 0)
          continue;
        IFontMetrics metric = charSet[Math.Min(charSet.Count - 1, i)];

        // Apply kern
        if (kerning)
          x += metric.Kern;

        // Save char pos , store line in z
        charInfos.Add(new CharInfo(x, y, lineNumb, charPosInLine, metric.Width));

        if (c == '\n' && multiLine)
        {
          // calc symbols per line
          lines.Add(new Vector4(charPosInLine, x, i, 1));

          // apply result;
          if (result.LastCharIndex == -1 && charPosInLine > 1)
          {
            result.LastCharIndex = charPosInLine - 2;
            result.Width = x;
            result.LastChar = text[result.LastCharIndex];
          }

          lineNumb++;
          x = paragraph;
          charPosInLine = 0;
          newWord = true;

          y = GetY(lineNumb, fontSize, lineSpacing);
          continue;
        }
        if (c == ' ')
        {
          x += wordSpacing;
          newWord = true;

          CharInfo info = charInfos[i];
          info.Width = wordSpacing;
          charInfos[i] = info;
        }
        else if (c == '\t')
        {
          x += tabSpacing;
          newWord = true;

          CharInfo info = charInfos[i];
          info.Width = tabSpacing;
          charInfos[i] = info;
        }

        //bool trimmed = false;
        if (!autoWidth && x >= bounds.Width && !multiLine && !isOverBoundsAllowed)
        {
          continue;
        }

        // Out of bounds
        if (multiLine && x + 2*letterSpacing + metric.Width > bounds.Width)
          newWord = true;

        // multiLine

        #region Multiline

        if (multiLine && newWord)
        {
          int endOfWord = text.IndexOfAny(FontStorage.FormatSymbols.ToArray(), i);
          if (endOfWord == -1)
            endOfWord = text.Length;
          string word = text.Substring(i, endOfWord - i);

          var textTillThatIndex = i > 0 ? text.Substring(0, i - 1) : string.Empty;
          var startOfWord = textTillThatIndex.Length > 0
            ? textTillThatIndex.LastIndexOfAny(FontStorage.FormatSymbols.ToArray(), 0)
            : 0;
          if (startOfWord == -1)
            startOfWord = 0;

          string fullWord = text.Substring(startOfWord, endOfWord - i);

          // word lendth
          int wordLendth = 0;
          for (int j = 0; j < word.Length; ++j)
          {
            wordLendth += (charSet[i + j].Width + letterSpacing);
            if (_isOSX)
              wordLendth -= FontStorage.OSX_AA_PIXEL_OFFSET;
          }
          wordLendth += letterSpacing;

          var fullWordLength = 0;
          for (int j = 0; j < fullWord.Length; ++j)
          {
            fullWordLength += (charSet[i + j].Width + letterSpacing);
            if (_isOSX)
              fullWordLength -= FontStorage.OSX_AA_PIXEL_OFFSET;
          }
          fullWordLength += letterSpacing;

          // new line
          if ((x + wordLendth > bounds.Width && fullWordLength <= bounds.Width) ||
              (x + 2*letterSpacing + metric.Width > bounds.Width && fullWordLength > bounds.Width))
          {
            if (text[i] == ' ')
              x -= wordSpacing;
            if (text[i] == '\t')
              x -= tabSpacing;

            // calc symbols per line
            lines.Add(new Vector3(charPosInLine - 1, x, i - 1));

            // apply result
            if (result.LastCharIndex == -1)
            {
              result.LastCharIndex = charPosInLine > 1 ? charPosInLine - 2 : 0;
              result.Width = x;
              result.LastChar = text[result.LastCharIndex];
            }

            lineNumb++;
            x = 0;
            charPosInLine = 1;

            // Repair symbol
            y = GetY(lineNumb, fontSize, lineSpacing);
            charInfos[i] = new CharInfo(x, y, lineNumb, charPosInLine, metric.Width);
          }
        }

        #endregion

        if (metric.Width == 0)
          continue;

        newWord = false;

        y = GetY(lineNumb, fontSize, lineSpacing);

        #region Meshes

        int baseLine = y - metric.Floor;
        vertexList[symbolsPassed*4 + 0] = new Vector3(x, baseLine, 0) + new Vector3(-EXTENT, EXTENT);
        vertexList[symbolsPassed*4 + 1] = new Vector3(x + metric.Width, baseLine, 0) + new Vector3(EXTENT, EXTENT);
        vertexList[symbolsPassed*4 + 2] = new Vector3(x + metric.Width, baseLine - metric.Height, 0) +
                                          new Vector3(EXTENT, -EXTENT);
        vertexList[symbolsPassed*4 + 3] = new Vector3(x, baseLine - metric.Height, 0) + new Vector3(-EXTENT, -EXTENT);

        uvList[symbolsPassed*4 + 0] = new Vector2(metric.UvMin.x, metric.UvMin.y) + new Vector2(-EXTENT, -EXTENT);
        uvList[symbolsPassed*4 + 1] = new Vector2(metric.UvMax.x, metric.UvMin.y) + new Vector2(EXTENT, -EXTENT);
        uvList[symbolsPassed*4 + 2] = new Vector2(metric.UvMax.x, metric.UvMax.y) + new Vector2(EXTENT, EXTENT);
        uvList[symbolsPassed*4 + 3] = new Vector2(metric.UvMin.x, metric.UvMax.y) + new Vector2(-EXTENT, EXTENT);

        uvList[symbolsPassed*4 + 0] /= FontStorage.DEFAULT_TEX_SIZE;
        uvList[symbolsPassed*4 + 1] /= FontStorage.DEFAULT_TEX_SIZE;
        uvList[symbolsPassed*4 + 2] /= FontStorage.DEFAULT_TEX_SIZE;
        uvList[symbolsPassed*4 + 3] /= FontStorage.DEFAULT_TEX_SIZE;

        colorList[symbolsPassed*4 + 0] = (c == IMAGE_LITERAL) ? Color.white : color;
        colorList[symbolsPassed*4 + 1] = (c == IMAGE_LITERAL) ? Color.white : color;
        colorList[symbolsPassed*4 + 2] = (c == IMAGE_LITERAL) ? Color.white : color;
        colorList[symbolsPassed*4 + 3] = (c == IMAGE_LITERAL) ? Color.white : color;

        tangentList[symbolsPassed*4 + 0] = Color.clear;
        tangentList[symbolsPassed*4 + 1] = Color.clear;
        tangentList[symbolsPassed*4 + 2] = Color.clear;
        tangentList[symbolsPassed*4 + 3] = Color.clear;

        int offset = triangleOffset*4;
        triangleList[symbolsPassed*6 + 0] = 0 + offset;
        triangleList[symbolsPassed*6 + 1] = 3 + offset;
        triangleList[symbolsPassed*6 + 2] = 2 + offset;
        triangleList[symbolsPassed*6 + 3] = 0 + offset;
        triangleList[symbolsPassed*6 + 4] = 2 + offset;
        triangleList[symbolsPassed*6 + 5] = 1 + offset;

        vertexMap[i] = triangleOffset;
        triangleOffset++;

        #endregion

        x += (metric.Width + letterSpacing);
        if (_isOSX)
          x -= FontStorage.OSX_AA_PIXEL_OFFSET;
        symbolsPassed++;
      }

      lines.Add(new Vector3(charPosInLine, x, text.Length - 1));
      // Add last pos
      charInfos.Add(new CharInfo(x, y, lineNumb, charPosInLine, charSet.Count > 0 ? charSet[charSet.Count - 1].Width : 0));

      // apply result);
      if (result.LastCharIndex == -1)
      {
        result.LastCharIndex = Math.Max(charPosInLine - 1, 0);
        result.Width = x;
        result.LastChar = text[result.LastCharIndex];
      }

      result.LinesCount = lines.Count;

      #endregion

      #region AUTO HEIGHT + ADJUSTMENT

      int height = GetY(lines.Count, fontSize, lineSpacing);
      if (charSet.Count > 0)
        height = GetY(lines.Count, fontSize, lineSpacing);

      UpdateLocalBoundsWithHeight(margin, bounds, height, autoHeight, minHeight);

      #endregion

      #region ALIGNMENT

      // Horiz alignment
      int curSymbol = 0;
      float offsetWidth = 0;
      for (int l = 0; l < lines.Count; l++)
      {
        Vector4 entry = lines[l];

        // Don't do last line alignment
        if (align == TextAlignment.Justify && (l == lines.Count - 1 || Math.Abs(entry.w - 1f) < TOLERANCE))
        {
          goto increment;
        }

        // Most right minus most left vertex
        var lineWidth = (int) entry.y;
        var index = (int) entry.z;
        offsetWidth = (int) bounds.LeftTop.x;

        //Take away white spaces
        for (int i = index; i >= 0; i--)
        {
          if (text[i] == ' ')
            lineWidth -= wordSpacing;
          else if (text[i] == '\t')
            lineWidth -= tabSpacing;
          else if (text[i] != '\n')
            break;
        }

        lineWidth = Mathf.Clamp(lineWidth, 0, lineWidth);

        if (align == TextAlignment.TopRight || align == TextAlignment.MiddleRight || align == TextAlignment.BottomRight ||
            align == TextAlignment.Justify)
          offsetWidth += Mathf.RoundToInt(bounds.Width - lineWidth);
        else if (align == TextAlignment.TopCenter || align == TextAlignment.MiddleCenter ||
                 align == TextAlignment.BottomCenter)
          offsetWidth += Mathf.RoundToInt((bounds.Width - lineWidth)/2);

        // align
        if (align == TextAlignment.Justify)
        {
          float rightX = 10000;
          float leftX;
          int spaces = 0;

          // Calc spaces count
          for (int j = curSymbol; j < curSymbol + entry.x; ++j)
          {
            int vertex = vertexMap[j];
            if (vertex != -1)
            {
              vertex *= 4;
              leftX = vertexList[vertex].x;
              if (leftX - rightX > letterSpacing)
                spaces++;
              rightX = vertexList[vertex + 1].x;
            }
          }

          if (spaces > 0)
          {
            float stepOffset = offsetWidth/spaces;
            spaces = 0;
            float offset = 0;

            for (int j = curSymbol; j < curSymbol + entry.x; ++j)
            {
              int vertex = vertexMap[j];
              if (vertex != -1)
              {
                vertex *= 4;
                leftX = vertexList[vertex].x;
                if (leftX - rightX > letterSpacing)
                  spaces++;
                rightX = vertexList[vertex + 1].x;

                if (spaces > 0)
                {
                  offset = stepOffset*spaces;
                  for (int k = 0; k < 4; ++k)
                  {
                    vertexList[vertex] = new Vector3(vertexList[vertex].x + offset, vertexList[vertex].y,
                      vertexList[vertex].z);
                    vertex++;
                  }
                }
              }

              // Char pos storage
              CharInfo info = charInfos[j];
              info.X += offset;
              charInfos[j] = info;
            }
          }
        }
        else
        {
          for (int j = curSymbol; j < curSymbol + entry.x; ++j)
          {
            int vertex = vertexMap[j];
            if (vertex != -1)
            {
              vertex *= 4;
              for (int k = 0; k < 4; ++k)
              {
                vertexList[vertex] = new Vector3(vertexList[vertex].x + offsetWidth + EXTENT, vertexList[vertex].y,
                  vertexList[vertex].z);
                vertex++;
              }
            }

            // Char pos storage
            CharInfo info = charInfos[j];
            info.X += offsetWidth;
            charInfos[j] = info;
          }
        }

        increment:
        curSymbol += (int) entry.x;
      }

      // Lats pos in storage
      if (charInfos.Count > 1)
      {
        CharInfo info = charInfos[charInfos.Count - 1];
        info.X += offsetWidth;
        charInfos[charInfos.Count - 1] = info;
      }

      // Vert alignment
      var offsetHeight = (int) bounds.LeftTop.y;
      if (align == TextAlignment.BottomCenter || align == TextAlignment.BottomLeft || align == TextAlignment.BottomRight)
      {
        offsetHeight += (int) (bounds.Height - height);
      }
      else if (align == TextAlignment.MiddleCenter || align == TextAlignment.MiddleLeft ||
               align == TextAlignment.MiddleRight)
      {
        offsetHeight += (int) ((bounds.Height - height)/2);
      }
      if (offsetHeight != 0)
      {
        for (int v = 0; v < vertexList.Length; ++v)
        {
          vertexList[v] = new Vector3(vertexList[v].x, vertexList[v].y + offsetHeight, vertexList[v].z);
        }

        // Char pos storage
        for (int i = 0; i < charInfos.Count; i++)
        {
          CharInfo info = charInfos[i];
          info.Y += offsetHeight;
          charInfos[i] = info;
        }
      }

      #endregion

      // Submit
      textShape.FillMesh.vertices = vertexList;
      textShape.FillMesh.uv = uvList;
      textShape.FillMesh.tangents = tangentList;
      textShape.FillMesh.colors = colorList;
      textShape.FillMesh.triangles = triangleList;
      textShape.FillMaterial.RenderMaterial.SetTexture("_FillTex", charSet.Count > 0 ? charSet[0].Tex : null);

      result.Height = GetY(lineNumb, fontSize, lineSpacing);
      return result;
    }

    public TextFieldViewData RenderFormatedString(FormatedText formatedText,
      List<KeyValuePair<object, List<IFontMetrics>>> formatedCharSet, bool multiLine, TextAlignment align, Margin margin,
      bool autoWidth, bool autoHeight, float minHeight, int autoSizeMaxWidth)
    {
      ////Profiler.BeginSample("PUSH_FORMATED_STRING");

      var result = new TextFieldViewData {LastCharIndex = -1};
      var context = new View_TextField_Context();

      //TODO copypaste c RenderString

      #region MESH

      ShapeElement textShape;
      if (_target.Shapes != null && _target.Shapes.Count > 0)
        textShape = (ShapeElement) _target.Shapes[0];
      else
      {
        textShape = new ShapeElement {FillMaterial = new FlashTextMaterial(), FillMesh = new Mesh()};
        _target.Shapes = new List<RenderableElement>(1) {textShape};
      }

      if (textShape.FillMesh == null)
      {
        return result;
      }

      textShape.FillMesh.Clear();
      if (formatedText == null)
        return result;

      #endregion

      #region CONCATENATE

      var styleMap = new List<Style>(1);
      foreach (FormatEntry formatEntry in formatedText)
      {
        var s = formatEntry.Data as string;
        if (s != null)
        {
          var str = s;
          for (int i = 0; i < str.Length; i++)
            styleMap.Add(formatEntry.Style);
        }
        else
        {
          styleMap.Add(formatEntry.Style);
        }
      }

      string concatText = String.Empty;
      var concatCharSet = new List<IFontMetrics>(formatedCharSet.Count);
      foreach (KeyValuePair<object, List<IFontMetrics>> keyValuePair in formatedCharSet)
      {
        string key = keyValuePair.Key is string ? (string) keyValuePair.Key : new string(IMAGE_LITERAL, 1);
        List<IFontMetrics> value = keyValuePair.Value;

        concatText += key;
        concatCharSet.AddRange(value);
      }

      #endregion

      #region AUTO WIDTH

      if (autoWidth)
      {
        String[] paragraphs = concatText.Split(new[] {'\n'}, StringSplitOptions.RemoveEmptyEntries);

        int maxLendth = 0;
        foreach (string paragraph in paragraphs)
        {
          int startOffset = concatText.IndexOf(paragraph, StringComparison.Ordinal);
          int paragraphLendth = 0;
          for (int i = 0; i < paragraph.Length; i++)
          {
            int pos = i + startOffset;

            char c = concatText[pos];
            IFontMetrics metric = concatCharSet[pos];
            // Set Context
            if (context.CurrentStyle != styleMap[pos])
            {
              context.CurrentStyle = styleMap[pos];
              context.SetContext(context.CurrentStyle);
            }

            if (c == ' ')
            {
              paragraphLendth += context.WordSpacing;
              continue;
            }
            if (c == '\t')
            {
              paragraphLendth += context.TabSpacing;
              continue;
            }

            paragraphLendth += metric.Width + context.LetterSpacing;
          }
          paragraphLendth -= context.LetterSpacing;

          if (paragraphLendth > maxLendth)
            maxLendth = paragraphLendth;
        }

        if (maxLendth > autoSizeMaxWidth)
          maxLendth = autoSizeMaxWidth;

        var newbounds = new Bounds
        {
          LeftTop = _target.LocalBounds.LeftTop,
          RightBottom =
            new Vector3(_target.LocalBounds.LeftTop.x + margin.left + margin.right + maxLendth,
              _target.LocalBounds.RightBottom.y)
        };
        _target.LocalBounds = newbounds;
      }

      #endregion

      #region BOUNDS

      var bounds = new Bounds
      {
        LeftTop = new Vector3(_target.LocalBounds.LeftTop.x + margin.left, _target.LocalBounds.LeftTop.y + margin.top),
        RightBottom = new Vector3(_target.WorldBounds.Width - margin.right, _target.WorldBounds.Height - margin.bottom)
      };

      #endregion

      #region GENERATE MESHES

      var vertexList = new Vector3[(concatText.Length*4)];
      var uvList = new Vector2[(concatText.Length*4)];
      var colorList = new Color[(concatText.Length*4)];
      var tangentList = new Vector4[(concatText.Length*4)];
      var triangleList = new int[(concatText.Length*6)];
      var lines = new List<int>(1);
      var charToVertexMap = new SortedList<int, int>(concatText.Length);
      var lastLineChars = new List<int>(1);
      bool styleChanged = false;

      int symbolsPassed = 0;
      for (int i = 0; i < concatText.Length; ++i)
      {
        char c = concatText[i];
        IFontMetrics metric = concatCharSet[i];

        // Apply kern
        context.X += metric.Kern;

        charToVertexMap.Add(i, -1);

        // Set Context
        if (context.CurrentStyle != styleMap[i])
        {
          styleChanged = true;

          context.CurrentStyle = styleMap[i];
          context.SetContext(context.CurrentStyle);
        }

        // First Line Step
        if (i == 0)
        {
          context.Y = context.LineSpacing > context.FontSize ? context.LineSpacing : context.FontSize;
          context.LineLineSpacing = context.Y;
          context.LineBaseLine = context.Y - context.BaseLine;
        }

        // New line
        if (c == '\n')
        {
          // Calc line width
          lines.Add(context.X);
          // apply result
          if (result.LastCharIndex == -1)
          {
            if (i > 0)
            {
              result.LastCharIndex = i - 1;
              result.Width = context.X;
              result.LastChar = concatText[result.LastCharIndex];
            }
            else
            {
              result.LastCharIndex = 0;
              result.Width = 0;
              result.LastChar = '\n';
            }
          }

          // Line Step
          context.Y += context.LineSpacing;

          context.LineBaseLine = context.Y - context.BaseLine;
          context.LineLineSpacing = context.LineSpacing;
          context.X = context.Paragraph;
          context.NewWord = true;
          lastLineChars.Add(i - 1);
          continue;
        }
        if (c == ' ')
        {
          context.X += context.WordSpacing;
          context.NewWord = true;

          continue;
        }
        if (c == '\t')
        {
          context.X += context.TabSpacing;
          context.NewWord = true;

          continue;
        }

        // Out of bounds
        if (multiLine && context.X > bounds.Width)
        {
          context.NewWord = true;
        }

        if (metric.Width == 0)
          continue;

        // MultiLine
        if (multiLine && context.NewWord && i > 0)
        {
          int endOfWord = concatText.IndexOfAny(FontStorage.FormatSymbols.ToArray(), i);
          if (endOfWord == -1)
            endOfWord = concatText.Length;
          string word = concatText.Substring(i, endOfWord - i);

          // Word lendth
          int wordLendth = 0;
          View_TextField_Context tempContext = new View_TextField_Context();
          for (int j = 0; j < word.Length; ++j)
          {
            tempContext.SetContext(styleMap[i + j]);
            wordLendth += (concatCharSet[i + j].Width + tempContext.LetterSpacing);
            //if ( _isOSX )
            //  wordLendth -= FontStorage.OSX_AA_PIXEL_OFFSET;
          }
          wordLendth -= tempContext.LetterSpacing;

          // New line
          if (context.X + wordLendth > bounds.Width)
          {
            // Calc line width
            lines.Add(context.X - context.WordSpacing);
            // apply result
            if (result.LastCharIndex == -1)
            {
              result.LastCharIndex = i - 1;
              result.Width = context.X;
              result.LastChar = concatText[result.LastCharIndex];
            }

            // Line Step
            context.Y += context.LineSpacing;
            context.LineBaseLine = context.Y - context.BaseLine;
            context.LineLineSpacing = context.LineSpacing;
            context.X = 0;

            lastLineChars.Add(i - 2);
          }
        }

        context.NewWord = false;

        // Height adjustment
        if (styleChanged)
        {
          styleChanged = false;

          if (context.LineLineSpacing < context.LineSpacing && i > 0 && concatText[i - 1] != '\n')
          {
            context.LineLineSpacing = context.LineSpacing;
            context.Y += context.LineSpacing - context.PrevLineSpacing;
            context.LineBaseLine = context.Y - context.BaseLine;

            int baseLineDelta = context.LineBaseLine - context.PrevBaseLine;
            int startForOffset = 0;
            if (lastLineChars.Count > 0)
              startForOffset = lastLineChars[lastLineChars.Count - 1] + 1;

            for (int j = startForOffset; j < i; ++j)
            {
              int vertex = charToVertexMap[j];
              if (vertex != -1)
              {
                for (int k = vertex; k < vertex + 4; k++)
                {
                  Vector3 v = vertexList[k];
                  v.y += baseLineDelta;
                  vertexList[k] = v;
                }
              }
            }
          }
        }

        if (c == IMAGE_LITERAL)
          context.Extent = 0;

        int floor = context.LineBaseLine + (context.BaseLine - metric.Floor);

        vertexList[symbolsPassed*4 + 0] = new Vector3(context.X, floor, 0) +
                                          new Vector3(-context.Extent, context.Extent);
        vertexList[symbolsPassed*4 + 1] = new Vector3(context.X + metric.Width, floor, 0) +
                                          new Vector3(context.Extent, context.Extent);
        vertexList[symbolsPassed*4 + 2] = new Vector3(context.X + metric.Width, floor - metric.Height, 0) +
                                          new Vector3(context.Extent, -context.Extent);
        vertexList[symbolsPassed*4 + 3] = new Vector3(context.X, floor - metric.Height, 0) +
                                          new Vector3(-context.Extent, -context.Extent);

        uvList[symbolsPassed*4 + 0] = new Vector2(metric.UvMin.x, metric.UvMin.y) +
                                      new Vector2(-context.Extent, -context.Extent);
        uvList[symbolsPassed*4 + 1] = new Vector2(metric.UvMax.x, metric.UvMin.y) +
                                      new Vector2(context.Extent, -context.Extent);
        uvList[symbolsPassed*4 + 2] = new Vector2(metric.UvMax.x, metric.UvMax.y) +
                                      new Vector2(context.Extent, context.Extent);
        uvList[symbolsPassed*4 + 3] = new Vector2(metric.UvMin.x, metric.UvMax.y) +
                                      new Vector2(-context.Extent, context.Extent);

        uvList[symbolsPassed*4 + 0] /= FontStorage.DEFAULT_TEX_SIZE;
        uvList[symbolsPassed*4 + 1] /= FontStorage.DEFAULT_TEX_SIZE;
        uvList[symbolsPassed*4 + 2] /= FontStorage.DEFAULT_TEX_SIZE;
        uvList[symbolsPassed*4 + 3] /= FontStorage.DEFAULT_TEX_SIZE;

        colorList[symbolsPassed*4 + 0] = (c == IMAGE_LITERAL) ? Color.white : context.Color;
        colorList[symbolsPassed*4 + 1] = (c == IMAGE_LITERAL) ? Color.white : context.Color;
        colorList[symbolsPassed*4 + 2] = (c == IMAGE_LITERAL) ? Color.white : context.Color;
        colorList[symbolsPassed*4 + 3] = (c == IMAGE_LITERAL) ? Color.white : context.Color;

        tangentList[symbolsPassed*4 + 0] = context.GlowColor;
        tangentList[symbolsPassed*4 + 1] = context.GlowColor;
        tangentList[symbolsPassed*4 + 2] = context.GlowColor;
        tangentList[symbolsPassed*4 + 3] = context.GlowColor;

        int offset = context.TriangleOffset*4;
        charToVertexMap[i] = offset;

        triangleList[symbolsPassed*6 + 0] = 0 + offset;
        triangleList[symbolsPassed*6 + 1] = 3 + offset;
        triangleList[symbolsPassed*6 + 2] = 2 + offset;
        triangleList[symbolsPassed*6 + 3] = 0 + offset;
        triangleList[symbolsPassed*6 + 4] = 2 + offset;
        triangleList[symbolsPassed*6 + 5] = 1 + offset;

        context.TriangleOffset++;

        context.X += (metric.Width + context.LetterSpacing);
        // Restore
        context.Extent = View_TextField_Context.EXTENT;
        symbolsPassed++;
      }
      lastLineChars.Add(concatText.Length - 1);
      lines.Add(context.X);
      // apply result
      if (result.LastCharIndex == -1 && concatText.Length != 0)
      {
        result.LastCharIndex = concatText.Length - 1;
        result.Width = context.X;
        result.LastChar = concatText[result.LastCharIndex];
      }

      result.LinesCount = lines.Count;

      #endregion

      if (vertexList.Length == 0)
        return result;

      #region ALIGN

      // Horiz alignment По последнему символу в строке
      Vector2[] prevLastQuad = null;
      for (int i = 0; i < lastLineChars.Count; ++i)
      {
        if (lastLineChars[i] < 0)
          continue;

        Style style = styleMap[lastLineChars[i]];
        int offsetWidth = (int) bounds.LeftTop.x + 1;

        if (style.Align == UnityEngine.TextAlignment.Right)
        {
          offsetWidth += (int) bounds.Width - lines[i];
        }
        else if (style.Align == UnityEngine.TextAlignment.Center)
        {
          offsetWidth += (int) (bounds.Width - lines[i])/2;
        }

        int start = 0;
        int end = lastLineChars[i];
        if (i > 0)
          start = lastLineChars[i - 1] + 1;


        Vector2[] firstQuad = null;
        Vector2[] lastQuad = null;
        for (int j = start; j < end + 1; ++j)
        {
          int vert = charToVertexMap[j];
          if (vert > -1)
          {
            for (int k = 0; k < 4; ++k)
            {
              Vector3 vertex = vertexList[vert + k];
              vertex.x += offsetWidth;
              vertexList[vert + k] = vertex;
            }

            // Save quads
            if (j == end)
            {
              lastQuad = new Vector2[4];
              for (int k = 0; k < 4; ++k)
              {
                lastQuad[k] = vertexList[vert + k];
              }
            }

            if (firstQuad == null)
            {
              firstQuad = new Vector2[4];
              for (int k = 0; k < 4; ++k)
              {
                firstQuad[k] = vertexList[vert + k];
              }
            }
          }
        }

        // Test intersection for right teg only
        if (style.Align == UnityEngine.TextAlignment.Right && firstQuad != null && prevLastQuad != null)
        {
          // intersect line
          if (firstQuad[3].y <= prevLastQuad[0].y)
          {
            float delta = prevLastQuad[1].x - firstQuad[0].x;
            if (delta > result.ExpectedExtent)
            {
              result.ExpectedExtent = delta;
            }
          }
        }

        prevLastQuad = lastQuad;
      }

      // Vert alignment
      int height = context.Y;
      var offsetHeight = (int) bounds.LeftTop.y;
      if (align == TextAlignment.BottomCenter || align == TextAlignment.BottomLeft || align == TextAlignment.BottomRight)
      {
        offsetHeight += (int) (bounds.Height - height);
      }
      else if (align == TextAlignment.MiddleCenter || align == TextAlignment.MiddleLeft ||
               align == TextAlignment.MiddleRight)
      {
        offsetHeight += (int) ((bounds.Height - height)/2);
      }
      if (offsetHeight != 0)
      {
        for (int v = 0; v < vertexList.Length; ++v)
        {
          vertexList[v] = new Vector3(vertexList[v].x, vertexList[v].y + offsetHeight, vertexList[v].z);
        }
      }

      #endregion

      #region AUTO HEIGHT + ADJUSTMENT

      UpdateLocalBoundsWithHeight(margin, bounds, height, autoHeight, minHeight);

      #endregion

      // Submit
      textShape.FillMesh.vertices = vertexList;
      textShape.FillMesh.uv = uvList;
      textShape.FillMesh.tangents = tangentList;
      textShape.FillMesh.colors = colorList;
      textShape.FillMesh.triangles = triangleList;
      textShape.FillMaterial.RenderMaterial.SetTexture("_FillTex", concatCharSet[0].Tex);

      ////Profiler.EndSample();
      result.Height = context.Y;
      return result;
    }

    private void UpdateLocalBoundsWithHeight(Margin margin, Bounds bounds, int height, bool autoHeight, float minHeight)
    {
      const float TOLERANCE = 0.01f;
      // Math.Abs(minHeight + 1) > TOLERANCE eq minHeight != -1
      bool isMinHeight = height < minHeight && Math.Abs(minHeight + 1f) > TOLERANCE;

      if (height > bounds.Height || autoHeight || isMinHeight)
      {
        var newLocalBounds = new Bounds {LeftTop = _target.LocalBounds.LeftTop};
        newLocalBounds.RightBottom = new Vector3(_target.LocalBounds.RightBottom.x,
          newLocalBounds.LeftTop.y + (isMinHeight ? minHeight : height + margin.top + margin.bottom));
        _target.LocalBounds = newLocalBounds;
        bounds.RightBottom = new Vector3(bounds.RightBottom.x, bounds.LeftTop.y + (isMinHeight ? minHeight : height));
      }
    }

    private int GetY(int lineCount, int fontSize, float lineSpacing)
    {
      return (lineCount - 1)*(int) (fontSize*lineSpacing) + fontSize;
    }
  }
}
