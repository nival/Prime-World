#pragma once
#include "System/SystemLog.h"
#include "../PlayerGlobalIncludes.h"
#include "../events/EventDispatcher.h"
#include "../geom/Transform.h"
#include "../../SwfTypes.h"
#include "UI/Defines.h"

#include "BlendMode.h"

namespace Render
{
  _interface IFlashRenderer;
}

namespace flash
{
  _interface IDisplayTag;
}

namespace avmplus
{
class DisplayObjectObject;
class ScriptObject;
class ShaderObject;
class DisplayObjectContainerObject;
class LoaderInfoObject;
class ArrayObject;
class StageObject;


class DisplayObjectObject: public EventDispatcherObject
{
public:
  DisplayObjectObject( DisplayObjectClass * classType );
  DisplayObjectObject( VTable* ivtable, ScriptObject* prototype );
  ~DisplayObjectObject();

  // from ScriptCommand
  virtual Atom toString();

  // AS methods

  DisplayObjectContainerObject* get_parent();
  DisplayObjectObject* get_root();
  StageObject* get_stage();

  void set_name(AvmString value);
  AvmString get_name();

  void set_visible(bool value);
  bool get_visible() { return visible; }

  void set_cacheAsBitmap(bool value) { cacheAsBitmap = value; }
  bool get_cacheAsBitmap() { return cacheAsBitmap; }

  void set_alpha(double value);
  double get_alpha();

  virtual void set_x(double value);
  virtual double get_x();

  virtual void set_y(double value);
  virtual double get_y();

  void set_z(double value) { zLocal = value; }
  double get_z() { return zLocal; }

  void set_rotation(double value);
  double get_rotation();

  void set_rotationX(double value) { rotationX = value; }
  double get_rotationX() { return rotationX; }
  void set_rotationY(double value) { rotationY = value; }
  double get_rotationY() { return rotationY; }
  void set_rotationZ(double value) { rotationZ = value; }
  double get_rotationZ() { return rotationZ; }

  void set_scaleX(double value);
  double get_scaleX();
  void set_scaleY(double value);
  double get_scaleY();
  void set_scaleZ(double value) { scaleZ = value; }
  double get_scaleZ() { return scaleZ; }

  virtual void set_width(double value);
  virtual double get_width();

  void set_height(double value);
  double get_height();

  double get_mouseX();
  double get_mouseY();

  void set_mask(DisplayObjectObject* value);
  DisplayObjectObject* get_mask() { return mask; }

  void set_transform(TransformObject* value);
  TransformObject* get_transform();

  void set_filters(ArrayObject* value) { filters = value; }
  ArrayObject* get_filters() { return filters; }

  void set_scale9Grid(ScriptObject/*Rectangle*/ * innerRectangle);
  ScriptObject/*Rectangle*/ * get_scale9Grid();

  void set_scrollRect(ScriptObject/*Rectangle*/ * value) { scrollRect = value; }
  ScriptObject/*Rectangle*/ * get_scrollRect() { return scrollRect; }

  void set_accessibilityProperties(ScriptObject/*AccessibilityProperties*/ * value) { accessibilityProperties = value; }
  ScriptObject/*AccessibilityProperties*/ * get_accessibilityProperties() { return accessibilityProperties; }

  bool _hitTest(bool use_xy, double x, double y, bool useShape, DisplayObjectObject* hitTestObject);

  ScriptObject/*Point*/ * localToGlobal(ScriptObject/*Point*/ * point);
  ScriptObject/*Point*/ * globalToLocal(ScriptObject/*Point*/ * point);

  ScriptObject/*Point*/ * local3DToGlobal(ScriptObject/*Vector3D*/ * point3d);
  ScriptObject/*Vector3D*/ * globalToLocal3D(ScriptObject/*Point*/ * point);

  LoaderInfoObject* get_loaderInfo() { return loaderInfo; }
  void SetLoaderInfo(LoaderInfoObject* value) { loaderInfo = value; }

  void set_opaqueBackground(AvmBox value) { opaqueBackground = value; }
  AvmBox get_opaqueBackground() { return opaqueBackground; }

  ScriptObject/*Rectangle*/ * getBounds(DisplayObjectObject* targetCoordinateSpace);
  ScriptObject/*Rectangle*/ * getRect(DisplayObjectObject* targetCoordinateSpace);

  void set_blendShader(ShaderObject* value);

  AvmString get_blendMode() { return blendMode->GetStringValue(); }
  void set_blendMode(AvmString value) { blendMode->SetStringValue( value ); }

  DECLARE_EVENT(ADDED_TO_STAGE);
  DECLARE_EVENT(REMOVED_FROM_STAGE);

  // own methods

  void SetDragged( bool _dragged ) { beeingDragged = _dragged; }
  bool IsDragged() const { return beeingDragged; }

  void SetUsedAsMask( bool _usedAsMask ) { usedAsMask = _usedAsMask; }
  bool UsedAsMask() const { return usedAsMask; }

  void SetAdvanceMark( bool mark ) { advanceMark = mark; }
  bool GetAdvanceMark() const { return advanceMark; }

  void SetCreationFrame( int _creationFrame ) { creationFrame = _creationFrame; }
  int GetCreationFrame() const { return creationFrame; }

  void SetCharacterID( int id );
  int GetCharacterID() const { return characterID; }

  void SetDepth( int _depth ) { depth = _depth; }
  int GetDepth() const { return depth; }

  void SetRatio( flash::UI16 _ratio ) { ratio = _ratio; }
  flash::UI16 GetRatio() const { return ratio; }

  void SetClippingDepth( int _depth ) { clippingDepth = _depth; }
  int GetClippingDepth() const { return clippingDepth; }

  virtual void OnSetCharacterID( int id ) {}
  
  virtual void SetStageAndRoot(StageObject * newStage, DisplayObjectObject* newRoot, bool parentHasListener);

  void SetParent( DisplayObjectContainerObject * parentObject );

  void SetRoot( DisplayObjectObject* newRoot );
  void SetStage( StageObject * newStage, bool fireStage );

  bool IsAncestor( DisplayObjectObject* ancestor ) const;

  void SetMatrix( flash::SWF_MATRIX& _matrix );

  virtual const flash::SWF_MATRIX& GetMatrix() const;
  virtual flash::SWF_MATRIX& GetMatrix();

  void SetColorTransform( flash::SWF_CXFORMWITHALPHA& _matrix );

  const flash::SWF_CXFORMWITHALPHA& GetColorTransform() const;
        flash::SWF_CXFORMWITHALPHA& GetColorTransform();

  BlendMode* GetBlendMode() { return blendMode; }
  const BlendMode* GetBlendMode() const { return blendMode; }
        
  void GetWorldMatrix( flash::SWF_MATRIX& worldMatrix ) const;

  void Render( Render::IFlashRenderer* _renderer, const flash::SWF_MATRIX& _matrix, const flash::SWF_CXFORMWITHALPHA& _cxform, EFlashBlendMode::Enum _worldMode, bool asMask );

  void GetWorldBounds( flash::SWF_RECT& _rect );
  void GetLocalBounds( flash::SWF_RECT& _rect );

  void LocalToGlobal( flash::SWF_POINT& _result, const flash::SWF_POINT& _point ) const;
  void GlobalToLocal( flash::SWF_POINT& _result, const flash::SWF_POINT& _point ) const;

  virtual bool HitTest( const flash::SWF_POINT & worldPoint );

  virtual DisplayObjectObject* GetTopMostObject( const flash::SWF_POINT & point );

  virtual void DumpHierarchy( int _depth );
  virtual const char* GetDumpName() { return "<Unknown type>"; }

  virtual void DoRender( Render::IFlashRenderer* _renderer, const flash::SWF_MATRIX& _matrix, const flash::SWF_CXFORMWITHALPHA& _cxform, EFlashBlendMode::Enum _worldMode);
  virtual void GetBounds( flash::SWF_RECT& _rect );

  virtual bool IsInteractive() const { return false; }

  virtual void SetGlowHack( bool useGlow, flash::SWF_RGBA& _color ) {}

  const flash::SWF_RECT& GetScale9Grid() { return scale9GridRect; } 

  const nstl::string GetNameDebug();

  void SetScale9Grid( const flash::SWF_RECT& _scale9Grid );
  void SetScale9GridFromParent( const CVec4& _constX, const CVec4& _constY, const CVec4& _trans );
  void SetUseScale9GridFromParent( bool _use ) { useParentScale9Grid = _use; }

  virtual void OnAddedToDisplayList() {}
  virtual void OnRemovedFromDisplayList() {}
  virtual void OnMovedSized() {}

  // blocking
  bool IsNonBlocked() const { return isNonBlocked; }
  bool IsNonBlockedOverride() const { return isNonBlockedOverride; }
  virtual void SetNonBlocked( bool _isNonBlocked ) { isNonBlocked = _isNonBlocked; isNonBlockedOverride = false; }
  virtual void SetNonBlockedOverride( bool _isNonBlockedOverride ) { isNonBlockedOverride = _isNonBlockedOverride; }

  virtual DisplayObjectObject* FindDisplayObjectByInstance( const char* _instanceName );

protected:

  ScriptObject/*Point*/ * GlobalConvert(ScriptObject/*Point*/ * point, bool local2global);

  virtual void OnEnterFrame() {}

  bool HasAddToStageListener();
  bool HasRemoveFromStageListener();

  bool usedAsMask;

  flash::SWF_RECT scale9GridRect;
  bool useScale9Grid;
  CVec4 scale9ConstX; // from parent MovieClip 
  CVec4 scale9ConstY; // from parent MovieClip
  CVec4 trans9Const; // from parent MovieClip
  bool useParentScale9Grid;

private:
  //this method is called in ctor
  void Initialize();

  void BeginFilters( Render::IFlashRenderer* _renderer );
  void EndFilters( Render::IFlashRenderer* _renderer );

  void GetLocalMousePoint( flash::SWF_POINT& point );

  bool beeingDragged;

  int characterID;
  int depth;
  int clippingDepth;
  bool advanceMark;
  flash::UI16 ratio;
  int creationFrame;

  bool visible;
  bool cacheAsBitmap; // we don't care about it

  double zLocal; // [TODO] implement functionality

  double rotationX; // [TODO] implement functionality
  double rotationY; // [TODO] implement functionality
  double rotationZ; // [TODO] implement functionality

  double scaleZ; // [TODO] implement functionality

  double mouseX; // [TODO] implement functionality
  double mouseY; // [TODO] implement functionality

  bool isNonBlocked;
  bool isNonBlockedOverride;

  DRCWB( DisplayObjectObject* ) mask;
  DRCWB( TransformObject* ) transform;
  DRCWB( ArrayObject* ) filters;
  DRCWB( LoaderInfoObject* ) loaderInfo; // [TODO] implement functionality. Default NULL

  DRCWB( ScriptObject* ) accessibilityProperties; // [TODO] implement functionality
  DRCWB( ScriptObject* ) scrollRect;  // [TODO] implement functionality. Default NULL

  DRCWB( ScriptObject* ) scale9Grid;

  AvmBox opaqueBackground;  // [TODO] implement functionality. Default NULL
  BlendMode* blendMode;

  DRCWB(AvmString) name;
  nstl::string nameCopy;

  DWB(MMgc::GCWeakRef*) parent; //DisplayObjectContainerObject*
  DWB(MMgc::GCWeakRef*) stage; // StageObject*
  DWB(MMgc::GCWeakRef*) root; // DisplayObjectObject*

  DRCWB(avmplus::EventObject*) enterFrameEvent;

  DECLARE_SLOTS_DisplayObjectObject;
};
 
DECLARE_AS_CLASS( DisplayObjectClass, EventDispatcherClass, DisplayObjectObject )

struct DisplayObjectGCRoot: public MMgc::GCRoot
{
  DisplayObjectGCRoot(MMgc::GC * gc, DisplayObjectObject * _displayObject) : MMgc::GCRoot(gc)
  {
    displayObject = _displayObject;
  }

  DRC(DisplayObjectObject*) displayObject;
};

typedef GCRootWrapper<DisplayObjectGCRoot> DisplayObjectWrapper;

}