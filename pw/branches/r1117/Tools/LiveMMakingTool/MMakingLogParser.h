#ifndef MMAKINGLOGPARSER_H_INCLUDED
#define MMAKINGLOGPARSER_H_INCLUDED

#include "LogParser.h"


namespace mm_test
{

class LogParser : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( LogParser, BaseObjectST );

public:
  class Excep {
  public:
    Excep( const Excep & other ) : _textSample( other._textSample ), _reason( other._reason ), _file( other._file ) {}
    Excep( const char * textPtr, const char * reason, const char * file ) :
    _textSample( textPtr, Min( strlen(textPtr), 256u ) ), _reason( reason ), _file( file ) {}

    void SetFile( const char * name ) { _file = name; }
    const char * TextSample() const { return _textSample.c_str(); }
    const char * Reason() const { return _reason.c_str(); }
    const char * File() const { return _file.c_str(); }
  private:
    string _textSample;
    string _reason;
    string _file;
  };

  class ExcepFile : public Excep {
  public:
    ExcepFile( const char * reason, const char * file ) : Excep( "", reason, file ) {}
  };

  class ExcepText : public Excep {
  public:
    ExcepText( const char * textPtr, const char * reason ) : Excep( textPtr, reason, "" ) {}
  };

  LogParser( ILogParserCb * cb, ELogVersion::Enum logVersion );

  void AddFile( const char * name );
  void AddText( const char * text, const char * filename );


protected:
  struct Ctx {
    string        text;
    const char *  ptr;
    Ctx() : ptr( 0 ) {}
    Ctx( const char * txt ) : text( txt ), ptr( text.c_str() ) {}
    void Advance( int sz ) { ptr += sz; }
  };

private:
  const ELogVersion::Enum _logVersion;
  Strong<ILogParserCb> _cb;

  void ReadFile( string & text, const char * name );
  void ParseFile( Ctx & ctx );
  bool GetToTheEol( Ctx & ctx, string & line );
  void SkipToTheEol( Ctx & ctx ) { string tmp; GetToTheEol( ctx, tmp ); }
  void SkipUtcMarker( Ctx & ctx );
  void GetTimestamp( Ctx & ctx, Timestamp & ts );
  void GetKeywords( Ctx & ctx, string & words );
  void GetRequest( Ctx & ctx, const Timestamp & ts );
  static lobby::ESex::Enum StringToSex( Ctx & ctx, const char * s );
  bool GetRequestMemeber( Ctx & ctx, vector<mmaking::SRequestMember> & memebers );
  void GetRequestRemoval( Ctx & ctx, const Timestamp & ts );
  void GetGame( Ctx & ctx, const Timestamp & ts );
  bool GetGameMember( Ctx & ctx, mmaking::SGame & game, bool first );
  mmaking::EBasket::Enum DetermineMemberBasket( const mmaking::SRequestMember & memb );
  mmaking::EBasket::Enum DetermineGameBasket( const mmaking::SGame & game );
};

} //namespace mm_test

#endif //MMAKINGLOGPARSER_H_INCLUDED
