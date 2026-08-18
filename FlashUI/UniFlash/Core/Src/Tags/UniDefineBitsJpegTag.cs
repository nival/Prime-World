using System.IO;
using System.Runtime.Serialization;
using Flash.Utils;
using ICSharpCode.SharpZipLib.Zip.Compression.Streams;
using SwfDotNet.IO.Tags;
using SwfDotNet.IO.Tags.Types;
using UnityEngine;

namespace Flash
{
  [System.Serializable]
  public class UniDefineBitsJpegTag : UniBaseShapeTag, ISerializable
  {
    private int _textureIdResources = -1;
    public int TextureIdResources
    {
      get { return _textureIdResources; }
      set { _textureIdResources = value; }
    }
    private Texture2D _texture;
    public Texture2D Texture
    {
      get { return _texture; }
    }

    public override void GetObjectData( SerializationInfo info, StreamingContext context )
    {
      base.GetObjectData( info, context );

      Flash.SerializeHelpers.Pack( info, "_textureIdResources", _textureIdResources );
    }

    public UniDefineBitsJpegTag( SerializationInfo info, StreamingContext context )
      : base( info, context )
    {
      Flash.SerializeHelpers.Unpack( info, "_textureIdResources", out _textureIdResources );
    }

    public UniDefineBitsJpegTag( DefineBitsJpeg2Tag baseTag, UniSwf owner )
      : base( baseTag, owner )
    {
      LoadJpegData( baseTag.JpegData );
      PostInit();
    }
    public UniDefineBitsJpegTag( DefineBitsJpeg3Tag baseTag, UniSwf owner )
      : base( baseTag, owner )
    {
      LoadJpegData( baseTag.JpegData );

      //if ( ( baseTag.AlphaData != null && baseTag.AlphaData.Length > 0 ) )
      //  Debug.LogError( "UNALLOWED BITMAP FORMAT ASSERT : DefineBitsJpeg3Tag" );

      // unzip alpha
      InflaterInputStream zip_stream = new InflaterInputStream( new MemoryStream( baseTag.AlphaData ) );
      int image_size = _texture.width * _texture.height;
      byte[] unpacked_alpha = new byte[image_size];
      zip_stream.Read( unpacked_alpha, 0, image_size );

      Color[] pixels = _texture.GetPixels();
      for ( int i = 0; i < pixels.Length; ++i )
      {
        pixels[i].a = unpacked_alpha[i] / 255.0F;
        // premul alpha
        pixels[i].r /= pixels[i].a;
        pixels[i].g /= pixels[i].a;
        pixels[i].b /= pixels[i].a;
      }

      Texture2D texWithAlpha = new Texture2D( _texture.width, _texture.height, TextureFormat.ARGB32, false );
      texWithAlpha.SetPixels( pixels );
      texWithAlpha.Apply();

      /*if (Application.isEditor)
        DestroyImmediate(_texture);
      else
        Destroy(_texture);*/

      _texture = texWithAlpha;

      PostInit();
    }
    public UniDefineBitsJpegTag( DefineBitsTag baseTag, UniSwf owner )
      : base( baseTag, owner )
    {
      LoadJpegData( baseTag.JpegData );
      PostInit();
    }
    public UniDefineBitsJpegTag( DefineBitsLossLessTag baseTag, UniSwf owner )
      : base( baseTag, owner )
    {
      _texture = new Texture2D( baseTag.BitmapWidth, baseTag.BitmapHeight, TextureFormat.ARGB32, false );

      Color[] colors = null;
      if ( baseTag.BitmapFormat == 5 )
      {
        colors = new Color[baseTag.BitmapData.bitmapPixelDataPix24.Length];
        for ( int j = 0; j < baseTag.BitmapHeight; ++j )
        {
          for ( int i = 0; i < baseTag.BitmapWidth; ++i )
          {
            int direct = i + j * baseTag.BitmapWidth;
            int invert = ( baseTag.BitmapHeight - j - 1 ) * baseTag.BitmapWidth + i;
            colors[direct] = FlashToUnityConverter.ConvertColor( baseTag.BitmapData.bitmapPixelDataPix24[invert].PixelColor );
          }
        }
      }
      else if ( baseTag.BitmapFormat == 4 )
      {
        Debug.LogError( "Bitmap Format 4 is not implemented" );
      }
      // TODO: ����������� �������� ���
      else if ( baseTag.BitmapFormat == 3 )
      {
        colors = new Color[baseTag.ColorMapData.ColorMapPixelData.Length];
        for ( int j = 0; j < baseTag.BitmapHeight; ++j )
        {
          for ( int i = 0; i < baseTag.BitmapWidth; ++i )
          {
            int direct = i + j * baseTag.BitmapWidth;
            int invert = ( baseTag.BitmapHeight - j - 1 ) * baseTag.BitmapWidth + i;
            colors[direct] = FlashToUnityConverter.ConvertColor( baseTag.ColorMapData.ColorTableRGB[baseTag.ColorMapData.ColorMapPixelData[invert]] );
          }
        }
      }

      _texture.SetPixels( colors );

      PostInit();
    }
    public UniDefineBitsJpegTag( DefineBitsLossLess2Tag baseTag, UniSwf owner )
      : base( baseTag, owner )
    {
      _texture = new Texture2D( baseTag.BitmapWidth, baseTag.BitmapHeight, TextureFormat.ARGB32, false );

      Color[] colors = new Color[baseTag.AlphaBitmapData.BitmapPixelData.Length];
      int hIndex = baseTag.BitmapHeight - 1;
      for ( int j = 0; j < baseTag.BitmapHeight; ++j )
      {
        for ( int i = 0; i < baseTag.BitmapWidth; ++i )
        {
          int direct = j * baseTag.BitmapWidth + i;
          int invert = ( hIndex - j ) * baseTag.BitmapWidth + i;
          colors[direct] = FlashToUnityConverter.ConvertColor( baseTag.AlphaBitmapData.BitmapPixelData[invert] );
          // premul alpha
          colors[direct].r /= colors[direct].a;
          colors[direct].g /= colors[direct].a;
          colors[direct].b /= colors[direct].a;
        }
      }
      _texture.SetPixels( colors );

      PostInit();
    }
    public UniDefineBitsJpegTag( Texture2D texture, UniSwf owner )
      : base( null, owner )
    {
      if ( _texture == null )
        return;

      _texture = texture;
      PostInit();
    }
    public void GenerateShape()
    {
      if ( _shapes.Count != 0 )
        return;

      // Generate shape
      ShapeElement shape = new ShapeElement();
      BitmapFill style = new BitmapFill( FillStyleType.ClippedBitmapFill );
      style.BitmapId = Id;
      shape.UniFillStyle = new UniFillStyle( style, Swf );
      
      Vector2 textureSize = _swf.AtlasData.Sizes[_textureIdResources];
      
      shape.Points.Add( Vector3.zero );
      shape.Points.Add( new Vector3( textureSize.x, 0, 0 ) );
      shape.Points.Add( new Vector3( textureSize.x, textureSize.y, 0 ) );
      shape.Points.Add( new Vector3( 0, textureSize.y, 0 ) );
      shape.Points.Add( Vector3.zero );
      
      CreateMeshes( Swf, shape, _swf.Name );
      shape.Release();
      _shapes.Add( shape );

      _localBounds.LeftTop = new Vector3( 0, 0 );
      _localBounds.RightBottom = new Vector3( textureSize.x, textureSize.y );
    }

    private void LoadJpegData( byte[] jpegData )
    {
      byte[] data = null;

      int offset = 0;
      if ( jpegData[0] != 0xFF || jpegData[1] != 0xD8 )
        offset = 4; // Offset for the JFIF format

      data = new byte[jpegData.Length - offset];
      for ( int i = offset, j = 0; i < jpegData.Length; i++, j++ )
        data[j] = jpegData[i];

      _texture = new Texture2D( 1, 1, TextureFormat.ARGB32, false );
      _texture.LoadImage( data );
    }
    private void PostInit()
    {
      _texture.wrapMode = TextureWrapMode.Clamp;
      _texture.filterMode = FilterMode.Bilinear;
      _texture.Apply();
      //GameObject g = new GameObject("tex origin", typeof(GUITexture));
      //g.GetComponent<GUITexture>().texture = _texture;
    }
  }
}
