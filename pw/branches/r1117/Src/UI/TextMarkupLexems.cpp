#include "stdafx.h"

#include "TextMarkupLexems.h"


namespace NMarkup
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const static TChar TagOpenChar        = NMARKUP_STRING( '<' );
const static TChar TagCloseChar       = NMARKUP_STRING( '>' );
const static TChar TagCloseNameChar   = NMARKUP_STRING( '/' );
const static TChar TagValueChar       = NMARKUP_STRING( ':' );
const static TChar TagOptionChar      = NMARKUP_STRING( '=' );
const static TChar TagSkipValueChar   = NMARKUP_STRING( '=' );

const static TChar TagPlusSign        = NMARKUP_STRING( '+' );
const static TChar TagMinusSign       = NMARKUP_STRING( '-' );

const static TChar TagDotChar         = NMARKUP_STRING( '.' );


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Lexem::IsSpace( TChar c )
{
  return ( c == NMARKUP_STRING( ' ' ) ) || ( c == NMARKUP_STRING( '\t' ) ) || ( c == NMARKUP_STRING( '\r' ) ) || ( c == NMARKUP_STRING( '\n' ) );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TOffset Lexem::IsNewLine( TChar c0, TChar c1 )
{
  const TChar r = NMARKUP_STRING( '\r' ), n = NMARKUP_STRING( '\n' );

  if ( ( c0 == r ) && ( c1 == n ) )
    return 2;

  if ( ( c0 == r ) || ( c0 == n ) )
    return 1;

  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Lexem::IsNameChar( TChar c, bool firstSybmol )
{
  if( c >= NMARKUP_STRING( 'a' ) && c <= NMARKUP_STRING( 'z' ) )
    return true;
  if( c >= NMARKUP_STRING( 'A' ) && c <= NMARKUP_STRING( 'Z' ) )
    return true;
  if( c == NMARKUP_STRING( '_' ) )
    return true;
  if( !firstSybmol )
    if( c >= NMARKUP_STRING( '0' ) && c <= NMARKUP_STRING ('9' ) )
      return true;
  return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Lexem::IsNumeric( TChar c )
{
  if( c >= NMARKUP_STRING( '0' ) && c <= NMARKUP_STRING( '9' ) )
    return true;
  return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Lexem::DigitToNumber( TChar c )
{
  NI_ASSERT( IsNumeric( c ), "" );
  return c - NMARKUP_STRING( '0' );
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TOffset Lexem::ImplSkipSpaces( TOffset offset )
{
  NI_ASSERT( pText, "" );
  for( ; offset < pText->length(); ++offset )
    if( !IsSpace( (*pText)[offset] ) )
      break;
  return offset;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TOffset Lexem::ImplScanName( TOffset offset )
{
  NI_ASSERT( pText, "" );
  TOffset o = offset;
  for( ; o < pText->length(); ++o )
    if( !IsNameChar( (*pText)[o], o == offset ) )
      break;
  return o;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Lexem::ImplGetString( TString * str, TOffset _begin, TOffset _end ) const
{
  NI_ASSERT( pText, "" );
  NI_ASSERT( _end >= _begin, "" );
  str->assign( pText->c_str() + _begin, _end - _begin );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TString Lexem::ImplString( TOffset _begin, TOffset _end ) const
{
  TString str;
  ImplGetString( &str, _begin, _end );
  return str;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Lexem::ImplIs( const TChar * str, TOffset _begin, TOffset _end ) const
{
  NI_ASSERT( pText, "" );
  TOffset i = _begin;
  for( ; ( i < _end ) && *str; ++i, ++str )
    if( *str != (*pText)[i] )
      return false;
  return !*str && i == _end;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Lexem::ImplGetInt( TOffset _begin, TOffset _end, int defaultValue, int radix ) const
{
  if( _begin >= _end )
    return defaultValue;

  int value = 0;
  bool digits = false;
  int sign = +1;
  for( TOffset i = _begin; i < _end; ++i )
  {
    TChar c = pText->at( i );
    
    if( c == TagPlusSign || c == TagMinusSign )
    {
      if( digits )
        return defaultValue;
      if( c == TagMinusSign )
        sign = -sign;
    }
    else if( IsNumeric( c ) )
    {
      value = radix * value + DigitToNumber( c );
      digits = true;
    }
    else
      return defaultValue;
  }
  return value * sign;
}

float Lexem::ImplGetFloat( TOffset _begin, TOffset _end, float defaultValue, int radix ) const
{
  if( _begin >= _end )
    return defaultValue;

  float value = 0.f;
  bool digits = false;
  bool delemit = false;
  float sign = +1;
  TOffset i;

  for( i = _begin; i < _end; ++i )
  {
    TChar c = pText->at( i );
    if( c == TagPlusSign || c == TagMinusSign )
    {
      if( digits )
        return defaultValue;
      if( c == TagMinusSign )
        sign = -sign;
    }
    else if(c == TagDotChar)
    {
      delemit = true;
    }
    else if( IsNumeric( c ) )
    {
      //value = radix * value + DigitToNumber( c );
      digits = true;
    }
    else
      return defaultValue;
  }

  TString ptt = pText->substr( _begin, i );
  value = (float) _wtof(ptt.c_str());

  return value * sign;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Lexem::ImplGetBool( TOffset _begin, TOffset _end, bool defaultValue ) const
{
  if( ImplIs( NMARKUP_STRING( "on" ), _begin, _end ) )
    return true;
  if( ImplIs( NMARKUP_STRING( "off" ), _begin, _end ) )
    return false;
  return defaultValue;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Word::Read( const TString * text, TOffset _begin, bool tagsEnabled )
{
  if( !Lexem::Read( text, _begin ) )
    return false;

  for( ; end < pText->length(); ++end )
  {
    if( IsSpace( pText->at( end ) ) )
      break;

    if( tagsEnabled && ( pText->at( end ) == TagOpenChar ) )
    {
      if( end + 1 < pText->length() ) //check for double '<'
        if( pText->at( end + 1 ) == TagOpenChar )
        {
          ++end;
          continue;
        }
      break;
    }
  }

  return ( end > begin );
};



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Tag::Clear()
{
  Lexem::Clear();

  nameBegin = nameEnd = 0;
  valueBegin = valueEnd = 0;
  options.clear();
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Tag::Read( const TString * text, TOffset _begin )
{
  Clear();

  if( !Lexem::Read( text, _begin ) )
    return false;

  const TOffset length = pText->length();

  //check for opening '<'
  if( end >= length )
    return false;
  if( pText->at( end ) != TagOpenChar )
    return false;
  ++end;

  //Parse tag's name
  nameBegin = end;
  if( end < length && pText->at( end ) == TagCloseNameChar ) //Include '\' symbol
    ++end;
  nameEnd = end = ImplScanName( end );
  if( nameEnd <= nameBegin )
    return false; //Error

  end = ImplSkipSpaces( end );

  //skip value till the very end
  if( pText->at( end ) == TagSkipValueChar)
  {
    for( ; end < length; end ++ )
    {
      if( pText->at( end ) == TagCloseChar )
        return true;
    }
  }

  // possible ':' sign
  if( end >= length )
    return false; //Error
  if( pText->at( end ) == TagValueChar )
  {
    ++end;
    end = ImplSkipSpaces( end );
    //Scan value
    valueBegin = end;
    for( ; end < length; ++end )
      if( pText->at( end ) == TagCloseChar || IsSpace( pText->at( end ) ) )
        break;
    valueEnd = end;
    if( valueEnd <= valueBegin )
      return false; //Error
  }

  //Parse tag's options
  for( ; end < length; )
  {
    if( pText->at( end ) == TagCloseChar )
    {
      ++end;
      return true;
    }

    if( IsSpace( pText->at( end ) ) )
    {
      ++end;
      continue;
    }

    //option found, let's parse it
    SOption opt;

    //read option name
    opt.nameBegin = end;
    opt.nameEnd = end = ImplScanName( end );
    if( opt.nameEnd <= opt.nameBegin )
      return false; //Error

    end = ImplSkipSpaces( end );

    // '=' symbol
    if( end >= length )
      return false; //Error
    if( pText->at( end ) != TagOptionChar )
      return false; //Error
    ++end;

    end = ImplSkipSpaces( end );

    //read option value
    opt.valueBegin = end;
    for( ; end < length; ++end )
      if( pText->at( end ) == TagCloseChar || IsSpace( pText->at( end ) ) )
        break;
    opt.valueEnd = end;
    if( opt.valueEnd <= opt.valueBegin )
      return false; //Error

    options.push_back( opt );
  }

  return false;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Tag::GetOptionValue( const TChar * name, TString * str ) const
{
  for( TOffset i = 0; i < options.size(); ++i )
    if( OptionIs( i, name ) )
    {
      ImplGetString( str, options[i].valueBegin, options[i].valueEnd );
      return true;
    }
  return false;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Tag::GetOptionIntValue( TOffset index, int defaultValue, int radix ) const
{
  if( index < 0 || index >= (TOffset)options.size() )
    return defaultValue;
  const SOption & opt = options[ index ];

  return ImplGetInt( opt.valueBegin, opt.valueEnd, defaultValue, radix );
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Tag::GetOptionIntValue( const TChar * name, int defaultValue, int radix ) const
{
  for( TOffset i = 0; i < options.size(); ++i )
    if( OptionIs( i, name ) )
      return GetOptionIntValue( i, defaultValue, radix );
  return defaultValue;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float Tag::GetOptionFloatValue( const TChar * name, float defaultValue, int radix ) const
{
  for( TOffset i = 0; i < options.size(); ++i )
    if( OptionIs( i, name ) )
      return GetOptionFloatValue( i, defaultValue, radix );
  return defaultValue;
}

float Tag::GetOptionFloatValue( TOffset index, float defaultValue, int radix) const
{
  if( index < 0 || index >= (TOffset)options.size() )
    return defaultValue;
  const SOption & opt = options[ index ];

  return ImplGetFloat( opt.valueBegin, opt.valueEnd, defaultValue, radix );
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Tag::GetOptionBoolValue( TOffset index, bool defaultValue ) const
{
  if( index < 0 || index >= (TOffset)options.size() )
    return defaultValue;
  const SOption & opt = options[ index ];

  return ImplGetBool( opt.valueBegin, opt.valueEnd, defaultValue );
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Tag::GetOptionBoolValue( const TChar * name, bool defaultValue ) const
{
  for( TOffset i = 0; i < options.size(); ++i )
    if( OptionIs( i, name ) )
      return GetOptionBoolValue( i, defaultValue );
  return defaultValue;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Tag::Dump() const
{
  NI_ASSERT( pText, "");

  NMARKUP_DUMP( "Tag name = '%s'", Name().c_str() );
  NMARKUP_DUMP( "Tag value = '%s'", Value().c_str() );

  for( NMarkup::TOffset i = 0; i < OptionsCount(); ++i )
  {
    NMarkup::TString nm, vl;
    GetOption( i, &nm );
    GetOptionValue( i, &vl );
    NMARKUP_DUMP( "  Tag option '%s' = '%s' ( %i / %s )", nm.c_str(), vl.c_str(), GetOptionIntValue( i ), GetOptionBoolValue( i ) ? "on" : "off" );
  }
}

}; //namespace NMarkup
