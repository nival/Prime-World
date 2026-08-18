using UnityEngine;

namespace Flash
{
    public interface IFontStorage
    {
        int BaseLine { get; }

        void TryGetMetric( char prev, char character, ref IFontMetrics metric );

        void TryGetMetric( Texture2D character, ref IFontMetrics metric );

        void SetString( string characters );

        void SetTexture( Texture2D texture );
    }
}