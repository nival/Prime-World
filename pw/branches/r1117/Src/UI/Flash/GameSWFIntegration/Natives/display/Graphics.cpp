#include "TamarinPCH.h"

#include <Render/FlashRendererInterface.h>

#include "../../Characters.h"
#include "../../FlashMovie.h"
#include "../../MorphData.h"

#include "FlashMeshCollection.h"
#include "Graphics.h"
#include "MeshSet.h"

namespace avmplus
{

#pragma warning( disable: 4355 ) //'this' : used in base member initializer list

GraphicsObject::GraphicsObject( GraphicsClass * classType ) : 
  FlashScriptObject(classType->ivtable(), classType->prototype ),
  meshSetID(-1),
  tesselatorThunk(*this),
  pathsOutOfDate(false),
  boundsOutOfDate(false)
{ 

}

GraphicsObject::GraphicsObject( VTable* ivtable, ScriptObject* prototype ) : 
  FlashScriptObject(ivtable, prototype),
  meshSetID(-1),
  tesselatorThunk(*this),
  pathsOutOfDate(false),
  boundsOutOfDate(false)
{ 

}

GraphicsObject::~GraphicsObject() 
{ 
  Clear();
}

void GraphicsObject::Clear()
{
  paths.clear();

  ClearMeshCache();

  pathsOutOfDate = false;
  boundsOutOfDate = true;
}

void GraphicsObject::ClearMeshCache()
{
  cachedMeshes.clear();
}

void GraphicsObject::drawTriangles(DoubleVectorObject* vertices, IntVectorObject* indices, DoubleVectorObject* uvtData, AvmString culling)
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  pathsOutOfDate = true;
  boundsOutOfDate = true;
  meshSetID = -1;
}

void GraphicsObject::drawRect(double x, double y, double width, double height)
{
  float curX = PIXELS_TO_TWIPS( x );
  float curY = PIXELS_TO_TWIPS( y );

  currentPath.m_ax = curX;
  currentPath.m_ay = curY;

  curY += PIXELS_TO_TWIPS( height );
  currentPath.m_edges.push_back( flash::edge(curX, curY, curX, curY) );
  curX += PIXELS_TO_TWIPS( width );
  currentPath.m_edges.push_back( flash::edge(curX, curY, curX, curY) );
  curY -= PIXELS_TO_TWIPS( height );
  currentPath.m_edges.push_back( flash::edge(curX, curY, curX, curY) );
  curX -= PIXELS_TO_TWIPS( width );
  currentPath.m_edges.push_back( flash::edge(curX, curY, curX, curY) );

  pathsOutOfDate = true;
  boundsOutOfDate = true;
  meshSetID = -1;
}

void GraphicsObject::drawPath(IntVectorObject* commands, DoubleVectorObject* data, AvmString winding)
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  pathsOutOfDate = true;
  boundsOutOfDate = true;
  meshSetID = -1;
}

void GraphicsObject::curveTo(double controlX, double controlY, double anchorX, double anchorY)
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  pathsOutOfDate = true;
  boundsOutOfDate = true;
  meshSetID = -1;
}

void GraphicsObject::beginFill(uint color, double alpha)
{
  flash::SWF_FILLSTYLE newFillStyle;
  newFillStyle.FillStyleType = 0x00;
  newFillStyle.Color.SetUInt( color );
  newFillStyle.Color.a = flash::UI8( alpha * 255.0 );

  fillStyles.push_back( newFillStyle );

  currentPath.m_fill0 = fillStyles.size();

  pathsOutOfDate = true;
  meshSetID = -1;
}

void GraphicsObject::clear()
{
  Clear();
}

void GraphicsObject::lineTo(double x, double y)
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  pathsOutOfDate = true;
  boundsOutOfDate = true;
  meshSetID = -1;
}

void GraphicsObject::beginShaderFill(ShaderObject* shader, ScriptObject/*Matrix*/ * matrix)
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  pathsOutOfDate = true;
  meshSetID = -1;
}

void GraphicsObject::lineGradientStyle(AvmString type, ArrayObject* colors, ArrayObject* alphas, ArrayObject* ratios, ScriptObject/*Matrix*/ * matrix, AvmString spreadMethod, AvmString interpolationMethod, double focalPointRatio)
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  pathsOutOfDate = true;
  meshSetID = -1;
}

void GraphicsObject::beginBitmapFill(BitmapDataObject* bitmap, ScriptObject/*Matrix*/ * matrix, bool repeat, bool smooth)
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  pathsOutOfDate = true;
  meshSetID = -1;
}

void GraphicsObject::beginGradientFill(AvmString type, ArrayObject* colors, ArrayObject* alphas, ArrayObject* ratios, ScriptObject/*Matrix*/ * matrix, AvmString spreadMethod, AvmString interpolationMethod, double focalPointRatio)
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  pathsOutOfDate = true;
  meshSetID = -1;
}

void GraphicsObject::lineStyle(double thickness, uint color, double alpha, bool pixelHinting, AvmString scaleMode, AvmString caps, AvmString joints, double miterLimit)
{
  flash::SWF_LINESTYLE2 newLineStyle;

  newLineStyle.Width = PIXELS_TO_TWIPS( thickness );
  newLineStyle.Color.SetUInt( color );
  newLineStyle.Color.a = flash::UI8( alpha * 255.0 );

  lineStyles.push_back( newLineStyle );

  currentPath.m_line = lineStyles.size();

  pathsOutOfDate = true;
  meshSetID = -1;
}

void GraphicsObject::drawRoundRectComplex(double x, double y, double width, double height, double topLeftRadius, double topRightRadius, double bottomLeftRadius, double bottomRightRadius)
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  pathsOutOfDate = true;
  boundsOutOfDate = true;
  meshSetID = -1;
}

void GraphicsObject::moveTo(double x, double y)
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  pathsOutOfDate = true;
  boundsOutOfDate = true;
  meshSetID = -1;
}

void GraphicsObject::BuildArc( float startAngle, float endAngle, nstl::vector<flash::edge>& edges, const CVec2& center, const CVec2& radiuses,
                              int parts, float radiusExtent, float lastX, float lastY )
{
  float angleStepHalf = 0.5f * ( endAngle - startAngle ) / parts;

  for ( int i = 0; i < parts; ++i )
  {
    startAngle += angleStepHalf;

    // control angles
    float cosValC = cos( startAngle );
    float sinValC = -sin( startAngle );

    startAngle += angleStepHalf;

    // anchor angles
    float cosValA = cos( startAngle );
    float sinValA = -sin( startAngle );

    if ( i == parts - 1 )
    {
      currentPath.m_edges.push_back( flash::edge(center.x + radiuses.x * cosValC * radiusExtent, center.y + radiuses.y * radiusExtent * sinValC, 
                                                  lastX, lastY) );
    }
    else
    {
      currentPath.m_edges.push_back( flash::edge(center.x + radiuses.x * cosValC * radiusExtent, center.y + radiuses.y * radiusExtent * sinValC, 
                                                  center.x + radiuses.x * cosValA, center.y + radiuses.y * sinValA) );
    }
  }
}

void GraphicsObject::drawRoundRect(double x, double y, double width, double height, double ellipseWidth, double ellipseHeight)
{
  height = PIXELS_TO_TWIPS( height );
  width = PIXELS_TO_TWIPS( width );

  ellipseHeight = PIXELS_TO_TWIPS( ellipseHeight / 2.0 );
  ellipseWidth = PIXELS_TO_TWIPS( ellipseWidth / 2.0 );

  float curX = PIXELS_TO_TWIPS( x );
  float curY = PIXELS_TO_TWIPS( y ) + ellipseHeight;

  currentPath.m_ax = curX;
  currentPath.m_ay = curY;

//  float oldHeight = height;
//  float oldWidth = width;

  height -= ellipseHeight * 2.0;
  width  -= ellipseWidth * 2.0;

  curY += height;
  currentPath.m_edges.push_back( flash::edge(curX, curY, curX, curY) );

  curX += ellipseWidth;
  curY += ellipseHeight;

  CVec2 center( curX, curY - ellipseHeight );
  CVec2 radiuses( ellipseWidth, ellipseHeight );

  BuildArc( FP_PI, FP_PI * 1.5f, currentPath.m_edges, center, radiuses, 3, 1.03f, curX, curY );

  curX += width;
  currentPath.m_edges.push_back( flash::edge(curX, curY, curX, curY) );

  curX += ellipseWidth;
  curY -= ellipseHeight;
  center = CVec2( curX - ellipseWidth, curY );
  BuildArc( FP_PI * 1.5f, FP_PI * 2.0f, currentPath.m_edges, center, radiuses, 3, 1.03f, curX, curY );

  curY -= height;
  currentPath.m_edges.push_back( flash::edge(curX, curY, curX, curY) );

  curX -= ellipseWidth;
  curY -= ellipseHeight;
  center = CVec2( curX, curY + ellipseHeight);
  BuildArc( 0.f, FP_PI * 0.5f, currentPath.m_edges, center, radiuses, 3, 1.03f, curX, curY );

  curX -= width;
  currentPath.m_edges.push_back( flash::edge(curX, curY, curX, curY) );

  curX -= ellipseWidth;
  curY += ellipseHeight;
  center = CVec2( curX + ellipseWidth, curY );
  BuildArc( FP_PI * 0.5f, FP_PI, currentPath.m_edges, center, radiuses, 3, 1.03f, curX, curY );

  pathsOutOfDate = true;
  boundsOutOfDate = true;
  meshSetID = -1;
}

void GraphicsObject::lineBitmapStyle(BitmapDataObject* bitmap, ScriptObject/*Matrix*/ * matrix, bool repeat, bool smooth)
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  pathsOutOfDate = true;
  meshSetID = -1;
}

void GraphicsObject::lineShaderStyle(ShaderObject* shader, ScriptObject/*Matrix*/ * matrix)
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  pathsOutOfDate = true;
  meshSetID = -1;
}

void GraphicsObject::endFill()
{
  EndPath();
  pathsOutOfDate = true;
  meshSetID = -1;
}

void GraphicsObject::copyFrom(GraphicsObject* sourceGraphics)
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  pathsOutOfDate = true;
  boundsOutOfDate = true;
  meshSetID = -1;
}

void GraphicsObject::SetCharacterID( int characterID, int rate )
{
  const char* filename = FlashCore()->GetMovie()->GetFileName().c_str();

  if ( flash::FlashMeshCollection::GetInstance() )
    meshSetID = flash::FlashMeshCollection::GetInstance()->GetMeshSetID( filename, characterID, rate );
}

void GraphicsObject::SetShape( const flash::ShapeDefinition& _shapeDesc )
{
  paths = _shapeDesc.GetPaths();
  fillStyles = _shapeDesc.fillStyles;
  lineStyles = _shapeDesc.lineStyles;

  bounds = _shapeDesc.shapeBounds;

  pathsOutOfDate = true;
}

void GraphicsObject::SetMorphData( flash::MorphData* _morphData )
{
  morphData = _morphData;
}

void GraphicsObject::Tesselate( float error_tolerance, flash::IMeshAccepter * accepter )
{
  flash::Tesselator tesselator;

  tesselator.begin_shape( &tesselatorThunk, accepter, error_tolerance );

  for ( int i = 0; i < paths.size(); ++i )
  {
    if ( paths[i].m_new_shape )
    {
      tesselator.end_shape();
      tesselator.begin_shape( &tesselatorThunk, accepter, error_tolerance );
    }
    else
    {
      paths[i].tesselate( tesselator );
    }
  }

  tesselator.end_shape();
}

bool GraphicsObject::GetMaxError( const flash::SWF_MATRIX& _matrix, float& _error )
{
  float	max_scale = _matrix.GetMaxScale();

  if ( fabsf( max_scale ) < 1e-6f )
    return false;

  const float s_curve_max_pixel_error = 20.f; // TODO move to options

  float pixelScale = FlashCore()->GetMovie()->GetPixelScale();

  _error = flash::TWIP / max_scale / pixelScale * s_curve_max_pixel_error;

  return true;
}

flash::MeshSet* GraphicsObject::GetMesh( float _error )
{
  if ( meshSetID >= 0 )
    return flash::FlashMeshCollection::GetInstance()->GetMeshSet( meshSetID, _error, &tesselatorThunk );

  return 0;
}

void GraphicsObject::DoRender( Render::IFlashRenderer* _renderer, const flash::SWF_MATRIX& _matrix, const flash::SWF_CXFORMWITHALPHA& _cxform, EFlashBlendMode::Enum blendMode )
{
  float	object_space_max_error;

  if ( !GetMaxError( _matrix, object_space_max_error ) )
    return;

  _renderer->SetMatrix( _matrix );
  _renderer->SetColorTransform( _cxform );
  _renderer->SetBlendMode( blendMode );

  if ( meshSetID >= 0 )
  {
    Weak<flash::MeshSet>	candidate = flash::FlashMeshCollection::GetInstance()->GetMeshSet( meshSetID, object_space_max_error, &tesselatorThunk );

    if ( candidate )
      candidate->Display( _renderer, FlashCore()->GetMovie(), fillStyles, lineStyles );
  }
  else
  {
    if ( pathsOutOfDate )
    {
      EndPath();
      ClearMeshCache();
      pathsOutOfDate = false;
    }

    for (int i = 0, n = cachedMeshes.size(); i < n; i++)
    {
      Weak<flash::MeshSet>	candidate = cachedMeshes[i];

      if (object_space_max_error > candidate->get_error_tolerance() * 3.0f)
        break;

      if (object_space_max_error > candidate->get_error_tolerance())
      {
        candidate->Display( _renderer, FlashCore()->GetMovie(),fillStyles, lineStyles );
        return;
      }
    }

    Strong<flash::MeshSet>	meshSet = new flash::MeshSet( &tesselatorThunk, object_space_max_error * 0.75f);
    cachedMeshes.push_back( meshSet );
    meshSet->Display( _renderer, FlashCore()->GetMovie(),fillStyles, lineStyles );

    void SortAndCleanMeshes();
  }
}

void GraphicsObject::DoRenderMorph( Render::IFlashRenderer* _renderer, const flash::SWF_MATRIX& _matrix, const flash::SWF_CXFORMWITHALPHA& _cxform, EFlashBlendMode::Enum blendMode, float _rate )
{
  float	object_space_max_error;

  if ( !GetMaxError( _matrix, object_space_max_error ) )
    return;

  _renderer->SetMatrix( _matrix );
  _renderer->SetColorTransform( _cxform );
  _renderer->SetBlendMode( blendMode );

  NI_VERIFY( meshSetID >= 0, "Morph should have mesh set ID", return );

  Weak<flash::MeshSet>	meshSet = flash::FlashMeshCollection::GetInstance()->GetMeshSet( meshSetID, object_space_max_error, &tesselatorThunk );

  if ( meshSet && morphData )
  {
    meshSet->ApplyColorsAndUV( _renderer, FlashCore()->GetMovie(), fillStyles, lineStyles );
    meshSet->DisplayMorph( _renderer, FlashCore()->GetMovie(), 
      morphData->GetStartShape().fillStyles, morphData->GetStartShape().lineStyles, 
      morphData->GetEndShape().fillStyles, morphData->GetEndShape().lineStyles, _rate );
//     meshSet->DisplayMorph( _renderer, FlashCore()->GetMovie(), 
//       fillStyles, lineStyles, 
//       fillStyles, lineStyles, 0.f );
  }
}

static int SortByError(const void* A, const void* B)
{
  const flash::MeshSet*	a = *(const flash::MeshSet**) A;
  const flash::MeshSet*	b = *(const flash::MeshSet**) B;

  if (a->get_error_tolerance() < b->get_error_tolerance())
  {
    return 1;
  }
  else if (a->get_error_tolerance() > b->get_error_tolerance())
  {
    return -1;
  }
  else
  {
    return 0;
  }
}

void GraphicsObject::SortAndCleanMeshes()
{
  if (cachedMeshes.size() > 0)
  {
    qsort(
      &cachedMeshes[0],
      cachedMeshes.size(),
      sizeof(cachedMeshes[0]),
      SortByError);
  }
}

void GraphicsObject::GetBounds( flash::SWF_RECT& _bounds ) 
{ 
  if (  boundsOutOfDate )
  {
    bounds.X1 = FLT_MAX;
    bounds.X2 = FLT_MIN;
    bounds.Y1 = FLT_MAX;
    bounds.Y2 = FLT_MIN;
    
    EndPath();

    for ( int i = 0; i < paths.size(); ++i )
    {
      nstl::vector<flash::edge>& edges = paths[i].m_edges;

      for ( int j = 0; j < edges.size(); ++j )
      {
        bounds.ExpandToPoint( flash::SWF_POINT( edges[j].m_cx, edges[j].m_cy ) );
        bounds.ExpandToPoint( flash::SWF_POINT( edges[j].m_ax, edges[j].m_ay ) );
      }
    }

    boundsOutOfDate = false;
  }

  _bounds = bounds; 
}

bool GraphicsObject::HitTest( const flash::SWF_POINT & localPoint )
{
  for ( int i = 0; i < paths.size(); ++i )
  {
    if ( paths[i].point_test( localPoint.X, localPoint.Y ) )
      return true;
  }

  return false;
}

void GraphicsObject::EndPath()
{
  if ( !currentPath.is_empty() )
  {
    paths.push_back( currentPath );
    currentPath.m_edges.resize( 0 );
  }
}


}