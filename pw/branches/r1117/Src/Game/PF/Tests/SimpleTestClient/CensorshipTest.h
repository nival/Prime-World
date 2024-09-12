#pragma once

#include "Server/Censorship/ICensorClient.h"
#include "System/ConfigFiles.h"

namespace censorship_test
{

class CensureTest : public censorship::ICensorClientCallback, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( CensureTest, censorship::ICensorClientCallback, BaseObjectMT );

public:
  CensureTest() {}

  virtual void TextCheckResult( censorship::TRequestId _reqId, censorship::TAuxId _auxId, censorship::ECheckResult::Enum _result, const wstring & _filteredText )
  {
    DebugTrace( "Check result: reqId=%d, auxId=%d, result=%s, text=%s", _reqId, _auxId, censorship::ECheckResult::ToString(_result), _filteredText );
  }
};



inline bool Test()
{
  if ( !CmdLineLite::Instance().IsKeyDefined( "-censorship" ) )
    return false;

  NGlobal::ExecuteConfig( "pvx_srv_chat.cfg", NProfile::FOLDER_GLOBAL );

  int count = CmdLineLite::Instance().GetIntKey( "-count", 1 );
  int sleep = CmdLineLite::Instance().GetIntKey( "-sleep", 1 );

  MessageTrace( "Performing Censorship Test" );
  MessageTrace( "Count: %d", count );
  MessageTrace( "Sleep: %d", sleep );

  int aux = 333;

  StrongMT<censorship::ICensorClient> client = censorship::CreateClient();

  StrongMT<CensureTest> censTest = new CensureTest;

  wstring checkTexts[] = {
      wstring( L"clean speak" ),
      wstring( L"test fuck test" ),
      wstring( L"Quick brown fouck jumped over the lazy dog" ),
      wstring( L"The Content Item service provides a single API that performs all content handling functionality. This includes filtering (for emails, URLs, and all entries on the white and black lists in the database), content storage and search indexing, content moderation, and content updating." ),
      wstring( L"Удали игру днище! Встань блядь под башней читай тултипы на xуй!" ),
      wstring( L"А вот и наши кавычки: \" И наши амперсанды: & И кое-что в апострофах: '<>'" ),
      wstring( L"XML escape: &apos &quot &lt &amp &gt." )
    };
  const size_t checkTextsNum = sizeof( checkTexts ) / sizeof( wstring );

  DWORD t = GetTickCount();
  srand( t );
  for ( int i = 0; i < count; ++i )
  {
    const wstring & checkText = checkTexts[rand() % checkTextsNum];
    censorship::TRequestId reqId = client->Check( aux++, censTest, checkText );

    if ( !reqId )
      ErrorTrace( "Failed to add request!" );

    if ( sleep )
      Sleep( sleep );

    if ( GetTickCount() > t + 100 )
      client->Poll();
  }

  MessageTrace( "Main cycle finished" );

  client->Poll();
  Sleep( 1000 );
  client->Poll();

  MessageTrace( "Cleaning up" );
  client = 0;
  return true;
}

} //namespace censorship_test
