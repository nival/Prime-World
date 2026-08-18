using System;
using System.Collections.Generic;
using System.IO;
using SDFFonts.Tools;
using UnityEngine;
using UnityEngine.Assertions;

namespace SDFFonts
{
    [Serializable]
    public class Font
    {
        private const char DefaultChar = '#';

        [SerializeField]
        private string _fontName;
        [SerializeField]
        private FontStyle _fontStyle;
        [SerializeField]
        private int _fontSize;
        [SerializeField]
        private Texture2D _glyphAtlas;
        [SerializeField]
        private TextAsset _glyphDescription;

        private readonly Dictionary<char, Glyph> _glyphs = new Dictionary<char, Glyph>();
        private readonly Dictionary<char, Dictionary<char, int>> _kerning = new Dictionary<char, Dictionary<char, int>>();

        private int _lineHeight;
        private int _baseLine;

        public string FontName { get { return _fontName; } }
        public FontStyle FontStyle { get { return _fontStyle; } }
        public int BaseFontSize { get { return _fontSize; } }
        public int LineHeight { get { return _lineHeight; } }
        public int BaseLine { get { return _baseLine; } }

        public override string ToString( )
        {
            return string.Format("{0} ({1})", _fontName, _fontStyle);
        }

        public Glyph this[char index]
        {
            get
            {
                Glyph glyph;
                if (!_glyphs.TryGetValue(index, out glyph))
                    glyph = _glyphs[DefaultChar];
                return glyph;
            }
        }

        public int this[char first, char second]
        {
            get
            {
                Dictionary<char, int> kerning;
                if (_kerning.TryGetValue(first, out kerning))
                {
                    int value;
                    kerning.TryGetValue(second, out value);
                    return value;
                }
                else
                {
                    return 0;
                }
            }
        }

        public void LoadFont()
        {
            //TODO: Maybe improve AngelCode .fnt parser?

            Assert.IsTrue(_glyphAtlas != null);
            Assert.IsTrue(_glyphDescription != null);

            using (var reader = new StringReader(_glyphDescription.text))
            {
                KeyValueParser commonParser = new KeyValueParser();
                KeyValueParser charParser = new KeyValueParser();
                KeyValueParser kerningParser = new KeyValueParser();

                string line;
                while ((line = reader.ReadLine()) != null)
                {
                    if (line.StartsWith("common "))
                    {
                        commonParser.Fill(line);
                        _lineHeight = commonParser.GetValue("lineHeight", 0);
                        _baseLine = commonParser.GetValue("base", 0);
                    }
                    else if (line.StartsWith("char "))
                    {
                        charParser.Fill(line);
                        LoadGlyphData(charParser);
                    }
                    else if (line.StartsWith("kerning "))
                    {
                        kerningParser.Fill(line);
                        LoadKerningData(kerningParser);
                    }
                }
            }
        }

        private void LoadGlyphData(KeyValueParser parser)
        {
            int charId = parser.GetValue("id", 0);
            char charValue = Convert.ToChar(charId);
            Glyph glyph = new Glyph {
                Char = charValue,
                FontSize = _fontSize,
                LineHeight = _lineHeight,
                BaseLine = _baseLine,
                X = parser.GetValue("x", 0),
                Y = parser.GetValue("y", 0),
                Width = parser.GetValue("width", 0),
                Height = parser.GetValue("height", 0),
                XOffset = parser.GetValue("xoffset", 0),
                YOffset = parser.GetValue("yoffset", 0),
                XAdvance = parser.GetValue("xadvance", 0),
                YAdvance = _lineHeight,
                Atlas = _glyphAtlas,
            };
            glyph.CalculateUvs();
            _glyphs[charValue] = glyph;
        }

        private void LoadKerningData(KeyValueParser parser)
        {
            int firstCharId = parser.GetValue("first", 0);
            int secondCharId = parser.GetValue("second", 0);
            int kerning = parser.GetValue("amount", 0);
            char firstChar = Convert.ToChar(firstCharId);
            char secondChar = Convert.ToChar(secondCharId);

            Dictionary<char, int> kerningSet;
            if (!_kerning.TryGetValue(firstChar, out kerningSet))
            {
                kerningSet = new Dictionary<char, int>();
                _kerning[firstChar] = kerningSet;
            }
            kerningSet[secondChar] = kerning;
        }
    }
}
