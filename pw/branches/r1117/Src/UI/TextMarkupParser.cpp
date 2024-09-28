#include "stdafx.h"

#include "TextMarkupParser.h"

namespace NMarkup
{



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Parser::Parser( const TString * text ) :
pText( text ),
offset( 0 )
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Parser::~Parser()
{
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Parser::ReadTag( Tag * tag )
{
  SkipSpaces();

  if( tag->Read( pText, offset ) )
  {
    offset = tag->End();
    return true;
  }

  return false;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Parser::ReadWord( Word * word, bool condenseWhite, bool tagsEnabled )
{
  if ( condenseWhite )
    SkipSpaces();

  if( word->Read( pText, offset, tagsEnabled ) )
  {
    offset = word->End();
    return true;
  }
  return false;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Parser::SkipSpaces()
{
  for( ; offset < pText->length(); ++offset )
    if( !Lexem::IsSpace( pText->at( offset ) ) )
      break;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Parser::ReadNewLine( TOffset * newLineBegin )
{
  if ( offset < pText->length() )
  {
    TChar c0 = pText->at( offset );
    TChar c1 = ( offset + 1 ) < pText->length() ? pText->at( offset + 1 ) : 0;
    int newLineLen = Lexem::IsNewLine( c0, c1 );
    NI_ASSERT( offset + newLineLen <= pText->length(), "" );
    offset += newLineLen;

    if ( newLineLen )
      *newLineBegin = offset;

    return newLineLen ? true : false;
  }
  return false;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Parser::ReadSpace( TOffset * begin )
{
  if ( offset < pText->length() )
    if ( Lexem::IsSpace( pText->at( offset ) ) )
    {
      *begin = offset;
      ++offset;
      return true;
    }
  return false;
}

} //namespace NMarkup
