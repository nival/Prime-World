#pragma once

#include <set>

#pragma warning( push )
#pragma warning( disable : 4996 ) //warning C4996: This function or variable may be unsafe

namespace simple_parser
{


struct Context
{
  const char *        ptr;
  const char *        errorPtr;
  string              errorMsg;

  Context( const char * _text ) : ptr( _text ), errorPtr( 0 ) {}

  bool Ok() const { return !errorPtr; }

private:
  void operator = ( const Context & ) {}
};



class Parser
{
public:
  Parser() {}

protected:

  static const char * SkipSpaces( const char * _p )
  {
    while ( *_p == ' ' || *_p == '\t' || *_p == '\r' || *_p == '\n' )
      ++_p;
    return _p;
  }

  static const char * PeekSymbol( const Context & _ctx, const char * _sym )
  {
    int l = strlen( _sym );
    NI_ASSERT( l > 0 && l < 32, "" );

    char fmt[32] = "";
    sprintf( fmt, "%%%ds%%n", l );

    char buf[32] = "";
    int pos = 0;
    if ( ( sscanf( _ctx.ptr, fmt, buf, &pos ) == 1 ) )
      if ( !strcmp( buf, _sym ) )
        return _ctx.ptr + pos;

    return 0;
  }



  static bool PopSymbol( Context & _ctx, const char * _sym )
  {
    const char * endPtr = PeekSymbol( _ctx, _sym );
    if ( endPtr )
    {
      _ctx.ptr = endPtr;
      return true;
    }

    return false;
  }



  static const char * PeekWord( string & _word, Context & _ctx )
  {
    const char * p = SkipSpaces( _ctx.ptr );

    char buf[256] = "";
    int pos = 0;
    if ( sscanf( p, "%255[a-zA-Z_]%n", buf, &pos ) == 1 )
    {
      _word = buf;
      return p + pos;
    }

    return 0;
  }



  static bool PopWord( string & _word, Context & _ctx )
  {
    const char * endPtr = PeekWord( _word, _ctx );
    if ( endPtr )
    {
      _ctx.ptr = endPtr;
      return true;
    }

    return false;
  }



  static bool ForceWord( string & _word, Context & _ctx )
  {
    if ( PopWord( _word, _ctx ) )
      return true;
    return HandleError( _ctx, "Word expected" );
  }



  static bool ForceSpecificWord( Context & _ctx, const string & _word )
  {
    string word;
    if ( PopWord( word, _ctx ) )
      if ( word == _word )
        return true;
    return HandleErrorf( _ctx, "Word '%s' expected", _word.c_str() );
  }


  template <class TValue>
  static bool ParseValue( TValue & _val, Context & _ctx )
  {
    const char * p = SkipSpaces( _ctx.ptr );

    char buf[256] = "";
    int pos = 0;
    if ( sscanf( p, "%255[a-zA-Z_0-9.]%n", buf, &pos ) == 1 )
    {
      p += pos;
      if ( simple_parser::ParseSingleValue( _val, buf ) )
      {
        _ctx.ptr = p;
        return true;
      }
    }

    _ctx.errorPtr = p;
    return false;
  }



  static bool HandleError( Context & _ctx ) {
    _ctx.errorPtr = _ctx.ptr;
    return false;
  }


  static bool HandleError( Context & _ctx, const char * _errorMsg ) {
    _ctx.errorPtr = _ctx.ptr;
    _ctx.errorMsg = _errorMsg;
    return false;
  }


  static bool HandleErrorf( Context & _ctx, const char * _errorMsgFmt, ... ) {
    char buf[256] = "";
    va_list va;
    va_start( va, _errorMsgFmt );
    vsprintf_s( buf, _errorMsgFmt, va );
    va_end(va);

    _ctx.errorPtr = _ctx.ptr;
    _ctx.errorMsg = buf;
    return false;
  }


  static bool ForceSymbol( Context & _ctx, const char * _sym )
  {
    if ( PopSymbol( _ctx, _sym ) )
      return true;
    return HandleErrorf( _ctx, "Symbol '%s' expected", _sym );
  }


  template <class TValue>
  static bool ForceValue( TValue & _val, Context & _ctx )
  {
    if ( ParseValue( _val, _ctx ) )
      return true;
    return HandleError( _ctx, "Values expected" );
  }
};



template <class TValue, class TStorage>
class TValueStorage : public Parser, public TStorage
{
public:
  TValueStorage() {}

  bool Parse( Context & _ctx )
  {
    Clear();

    if ( PopSymbol( _ctx, OpeningSymbol() ) )
    {
      while ( true )
      {
        if ( CanBeFinished() )
          if ( PopSymbol( _ctx, ClosingSymbol() ) )
            return true;

        if ( HaveToBeFinished() )
          return HandleError( _ctx, "Too many values" );

        if ( !Empty() )
        {
          if ( !ForceSymbol( _ctx, Separator() ) )
            return false;
        }
        
        TValue v;
        if ( !ForceValue( v, _ctx ) )
          return false;

        if ( !AddValue( v ) )
          return HandleError( _ctx, "Value cannot be added" );
      }
    }
    else
    {
      TValue v;
      if ( !ForceValue( v, _ctx ) )
        return false;
      SetValue( v );
      return true;
    }
  }
};



struct TStorageBase
{
  const char * OpeningSymbol() const { return "["; }
  const char * ClosingSymbol() const { return "]"; }
  const char * Separator() const { return ","; }
  bool CanBeFinished() const { return true; }
  bool HaveToBeFinished() const { return false; }
};



template <class TValue>
struct TValuesSetStorage : public TStorageBase, public std::set<TValue>
{
  TValuesSetStorage() {}

  const char * OpeningSymbol() const { return "{"; }
  const char * ClosingSymbol() const { return "}"; }
  void Clear() { clear(); }
  bool Empty() const { return empty(); }

  bool AddValue( const TValue & _v ) {
    std::pair<std::set<TValue>::iterator, bool> result = insert( _v );
    return result.second;
  }

  void SetValue( const TValue & _v ) { insert( _v ); }
};



template <class TValue>
struct TValuesVectorStorage : public TStorageBase, public vector<TValue>
{
  TValuesVectorStorage() {}

  const char * OpeningSymbol() const { return "{"; }
  const char * ClosingSymbol() const { return "}"; }
  void Clear() { clear(); }
  bool Empty() const { return empty(); }

  bool AddValue( const TValue & _v ) { push_back( _v ); return true; }
  void SetValue( const TValue & _v ) { push_back( _v ); }
};



template <class TValue>
struct TValuesRangeStorage : public TStorageBase
{
  TValuesRangeStorage() : from(), to(), valuesSet( 0 ) {}

  void Clear() { valuesSet = 0; from = TValue(); to = TValue(); }
  bool Empty() const { return valuesSet == 0; }
  bool CanBeFinished() const { return valuesSet >= 2; }
  bool HaveToBeFinished() const { return valuesSet >= 2; }

  bool AddValue( const TValue & _v ) {
    if ( valuesSet == 0 ) {
      from = _v;
      valuesSet = 1;
    } else if ( valuesSet == 1 ) {
      to = _v;
      valuesSet = 2;
    } else
      return false;
    return true;
  }

  void SetValue( const TValue & _v ) {
    from = to = _v;
    valuesSet = 1;
  }

  TValue Delta() const { return to - from; }

  TValue from, to;
  int valuesSet;
};



template <class TValue>
class ValuesSet : public TValueStorage<TValue, TValuesSetStorage<TValue>>
{
public:
  ValuesSet() {}
};



template <class TValue>
class ValuesVector : public TValueStorage<TValue, TValuesVectorStorage<TValue>>
{
public:
  ValuesVector() {}
};



template <class TValue>
class ValuesRange : public TValueStorage<TValue, TValuesRangeStorage<TValue>>
{
public:
  ValuesRange() {}
};



bool ParseSingleValue( int & _val, const char * _text )
{
  return sscanf( _text, "%d", &_val ) == 1;
}


bool ParseSingleValue( float & _val, const char * _text )
{
  return sscanf( _text, "%f", &_val ) == 1;
}


bool ParseSingleValue( double & _val, const char * _text )
{
  return sscanf( _text, "%lf", &_val ) == 1;
}


bool ParseSingleValue( string & _val, const char * _text )
{
  _val = _text;
  return true;
}

#pragma warning( pop )

} //namespace simple_parser
