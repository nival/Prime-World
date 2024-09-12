#include "TamarinPCH.h"

#include "FlashBaseClasses.h"


namespace avmplus
{

void FlashScriptObject::SetPropertyByName( Stringp _property, Atom _value )
{
  SetPropertyToObject(this, _property, _value);
}

void SetPropertyToObject( ScriptObject* _scriptObject, Stringp _property, Atom _value )
{
  if (!_scriptObject || !_property)
    return;

  Multiname qname( _scriptObject->core()->getAnyPublicNamespace(), _property );

  if ( _scriptObject->vtable->toplevel()->hasproperty( _scriptObject->atom(), &qname, _scriptObject->vtable ) )
  {
    _scriptObject->vtable->toplevel()->setproperty( _scriptObject->atom(), &qname, _value, _scriptObject->vtable );
  }
  else
  {
    _scriptObject->setStringProperty( _property, _value );
  }
}



avmplus::Atom GetStringPropertyFromObject( ScriptObject* _scriptObject, Stringp _property )
{
  Multiname qname( _scriptObject->core()->getAnyPublicNamespace(), _property );

  if ( _scriptObject->toplevel()->hasproperty( _scriptObject->atom(), &qname, _scriptObject->vtable ) )
  {
    return _scriptObject->toplevel()->getproperty( _scriptObject->atom(), &qname, _scriptObject->vtable );
  }
  else
  {
    if ( _scriptObject->hasStringProperty( _property ) )
      return _scriptObject->getStringProperty( _property );
    else
      return nullObjectAtom;
  }
}

Atom GetMultinamePropertyFromObject( ScriptObject* _scriptObject, char const* name )
{
  Multiname qname( _scriptObject->core()->getAnyPublicNamespace(), _scriptObject->core()->internConstantStringLatin1( name ) );

  if ( _scriptObject->toplevel()->hasproperty( _scriptObject->atom(), &qname, _scriptObject->vtable ) )
  {
    return _scriptObject->toplevel()->getproperty( _scriptObject->atom(), &qname, _scriptObject->vtable );
  }
  else
  {
    if ( _scriptObject->hasMultinameProperty( &qname ) )
      return _scriptObject->getMultinameProperty( &qname );
    else
      return nullObjectAtom;
  }
}

bool FlashScriptObject::PropertyIsNotNull( Stringp _property )
{
  Multiname qname( core()->getAnyPublicNamespace(), _property );

  Atom prop = undefinedAtom;

  if ( vtable->toplevel()->hasproperty( atom(), &qname, vtable ) )
    prop = vtable->toplevel()->getproperty( atom(), &qname, vtable );
  else if ( hasStringProperty( _property ) )
    prop = getStringProperty( _property );

  return AvmCore::isObject( prop );
}

Stringp FlashScriptObject::GetPropertyTypeName( Stringp _property )
{
  Multiname qname( core()->getAnyPublicNamespace(), _property );

  Traits* traits = vtable->traits;
  Toplevel* toplevel = vtable->toplevel();
  Binding binding = toplevel->getBinding( traits, &qname );
  const TraitsBindingsp traitsBindings = traits->getTraitsBindings();

  int slotId = avmplus::AvmCore::bindingToSlotId( binding );

  Traits* slotTraits =  traitsBindings->getSlotTraits( slotId );

  return slotTraits->name();
}

int FlashScriptObject::GetSlotID( ScriptObject* _object, const char* _property )
{
  Multiname qname( _object->core()->getAnyPublicNamespace(), _object->core()->internConstantStringLatin1( _property ) );

  Traits* traits = _object->vtable->traits;
  Toplevel* toplevel = _object->vtable->toplevel();
  Binding binding = toplevel->getBinding( traits, &qname );

  if ( !binding )
    return -1;

  return avmplus::AvmCore::bindingToSlotId( binding );
}


int FlashScriptObject::GetSlotID( const char* _property )
{
  return GetSlotID( this, _property );
}

void CollectPropertiesFromObject( ScriptObject* _scriptObject, nstl::list<nstl::string>& _proplist )
{
  if (!_scriptObject)
    return;

  avmplus::Traits* traits = _scriptObject->traits();

  avmplus::TraitsBindingsp traitsBindings = traits->getTraitsBindings();
  avmplus::StTraitsBindingsIterator iter(traitsBindings);
  while (iter.next())
  {
    avmplus::Stringp name = iter.key();
    if (!name) continue;

    Atom propValue = GetStringPropertyFromObject( _scriptObject, name );
    if (_scriptObject->core()->isString(propValue))
    {
      StUTF8String nextFieldConv( name );
      _proplist.push_back( nextFieldConv.c_str() );
    }
  }
}

bool FlashScriptObject::CallMethod( const char * path, char const* name )
{
  ScriptObject* object = FindChild( this, path );

  if ( object )
  {
    Atom argv[] = { this->atom() };
    Atom result;
    return CallMethodI( object, name, 0, argv, result );
  }
  else
    return false;
}

bool FlashScriptObject::CallMethod( const char * path, char const* name, const char* arg1 )
{
  ScriptObject* object = FindChild( this, path );

  if ( object )
  {
    Atom argv[] = { this->atom(), core()->newStringLatin1( arg1 )->atom() };
    Atom result;
    return CallMethodI( object, name, 1, argv, result );
  }
  else
    return false;
}

bool FlashScriptObject::CallMethod( const char * path, char const* name, const char* arg1, const char* arg2 )
{
  ScriptObject* object = FindChild( this, path );

  if ( object )
  {
    Atom argv[] = { this->atom(), core()->newStringLatin1( arg1 )->atom() , core()->newStringLatin1( arg2 )->atom() };
    Atom result;
    return CallMethodI( object, name, 2, argv, result );
  }
  else
    return false;
}

bool FlashScriptObject::CallMethod( const char * path, char const* name, int arg1, int arg2 )
{
  ScriptObject* object = FindChild( this, path );

  if ( object )
  {
    Atom argv[] = { this->atom(),core()->intToAtom(arg1), core()->intToAtom(arg2) };
    Atom result;
    return CallMethodI( object, name, 2, argv, result );
  }
  else
    return false;
}

bool FlashScriptObject::CallMethod( const char * path, char const* name, const vector<Atom> & args )
{
  ScriptObject* object = FindChild( this, path );

  if ( object )
  {
    vector<Atom> argv(args.size()+1); 
    argv[0] = this->atom();
    
    //TODO memcpy may be?
    for(int i=0; i<args.size();i++)
      argv[i+1] = args[i];
    
    Atom result;

    return CallMethodI( object, name, args.size(), &(argv[0]), result );
  }
  else
    return false;
}

ScriptObject* FlashScriptObject::FindChild( ScriptObject* _parentObject, const char * path )
{
  if ( !path )
    return _parentObject;

  if ( !path[0] )
    return _parentObject;

  const char* nextPos = strchr( path, '.' );

  if ( nextPos )
  {
    char pathPart[1000];
    strncpy_s( pathPart, path, nextPos - path );
    pathPart[ nextPos - path ] = 0;
    ScriptObject* next = _parentObject->core()->atomToScriptObject( GetMultinamePropertyFromObject( _parentObject, pathPart ) );
    
    if ( next )
      return FindChild( next, nextPos + 1 );
    else
      return 0;
  }
  else
  {
    return _parentObject->core()->atomToScriptObject( GetMultinamePropertyFromObject( _parentObject, path ) );
  }
}

bool FlashScriptObject::CallMethodI( ScriptObject* _scriptObject, char const* name, int argc, Atom argv[], Atom& result )
{
  using avmplus::ExceptionFrame;
  using avmplus::Exception;

  if (!_scriptObject)
    return false;

  Multiname qname( _scriptObject->core()->getAnyPublicNamespace(), _scriptObject->core()->internConstantStringLatin1( name ) );

  TRY( _scriptObject->core(), avmplus::kCatchAction_ReportAsError )
  {
    if ( _scriptObject->hasMultinameProperty( &qname ) )
      result = _scriptObject->callProperty( &qname, argc, argv );
    else
      result = _scriptObject->toplevel()->callproperty( _scriptObject->atom(), &qname, argc, argv, _scriptObject->vtable );
  }
  CATCH ( Exception *exception )
  {
    NI_ALWAYS_ASSERT(NStr::StrFmt("exception in AS in method %s: %s", name, StUTF8String(_scriptObject->core()->string(exception->atom)).c_str()));
    //FlashCore()->PrintException(exception);
  }
  END_CATCH
  END_TRY
  
  return true;
}




}