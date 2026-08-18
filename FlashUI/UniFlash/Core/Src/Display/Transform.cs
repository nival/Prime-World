#define ENABLE_POST_PROCESS
using System;
using Flash.Utils;
using SwfDotNet.IO.Tags;
using SwfDotNet.IO.Tags.Types;
using UnityEngine;

namespace Flash
{
  public class Transform : ICloneable
  {
    #region positioning

    private Vector3 _position = Vector3.zero;
    private Vector3 _rotation = Vector3.zero;
    private Vector3 _scale = Vector3.one;

    private Vector3 _worldScale = Vector3.one;

    private Vector3 _right = new Vector3( 1, 0, 0 );

    private bool _dirtyWorldMatrix;

    private void UpdateVector( Vector3 value, ref Vector3 variable )
    {
      if ( value == variable )
        return;

      variable = value;
      UpdateMatrix();
    }

    private void DecomposeWorldMatrix()
    {
      _dirtyWorldMatrix = false;
      var decomposedMatrix = new DecomposedMatrix();
      MathUtils.DecomposeMatrix( _worldMatrix, ref decomposedMatrix );
      _worldScale = decomposedMatrix.scale;
    }

    public Vector3 Position { get { return _position; } set { UpdateVector( value, ref _position ); } }
    public Vector3 Rotation { get { return _rotation; } set { UpdateVector( value, ref _rotation ); } }
    public Vector3 Scale { get { return _scale; } set { UpdateVector( value, ref _scale ); } }

    public Vector3 Right { get { return _right; } }

    public Vector3 WorldScale
    {
      get
      {
        if ( _dirtyWorldMatrix )
          DecomposeWorldMatrix();
        return _worldScale;
      }
    }

    #endregion

    private float _alpha = 1;
    public float Alpha
    {
      get { return _alpha; }
      set
      {
        if ( _alpha == value )
          return;

        _alpha = value;
        ConcatenateRecursively( false, true );
      }
    }


    private float _concatenatedAlpha = 1;
    public float ConcatenatedAlpha
    {
      get { return _concatenatedAlpha; }
    }


    private bool _hasTransform;
    public bool HasTransform
    {
      get { return _hasTransform; }
    }


    private bool _hasCxForm;
    public bool HasCxForm
    {
      get { return _hasCxForm; }
      set { _hasCxForm = value; }
    }


    private bool _hasColorMatrix;
    public bool HasColorMatrix
    {
      get { return _hasColorMatrix; }
      set { _hasColorMatrix = value; }
    }


    private bool _hasBlendMode;
    public bool HasBlendMode
    {
      get { return _hasBlendMode; }
    }


    private Matrix4x4 _matrix = Matrix4x4.identity;
    public Matrix4x4 Matrix
    {
      get { return _matrix; }
      set
      {
        _matrix = value;
        DecomposeMatrix();
      }
    }


    private Matrix4x4 _worldMatrix = Matrix4x4.identity;
    public Matrix4x4 WorldMatrix
    {
      get
      {
        return _worldMatrix;
      }
      private set
      {
        _dirtyWorldMatrix = true;
        _worldMatrix = value;
      }
    }

    private bool _hasFinalColorTransform;
    public bool HasFinalColorTransform
    {
      get { return _hasFinalColorTransform; }
      set { _hasFinalColorTransform = value; }
    }

    private ColorTransform _colorTransform = new ColorTransform( null );
    public ColorTransform ColorTransform
    {
      get { return _colorTransform; }
      set
      {
        _colorTransform = value;
        ConcatenateRecursively( false, true );
      }
    }

    private ColorTransform _concatenatedColorTransform = new ColorTransform( null );
    public ColorTransform ConcatenatedColorTransform
    {
      get { return _concatenatedColorTransform; }
    }

    private bool _hasFinalColorMatrix;
    public bool HasFinalColorMatrix
    {
      get { return _hasFinalColorMatrix; }
      set { _hasFinalColorMatrix = value; }
    }


    private Matrix4x4 _colorMatrix_mul = Matrix4x4.identity;
    public Matrix4x4 ColorMatrix_mul
    {
      get { return _colorMatrix_mul; }
      set
      {
        _colorMatrix_mul = value;
        ConcatenateRecursively( false, true );
      }
    }


    private Matrix4x4 _concatenatedColorMatrix_mul = Matrix4x4.identity;
    public Matrix4x4 ConcatenatedColorMatrix_mul
    {
      get { return _concatenatedColorMatrix_mul; }
    }


    private Vector4 _colorMatrix_add = Vector4.zero;
    public Vector4 ColorMatrix_add
    {
      get { return _colorMatrix_add; }
      set
      {
        _colorMatrix_add = value;
        ConcatenateRecursively( false, true );
      }
    }


    private Vector4 _concatenatedColorMatrix_add = Vector4.zero;
    public Vector4 ConcatenatedColorMatrix_add
    {
      get { return _concatenatedColorMatrix_add; }
    }


    private BlendMode _blendMode = BlendMode.Normal;
    public BlendMode BlendMode
    {
      get { return _blendMode; }
      set { _blendMode = value; }
    }
    private Color _glowColor = Color.clear;
    public Color GlowColor
    {
      get { return _glowColor; }
      set { _glowColor = value; }
    }
    private float _ratio;
    public float Ratio
    {
      get { return _ratio; }
      set
      {
        _ratio = value;
      }
    }
    private DisplayObject _target;
    public DisplayObject Target
    {
      get { return _target; }
      set
      {
        if(value==_target)
          return;
        
        _target = value;
        UpdateMatrix();
      }
    }
    private bool _autoUpdateMatrix = true;
    private bool AutoUpdateMatrix
    {
      set
      {
        _autoUpdateMatrix = value;
        if ( _autoUpdateMatrix )
          UpdateMatrix();
      }
    }


    public Transform() { }
    public Transform( UniPlaceObjectTag placeTag )
    {
      _hasTransform = placeTag.HasTransform;
      _hasCxForm = placeTag.HasCxForm;
      Matrix = placeTag.Transform;
      _ratio = placeTag.Ratio;
      _colorTransform = placeTag.CxForm;
      _hasBlendMode = placeTag.HasBlendMode;

      if ( placeTag.HasBlendMode )
      {
        _blendMode = placeTag.BlendMode;
      }

      if ( placeTag.HasFilterList )
      {
        FilterList list = placeTag.FilterList;
        for(int i =0; i <  list.Filters.Length; i++ )
        {
          // Color matrix
          if ( list.Filters[i] is ColorMatrixFilter )
          {
            _hasColorMatrix = true;

            float[] matrix = ( (ColorMatrixFilter)list.Filters[i] ).ColorMatrix;

            _colorMatrix_mul[0, 0] = matrix[0];
            _colorMatrix_mul[0, 1] = matrix[1];
            _colorMatrix_mul[0, 2] = matrix[2];
            _colorMatrix_mul[0, 3] = matrix[3];

            _colorMatrix_mul[1, 0] = matrix[5];
            _colorMatrix_mul[1, 1] = matrix[6];
            _colorMatrix_mul[1, 2] = matrix[7];
            _colorMatrix_mul[1, 3] = matrix[8];

            _colorMatrix_mul[2, 0] = matrix[10];
            _colorMatrix_mul[2, 1] = matrix[11];
            _colorMatrix_mul[2, 2] = matrix[12];
            _colorMatrix_mul[2, 3] = matrix[13];

            _colorMatrix_mul[3, 0] = matrix[15];
            _colorMatrix_mul[3, 1] = matrix[16];
            _colorMatrix_mul[3, 2] = matrix[17];
            _colorMatrix_mul[3, 3] = matrix[18];

            _colorMatrix_add = new Vector4( matrix[4], matrix[9], matrix[14], matrix[19] );

            _colorMatrix_add *= 0.0033F;

            break;
          }

          // Glow
          if ( list.Filters[i] is GlowFilter )
          {
            _glowColor = FlashToUnityConverter.ConvertColor( ( (GlowFilter)list.Filters[i] ).GlowColor );
          }
        }
      }
    }

    public void Concatenate( bool transform, bool color )
    {
      if ( _target == null || _target.Parent == null )
        return;

      if ( transform )
      {
        WorldMatrix = _target.Parent.Transform.WorldMatrix * _matrix;

        _right = _worldMatrix.GetColumn( 0 );
        _right.Normalize();

        _target.SetDirty();
      }

      if ( color )
      {
        if (_target.Parent.Transform.HasFinalColorTransform)
        {
          _concatenatedColorTransform.AddColor = _target.Parent.Transform.ConcatenatedColorTransform.AddColor + _colorTransform.AddColor;
          _concatenatedColorTransform.MultColor = _target.Parent.Transform.ConcatenatedColorTransform.MultColor * _colorTransform.MultColor;
          HasFinalColorTransform = true;
        }
        else
        {
          _concatenatedColorTransform.AddColor = _colorTransform.AddColor;
          _concatenatedColorTransform.MultColor = _colorTransform.MultColor;
          HasFinalColorTransform = HasCxForm;
        }



        _concatenatedAlpha = _target.Parent.Transform.ConcatenatedAlpha * _alpha;


        if (_target.IgnoreParentFiltersSwitching || !_target.Parent.Transform.HasFinalColorMatrix)
        {
          _concatenatedColorMatrix_mul = _colorMatrix_mul;
          _concatenatedColorMatrix_add = _colorMatrix_add;
          HasFinalColorMatrix = HasColorMatrix;
        }
        else
        {
          _concatenatedColorMatrix_mul = _target.Parent.Transform._concatenatedColorMatrix_mul * _colorMatrix_mul;
          _concatenatedColorMatrix_add = _target.Parent.Transform._concatenatedColorMatrix_add.Mul(_colorMatrix_add);
          HasFinalColorMatrix = true;
        }
      }
    }

    public void ConcatenateRecursively( bool transform, bool color )
    {
      Concatenate( transform, color );

      if ( _target is DisplayObjectContainer )
      {
        DisplayObjectContainer container = _target as DisplayObjectContainer;

        if ( container.Children != null )
        {
          for ( int i = 0; i < container.Children.Count; i++ )
          {
            if ( container.Children[i].DisplayObject.Visible )
              container.Children[i].DisplayObject.Transform.ConcatenateRecursively( transform, color );
          }
        }
      }
    }

    public object Clone()
    {
      return MemberwiseClone();
    }

    public void UpdateMatrix()
    {
      if ( _autoUpdateMatrix )
      {
        _matrix = Matrix4x4.TRS( _position, Quaternion.Euler( _rotation ), _scale );
        ConcatenateRecursively( true, true );
      }
    }
    
    private void DecomposeMatrix()
    {
      AutoUpdateMatrix = false;
      DecomposedMatrix decomposedMatrix = new DecomposedMatrix();
      MathUtils.DecomposeMatrix( _matrix, ref decomposedMatrix );
      Position = decomposedMatrix.position;
      Rotation = decomposedMatrix.rotation;
      Scale = decomposedMatrix.scale;
      AutoUpdateMatrix = true;
    }
  }
}
