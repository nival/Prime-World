#pragma once
#include "System/SystemLog.h"
#include "../PlayerGlobalIncludes.h"
#include "InteractiveObject.h"

namespace avmplus
{
class DisplayObjectObject;
class TextSnapshotObject;
class ArrayObject;
class ScriptObject;

class DisplayObjectContainerObject: public InteractiveObjectObject
{
  typedef nstl::list<Strong<DisplayObjectWrapper>> DisplayObjects;

  //TODO may be another container would be more optimal
  DisplayObjects children;
  bool mouseChildren;
  bool tabChildren;

public:
  DisplayObjectContainerObject(DisplayObjectContainerClass * classType);
  DisplayObjectContainerObject(VTable* ivtable, ScriptObject* prototype);

  ~DisplayObjectContainerObject(void) {}


  // AS3 methods

  bool contains(DisplayObjectObject* child);

  DisplayObjectObject* getChildByName(AvmString name);

  int getChildIndex(DisplayObjectObject* child);

  int get_numChildren() { return children.size();}

  DisplayObjectObject* addChild(DisplayObjectObject* child);
  DisplayObjectObject* addChildAt(DisplayObjectObject* child, int index);
   
  void ClearSWFObjects(); // remove DisplayObjects loaded from SWF
  DisplayObjectObject* GetDisplayObjectAtDepth( int Depth );
  void SetDisplayObjectAtDepth( int Depth, DisplayObjectObject* _displayObject );

  DisplayObjectObject* removeChild(DisplayObjectObject* child);
  DisplayObjectObject* removeChildAt(int index);

  void setChildIndex(DisplayObjectObject* child, int index);
  DisplayObjectObject* getChildAt(int index);

  void swapChildren(DisplayObjectObject* child1, DisplayObjectObject* child2);
  void swapChildrenAt(int index1, int index2);

  //TODO implement this property in EventDispatcher
  bool get_mouseChildren();
  void set_mouseChildren(bool enable);

  //TODO implement this property somewhere
  bool get_tabChildren() { return tabChildren; }
  void set_tabChildren(bool enable) { tabChildren = enable;}


  //////////////////////////////////////////////////////////////////////////
  TextSnapshotObject* get_textSnapshot()
  {
    NI_ALWAYS_ASSERT("Not yet implemented");
    return (TextSnapshotObject*)0;
  }

  ArrayObject* getObjectsUnderPoint(ScriptObject/*Point*/ * point)
  {
    NI_ALWAYS_ASSERT("Not yet implemented");
    return (ArrayObject*)0;
  }

  bool areInaccessibleObjectsUnderPoint(ScriptObject/*Point*/ * point)
  {
    NI_ALWAYS_ASSERT("Not yet implemented");
    return (bool)0;
  }

  // own methods

  virtual void SetStageAndRoot(StageObject * newStage, DisplayObjectObject* newRoot, bool parentHasListener);
  virtual void DumpHierarchy( int _depth );
  virtual const char* GetDumpName() { return "<DisplayObjectContainer>"; }

  virtual DisplayObjectObject* GetTopMostObject( const flash::SWF_POINT & point );

  virtual void SetNonBlocked( bool _isNonBlocked );
  virtual void SetNonBlockedOverride( bool _isNonBlockedOverride );

  virtual DisplayObjectObject* FindDisplayObjectByInstance( const char* _instanceName );

  virtual void OnMovedSized();

protected:

  DisplayObjects& GetChildren() { return children; }

private:
  virtual void DoRender( Render::IFlashRenderer* _renderer, const flash::SWF_MATRIX& _matrix, const flash::SWF_CXFORMWITHALPHA& _cxform, EFlashBlendMode::Enum _worldMode );
  virtual void GetBounds( flash::SWF_RECT& _rect );

  void SwapChildrenInternal( DisplayObjects::iterator child1, DisplayObjects::iterator child2);

  bool PrepareScale9GridConsts( CVec4& scale9ConstX, CVec4& scale9ConstY, CVec4& trans9Const, const flash::SWF_MATRIX& _matrix );

  DisplayObjects::iterator GetIterAt(int index);
  DisplayObjects::iterator GetChildIter(DisplayObjectObject * child);

  DECLARE_SLOTS_DisplayObjectContainerObject;
};
 
DECLARE_AS_CLASS(DisplayObjectContainerClass,InteractiveObjectClass, DisplayObjectContainerObject)
}