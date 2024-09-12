#include "TamarinPCH.h"

#include <Render/FlashRendererInterface.h>

#include "../../FlashMovieAvmCore.h"
#include "../../FlashMovie.h"

#include "../geom/Transform.h"

#include "../../Characters.h"

#include "BitmapData.h"

namespace avmplus
{

Atom BitmapDataClass::construct(int argc, Atom* argv)
{
  int _width = 16;
  int _height = 16;
  bool _transparent = false;
  uint _fillColor = 1;

  if ( argc > 0 )
    _width =  core()->integer_i( argv[1] );
  if ( argc > 1 )
    _height = core()->integer_i( argv[2] );

  BitmapDataObject * object = new (core()->GetGC(), ivtable()->getExtraSize()) BitmapDataObject(this, _width, _height, _transparent, _fillColor );
  return object->atom();
}


BitmapDataObject::BitmapDataObject( BitmapDataClass * classType ) : 
  FlashScriptObject(classType->ivtable(), classType->prototype )
{ 

}

BitmapDataObject::BitmapDataObject( BitmapDataClass * classType,  int width, int height, bool transparent, uint fillColor ) :
  FlashScriptObject(classType->ivtable(), classType->prototype )
{
  _Init( width, height, transparent, fillColor );
}

BitmapDataObject::BitmapDataObject( VTable* ivtable, ScriptObject* prototype ) : 
  FlashScriptObject(ivtable, prototype)
{ 

}

void BitmapDataObject::_Init( int width, int height, bool transparent, uint fillColor )
{
  AvmString className = this->vtable->traits->formatClassName();

  //check. may be we have data associated with this class
  flash::ICharacter * bitmapCharacter = FlashCore()->GetMovie()->GetCharacterByName(className);

  if ( bitmapCharacter )
  {
    bitmapCharacter->InitObject( this );
  }
  else
  {
    bitmapInfo = FlashCore()->GetMovie()->GetFlashRenderer()->CreateBitmap( width, height );
  }
}

void BitmapDataObject::SetTexture( const Render::Texture2DRef& _texture )
{
  bitmapInfo = FlashCore()->GetMovie()->GetFlashRenderer()->CreateBitmapFromTexture ( _texture );
}

BitmapDataObject::~BitmapDataObject() 
{ 

}

void BitmapDataObject::copyPixels(BitmapDataObject* sourceBitmapData, ScriptObject/*Rectangle*/ * sourceRect, ScriptObject/*Point*/ * destPoint, BitmapDataObject* alphaBitmapData, ScriptObject/*Point*/ * alphaPoint, bool mergeAlpha)
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  return (void)0;
}

void BitmapDataObject::setPixel(int x, int y, uint color)
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  return (void)0;
}

bool BitmapDataObject::hitTest(ScriptObject/*Point*/ * firstPoint, uint firstAlphaThreshold, AvmBox secondObject, ScriptObject/*Point*/ * secondBitmapDataPoint, uint secondAlphaThreshold)
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  return (bool)0;
}

void BitmapDataObject::applyFilter(BitmapDataObject* sourceBitmapData, ScriptObject/*Rectangle*/ * sourceRect, ScriptObject/*Point*/ * destPoint, BitmapFilterObject* filter)
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  return (void)0;
}

void BitmapDataObject::fillRect(ScriptObject/*Rectangle*/ * rect, uint color)
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  return (void)0;
}

void BitmapDataObject::colorTransform(ScriptObject/*Rectangle*/ * rect, ScriptObject/*ColorTransform*/ * colorTransform)
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  return (void)0;
}

void BitmapDataObject::draw(ScriptObject/*IBitmapDrawable*/ * source, ScriptObject/*Matrix*/ * matrix, ScriptObject/*ColorTransform*/ * colorTransform, AvmString blendMode, ScriptObject/*Rectangle*/ * clipRect, bool smoothing)
{
  BitmapDataObject* sourceBMP = dynamic_cast<BitmapDataObject*>( source );

  if ( sourceBMP && sourceBMP->GetBitmapInfo() && bitmapInfo )
  {
    Atom args[] = {0};
    TransformClass * transformClass = FlashCore()->GetClassCache().GetClass<TransformClass>( EFlashClassID::TransformClass );
    TransformObject * transform = (TransformObject *)FlashCore()->atomToScriptObject(transformClass->construct(0, args));

    if ( matrix )
      transform->set_matrix( matrix );
    if ( colorTransform )
      transform->set_colorTransform( colorTransform );

    float _width = sourceBMP->GetBitmapInfo()->GetWidth();
    float _height = sourceBMP->GetBitmapInfo()->GetHeight();
    float _x = 0;
    float _y = 0;

    if ( clipRect )
    {
      int _c_width = GetSlotID( clipRect, "width" );
      int _c_height = GetSlotID( clipRect, "height" );
      int _c_x = GetSlotID( clipRect, "x" );
      int _c_y = GetSlotID( clipRect, "y" );
      
      _width = core()->number_d( clipRect->getSlotAtom( _c_width ) );
      _height = core()->number_d( clipRect->getSlotAtom( _c_height ) );
      _x = core()->number_d( clipRect->getSlotAtom( _c_x ) );
      _y = core()->number_d( clipRect->getSlotAtom( _c_y ) );
    }

    const flash::SWF_MATRIX& matrixI = transform->GetMatrix();

    bitmapInfo->Draw( sourceBMP->GetBitmapInfo(), matrixI, _x, _y, _x + _width, _y + _height );
  }
}

int BitmapDataObject::get_width()
{
  if ( bitmapInfo )
    return bitmapInfo->GetWidth();

  return 0;
}

void BitmapDataObject::copyChannel(BitmapDataObject* sourceBitmapData, ScriptObject/*Rectangle*/ * sourceRect, ScriptObject/*Point*/ * destPoint, uint sourceChannel, uint destChannel)
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  return (void)0;
}

uint BitmapDataObject::getPixel(int x, int y)
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  return (uint)0;
}

ScriptObject/*Rectangle*/ * BitmapDataObject::generateFilterRect(ScriptObject/*Rectangle*/ * sourceRect, BitmapFilterObject* filter)
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  return (ScriptObject/*Rectangle*/ *)0;
}

bool BitmapDataObject::get_transparent()
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  return (bool)0;
}

void BitmapDataObject::unlock(ScriptObject/*Rectangle*/ * changeRect)
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  return (void)0;
}

void BitmapDataObject::scroll(int x, int y)
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  return (void)0;
}

ScriptObject/*Rectangle*/ * BitmapDataObject::getColorBoundsRect(uint mask, uint color, bool findColor)
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  return (ScriptObject/*Rectangle*/ *)0;
}

int BitmapDataObject::pixelDissolve(BitmapDataObject* sourceBitmapData, ScriptObject/*Rectangle*/ * sourceRect, ScriptObject/*Point*/ * destPoint, int randomSeed, int numPixels, uint fillColor)
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  return (int)0;
}

void BitmapDataObject::noise(int randomSeed, uint low, uint high, uint channelOptions, bool grayScale)
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  return (void)0;
}

BitmapDataObject* BitmapDataObject::clone()
{
  if ( bitmapInfo )
  {
    avmplus::BitmapDataClass * classInstance = ((flash::FlashMovieAvmCore*)core())->GetClassCache().GetClass<avmplus::BitmapDataClass>( EFlashClassID::BitmapDataClass );
    avmplus::Atom args[] = {0};
    avmplus::BitmapDataObject * bitmapData =(avmplus::BitmapDataObject*)((flash::FlashMovieAvmCore*)core())->atomToScriptObject(classInstance->construct(0, args));

    bitmapData->SetBitmapInfo( bitmapInfo->Clone() );

    return bitmapData;
  }

  return 0;
}

void BitmapDataObject::_setVector(UIntVectorObject* inputVector, int x, int y, int width, int height)
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  return (void)0;
}

void BitmapDataObject::dispose()
{

}

void BitmapDataObject::floodFill(int x, int y, uint color)
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  return (void)0;
}

void BitmapDataObject::setPixel32(int x, int y, uint color)
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  return (void)0;
}

AvmBox BitmapDataObject::compare(BitmapDataObject* otherBitmapData)
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  return (AvmBox)0;
}

void BitmapDataObject::perlinNoise(double baseX, double baseY, uint numOctaves, int randomSeed, bool stitch, bool fractalNoise, uint channelOptions, bool grayScale, ArrayObject* offsets)
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  return (void)0;
}

int BitmapDataObject::get_height()
{
  if ( bitmapInfo )
    return bitmapInfo->GetHeight();

  return 0;
}

void BitmapDataObject::paletteMap(BitmapDataObject* sourceBitmapData, ScriptObject/*Rectangle*/ * sourceRect, ScriptObject/*Point*/ * destPoint, ArrayObject* redArray, ArrayObject* greenArray, ArrayObject* blueArray, ArrayObject* alphaArray)
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  return (void)0;
}

ByteArrayObject* getPixels(ScriptObject/*Rectangle*/ * rect)
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  return (ByteArrayObject*)0;
}

uint BitmapDataObject::threshold(BitmapDataObject* sourceBitmapData, ScriptObject/*Rectangle*/ * sourceRect, ScriptObject/*Point*/ * destPoint, AvmString operation, uint threshold, uint color, uint mask, bool copySource)
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  return (uint)0;
}

uint BitmapDataObject::getPixel32(int x, int y)
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  return (uint)0;
}

void BitmapDataObject::lock()
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  return (void)0;
}

void BitmapDataObject::setPixels(ScriptObject/*Rectangle*/ * rect, ByteArrayObject* inputByteArray)
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  return (void)0;
}

ByteArrayObject* BitmapDataObject::getPixels(ScriptObject/*Rectangle*/ * rect)
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  return (ByteArrayObject*)0;
}

void BitmapDataObject::merge(BitmapDataObject* sourceBitmapData, ScriptObject/*Rectangle*/ * sourceRect, ScriptObject/*Point*/ * destPoint, uint redMultiplier, uint greenMultiplier, uint blueMultiplier, uint alphaMultiplier)
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  return (void)0;
}

AvmBox BitmapDataObject::_getVector(UIntVectorObject* v, int x, int y, int width, int height)
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  return (AvmBox)0;
}

ObjectVectorObject* BitmapDataObject::histogram(ScriptObject/*Rectangle*/ * hRect)
{
  NI_ALWAYS_ASSERT("Not yet implemented");
  return (ObjectVectorObject*)0;
}

}