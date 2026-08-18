using System;
using System.Collections.Generic;
using Flash.Render;
using Flash.Utils;
using Flash.Utils.Atlasses;
using UnityEngine;

namespace Flash
{
  public class Loader : MovieClip
  {
    public Mesh _fillMesh;
    public Shape _imageShape;
    private Texture texture;
    public Material _material;
    public Material p_material { get { return _material; } set { _material = value; } }
    public Matrix4x4 _textureMatrix;
    public Texture Texture
    {
      get { return texture; }
        set 
        { 
            texture = value;

            _material.SetFloat("_Web", 1.0f);
            _material.SetTexture("_FillTex", texture); 
        }
    }

    public Loader()
    {
      // Create text mesh
      _fillMesh = new Mesh();
      // TODO оптимизировать под один статичный меш для Loader
      Vector3[] vertexes = new Vector3[4];
      int[] triangles = new int[6];

      vertexes[0] = new Vector3( 0, 0, 0 );
      vertexes[1] = new Vector3( 0, 1, 0 );
      vertexes[2] = new Vector3( 1, 1, 0 );
      vertexes[3] = new Vector3( 1, 0, 0 );

      Bounds bounds = new Bounds();
      bounds.LeftTop = Vector3.zero;
      bounds.RightBottom = new Vector3( 1, 1, 0 );

      triangles[0] = 0;
      triangles[1] = 2;
      triangles[2] = 1;

      triangles[3] = 0;
      triangles[4] = 3;
      triangles[5] = 2;

      _fillMesh.vertices = vertexes;
      Vector2[] texcoord = new Vector2[_fillMesh.vertexCount]; // empty
      for ( int i = 0; i < texcoord.Length; ++i )
        texcoord[i] = new Vector2( 0.0001F, 0.0001F );
      _fillMesh.uv = texcoord;
      _fillMesh.triangles = triangles;

      // Material
      FlashMaterial material = new FlashShapeMaterial();
      material.Pin_FillType = FillTypePin.Bitmap;
      _material = material.RenderMaterial;
      _imageShape = new Shape();

      ShapeElement element = new ShapeElement();
      UniFillStyle fillStyle = new UniFillStyle();

      element.FillMesh = _fillMesh;
      element.FillMaterial = material;
      element.UniFillStyle = fillStyle;
      _textureMatrix = Matrix4x4.Scale( new Vector3( 1.0F / bounds.RightBottom.x, -1.0F / bounds.RightBottom.y, 1 ) );
      _textureMatrix.m13 = 1;
      element.UniFillStyle.BitmapTransform = _textureMatrix;
      UpdateTextureMatrix();

      UniFlashPlayer.MaterialsReseted += UpdateTextureMatrix;
      material.Pin_EnableWrap = BooleanPin.None;

      _imageShape.Shapes = new List<RenderableElement>( 1 );
      _imageShape.Shapes.Add( element );
      _imageShape.LocalBounds = bounds;

      // add frame
      Frame singleFrame = new Frame();
      TimeLine.Add( singleFrame );
      Children = TimeLine[0];

      AddChild( _imageShape );

      UpdateLocalBounds();
    }
    /// <summary>
    /// Updates texture mattix in <see cref="_material"/> by <see cref="_textureMatrix"/>
    /// Using to avoid graphical artifacts after device lost/obtain cycle. PF-52674
    /// </summary>
    private void UpdateTextureMatrix()
    {
      _material.SetMatrix( "_BitmapMatrix", _textureMatrix );
    }

    public override void Destroy()
    {
      base.Destroy();
      UniFlashPlayer.MaterialsReseted -= UpdateTextureMatrix;
    }
    //TODO: Mock
    public void Load( AtlassedTexture texture, string _name )
    {
      return;
    }

    public void Load( Texture _texture, string _name )
    {
      _material = _imageShape.Shapes[0].FillMaterial.RenderMaterial;

      texture = _texture;

      if ( texture == null )
      {
        _material.SetTexture( "_FillTex", null );
        return;
      }

      int initWidth = texture.width;
      int initHeight = texture.height;
      int newWidth = initWidth;
      int newHeight = initHeight;

      try
      {
        if ( texture is Texture2D && _name != null)
        {
          TextureUtils.ExtendToPowerOfTwo( (Texture2D)texture, _name, ref initWidth, ref initHeight );
          newWidth = texture.width;
          newHeight = texture.height;

          GarbageCollectorTimer.Collect();
        }
        // Р’РµС‚РєР° MovieTexture (pow2) СѓР±СЂР°РЅР°: РІРёРґРµРѕ С‚РµРїРµСЂСЊ РїСЂРёС…РѕРґРёС‚ RenderTexture'РѕРј С‚РѕС‡РЅРѕРіРѕ СЂР°Р·РјРµСЂР° (РјРёРіСЂР°С†РёСЏ 2019).
      }
      catch ( Exception e )
      {
        Debug.LogWarning( e.ToString() );
      }

      Vector3[] vertexes = new Vector3[4];
      vertexes[0] = new Vector3( 0, 0, 0 );
      vertexes[1] = new Vector3( 0, initHeight, 0 );
      vertexes[2] = new Vector3( initWidth, initHeight, 0 );
      vertexes[3] = new Vector3( initWidth, 0, 0 );
      _fillMesh.vertices = vertexes;

      Bounds bounds = new Bounds();
      bounds.LeftTop = Vector3.zero;
      bounds.RightBottom = new Vector3( initWidth, initHeight, 0 );
      _imageShape.LocalBounds = bounds;
      _textureMatrix = Matrix4x4.Scale( new Vector3( 1.0F * initWidth / newWidth / bounds.RightBottom.x, -1.0F * initHeight / newHeight / bounds.RightBottom.y, 1 ) );
      _textureMatrix.m13 = 1.0F;

      ( (ShapeElement)_imageShape.Shapes[0] ).UniFillStyle.BitmapTransform = _textureMatrix;

      UpdateTextureMatrix();

      texture.filterMode = FilterMode.Bilinear;
      _material.SetTexture( "_FillTex", texture );

      UpdateLocalBounds();
      SetDirty();
    }
  }
}
