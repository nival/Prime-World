#include "TamarinPCH.h"

#include "../../FlashMovie.h"

#include "Timer.h"
#include "UtilsScripts.h"

namespace avmplus
{

  void UtilsScripts::clearInterval( ScriptObject* self, uint id )
  {
    NI_ASSERT(self, "self is NULL");

    flash::FlashMovieAvmCore * flashCore = (flash::FlashMovieAvmCore *) self->core();

    flashCore->GetMovie()->UnsubscribeForAdvanceByID( id );
  }

  void UtilsScripts::clearTimeout( ScriptObject* self, uint id )
  {
    NI_ASSERT(self, "self is NULL");

    flash::FlashMovieAvmCore * flashCore = (flash::FlashMovieAvmCore *) self->core();

    flashCore->GetMovie()->UnsubscribeForAdvanceByID( id );
  }

  XMLObject * UtilsScripts::describeType( ScriptObject* self, AvmBox value )
  {
    NI_ALWAYS_ASSERT( "Not yet implemented" );
    return (XMLObject *)0;
  }

  avmplus::AvmString UtilsScripts::escapeMultiByte( ScriptObject* self, AvmString value )
  {
    NI_ALWAYS_ASSERT( "Not yet implemented" );
    return (AvmString)0;
  }

  avmplus::AvmBox UtilsScripts::getDefinitionByName( ScriptObject* self,  AvmString name )
  {
    flash::FlashMovieAvmCore * flashCore = (flash::FlashMovieAvmCore*) self->core();
    ClassClosure* testClass = flashCore->GetClassByNameAVM( name );

    if ( testClass )
      return testClass->atom();

    return nullObjectAtom;
  }

  avmplus::AvmString UtilsScripts::getQualifiedClassName(ScriptObject* self,  AvmBox value )
  {
    return DescribeTypeClass::getQualifiedClassName( self, value );
  }

  avmplus::AvmString UtilsScripts::getQualifiedSuperclassName(ScriptObject* self,  AvmBox value )
  {
    return DescribeTypeClass::getQualifiedSuperclassName( self, value );
  }

  int UtilsScripts::getTimer(ScriptObject* self)
  {
    NI_ASSERT(self, "self is NULL");
    
    flash::FlashMovieAvmCore * flashCore = (flash::FlashMovieAvmCore *) self->core();

    return (int)(flashCore->GetMovie()->GetTimeFromStart() * 1000.0);
  }

  static uint StartInnerTimer(ScriptObject* self,  FunctionObject* closure, double delay, int repeatCount )
  {
    static int nextTimerID = 1;

    NI_ASSERT(self, "self is NULL");

    flash::FlashMovieAvmCore * flashCore = (flash::FlashMovieAvmCore*) self->core();

    TimerClass* timerClass = flashCore->GetClassCache().GetClass<TimerClass>( EFlashClassID::TimerClass );

    Atom params[3];

    params[1] = self->core()->doubleToAtom( delay );
    params[2] = self->core()->intToAtom( repeatCount );

    Atom newTimerAtom = timerClass->construct( 2, params );

    TimerObject* newTimer = dynamic_cast<TimerObject*>( AvmCore::atomToScriptObject( newTimerAtom ) );

    if ( newTimer )
    {
      newTimer->SetTimerID( nextTimerID );
      newTimer->_start( delay, closure );
      nextTimerID++;

      return nextTimerID;
    }

    return 0;
  }

  uint UtilsScripts::setInterval(ScriptObject* self,  FunctionObject* closure, double delay, AvmBox arguments)
  {
    return StartInnerTimer( self, closure, delay, 0 );
  }

  uint UtilsScripts::setTimeout(ScriptObject* self,  FunctionObject* closure, double delay, AvmBox arguments )
  {
    return StartInnerTimer( self, closure, delay, 1 );
  }

  avmplus::AvmString UtilsScripts::unescapeMultiByte(ScriptObject* self,  AvmString value )
  {
    NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "UtilsScripts", "unescapeMultiByte" );
    return (AvmString)0;
  }

  AvmBox UtilsScripts::trace( ScriptObject* self, AvmBox* argv, int argc )
  {
    nstl::string text;

    for ( int i = 0; i < argc; ++i )
    {
      StUTF8String message( self->core()->string( argv[i] ) );
      text += message.c_str();
      text += " ";
    }

    DebugTrace(" TRACE FROM FLASH %s", text.c_str() );

    return (AvmBox)0;    
  }
}