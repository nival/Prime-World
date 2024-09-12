#include "TamarinPCH.h"

#include <Render/FlashRendererInterface.h>

#include "ColorMatrixFilter.h"

namespace avmplus
{

ColorMatrixFilterObject::ColorMatrixFilterObject(VTable *ivtable, ScriptObject *delegate) : 
  BitmapFilterObject(ivtable, delegate),
  addColor( 0.f, 0.f, 0.f, 0.f )
{
  Identity( &colorMatrix );

  colorMatrix._11 = colorMatrix._22 = colorMatrix._33 = colorMatrix._44 = 1.f;

  externalColorMatrix = toplevel()->arrayClass->newArray( 20 );

  CopyInternalToExternal();
}

void ColorMatrixFilterObject::CopyInternalToExternal()
{
  for ( int i = 0; i < 4; ++i )
  {
    for ( int j = 0; j < 4; ++j )
    {
      externalColorMatrix->setIntProperty( i * 5 + j, core()->doubleToAtom( colorMatrix.m[i][j] ) );
    }

    externalColorMatrix->setIntProperty( i * 5 + 4, core()->doubleToAtom( addColor.m[i] ) );
  }
}

void ColorMatrixFilterObject::CopyExternalToInternal()
{
  for ( int i = 0; i < 4; ++i )
  {
    for ( int j = 0; j < 4; ++j )
    {
      colorMatrix.m[i][j] = core()->number_d( externalColorMatrix->getIntProperty( i * 5 + j ) );
    }

    addColor.m[i] = core()->number_d( externalColorMatrix->getIntProperty( i * 5 + 4 ) );
  }
}

ArrayObject* ColorMatrixFilterObject::get_matrix()
{
  CopyInternalToExternal();
  return externalColorMatrix;
}

void ColorMatrixFilterObject::set_matrix(ArrayObject* value)
{
  externalColorMatrix = value;
  CopyExternalToInternal();
}

void ColorMatrixFilterObject::RealtimeBegin( Render::IFlashRenderer* _renderer )
{
  _renderer->BeginColorMatrix( colorMatrix, addColor );
}

void ColorMatrixFilterObject::RealtimeEnd( Render::IFlashRenderer* _renderer )
{
  _renderer->EndColorMatrix();
}

}