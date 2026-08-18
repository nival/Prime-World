using System;
using System.Runtime.Serialization;
using System.Collections.Generic;
using System.IO;
using Flash.Utils;
using SwfDotNet.IO.Tags;
using SwfDotNet.IO.Tags.Types;
using UnityEngine;

namespace Flash
{
  [System.Serializable]
  public class UniDefineShapeTag : UniBaseShapeTag, ISerializable
  {
    private FillStyle _currentFillStyle;
    private LineStyle _currentLineStyle;
    private FillStyleCollection _currentFillStyleArray;
    private LineStyleCollection _currentLineStyleArray;

    public UniDefineShapeTag( SerializationInfo info, StreamingContext context )
      : base( info, context )
    {
    }

    public UniDefineShapeTag( BaseTag baseTag, UniSwf owner )
      : base( baseTag, owner )
    {
      DefineShape defineShape = baseTag as DefineShape;
      _localBounds.LeftTop = FlashToUnityConverter.ConvertPosition( defineShape.Rect.XMin, defineShape.Rect.YMin );
      _localBounds.RightBottom = FlashToUnityConverter.ConvertPosition( defineShape.Rect.XMax, defineShape.Rect.YMax );
      if ( defineShape is DefineShape4Tag )
      {
        DefineShape4Tag defShape4 = (DefineShape4Tag)defineShape;
        //Debug.LogWarning("DEFINE SHAPE 4 TAG FOUNDED");
        //Debug.Log("RECT : " + defShape4.Rect.Rectangle);
        //Debug.Log("EDGE RECT : " + defShape4.EdgeRect.Rectangle );
        _localBounds.LeftTop = FlashToUnityConverter.ConvertPosition( defShape4.EdgeRect.XMin, defShape4.EdgeRect.YMin );
        _localBounds.RightBottom = FlashToUnityConverter.ConvertPosition( defShape4.EdgeRect.XMax, defShape4.EdgeRect.YMax );
      }
      ParseContour( (DefineShape)baseTag );
      BuildStyles();
    }

    public override void BuildMeshes()
    {
      if ( Shapes.Count == 0 )
      {
        return;
      }

      var shape = Shapes[0] as ShapeElement;
      for ( int i=1; i < Shapes.Count; ++i )
      {
        var elem = Shapes[i] as ShapeElement;
        if ( !elem.ContainsFillStyle && !elem.ContainsLineStyle )
        {
          if ( elem.Points.Count > 1 )
          {
            shape.Points.Add( new Vector3( float.NaN, float.NaN, float.NaN ) );
            foreach ( var v in elem.Points )
            {
              shape.Points.Add( v );
            }
          }
          elem.Release();
        }
        else
        {
          CreateMeshes( _swf, shape, _swf.Name );
          shape = elem;
        }
      }

      CreateMeshes( _swf, shape, _swf.Name );
    }
    public override void Release()
    {
      _currentFillStyle = null;
      _currentLineStyle = null;
      _currentFillStyleArray = null;
      _currentLineStyleArray = null;
    }

    private void ParseContour( DefineShape baseTag )
    {
      _currentFillStyleArray = baseTag.ShapeWithStyle.FillStyleArray;
      _currentLineStyleArray = baseTag.ShapeWithStyle.LineStyleArray;

      // Parse points
      foreach ( ShapeRecord shapeRecord in baseTag.ShapeWithStyle.Shapes )
      {
        // Style change
        if ( shapeRecord is StyleChangeRecord )
        {

          StyleChangeRecord styleChangeRecord = shapeRecord as StyleChangeRecord;
          ShapeElement element = null;

          if ( _shapes.Count > 0 && IsTheSameContour( styleChangeRecord, (ShapeElement)_shapes[_shapes.Count - 1] ) )
          {
            element = (ShapeElement)_shapes[_shapes.Count - 1];
          }
          else
          {
            element = new ShapeElement();
            _shapes.Add( element );
          }

          // Проверяем есть ли запись о смещении
          if ( styleChangeRecord.MoveDeltaX != int.MinValue && styleChangeRecord.MoveDeltaY != int.MinValue )
            _drawingPosition = FlashToUnityConverter.ConvertPosition( styleChangeRecord.MoveDeltaX, styleChangeRecord.MoveDeltaY );

          element.StyleChangeRecord = styleChangeRecord;
          element.Points.Add( _drawingPosition );
        }
        // Edge
        else if ( shapeRecord is StraightEdgeRecord )
        {
          StraightEdgeRecord record = shapeRecord as StraightEdgeRecord;
          _drawingPosition = FlashToUnityConverter.ConvertPosition( record.DeltaX, record.DeltaY ) + _drawingPosition;
          ( (ShapeElement)_shapes[_shapes.Count - 1] ).Points.Add( _drawingPosition );
        }
        // Curve
        else if ( shapeRecord is CurvedEdgeRecord )
        {
          CurvedEdgeRecord record = shapeRecord as CurvedEdgeRecord;
          Vector3 controlPoint = FlashToUnityConverter.ConvertPosition( record.ControlDeltaX, record.ControlDeltaY ) + _drawingPosition;
          Vector3 anchorPoint = FlashToUnityConverter.ConvertPosition( record.AnchorDeltaX, record.AnchorDeltaY ) + controlPoint;
          QuadraticBezier bezier = new QuadraticBezier( _drawingPosition, controlPoint, anchorPoint );
          ( (ShapeElement)_shapes[_shapes.Count - 1] ).Points.AddRange( bezier.GetTesselatedPoints( FlashEnv.SEGMENTS_PER_CURVE ) );
          _drawingPosition = anchorPoint;
        }
        //End
        else if ( shapeRecord is EndShapeRecord )
        {
        }
      }
    }
    private bool IsTheSameContour( StyleChangeRecord styleChangeRecord, ShapeElement element )
    {
      Vector3 pos = new Vector3( float.MinValue, float.MinValue, float.MinValue );
      if ( styleChangeRecord.MoveDeltaX != int.MinValue && styleChangeRecord.MoveDeltaY != int.MinValue )
        pos = FlashToUnityConverter.ConvertPosition( styleChangeRecord.MoveDeltaX, styleChangeRecord.MoveDeltaY );
      bool samePos = pos == element.Points.LastAddedPoint;

      if ( ( styleChangeRecord.FillStyle0 == int.MinValue ||
          styleChangeRecord.FillStyle1 == int.MinValue ) && samePos/* && 
                styleChangeRecord.LineStyle == int.MinValue*/)
        return true;



      if ( styleChangeRecord.FillStyle0 != element.StyleChangeRecord.FillStyle0 )
        return false;
      if ( styleChangeRecord.FillStyle1 != element.StyleChangeRecord.FillStyle1 )
        return false;
      //if (styleChangeRecord.LineStyle != element.StyleChangeRecord.LineStyle)
      //    return false;

      return true;
    }
    private void BuildStyles()
    {
      foreach ( RenderableElement element in Shapes )
      {
        CreateStyles( (ShapeElement)element );
      }
    }
    private void CreateStyles( ShapeElement element )
    {
      //Debug.Log(" FS0:  " + element.StyleChangeRecord.FillStyle0 + "     FS1:  " + element.StyleChangeRecord.FillStyle1 +
      //          "     LS:  " + element.StyleChangeRecord.LineStyle + "    0xF:   " + element.StyleChangeRecord.FillStyles +
      //          "    0xL:   " + element.StyleChangeRecord.LineStyles +" Count : " + element.Contour.Count);


      // Update filStyleArray
      if ( element.StyleChangeRecord.FillStyles != null )
        _currentFillStyleArray = element.StyleChangeRecord.FillStyles;

      // Update fillStyle
      if ( element.StyleChangeRecord.FillStyle1 != int.MinValue )
      {
        if ( element.StyleChangeRecord.FillStyle1 != 0 )
          _currentFillStyle = _currentFillStyleArray[element.StyleChangeRecord.FillStyle1 - 1];
        else
          _currentFillStyle = null;
      }
      // TODO : поддержка обоих филстайлов
      if ( element.StyleChangeRecord.FillStyle0 != int.MinValue )
      {
        if ( element.StyleChangeRecord.FillStyle0 != 0 )
          _currentFillStyle = _currentFillStyleArray[element.StyleChangeRecord.FillStyle0 - 1];
        else
          _currentFillStyle = null;
      }
      if ( _currentFillStyle != null )
        element.UniFillStyle = new UniFillStyle( _currentFillStyle, Swf );

      // Update lineStyleArray
      if ( element.StyleChangeRecord.LineStyles != null )
        _currentLineStyleArray = element.StyleChangeRecord.LineStyles;

      // Update lineStyle
      if ( element.StyleChangeRecord.LineStyle != int.MinValue )
      {
        if ( element.StyleChangeRecord.LineStyle != 0 )
          _currentLineStyle = _currentLineStyleArray[element.StyleChangeRecord.LineStyle - 1];
        else
          _currentLineStyle = null;
      }
      if ( _currentLineStyle != null )
      {
        element.UniLineStyle = new UniLineStyle( _currentLineStyle, Swf );
      }
    }
  }
}