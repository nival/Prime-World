#ifndef TEXTMARKUPLEXEMS_H_INCLUDED
#define TEXTMARKUPLEXEMS_H_INCLUDED


#include "TextMarkupCommon.h"


namespace NMarkup
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Lexem
{
public:
  Lexem() { Clear(); }

  TOffset Begin() const { return begin; }
  TOffset End() const { return end; }
  
  void GetString( TString * str ) const { ImplGetString( str, begin, end ); }
  TString String() const { return ImplString( begin, end ); }
  bool Is( const TChar * str ) const { return ImplIs( str, begin, end ); }

  static bool IsSpace( TChar c );
  static TOffset IsNewLine( TChar c0, TChar c1 ); //Returns new-line sequence length
  static bool IsNameChar( TChar c, bool firstSybmol = false );
  static bool IsNumeric( TChar c );
  static int DigitToNumber( TChar c );

protected:
  const TString * pText;
  TOffset begin, end;

  void Clear()
  {
    pText = 0;
    begin = end = 0;
  }

  bool Read( const TString * text, TOffset _begin )
  {
    Clear();

    pText = text;
    begin = end = _begin;
    return true;
  }

  TOffset ImplSkipSpaces( TOffset offset );
  TOffset ImplScanName( TOffset offset );

  void ImplGetString( TString * str, TOffset _begin, TOffset _end ) const;
  TString ImplString( TOffset _begin, TOffset _end ) const;

  bool ImplIs( const TChar * str, TOffset _begin, TOffset _end ) const;

  int ImplGetInt( TOffset _begin, TOffset _end, int defaultValue, int radix ) const;
  bool ImplGetBool( TOffset _begin, TOffset _end, bool defaultValue ) const;
  float ImplGetFloat( TOffset _begin, TOffset _end, float defaultValue, int radix ) const;
};



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Word : public Lexem
{
public:
  Word() : Lexem() {};

  bool Read( const TString * text, TOffset _begin, bool tagsEnabled );
};



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Tag : public Lexem
{
public:
  Tag() : Lexem() {}

  void Clear();

  bool Read( const TString * text, TOffset _begin );

  void GetName( TString * str ) const { ImplGetString( str, nameBegin, nameEnd ); }
  TString Name() const { return ImplString( nameBegin, nameEnd ); }
  bool NameIs( const TChar * name ) const { return ImplIs( name, nameBegin, nameEnd ); }

  void GetValue( TString * str ) const { ImplGetString( str, valueBegin, valueEnd ); }
  TString Value() const { return ImplString( valueBegin, valueEnd ); }
  int GetIntValue( int defaultValue ) const { return ImplGetInt( valueBegin, valueEnd, defaultValue, 10 ); }
  bool GetBoolValue( bool defaultValue ) const { return ImplGetBool( valueBegin, valueEnd, defaultValue ); }

  TOffset OptionsCount() const { return (TOffset)options.size(); }
  
  void GetOption( TOffset index, TString * str ) const {
    if( index < 0 || index >= (TOffset)options.size() )
      return;
    ImplGetString( str, options[index].nameBegin, options[index].nameEnd );
  }

  void GetOptionValue( TOffset index, TString * str ) const {
    if( index < 0 || index >= (TOffset)options.size() )
      return;
    ImplGetString( str, options[index].valueBegin, options[index].valueEnd );
  }

  bool GetOptionValue( const TChar * name, TString * str ) const;

  bool OptionIs( TOffset index, const TChar * str ) const {
    if( index < 0 || index >= (TOffset)options.size() )
      return false;
    return ImplIs( str, options[index].nameBegin, options[index].nameEnd );
  }

  bool OptionValueIs( TOffset index, TChar * str ) const {
    if( index < 0 || index >= (TOffset)options.size() )
      return false;
    return ImplIs( str, options[index].valueBegin, options[index].valueEnd );
  }

  int GetOptionIntValue( TOffset index, int defaultValue = 0, int radix = 10 ) const;
  int GetOptionIntValue( const TChar * name, int defaultValue = 0, int radix = 10 ) const;

  float GetOptionFloatValue( TOffset index, float defaultValue = 0.f, int radix = 10 ) const;
  float GetOptionFloatValue( const TChar * name, float defaultValue = 0.f, int radix = 10 ) const;

  bool GetOptionBoolValue( TOffset index, bool defaultValue = false ) const;
  bool GetOptionBoolValue( const TChar * name, bool defaultValue = false ) const;

  void Dump() const;

private:
  struct SOption
  {
    TOffset   nameBegin, nameEnd;
    TOffset   valueBegin, valueEnd;
    SOption() : nameBegin( 0 ), nameEnd( 0 ), valueBegin( 0 ), valueEnd( 0 ) {}
  };

  TOffset nameBegin, nameEnd;
  TOffset valueBegin, valueEnd;
  vector<SOption> options;
};

}; //namespace NMarkup

#endif //TEXTMARKUPLEXEMS_H_INCLUDED
