#ifndef JSONLOGPARSER_H_INCLUDED
#define JSONLOGPARSER_H_INCLUDED

#include "LogParser.h"

namespace Json
{
  class Value;
}

namespace mm_test
{


class JsonLogParser : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( JsonLogParser, BaseObjectST );

public:
  JsonLogParser( ILogParserCb * cb, ELogVersion::Enum logVersion );

  bool AddFile( const char * name );

protected:

private:
  struct JsonExcep {
    string msg;
    JsonExcep( const char * _msg ) : msg( _msg ) {}
  };

  const ELogVersion::Enum _logVersion;
  Strong<ILogParserCb> _cb;

  bool ReadFile( FILE * f );
  bool ParseJson( const char * text );
  void ProcessJsonValue( const Json::Value & value );
  void ParseGeoInfo( mmaking::SGeoInfo & geo, const Json::Value & value );
  void ProcessAddRequest( const Json::Value & value );
  void ProcessRemoveRequest( const Json::Value & value );
  void ProcessGame( const Json::Value & value );
  void ParseTimestamp( Timestamp & ts, const Json::Value & value );
};

} //namespace mm_test

#endif //JSONLOGPARSER_H_INCLUDED
