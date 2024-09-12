#include "StdAfx.h"

#include "FlashInterface.h"
#include "FlashContainer2.h"

#include "Flash/GameSWFIntegration/FlashBaseClasses.h"
#include "Flash/GameSWFIntegration/FlashEnterFunction.h"

#define FLASH_INTERFACE_ENTER_FUNCTION(_numParam) \
  if ( !mainInterface ) return undefinedAtom;\
  FLASH_ENTER_FUNCTION_RETURN( mainInterface->gc(),undefinedAtom);\
  avmplus::Atom argv[_numParam + 1];\
  argv[0] = mainInterface->atom();

namespace UI
{

avmplus::Atom FVar::GetAtom( avmplus::Toplevel * _toplevel ) const
{
  switch ( type )
  {
  case Bool: return valueBool ? avmplus::AtomConstants::trueAtom : avmplus::AtomConstants::falseAtom;
  case Int: return _toplevel->core()->intToAtom( valueInt );
  case IntArray:
    {
      avmplus::ArrayObject* array = _toplevel->arrayClass->newArray( valueIntArray.size() );

      for ( int i = 0; i < valueIntArray.size(); ++i )
      {
        array->setIntProperty( i, _toplevel->core()->intToAtom( valueIntArray[i]));
      }

      return array->atom();
    }
  case Uint: return _toplevel->core()->uintToAtom( valueUint);
  case UintArray:
    {
      avmplus::ArrayObject* array = _toplevel->arrayClass->newArray( valueUintArray.size() );

      for ( int i = 0; i < valueUintArray.size(); ++i )
      {
        array->setIntProperty( i, _toplevel->core()->uintToAtom( valueUintArray[i]));
      }

      return array->atom();
    }
  case Float: return _toplevel->core()->doubleToAtom( valueFloat );
  case ConstChar: return _toplevel->core()->newStringLatin1( valueChar )->atom();
  case WString: return _toplevel->core()->newStringUTF16( (wchar*)valueWString.c_str() )->atom();
  case WStringArray:
    {
      avmplus::ArrayObject* array = _toplevel->arrayClass->newArray( valueWSArray.size() );

      for ( int i = 0; i < valueWSArray.size(); ++i )
      {
        array->setIntProperty( i, _toplevel->core()->newStringUTF16( (wchar*)valueWSArray[i].c_str() )->atom() );
      }

      return array->atom();
    }
  }

  return avmplus::AtomConstants::nullObjectAtom;
}

FlashInterface::FlashInterface( UI::FlashContainer2 * _flashWnd, const char* _className ) 
{
  if ( !_flashWnd )
    return;

  mainInterface = _flashWnd->GetFlashObject( _className );
  NI_ASSERT(mainInterface, "flashMovie should be valid!");
}

avmplus::ScriptObject * FlashInterface::AtomToObject( avmplus::Atom atom )
{
  if ( mainInterface )
    return mainInterface->toplevel()->core()->atomToScriptObject( atom );

  return 0;
}

bool FlashInterface::AtomGetBool( avmplus::Atom atom )
{
  return avmplus::AvmCore::boolean( atom );
}

int FlashInterface::AtomGetInt( avmplus::Atom atom )
{
  return avmplus::AvmCore::integer( atom );
}

avmplus::Atom FlashInterface::CallMethodI( const char * method )
{
  FLASH_INTERFACE_ENTER_FUNCTION( 0 );
  avmplus::Atom result;
  avmplus::FlashScriptObject::CallMethodI( mainInterface, method, 0, argv, result );
  return result;
}

avmplus::Atom FlashInterface::CallMethodI( const char * method, const FVar& p1 )
{
  FLASH_INTERFACE_ENTER_FUNCTION( 1 );
  avmplus::Atom result;
  argv[1] = p1.GetAtom( mainInterface->toplevel() );
  avmplus::FlashScriptObject::CallMethodI( mainInterface, method, 1, argv, result );
  return result;
}

avmplus::Atom FlashInterface::CallMethodI( const char * method, const FVar& p1, const FVar& p2 )
{
  FLASH_INTERFACE_ENTER_FUNCTION( 2 );
  avmplus::Atom result;
  argv[1] = p1.GetAtom( mainInterface->toplevel() );
  argv[2] = p2.GetAtom( mainInterface->toplevel() );
  avmplus::FlashScriptObject::CallMethodI( mainInterface, method, 2, argv, result );
  return result;
}

avmplus::Atom FlashInterface::CallMethodI( const char * method, const FVar& p1, const FVar& p2, const FVar& p3 )
{
  FLASH_INTERFACE_ENTER_FUNCTION( 3 );
  avmplus::Atom result;
  argv[1] = p1.GetAtom( mainInterface->toplevel() );
  argv[2] = p2.GetAtom( mainInterface->toplevel() );
  argv[3] = p3.GetAtom( mainInterface->toplevel() );
  avmplus::FlashScriptObject::CallMethodI( mainInterface, method, 3, argv, result );
  return result;
}

avmplus::Atom FlashInterface::CallMethodI( const char * method, const FVar& p1, const FVar& p2, const FVar& p3, const FVar& p4 )
{
  FLASH_INTERFACE_ENTER_FUNCTION( 4 );
  avmplus::Atom result;
  argv[1] = p1.GetAtom( mainInterface->toplevel() );
  argv[2] = p2.GetAtom( mainInterface->toplevel() );
  argv[3] = p3.GetAtom( mainInterface->toplevel() );
  argv[4] = p4.GetAtom( mainInterface->toplevel() );
  avmplus::FlashScriptObject::CallMethodI( mainInterface, method, 4, argv, result );
  return result;
}

avmplus::Atom FlashInterface::CallMethodI( const char * method, const FVar& p1, const FVar& p2, const FVar& p3, const FVar& p4, const FVar& p5 )
{
  FLASH_INTERFACE_ENTER_FUNCTION( 5 );
  avmplus::Atom result;
  argv[1] = p1.GetAtom( mainInterface->toplevel() );
  argv[2] = p2.GetAtom( mainInterface->toplevel() );
  argv[3] = p3.GetAtom( mainInterface->toplevel() );
  argv[4] = p4.GetAtom( mainInterface->toplevel() );
  argv[5] = p5.GetAtom( mainInterface->toplevel() );
  avmplus::FlashScriptObject::CallMethodI( mainInterface, method, 5, argv, result );
  return result;
}

avmplus::Atom FlashInterface::CallMethodI( const char * method, const FVar& p1, const FVar& p2, const FVar& p3, const FVar& p4, const FVar& p5, const FVar& p6 )
{
  FLASH_INTERFACE_ENTER_FUNCTION( 6 );
  avmplus::Atom result;
  argv[1] = p1.GetAtom( mainInterface->toplevel() );
  argv[2] = p2.GetAtom( mainInterface->toplevel() );
  argv[3] = p3.GetAtom( mainInterface->toplevel() );
  argv[4] = p4.GetAtom( mainInterface->toplevel() );
  argv[5] = p5.GetAtom( mainInterface->toplevel() );
  argv[6] = p6.GetAtom( mainInterface->toplevel() );
  avmplus::FlashScriptObject::CallMethodI( mainInterface, method, 6, argv, result );
  return result;
}

avmplus::Atom FlashInterface::CallMethodI( const char * method, const FVar& p1, const FVar& p2, const FVar& p3, const FVar& p4, const FVar& p5, const FVar& p6, const FVar& p7 )
{
  FLASH_INTERFACE_ENTER_FUNCTION( 7 );
  avmplus::Atom result;
  argv[1] = p1.GetAtom( mainInterface->toplevel() );
  argv[2] = p2.GetAtom( mainInterface->toplevel() );
  argv[3] = p3.GetAtom( mainInterface->toplevel() );
  argv[4] = p4.GetAtom( mainInterface->toplevel() );
  argv[5] = p5.GetAtom( mainInterface->toplevel() );
  argv[6] = p6.GetAtom( mainInterface->toplevel() );
  argv[7] = p7.GetAtom( mainInterface->toplevel() );
  avmplus::FlashScriptObject::CallMethodI( mainInterface, method, 7, argv, result );
  return result;
}

avmplus::Atom FlashInterface::CallMethodI( const char * method, const FVar& p1, const FVar& p2, const FVar& p3, const FVar& p4, const FVar& p5, const FVar& p6, const FVar& p7, const FVar& p8 )
{
  FLASH_INTERFACE_ENTER_FUNCTION( 8 );
  avmplus::Atom result;
  argv[1] = p1.GetAtom( mainInterface->toplevel() );
  argv[2] = p2.GetAtom( mainInterface->toplevel() );
  argv[3] = p3.GetAtom( mainInterface->toplevel() );
  argv[4] = p4.GetAtom( mainInterface->toplevel() );
  argv[5] = p5.GetAtom( mainInterface->toplevel() );
  argv[6] = p6.GetAtom( mainInterface->toplevel() );
  argv[7] = p7.GetAtom( mainInterface->toplevel() );
  argv[8] = p8.GetAtom( mainInterface->toplevel() );
  avmplus::FlashScriptObject::CallMethodI( mainInterface, method, 8, argv, result );
  return result;
}

avmplus::Atom FlashInterface::CallMethodI( const char * method, const FVar& p1, const FVar& p2, const FVar& p3, const FVar& p4, const FVar& p5, const FVar& p6, const FVar& p7, const FVar& p8, const FVar& p9 )
{
  FLASH_INTERFACE_ENTER_FUNCTION( 9 );
  avmplus::Atom result;
  argv[1] = p1.GetAtom( mainInterface->toplevel() );
  argv[2] = p2.GetAtom( mainInterface->toplevel() );
  argv[3] = p3.GetAtom( mainInterface->toplevel() );
  argv[4] = p4.GetAtom( mainInterface->toplevel() );
  argv[5] = p5.GetAtom( mainInterface->toplevel() );
  argv[6] = p6.GetAtom( mainInterface->toplevel() );
  argv[7] = p7.GetAtom( mainInterface->toplevel() );
  argv[8] = p8.GetAtom( mainInterface->toplevel() );
  argv[9] = p9.GetAtom( mainInterface->toplevel() );
  avmplus::FlashScriptObject::CallMethodI( mainInterface, method, 9, argv, result );
  return result;
}

avmplus::Atom FlashInterface::CallMethodI( const char * method, const FVar& p1, const FVar& p2, const FVar& p3, const FVar& p4, const FVar& p5, const FVar& p6, const FVar& p7, const FVar& p8, const FVar& p9 , const FVar& p10)
{
	FLASH_INTERFACE_ENTER_FUNCTION( 10 );
	avmplus::Atom result;
	argv[1] = p1.GetAtom( mainInterface->toplevel() );
	argv[2] = p2.GetAtom( mainInterface->toplevel() );
	argv[3] = p3.GetAtom( mainInterface->toplevel() );
	argv[4] = p4.GetAtom( mainInterface->toplevel() );
	argv[5] = p5.GetAtom( mainInterface->toplevel() );
	argv[6] = p6.GetAtom( mainInterface->toplevel() );
	argv[7] = p7.GetAtom( mainInterface->toplevel() );
	argv[8] = p8.GetAtom( mainInterface->toplevel() );
	argv[9] = p9.GetAtom( mainInterface->toplevel() );
	argv[10] = p10.GetAtom( mainInterface->toplevel() );
	avmplus::FlashScriptObject::CallMethodI( mainInterface, method, 10, argv, result );
	return result;
}

avmplus::Atom FlashInterface::CallMethodI( const char * method, const FVar& p1, const FVar& p2, const FVar& p3, const FVar& p4, const FVar& p5, const FVar& p6, const FVar& p7, const FVar& p8, const FVar& p9 , const FVar& p10, const FVar& p11)
{
  FLASH_INTERFACE_ENTER_FUNCTION( 11 );
  avmplus::Atom result;
  argv[1] = p1.GetAtom( mainInterface->toplevel() );
  argv[2] = p2.GetAtom( mainInterface->toplevel() );
  argv[3] = p3.GetAtom( mainInterface->toplevel() );
  argv[4] = p4.GetAtom( mainInterface->toplevel() );
  argv[5] = p5.GetAtom( mainInterface->toplevel() );
  argv[6] = p6.GetAtom( mainInterface->toplevel() );
  argv[7] = p7.GetAtom( mainInterface->toplevel() );
  argv[8] = p8.GetAtom( mainInterface->toplevel() );
  argv[9] = p9.GetAtom( mainInterface->toplevel() );
  argv[10] = p10.GetAtom( mainInterface->toplevel() );
  argv[11] = p11.GetAtom( mainInterface->toplevel() );
  avmplus::FlashScriptObject::CallMethodI( mainInterface, method, 11, argv, result );
  return result;
}

avmplus::Atom FlashInterface::CallMethodI( const char * method, const FVar& p1, const FVar& p2, const FVar& p3, const FVar& p4, const FVar& p5, const FVar& p6, const FVar& p7, const FVar& p8, const FVar& p9 , const FVar& p10, const FVar& p11, const FVar& p12)
{
  FLASH_INTERFACE_ENTER_FUNCTION( 12 );
  avmplus::Atom result;
  argv[1] = p1.GetAtom( mainInterface->toplevel() );
  argv[2] = p2.GetAtom( mainInterface->toplevel() );
  argv[3] = p3.GetAtom( mainInterface->toplevel() );
  argv[4] = p4.GetAtom( mainInterface->toplevel() );
  argv[5] = p5.GetAtom( mainInterface->toplevel() );
  argv[6] = p6.GetAtom( mainInterface->toplevel() );
  argv[7] = p7.GetAtom( mainInterface->toplevel() );
  argv[8] = p8.GetAtom( mainInterface->toplevel() );
  argv[9] = p9.GetAtom( mainInterface->toplevel() );
  argv[10] = p10.GetAtom( mainInterface->toplevel() );
  argv[11] = p11.GetAtom( mainInterface->toplevel() );
  argv[12] = p12.GetAtom( mainInterface->toplevel() );
  avmplus::FlashScriptObject::CallMethodI( mainInterface, method, 12, argv, result );
  return result;
}

avmplus::Atom FlashInterface::CallMethodI( const char * method, const FVar& p1, const FVar& p2, const FVar& p3, const FVar& p4, const FVar& p5, const FVar& p6, const FVar& p7, const FVar& p8, const FVar& p9, const FVar& p10, const FVar& p11, const FVar& p12, const FVar& p13 )
{
	FLASH_INTERFACE_ENTER_FUNCTION( 13 );
	avmplus::Atom result;
	argv[1] = p1.GetAtom( mainInterface->toplevel() );
	argv[2] = p2.GetAtom( mainInterface->toplevel() );
	argv[3] = p3.GetAtom( mainInterface->toplevel() );
	argv[4] = p4.GetAtom( mainInterface->toplevel() );
	argv[5] = p5.GetAtom( mainInterface->toplevel() );
	argv[6] = p6.GetAtom( mainInterface->toplevel() );
	argv[7] = p7.GetAtom( mainInterface->toplevel() );
	argv[8] = p8.GetAtom( mainInterface->toplevel() );
	argv[9] = p9.GetAtom( mainInterface->toplevel() );
	argv[10] = p10.GetAtom( mainInterface->toplevel() );
	argv[11] = p11.GetAtom( mainInterface->toplevel() );
	argv[12] = p12.GetAtom( mainInterface->toplevel() );
	argv[13] = p13.GetAtom( mainInterface->toplevel() );
	avmplus::FlashScriptObject::CallMethodI( mainInterface, method, 13, argv, result );
	return result;
}

avmplus::Atom FlashInterface::CallMethodI( const char * method, const FVar& p1, const FVar& p2, const FVar& p3, const FVar& p4, const FVar& p5, const FVar& p6, const FVar& p7, const FVar& p8, const FVar& p9, const FVar& p10, const FVar& p11, const FVar& p12, const FVar& p13, const FVar& p14 )
{
	FLASH_INTERFACE_ENTER_FUNCTION( 14 );
	avmplus::Atom result;
	argv[1] = p1.GetAtom( mainInterface->toplevel() );
	argv[2] = p2.GetAtom( mainInterface->toplevel() );
	argv[3] = p3.GetAtom( mainInterface->toplevel() );
	argv[4] = p4.GetAtom( mainInterface->toplevel() );
	argv[5] = p5.GetAtom( mainInterface->toplevel() );
	argv[6] = p6.GetAtom( mainInterface->toplevel() );
	argv[7] = p7.GetAtom( mainInterface->toplevel() );
	argv[8] = p8.GetAtom( mainInterface->toplevel() );
	argv[9] = p9.GetAtom( mainInterface->toplevel() );
	argv[10] = p10.GetAtom( mainInterface->toplevel() );
	argv[11] = p11.GetAtom( mainInterface->toplevel() );
	argv[12] = p12.GetAtom( mainInterface->toplevel() );
	argv[13] = p13.GetAtom( mainInterface->toplevel() );
	argv[14] = p14.GetAtom( mainInterface->toplevel() );
	avmplus::FlashScriptObject::CallMethodI( mainInterface, method, 14, argv, result );
	return result;
}
avmplus::Atom FlashInterface::CallMethodI( const char * method, const FVar& p1, const FVar& p2, const FVar& p3, const FVar& p4, const FVar& p5, const FVar& p6, const FVar& p7, const FVar& p8, const FVar& p9, const FVar& p10, const FVar& p11, const FVar& p12, const FVar& p13, const FVar& p14, const FVar& p15 )
{
  FLASH_INTERFACE_ENTER_FUNCTION( 15 );
  avmplus::Atom result;
  argv[1] = p1.GetAtom( mainInterface->toplevel() );
  argv[2] = p2.GetAtom( mainInterface->toplevel() );
  argv[3] = p3.GetAtom( mainInterface->toplevel() );
  argv[4] = p4.GetAtom( mainInterface->toplevel() );
  argv[5] = p5.GetAtom( mainInterface->toplevel() );
  argv[6] = p6.GetAtom( mainInterface->toplevel() );
  argv[7] = p7.GetAtom( mainInterface->toplevel() );
  argv[8] = p8.GetAtom( mainInterface->toplevel() );
  argv[9] = p9.GetAtom( mainInterface->toplevel() );
  argv[10] = p10.GetAtom( mainInterface->toplevel() );
  argv[11] = p11.GetAtom( mainInterface->toplevel() );
  argv[12] = p12.GetAtom( mainInterface->toplevel() );
  argv[13] = p13.GetAtom( mainInterface->toplevel() );
  argv[14] = p14.GetAtom( mainInterface->toplevel() );
  argv[15] = p15.GetAtom( mainInterface->toplevel() );
  avmplus::FlashScriptObject::CallMethodI( mainInterface, method, 15, argv, result );
  return result;
}

avmplus::Atom FlashInterface::CallMethodI( const char * method, const FVar& p1, const FVar& p2, const FVar& p3, const FVar& p4, const FVar& p5, const FVar& p6, const FVar& p7, const FVar& p8, const FVar& p9, const FVar& p10, const FVar& p11, const FVar& p12, const FVar& p13, const FVar& p14, const FVar& p15, const FVar& p16 )
{
  FLASH_INTERFACE_ENTER_FUNCTION( 16 );
  avmplus::Atom result;
  argv[1] = p1.GetAtom( mainInterface->toplevel() );
  argv[2] = p2.GetAtom( mainInterface->toplevel() );
  argv[3] = p3.GetAtom( mainInterface->toplevel() );
  argv[4] = p4.GetAtom( mainInterface->toplevel() );
  argv[5] = p5.GetAtom( mainInterface->toplevel() );
  argv[6] = p6.GetAtom( mainInterface->toplevel() );
  argv[7] = p7.GetAtom( mainInterface->toplevel() );
  argv[8] = p8.GetAtom( mainInterface->toplevel() );
  argv[9] = p9.GetAtom( mainInterface->toplevel() );
  argv[10] = p10.GetAtom( mainInterface->toplevel() );
  argv[11] = p11.GetAtom( mainInterface->toplevel() );
  argv[12] = p12.GetAtom( mainInterface->toplevel() );
  argv[13] = p13.GetAtom( mainInterface->toplevel() );
  argv[14] = p14.GetAtom( mainInterface->toplevel() );
  argv[15] = p15.GetAtom( mainInterface->toplevel() );
  argv[16] = p16.GetAtom( mainInterface->toplevel() );
  avmplus::FlashScriptObject::CallMethodI( mainInterface, method, 16, argv, result );
  return result;
}

avmplus::Atom FlashInterface::CallMethodI( const char * method, const FVar& p1, const FVar& p2, const FVar& p3, const FVar& p4, const FVar& p5, const FVar& p6, const FVar& p7, const FVar& p8, const FVar& p9, const FVar& p10, const FVar& p11, const FVar& p12, const FVar& p13, const FVar& p14, const FVar& p15, const FVar& p16, const FVar& p17 )
{
  FLASH_INTERFACE_ENTER_FUNCTION( 17 );
  avmplus::Atom result;
  argv[1] = p1.GetAtom( mainInterface->toplevel() );
  argv[2] = p2.GetAtom( mainInterface->toplevel() );
  argv[3] = p3.GetAtom( mainInterface->toplevel() );
  argv[4] = p4.GetAtom( mainInterface->toplevel() );
  argv[5] = p5.GetAtom( mainInterface->toplevel() );
  argv[6] = p6.GetAtom( mainInterface->toplevel() );
  argv[7] = p7.GetAtom( mainInterface->toplevel() );
  argv[8] = p8.GetAtom( mainInterface->toplevel() );
  argv[9] = p9.GetAtom( mainInterface->toplevel() );
  argv[10] = p10.GetAtom( mainInterface->toplevel() );
  argv[11] = p11.GetAtom( mainInterface->toplevel() );
  argv[12] = p12.GetAtom( mainInterface->toplevel() );
  argv[13] = p13.GetAtom( mainInterface->toplevel() );
  argv[14] = p14.GetAtom( mainInterface->toplevel() );
  argv[15] = p15.GetAtom( mainInterface->toplevel() );
  argv[16] = p16.GetAtom( mainInterface->toplevel() );
  argv[17] = p17.GetAtom( mainInterface->toplevel() );
  avmplus::FlashScriptObject::CallMethodI( mainInterface, method, 17, argv, result );
  return result;
}

avmplus::Atom FlashInterface::CallMethodI( const char * method, const FVar& p1, const FVar& p2, const FVar& p3, const FVar& p4, const FVar& p5, const FVar& p6, const FVar& p7, const FVar& p8,  const FVar& p9, const FVar& p10, const FVar& p11, const FVar& p12, const FVar& p13, const FVar& p14, const FVar& p15, const FVar& p16, const FVar& p17, const FVar& p18 )
{
  FLASH_INTERFACE_ENTER_FUNCTION( 18 );
  avmplus::Atom result;
  argv[1] = p1.GetAtom( mainInterface->toplevel() );
  argv[2] = p2.GetAtom( mainInterface->toplevel() );
  argv[3] = p3.GetAtom( mainInterface->toplevel() );
  argv[4] = p4.GetAtom( mainInterface->toplevel() );
  argv[5] = p5.GetAtom( mainInterface->toplevel() );
  argv[6] = p6.GetAtom( mainInterface->toplevel() );
  argv[7] = p7.GetAtom( mainInterface->toplevel() );
  argv[8] = p8.GetAtom( mainInterface->toplevel() );
  argv[9] = p9.GetAtom( mainInterface->toplevel() );
  argv[10] = p10.GetAtom( mainInterface->toplevel() );
  argv[11] = p11.GetAtom( mainInterface->toplevel() );
  argv[12] = p12.GetAtom( mainInterface->toplevel() );
  argv[13] = p13.GetAtom( mainInterface->toplevel() );
  argv[14] = p14.GetAtom( mainInterface->toplevel() );
  argv[15] = p15.GetAtom( mainInterface->toplevel() );
  argv[16] = p16.GetAtom( mainInterface->toplevel() );
  argv[17] = p17.GetAtom( mainInterface->toplevel() );
  argv[18] = p18.GetAtom( mainInterface->toplevel() );
  avmplus::FlashScriptObject::CallMethodI( mainInterface, method, 18, argv, result );
  return result;
}

avmplus::Atom FlashInterface::CallMethodI( const char * method, const FVar& p1, const FVar& p2, const FVar& p3, const FVar& p4, const FVar& p5, const FVar& p6, const FVar& p7, const FVar& p8,  const FVar& p9, const FVar& p10, const FVar& p11, const FVar& p12, const FVar& p13, const FVar& p14, const FVar& p15, const FVar& p16, const FVar& p17, const FVar& p18, const FVar& p19 )
{
  FLASH_INTERFACE_ENTER_FUNCTION( 19 );
  avmplus::Atom result;
  argv[1] = p1.GetAtom( mainInterface->toplevel() );
  argv[2] = p2.GetAtom( mainInterface->toplevel() );
  argv[3] = p3.GetAtom( mainInterface->toplevel() );
  argv[4] = p4.GetAtom( mainInterface->toplevel() );
  argv[5] = p5.GetAtom( mainInterface->toplevel() );
  argv[6] = p6.GetAtom( mainInterface->toplevel() );
  argv[7] = p7.GetAtom( mainInterface->toplevel() );
  argv[8] = p8.GetAtom( mainInterface->toplevel() );
  argv[9] = p9.GetAtom( mainInterface->toplevel() );
  argv[10] = p10.GetAtom( mainInterface->toplevel() );
  argv[11] = p11.GetAtom( mainInterface->toplevel() );
  argv[12] = p12.GetAtom( mainInterface->toplevel() );
  argv[13] = p13.GetAtom( mainInterface->toplevel() );
  argv[14] = p14.GetAtom( mainInterface->toplevel() );
  argv[15] = p15.GetAtom( mainInterface->toplevel() );
  argv[16] = p16.GetAtom( mainInterface->toplevel() );
  argv[17] = p17.GetAtom( mainInterface->toplevel() );
  argv[18] = p18.GetAtom( mainInterface->toplevel() );
  argv[19] = p19.GetAtom( mainInterface->toplevel() );
  avmplus::FlashScriptObject::CallMethodI( mainInterface, method, 19, argv, result );
  return result;
}

avmplus::Atom FlashInterface::CallMethodI( const char * method, const FVar& p1, const FVar& p2, const FVar& p3, const FVar& p4, const FVar& p5, const FVar& p6, const FVar& p7, const FVar& p8,  const FVar& p9, const FVar& p10, const FVar& p11, const FVar& p12, const FVar& p13, const FVar& p14, const FVar& p15, const FVar& p16, const FVar& p17, const FVar& p18, const FVar& p19, const FVar& p20 )
{
  FLASH_INTERFACE_ENTER_FUNCTION( 20 );
  avmplus::Atom result;
  argv[1] = p1.GetAtom( mainInterface->toplevel() );
  argv[2] = p2.GetAtom( mainInterface->toplevel() );
  argv[3] = p3.GetAtom( mainInterface->toplevel() );
  argv[4] = p4.GetAtom( mainInterface->toplevel() );
  argv[5] = p5.GetAtom( mainInterface->toplevel() );
  argv[6] = p6.GetAtom( mainInterface->toplevel() );
  argv[7] = p7.GetAtom( mainInterface->toplevel() );
  argv[8] = p8.GetAtom( mainInterface->toplevel() );
  argv[9] = p9.GetAtom( mainInterface->toplevel() );
  argv[10] = p10.GetAtom( mainInterface->toplevel() );
  argv[11] = p11.GetAtom( mainInterface->toplevel() );
  argv[12] = p12.GetAtom( mainInterface->toplevel() );
  argv[13] = p13.GetAtom( mainInterface->toplevel() );
  argv[14] = p14.GetAtom( mainInterface->toplevel() );
  argv[15] = p15.GetAtom( mainInterface->toplevel() );
  argv[16] = p16.GetAtom( mainInterface->toplevel() );
  argv[17] = p17.GetAtom( mainInterface->toplevel() );
  argv[18] = p18.GetAtom( mainInterface->toplevel() );
  argv[19] = p19.GetAtom( mainInterface->toplevel() );
  argv[20] = p20.GetAtom( mainInterface->toplevel() );
  avmplus::FlashScriptObject::CallMethodI( mainInterface, method, 20, argv, result );
  return result;
}

}

NI_DEFINE_REFCOUNT( UI::FlashInterface )