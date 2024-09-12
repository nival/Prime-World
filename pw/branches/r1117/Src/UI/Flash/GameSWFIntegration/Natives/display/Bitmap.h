#pragma once
#include "System/SystemLog.h"
#include "../PlayerGlobalIncludes.h"
#include "DisplayObject.h"

namespace flash
{
  struct ImageData;
}

namespace avmplus
{
class BitmapDataObject;


class BitmapObject: public DisplayObjectObject
{
public:

  BitmapObject( BitmapClass * classType );
  BitmapObject( BitmapClass * classType, BitmapDataObject * bitmapData );
  BitmapObject( VTable* ivtable, ScriptObject* prototype );
  ~BitmapObject();

  void _Init( BitmapDataObject * bitmapData, AvmString pixelSnapping, bool _smoothing );

  void set_bitmapData(BitmapDataObject* value);
  BitmapDataObject* get_bitmapData();

  AvmString get_pixelSnapping();
  void set_pixelSnapping(AvmString value);

  void set_smoothing(bool value) { smoothing = value; }
  bool get_smoothing() { return smoothing; }

  // own methods
  void SetImage( const flash::ImageData& _imageData );
  void LoadImage( const nstl::string& _imageFile );

  void SetTexture( const Render::Texture2DRef& _texture );

  void SetTextureSmoothing( bool _smoothing ) { textureSmoothing = _smoothing; }

  virtual const char* GetDumpName() { return "<Bitmap>"; }

private:
  virtual void DoRender( Render::IFlashRenderer* _renderer, const flash::SWF_MATRIX& _matrix, const flash::SWF_CXFORMWITHALPHA& _cxform, EFlashBlendMode::Enum _worldMode );
  virtual void GetBounds( flash::SWF_RECT& _rect );

  void CreateBitmapData();

  void Set__internalUsage__();

  DRCWB( BitmapDataObject* ) bitmapData;
  bool smoothing;
  bool textureSmoothing;

  DECLARE_SLOTS_BitmapObject;
};
  
class BitmapClass : public DisplayObjectClass
{
public:
  BitmapClass(VTable *vtable): DisplayObjectClass(vtable)
  { 
    flash::FlashMovieAvmCore * flashCore = (flash::FlashMovieAvmCore*) core();
    flashCore->GetClassCache().RegisterClass( EFlashClassID::BitmapClass, this );
  }

  ~BitmapClass()
  {

  }

  virtual Atom construct(int argc, Atom* argv);

  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) BitmapObject(ivtable, prototype);
  } 

private:
  DECLARE_SLOTS_BitmapClass;
};


}