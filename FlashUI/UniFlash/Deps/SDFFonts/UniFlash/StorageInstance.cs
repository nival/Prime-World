using System.Collections.Generic;
using Flash;
using UnityEngine;

using Font = SDFFonts.Font;

namespace SDFFonts.UniFlash
{
    public class StorageInstance : IFontStorage
    {
        public string Name { get; private set; }
        public FontStyle Style { get; private set; }
        public int Size { get; private set; }

        private readonly Dictionary<char, MetricsInstance> _simpleMetrics = new Dictionary<char, MetricsInstance>();
        private readonly Dictionary<uint, MetricsInstance> _kernedMetrics = new Dictionary<uint, MetricsInstance>();
        private readonly Dictionary<Texture2D, MetricsInstance> _iconMetrics = new Dictionary<Texture2D, MetricsInstance>();

        private Font _font;
        private readonly float _size;
        private readonly float _scale;
        private readonly float _lineHeight;
        private readonly float _baseLine;
        private readonly int _intBaseLine;
        private readonly IconCache _iconCache;

        public StorageInstance(string name, Font font, int size, IconCache iconCache)
        {
            _iconCache = iconCache;
            _font = font;
            Name = name;
            Style = _font.FontStyle;
            Size = size;
            _size = (float)size;
            _scale = _size / (float)(_font.BaseFontSize);
            _lineHeight = (float)(_font.LineHeight) * _scale;
            _baseLine = (float)(_font.BaseLine) * _scale;
            _intBaseLine = Mathf.RoundToInt(_baseLine);
        }

        public override string ToString()
        {
            return string.Format("StorageInstance for \"{0}\" ({1}) {2}", Name, Style, Size);
        }

        #region IFontStorage

        public void SetTexture(Texture2D icon)
        {
            if (icon == null)
                return;

            MetricsInstance metricsInstance;
            if (_iconMetrics.TryGetValue(icon, out metricsInstance))
                return;

            Vector2 uvMin = default(Vector2);
            Vector2 uvMax = default(Vector2);
            if (!_iconCache.GetIcon(icon, ref uvMin, ref uvMax))
                return;

            float sizeScale = Mathf.Min(_lineHeight / (float)icon.height, 1f);
            float targetWidth = (float)icon.width * sizeScale;
            float targetHeight = (float)icon.height * sizeScale;
            float targetOffsetY = targetHeight > _baseLine ? 0f : _baseLine - targetHeight;

            MetricsExt ext = new MetricsExt {
                FontSize = _size,
                Size = new Vector2(targetWidth, targetHeight),
                Offset = new Vector2(0f, targetOffsetY),
                Advance = new Vector2(targetWidth, _lineHeight),
                LineHeight = _lineHeight,
                BaseLine = _baseLine,
                Kerning = 0f,
            };

            metricsInstance = new MetricsInstance(_iconCache.Tex, uvMin, uvMax, ext);
            _iconMetrics[icon] = metricsInstance;
        }

        public void SetString(string charset)
        {
            char prev = '\0';
            foreach (var @char in charset)
            {
                MetricsInstance metricsInstance;
                if (!_simpleMetrics.TryGetValue(@char, out metricsInstance))
                {
                    Glyph glyph = _font[@char];
                    metricsInstance = new MetricsInstance(glyph, _scale);
                    _simpleMetrics[@char] = metricsInstance;
                }

                if (prev != '\0')
                {
                    uint id = ((uint)@char << 16) + (uint)prev;
                    MetricsInstance kerningInstance;
                    if (!_kernedMetrics.TryGetValue(id, out kerningInstance))
                    {
                        int kerning = _font[prev, @char];
                        if (kerning != 0)
                        {
                            kerningInstance = new MetricsInstance(metricsInstance, kerning);
                            _kernedMetrics[id] = kerningInstance;
                        }
                    }
                }

                prev = @char;
            }
        }

        public void TryGetMetric(Texture2D icon, ref IFontMetrics metric)
        {
            MetricsInstance metricsInstance;
            _iconMetrics.TryGetValue(icon, out metricsInstance);
            metric = metricsInstance;
        }

        public void TryGetMetric(char prev, char @char, ref IFontMetrics metric)
        {
            uint id = ((uint)@char << 16) + (uint)prev;
            MetricsInstance metricsInstance;
            if (!_kernedMetrics.TryGetValue(id, out metricsInstance))
            {
                _simpleMetrics.TryGetValue(@char, out metricsInstance);
            }
            metric = metricsInstance;
        }

        public int BaseLine { get { return _intBaseLine; } }

        #endregion
    }
}