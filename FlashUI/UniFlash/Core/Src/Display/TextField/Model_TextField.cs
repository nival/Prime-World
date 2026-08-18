using System;
using System.Collections.Generic;
using UnityEngine;

namespace Flash
{
  internal class Model_TextField : IModel_TextField
  {
    private string _text;
    private readonly List<IFontMetrics> _charSet = new List<IFontMetrics>();
    private FormatedText _formatedText;
    private List<KeyValuePair<object, List<IFontMetrics>>> _formatedCharSet;

    public List<IFontMetrics> CharSet
    {
      get { return _charSet; }
    }

    public List<KeyValuePair<object, List<IFontMetrics>>> FormatedCharSet
    {
      get { return _formatedCharSet; }
    }

    public static IFontMetrics GetMetric(char c, Font font, int fontSize, FontStyle fontStyle)
    {
      IFontMetrics metric = null;
      IFontStorage fontStorage = FontStorage.GetStorage(font, fontSize, fontStyle);
      if (fontStorage != null)
      {
        fontStorage.SetString(new string(c, 1));
        fontStorage.TryGetMetric('\0', c, ref metric);
      }

      return metric;
    }

    public string GetText()
    {
      return _text;
    }

    public void SetText(string text, Font font, int fontSize, FontStyle fontStyle)
    {
      _formatedText = null;

      IFontStorage fontStorage = null;
      if (!string.IsNullOrEmpty(text))
      {
        fontStorage = FontStorage.GetStorage(font, fontSize, fontStyle);
        try
        {
          fontStorage.SetString(text);
        }
        catch (Exception e)
        {
          Debug.LogError(e.Message + "\n" + e.StackTrace);
        }
      }

      _text = text;
      _charSet.Clear();

      if (fontStorage != null)
      {
        char prev = '\0';
        foreach (char c in text)
        {
          IFontMetrics metric = null;
          fontStorage.TryGetMetric(prev, c, ref metric);
          prev = c;
          _charSet.Add(metric);
        }
      }
    }
    public FormatedText GetFormatedText()
    {
      return _formatedText;
    }
    public void SetFormatedText(FormatedText formatedText)
    {
      _text = string.Empty;
      _formatedText = formatedText;

      if (_formatedCharSet == null)
        _formatedCharSet = new List<KeyValuePair<object, List<IFontMetrics>>>( _formatedText.Count );

      _formatedCharSet.Clear();

      if(_formatedText==null)
        return;

      foreach (FormatEntry entry in _formatedText)
      {
        Style style = entry.Style;
        IFontStorage fontStorage = FontStorage.GetStorage(style.Font, style.FontSize, style.FontStyle);
        entry.Style.SetBaseLine(fontStorage.BaseLine);

        if (entry.Data is string)
        {
          string text = (string)entry.Data;
          _text += text;
          try
          {
            fontStorage.SetString(text);
          }
          catch (Exception e)
          {
            Debug.LogError(e.Message + "\n" + e.StackTrace);
          }

          List<IFontMetrics> metrics = new List<IFontMetrics>( text.Length );
          char prev = '\0';
          foreach (char c in text)
          {
            IFontMetrics metric = null;
            fontStorage.TryGetMetric(prev,c, ref metric);
            prev = c;
            metrics.Add(metric);
          }

          _formatedCharSet.Add(new KeyValuePair<object, List<IFontMetrics>>(text, metrics));
        }

        if (entry.Data is Texture2D)
        {
          Texture2D texture = (Texture2D)entry.Data;

          fontStorage.SetTexture(texture);

          IFontMetrics metric = null;
          fontStorage.TryGetMetric(texture, ref metric);
          //TODO: Move to metric creation
          Metrics m = metric as Metrics;
          if (m != null)
          {
            m.Floor = 2;
          }

          _formatedCharSet.Add(new KeyValuePair<object, List<IFontMetrics>>(entry.Data, new List<IFontMetrics> { metric }));
        }
      }
    }
  }

  internal interface IModel_TextField
  {
    string GetText();
    void SetText(string text, Font font, int fontSize, FontStyle fontStyle);
    FormatedText GetFormatedText();
    void SetFormatedText(FormatedText formatedText);
    List<IFontMetrics> CharSet { get; }
    List<KeyValuePair<object, List<IFontMetrics>>> FormatedCharSet { get; }
  }
}

