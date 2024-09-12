#include "TamarinPCH.h"

#include "Render/FlashRendererInterface.h"

#include "DisplayObjectContainer.h"

#include "System/InlineProfiler.h"

namespace avmplus
{

DisplayObjectContainerObject::DisplayObjectContainerObject( DisplayObjectContainerClass * classType ) :
InteractiveObjectObject(classType),
mouseChildren(true),
tabChildren(true)
{}

DisplayObjectContainerObject::DisplayObjectContainerObject( VTable* ivtable, ScriptObject* prototype ) : 
InteractiveObjectObject(ivtable, prototype),
mouseChildren(true),
tabChildren(true)
{

}
bool DisplayObjectContainerObject::contains( DisplayObjectObject* child )
{
  for (DisplayObjects::iterator childIter = children.begin(); childIter!=children.end(); ++childIter)
  {
    if (child == (*childIter)->Get()->displayObject)
      return true;
  }

  return false;
}

DisplayObjectObject* DisplayObjectContainerObject::getChildByName( AvmString name )
{
  for (DisplayObjects::iterator child = children.begin(); child!=children.end(); ++child)
  {
    DisplayObjectObject * childObject = (*child)->Get()->displayObject;
    if (childObject->get_name() == name)
      return childObject;
  }
  AvmAssert(false);
  //throw exception if that child is not exist
  return 0;
}

DisplayObjectObject* DisplayObjectContainerObject::removeChildAt( int index )
{
  if (index>=children.size() || index<0)
  {
    return 0;
  }

  return removeChild(getChildAt(index));
}

int DisplayObjectContainerObject::getChildIndex( DisplayObjectObject* child )
{
  int index = 0;

  DisplayObjects::iterator childIter = children.begin();
  for (; childIter!=children.end(); ++childIter, index++)
  {
    if (child == (*childIter)->Get()->displayObject)
      break;
  }

  if (childIter == children.end()) 
  {
    AvmAssert(false);
    //TODO throw error here!
    return -1;
  }
  
  return index;
  
}

DisplayObjectObject* DisplayObjectContainerObject::addChild( DisplayObjectObject* child )
{
  return addChildAt(child, children.size());
}

DisplayObjectObject* DisplayObjectContainerObject::addChildAt( DisplayObjectObject* child, int index )
{
  //dont add it twice
  if (contains(child)) return child;

  //TODO its a common condition
  if (index>children.size() || index<0)
  {
    AvmAssert(false);
    //TODO throw exception here
    return 0;
  }

  DisplayObjectContainerObject * formerParent = child->get_parent();
  if (formerParent)
    formerParent->removeChild(child);
  
  Strong<DisplayObjectWrapper> objectWrapper = new DisplayObjectWrapper(new DisplayObjectGCRoot(core()->GetGC(), child));

  children.insert(GetIterAt(index), objectWrapper);

  {
    child->SetDepth(-1);
    child->SetClippingDepth(-1);
    child->SetParent(this);
    child->SetStageAndRoot(get_stage(), get_root(), get_stage()&&willTrigger(FlashCore()->GetEventTypes().ADDED_TO_STAGE));
  }
  

  return child;
}

DisplayObjectObject* DisplayObjectContainerObject::removeChild( DisplayObjectObject* child )
{
  DisplayObjects::iterator childIter = children.begin();

  for (; childIter!=children.end(); ++childIter)
  {
    if (child == (*childIter)->Get()->displayObject)
      break;
  }

  if (childIter!=children.end())
    children.erase(childIter);

  //reset parent, stage and root properties
  child->SetParent(0);
  child->SetStageAndRoot(0, 0, false);

  return child;
}

void DisplayObjectContainerObject::setChildIndex( DisplayObjectObject* child, int index )
{
  if (index<0)
  {
    AvmAssert(false);
    //TODO throw exceptions here.
    return;
  }

  DisplayObjects::iterator childIter = GetChildIter(child);

  if (childIter==children.end())
  {
    AvmAssert(false);
    //TODO throw exceptions here.
    return;
  }

  Strong<DisplayObjectWrapper> childWrapper = *childIter;

  children.erase(childIter);
  children.insert(GetIterAt(index), childWrapper);
}

DisplayObjectObject* DisplayObjectContainerObject::getChildAt( int index )
{
  //TODO move this condition to method or function
  if (index>=children.size() || index<0)
  {
    AvmAssert(false);
    //TODO throw exceptions here.
    return 0;
  }
 
  DisplayObjects::iterator childIter = children.begin();

  for (int i = 0; childIter!=children.end(); ++childIter, i++)
  {
    if (i==index) 
       return (*childIter)->Get()->displayObject;
  }

  NI_ALWAYS_ASSERT("wtf!?");
  return 0;
}

void DisplayObjectContainerObject::swapChildrenAt( int index1, int index2 )
{
  SwapChildrenInternal(GetIterAt( index1), GetIterAt(index2));
}

void DisplayObjectContainerObject::swapChildren( DisplayObjectObject* child1, DisplayObjectObject* child2 )
{
  //TODO throw argument exception
  SwapChildrenInternal(GetChildIter(child1), GetChildIter(child2));
}

void DisplayObjectContainerObject::SwapChildrenInternal( DisplayObjects::iterator child1, DisplayObjects::iterator child2 )
{
  if (child1 == children.end() || child2 == children.end())
  {
    //not in list
    AvmAssert(false);
    return;
  }
  Strong<DisplayObjectWrapper> child1Wraper = (*child1);
  Strong<DisplayObjectWrapper> child2Wraper = (*child2);
  (*child1) = child2Wraper;
  (*child2) = child1Wraper;
}

void DisplayObjectContainerObject::SetStageAndRoot( StageObject * newStage , DisplayObjectObject* newRoot, bool parentHasListener  )
{
  //set root and stage to this object
  DisplayObjectObject::SetStageAndRoot(newStage, newRoot, parentHasListener);

  bool removedFromStage = get_stage() && !newStage;

  bool hasStageListener = removedFromStage ? HasRemoveFromStageListener() : HasAddToStageListener() && newStage;
  //notify all children here
  for ( DisplayObjects::iterator child = children.begin(); child != children.end(); ++child)
  {
    (*child)->Get()->displayObject->SetStageAndRoot(newStage,  newRoot, hasStageListener || parentHasListener);
  }
}

DisplayObjectContainerObject::DisplayObjects::iterator DisplayObjectContainerObject::GetIterAt( int index )
{
  DisplayObjects::iterator insertIter = children.begin();

  if (index == 0)
    return insertIter;

  if (index == children.size())
    return children.end();

  for (int i = 0; insertIter!=children.end(); ++insertIter, i++)
  {
    if (i==index) 
      return insertIter;
  }

  NI_ALWAYS_ASSERT("wtf out of index");

  return children.end();
}

DisplayObjectContainerObject::DisplayObjects::iterator DisplayObjectContainerObject::GetChildIter( DisplayObjectObject * child )
{
  for (DisplayObjects::iterator childIter = children.begin(); childIter!=children.end(); ++childIter)
  {
    if ( child == (*childIter)->Get()->displayObject )
      return childIter;
  }

  NI_ALWAYS_ASSERT("wtf wrong child");

  return children.end();
}

bool DisplayObjectContainerObject::PrepareScale9GridConsts( CVec4& scale9ConstX, CVec4& scale9ConstY, CVec4& trans9Const, const flash::SWF_MATRIX& _matrix )
{
  if ( fabs( get_rotation() ) > FLT_EPSILON ) // disable scale9Grid on rotation;
    return false;

  flash::SWF_RECT bounds;
  GetBounds( bounds );

  float scaleX = _matrix.GetXScale();
  float scaleY = _matrix.GetYScale();
  float outterPartX = bounds.GetWidth() - scale9GridRect.GetWidth();
  float outterPartY = bounds.GetHeight() - scale9GridRect.GetHeight();
  float AX = ( scaleX * bounds.GetWidth() - outterPartX ) / scale9GridRect.GetWidth();
  float AY = ( scaleY * bounds.GetHeight() - outterPartY ) / scale9GridRect.GetHeight();
  float BX = bounds.GetWidth() * ( scaleX - 1.f );
  float BY = bounds.GetHeight() * ( scaleY - 1.f );

  scale9ConstX = CVec4( scale9GridRect.X1, scale9GridRect.X2, AX, BX );
  scale9ConstY = CVec4( scale9GridRect.Y1, scale9GridRect.Y2, AY, BY );

  trans9Const.x = _matrix.m_[0][0]; //ScaleX;
  trans9Const.y = _matrix.m_[1][1]; //SacleY;
  trans9Const.z = _matrix.m_[0][2]; //TranslateX;
  trans9Const.w = _matrix.m_[1][2]; //TranslateY;

  return true;
}

void DisplayObjectContainerObject::DoRender( Render::IFlashRenderer* _renderer, const flash::SWF_MATRIX& _matrix, const flash::SWF_CXFORMWITHALPHA& _cxform, EFlashBlendMode::Enum _worldMode )
{
  NI_PROFILE_HEAVY_FUNCTION

  int currentDepth = -1;
  int clipedDepth = -1;

  bool applyScale9Grid = false;
  CVec4 scale9ConstX, sclae9ConstY, trans9Const;

  if ( useScale9Grid )
    applyScale9Grid = PrepareScale9GridConsts( scale9ConstX, sclae9ConstY, trans9Const, _matrix );

  DisplayObjectObject* maskObject = 0;

  for ( DisplayObjects::iterator childIter = children.begin(); childIter != children.end(); ++childIter)
  {
    DisplayObjectObject* object = (*childIter)->Get()->displayObject;

    if ( object->UsedAsMask() )
      continue;

    if ( object )
    {
      if ( object->GetDepth() >= 0 )
        currentDepth = object->GetDepth();

      if ( clipedDepth != -1 && currentDepth > clipedDepth )
      {
        clipedDepth = -1;
        NI_ASSERT( maskObject, "Mask object should not be null" );
        
        if ( maskObject )
        {
          _renderer->BeginUnSubmitMask();
          maskObject->Render( _renderer, _matrix, _cxform, _worldMode, false );
          maskObject = 0;
        }

        _renderer->DisableMask();
      }

      if ( object->GetClippingDepth() > currentDepth )
      {
        maskObject = object;
        _renderer->BeginSubmitMask();
      }

      object->SetUseScale9GridFromParent( applyScale9Grid );

      if ( applyScale9Grid )
        object->SetScale9GridFromParent( scale9ConstX, sclae9ConstY, trans9Const );

      object->Render( _renderer, _matrix, _cxform, _worldMode, false );

      if ( object->GetClippingDepth() > currentDepth )
      {
        _renderer->EndSubmitMask();
        clipedDepth = object->GetClippingDepth();
      }
    }
  }

  if ( clipedDepth != -1 )
  {
    NI_ASSERT( maskObject, "Mask object should not be null" );

    if ( maskObject )
    {
      _renderer->BeginUnSubmitMask();
      maskObject->Render( _renderer, _matrix, _cxform, _worldMode, false );
      maskObject = 0;
    }

    _renderer->DisableMask();
  }
}

void DisplayObjectContainerObject::GetBounds( flash::SWF_RECT& _rect )
{
  if ( children.size() <= 0 )
    return;

  DisplayObjects::const_iterator childIter = children.begin();
  DisplayObjectObject* object = (*childIter)->Get()->displayObject;

  if ( object )
  {
    object->GetBounds( _rect );
    object->GetMatrix().Transform( _rect );
  }

  ++childIter;

  for ( ; childIter != children.end(); ++childIter)
  {
    object = (*childIter)->Get()->displayObject;
    if ( object )
    {
      flash::SWF_RECT childRect;

      object->GetBounds( childRect );
      object->GetMatrix().Transform( childRect );

      _rect.ExpandToRect( childRect );
    }
  }
}

DisplayObjectObject* DisplayObjectContainerObject::GetTopMostObject( const flash::SWF_POINT & point )
{
  if ( !get_visible() || usedAsMask )
    return 0;

  if ( get_mask() )
  {
    if ( !get_mask()->HitTest( point ) )
      return 0;
  }

  //object is transparent for mouse
  if ( !mouseChildren && !get_mouseEnabled())
    return 0;

  int currentDepth = -1;
  int clipedDepth = -1;
  bool clipedByMask = false;

  DisplayObjectObject* topMostInteractive = 0;
  DisplayObjectObject* topMostNonInteractive = 0;

  for ( DisplayObjects::iterator childIter = children.begin(); childIter != children.end(); ++childIter)
  {
    DisplayObjectObject* object = (*childIter)->Get()->displayObject;

    if ( object )
    {
      if ( object->GetDepth() >= 0 )
        currentDepth = object->GetDepth();

      if ( clipedDepth != -1 && currentDepth > clipedDepth )
      {
        clipedDepth = -1;
        clipedByMask = false;
      }

      if ( object->GetClippingDepth() > currentDepth )
      {
        clipedDepth = object->GetClippingDepth();
        DisplayObjectObject* maskTopMost = object->GetTopMostObject( point );
        clipedByMask  = ( maskTopMost == 0 );
        continue;
      }

      if ( !clipedByMask )
      {
        DisplayObjectObject* newTopMost = object->GetTopMostObject( point );

        if ( newTopMost )
        {
          if ( newTopMost->IsInteractive() )
            topMostInteractive = newTopMost;
          else
            topMostNonInteractive = newTopMost;
        }
      }
    }
  }

  if ( topMostInteractive )
  {
    if ( mouseChildren )
      return topMostInteractive;
    else
      return IsDragged() ? 0 : this;
  }

  if ( topMostNonInteractive && get_mouseEnabled() && !IsDragged() )
    return this;

  return 0;
}


void DisplayObjectContainerObject::SetNonBlocked( bool _isNonBlocked )
{
  DisplayObjectObject::SetNonBlocked( _isNonBlocked );

  for ( DisplayObjects::iterator childIter = children.begin(); childIter != children.end(); ++childIter)
  {
    DisplayObjectObject* object = (*childIter)->Get()->displayObject;

    if ( object )
      object->SetNonBlocked( _isNonBlocked );
  }
}

void DisplayObjectContainerObject::SetNonBlockedOverride( bool _isNonBlocked )
{
  DisplayObjectObject::SetNonBlockedOverride( _isNonBlocked );

  for ( DisplayObjects::iterator childIter = children.begin(); childIter != children.end(); ++childIter)
  {
    DisplayObjectObject* object = (*childIter)->Get()->displayObject;

    if ( object )
      object->SetNonBlockedOverride( _isNonBlocked );
  }
}

DisplayObjectObject* DisplayObjectContainerObject::FindDisplayObjectByInstance( const char* _instanceName )
{
  if ( GetNameDebug() == _instanceName )
    return this;

  for ( DisplayObjects::iterator childIter = children.begin(); childIter != children.end(); ++childIter)
  {
    DisplayObjectObject* object = (*childIter)->Get()->displayObject;

    if ( object )
    {
      DisplayObjectObject* foundObject = object->FindDisplayObjectByInstance( _instanceName );

      if ( foundObject )
        return foundObject;
    }
  }

  return 0;
}


void DisplayObjectContainerObject::OnMovedSized()
{
  for ( DisplayObjects::iterator childIter = children.begin(); childIter != children.end(); ++childIter)
  {
    DisplayObjectObject* object = (*childIter)->Get()->displayObject;

    if ( object )
    {
      object->OnMovedSized();
    }
  }
}

bool DisplayObjectContainerObject::get_mouseChildren() 
{ 
  return mouseChildren;
}

void DisplayObjectContainerObject::set_mouseChildren(bool enable) 
{ 
  mouseChildren = enable;
}

void DisplayObjectContainerObject::DumpHierarchy( int _depth )
{
  InteractiveObjectObject::DumpHierarchy( _depth );

  for ( DisplayObjects::iterator childIter = children.begin(); childIter != children.end(); ++childIter)
  {
    DisplayObjectObject* object = (*childIter)->Get()->displayObject;
    object->DumpHierarchy( _depth + 1 );
  }
}

void DisplayObjectContainerObject::ClearSWFObjects()
{
  NI_PROFILE_FUNCTION

  DisplayObjects::iterator it = children.begin();

  for ( ; it != children.end();  )
  {
    DisplayObjectObject* object = (*it)->Get()->displayObject;

    if ( object->GetDepth() >= 0 && object->GetCreationFrame() != 1 )
    {
      object->SetParent(0);
      object->SetStageAndRoot(0, 0, false);

      it = children.erase( it );
    }
    else
      ++it;
  }
}

DisplayObjectObject* DisplayObjectContainerObject::GetDisplayObjectAtDepth( int Depth )
{
  DisplayObjects::iterator it = children.begin();
  DisplayObjects::iterator last = children.end();

  for ( ; it != last; ++it )
  {
    DisplayObjectObject* object = (*it)->Get()->displayObject;

    if ( object->GetDepth() == Depth )
      return object;
  }

  return 0;
}

void DisplayObjectContainerObject::SetDisplayObjectAtDepth( int Depth, DisplayObjectObject* _displayObject )
{
  NI_PROFILE_FUNCTION

  DisplayObjects::iterator it = children.begin();
  
  for ( ; it != children.end(); ++it )
  {
    DisplayObjectObject* object = (*it)->Get()->displayObject;

    if ( object->GetDepth() == Depth )
    {
      if ( object == _displayObject )
        return;

      object->SetParent(0);
      object->SetStageAndRoot(0, 0, false);

      if ( _displayObject )
      {
        (*it)->Get()->displayObject = _displayObject;
        _displayObject->SetDepth( Depth );

        _displayObject->SetParent(this);
        _displayObject->SetStageAndRoot(get_stage(), get_root(), get_stage()&&willTrigger(FlashCore()->GetEventTypes().ADDED_TO_STAGE));
      }
      else
      {
        children.erase( it );
      }

      return;
    }

    if ( object->GetDepth() > Depth )
      break;
  }

  Strong<DisplayObjectWrapper> objectWrapper = new DisplayObjectWrapper(new DisplayObjectGCRoot(core()->GetGC(), _displayObject));
  children.insert( it, objectWrapper );

  _displayObject->SetParent(this);
  _displayObject->SetStageAndRoot(get_stage(), get_root(), get_stage()&&willTrigger(FlashCore()->GetEventTypes().ADDED_TO_STAGE));
}


}