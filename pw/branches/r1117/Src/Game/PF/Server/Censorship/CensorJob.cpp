#include "stdafx.h"
#include "CensorClient.h"
#include <tinyxml/tinyxml.h>

namespace censorship
{

bool CheckJob::Perform( webClient::IHttpClient * httpClient )
{
  ++triesNumber;

  string utf8text;
  NStr::UnicodeToUTF8( &utf8text, sourceText );

  string urlEncText;
  urlEncText.reserve( utf8text.size() * 2 + 16 );
  NStr::UrlEncode( urlEncText, utf8text, true, false );

  string requestText;
  requestText.reserve( sett->cleanSpeakRequest.size() + urlEncText.size() + 128 );

  requestText += sett->cleanSpeakRequest;

  requestText += "&contentItem.content=";
  requestText += urlEncText;

  string answerHeader, answerBody;
  if ( !httpClient->PerformPOST( sett->cleanSpeakUrl.c_str(), requestText.c_str(), requestText.length(), answerHeader, answerBody ) )
  {
    ErrorTrace( "CleanSpeak: HTTP request failed! req=%d, aux=%d, url=%s, text='%s'", requestId, auxId, sett->cleanSpeakUrl, requestText );
    return false;
  }

  if ( httpClient->GetResponseCode() != 200 )
  {
    ErrorTrace( "CleanSpeak: Server returned error! req=%d, aux=%d, response=%d, url=%s, text='%s'", requestId, auxId, httpClient->GetResponseCode(), sett->cleanSpeakUrl, requestText );
    return false;
  }


  TiXmlDocument xmlDoc;
  xmlDoc.Parse( answerBody.c_str(), 0, TIXML_ENCODING_UTF8 );
  if ( !xmlDoc.Error() )
    if ( TiXmlElement * root = xmlDoc.FirstChildElement( "handle" ) )
      if ( TiXmlElement * filter = root->FirstChildElement( "filter" ) )
      {
        bool matched = false;
        if ( const char * matchedAttr = filter->Attribute( "matched" ) )
          matched = !NStr::ICmp( matchedAttr, "true" );

        if ( TiXmlElement * replacement = filter->FirstChildElement( "replacement" ) )
          for ( TiXmlNode * textNode = replacement->FirstChild(); textNode; textNode = textNode->NextSibling() )
            if ( TiXmlText * cdataTextNode = textNode->ToText() )
              if ( cdataTextNode->CDATA() )
              {
                const char * text = cdataTextNode->Value();

                wstring unicodeText;
                NStr::UTF8ToUnicode( &unicodeText, text );

                NStr::StripXmlEscapes( newText, unicodeText );

                if ( matched )
                {
                  DebugTrace( "CleanSpeak: Matches found! Replacement text: '%s'", newText );

                  for ( TiXmlElement * match = filter->FirstChildElement( "match" ); match; match = textNode->NextSiblingElement( "match" ) )
                  {
                    const char * matched = match->Attribute( "matched" );
                    const char * severity = match->Attribute( "severity" );
                    DebugTrace( "CleanSpeak: matched='%s', severity='%s'", matched, severity );
                  }
                }
                else
                  DebugTrace( "CleanSpeak: Matches not found! Replacement text: '%s'", newText );
                result = matched ? ECheckResult::Dirty : ECheckResult::Clean;
                return true;
              }
      }

  ErrorTrace( "CleanSpeak: Answer parse error! req=%d, aux=%d, url=%s, text='%s'", requestId, auxId, sett->cleanSpeakUrl, requestText );
  DebugTrace( "CleanSpeak: Answer text:\n%s", answerBody.c_str() );
 
  return false;
}



void CheckJob::Finish()
{
  StrongMT<ICensorClientCallback> locked = callback.Lock();

  const wstring & text = ( result == ECheckResult::SvcFailure ) ? sourceText : newText;

  DebugTrace( "CleanSpeak: Request served. req=%d, aux=%d, result=%s, callback=%d, text='%s'", requestId, auxId, ECheckResult::ToString( result ), locked.Valid(), text );

  if ( !locked )
    return;

  locked->TextCheckResult( requestId, auxId, result, text );
}

} //namespace censorship
