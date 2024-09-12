#ifndef TEXTMARKUP_H_INCLUDED
#define TEXTMARKUP_H_INCLUDED

#include "TextMarkupCommon.h"


namespace NNameMap
{
  class ReadonlyVariant;
  _interface IMap;
};


namespace NMarkup
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace EJustify
{
  enum Enum { Left, Center, Right };
};



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace EVerticalAlign
{
  enum Enum { Top, Center, Bottom };
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
_interface INameMapResolver
{
  virtual NNameMap::ReadonlyVariant * GetVariant( const char * name ) = 0;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Tag;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class TextMarkup
{
public:
  TextMarkup();
  ~TextMarkup();

  void CondenseWhite( bool condense ) { condenseWhite = condense; }
  void EnableTags( bool enable ) { enableTags = enable; }
  void KeepSpacesBeforePunct( bool keep ) { keepSpacesBeforePunct = keep; }

  void SetDefaultParams( EVerticalAlign::Enum align, EJustify::Enum justify, bool _wordWrap, bool _stretch );

  void Process( const TChar * _text, IUiRender * _uiRender, const TPoint & _area, INameMapResolver * map );

  void Render() const;

  const TString & Text() const { return text; }

  const TPoint & Area() const { return area; }

  const TPoint & TextBounds() const { return textBounds; }

  bool GetCharInfo( TOffset charIndex, TPoint * offset, TPoint * size, int * lineIndex ) const;

  int LinesCount() const { return currentLine; }
  bool GetLineInfo( int lineIndex, TPoint & min, TPoint & max, TOffset & start, TOffset & length, TString * destString ) const;

  TOffset ElementsCount() const { return elements.size(); } //Mainly for testing purpose

private:
  struct SElement
  {
    TOffset   begin, end;  //Ссылки в текст
    int       line;
    IImage *  image;
    SBounds   bounds; //Габариты блока текста или изображения
    TPoint    offset; //Координаты для рендера; У первого символа в режиме left/top offset = [0, 0]
    bool      noSpaceBefore, noSpaceAfter; //если один из этих флагов false, то пробела с соответствующей стороны не будет
    TUnit     minSpaceBefore, minSpaceAfter;
    IStyle *  style;
    bool      valueElement;
    wstring   valueText;

    SElement() :
    begin( 0 ), end( 0 ),
    line( 0 ),
    image( 0 ),
    noSpaceBefore( false ), noSpaceAfter( false ),
    minSpaceBefore( 0 ), minSpaceAfter( 0 ),
    style( 0 ),
    valueElement( false )
    {}
  };

  TString             text;
  IUiRender *         pUiRender;
  TPoint              area;
  IStyle *            defaultFontStyle;
  vector< IStyle *>   stylesStack;
  EVerticalAlign::Enum verticalAlign;

  TPoint              textBounds; //Габариты текста, вычисленные со всеми отступами
  TUnit               upperGap; //Отступ текста сверху
  TUnit               lowerGapAndDescent; //Отступ текста снизу

  bool                condenseWhite;
  bool                enableTags;
  int                 skipCaslteTagDepth;

  vector< SElement >  elements;
  EJustify::Enum      currentJustify;
  TOffset             lineBegin; //индекс первого элемента текущей строки, или NullOffset, если строка еще не началась
  TUnit               currentXOffs;
  int                 currentLine;
  bool                wordWrap;
  bool                stretch;
  TUnit               currentStretchFactor; //текущее максимальное растяжение текста (в долях от area)
  TOffset             atomBegin;
  TOffset             frightBegin; // i.e. Flush-Right =)

  bool                keepSpacesBeforePunct;

  void Clear( bool clearStyle );
  IStyle * CurrentStyle();
  void AddWord( TOffset begin, TOffset end, const wchar_t * valueText, bool spacesAroundNeeded );
  void ArrangeElement( TOffset index, bool enableWordWrap );
  void EndLine( bool forced, TOffset endOfTheLine, float defaultAscentScale );
  void JustifyFreshLine( TOffset endOfTheLine );
  void JustifyTag( EJustify::Enum j, bool forcedEndLine, const Tag & tag );
  void SpaceTag( const Tag & tag );
  void StyleTag( const Tag & tag );
  void StyleCloseTag();
  void StartAtom();
  void FinishAtom();
  void ImageTag( const Tag & tag );
  void ValueTag( const Tag & tag, INameMapResolver * map );
  void RecommendedTag();
  void AddStrutElement( float defaultAscentScale );
  void ProcessTag( const Tag & tag, INameMapResolver * map );
  void AlignVertically();
  bool WordStartsWithDot(const wchar_t * word, TOffset begin);
  bool IsPunctuationMark(const wchar_t * word, TOffset length);
  bool WordStartsWithPunctuationMark(const wchar_t * word, TOffset begin);

};

} //namespace NMarkup

#endif //TEXTMARKUP_H_INCLUDED
