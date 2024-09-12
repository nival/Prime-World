#pragma once

#include <Render/FlashRendererInterface.h>

#include "System/SystemLog.h"

#include "../../swf_parse.h"
#include "../../FlashMovieAvmCore.h"
#include "../../FlashBaseClasses.h"
#include "../PlayerGlobalIncludes.h"

#include "Geometry.h"
#include "Tesselate.h"
#include "MeshSet.h"

namespace Render
{
  _interface IFlashRenderer;
}

namespace flash
{
  struct ShapeDefinition;
  struct mesh_set;
  struct edge;
  class MorphData;
}

namespace avmplus
{
class DoubleVectorObject;
class IntVectorObject;
class ShaderObject;
class ScriptObject;
class ArrayObject;
class BitmapDataObject;
class GraphicsObject;

class GraphicsObject : public FlashScriptObject
{
public:
  GraphicsObject( GraphicsClass * classType );
  GraphicsObject( VTable* ivtable, ScriptObject* prototype );
  ~GraphicsObject();

  // AS methods

  void curveTo(double controlX, double controlY, double anchorX, double anchorY);
  void lineTo(double x, double y);
  void moveTo(double x, double y);

  void drawTriangles(DoubleVectorObject* vertices, IntVectorObject* indices, DoubleVectorObject* uvtData, AvmString culling);
  void drawRect(double x, double y, double width, double height);
  void drawPath(IntVectorObject* commands, DoubleVectorObject* data, AvmString winding);
  void drawRoundRectComplex(double x, double y, double width, double height, double topLeftRadius, double topRightRadius, double bottomLeftRadius, double bottomRightRadius);
  void drawRoundRect(double x, double y, double width, double height, double ellipseWidth, double ellipseHeight);

  void lineStyle(double thickness, uint color, double alpha, bool pixelHinting, AvmString scaleMode, AvmString caps, AvmString joints, double miterLimit);
  void lineGradientStyle(AvmString type, ArrayObject* colors, ArrayObject* alphas, ArrayObject* ratios, ScriptObject/*Matrix*/ * matrix, AvmString spreadMethod, AvmString interpolationMethod, double focalPointRatio);
  void lineBitmapStyle(BitmapDataObject* bitmap, ScriptObject/*Matrix*/ * matrix, bool repeat, bool smooth);
  void lineShaderStyle(ShaderObject* shader, ScriptObject/*Matrix*/ * matrix);

  void beginFill(uint color, double alpha);
  void beginGradientFill(AvmString type, ArrayObject* colors, ArrayObject* alphas, ArrayObject* ratios, ScriptObject/*Matrix*/ * matrix, AvmString spreadMethod, AvmString interpolationMethod, double focalPointRatio);
  void beginBitmapFill(BitmapDataObject* bitmap, ScriptObject/*Matrix*/ * matrix, bool repeat, bool smooth);
  void beginShaderFill(ShaderObject* shader, ScriptObject/*Matrix*/ * matrix);

  void endFill();
  
  void clear();

  void copyFrom(GraphicsObject* sourceGraphics);

  // own methods

  void SetCharacterID( int characterID, int rate );
  void SetShape( const flash::ShapeDefinition& _shapeDesc );

  void SetMorphData( flash::MorphData* _morphData );
  
  void DoRender( Render::IFlashRenderer* _renderer, const flash::SWF_MATRIX& _matrix, const flash::SWF_CXFORMWITHALPHA& _cxform, EFlashBlendMode::Enum blendMode );
  void DoRenderMorph( Render::IFlashRenderer* _renderer, const flash::SWF_MATRIX& _matrix, const flash::SWF_CXFORMWITHALPHA& _cxform, EFlashBlendMode::Enum blendMode, float _rate );

  void GetBounds( flash::SWF_RECT& _bounds );
  bool HitTest( const flash::SWF_POINT & localPoint );

  bool GetMaxError( const flash::SWF_MATRIX& _matrix, float& _error );
  flash::MeshSet* GetMesh( float _error );

  flash::FillStyles& GetFillStyles() { return fillStyles; }
  flash::LineStyles& GetLineStyles() { return lineStyles; }

  const flash::FillStyles& GetFillStyles() const { return fillStyles; }
  const flash::LineStyles& GetLineStyles() const { return lineStyles; }

private:

  void Tesselate( float error_tolerance, flash::IMeshAccepter * accepter );

  void Clear();
  void ClearMeshCache();

  void SortAndCleanMeshes();

  void BuildArc( float startAngle, float endAngle, nstl::vector<flash::edge>& edges, const CVec2& center, const CVec2& radiuses,
                 int parts, float radiusExtent, float lastX, float lastY );
  void EndPath();

  // temporary

  bool pathsOutOfDate;
  bool boundsOutOfDate;

  nstl::vector<flash::path>	paths;
  nstl::vector<Strong<flash::MeshSet>> cachedMeshes;
  flash::path	currentPath;

  flash::FillStyles fillStyles;
  flash::LineStyles lineStyles;

  Weak<flash::MorphData> morphData;

  flash::SWF_RECT bounds;

  int meshSetID;

  struct TesselatorThunk : public flash::ITesselatedShape 
  {
    TesselatorThunk( GraphicsObject& _parent ) : parent(_parent) {}

    GraphicsObject& parent;

    virtual const flash::FillStyles& GetFillStyles() const { return parent.GetFillStyles(); }
    virtual const flash::LineStyles& GetLineStyles() const { return parent.GetLineStyles(); }

    virtual void  Tesselate( float error_tolerance, flash::IMeshAccepter * accepter ) const { parent.Tesselate( error_tolerance, accepter ); }
  };

  TesselatorThunk tesselatorThunk;

  DECLARE_SLOTS_GraphicsObject;
};
  
DECLARE_AS_CLASS_WITH_CACHE( GraphicsClass, ClassClosure, GraphicsObject )

}