using System;
using System.IO;
using System.Collections.Generic;
using System.Runtime.Serialization;
using Flash.Utils;
using Flash.Render;
using SwfDotNet.IO.Tags;
using SwfDotNet.IO.Tags.Types;
using UnityEngine;

namespace Flash
{
  [Serializable]
  public class UniDefineMorphShapeTag : UniBaseShapeTag, ISerializable
  {
    public struct MorphLerped
    {
      public Mesh mesh;
      public Color fillColor;
      public float lineWidth;
      public UnityEngine.Rect bounds;
    };
    
    private class Path
    {
      public Path()
      {
        fill0 = fill1 = line = -1;
        x = y = -1;
      }
    
      public int fill0, fill1, line;
      public float x, y;      
    };
 
    private Path _currentPath = null;
    private Dictionary<string, MorphLerped> _morphDict = new Dictionary<string, MorphLerped>();
    private List<ShapeElement> _startShapeCollection = new List<ShapeElement>();
    private List<ShapeElement> _endShapeCollection = new List<ShapeElement>();
    private MorphFillStyle _currentMorphFillStyle;
    private MorphLineStyle _currentMorphLineStyle;
    private MorphFillStyleCollection _currentMorphFillStyleArray;
    private MorphLineStyleCollection _currentMorphLineStyleArray;
    private ShapeRecordCollection _endEdges = new ShapeRecordCollection();
    private Bounds _localBoundsStart;
    public Bounds LocalBoundsStart
    {
      get { return _localBoundsStart; }
    }
    private Bounds _localBoundsEnd;
    public Bounds LocalBoundsEnd
    {
      get { return _localBoundsEnd; }
    }
        
    public UniDefineMorphShapeTag( BaseTag baseTag, UniSwf owner )
      : base( baseTag, owner )
    {
      DefineMorphShapeTag morphShape = baseTag as DefineMorphShapeTag;
      _localBoundsStart.LeftTop = FlashToUnityConverter.ConvertPosition( morphShape.StartBounds.XMin, morphShape.StartBounds.YMin );
      _localBoundsStart.RightBottom = FlashToUnityConverter.ConvertPosition( morphShape.StartBounds.XMax, morphShape.StartBounds.YMax );
      _localBoundsEnd.LeftTop = FlashToUnityConverter.ConvertPosition( morphShape.EndBounds.XMin, morphShape.EndBounds.YMin );
      _localBoundsEnd.RightBottom = FlashToUnityConverter.ConvertPosition( morphShape.EndBounds.XMax, morphShape.EndBounds.YMax );

      ParseContour( morphShape, false );
      ParseContour( morphShape, true );

      BuildStyles();
    }

    public override void GetObjectData( SerializationInfo info, StreamingContext context )
    {
      base.GetObjectData( info, context );

      SerializeHelpers.Pack( info, "_startShapeCollection", _startShapeCollection );
      SerializeHelpers.Pack( info, "_endShapeCollection", _endShapeCollection );
      SerializeHelpers.Pack( info, "_currentMorphFillStyle", _currentMorphFillStyle );
      SerializeHelpers.Pack( info, "_currentMorphLineStyle", _currentMorphLineStyle );
      SerializeHelpers.Pack( info, "_currentMorphFillStyleArray", _currentMorphFillStyleArray );
      SerializeHelpers.Pack( info, "_currentMorphLineStyleArray", _currentMorphLineStyleArray );
      SerializeHelpers.Pack( info, "_endEdges", _endEdges );
      SerializeHelpers.Pack( info, "_localBoundsStart", _localBoundsStart );
      SerializeHelpers.Pack( info, "_localBoundsEnd", _localBoundsEnd );
    }

    protected UniDefineMorphShapeTag( SerializationInfo info, StreamingContext context )
      : base( info, context )
    {
      SerializeHelpers.Unpack( info, "_startShapeCollection", out _startShapeCollection );
      SerializeHelpers.Unpack( info, "_endShapeCollection", out _endShapeCollection );
      SerializeHelpers.Unpack( info, "_currentMorphFillStyle", out _currentMorphFillStyle );
      SerializeHelpers.Unpack( info, "_currentMorphLineStyle", out _currentMorphLineStyle );
      SerializeHelpers.Unpack( info, "_currentMorphFillStyleArray", out _currentMorphFillStyleArray );
      SerializeHelpers.Unpack( info, "_currentMorphLineStyleArray", out _currentMorphLineStyleArray );
      SerializeHelpers.Unpack( info, "_endEdges", out _endEdges );
      SerializeHelpers.Unpack( info, "_localBoundsStart", out _localBoundsStart );
      SerializeHelpers.Unpack( info, "_localBoundsEnd", out _localBoundsEnd );
    }

    public override void BuildMeshes()
    {
      if(_startShapeCollection.Count == 0 || _endShapeCollection.Count == 0)
      {
        return;
      }

      // Build start/end meshes and assign them to new start/end collection
      var startCollection = new List<ShapeElement>();
      ProcessShapes(_startShapeCollection, startCollection);
      
      var endCollection = new List<ShapeElement>();
      ProcessShapes(_endShapeCollection, endCollection);
      
      // Release old shapes
      for(int i=0; i<_startShapeCollection.Count; ++i)
      {
        _startShapeCollection[i].Release();
        _endShapeCollection[i].Release();
      }
      
      // Assign enw collections
      _startShapeCollection = startCollection;
      _endShapeCollection = endCollection;

      CreateMorphShapeCollection();
    }
    
    public void ProcessShapes(List<ShapeElement> oldColl, List<ShapeElement> newColl)
    {
      for ( int i = 0; i < oldColl.Count; ++i )
      {
        var shape = oldColl[i];
        if(shape.StyleChangeRecord.FillStyle0 < 1 && shape.StyleChangeRecord.FillStyle1 < 1)
        {
          continue;
        }
        
        // Clone mesh, remove line material for CreateMeshes()
        var fillShape = shape.Clone() as ShapeElement;
        fillShape.UniLineStyle = null;
        
        // Check for shapes enclosed by this shape (cutout)
        for(int j = i+1; j < oldColl.Count; ++j)
        {
          var nextShape = oldColl[j];
          if(fillShape.Contains(nextShape) && nextShape.StyleChangeRecord.FillStyle0 > 0 && nextShape.StyleChangeRecord.FillStyle1 < 1)
          {
            // Add next shape to current shape
            if ( nextShape.Points.Count > 1 )
            {
              fillShape.Points.Add( new Vector3( float.NaN, float.NaN, float.NaN ) ); // Separator
              fillShape.Points.AddRange(nextShape.Points);
            }
            ++i;
          }
          else break;
        }
        
        CreateMeshes( _swf, fillShape, _swf.Name );
        newColl.Add(fillShape);
      }
      
      for ( int i = 0; i < oldColl.Count; ++i )
      {
        var shape = oldColl[i];
        if(shape.StyleChangeRecord.LineStyle > 0)
        {
          var lineShape = shape.Clone() as ShapeElement;
          lineShape.UniFillStyle = null;
          
          CreateMeshes( _swf, lineShape, _swf.Name );
          newColl.Add(lineShape);
        }
      }
    }
    
    public override void Release()
    {
      _startShapeCollection = null;
      _endShapeCollection = null;
      _currentMorphFillStyle = null;
      _currentMorphLineStyle = null;
      _currentMorphFillStyleArray = null;
      _currentMorphLineStyleArray = null;
      _endEdges = null;
    }

    private void ParseContour( DefineMorphShapeTag tag, bool endContour )
    {
      _currentMorphFillStyleArray = tag.MorphFillStyles;
      _currentMorphLineStyleArray = tag.MorphLineStyles;

      int j = 0;
      List<ShapeElement> shapeCollection = endContour ? _endShapeCollection : _startShapeCollection;

      for ( int i=0; i < tag.StartEdges.Count; ++i )
      {
        ShapeRecord rec = tag.StartEdges[i];

        if ( rec is StyleChangeRecord )
        {
          StyleChangeRecord changeRec = rec as StyleChangeRecord;
          if ( changeRec.HasMoveTo() )
          {
            _drawingPosition = FlashToUnityConverter.ConvertPosition( changeRec.MoveDeltaX, changeRec.MoveDeltaY );
          }

          if ( endContour && tag.EndEdges.Count > j && tag.EndEdges[j] is StyleChangeRecord )
          {
            // According to specs no style record is defined in end edges
            // unless it's a move-to record
            var endrec = tag.EndEdges[j++] as StyleChangeRecord;
            if ( endrec.HasMoveTo() )
            {
              _drawingPosition = FlashToUnityConverter.ConvertPosition( endrec.MoveDeltaX, endrec.MoveDeltaY );
            }
          }

          var shape = new ShapeElement();
          shapeCollection.Add(shape);
          shape.StyleChangeRecord = changeRec;
          shape.LocalBounds = endContour ? tag.EndBounds : tag.StartBounds;
          shape.Points.Add( _drawingPosition );
        }
        else if ( rec is StraightEdgeRecord || rec is CurvedEdgeRecord )
        {
          if ( endContour )
          {
            rec = tag.EndEdges[j++];
          }

          if ( rec is StraightEdgeRecord )
          {
            var record = rec as StraightEdgeRecord;
            var curveRecord = new CurvedEdgeRecord(record.DeltaX/2, record.DeltaY/2, record.DeltaX/2, record.DeltaY/2);
            var controlPoint = FlashToUnityConverter.ConvertPosition(curveRecord.ControlDeltaX, curveRecord.ControlDeltaY) + _drawingPosition;
            var anchorPoint = FlashToUnityConverter.ConvertPosition(curveRecord.AnchorDeltaX, curveRecord.AnchorDeltaY) + controlPoint;
            var bezier = new QuadraticBezier(_drawingPosition, controlPoint, anchorPoint);

            var shape = shapeCollection[shapeCollection.Count - 1];
            shape.Points.AddRange(bezier.GetTesselatedPoints(FlashEnv.SEGMENTS_PER_CURVE));
            _drawingPosition = anchorPoint;
          }
          else
          {
            var record = rec as CurvedEdgeRecord;
            var controlPoint = FlashToUnityConverter.ConvertPosition( record.ControlDeltaX, record.ControlDeltaY ) + _drawingPosition;
            var anchorPoint = FlashToUnityConverter.ConvertPosition( record.AnchorDeltaX, record.AnchorDeltaY ) + controlPoint;
            var bezier = new QuadraticBezier( _drawingPosition, controlPoint, anchorPoint );

            var shape = shapeCollection[shapeCollection.Count - 1];
            shape.Points.AddRange( bezier.GetTesselatedPoints( FlashEnv.SEGMENTS_PER_CURVE ) );
            _drawingPosition = anchorPoint;
          }
        }
      }

      ResetStyles();
    }

    private void BuildStyles()
    {
      for ( int i = 0; i < _startShapeCollection.Count; ++i )
      {
        CreateStyles( _startShapeCollection[i], false );
        ResetStyles();
        CreateStyles( _endShapeCollection[i], true );
        ResetStyles();
      }
      
      _currentPath = null;
    }
    
    private void CreateStyles( ShapeElement element, bool end )
    {
      if(_currentPath == null)
      {
        _currentPath = new Path();
      }
      
      if(element.StyleChangeRecord.HasMoveTo())
      {
        _currentPath.x = element.StyleChangeRecord.MoveDeltaX;
        _currentPath.y = element.StyleChangeRecord.MoveDeltaY;
      }
      
      if(element.StyleChangeRecord.HasFillStyle0())
      {
        _currentPath.fill0 = element.StyleChangeRecord.FillStyle0;
      }
      
      if(element.StyleChangeRecord.HasFillStyle1())
      {
        _currentPath.fill1 = element.StyleChangeRecord.FillStyle1;
      }
      
      if(element.StyleChangeRecord.HasLineStyle())
      {
        _currentPath.line = element.StyleChangeRecord.LineStyle;
      }
      
      if(element.StyleChangeRecord.HasNewStyle())
      {
        _currentPath.fill0 = -1;
        _currentPath.fill1 = -1;
        _currentPath.line = -1;
      }
      
      // Set fill style
      if ( _currentPath.fill0 > 0 )
        _currentMorphFillStyle = _currentMorphFillStyleArray[_currentPath.fill0 - 1];
      else
      {
        if (_currentPath.fill1 > 0 )
          _currentMorphFillStyle = _currentMorphFillStyleArray[_currentPath.fill1 - 1];
        else
          _currentMorphFillStyle = null;
      }
       
      if ( _currentMorphFillStyle != null)
      {
        element.UniFillStyle = new UniFillStyle( _currentMorphFillStyle, Swf, end );
      }

      // Set line style
      if ( _currentPath.line > 0 )
        _currentMorphLineStyle = _currentMorphLineStyleArray[_currentPath.line - 1];
      else
        _currentMorphLineStyle = null;

      if ( _currentMorphLineStyle != null )
      {
        element.UniLineStyle = new UniLineStyle( _currentMorphLineStyle, Swf, end );
      }
      
      // Adjust style record
      element.StyleChangeRecord.FillStyle0 = _currentPath.fill0;
      element.StyleChangeRecord.FillStyle1 = _currentPath.fill1;
      element.StyleChangeRecord.LineStyle = _currentPath.line;
    }

    private void CopyMeshAndMaterial(ref Mesh _meshDest, ref FlashMaterial _matDest, Mesh _meshSrc, Mesh _meshSrcEnd, FlashMaterial _matSrc, FlashMaterial _matSrcEnd)
    {
      if (_meshSrc == null || _meshSrcEnd == null || _matSrc == null || _matSrcEnd == null)
        return;

      _matDest = new FlashMorphMaterial();

      _matDest.Pin_FillType = _matSrc.Pin_FillType;

      _matDest.RenderMaterial.SetTexture("_FillTex", _swf.AtlasData.Atlas);
      _matDest.RenderMaterial.SetVector("_atlasOffset", _matSrc.RenderMaterial.GetVector("_atlasOffset"));
      _matDest.RenderMaterial.SetVector("_atlasOffsetEnd", _matSrcEnd.RenderMaterial.GetVector("_atlasOffset"));

      _meshDest = _meshSrc;

      // vertexes
      Vector3[] vertexes2 = _meshSrcEnd.vertices;
      Vector3[] vertToNormal = new Vector3[_meshDest.vertexCount];
      for (int j = 0; j < vertToNormal.Length && j < vertexes2.Length; ++j)
      {
        vertToNormal[j] = vertexes2[j];
      }
      _meshDest.normals = vertToNormal;

      // uv
      Vector2[] uv2 = _meshSrcEnd.uv;
      Vector2[] uvToNormals = new Vector2[_meshDest.vertexCount];
      for (int j = 0; j < uvToNormals.Length && j < uv2.Length; ++j)
        uvToNormals[j] = uv2[j];
      _meshDest.uv2 = uvToNormals;

      // colors
      Color[] colors = _meshSrcEnd.colors;
      Vector4[] colorToTangents = new Vector4[_meshDest.vertexCount];
      for (int j = 0; j < colorToTangents.Length && j < colors.Length; ++j)
        colorToTangents[j] = colors[j];
      _meshDest.tangents = colorToTangents;

      _meshDest.triangles = _meshSrc.triangles;
    }

    private void CreateMorphShapeCollection()
    {
      for ( int i = 0; i < _startShapeCollection.Count; ++i )
      {
        var startShape = _startShapeCollection[i];
        var endShape = _endShapeCollection[i];
        if ( startShape != null && startShape.Points == null || startShape.Points.Count == 0 )
        {
          continue;
        }
        
        var morphElement = new MorphElement();
        morphElement.StartContours = new List<Vector3>( startShape.Points );
        morphElement.EndContours = new List<Vector3>( endShape.Points );
        morphElement.StartBounds = new UnityEngine.Rect(startShape.LocalBounds.XMin, startShape.LocalBounds.YMin, startShape.LocalBounds.XMax, startShape.LocalBounds.YMax);
        morphElement.EndBounds = new UnityEngine.Rect(endShape.LocalBounds.XMin, endShape.LocalBounds.YMin, endShape.LocalBounds.XMax, endShape.LocalBounds.YMax);
        morphElement.IsClosed = startShape.IsClosed;

        if(_startShapeCollection[i].ContainsFillStyle && _endShapeCollection[i].ContainsFillStyle)
        {
          morphElement.StartFillColor = _startShapeCollection[i].UniFillStyle.FillColor;
          morphElement.EndFillColor = _endShapeCollection[i].UniFillStyle.FillColor;
          morphElement.StartFillBitmapTransform = _startShapeCollection[i].UniFillStyle.BitmapTransform;
          morphElement.EndFillBitmapTransform = _endShapeCollection[i].UniFillStyle.BitmapTransform;
          morphElement.StartFillTextureTransform = _startShapeCollection[i].UniFillStyle.TextureTransform;
          morphElement.EndFillTextureTransform = _endShapeCollection[i].UniFillStyle.TextureTransform;
          morphElement.StartFillFocalPoint = _startShapeCollection[i].UniFillStyle.FocalPoint;
          morphElement.EndFillFocalPoint = _endShapeCollection[i].UniFillStyle.FocalPoint;
        }
        
        if(_startShapeCollection[i].ContainsLineStyle && _endShapeCollection[i].ContainsLineStyle)
        {
          morphElement.StartLineColor = _startShapeCollection[i].UniLineStyle.LineColor;
          morphElement.EndLineColor = _endShapeCollection[i].UniLineStyle.LineColor;
          morphElement.StartLineWidth = _startShapeCollection[i].UniLineStyle.Width;
          morphElement.EndLineWidth = _endShapeCollection[i].UniLineStyle.Width;
  
          if ( _startShapeCollection[i].UniLineStyle.UniFillStyle != null )
          {
            morphElement.StartFillBitmapTransform = _startShapeCollection[i].UniLineStyle.UniFillStyle.BitmapTransform;
            morphElement.EndFillBitmapTransform = _endShapeCollection[i].UniLineStyle.UniFillStyle.BitmapTransform;
            morphElement.StartFillTextureTransform = _startShapeCollection[i].UniLineStyle.UniFillStyle.TextureTransform;
            morphElement.EndFillTextureTransform = _endShapeCollection[i].UniLineStyle.UniFillStyle.TextureTransform;
  
            morphElement.StartFillFocalPoint = _startShapeCollection[i].UniLineStyle.UniFillStyle.FocalPoint;
            morphElement.EndFillFocalPoint = _endShapeCollection[i].UniLineStyle.UniFillStyle.FocalPoint;
          }
        }

        Mesh newMesh = morphElement.FillMesh;
        FlashMaterial newMaterial = morphElement.FillMaterial;
        CopyMeshAndMaterial(ref newMesh, ref newMaterial,
            _startShapeCollection[i].FillMesh, _endShapeCollection[i].FillMesh,
            _startShapeCollection[i].FillMaterial, _endShapeCollection[i].FillMaterial);
        morphElement.FillMesh = newMesh;
        morphElement.FillMaterial = newMaterial;

        newMesh = morphElement.LineMesh;
        newMaterial = morphElement.LineMaterial;
        CopyMeshAndMaterial(ref newMesh, ref newMaterial,
            _startShapeCollection[i].LineMesh, _endShapeCollection[i].LineMesh,
            _startShapeCollection[i].LineMaterial, _endShapeCollection[i].LineMaterial);
        morphElement.LineMesh = newMesh;
        morphElement.LineMaterial = newMaterial;

        // Assign line fill type to all morph lines (those must be extruded in MorphShader)
        if (morphElement.LineMaterial != null && morphElement.LineMaterial.Pin_FillType == FillTypePin.Solid )
        {
          morphElement.LineMaterial.Pin_FillType = FillTypePin.Line;
        }
        _shapes.Add( morphElement );
      }
    }

    public bool LerpMesh( MorphElement morphElem, float t, ref MorphLerped morphOut )
    {
      var cachedName = morphElem.FillMesh.name + "_at_" + t.ToString("0.00");
      MorphLerped cachedMorph;
      if ( _morphDict.TryGetValue( cachedName, out cachedMorph ) )
      {
        morphOut = cachedMorph;
        return true;
      }

      if ( this._shapes.Count == 0 )
      {
        return false;
      }

      var lerpedContours = new List<Vector3>();
      if ( morphElem.StartContours.Count != morphElem.EndContours.Count )
      {
        Debug.LogError( "Contour count mismatch" );
      }

      for ( int i=0; i < morphElem.StartContours.Count; ++i )
      {
        var sp = morphElem.StartContours[i];
        var ep = morphElem.EndContours[i];
        var lp = sp + (ep - sp) * t;
        lerpedContours.Add( lp );
      }

      // Tessellate with cutouts first, if this gives 0 vertices 
      // re-tessellate without any cutouts
      var verts = new List<Vector3>();
      var inds = new List<int>();
      if ( !Mesh2DGen.Tessellate( true, lerpedContours, verts, inds ) )
      {
        if ( !Mesh2DGen.Tessellate( false, lerpedContours, verts, inds ) )
        {
          // Return original mesh on failure
          return false;
        }
      }

      Mesh newMesh = new Mesh();
      newMesh.name = cachedName;
      newMesh.vertices = verts.ToArray();
      newMesh.triangles = inds.ToArray();

      // Cache interpolated morph
      var morphLerped = new MorphLerped();
      morphLerped.mesh = newMesh;
      morphLerped.fillColor = morphElem.StartFillColor + ( morphElem.EndFillColor - morphElem.StartFillColor ) * t;
      morphLerped.bounds = LerpBounds(morphElem.StartBounds, morphElem.EndBounds, t);
      _morphDict.Add( cachedName, morphLerped );

      morphOut = morphLerped;
      return true;
    }

    public bool LerpLine( MorphElement morphElem, float t, float lineWidth, ref MorphLerped morphOut )
    {
      var cachedName = morphElem.LineMesh.name + "_at_" + t.ToString("0.00");
      MorphLerped cachedMorph;
      if ( _morphDict.TryGetValue( cachedName, out cachedMorph ) )
      {
        morphOut = cachedMorph;
        return true;
      }

      if ( this._shapes.Count == 0 )
      {
        return false;
      }

      var lerpedContours = new List<Vector3>();
      if ( morphElem.StartContours.Count != morphElem.EndContours.Count )
      {
        Debug.LogError( "Contour count mismatch" );
      }

      for ( int i=0; i < morphElem.StartContours.Count; ++i )
      {
        var sp = morphElem.StartContours[i];
        var ep = morphElem.EndContours[i];
        var lp = sp + ( ep - sp ) * t;
        lerpedContours.Add( lp );
      }

      // Create line mesh from lerped contours
      var points = new List<Vector3>();
      var normals = new List<Vector2>();
      var markers = new List<Vector2>();
      var colors = new List<Color>();
      var indices = new List<int>(); 

      var color1 = morphElem.StartLineColor;
      var color2 = morphElem.EndLineColor;
      var width = morphElem.StartLineWidth + ( morphElem.EndLineWidth - morphElem.StartLineWidth ) * t;

      Mesh2DGen.TessellateLine( width, morphElem.IsClosed, 0.5f, lerpedContours, color1, color2, points, normals, markers, colors, indices );

      Mesh newMesh = new Mesh();
      newMesh.name = cachedName;
      newMesh.vertices = points.ToArray();
      newMesh.uv = normals.ToArray();
      newMesh.uv2 = markers.ToArray();
      newMesh.colors = colors.ToArray();
      newMesh.triangles = indices.ToArray();

      // Cache interpolated morph (colors are part of vertex stream)
      var morphLerped = new MorphLerped();
      morphLerped.mesh = newMesh;
      morphLerped.lineWidth = width;
      morphLerped.bounds = LerpBounds(morphElem.StartBounds, morphElem.EndBounds, t);
      _morphDict.Add( cachedName, morphLerped );

      morphOut = morphLerped;

      return true;
    }
    
    private UnityEngine.Rect LerpBounds(UnityEngine.Rect b1, UnityEngine.Rect b2, float t)
    {
      var xmin = b1.xMin + (b2.xMin - b1.xMin) * t;
      var xmax = b1.xMax + (b2.xMax - b1.xMax) * t;
      var ymin = b1.yMin + (b2.yMin - b1.yMin) * t;
      var ymax = b1.yMax + (b2.yMax - b1.yMax) * t;
      return new UnityEngine.Rect(xmin, ymin, xmax, ymax);
    }

    private void ResetStyles()
    {
      _currentMorphFillStyle = null;
      _currentMorphLineStyle = null;
    }
  }
}

