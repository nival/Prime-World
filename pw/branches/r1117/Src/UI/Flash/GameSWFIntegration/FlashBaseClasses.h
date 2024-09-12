#pragma once

#include "FlashMovieAvmCore.h"


namespace avmplus
{


Atom GetStringPropertyFromObject( ScriptObject* _scriptObject, Stringp _property );
void SetPropertyToObject(ScriptObject* _scriptObject, Stringp _property, Atom _value );

void CollectPropertiesFromObject( ScriptObject* _scriptObject, nstl::list<nstl::string>& _proplist );
Atom GetMultinamePropertyFromObject( ScriptObject* _scriptObject, char const* name );

//NOTE that for now they are almost the same. can we exclude the common code?
class FlashScriptObject: public ScriptObject
{
public:
  FlashScriptObject(VTable* vtable, ScriptObject* delegate):ScriptObject(vtable, delegate) {}

  flash::FlashMovieAvmCore * FlashCore() { return (flash::FlashMovieAvmCore*) core(); }

  // It is slow. Better to cache slotId if possible
  void SetPropertyByName( Stringp _property, Atom _value );

  int  GetSlotID( const char* _property );
  static int GetSlotID( ScriptObject* _object, const char* _property );

  bool PropertyIsNotNull( Stringp _property );

  Stringp GetPropertyTypeName( Stringp _property );
   
  bool CallMethod( const char * path, char const* name, const vector<Atom> & args);
  bool CallMethod( const char * path, char const* name );
  bool CallMethod( const char * path, char const* name, const char* arg1 );
  bool CallMethod( const char * path, char const* name, const char* arg1, const char* arg2 );
  bool CallMethod( const char * path, char const* name, int arg1, int arg2 );

  static ScriptObject* FindChild( ScriptObject* _parentObject, const char * path );
  static bool CallMethodI( ScriptObject* _scriptObject, char const* name, int argc, Atom argv[], Atom& result );
//
//#ifdef DEBUGGER
//  virtual uint64 size() const {return 0;}
//#endif

private:
 

};

class FlashClassClosure: public ClassClosure
{
public:
  FlashClassClosure(VTable *cvtable):ClassClosure(cvtable) {}
  flash::FlashMovieAvmCore * FlashCore() {return (flash::FlashMovieAvmCore*) core();}
};

}