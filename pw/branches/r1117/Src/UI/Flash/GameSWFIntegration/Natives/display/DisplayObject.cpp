#include "TamarinPCH.h"

#include "Render/FlashRendererInterface.h"

#include "../../FlashMovie.h"
#include "../../builtins/BuiltinPools.h"

#include "../filters/BitmapFilter.h"

#include "DisplayObject.h"
#include "DisplayObjectContainer.h"
#include "Stage.h"

#include "System/InlineProfiler.h"

namespace 
{
  static bool g_DebugRender = false;
  static nstl::string g_DebugObjectName = "";

  REGISTER_DEV_VAR( "flash_debug_render", g_DebugRender, STORAGE_NONE );
  REGISTER_DEV_VAR( "flash_debug_object", g_DebugObjectName, STORAGE_NONE );
}

namespace avmplus
{
DisplayObjectObject::DisplayObjectObject( DisplayObjectClass * classType ):
  EventDispatcherObject((EventDispatcherClass*)classType, NULL),
  advanceMark(false),
  isNonBlocked(false),
  isNonBlockedOverride(false),
  parent( core()->GetGC()->emptyWeakRef ),
  stage( core()->GetGC()->emptyWeakRef ),
  root( core()->GetGC()->emptyWeakRef )
{
  Initialize();
}

DisplayObjectObject::DisplayObjectObject(VTable* ivtable, ScriptObject* prototype):
  EventDispatcherObject(ivtable, prototype),
  advanceMark(false),
  isNonBlocked(false),
  isNonBlockedOverride(false),
  parent( core()->GetGC()->emptyWeakRef ),
  stage( core()->GetGC()->emptyWeakRef ),
  root( core()->GetGC()->emptyWeakRef )
{
  Initialize();
}

DisplayObjectContainerObject* DisplayObjectObject::get_parent() 
{ 
  DisplayObjectContainerObject* _parent = (DisplayObjectContainerObject*)parent->get(); 
  return _parent;
}

DisplayObjectObject* DisplayObjectObject::get_root() 
{
  DisplayObjectObject* _root = (DisplayObjectObject*)root->get(); 
  return _root;
}

StageObject* DisplayObjectObject::get_stage() 
{
  StageObject* _stage = (StageObject*)stage->get(); 
  return _stage;
}

void DisplayObjectObject::Initialize()
{
  beeingDragged = false;
  usedAsMask = false;

  useScale9Grid = false;
  useParentScale9Grid = false;

  characterID = 0;
  depth = -1;
  clippingDepth = 0;
  ratio = 0;
  creationFrame = -1;

  visible = true;
  cacheAsBitmap = false;

  zLocal = 0.0;

  rotationX = 0.0;
  rotationY = 0.0;
  rotationZ = 0.0;

  scaleZ = 1.0;

  mouseX = 0.0;
  mouseY = 0.0;

  opaqueBackground = nullObjectAtom;
  blendMode = new BlendMode( core() );

  flash::FlashMovieAvmCore * flashCore = (flash::FlashMovieAvmCore*) core();

  name = flashCore->GenerateUniqueName();

  Atom args[] = {0};

  TransformClass * transformClass = flashCore->GetClassCache().GetClass<TransformClass>( EFlashClassID::TransformClass );
  transform = (TransformObject *)flashCore->atomToScriptObject(transformClass->construct(0, args));

  avmplus::ClassClosure * closure1 = flashCore->GetClassInPool( "AccessibilityProperties", PoolType::Accessibility );
  accessibilityProperties = flashCore->atomToScriptObject( closure1->construct(0, args));

  enterFrameEvent = FlashCore()->CreateSimpleEvent( FlashCore()->GetEventTypes().ENTER_FRAME );
}

DisplayObjectObject::~DisplayObjectObject()
{
  delete blendMode;
}

Atom DisplayObjectObject::toString()
{
  char pointerStr[32];

  sprintf_s( pointerStr, "[object (%p)", this );

  AvmCore* core = this->core();
  Stringp s = core->concatStrings(core->newConstantStringLatin1( pointerStr ), get_name());
  return core->concatStrings(s, core->newConstantStringLatin1("]"))->atom();
}

void DisplayObjectObject::SetCharacterID( int id ) 
{ 
  characterID = id; 
  OnSetCharacterID( characterID ); 
}

void DisplayObjectObject::set_visible(bool value) 
{ 
  visible = value; 
}

void DisplayObjectObject::set_name(AvmString value) 
{
  StUTF8String nameT( name );
  nameCopy = nameT.c_str();
  name = value;
}

avmplus::AvmString DisplayObjectObject::get_name()
{
  AvmAssert(name!=0);
  return name;
}

void DisplayObjectObject::SetStageAndRoot( StageObject * newStage, DisplayObjectObject* newRoot, bool parentHasListener )
{
  SetRoot(newRoot);
  bool hasListener = newStage? HasAddToStageListener() : HasRemoveFromStageListener();
  SetStage(newStage, hasListener || parentHasListener );
}

void DisplayObjectObject::SetParent( DisplayObjectContainerObject * parentObject ) 
{
  if ( parentObject )
    parent = parentObject->GetWeakRef(); 
  else
    parent = core()->GetGC()->emptyWeakRef;
}

void DisplayObjectObject::SetRoot( DisplayObjectObject* newRoot ) 
{
  if ( newRoot )
    root = newRoot->GetWeakRef(); 
  else
    root = core()->GetGC()->emptyWeakRef;
}

void DisplayObjectObject::SetStage( StageObject * newStage, bool fireStage ) 
{
  bool removedFromStage = stage->get() && !newStage;

  if ( newStage )
    stage = newStage->GetWeakRef(); 
  else
    stage = core()->GetGC()->emptyWeakRef;

  if ( removedFromStage )
  {
    OnRemovedFromDisplayList();

    if ( fireStage )
      Fire_REMOVED_FROM_STAGE();
  }
  else if ( newStage )
  {
    OnAddedToDisplayList();

    if ( fireStage )
      Fire_ADDED_TO_STAGE();
  }
}

bool DisplayObjectObject::_hitTest(bool use_xy, double x, double y, bool useShape, DisplayObjectObject* hitTestObject)
{
  NI_ALWAYS_ASSERT("Not implemented");
  return false;
}

void DisplayObjectObject::set_mask(DisplayObjectObject* value) 
{ 
  if ( mask )
    mask->SetUsedAsMask( false );

  mask = value; 

  if ( mask )
    mask->SetUsedAsMask( true );
}

ScriptObject/*Point*/ * DisplayObjectObject::localToGlobal(ScriptObject/*Point*/ * point)
{
  return GlobalConvert(point, true);
}

ScriptObject/*Point*/ * DisplayObjectObject::globalToLocal(ScriptObject/*Point*/ * point)
{
  return GlobalConvert(point, false);
}


ScriptObject/*Point*/ * DisplayObjectObject::GlobalConvert( ScriptObject/*Point*/ * point, bool local2global )
{
  flash::SWF_POINT inputPoint, outputPoint;

  int _c_x = FlashScriptObject::GetSlotID( point, "x" );
  int _c_y = FlashScriptObject::GetSlotID( point, "y" );

  inputPoint.X = core()->number_d( point->getSlotAtom( _c_x ) ) * 20.f;
  inputPoint.Y = core()->number_d( point->getSlotAtom( _c_y ) ) * 20.f;

  local2global? LocalToGlobal(outputPoint, inputPoint) : GlobalToLocal(outputPoint, inputPoint);;

  Atom args[] = {0};
  avmplus::ClassClosure * closurePoint = FlashCore()->GetClassInPool("Point", PoolType::Geom);

  if (!closurePoint)
    return 0;

  ScriptObject * result = FlashCore()->atomToScriptObject(closurePoint->construct(0, args));

  result->coerceAndSetSlotAtom( _c_x, core()->doubleToAtom( outputPoint.X / 20.f  ) );
  result->coerceAndSetSlotAtom( _c_y, core()->doubleToAtom( outputPoint.Y /20.f) );
  return result;
}

ScriptObject/*Point*/ * DisplayObjectObject::local3DToGlobal(ScriptObject/*Vector3D*/ * point3d)
{
  NI_ALWAYS_ASSERT("Not implemented");
  return 0;
}

ScriptObject/*Vector3D*/ * DisplayObjectObject::globalToLocal3D(ScriptObject/*Point*/ * point)
{
  NI_ALWAYS_ASSERT("Not implemented");
  return 0;
}

ScriptObject/*Rectangle*/ * DisplayObjectObject::getBounds(DisplayObjectObject* targetCoordinateSpace)
{

  return 0;
}

ScriptObject/*Rectangle*/ * DisplayObjectObject::getRect(DisplayObjectObject* targetCoordinateSpace)
{
  NI_ALWAYS_ASSERT("Not implemented");
  return 0;
}

void DisplayObjectObject::set_blendShader(ShaderObject* value)
{
  NI_ALWAYS_ASSERT("Not implemented");
}

void DisplayObjectObject::set_width(double value) 
{ 
  flash::SWF_RECT bounds;
  GetBounds( bounds );

  if ( bounds.GetWidth() > 0.f )
    set_scaleX( PIXELS_TO_TWIPS( value ) / bounds.GetWidth() );
}

double DisplayObjectObject::get_width() 
{ 
  flash::SWF_RECT bounds;
  GetBounds( bounds );

  float _scale = get_scaleX();
  float _width = TWIPS_TO_PIXELS( bounds.GetWidth() * _scale );

  return _width;
}

void DisplayObjectObject::set_height(double value) 
{ 
  flash::SWF_RECT bounds;
  GetBounds( bounds );

  if ( bounds.GetWidth() > 0.f )
    set_scaleY( PIXELS_TO_TWIPS( value ) / bounds.GetHeight() );
}

double DisplayObjectObject::get_height() 
{ 
  flash::SWF_RECT bounds;
  GetBounds( bounds );

  return TWIPS_TO_PIXELS( bounds.GetHeight() * get_scaleY() );
}

void DisplayObjectObject::set_alpha(double value) 
{ 
  GetColorTransform().m_[3][1] = 0.f; 
  GetColorTransform().m_[3][0] = value; 
}

double DisplayObjectObject::get_alpha() 
{ 
  return GetColorTransform().m_[3][0]; 
}

void DisplayObjectObject::set_x(double value) 
{ 
  NI_ASSERT( !_isnan( value ) && _finite( value ), "Wrong set_x value from script" );
  GetMatrix().m_[0][2] = PIXELS_TO_TWIPS( value ); 
}

double DisplayObjectObject::get_x() 
{ 
  return TWIPS_TO_PIXELS( GetMatrix().m_[0][2] ); 
}

void DisplayObjectObject::set_y(double value) 
{ 
  NI_ASSERT( !_isnan( value ) && _finite( value ), "Wrong set_y value from script" );
  GetMatrix().m_[1][2] = PIXELS_TO_TWIPS( value ); 
}

double DisplayObjectObject::get_y() 
{ 
  return TWIPS_TO_PIXELS( GetMatrix().m_[1][2] ); 
}

void DisplayObjectObject::set_scaleX(double value) 
{ 
  NI_ASSERT( !_isnan( value ) && _finite( value ), "Wrong scaleX value from script" );
  
  double scaleY = GetMatrix().GetYScale();
  double rotation = GetMatrix().GetRotation();

  GetMatrix().SetScaleRotation( value, scaleY, rotation ); 
}

double DisplayObjectObject::get_scaleX()
{
  return GetMatrix().GetXScale();
}

void DisplayObjectObject::set_scaleY(double value) 
{ 
  NI_ASSERT( !_isnan( value ) && _finite( value ), "Wrong scaleY value from script" );

  double scaleX = GetMatrix().GetXScale();
  double rotation = GetMatrix().GetRotation();

  GetMatrix().SetScaleRotation( scaleX, value, rotation ); 
}

double DisplayObjectObject::get_scaleY()
{
  return GetMatrix().GetYScale();
}

void DisplayObjectObject::set_rotation(double value)
{
  NI_ASSERT( !_isnan( value ) && _finite( value ), "Wrong rotation value from script" );

  double scaleX = GetMatrix().GetXScale();
  double scaleY = GetMatrix().GetYScale();

  GetMatrix().SetScaleRotation( scaleX, scaleY, value ); 
}

double DisplayObjectObject::get_rotation()
{
  return GetMatrix().GetRotation();
}

void DisplayObjectObject::GetLocalMousePoint( flash::SWF_POINT& localPoint )
{
  flash::SWF_POINT flashMousePoint;

  FlashCore()->GetMovie()->GetFlashMousePoint( flashMousePoint );

  GlobalToLocal( localPoint, flashMousePoint );
}

double DisplayObjectObject::get_mouseX() 
{ 
  flash::SWF_POINT localMousePoint;

  GetLocalMousePoint( localMousePoint );

  return TWIPS_TO_PIXELS( localMousePoint.X ); 
}

double DisplayObjectObject::get_mouseY() 
{ 
  flash::SWF_POINT localMousePoint;

  GetLocalMousePoint( localMousePoint );

  return TWIPS_TO_PIXELS( localMousePoint.Y ); 
}

void DisplayObjectObject::Render( Render::IFlashRenderer* _renderer, const flash::SWF_MATRIX& _matrix, 
                                 const flash::SWF_CXFORMWITHALPHA& _cxform, EFlashBlendMode::Enum _worldMode,  bool asMask )
{
  NI_PROFILE_HEAVY_FUNCTION

  if ( !visible )
    return;

  if ( !asMask && usedAsMask )
    return;

  if ( fabs ( GetColorTransform().m_[3][0] ) < DBL_EPSILON )
    return;

  flash::SWF_MATRIX worldMatrix( true );   
  worldMatrix.Concatenate( _matrix, GetMatrix() );

  flash::SWF_CXFORMWITHALPHA worldCXform( true );   
  worldCXform.Concatenate( _cxform, GetColorTransform() );

  EFlashBlendMode::Enum worldBlendMode = ( _worldMode == EFlashBlendMode::NORMAL ) ? GetBlendMode()->GetValue() : _worldMode;

  flash::SWF_MATRIX maskMatrix( true );   

  if ( mask )
  {
     mask->GetWorldMatrix( maskMatrix );

     _renderer->BeginSubmitMask();
     mask->Render( _renderer, maskMatrix, worldCXform, EFlashBlendMode::NORMAL, true );
     _renderer->EndSubmitMask();
  }

  BeginFilters( _renderer );

  if ( g_DebugRender )
  {
    avmplus::AvmString name = get_name();
    avmplus::StUTF8String nameT( name );
    
    if ( g_DebugObjectName == nameT.c_str() )
      _renderer->DebugNextBatch();
  }

  DoRender( _renderer, worldMatrix, worldCXform, worldBlendMode );

  EndFilters( _renderer );

  if ( mask )
  {
    _renderer->BeginUnSubmitMask();
    mask->Render( _renderer, maskMatrix, worldCXform, EFlashBlendMode::NORMAL, true );
    _renderer->DisableMask();
  }
}

void DisplayObjectObject::BeginFilters( Render::IFlashRenderer* _renderer )
{
  flash::Movie* flashMovie = FlashCore()->GetMovie();

  bool nonBlocked = false;
  bool hasFilters = false;

  if ( flashMovie && flashMovie->IsBlocked() && !IsNonBlockedOverride() )
  {
    if ( !IsNonBlocked() )
    {
      _renderer->BeginColorMatrix( flashMovie->GetUIBlockColorMatrix(), flashMovie->GetUIBlockAddColor() );
      return;
    }
    else
    {
      _renderer->BeginColorMatrix( flashMovie->GetUINonBlockColorMatrix(), flashMovie->GetUIBlockAddColor() );
      nonBlocked = true;
    }
  }

  if ( !filters )
    return;

  uint32 numFilters = filters->getLength();

  for ( uint32 i = 0; i < numFilters; ++i )
  {
    BitmapFilterObject* filter = dynamic_cast<BitmapFilterObject*>( core()->atomToScriptObject( filters->getIntProperty( i ) ) );

    if ( filter )
    {
      filter->RealtimeBegin( _renderer );
      hasFilters = true;
    }
  }

  if ( nonBlocked && hasFilters )
    SetNonBlockedOverride( true );
}

void DisplayObjectObject::EndFilters( Render::IFlashRenderer* _renderer )
{
  flash::Movie* flashMovie = FlashCore()->GetMovie();

  if ( flashMovie && flashMovie->IsBlocked() && !IsNonBlockedOverride() )
  {
    if ( !IsNonBlocked() )
    {
      _renderer->EndColorMatrix();
      return;
    }
    else
    {
      _renderer->EndColorMatrix();
    }
  }

  if ( !filters )
    return;

  uint32 numFilters = filters->getLength();

  for ( uint32 i = 0; i < numFilters; ++i )
  {
    BitmapFilterObject* filter = dynamic_cast<BitmapFilterObject*>( core()->atomToScriptObject( filters->getIntProperty( i ) ) );

    if ( filter )
      filter->RealtimeEnd( _renderer );
  }
}

void DisplayObjectObject::DoRender( Render::IFlashRenderer* _renderer, const flash::SWF_MATRIX& _matrix, const flash::SWF_CXFORMWITHALPHA& _cxform, EFlashBlendMode::Enum _worldMode )
{

}

void DisplayObjectObject::GetWorldMatrix( flash::SWF_MATRIX& worldMatrix ) const
{
  DisplayObjectContainerObject* _parent = (DisplayObjectContainerObject*)parent->get();

  if ( _parent )
  {
    flash::SWF_MATRIX parentMatrix( true );
    _parent->GetWorldMatrix( parentMatrix );

    worldMatrix.Concatenate( parentMatrix, GetMatrix() );
  }
  else
  {
    worldMatrix = GetMatrix();
  }
}

void DisplayObjectObject::GetBounds( flash::SWF_RECT& _rect )
{
  _rect.X1 = _rect.X2 = 0;
  _rect.Y1 = _rect.Y2 = 0;
}

void DisplayObjectObject::GetWorldBounds( flash::SWF_RECT& _rect )
{
  GetBounds( _rect );
  
  flash::SWF_MATRIX worldMatrix( true );

  GetWorldMatrix( worldMatrix ); 
    
  worldMatrix.Transform( _rect );
}

void DisplayObjectObject::GetLocalBounds( flash::SWF_RECT& _rect )
{
  GetBounds( _rect );

  GetMatrix().Transform( _rect );
}

void DisplayObjectObject::LocalToGlobal( flash::SWF_POINT& _result, const flash::SWF_POINT& _point ) const
{
  flash::SWF_MATRIX worldMatrix( true );

  GetWorldMatrix( worldMatrix ); 

  worldMatrix.Transform( _result, _point );
}

void DisplayObjectObject::GlobalToLocal( flash::SWF_POINT& _result, const flash::SWF_POINT& _point ) const
{
  flash::SWF_MATRIX worldMatrix( true );
  flash::SWF_MATRIX invWorldMatrix( true );

  GetWorldMatrix( worldMatrix ); 

  invWorldMatrix.SetInverse( worldMatrix );
  invWorldMatrix.Transform( _result, _point );
}

bool DisplayObjectObject::HitTest( const flash::SWF_POINT & worldPoint )
{
  if ( !visible )
    return false;

  flash::SWF_RECT worldBounds;

  GetWorldBounds( worldBounds );

  return worldBounds.PointTest( worldPoint.X, worldPoint.Y );
}

DisplayObjectObject* DisplayObjectObject::GetTopMostObject( const flash::SWF_POINT & point )
{
  if ( !visible || usedAsMask || IsDragged() )
    return 0;

  if ( get_mask() )
  {
    if ( !get_mask()->HitTest( point ) )
      return 0;
  }

  if ( HitTest( point ) )
    return this;

  return 0;
}

bool DisplayObjectObject::IsAncestor( DisplayObjectObject* ancestor ) const
{
  DisplayObjectContainerObject * nextAncestor = (DisplayObjectContainerObject*)parent->get();

  while ( nextAncestor )
  {
    if ( nextAncestor == ancestor )
      return true;

    nextAncestor = (DisplayObjectContainerObject*)nextAncestor->parent->get();
  }

  return false;
}

void DisplayObjectObject::set_transform(TransformObject* value) 
{ 
  NI_VERIFY(value, "transform should not be null", return );
  transform = value; 
}

TransformObject* DisplayObjectObject::get_transform() 
{ 
  return transform; 
}

void DisplayObjectObject::set_scale9Grid( ScriptObject/*Rectangle*/ * innerRectangle ) 
{ 
  if ( !innerRectangle )
  {
    useScale9Grid = false;
    scale9Grid = 0; 
  }
  else
  {
    FlashCore()->ScriptObjectToRect( innerRectangle, scale9GridRect );
    useScale9Grid = true;
    scale9Grid = innerRectangle; 
  }
}

ScriptObject/*Rectangle*/ * DisplayObjectObject::get_scale9Grid() 
{ 
  if ( !useScale9Grid )
    return 0;

  if ( !scale9Grid )
  {
    Atom args[] = {0};
    avmplus::ClassClosure * classClosure = FlashCore()->GetClassInPool("Rectangle", PoolType::Geom);
    scale9Grid = FlashCore()->atomToScriptObject(classClosure->construct(0, args));
  }

  FlashCore()->RectToScriptObject( scale9Grid, scale9GridRect );

  return scale9Grid; 
}

void DisplayObjectObject::SetMatrix( flash::SWF_MATRIX& _matrix ) 
{
  NI_ASSERT( transform, "Transform is NULL" );
  transform->SetMatrix( _matrix );
}

flash::SWF_MATRIX& DisplayObjectObject::GetMatrix()
{ 
  NI_ASSERT( transform, "Transform is NULL" );
  return transform->GetMatrix();
}

const flash::SWF_MATRIX& DisplayObjectObject::GetMatrix() const
{
  NI_ASSERT( transform, "Transform is NULL" );
  return transform->GetMatrix();
}

void DisplayObjectObject::SetColorTransform( flash::SWF_CXFORMWITHALPHA& _matrix )
{
  NI_ASSERT( transform, "Transform is NULL" );
  transform->SetColorTransform( _matrix );
}

const flash::SWF_CXFORMWITHALPHA& DisplayObjectObject::GetColorTransform() const
{
  NI_ASSERT( transform, "Transform is NULL" );
  return transform->GetColorTransform();
}

flash::SWF_CXFORMWITHALPHA& DisplayObjectObject::GetColorTransform()
{
  NI_ASSERT( transform, "Transform is NULL" );
  return transform->GetColorTransform();
}

void DisplayObjectObject::DumpHierarchy( int _depth )
{
  StUTF8String nameT( get_name() );
  nstl::string nameTT;

  StUTF8String blendT( blendMode->GetStringValue() );
  nstl::string blendTT = blendT.c_str();

  for ( int i = 0; i < _depth; ++i ) nameTT += " ";
  
  nameTT += nstl::string( nameT.c_str() ) + nstl::string( GetDumpName() );

//  DebugTrace( "%s BM: %s D: %d CD: %d XS: %f", nameTT.c_str(), blendTT.c_str(), depth, clippingDepth, get_scaleX() );
}

const nstl::string DisplayObjectObject::GetNameDebug()
{
  StUTF8String nameT( get_name() );
  return nameT.c_str();
}

void DisplayObjectObject::SetScale9Grid( const flash::SWF_RECT& _scale9Grid )
{
  scale9GridRect = _scale9Grid;
  useScale9Grid = true;
}

void DisplayObjectObject::SetScale9GridFromParent( const CVec4& _constX, const CVec4& _constY, const CVec4& _trans ) 
{ 
  scale9ConstX = _constX; 
  scale9ConstY = _constY; 
  trans9Const = _trans;
}

bool DisplayObjectObject::HasAddToStageListener()
{
  return hasEventListener(FlashCore()->GetEventTypes().ADDED_TO_STAGE);
}

bool DisplayObjectObject::HasRemoveFromStageListener()
{
  return hasEventListener(FlashCore()->GetEventTypes().REMOVED_FROM_STAGE);
}

DisplayObjectObject* DisplayObjectObject::FindDisplayObjectByInstance( const char* _instanceName )
{
  if ( GetNameDebug() == _instanceName )
    return this;

  return 0;
}

}