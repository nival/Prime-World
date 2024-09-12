#ifndef TEXTMARKUPPARSER_H_INCLUDED
#define TEXTMARKUPPARSER_H_INCLUDED

#include "TextMarkupLexems.h"

namespace NMarkup
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Parser
{
public:
  Parser( const TString * text );
  ~Parser();

  bool ReadTag( Tag * tag );
  bool ReadWord( Word * word, bool condenseWhite, bool tagsEnabled );

  void SkipSpaces();

  bool ReadNewLine( TOffset * newLineBegin );
  bool ReadSpace( TOffset * begin );

private:
  const TString *   pText;
  TOffset           offset;
};

} //namespace NMarkup

#endif //TEXTMARKUPPARSER_H_INCLUDED
