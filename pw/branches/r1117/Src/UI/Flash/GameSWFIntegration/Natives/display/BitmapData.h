#pragma once
#include "System/SystemLog.h"

#include "../PlayerGlobalIncludes.h"

#include "../../FlashBaseClasses.h"

namespace Render
{
  _interface IBitmapInfo;
}

namespace avmplus
{

class BitmapDataObject;
class ScriptObject;
class BitmapFilterObject;
class UIntVectorObject;
class ArrayObject;
class ByteArrayObject;
class ObjectVectorObject;

class BitmapDataObject : public FlashScriptObject
{
public:

  BitmapDataObject( BitmapDataClass * classType );
  BitmapDataObject( BitmapDataClass * classType,  int width, int height, bool transparent, uint fillColor );
  BitmapDataObject( VTable* ivtable, ScriptObject* prototype );
  ~BitmapDataObject();

  void _Init( int width, int height, bool transparent, uint fillColor );

  // AS methods

  int get_width();
  int get_height();
  bool get_transparent();

  void lock();
  void unlock(ScriptObject/*Rectangle*/ * changeRect);

  void copyPixels(BitmapDataObject* sourceBitmapData, ScriptObject/*Rectangle*/ * sourceRect, ScriptObject/*Point*/ * destPoint, BitmapDataObject* alphaBitmapData, ScriptObject/*Point*/ * alphaPoint, bool mergeAlpha);

  void setPixel(int x, int y, uint color);
  uint getPixel(int x, int y);
  void setPixel32(int x, int y, uint color);
  uint getPixel32(int x, int y);
  void setPixels(ScriptObject/*Rectangle*/ * rect, ByteArrayObject* inputByteArray);
  ByteArrayObject* getPixels(ScriptObject/*Rectangle*/ * rect);

  bool hitTest(ScriptObject/*Point*/ * firstPoint, uint firstAlphaThreshold, AvmBox secondObject, ScriptObject/*Point*/ * secondBitmapDataPoint, uint secondAlphaThreshold);

  void draw(ScriptObject/*IBitmapDrawable*/ * source, ScriptObject/*Matrix*/ * matrix, ScriptObject/*ColorTransform*/ * colorTransform, AvmString blendMode, ScriptObject/*Rectangle*/ * clipRect, bool smoothing);
  void copyChannel(BitmapDataObject* sourceBitmapData, ScriptObject/*Rectangle*/ * sourceRect, ScriptObject/*Point*/ * destPoint, uint sourceChannel, uint destChannel);
  void merge(BitmapDataObject* sourceBitmapData, ScriptObject/*Rectangle*/ * sourceRect, ScriptObject/*Point*/ * destPoint, uint redMultiplier, uint greenMultiplier, uint blueMultiplier, uint alphaMultiplier);
  BitmapDataObject* clone();
  AvmBox compare(BitmapDataObject* otherBitmapData);

  ScriptObject/*Rectangle*/ * generateFilterRect(ScriptObject/*Rectangle*/ * sourceRect, BitmapFilterObject* filter);
  ScriptObject/*Rectangle*/ * getColorBoundsRect(uint mask, uint color, bool findColor);

  void applyFilter(BitmapDataObject* sourceBitmapData, ScriptObject/*Rectangle*/ * sourceRect, ScriptObject/*Point*/ * destPoint, BitmapFilterObject* filter);
  void fillRect(ScriptObject/*Rectangle*/ * rect, uint color);
  void colorTransform(ScriptObject/*Rectangle*/ * rect, ScriptObject/*ColorTransform*/ * colorTransform);
  void floodFill(int x, int y, uint color);
  void paletteMap(BitmapDataObject* sourceBitmapData, ScriptObject/*Rectangle*/ * sourceRect, ScriptObject/*Point*/ * destPoint, ArrayObject* redArray, ArrayObject* greenArray, ArrayObject* blueArray, ArrayObject* alphaArray);
  void noise(int randomSeed, uint low, uint high, uint channelOptions, bool grayScale);
  void perlinNoise(double baseX, double baseY, uint numOctaves, int randomSeed, bool stitch, bool fractalNoise, uint channelOptions, bool grayScale, ArrayObject* offsets);
  int pixelDissolve(BitmapDataObject* sourceBitmapData, ScriptObject/*Rectangle*/ * sourceRect, ScriptObject/*Point*/ * destPoint, int randomSeed, int numPixels, uint fillColor);
  uint threshold(BitmapDataObject* sourceBitmapData, ScriptObject/*Rectangle*/ * sourceRect, ScriptObject/*Point*/ * destPoint, AvmString operation, uint threshold, uint color, uint mask, bool copySource);

  void _setVector(UIntVectorObject* inputVector, int x, int y, int width, int height);
  AvmBox _getVector(UIntVectorObject* v, int x, int y, int width, int height);

  ObjectVectorObject* histogram(ScriptObject/*Rectangle*/ * hRect);
  void scroll(int x, int y);
  void dispose();

  // own methods

  void SetBitmapInfo( Render::IBitmapInfo* _bitmapInfo ) { bitmapInfo = _bitmapInfo; }
  Render::IBitmapInfo* GetBitmapInfo() const { return bitmapInfo; }

  void SetTexture( const Render::Texture2DRef& _texture );

  void SetParentBitmap( BitmapObject* _parent ) { parentBitmap = _parent; } 
  BitmapObject* GetParentBitmap() { return parentBitmap; }

private:
  Strong<Render::IBitmapInfo> bitmapInfo;

  DRCWB( BitmapObject* ) parentBitmap;

  DECLARE_SLOTS_BitmapDataObject;
};
  
class BitmapDataClass : public FlashClassClosure
{
public:
  BitmapDataClass(VTable *vtable): FlashClassClosure(vtable)
  { 
    flash::FlashMovieAvmCore * flashCore = (flash::FlashMovieAvmCore*) core();
    flashCore->GetClassCache().RegisterClass( EFlashClassID::BitmapDataClass, this );
  }

  ~BitmapDataClass() {}

  virtual Atom construct(int argc, Atom* argv);

  virtual ScriptObject* createInstance(VTable* ivtable, ScriptObject* prototype)
  {
    return new (core()->GetGC(), ivtable->getExtraSize()) BitmapDataObject(ivtable, prototype);
  } 

private:
  DECLARE_SLOTS_BitmapDataClass;
};


}