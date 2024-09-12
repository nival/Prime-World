#include "TamarinPCH.h"

#include <Render/FlashRendererInterface.h>

#include "../../FlashClassesCache.h"
#include "../../ImageData.h"
#include "../../FlashMovie.h"

#include "Bitmap.h"
#include "BitmapData.h"
#include "DisplayObjectContainer.h"

namespace avmplus
{

Atom BitmapClass::construct(int argc, Atom* argv)
{
  BitmapDataObject* _bitmapData = 0;

  if ( argc > 0 )
    _bitmapData = dynamic_cast<BitmapDataObject*>( core()->atomToScriptObject( argv[1] ) );

  BitmapObject * object = new (core()->GetGC(), ivtable()->getExtraSize()) BitmapObject( this, _bitmapData );
  return object->atom();
}

BitmapObject::BitmapObject( BitmapClass * classType ) : 
  DisplayObjectObject((DisplayObjectClass*)classType),
  smoothing(false),
  textureSmoothing(true)
{

}

BitmapObject::BitmapObject( VTable* ivtable, ScriptObject* prototype ) :
  DisplayObjectObject(ivtable, prototype),
  smoothing(false),
  textureSmoothing(true)
{

}

BitmapObject::BitmapObject( BitmapClass * classType, BitmapDataObject * _bitmapData ) :
  DisplayObjectObject((DisplayObjectClass*)classType),
  smoothing(false),
  textureSmoothing(true)
{
  _Init( _bitmapData, 0, true );
}

BitmapObject::~BitmapObject()
{

}

void BitmapObject::Set__internalUsage__()
{
  int slotID = GetSlotID( "__internalUsage__" );

  if ( slotID != -1 )
    coerceAndSetSlotAtom( slotID, trueAtom ); 
}

void BitmapObject::_Init( BitmapDataObject * _bitmapData, AvmString pixelSnapping, bool _smoothing )
{
  if ( !bitmapData && _bitmapData )
  {
    set_bitmapData( _bitmapData );
    smoothing = _smoothing;
  }

  Set__internalUsage__();
}

void BitmapObject::set_bitmapData( BitmapDataObject* value ) 
{ 
  if ( value )
  {
    if ( value->GetParentBitmap() )
      value->GetParentBitmap()->set_bitmapData( 0 );
  }

  bitmapData = value; 

  if ( bitmapData )
    bitmapData->SetParentBitmap( this );
}

BitmapDataObject* BitmapObject::get_bitmapData() 
{ 
  return bitmapData; 
}

AvmString BitmapObject::get_pixelSnapping()
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "BitmapObject", "get_pixelSnapping" );
  return (AvmString)0;
}

void BitmapObject::set_pixelSnapping(AvmString value)
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "BitmapObject", "set_pixelSnapping" );
  return (void)0;
}

void BitmapObject::CreateBitmapData()
{
  if ( !bitmapData )
  {
    avmplus::BitmapDataClass * classInstance = ((flash::FlashMovieAvmCore*)core())->GetClassCache().GetClass<avmplus::BitmapDataClass>( EFlashClassID::BitmapDataClass );
    avmplus::Atom args[] = {0};
    bitmapData =(avmplus::BitmapDataObject*)((flash::FlashMovieAvmCore*)core())->atomToScriptObject(classInstance->construct(0, args));
  }
}

void BitmapObject::SetImage( const flash::ImageData& _imageData )
{
  CreateBitmapData();
  bitmapData->SetBitmapInfo( _imageData.GetBitmapInfo() );
}

void BitmapObject::LoadImage( const nstl::string& _imageFile )
{
  if ( FlashCore()->GetMovie()->GetFlashRenderer() )
  {
    Strong<Render::IBitmapInfo> bitmaInfo = FlashCore()->GetMovie()->GetFlashRenderer()->CreateBitmapFromFile( _imageFile );

    CreateBitmapData();
    bitmapData->SetBitmapInfo( bitmaInfo );
  }
}

void BitmapObject::SetTexture( const Render::Texture2DRef& _texture )
{
  CreateBitmapData();
  bitmapData->SetTexture( _texture );
}

void BitmapObject::GetBounds( flash::SWF_RECT& _rect )
{
  _rect.X1 = 0;
  _rect.Y1 = 0;

  if ( bitmapData && bitmapData->GetBitmapInfo() )
  {
    _rect.X2 = PIXELS_TO_TWIPS(bitmapData->GetBitmapInfo()->GetWidth());
    _rect.Y2 = PIXELS_TO_TWIPS(bitmapData->GetBitmapInfo()->GetHeight());
  }
  else
  {
    _rect.X2 = 0;
    _rect.Y2 = 0;
  }
}

void BitmapObject::DoRender( Render::IFlashRenderer* _renderer, const flash::SWF_MATRIX& _matrix, const flash::SWF_CXFORMWITHALPHA& _cxform, EFlashBlendMode::Enum _worldMode )
{
  if ( !bitmapData )
    return;

  if ( !bitmapData->GetBitmapInfo() )
    return;

  float width = PIXELS_TO_TWIPS(bitmapData->GetBitmapInfo()->GetWidth());
  float height = PIXELS_TO_TWIPS(bitmapData->GetBitmapInfo()->GetHeight());

  _renderer->SetMatrix( _matrix );
  _renderer->SetColorTransform( _cxform );
  _renderer->SetBlendMode( _worldMode );

  if ( get_scale9Grid() )
  {
    const flash::SWF_RECT& _scale9Grid = GetScale9Grid();
    flash::SWF_RECT _scale9GridReal; 
    _scale9GridReal.X1 = _scale9Grid.X1 / flash::TWIP;
    _scale9GridReal.X2 = _scale9Grid.X2 / flash::TWIP;
    _scale9GridReal.Y1 = _scale9Grid.Y1 / flash::TWIP;
    _scale9GridReal.Y2 = _scale9Grid.Y2 / flash::TWIP;

    _renderer->DrawBitmapScale9Grid( bitmapData->GetBitmapInfo(), width, height, _scale9GridReal, _matrix.m_[0][0], _matrix.m_[1][1], -1, textureSmoothing );
  }
  else
  {
    _renderer->DrawBitmap( bitmapData->GetBitmapInfo(), width, height, -1, textureSmoothing );
  }
}

}