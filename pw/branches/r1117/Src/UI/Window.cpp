#include "stdafx.h"

#include "Window.h"
#include "SkinStyles.h"
#include "Resolution.h"
#include "User.h"
#include "Render/UIRenderer.h"
#include "Sound/EventScene.h"
#include "LuaEventResult.h"
#include "Scripts/Script.h"
#include "Scripts/lua.hpp" //Only for 'GetIndexFromString'
#include "Scripts/LuaConstants.h"
#include "System/InlineProfiler.h"



namespace EventNames
{
  const static string Init              = "OnInit";
  const static string Enable            = "OnEnable";
  const static string Show              = "OnShow"; 
  const static string KeyboardFocus     = "OnKeyboardFocus"; 
  const static string MouseOver         = "OnMouseOver";
  const static string MouseMove         = "OnMouseMove";
  const static string MouseDown         = "OnMouseDown";
  const static string MouseUp           = "OnMouseUp";
  const static string DoubleClick       = "OnDoubleClick";
  const static string DragDrop          = "OnDragDrop";
  const static string Tooltip           = "OnTooltip";
  const static string Char              = "OnChar";
  const static string ScreenFocus       = "OnScreenFocus";
  const static string Action            = "OnAction";

  const static string StartDrag         = "OnStartDrag";
  const static string DropTest          = "OnDropTest";
  const static string DropTarget        = "OnDropTarget";
  const static string DragMove          = "OnDragMove";
  const static string Drop              = "OnDrop";
  const static string CancelDrag        = "OnCancelDrag";

  const static string Invalid           = "";
} // namespace



namespace UI
{

DECLARE_NULL_RENDER_FLAG

BEGIN_LUA_TYPEINFO_NOBASE(Window)
  LUA_METHOD( Enable )
  LUA_METHOD_EX( "IsThisEnabled", IsEnabled )
  LUA_METHOD_EX( "IsEnabled", IsFullyEnabled )
  LUA_METHOD( Show )
  LUA_METHOD( PlayActivationSound )
  LUA_METHOD_EX( "IsThisVisible", IsVisible )
  LUA_METHOD_EX( "IsVisible", IsFullyVisible )
  LUA_METHOD( SetTransparent )
  LUA_METHOD( SetCropping )
  LUA_METHOD( SetState )
  LUA_METHOD( SetLocation )
  LUA_METHOD( SetSize )
  LUA_METHOD( SetOpacity )
  LUA_METHOD( GetParent )
  LUA_METHOD( GetBaseParent )
  LUA_METHOD( CreateChild )
  LUA_METHOD( RemoveChild )
  LUA_METHOD_EX( "GetChild", GetChildByName )
  LUA_METHOD( FindChild )
  LUA_METHOD( Close )
  LUA_METHOD( SetSortOrder )
  LUA_METHOD( ForceUpdate )
  LUA_METHOD( SetCursor )
  LUA_METHOD( SetFocus )
  LUA_METHOD( IsFocused )
  LUA_METHOD( SetBind )
  LUA_METHOD( SetRepeatBind )
  LUA_METHOD( SetScriptTimeTrigger )
  LUA_METHOD( SetMsgHandler )
  LUA_METHOD( SendMsg )
  LUA_METHOD( SendMsgAll )
  LUA_METHOD( PostCommand )
  LUA_METHOD( PostCommandWide )
  LUA_METHOD( GetConsoleVariable )
  LUA_METHOD( GetRelatedText )
  LUA_METHOD( GetContext )
  LUA_METHOD( RedirectNameMap )

  LUA_READONLY_PROPERTY_EX( base, GetBase )
  LUA_READONLY_PROPERTY( name )
  LUA_READONLY_PROPERTY( x )
  LUA_READONLY_PROPERTY( y )
  LUA_READONLY_PROPERTY( w )
  LUA_READONLY_PROPERTY( h )
  LUA_READONLY_PROPERTY( sx )
  LUA_READONLY_PROPERTY( sy )
  LUA_READONLY_PROPERTY( sw )
  LUA_READONLY_PROPERTY( sh )
  LUA_READONLY_PROPERTY( state )
  LUA_READONLY_PROPERTY_EX( context, GetContext )
  LUA_READONLY_PROPERTY_EX( parent, GetParent )
END_LUA_TYPEINFO( Window )


LUA_EXPORT_CONSTANT2( "WINDOW_HALIGN_LEFT",         NDb::UIELEMENTHALIGN_LEFT );
LUA_EXPORT_CONSTANT2( "WINDOW_HALIGN_RIGHT",        NDb::UIELEMENTHALIGN_RIGHT );
LUA_EXPORT_CONSTANT2( "WINDOW_HALIGN_CENTER",       NDb::UIELEMENTHALIGN_CENTER );
LUA_EXPORT_CONSTANT2( "WINDOW_HALIGN_FIXEDMARGINS", NDb::UIELEMENTHALIGN_FIXEDMARGINS );
LUA_EXPORT_CONSTANT2( "WINDOW_HALIGN_PROPORTIONAL", NDb::UIELEMENTHALIGN_PROPORTIONAL );

LUA_EXPORT_CONSTANT2( "WINDOW_VALIGN_TOP",          NDb::UIELEMENTVALIGN_TOP );
LUA_EXPORT_CONSTANT2( "WINDOW_VALIGN_BOTTOM",       NDb::UIELEMENTVALIGN_BOTTOM );
LUA_EXPORT_CONSTANT2( "WINDOW_VALIGN_CENTER",       NDb::UIELEMENTVALIGN_CENTER );
LUA_EXPORT_CONSTANT2( "WINDOW_VALIGN_FIXEDMARGINS", NDb::UIELEMENTVALIGN_FIXEDMARGINS );
LUA_EXPORT_CONSTANT2( "WINDOW_VALIGN_PROPORTIONAL", NDb::UIELEMENTVALIGN_PROPORTIONAL );

LUA_EXPORT_CONSTANT2( "WINDOW_LMBUTTON",            EMButton::Left );
LUA_EXPORT_CONSTANT2( "WINDOW_RMBUTTON",            EMButton::Right );


static NDebug::PerformanceDebugVar ui_ScriptTime( "UIScriptTime", "MainPerf", 10, 10, true );



Window::Window()
  : toRemove( false )
  , visibilityOverride( EVisibilityOverride::Nope )
  , mode3d(E3DWindowMode::Nope)
  , depthBias(0)
  , transform(CVec3(0, 0, 0))
  , worldPosition(CVec3(0, 0, 0))
  , win3DScale(1.0f, 1.0f)
  , opacity( 255 )
  , resultOpacity( 255 )
  , parent(0)
  , needOrderReSort( false )
  , sortOrder( 0 )
  , refreshNeeded( false )
  , winRect(0, 0, 0, 0)
  , cropRect(0, 0, 0, 0)
  , childrenShift(0, 0)
  , bindResult( false )
  , timeTriggerActive( false )
  , timeTriggerTimeLeft( 0 )
{
}



Window *Window::GetBase()
{
  Window *p = this;
  while ( p )
  {
    if ( p->GetLayoutClone<NDb::UIBaseLayout>( false ) )
      return p;
    p = p->parent;
  }
  return 0;
}


Window * Window::GetBaseParent()
{
  Window * p = this;
  while( true )
  {
    if( !p->parent )
      return p;
    p = p->parent;
  }
}


bool Window::IsVisible() const
{
  if ( layout == 0 || toRemove )
    return false;

  if ( visibilityOverride != EVisibilityOverride::Nope )
    return visibilityOverride == EVisibilityOverride::ForceVisible;

  return layout->visible && resultOpacity > 0;
}



bool Window::IsFullyVisible() const
{
  for( const Window * p = this; p; p = p->parent ? p->parent : 0 )
    if( !p->IsVisible() )
      return false;
  return true;
}



bool Window::IsFullyEnabled() const
{
  for( const Window * p = this; p; p = p->parent ? p->parent : 0 )
    if( !p->IsEnabled() )
      return false;
  return true;
}



void Window::Enable( bool _enable )
{
  if ( toRemove )
    return;

  if ( layout->enabled == _enable )
    return;

  layout->enabled = _enable;
  OnEnable( _enable );

  if( IsSubclassed() )
    CallHandler( EventNames::Enable.c_str(), _enable );
}



void Window::Show( bool _show )
{
  if ( toRemove )
    return;

  if ( layout->visible == _show )
    return;

  layout->visible = _show;
  OnShow( _show );

  if( IsSubclassed() )
    CallHandler( EventNames::Show.c_str(), _show );

	if ( _show )
		NSoundScene::EventStart( layout->soundShow );
	else
		NSoundScene::EventStart( layout->soundHide );
}

void Window::ShowSilence( bool _show )
{
	if ( toRemove )
		return;

	if ( layout->visible == _show )
		return;

	layout->visible = _show;
	OnShow( _show );

	if( IsSubclassed() )
		CallHandler( EventNames::Show.c_str(), _show );
}


void Window::PlayActivationSound()
{
  NSoundScene::EventStart( layout->soundActivate );
}



void Window::SetState( const char * stateId )
{
  NI_PROFILE_FUNCTION;

  Point oldPos = layout->location;

  layout.SetState( stateId );
  currentState = stateId;

  layout->location = oldPos;

#ifndef _SHIPPING
  debugWindowName = layout->name;
#endif //_SHIPPING

  RecreateChildren();

  OnDataChanged();
}


const string& Window::GetState()
{
  return currentState;
}


void Window::ProcessWindowCoords( LinearCoord & resultOffs, LinearCoord & resultSize, NDb::EUIElementHAlign align, //Ну, тут все ясно
  ERecalcRectsReason reason, //Указывает, что имеет приоритет - size или offset
  LinearCoord prevOffs, LinearCoord newOffs, LinearCoord prevSize, LinearCoord newSize, //Координаты элемента, старые и новые
  LinearCoord prevParentSize, LinearCoord newParentSize ) //Размеры родителя, старые и новые
{
  NI_ASSERT( 
    NDb::UIELEMENTHALIGN_LEFT          == NDb::UIELEMENTVALIGN_TOP &&
    NDb::UIELEMENTHALIGN_RIGHT         == NDb::UIELEMENTVALIGN_BOTTOM &&
    NDb::UIELEMENTHALIGN_CENTER        == NDb::UIELEMENTVALIGN_CENTER &&
    NDb::UIELEMENTHALIGN_FIXEDMARGINS  == NDb::UIELEMENTVALIGN_FIXEDMARGINS &&
    NDb::UIELEMENTHALIGN_PROPORTIONAL  == NDb::UIELEMENTVALIGN_PROPORTIONAL, "" );

  switch ( align )
  {
  default:
    NI_ALWAYS_ASSERT( "Invalid align!" );
    //No 'break' needed !

  case NDb::UIELEMENTHALIGN_LEFT:
    {
      resultOffs = newOffs;
      resultSize = newSize;
      break;
    }

  case NDb::UIELEMENTHALIGN_RIGHT:
    {
      const LinearCoord prevRight = prevParentSize - (prevOffs + prevSize);
      if ( reason == eRecalcBySize || reason == eRecalcByParent )
      {
        resultOffs = newParentSize - prevRight - newSize;
        resultSize = newSize;
      }
      else
      {
        resultOffs = newOffs;
        resultSize = newParentSize - prevRight - newOffs;
      }
      break;
    }

  case NDb::UIELEMENTHALIGN_CENTER:
    {
      //we use float - we donnowanna loose (0.5 + 0.5 + 0.5) = 1.5 pixels
      const float offsFromCenter = (float)( prevOffs + prevSize / 2.f - prevParentSize / 2.f );

      LinearCoord newSizeCorrected = newSize;
      if ( reason != eRecalcBySize )
        newSizeCorrected = (LinearCoord)( 2.f * ( prevOffs + prevSize / 2.f - newOffs ) );

      resultOffs = (LinearCoord)( newParentSize / 2.f + offsFromCenter - newSizeCorrected / 2.f );
      resultSize = newSizeCorrected;
      break;
    }

  case NDb::UIELEMENTHALIGN_FIXEDMARGINS:
    {
      if ( reason == eRecalcByPos || reason == eRecalcByParent )
      { // Сохраняем правый край, а если  (newOffs == prevOffs), то и левый
        const LinearCoord prevRight = prevParentSize - (prevOffs + prevSize);
        resultOffs = newOffs;
        resultSize = newParentSize - newOffs - prevRight;
      }
      else if( reason == eRecalcBySize )
      { // Сохраняем левый край, действуем подобно ALIGN_LEFT
        resultOffs = prevOffs; //FIXME: use 'newOffs'?
        resultSize = newSize;
      }
      else
        NI_ALWAYS_ASSERT( "" );
      break;
    }

  case NDb::UIELEMENTHALIGN_PROPORTIONAL:
    {
      //FXIME: Если сначала уменьшить парента до 3 пикселей, а потом растянуть до 1000, то мы получим высокую дискретность координат!
      //Часть информации потеряется при масштабировании парента до 3 пикселей
      NI_ASSERT( prevParentSize > 0, "Proportional alignment with zero-sized parent" );
      const float kLeft = (float)prevOffs / (float)prevParentSize;
      const float kRight = (float)( prevOffs + prevSize ) / (float)prevParentSize;
      if ( reason == eRecalcByParent )
      {
        resultOffs = (LinearCoord)( newParentSize * kLeft + .5f );
        resultSize = (LinearCoord)( newParentSize * (kRight - kLeft) + .5f );
      }
      else if ( reason == eRecalcByPos )
      { //Сохраняем пропорции правого края
        resultOffs = newOffs;
        resultSize = (LinearCoord)( newParentSize * kRight + .5f ) - resultOffs;
      }
      else if( reason == eRecalcBySize )
      {
        resultOffs = (LinearCoord)( newParentSize * kLeft + .5f );
        resultSize = newSize;
      }
      break;
    }
  }

  if( resultSize < 0)
    resultSize = 0;
}


bool Window::ChangeOffsetAndSize( ERecalcRectsReason reason, const Point & newOffs, const Point & newSize, const Point & prevParentSize, const Point & newParentSize )
{
  const NDb::EUIElementHAlign hAlign = layout->hAlign, vAlign = (NDb::EUIElementHAlign)layout->vAlign;

  Point resultOffs, resultSize;

  switch ( layout->keepAspectRatio )
  {
  default:
  case NDb::UIELEMENTASPECTRATIO_DONTCARE:
    ProcessWindowCoords( resultOffs.x, resultSize.x, hAlign, reason, layout->location.x, newOffs.x, layout->size.x, newSize.x, prevParentSize.x, newParentSize.x );
    ProcessWindowCoords( resultOffs.y, resultSize.y, vAlign, reason, layout->location.y, newOffs.y, layout->size.y, newSize.y, prevParentSize.y, newParentSize.y );
    break;

  case NDb::UIELEMENTASPECTRATIO_WIDTHBASED:
    {
      //Сначала считаем ширину, потом вычисляем высоту и затем - выравнивание
      ProcessWindowCoords( resultOffs.x, resultSize.x, hAlign, reason, layout->location.x, newOffs.x, layout->size.x, newSize.x, prevParentSize.x, newParentSize.x );
      if(!RENDER_DISABLED)
        NI_VERIFY( resultSize.x, "Zero fixed aspect window width", break );
      LinearCoord fixedSize = (LinearCoord)( .5f + (float)layout->size.y * (float)resultSize.x / (float)layout->size.x );
      ProcessWindowCoords( resultOffs.y, resultSize.y, vAlign, reason, layout->location.y, newOffs.y, layout->size.y, fixedSize, prevParentSize.y, newParentSize.y );
      break;
    }

  case NDb::UIELEMENTASPECTRATIO_HEIGHTBASED:
    {
      //Аналогично ширине
      ProcessWindowCoords( resultOffs.y, resultSize.y, vAlign, reason, layout->location.y, newOffs.y, layout->size.y, newSize.y, prevParentSize.y, newParentSize.y );
      NI_VERIFY( resultSize.y, "Zero fixed aspect window height", break );
      LinearCoord fixedSize = (LinearCoord)( .5f + (float)layout->size.x * (float)resultSize.y / (float)layout->size.y );
      ProcessWindowCoords( resultOffs.x, resultSize.x, hAlign, reason, layout->location.x, newOffs.x, layout->size.x, fixedSize, prevParentSize.x, newParentSize.x );
      break;
    }
  }

  bool changed = (resultOffs != layout->location) || (resultSize != layout->size);
  layout->location = resultOffs;
  layout->size = resultSize;

  return changed;
}



void Window::RecalcRects( ERecalcRectsReason reason, const Point & newOffs, const Point & newSize, const Point & prevParentSize, const Point & newParentSize, const Rect & newParentWinRect, const Rect & parentCropRect, const Point & additionalOffs, bool forceNotify )
{
  const Point prevOffs = layout->location, prevSize = layout->size;
  const Rect prevWinRect = winRect, prevCropRect = cropRect;

  bool offsOrSizeChanged = ChangeOffsetAndSize( reason, newOffs, newSize, prevParentSize, newParentSize );

  winRect.x1 = additionalOffs.x + newParentWinRect.x1 + layout->location.x;
  winRect.y1 = additionalOffs.y + newParentWinRect.y1 + layout->location.y;
  winRect.x2 = winRect.x1 + layout->size.x;
  winRect.y2 = winRect.y1 + layout->size.y;

  cropRect = parentCropRect;
  if ( layout->needCrop )
    cropRect.Intersect( newParentWinRect );

  offsOrSizeChanged |= ( prevWinRect != winRect );
  offsOrSizeChanged |= ( prevCropRect != cropRect );

  if( offsOrSizeChanged || forceNotify )
  {
    OnMovedSized();
    if ( parent )
      parent->OnMovedSizedChild( this );
  }
  else
    if( reason != eRecalcByChildrenShift )
      return;

  Invalidate();

  for ( int i = 0; i < childs.size(); ++i )
    if ( childs[i] && !childs[i]->toRemove )
    {
      Window * child = childs[i];
      child->RecalcRects( eRecalcByParent, child->layout->location, child->layout->size, prevSize, layout->size, winRect, cropRect, childrenShift, forceNotify );
    }
}


void Window::RecalcThisWindowRects( ERecalcRectsReason reason, const Point & newOffs, const Point & newSize, bool forceNotify )
{
  Point parentOffs, parentSize, parentShift;
  Rect parentWin, parentCrop;

  if( parent )
  {
    parentOffs = parent->layout->location;
    parentSize = parent->layout->size;
    parentShift = parent->childrenShift;
    parentWin = parent->winRect;
    parentCrop = parent->cropRect;
  }
  else
  {
    parentOffs.Set( 0, 0 );
    parentSize = layout->size;
    parentShift.Set( 0, 0 );
    parentWin.Set( 0, 0, newSize.x, newSize.y );
    parentCrop = parentWin;
  }

  RecalcRects( reason, newOffs, newSize, parentSize, parentSize, parentWin, parentCrop, parentShift, forceNotify );
}



Point Window::ScreenToLocal( const Point& screenPos )
{
  Point localPos(screenPos);
  Window *p = this;
  while ( p )
  {
    localPos -= p->GetPos();
    p = p->parent;
  }
  return localPos;
}



Point Window::LocalToScreen( const Point& localPos )
{
  Point screenPos(localPos);
  Window *p = this;
  while ( p )
  {
    screenPos += p->GetPos();
    p = p->parent;
  }
  return screenPos;
}



void Window::SetChildrenShift( LinearCoord dx, LinearCoord dy )
{
  if ( dx == childrenShift.x && dy == childrenShift.y )
    return;

  childrenShift.x = dx;
  childrenShift.y = dy;

  RecalcThisWindowRects( eRecalcByChildrenShift );
}


void Window::SetWorldPosition(const SHMatrix & position, const CVec2 & worldSize, const CVec2 & align, float _depthBias, E3DWindowMode::Enum mode)
{
  NI_VERIFY(mode != E3DWindowMode::Nope, "Invalid 3D window mode", return);

  Window * parent = GetParent();
  NI_VERIFY( parent && !parent->GetParent(), "3D windows can only be made of root's children", return);

  mode3d = mode;
  worldPosition = position.GetTranslation();
  depthBias = _depthBias;

  transformRotated.Set(CVec3(0, 0, 0));

  if(mode3d == E3DWindowMode::DepthOnly)
  {
    win3DScale.Set(1.0f, 1.0f);
    transform = position;
    return;
  }

  //Проверим аспект
  CVec2 normWorldSize = worldSize;
  if(winRect.Width() && winRect.Height())
  {
    if(!normWorldSize.x)
      normWorldSize.x = normWorldSize.y * (float)winRect.Width() / (float)winRect.Height();
    else if(!normWorldSize.y)
      normWorldSize.y = normWorldSize.x * (float)winRect.Height() / (float)winRect.Width();
  }

  //Дополнительно трансформируем координаты для:
  // 1. УИ живет в плоскости OXY, а нам нужна плоскость OXZ
  // 2. Отскалим контрол под заданный размер normWorldSize
  // 3. Выравняем контрол в соответствии с align
  CVec2 parentSz(parent->winRect.Width(), parent->winRect.Height());
  //Координаты в эту матрицу приходят в диапазоне от -1.0 до 1.0 по x и по y
  //Пэтому размер квадрата составляет (2.0 х 2.0)

  float winScaleX = parentSz.x / winRect.Width();
  float winScaleY = parentSz.y / winRect.Height();
  float scalex = .5f * normWorldSize.x * winScaleX;
  float scalez = .5f * normWorldSize.y * winScaleY;

  float offsx = 2.f * scalex * (.5f - winRect.left / parentSz.x - align.x / winScaleX);
  float offsz = 2.f * scalez * (.5f - (parentSz.y - winRect.bottom) / parentSz.y - (1.f - align.y) / winScaleY);

  SHMatrix fix(
    scalex,                   0,                      0,              offsx,
    0,                        0,                      -1.0f,          0,
    0,                        scalez,                 0,              offsz,
    0,                        0,                      0,              1.0f);
  Multiply( &transform, ( mode == E3DWindowMode::World ) ? position : SHMatrix(position.GetTranslation()), fix );

  win3DScale.Set( parentSz.x, parentSz.y );
}


void Window::Stop3D()
{
  mode3d = E3DWindowMode::Nope;
  transform.Set(CVec3(0, 0, 0));
  win3DScale.Set(1.0f, 1.0f);
  depthBias = 0.0f;
}


bool Window::ConvertCoordinates( Point * coords )
{
  //For 3D-children elemets we'll get ray and cast it
  if(!Is3D())
    return false;

  if( mode3d == E3DWindowMode::DepthOnly )
    return true;

  CVec3 org, dir;
  Render::GetUIRenderer()->GetRay( &org, &dir, coords->x, coords->y );

  SHMatrix inv; //get it offline
  Invert(&inv, transformRotated);
  CVec3 locOrg, locDir;
  inv.RotateHVector(&locOrg, org);
  inv.RotateVector(&locDir, dir);

  float t = -locOrg.z / locDir.z;
  CVec3 p = locOrg + locDir * t;

  CVec2 check(0.5f * (p.x + 1.0f) * win3DScale.x, 0.5f * (1.0f - p.y) * win3DScale.y);

  coords->x = (LinearCoord)(0.5f + check.x);
  coords->y = (LinearCoord)(0.5f + check.y);
  return true;
}


void Window::SetLocation( LinearCoord x, LinearCoord y )
{
  if( x == -1 )
    x = GetPos().x;
  if( y == -1 )
    y = GetPos().y;

  RecalcThisWindowRects( eRecalcByPos, Point( x, y ), layout->size, false );
}


void Window::SetSize( LinearCoord width, LinearCoord height, bool forceNotify )
{
  if( width == -1 )
    width = GetSize().x;
  if( height == -1 )
    height = GetSize().y;

  RecalcThisWindowRects( eRecalcBySize, layout->location, Point( width, height ), forceNotify );
}



void Window::UpdateOpacity()
{
  int tmpOpacity = Clamp( (opacity * (parent ? parent->resultOpacity : 255)) / 255, 0, 255 );
  if ( tmpOpacity == resultOpacity )
    return;
  resultOpacity = tmpOpacity;
  for ( int i = 0; i < childs.size(); ++i )
    if ( childs[i] )
      childs[i]->UpdateOpacity();

  Invalidate();
}


void Window::SetOpacity( float _opacity )
{
  opacity = Clamp( (int)(_opacity * 255), 0, 255 );
  UpdateOpacity();
}


const NDb::UILayout * Window::GetRelatedLayout( const char * relatedLayout )
{
  if ( toRemove )
    return 0;
  if ( !layout )
    return 0;
  if ( !strcmp( relatedLayout, "self" ) )
    return layout;
  for ( int i = 0; i < layout->relatedLayouts.size(); ++i )
  {
    if ( layout->relatedLayouts[i].id == relatedLayout )
      return layout->relatedLayouts[i].layout;
  }
  return 0;
}


void Window::AddChild( Window *child )
{
  if ( !child || child->toRemove )
    return;

  childs.push_back( child );
  child->parent = this;
  child->toRemove = false;

  OnAddChild( child );

  child->RecalcThisWindowRects( eRecalcByParent );

  Invalidate();
}


Window * Window::CreateChild( const char * name, const char * relatedLayout, LinearCoord x, LinearCoord y, LinearCoord w, LinearCoord h, int hAlign, int vAlign )
{
  const NDb::UILayout * pLayout = GetRelatedLayout( relatedLayout );
  if ( !pLayout )
    return 0;

  // check name (if not empty)
  if ( !strlen( name ) )
    for ( int i = 0; i < childs.size(); ++i )
      if ( childs[i] )
        if ( !childs[i]->toRemove && childs[i]->GetWindowName() == name )
          return 0;

  // create child
  NDb::ClonedPtr<NDb::UILayout> newLayout;
  newLayout.Clone( pLayout );

  newLayout->name = name;

  newLayout->location.x = x;
  newLayout->location.y = y;
  newLayout->size.x = w > 0 ? w : pLayout->size.x;
  newLayout->size.y = h > 0 ? h : pLayout->size.y;
  newLayout->hAlign = (NDb::EUIElementHAlign)hAlign;
  newLayout->vAlign = (NDb::EUIElementVAlign)vAlign;

  Window * p = CreateUIWindowImpl( newLayout, context );

  if ( !p )
    return 0;

  AddChild( p );
  p->PostInit();

  return p;
}


Window *Window::GetChild( const char * name )
{
  for ( int i = ((int)childs.size())-1; i >= 0; --i )
  {
    Window *child = childs[i];
    if ( !child )
      continue;
    if ( child->GetWindowName() == name )
      return child;
  }

  return 0;
}


Window *Window::GetChildByMask( const char * name )
{
  for ( int i = ((int)childs.size())-1; i >= 0; --i )
  {
    Window *child = childs[i];
    if ( !child )
      continue;
    if ( child->GetWindowName().find(name) != string::npos )
      return child;
  }

  return 0;
}


Window * Window::FindChild( const char * name )
{
  if ( GetWindowName().compare(name) == 0 )
      return this;

  for ( int i = 0; i < childs.size(); ++i )
  {
    if ( !childs[i] )
      continue;
    if( childs[i]->toRemove )
      continue;
    Window * wnd = childs[i]->FindChild( name );
    if( wnd )
      return wnd;
  }

  return 0;
}


Window *Window::Traverse( IWindowJob * job )
{
  EWindowJobCode::Enum before = job->BeforeChildren( this );
  switch( before )
  {
  case EWindowJobCode::Ok:          break;
  case EWindowJobCode::ReturnThis:  return this;
  default:
  case EWindowJobCode::ReturnNull:  return 0;
  }

  Window * bestChild = NULL;
  float bestDepth = 0;

  //Если мышка попадает в 3D-окно, мы вынуждены перебрать все 3D-окна, что бы найти ближайшее к камере
  //Если все окна - 2D, то берем первое попавшееся
  //Причем 2D окна имеют приоритет над 3D

  for ( int i = ( (int)childs.size() - 1 ); i >= 0; --i )
  {
    Window * child = childs[i];

    if ( !child )
      continue;

    Window * p = child->Traverse( job );

    if ( p )
    {
      if(child->Is3D())
      {
        float depth = Render::GetUIRenderer()->CalcDepth( child->worldPosition );

        if ( !bestChild || depth < bestDepth )
        {
          bestChild = p;
          bestDepth = depth;
        }
      }
      else //Если нашлось простое 2D-окно, возвращаем его сразу
      {
        bestChild = p;
        break;
      }
    }
  }

  if(bestChild)
    return bestChild;

  EWindowJobCode::Enum after = job->AfterChildren( this );
  switch( after )
  {
  case EWindowJobCode::Ok:
  case EWindowJobCode::ReturnThis:
    return this;
  default:
  case EWindowJobCode::ReturnNull:
    return 0;
  }
}



bool Window::RemoveChild( const char * name )
{
  if ( !strlen( name ) )
    return false;

  for ( TChildsArray::iterator it = childs.begin(); it != childs.end(); ++it )
    if ( !(*it)->toRemove && (*it)->GetWindowName() == name )
      return (*it)->RemoveSelf();

  return false;
}



bool Window::RemoveSelf()
{
  if ( !parent ) // can't remove root
    return false;

  if ( toRemove )
    return false;

  toRemove = true;
  for ( TChildsArray::iterator it = childs.begin(); it != childs.end(); ++it )
    (*it)->RemoveSelf();

  return true;
}


bool Window::Close()
{
  return RemoveSelf();
}


void Window::SetSortOrder( float order )
{
  if ( !parent ) // can't change root's priority
    return;
  sortOrder = order;
  parent->needOrderReSort = true;
}


void Window::StepInternal( float deltaTime )
{
  NI_PROFILE_HEAVY_FUNCTION;

  if( !toRemove )
  {
    if( layout.IsModified() )
    {
      /* this may cause crash when Undo-ing a sublayout addition in editor
      ////DEBUG////
      DebugTrace( "Window %s \"%s\" data changed, reinitin. Immediate children:", layout.GetSourcePtr()->GetDBID().GetId().c_str(), layout->name.c_str() );

      for( TChildsArray::iterator it = childs.begin(); it != childs.end(); ++it )
      {
        DebugTrace( "Child %s \"%s\"",  (*it)->layout.GetSourcePtr()->GetDBID().GetId().c_str(), (*it)->layout->name.c_str() );
      }
      /////////////*/

      OnDataChanged();
    }

    Step( deltaTime );

    if( refreshNeeded )
    {
      refreshNeeded = false;
      OnRefresh( deltaTime );
    }

    CheckTimeTrigger( deltaTime );
  }

  for ( int i = 0; i < childs.size(); ++i )
  {
    Window * child = childs[i];

    NI_ASSERT( child, "" );

    child->StepInternal( deltaTime );

    if( child->toRemove )
    {
      OnRemoveChild( child );
      child->parent = 0;
      child->toRemove = false;
      child = 0;

      //@iA@TODO: делать erase со сдвигом вектора при удалении каждого чилда дороговато.
      //решение:
      //1. занулять удаляемые элементы, потом удалять их скопом. будут проблемы,
      //   когда во вовремя итерирования /виртуальной/ функции степ Step() кто-то начнет работать с чилдами.
      //2. использовать list<> со всеми вытекающими
      childs.erase( childs.begin() + i );
      i = i - 1; // same index item again
    }
  }

  SortPriority();
}


void Window::CheckTimeTrigger( float deltaTime )
{
  if( !timeTriggerActive )
    return;

  timeTriggerTimeLeft -= deltaTime;

  if( timeTriggerTimeLeft > 0 )
    return;

  timeTriggerActive = false;
  timeTriggerTimeLeft = 0;

  if( timeTriggerScriptFunction.empty() )
    OnTimeTrigger();
  else
    EventTime( timeTriggerScriptFunction );

  //we DO NOT clear any event information here, it might be set in event handler
}


void Window::SortPriority()
{
  // priority moving sort
  if ( !needOrderReSort )
    return;

  NI_PROFILE_FUNCTION; //HACK: do not profile disabled sort

  needOrderReSort = false;

  for ( int i = 0; i < childs.size(); ++i )
  {
    for ( int j = i + 1; j < childs.size(); ++j )
    {
      if ( childs[i]->sortOrder > childs[j]->sortOrder )
        swap( childs[i], childs[j] );
    }
  }
}


void Window::OnDataChanged()
{
  Invalidate();

  RecalcThisWindowRects( eRecalcByParent ); //@iA@TODO: завести еще один тип eRecalcByData??

  if ( layout )
    tooltipText = layout->tooltipText.GetText();

  //HACK{: if this is executed in the game (not in editor) it can have side effects (disappearance of dynamically created children
  if ( childs.size() != layout->subLayouts.size() )
    RecreateChildren();
  //HACK}
}


void Window::RecreateChildren()
{
  NI_PROFILE_FUNCTION;

  for ( TChildsArray::iterator it = childs.begin(); it != childs.end(); ++it )
    (*it)->RemoveSelf();

  LoadChildrenImpl();
}


void Window::RenderInternal( Window * specialWindow, ESpecialMode::Enum mode )
{
  ESpecialMode::Enum childrenSpecMode = mode;

  //UGLY: This tamtam dance is done mainly to draw drag'n'drop windows in correct order without moving them in hierarchy
  switch ( mode )
  {
    case ESpecialMode::None:
    default:
      Render();
      break;

    case ESpecialMode::Exclude:
      if( this == specialWindow )
        return;
      Render();
      break;

    case ESpecialMode::DrawOnlySpecial:
      if( this == specialWindow )
      {
        childrenSpecMode = ESpecialMode::None;
        Render();
      }
      break;
  }

  //Only children of base root window can be 3D
  bool isBase = !parent;

  for ( TChildsArray::iterator it = childs.begin(); it != childs.end(); ++it )
  {
    Window * wnd = *it;
    if ( !wnd->IsVisible() )
      continue;

    if( isBase && wnd->Is3D() )
    {
      Render::ETransformMode::Enum m = Render::ETransformMode::World;
      switch ( (*it)->mode3d )
      {
        case E3DWindowMode::World:          m = Render::ETransformMode::World; break;
        case E3DWindowMode::Billboard:      m = Render::ETransformMode::Billboard; break;
        case E3DWindowMode::AxisBillboard:  m = Render::ETransformMode::AxisBillboard; break;
        case E3DWindowMode::DepthOnly:      m = Render::ETransformMode::DepthOnly; break;
      }

      if ( m == Render::ETransformMode::World || m == Render::ETransformMode::DepthOnly )
        wnd->transformRotated = wnd->transform;
      else
        Render::GetUIRenderer()->GetBillboardMatrix( &wnd->transformRotated, wnd->transform, m, wnd->worldPosition, wnd->depthBias );

      Render::GetUIRenderer()->SetWorldMatrix( wnd->transformRotated, m, wnd->worldPosition, wnd->depthBias );
    }

    wnd->RenderInternal( specialWindow, childrenSpecMode );

    if ( isBase && wnd->Is3D() )
      Render::GetUIRenderer()->ResetWorldMatrix();
  }
}


void Window::RefreshAll( float deltaTime )
{
  OnRefresh( deltaTime );
  for ( TChildsArray::iterator it = childs.begin(); it != childs.end(); ++it )
    if ( !(*it)->toRemove )
      (*it)->RefreshAll( deltaTime );
}


//This is mainly for UI Editor?..
void Window::RefreshExternally()
{
  StepInternal( 0.f );
  RefreshAll( 0.f );
}



void Window::InvalidateAll()
{
  Invalidate();

  for ( TChildsArray::iterator it = childs.begin(); it != childs.end(); ++it )
    if ( !(*it)->toRemove )
      (*it)->InvalidateAll();
}



void Window::SetTimeTrigger( float duration )
{
  timeTriggerActive = true;
  timeTriggerTimeLeft = duration;
  timeTriggerScriptFunction.clear();
}


void Window::SetScriptTimeTrigger( float duration, const char * scriptFunction )
{
  timeTriggerActive = true;
  timeTriggerTimeLeft = duration;
  timeTriggerScriptFunction = scriptFunction;
}


wstring Window::GetRelatedText( const char * id )
{
  if ( !strlen( id ) )
    return wstring();
  if ( !layout )
    return wstring();
  for ( int i = 0; i < layout->relatedTexts.size(); ++i )
  {
    if ( layout->relatedTexts[i].id == id )
      return layout->relatedTexts[i].relatedText.GetText();
  }
  return wstring();
}


void Window::SetTooltipTextW( const wstring & text )
{
  tooltipText = text;
}


bool Window::GetCursor( string * name, const Point & screenCoords ) const
{
  if( layout->cursorTransparent )
    return false;

  return GetCustomCursor( name, screenCoords );
}


bool Window::GetCustomCursor( string * name, const Point & screenCoords ) const
{
  if ( !IsFullyEnabled() )
  {
    if (layout->cursors.disabled.empty())
      return false;
    *name = layout->cursors.disabled;
    return true;
  }

  if ( !cursorOverride.empty() )
  {
    *name = cursorOverride;
    return true;
  }

  if (layout->cursors.normal.empty())
    return false;
  *name = layout->cursors.normal;

  return true;
}



void Window::SetBind( const char * bind, const char * scriptFunction )
{
  context->SetBind( bind, this, scriptFunction, 0,0 );
}



void Window::SetRepeatBind( const char * bind, const char * scriptFunction, int repeatStartDelay, int repeatDelay )
{
  if ( repeatStartDelay < 1 )
    repeatStartDelay = 1;
  if ( repeatDelay < 1 )
    repeatDelay = 1;

  context->SetBind( bind, this, scriptFunction, (DWORD)repeatStartDelay, (DWORD)repeatDelay );
}



bool Window::IsFocused() const
{
  return context->HasKeyboardFocus( this );
}



void Window::SetFocus( bool focus )
{
  if( focus )
    context->SetKeyboardFocus( this );
  else
    if( context->HasKeyboardFocus( this ) )
      context->SetKeyboardFocus( 0 );
}



void Window::OnMouseOver( bool over, const Point & mouse )
{
}



bool Window::OnMouseDown( EMButton::Enum mbutton, const Point & point )
{ 
  if( IsDraggable() && mbutton == EMButton::Right )
  {
    GetContext()->StartDrag( this, "auto", -1, -1 );
  }

  return ( mbutton == EMButton::Left ) ? layout->defaultEventsCatch.leftMouseDown : layout->defaultEventsCatch.rightMouseDown;
}



bool Window::OnMouseUp( EMButton::Enum mbutton )
{
  if( IsDraggable() && mbutton == EMButton::Right )
    GetContext()->Drop( false );

  return ( mbutton == EMButton::Left ) ? layout->defaultEventsCatch.leftMouseUp : layout->defaultEventsCatch.rightMouseUp;
}



bool Window::OnDoubleClick( EMButton::Enum mbutton, const Point & point )
{
  return ( mbutton == EMButton::Left ) ? layout->defaultEventsCatch.leftDoubleClick : layout->defaultEventsCatch.rightDoubleClick;
}



bool Window::IsInsideWindow( const Point & point ) const
{
  if ( !IsVisible() )
    return false;

  Rect rect = winRect;
  rect.Intersect( cropRect );

  if ( !rect.IsInside( point.x, point.y ) )
    return false;

  const int local_x = point.x - winRect.x1;
  const int local_y = point.y - winRect.y1;

  return TestOpaque( local_x, local_y );
}


void Window::OnInit() 
{
  if ( layout )
    tooltipText = layout->tooltipText.GetText();
}



void Window::OnInitAfterChildrenCreated() 
{
}



bool Window::OnMouseMove( const Point & mouse )
{
  return layout->defaultEventsCatch.mouseMove;
}



void Window::EventMouseOver( bool over, const Point & mouse )
{
  OnMouseOver( over, mouse );

  Point localPos( mouse.x - winRect.x1, mouse.y - winRect.y1 );
  CallHandler( EventNames::MouseOver.c_str(), over, localPos.x, localPos.y );
}



bool Window::EventMouseMove( const Point & mouse )
{
  bool processed = OnMouseMove( mouse );

  Point localPos( mouse.x - winRect.x1, mouse.y - winRect.y1 );
  EEventResult::Enum result = EEventResult::Unhandled;
  if( CallMethod( EventNames::MouseMove.c_str(), result, localPos.x, localPos.y ) )
    processed = processed || ( result == EEventResult::Processed );

  if ( layout->transparent )
    processed = false;

  return processed;
}



bool Window::EventMouseDown( EMButton::Enum mbutton, const Point & point )
{
  if ( !IsFullyEnabled() )
    return !layout->transparent;

  bool processed = OnMouseDown( mbutton, point );

  Point localPos( point.x - winRect.x1, point.y - winRect.y1 );
  EEventResult::Enum result = EEventResult::Unhandled;
  if( CallMethod( EventNames::MouseDown.c_str(), result, (int)mbutton, localPos.x, localPos.y ) )
    processed = processed || ( result == EEventResult::Processed );

  if ( layout->transparent )
    processed = false;

  return processed;
}



bool Window::EventMouseUp( EMButton::Enum mbutton )
{
  if ( !IsFullyEnabled() )
    return !layout->transparent;

  bool processed = OnMouseUp( mbutton );

  EEventResult::Enum result = EEventResult::Unhandled;
  if( CallMethod( EventNames::MouseUp.c_str(), result, (int)mbutton ) )
    processed = processed || ( result == EEventResult::Processed );

  if ( layout->transparent )
    processed = false;

  return processed;
}



bool Window::EventDoubleClick( EMButton::Enum mbutton, const Point & point )
{
  if ( !IsFullyEnabled() )
    return !layout->transparent;

  bool processed = OnDoubleClick( mbutton, point );

  Point localPos( point.x - winRect.x1, point.y - winRect.y1 );
  EEventResult::Enum result = EEventResult::Unhandled;
  if( CallMethod( EventNames::DoubleClick.c_str(), result, (int)mbutton, localPos.x, localPos.y ) )
    processed = processed || ( result == EEventResult::Processed );

  if ( layout->transparent )
    processed = false;

  return processed;
}



bool Window::EventKeyboardFocus( bool gotFocus )
{
  DebugTrace( gotFocus ? "Window %s got focus" : "Window %s losing focus", GetWindowName().c_str() );

  bool processed = OnKeyboardFocus( gotFocus );

  EEventResult::Enum result = EEventResult::Unhandled;
  if ( CallMethod( EventNames::KeyboardFocus.c_str(), result, gotFocus ) )
    processed = processed || ( result == EEventResult::Processed );

  return processed;
}



bool Window::EventChar( int ch )
{
  if ( !IsFullyEnabled() )
    return false;

  bool processed = OnChar( ch );

  EEventResult::Enum result = EEventResult::Unhandled;
  if ( CallMethod( EventNames::Char.c_str(), result, ch ) )
    processed = processed || ( result == EEventResult::Processed );

  return processed;
}



bool Window::EventKeyPressed( int code, bool down )
{
  if ( !IsFullyEnabled() )
    return false;

  return OnKeyPressed( code, down );
}



bool Window::EventScroll( int delta )
{
  if ( !IsFullyEnabled() )
    return false;

  return OnScroll( delta );
}



bool Window::EventBind( const string & bind, const string & scriptFunction, float fDelta )
{
  if ( !IsFullyEnabled() )
    return false;

  bindResult = false;
  if ( OnBind( bind, fDelta, &bindResult ) )
    return bindResult;

  bindResult = true;

  if( CallHandler( scriptFunction.c_str(), fDelta ) )
    return false;

  return bindResult;
}



//TODO: refactor it
bool Window::EventActivationBind( const string & commandName )
{
  if ( !IsFullyEnabled() )
    return false;

  if ( !IsFullyVisible() )
    return false;

  if ( OnActivationBind( commandName ) )
    return true;

  for ( TChildsArray::iterator it = childs.begin(); it != childs.end(); ++it )
    if ( !(*it)->toRemove )
      if ( (*it)->EventActivationBind( commandName ) )
        return true;

  return false;
}



void Window::EventTime( const string & scriptFunction )
{
  OnTimeTrigger();

  if( CallHandler( scriptFunction.c_str() ) )
    return;
}



void Window::EventTooltip( const Point & coords )
{
  EEventResult::Enum result = EEventResult::Unhandled;
  if( CallMethod( EventNames::Tooltip.c_str(), result, coords.x, coords.y ) )
    if ( result == EEventResult::Processed )
      return;

  UI::STooltipDesc desc;
  desc.mousePos = coords;
  desc.targetWindow = this;
  desc.enabled = IsFullyEnabled();

  context->CreateTextTooltip( tooltipText, desc );
}



void Window::EventScreenFocus( bool focus )
{
  OnScreenFocus(focus);

  CallHandler( EventNames::ScreenFocus.c_str(), focus );
}



void Window::EventAction( EMButton::Enum mbutton )
{
  OnAction(mbutton);

  CallHandler( EventNames::Action.c_str(), (int)mbutton );
}


bool Window::EventStartDrag( const char * id )
{
  bool processed = OnStartDrag( id );

  EEventResult::Enum result = EEventResult::Unhandled;
  if( CallMethod( EventNames::StartDrag.c_str(), result, id ) )
    if ( result != EEventResult::Unhandled )
      processed = ( result == EEventResult::Processed );

  return processed;
}


bool Window::EventDropTest( const char * id, Window * dragTarget )
{
  bool processed = OnDropTest( id, dragTarget );

  EEventResult::Enum result = EEventResult::Unhandled;
  if( CallMethod( EventNames::DropTest.c_str(), result, id, dragTarget ) )
    if ( result != EEventResult::Unhandled )
      processed = ( result == EEventResult::Processed );

  return processed;
}



bool Window::EventDropTarget( const char * id, bool entering, Window * dropTarget )
{
  bool processed = OnDropTarget( id, entering, dropTarget );

  EEventResult::Enum result = EEventResult::Unhandled;
  if( CallMethod( EventNames::DropTarget.c_str(), result, id, entering, dropTarget ) )
    if ( result != EEventResult::Unhandled )
      processed = ( result == EEventResult::Processed );

  return processed;
}



void Window::EventDragMove( const char * id )
{
  OnDragMove( id );
  
  CallHandler( EventNames::DragMove.c_str(), id );
}



void Window::EventDrop( const char * id, Window * target )
{
  OnDrop( id, target );

  CallHandler( EventNames::Drop.c_str(), id, target );
}



void Window::EventCancelDrag( const char * id )
{
  OnCancelDrag( id );

  CallHandler( EventNames::CancelDrag.c_str(), id );
}



bool Window::IsDraggable() const
{
  return layout && layout->draggable;
}



bool Window::ProcessMsgInt( Window * wndFrom, const UIMessage & msg, Window *exclude, bool forAll )
{
  if ( IsFullyEnabled() )
  {
    TCPPMsgHandlers::iterator cppIt = msgCPPHandlers.find( msg.msg );
    if ( cppIt != msgCPPHandlers.end() && cppIt->second != 0 )
    {
      TCPPMessageHandler& fn = cppIt->second;
      (this->*fn)(dynamic_cast<Window*>(wndFrom),msg);
    }

    TScriptMsgHandlers::const_iterator it = msgScriptHandlers.find( msg.msg );
    if ( it != msgScriptHandlers.end() )
    {
      EventMsg( msg.msg, msg.s, msg.n );

      const string & scriptFunction = it->second;
      if ( !scriptFunction.empty() )
      {
        if( IsSubclassed() )
          CallHandler( scriptFunction.c_str(), msg.s.c_str(), msg.n );
      }

      if ( !forAll )
        return true; // processed, even with no Lua call (because subscripted)
    }
  }

  if ( !childs.empty() )
  {
    TChildsArray::iterator it = childs.end();
    while ( it != childs.begin() )
    {
      --it;
      if ( (*it)->toRemove || (*it) == exclude )
        continue;
      if ( (*it)->ProcessMsgInt( wndFrom, msg, 0, forAll ) )
        return forAll;
    }
  }

  return false;
}



bool Window::SendMsgInt( Window * wndFrom, const UIMessage & msg, Window *exclude, bool forAll )
{
  if ( toRemove )
    return false;
  if ( ProcessMsgInt( wndFrom, msg, exclude, forAll ) && !forAll )
    return true;
  if ( parent )
    return parent->SendMsgInt( wndFrom, msg, this, forAll );
  return false;
}



void Window::SendMsg( Window * wndFrom, const char * msg, const char * s, float n )
{
  SendMsgInt( wndFrom, UIMessage( msg, s, n ), 0, false );
}



void Window::SendMsgAll( Window * wndFrom, const char * msg, const char * s, float n )
{
  SendMsgInt( wndFrom, UIMessage( msg, s, n ), 0, true );
}



void Window::SetMsgHandlerInt( const char * msg, const char * scriptFunction )
{
  if ( !strlen( msg ) )
    return;

  msgScriptHandlers[ msg ] = scriptFunction;
}



void Window::SetMsgHandler( const char * msg, const char * scriptFunction )
{
  if ( !strlen( scriptFunction ) )
  {
    TScriptMsgHandlers::iterator it = msgScriptHandlers.find( msg );
    if ( it != msgScriptHandlers.end() )
      msgScriptHandlers.erase( it );
  }
  else
  {
    SetMsgHandlerInt( msg, scriptFunction );
  }
}



void Window::SetCPPMsgHandler( const char * msg, TCPPMessageHandler handlerFunction )
{
  if ( !handlerFunction )
  {
    TCPPMsgHandlers::iterator it = msgCPPHandlers.find( msg );
    if ( it != msgCPPHandlers.end() )
      msgCPPHandlers.erase( it );
  }
  else if( strlen( msg ) )
  {
    msgCPPHandlers[ msg ] = handlerFunction;
  }
}



void Window::PostCommand( const string & cmd )
{
  NGlobal::RunCommand( NStr::ToUnicode( cmd ) );
}



void Window::PostCommandWide( const wstring & cmd )
{
  NGlobal::RunCommand( cmd );
}



string Window::GetConsoleVariable( const char * name )
{
  const NGlobal::VariantValue & var = NGlobal::GetVar( name );
  return NStr::ToMBCS( var.GetString() );
}



bool Window::FireCustomUserMessage( const string & msg )
{
  if( !msg.empty() && GetBase() )
  {
    GetBase()->SendMsg( this, msg.c_str() );
  }

  return true;
}


float Window::CallLuaSortCompareFunction( const char * scriptFunction, const char * s1, const char * s2 )
{
  if ( !strlen( scriptFunction ) )
    return 0.0f;

  float result = 0.0f;
  if( CallMethod( scriptFunction, result, s1, s2 ) )
    return result;

  return 0.0f;
}


void Window::LoadLayout( const NDb::ClonedPtr< NDb::UILayout > &newLayout )
{
  NI_PROFILE_FUNCTION

  layout = newLayout;

#ifndef _SHIPPING
  debugWindowName = layout->name;
#endif //_SHIPPING

  //@iA@TODO: правильнее было бы сделать RecalcThisWindowRects _после_ создания чилдов, один раз и для всех
  //сейчас эта функция вызывается для каждого чилда отдельно
  RecalcThisWindowRects( eRecalcByParent );

  const NDb::UIBaseLayout * scriptedLayout = dynamic_cast<const NDb::UIBaseLayout *>( layout.GetPtr() );
  if ( scriptedLayout )
    AddScriptFile( scriptedLayout->scriptFile );

  {
    NI_PROFILE_BLOCK( "OnInit" );
    OnInit();
  }

  LoadChildrenImpl();

  OnInitAfterChildrenCreated();

  if( !layout->subclass.empty() )
    Subclass( GetUIScript()->GetState(), layout->subclass, this );
}



void Window::LoadChildrenImpl()
{
  for ( int i = 0; i < layout->subLayouts.size(); ++i )
  {
    if ( !layout->subLayouts[i] )
      continue;

    NDb::ClonedPtr<NDb::UILayout> childLayout;
    childLayout.Clone( layout->subLayouts[i] );

    Window * childWnd = CreateUIWindowImpl( childLayout, context );
    AddChild( childWnd );
  }
}



void Window::PostInit()
{
  if( IsSubclassed() )
    CallHandler( EventNames::Init.c_str() );

  for ( TChildsArray::iterator it = childs.begin(); it != childs.end(); ++it )
    if ( !(*it)->toRemove )
      (*it)->PostInit();
}



typedef hash_map< string, TWindowConstructor * > TWindowsFactory;

TWindowsFactory * GetWindowsFactory()
{
  static TWindowsFactory LayoutHandlers;
  return &LayoutHandlers;
}



void RegisterControlConstructor( const string & typeName, TWindowConstructor * pConstructor )
{
  (*GetWindowsFactory())[ typeName ] = pConstructor;
}


REGISTER_CONTROLTYPE( NDb::UILayout, Window );


Window * Window::CreateUIWindowImpl( const NDb::ClonedPtr<NDb::UILayout> &newLayout, ScreenLogicBase * context )
{
  PushDXPoolGuard dxPool("UI");

  string typeName = newLayout->GetObjectTypeName();

  TWindowsFactory::const_iterator it = (*GetWindowsFactory()).find( typeName );

  Window * newWindow = ( it == (*GetWindowsFactory()).end() ) ? ( new Window ) : (it->second)();

  newWindow->SetContext( context );
  newWindow->LoadLayout( newLayout );

  return newWindow;
}



Window * CreateUIWindow( const NDb::UILayout * newDbLayout, const char * stateName, ScreenLogicBase * context, Window * parent, const char * nameOverride, bool doPostInit )
{
  NI_PROFILE_FUNCTION_MEM

  NDb::ClonedPtr<NDb::UILayout> newLayout;
  newLayout.Clone( newDbLayout );

  if( nameOverride )
    newLayout->name = nameOverride;

  Window * newWnd = Window::CreateUIWindowImpl( newLayout, context );

  if( newWnd && parent )
    parent->AddChild( newWnd );

  if ( doPostInit )
    newWnd->PostInit();

  if ( stateName )
    newWnd->currentState = stateName;

  return newWnd;
}


static bool UIScriptsMachineCmd( const char *name, const vector<wstring>& params )
{
  if ( strcmp(name, "clear_ui_scripts_cache" ) == 0 )
  {
    GetUIScript()->ClearCache();
    systemLog( NLogg::LEVEL_MESSAGE ) << " clear cached ui scripts..." << endl;
  }
  return true;
}



int GetIndexFromString( const char * s )
{
  if ( !s )
    return -1;

  const int ln = strlen(s);
  if ( ln <= 0 )
    return -1;
  int lastNotDigit = ln-1;
  while ( lastNotDigit >= 0 )
  {
    if ( !isdigit(s[lastNotDigit]) )
      break;
    --lastNotDigit;
  }
  if ( ln - lastNotDigit <= 0 )
    return -1;
  return atoi( s + lastNotDigit + 1 );
}


int GetIndexFromString( lua_State * L )
{
  int luaTop = lua_gettop(L);
  NI_VERIFY( luaTop == 1, "GetIndexFromString() takes at 1 parameter", return 0 );

  if( lua_type( L, 1 ) != LUA_TSTRING ) //FIXME: Здесь лучше поставить NI_VERIFY
    return -1;

  const char * s = lua_tostring( L, 1 );
  NI_ASSERT(s, "");

  int idx = GetIndexFromString( s );
  lua_pushnumber( L, idx );
  return 1;
}
REGISTER_LUA_SFUNCTION_IMMEDIATE( (*UI::GetUIScript()), GetIndexFromString );


} // namespace UI


NI_DEFINE_REFCOUNT( UI::Window );


bool ProcessGC( const char *name, const vector<wstring> &params )
{
  lua_gc( *UI::GetUIScript(), LUA_GCCOLLECT, 0 );
  return true;
}


REGISTER_CMD( uilua_gc, ProcessGC )
REGISTER_DEV_CMD( clear_ui_scripts_cache, UI::UIScriptsMachineCmd );
