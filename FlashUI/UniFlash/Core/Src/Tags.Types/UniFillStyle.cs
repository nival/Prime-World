using System;
using System.Collections.Generic;
using Flash.Utils;
using SwfDotNet.IO.Tags.Types;
using UnityEngine;
using System.Runtime.Serialization;

namespace Flash
{
  [System.Serializable]
  public class UniFillStyle : ISerializable
  {

    private UniFillStyleType _type = UniFillStyleType.UniSolidFill;
    public UniFillStyleType Type
    {
      get { return _type; }
    }
    private Color _fillColor = Color.white;
    public Color FillColor
    {
      get { return _fillColor; }
    }
    private int _bitmapId;
    public int BitmapId
    {
      get { return _bitmapId; }
    }
    private Matrix4x4 _bitmapTransform = Matrix4x4.identity;
    public Matrix4x4 BitmapTransform
    {
      get { return _bitmapTransform; }
      set { _bitmapTransform = value; }
    }
    private TextureTransform _textureTransform = new TextureTransform();
    public TextureTransform TextureTransform
    {
      get { return _textureTransform; }
      set { _textureTransform = value; }
    }
    private List<UniGradientRecord> _gradientRecords;
    public List<UniGradientRecord> GradientRecords
    {
      get { return _gradientRecords; }
    }
    private int _gradiendId = -1;
    public int GradientID
    {
      get { return _gradiendId; }
      set { _gradiendId = value; }
    }
    private GradientSpreadMode _spreadMode = GradientSpreadMode.PadMode;
    public GradientSpreadMode SpreadMode
    {
      get { return _spreadMode; }
    }
    private float _focalPoint;
    public float FocalPoint
    {
      get { return _focalPoint; }
    }
    private bool _endStyle;
    public bool EndStyle
    {
      get { return _endStyle; }
    }

    public void GetObjectData( SerializationInfo info, StreamingContext context )
    {
      Flash.SerializeHelpers.Pack( info, "_type", _type );
      Flash.SerializeHelpers.Pack( info, "_fillColor", _fillColor );
      Flash.SerializeHelpers.Pack( info, "_bitmapId", _bitmapId );
      Flash.SerializeHelpers.Pack( info, "_bitmapTransform", _bitmapTransform );
      Flash.SerializeHelpers.Pack( info, "_textureTransform", _textureTransform );
      Flash.SerializeHelpers.Pack( info, "_gradientRecords", _gradientRecords );
      Flash.SerializeHelpers.Pack( info, "_gradiendId", _gradiendId );
      Flash.SerializeHelpers.Pack( info, "_spreadMode", _spreadMode );
      Flash.SerializeHelpers.Pack( info, "_focalPoint", _focalPoint );
      Flash.SerializeHelpers.Pack( info, "_endStyle", _endStyle );
    }

    public UniFillStyle( SerializationInfo info, StreamingContext context )
    {
      Flash.SerializeHelpers.Unpack( info, "_type", out _type );
      Flash.SerializeHelpers.Unpack( info, "_fillColor", out _fillColor );
      Flash.SerializeHelpers.Unpack( info, "_bitmapId", out _bitmapId );
      Flash.SerializeHelpers.Unpack( info, "_bitmapTransform", out _bitmapTransform );
      Flash.SerializeHelpers.Unpack( info, "_textureTransform", out _textureTransform );
      Flash.SerializeHelpers.Unpack( info, "_gradientRecords", out _gradientRecords );
      Flash.SerializeHelpers.Unpack( info, "_gradiendId", out _gradiendId );
      Flash.SerializeHelpers.Unpack( info, "_spreadMode", out _spreadMode );
      Flash.SerializeHelpers.Unpack( info, "_focalPoint", out _focalPoint );
      Flash.SerializeHelpers.Unpack( info, "_endStyle", out _endStyle );
    }

    public UniFillStyle() { }
    public UniFillStyle( FillStyle fillStyle, UniSwf swf )
    {
      if ( fillStyle is SolidFill )
      {
        _type = UniFillStyleType.UniSolidFill;
        _fillColor = FlashToUnityConverter.ConvertColor( ( fillStyle as SolidFill ).FillColor );
      }
      else if ( fillStyle is BitmapFill )
      {
        _type = UniFillStyleType.UniBitmapFill;
        if ( fillStyle.FillStyleType == FillStyleType.RepeatingBitmapFill || fillStyle.FillStyleType == FillStyleType.NonSmoothedRepeatingBitmap )
        {
          _type = UniFillStyleType.UniRepeatingBitmapFill;
        }

        _bitmapId = ( fillStyle as BitmapFill ).BitmapId;
        _bitmapTransform = FlashToUnityConverter.ConvertBitmapMatrix( ( fillStyle as BitmapFill ).BitmapTransform );
      }
      else if ( fillStyle is GradientFill )
      {
        if ( fillStyle.FillStyleType == FillStyleType.LinearGradientFill )
          _type = UniFillStyleType.UniLinearGradientFill;
        if ( fillStyle.FillStyleType == FillStyleType.RadialGradientFill )
          _type = UniFillStyleType.UniRadialGradientFill;
        if ( fillStyle.FillStyleType == FillStyleType.FocalRadialGradientFill )
          _type = UniFillStyleType.UniFocalRadialGradientFill;

        GradientFill grFill = fillStyle as GradientFill;

        _bitmapTransform = FlashToUnityConverter.ConvertGradientMatrix( grFill.GradientTransform );
        GradientRecordCollection gradients = grFill.Gradients;
        if ( _type == UniFillStyleType.UniFocalRadialGradientFill )
          _focalPoint = ( grFill.Gradients as FocalGradientRecordCollection ).FocalPoint;

        if ( swf.AtlasIsNotCached() )
        {
          _gradientRecords = new List<UniGradientRecord>( gradients.Count );

          foreach ( GradientRecord rec in gradients )
          {
            _gradientRecords.Add( new UniGradientRecord( rec.Ratio, FlashToUnityConverter.ConvertColor( rec.Color ) ) );
          }
        }

        TextureUtils.GenerateGradient( this, swf );

        _spreadMode = gradients.SpreadMode;
      }
    }
    public UniFillStyle( MorphFillStyle fillStyle, UniSwf swf, bool endStyle )
    {
      _endStyle = endStyle;

      if ( fillStyle is MorphSolidFill )
      {
        _type = UniFillStyleType.UniSolidFill;
        _fillColor = FlashToUnityConverter.ConvertColor( ( fillStyle as MorphSolidFill ).StartColor );
        //override
        if ( endStyle )
          _fillColor = FlashToUnityConverter.ConvertColor( ( fillStyle as MorphSolidFill ).EndColor );
      }
      else if ( fillStyle is MorphBitmapFill )
      {
        _type = UniFillStyleType.UniBitmapFill;

        _bitmapId = ( fillStyle as MorphBitmapFill ).BitmapId;
        _bitmapTransform = FlashToUnityConverter.ConvertBitmapMatrix( ( fillStyle as MorphBitmapFill ).StartBitmapMatrix );
        //override
        if ( endStyle )
          _bitmapTransform = FlashToUnityConverter.ConvertBitmapMatrix( ( fillStyle as MorphBitmapFill ).EndBitmapMatrix );
      }
      else if ( fillStyle is MorphGradientFill )
      {
        if ( fillStyle.FillStyleType == MorphFillStyleType.LinearGradientFill )
          _type = UniFillStyleType.UniLinearGradientFill;
        if ( fillStyle.FillStyleType == MorphFillStyleType.RadialGradientFill )
          _type = UniFillStyleType.UniRadialGradientFill;
        if ( fillStyle.FillStyleType == MorphFillStyleType.FocalGradientFill )
        {
          _type = UniFillStyleType.UniFocalRadialGradientFill;
        }

        MorphGradientFill grFill = fillStyle as MorphGradientFill;

        _bitmapTransform = FlashToUnityConverter.ConvertGradientMatrix( grFill.StartGradientMatrix );
        if ( endStyle )
          _bitmapTransform = FlashToUnityConverter.ConvertGradientMatrix( grFill.EndGradientMatrix );

        MorphGradientCollection gradients = grFill.Gradients;
        if ( gradients == null )
          return;

        if ( _type == UniFillStyleType.UniFocalRadialGradientFill )
        {
          if ( !endStyle )
            _focalPoint = gradients.StartFocalPoint;
          else
            _focalPoint = gradients.EndFocalPoint;
        }

        if ( swf.AtlasIsNotCached() )
        {
          _gradientRecords = new List<UniGradientRecord>( gradients.Count );

          foreach ( MorphGradRecord rec in gradients )
          {
            if ( !endStyle )
              _gradientRecords.Add( new UniGradientRecord( rec.StartRatio, FlashToUnityConverter.ConvertColor( rec.StartColor ) ) );
            else
              _gradientRecords.Add( new UniGradientRecord( rec.EndRatio, FlashToUnityConverter.ConvertColor( rec.EndColor ) ) );
          }
        }

        TextureUtils.GenerateGradient( this, swf );
      }
    }
  }
  public enum UniFillStyleType
  {
    UniSolidFill,
    UniBitmapFill,
    UniLinearGradientFill,
    UniRadialGradientFill,
    UniFocalRadialGradientFill,
    UniRepeatingBitmapFill
  }
  [System.Serializable]
  public struct UniGradientRecord : ISerializable
  {
    public int ratio;
    public Color color;

    public UniGradientRecord( int r, Color c )
    {
      ratio = r;
      color = c;
    }

    public void GetObjectData( SerializationInfo info, StreamingContext context )
    {
      Flash.SerializeHelpers.Pack( info, "ratio", ratio );
      Flash.SerializeHelpers.Pack( info, "color", color );
    }

    public UniGradientRecord( SerializationInfo info, StreamingContext context )
    {
      Flash.SerializeHelpers.Unpack( info, "ratio", out ratio );
      Flash.SerializeHelpers.Unpack( info, "color", out color );
    }
  }
}
