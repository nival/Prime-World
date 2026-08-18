using System.Collections.Generic;
using System.Runtime.Serialization;
using System.IO;
using Flash.Render;
using Flash.Utils;
using SwfDotNet.IO.Tags;
using SwfDotNet.IO.Tags.Types;
using UnityEngine;
using Color = UnityEngine.Color;
using MathUtils = Flash.Utils.MathUtils;
using Rect = UnityEngine.Rect;

namespace Flash
{
  [System.Serializable]
  public abstract class UniBaseShapeTag : UniBaseTag, ISerializable
  {
    // Renderable
    protected List<RenderableElement> _shapes = new List<RenderableElement>();
    public List<RenderableElement> Shapes
    {
      get { return _shapes; }
    }
    protected Vector3 _drawingPosition;

    public override void GetObjectData( SerializationInfo info, StreamingContext context )
    {
      base.GetObjectData( info, context );

      Flash.SerializeHelpers.Pack( info, "_shapes", _shapes );
    }

    protected UniBaseShapeTag( SerializationInfo info, StreamingContext context )
      : base( info, context )
    {
      Flash.SerializeHelpers.Unpack( info, "_shapes", out _shapes );
    }

    // Use static counters to give pseudo names to all created meshes
    private static int lineMeshCount = 0;
    private static int fillMeshCount = 0;
    protected static void CreateMeshes( UniSwf swf, ShapeElement element, string name )
    {
      ShapeElement.ShapePoints points = element.Points;

      bool transparent = false;
      bool transparentLine = false;

      // Calculate triangles
      if ( element.ContainsFillStyle )
      {
        element.FillMaterial = new FlashShapeMaterial();

        List<Vector3> vertexes = new List<Vector3>();
        List<Color> colors = new List<Color>();
        List<Vector2> texcoord = new List<Vector2>(); // empty
        List<Vector3> normals = new List<Vector3>(); // empty

        #region FILL

        // Tessellate with cutouts first, if this gives 0 vertices 
        // re-tessellate without any cutouts
        var paths = new List<Vector3>( points );
        var vertices = new List<Vector3>();
        var indices = new List<int>();
        if ( !Mesh2DGen.Tessellate( true, paths, vertices, indices ) )
        {
          if ( !Mesh2DGen.Tessellate( false, paths, vertices, indices ) )
          {
            return;
          }
        }

        vertexes.AddRange( vertices );

        for ( int i = 0; i < vertexes.Count; ++i )
          colors.Add( element.UniFillStyle.FillColor );

        for ( int i = 0; i < vertexes.Count; ++i )
          texcoord.Add( new Vector2( 0.0001F, 0.0001F ) );

        for ( int i = 0; i < vertexes.Count; ++i )
          normals.Add( Vector3.zero );
        #endregion

        Matrix4x4 bitmapMatrix = Matrix4x4.identity;
        Matrix4x4 textureSpaceMatrix = Matrix4x4.identity;

        element.FillMaterial.RenderMaterial.SetTexture( "_FillTex", swf.AtlasData.Atlas );
        element.FillMaterial.Pin_FillType = FillTypePin.Bitmap;

        if ( element.UniFillStyle.Type == UniFillStyleType.UniRepeatingBitmapFill )
        {
          element.FillMaterial.RenderMaterial.SetFloat( "_wrapType", 1 );
        }
        else if (( element.UniFillStyle.Type == UniFillStyleType.UniLinearGradientFill ||
          element.UniFillStyle.Type == UniFillStyleType.UniRadialGradientFill ||
          element.UniFillStyle.Type == UniFillStyleType.UniFocalRadialGradientFill ) &&
          element.UniFillStyle.SpreadMode == GradientSpreadMode.RepeatMode )
        {
          element.FillMaterial.RenderMaterial.SetFloat( "_wrapType", 1 );
        }

        if ( element.UniFillStyle.Type != UniFillStyleType.UniSolidFill )
        {
          DecomposedMatrix decomposed = new DecomposedMatrix();
          bitmapMatrix = GenerateBitmapMatrix( element.UniFillStyle.BitmapTransform, ref decomposed );
          int id = -1;
          textureSpaceMatrix = GenerateTextureSpaceMatrix( swf, element.UniFillStyle, ref id );

          Rect rect = swf.AtlasData.Rects[id];
          Matrix4x4 atlasMatrix = Matrix4x4.identity;
          if ( element.UniFillStyle.Type != UniFillStyleType.UniRadialGradientFill
          && element.UniFillStyle.Type != UniFillStyleType.UniFocalRadialGradientFill )
          {
            atlasMatrix = GenerateAtlasMatrix( rect );
          }

          element.UniFillStyle.BitmapTransform = textureSpaceMatrix * bitmapMatrix;
          if ( element.UniFillStyle.Type != UniFillStyleType.UniRadialGradientFill
          && element.UniFillStyle.Type != UniFillStyleType.UniFocalRadialGradientFill
          && element.UniFillStyle.Type != UniFillStyleType.UniLinearGradientFill )
          {
            Matrix4x4 m = element.UniFillStyle.BitmapTransform;
            m[1, 3] += 1;
            element.UniFillStyle.BitmapTransform = m;
          }
          element.UniFillStyle.BitmapTransform = atlasMatrix * element.UniFillStyle.BitmapTransform;
          element.FillMaterial.RenderMaterial.SetVector( "_atlasOffset", new Vector4( rect.x, rect.y, rect.width, rect.height ) );
          element.FillMaterial.RenderMaterial.SetMatrix( "_BitmapMatrix", element.UniFillStyle.BitmapTransform );
          //This registration required by updating textures process after device lost/obtain case. PF-52674
          element.RegisterTextureMatrixKeeper();
          element.UniFillStyle.TextureTransform = new TextureTransform( decomposed, atlasMatrix * textureSpaceMatrix );
        }

        if ( element.UniFillStyle.Type == UniFillStyleType.UniRadialGradientFill || element.UniFillStyle.Type == UniFillStyleType.UniFocalRadialGradientFill )
        {
          element.FillMaterial.Pin_FillType = FillTypePin.RadialGradient;
          element.FillMaterial.RenderMaterial.SetFloat( "_focalPoint", element.UniFillStyle.FocalPoint );
        }

        if (element.UniFillStyle.Type == UniFillStyleType.UniSolidFill)
        {
          element.FillMaterial.Pin_FillType = FillTypePin.Solid;
          transparent = (bool)(element.UniFillStyle.FillColor.a < (1.0F / 255.0F));
        }

        ++fillMeshCount;
        Mesh mesh = new Mesh();
        mesh.name = name + "_fill_mesh_" + fillMeshCount;
        mesh.vertices = vertexes.ToArray();
        mesh.colors = colors.ToArray();
        mesh.uv = texcoord.ToArray();
        mesh.normals = normals.ToArray();
        mesh.triangles = indices.ToArray();
        
        element.FillMesh = mesh;
      }

      if ( element.ContainsLineStyle )
      {
        element.LineMaterial = new FlashShapeMaterial();       

        #region LINE

        var contour = new List<Vector3>( points );
        var lpoints = new List<Vector3>();
        var lnormals = new List<Vector2>();
        var lmarkers = new List<Vector2>();
        var lcolors = new List<Color>();
        var lindices = new List<int>();
        
        Mesh2DGen.TessellateLine( element.UniLineStyle.Width, element.IsClosed, 0.5f, contour, element.UniLineStyle.LineColor, element.UniLineStyle.LineColor, lpoints, lnormals, lmarkers, lcolors, lindices );

        #endregion

        element.LineMaterial.Pin_FillType = FillTypePin.Bitmap;

        if ( element.UniLineStyle.UniFillStyle != null )
        {
          if ( element.UniLineStyle.UniFillStyle.Type == UniFillStyleType.UniRepeatingBitmapFill )
          {
            element.LineMaterial.RenderMaterial.SetFloat( "_wrapType", 1 );
          }
          else if ( element.UniLineStyle.UniFillStyle.Type == UniFillStyleType.UniLinearGradientFill ||
            element.UniLineStyle.UniFillStyle.Type == UniFillStyleType.UniRadialGradientFill ||
            element.UniLineStyle.UniFillStyle.Type == UniFillStyleType.UniFocalRadialGradientFill &&
            element.UniLineStyle.UniFillStyle.SpreadMode == GradientSpreadMode.RepeatMode )
          {
            element.LineMaterial.RenderMaterial.SetFloat("_wrapType", 1);
          }

          Matrix4x4 bitmapMatrix = Matrix4x4.identity;
          Matrix4x4 textureSpaceMatrix = Matrix4x4.identity;
          if ( element.UniLineStyle.UniFillStyle.Type != UniFillStyleType.UniSolidFill )
          {
            DecomposedMatrix decomposed = new DecomposedMatrix();
            bitmapMatrix = GenerateBitmapMatrix( element.UniLineStyle.UniFillStyle.BitmapTransform, ref decomposed );
            int id = -1;
            textureSpaceMatrix = GenerateTextureSpaceMatrix( swf, element.UniLineStyle.UniFillStyle, ref id );

            Rect rect = swf.AtlasData.Rects[id];
            Matrix4x4 atlasMatrix = Matrix4x4.identity;
            if ( element.UniLineStyle.UniFillStyle.Type != UniFillStyleType.UniRadialGradientFill
            && element.UniLineStyle.UniFillStyle.Type != UniFillStyleType.UniFocalRadialGradientFill )
            {
              atlasMatrix = GenerateAtlasMatrix( rect );
            }

            element.UniLineStyle.UniFillStyle.BitmapTransform = textureSpaceMatrix * bitmapMatrix;
            if ( element.UniLineStyle.UniFillStyle.Type != UniFillStyleType.UniRadialGradientFill
            && element.UniLineStyle.UniFillStyle.Type != UniFillStyleType.UniFocalRadialGradientFill
            && element.UniLineStyle.UniFillStyle.Type != UniFillStyleType.UniLinearGradientFill )
            {
              Matrix4x4 m = element.UniLineStyle.UniFillStyle.BitmapTransform;
              m[1, 3] += 1;
              element.UniLineStyle.UniFillStyle.BitmapTransform = m;
            }
            element.UniLineStyle.UniFillStyle.BitmapTransform = atlasMatrix * element.UniLineStyle.UniFillStyle.BitmapTransform;
            element.LineMaterial.RenderMaterial.SetVector("_atlasOffset", new Vector4(rect.x, rect.y, rect.width, rect.height));

            element.LineMaterial.RenderMaterial.SetMatrix("_BitmapMatrix", element.UniLineStyle.UniFillStyle.BitmapTransform);
            element.UniLineStyle.UniFillStyle.TextureTransform = new TextureTransform( decomposed, atlasMatrix * textureSpaceMatrix );
          }

          if ( element.UniLineStyle.UniFillStyle.Type == UniFillStyleType.UniRadialGradientFill || element.UniLineStyle.UniFillStyle.Type == UniFillStyleType.UniFocalRadialGradientFill )
          {
            element.LineMaterial.Pin_FillType = FillTypePin.RadialGradient;
            element.LineMaterial.RenderMaterial.SetFloat("_focalPoint", element.UniLineStyle.UniFillStyle.FocalPoint);
          }

          if (element.UniLineStyle.UniFillStyle.Type == UniFillStyleType.UniSolidFill)
          {
            transparentLine = (bool)(element.UniFillStyle.FillColor.a < (1.0F / 255.0F));
          }
        }
        else
        {
          element.LineMaterial.Pin_FillType = FillTypePin.Solid;
        }

        ++lineMeshCount;
        Mesh mesh = new Mesh();
        mesh.name = name + "_line_mesh_" + lineMeshCount;
        mesh.vertices = lpoints.ToArray();
        mesh.uv = lnormals.ToArray();
        mesh.uv2 = lmarkers.ToArray();
        mesh.colors = lcolors.ToArray();
        mesh.triangles = lindices.ToArray();

        element.LineMesh = mesh;
      }


      element.Transparent = transparent;
      element.TransparentLine = transparentLine;

      //AssetDatabase.CreateAsset( mesh, "Assets/Meshes/" + Guid.NewGuid() + ".asset" );
      //AssetDatabase.SaveAssets();
    }

    private static Matrix4x4 GenerateTextureSpaceMatrix( UniSwf swf, UniFillStyle fillStyle, ref int id )
    {
      Matrix4x4 textureSpaceMatrix = Matrix4x4.identity;
      if ( fillStyle.Type == UniFillStyleType.UniBitmapFill || fillStyle.Type == UniFillStyleType.UniRepeatingBitmapFill )
      {
        id = ( (UniDefineBitsJpegTag)swf.UniDictionary[fillStyle.BitmapId] ).TextureIdResources;
        Vector2 texSize = swf.AtlasData.Sizes[id];
        textureSpaceMatrix = Matrix4x4.Scale( new Vector3( 1.0F / texSize.x, 1.0F / texSize.y, 1 ) );
      }
      else if ( fillStyle.Type == UniFillStyleType.UniLinearGradientFill
        || fillStyle.Type == UniFillStyleType.UniRadialGradientFill
        || fillStyle.Type == UniFillStyleType.UniFocalRadialGradientFill )
      {
        id = fillStyle.GradientID;
        textureSpaceMatrix = Matrix4x4.Scale( new Vector3( 1.0F / FlashEnv.FLASH_GRADIENT_RES_IN_PIX, 1.0F / FlashEnv.FLASH_GRADIENT_RES_IN_PIX, 1 ) );
        Matrix4x4 pixTranslate = Matrix4x4.identity;
        pixTranslate[0, 3] = FlashEnv.FLASH_GRADIENT_RES_IN_PIX / 2;
        pixTranslate[1, 3] = FlashEnv.FLASH_GRADIENT_RES_IN_PIX / 2;
        textureSpaceMatrix = textureSpaceMatrix * pixTranslate;

        if ( fillStyle.Type == UniFillStyleType.UniLinearGradientFill )
          textureSpaceMatrix[1, 1] = 0;
      }

      return textureSpaceMatrix;
    }
    private static Matrix4x4 GenerateBitmapMatrix( Matrix4x4 bitmapTransform, ref DecomposedMatrix decomposed )
    {
      Matrix4x4 bitmapMatrix = bitmapTransform;
      MathUtils.DecomposeMatrix( bitmapMatrix, ref decomposed );

      // modify
      decomposed.position = -decomposed.position;
      decomposed.rotation.z = -decomposed.rotation.z;
      decomposed.scale.y = -decomposed.scale.y;
      Matrix4x4 translate = Matrix4x4.TRS( decomposed.position, Quaternion.identity, Vector3.one );
      Matrix4x4 rotate = Matrix4x4.TRS( Vector3.zero, Quaternion.Euler( decomposed.rotation ), Vector3.one );
      Vector3 sc = new Vector3( 1.0F / decomposed.scale.x, 1.0F / decomposed.scale.y, 1.0F / decomposed.scale.z );
      Matrix4x4 scale = Matrix4x4.TRS( Vector3.zero, Quaternion.identity, sc );
      Matrix4x4 shear = Matrix4x4.identity;
      shear[0, 1] = decomposed.shearXY;
      bitmapMatrix = scale * shear * rotate * translate;

      return bitmapMatrix;
    }
    private static Matrix4x4 GenerateAtlasMatrix( Rect rect )
    {
      Matrix4x4 result = Matrix4x4.identity;
      result[0, 0] = rect.width;
      result[1, 1] = rect.height;
      result[0, 3] = rect.x;
      result[1, 3] = rect.y;
      return result;
    }

    public UniBaseShapeTag( BaseTag baseTag, UniSwf owner ) : base( owner ) { }
    public virtual void BuildMeshes() { }
  }
}
