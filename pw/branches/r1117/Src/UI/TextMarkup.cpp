#include "stdafx.h"

#include "TextMarkup.h"
#include "TextMarkupParser.h"
#include "../System/NameMap.h"


namespace NMarkup
{


const static float DEFAULT_STRETCH = 0.40f;


TextMarkup::TextMarkup()
{
  Clear( true );
}



TextMarkup::~TextMarkup()
{
}



void TextMarkup::Clear( bool clearStyle )
{
  text.clear();
  pUiRender = 0;
  defaultFontStyle = 0;
  stylesStack.clear();

  textBounds = TPoint( 0, 0 );
  upperGap = 0;
  lowerGapAndDescent = 0;

  elements.clear();

  skipCaslteTagDepth = 0;

  lineBegin = NullOffset;
  currentXOffs = 0;
  currentLine = 0;

  atomBegin = NullOffset;
  frightBegin = NullOffset;

  if( clearStyle )
  {
    condenseWhite = true;
    enableTags = true;
    verticalAlign = EVerticalAlign::Top;
    currentJustify = EJustify::Left;
    wordWrap = true;
    stretch = false;
    keepSpacesBeforePunct = false;
  }

  currentStretchFactor = DEFAULT_STRETCH;
}



IStyle * TextMarkup::CurrentStyle()
{
  NI_ASSERT( defaultFontStyle, "" );
  if( stylesStack.empty() )
    return defaultFontStyle;
  return stylesStack.back();
}



void TextMarkup::SetDefaultParams( EVerticalAlign::Enum align, EJustify::Enum justify, bool _wordWrap, bool _stretch )
{
  verticalAlign = align;
  currentJustify = justify;
  wordWrap = _wordWrap;
  stretch = _stretch;
}



void TextMarkup::Process( const TChar * _text, IUiRender * _uiRender, const TPoint & _area, INameMapResolver * map )
{
  Clear( false );

  text = _text;
  pUiRender = _uiRender;
  area = _area;
  defaultFontStyle = pUiRender->GetStyle( 0 );
  NI_ASSERT( defaultFontStyle, "");

  Parser parser( &text );

  elements.reserve( text.size() / 6 );

  while( true )
  {
    if ( !condenseWhite )
    {
      TOffset nlBegin = 0;
      if ( parser.ReadNewLine( &nlBegin ))
      {
        if (!skipCaslteTagDepth)
          EndLine( true, NullOffset, 1.0f );
        continue;
      }

      TOffset spaceBegin = 0;
      if ( parser.ReadSpace( &spaceBegin ))
      {
        if (!skipCaslteTagDepth)
          AddWord( spaceBegin, spaceBegin + 1, 0, false );
        continue;
      }
    }

    if ( enableTags )
    {
      Tag tag;
      if( parser.ReadTag( &tag ) )
      {
        ProcessTag( tag, map );
        continue;
      }
    }

    Word word;
    if( parser.ReadWord( &word, condenseWhite, enableTags ))
    {
      if (!skipCaslteTagDepth)
        AddWord( word.Begin(), word.End(), 0, condenseWhite );
      continue;
    }
    break;
  }


  FinishAtom();

  if ( lineBegin == NullOffset )
    AddStrutElement( 1.0f );

  EndLine( false, NullOffset, 1.0f );

  AlignVertically();
}



void TextMarkup::AddWord( TOffset begin, TOffset end, const wchar_t * valueText, bool spacesAroundNeeded )
{
  NI_VERIFY( CurrentStyle(), "Could not find text style", return);

  const wchar_t * wordText = valueText ? valueText : text.c_str();

  TOffset wordBegin = valueText ? 0 : begin;
  TOffset wordEnd = valueText ? wcslen( valueText ) : end;

  //Если слово получается шире, чем area.x,  будем делить его на части, которые помещаются в area.x
  while( wordBegin < wordEnd )
  {
    elements.push_back( SElement() );
    SElement & elem = elements.back();

    TOffset lengthFit = CurrentStyle()->GetTextBounds( &elem.bounds, wordText + wordBegin, wordEnd - wordBegin, wordWrap ? area.x : 0 );
    if( wordWrap )
      lengthFit = Max( lengthFit, 1 );

    elem.begin = wordBegin;
    elem.end = wordBegin + lengthFit;

    wordBegin += lengthFit;

    elem.minSpaceBefore = elem.minSpaceAfter = CurrentStyle()->DefaultGlyphWidth();
    elem.noSpaceBefore = elem.noSpaceAfter = !spacesAroundNeeded;

    if (!keepSpacesBeforePunct)
    {
      const bool punct =
        IsPunctuationMark(wordText+elem.begin, lengthFit) ||
        WordStartsWithPunctuationMark(wordText,elem.begin);

      if (punct)
        elem.noSpaceBefore = true;
    }

    elem.style = CurrentStyle();
    elem.valueElement = valueText ? true : false;
    if( valueText )
      elem.valueText = valueText;

    ArrangeElement( elements.size() - 1, true );
  }
}



void TextMarkup::ArrangeElement( TOffset index, bool enableWordWrap )
{
  NI_ASSERT( index >= 0 && index < elements.size(), "" );
  SElement & elem = elements[index];

  SElement * prevElem = 0;
  if( lineBegin != NullOffset )
  {
    NI_ASSERT( lineBegin >= 0 && lineBegin < elements.size(), "" );
    NI_ASSERT( index > lineBegin, "" );
    prevElem = &elements[index - 1];
  }

  //Разберемся с пробелами
  TUnit leadingSpace = 0;
  if( lineBegin != NullOffset )
  {
    if( !prevElem->noSpaceAfter && !elem.noSpaceBefore )
    {
      if(prevElem->minSpaceAfter != elem.minSpaceBefore )
        leadingSpace = Min( prevElem->minSpaceAfter, elem.minSpaceBefore );
      else
        leadingSpace = Max( prevElem->minSpaceAfter, elem.minSpaceBefore );
    }
  }

  //проверим автоперенос слов
  if( enableWordWrap && wordWrap && ( atomBegin == NullOffset ) )
  {
    if( currentXOffs + leadingSpace + elem.bounds.width > area.x )
    {
      EndLine( false, index, 1.0f );
      leadingSpace = 0;
    }
  }

  //Начнем строку, если ее еще нет
  if( lineBegin == NullOffset )
    lineBegin = index;

  elem.line = currentLine;

  //Положим элемент в список, определим его координаты
  currentXOffs += leadingSpace;
  elem.offset.x = currentXOffs; // currentYOffs корректно определяется только на завершенной строке
  currentXOffs += elem.bounds.width;
}



void TextMarkup::EndLine( bool forced, TOffset endOfTheLine, float defaultAscentScale )
{
  if ( lineBegin == NullOffset )
  {
    //Add empty element only if line are empty
    if( !forced )
      return;
    AddStrutElement( defaultAscentScale );
  }
  NI_ASSERT( lineBegin != NullOffset, "" );

  if( endOfTheLine == NullOffset )
    endOfTheLine = elements.size();

  //Вычислим габариты строки как совокупности элементов
  TUnit maxAscent = 0, maxDescent = 0;
  TUnit maxAboveBL = 0, maxUnderBL = 0; //Accounting additional gaps

  //These two needed for 'Stretch' justify
  for( TOffset i = lineBegin; i < endOfTheLine; ++i )
  {
    const SBounds & b = elements[i].bounds;
    maxAscent = Max( maxAscent, b.ascent * defaultAscentScale );
    maxDescent = Max( maxDescent, b.descent );
    maxAboveBL = Max( maxAboveBL, b.ascent * defaultAscentScale + b.gapAbove );
    maxUnderBL = Max( maxUnderBL, b.descent + b.gapUnder );
  }

  //Запомним отступы сверху и под текстом
  if ( currentLine == 0 )
    upperGap = maxAboveBL - maxAscent;
  lowerGapAndDescent = maxUnderBL;

  //Теперь проставим все координаты, которые можно узнать, только завершив строку
  //Поставим все элементы на baseline
  if ( lineBegin != NullOffset )
    for( TOffset i = lineBegin; i < endOfTheLine; ++i )
    {
      TUnit blDiff = maxAboveBL - ( elements[i].bounds.ascent + elements[i].bounds.gapAbove );
      elements[i].offset.y = textBounds.y + blDiff;
    }

  //Займемся justify со строкой: left, right, center, justify, fright и другие позы
  JustifyFreshLine( endOfTheLine );

  //Подготовимся к следующей строке
  textBounds.y += maxAboveBL + maxUnderBL;

  ++currentLine;

  lineBegin = NullOffset;
  atomBegin = NullOffset;
  frightBegin = NullOffset;
  currentXOffs = 0;
}



void TextMarkup::JustifyFreshLine( TOffset endOfTheLine )
{
  if ( lineBegin == NullOffset )
    return;

  NI_ASSERT( lineBegin >= 0 && lineBegin < elements.size(), "" );
  NI_ASSERT( endOfTheLine >= 0 && endOfTheLine <= elements.size(), "" );
  NI_ASSERT( endOfTheLine >= lineBegin, "" );

  const SElement & last = elements[ Max(endOfTheLine - 1, 0) ];

  const TUnit rightX = last.offset.x + last.bounds.width;
  const TUnit rightMargin = area.x - rightX;

  textBounds.x = Max( textBounds.x, rightX );

  if( stretch && ( rightMargin > 0 ) )
  {
    TUnit totalSpace = 0;
    for( TOffset i = lineBegin + 1; i < endOfTheLine; ++i )
      totalSpace += elements[i].offset.x - ( elements[i - 1].offset.x + elements[i - 1].bounds.width );

    const TUnit maxStretchMargin = ( area.x * currentStretchFactor );
    if( ( totalSpace > 0 ) && ( rightMargin < maxStretchMargin ) )
    {
      TUnit space = 0;
      TUnit prevOffsX = elements[lineBegin].offset.x;
      for( TOffset i = lineBegin + 1; i < endOfTheLine; ++i )
      {
        space += elements[i].offset.x - ( prevOffsX + elements[i - 1].bounds.width );
        TUnit justify = space * rightMargin / totalSpace;

        prevOffsX = elements[i].offset.x;
        elements[i].offset.x += justify;
      }
      return;
    }
  }

  if( currentJustify == EJustify::Left )
  {
    if( frightBegin != NullOffset )
    {
      NI_ASSERT( frightBegin >= lineBegin, "" );
      for( TOffset i = frightBegin; i < endOfTheLine; ++i )
        elements[i].offset.x += rightMargin;
    }
  }
  else if( currentJustify == EJustify::Right )
  {
    for( TOffset i = lineBegin; i < endOfTheLine; ++i )
      elements[i].offset.x += rightMargin;
  }
  else if( currentJustify == EJustify::Center )
  {
    const TUnit leftMargin = elements[lineBegin].offset.x;
    const TUnit centerOffset = 0.50f * ( rightMargin - leftMargin );
    for( TOffset i = lineBegin; i < endOfTheLine; ++i )
      elements[i].offset.x += centerOffset;
  }
}



void TextMarkup::JustifyTag( EJustify::Enum j, bool forcedEndLine, const Tag & tag )
{
  FinishAtom();

  const int ascentScale = tag.GetIntValue( 100 );
  EndLine( forcedEndLine, NullOffset, 1e-2f * ascentScale );

  currentJustify = j;
  wordWrap = tag.GetOptionBoolValue( NMARKUP_STRING( "wrap" ), wordWrap );
  stretch = tag.GetOptionBoolValue( NMARKUP_STRING( "stretch" ), stretch );
  currentStretchFactor = 1e-2f * (TUnit)tag.GetOptionIntValue( NMARKUP_STRING( "max_stretch" ), (int)(currentStretchFactor * 100.0f) );
  currentStretchFactor = Clamp( currentStretchFactor, 0.0f, 1.0f );
}



void TextMarkup::SpaceTag( const class Tag & tag )
{
  NI_VERIFY( CurrentStyle(), "Could not find text style", return);

  int amount = Max( tag.GetIntValue( 1 ), 0 );
  bool pixels = tag.GetOptionBoolValue( NMARKUP_STRING( "pixels" ), false );

  elements.push_back( SElement() );
  SElement & elem = elements.back();
  elem.begin = tag.Begin();
  elem.end = tag.End();
  elem.bounds.ascent = 0;
  elem.bounds.descent = 0;
  elem.bounds.gapUnder = 0;
  elem.bounds.gapAbove = 0;
  elem.bounds.width = pixels ? (TUnit)amount : ( CurrentStyle()->DefaultGlyphWidth() * (TUnit)amount );
  elem.minSpaceBefore = elem.minSpaceAfter = 0;
  elem.noSpaceBefore = elem.noSpaceAfter = true;

  ArrangeElement( elements.size() - 1, true );
}



void TextMarkup::StyleTag( const class Tag & tag )
{
  TString name; //TODO: обойтись как-нибудь без хипа
  tag.GetValue( &name );

  IStyle * style = pUiRender->GetStyle( name.c_str() );
  NI_ASSERT( style, "IUiRender::GetStyle() should never return 0" );

  if( stylesStack.empty() )
    stylesStack.reserve(4);

  stylesStack.push_back( style );
}



void TextMarkup::StyleCloseTag()
{
  if( !stylesStack.empty() )
    stylesStack.pop_back();
}



void TextMarkup::StartAtom()
{
  if( atomBegin == NullOffset )
    atomBegin = elements.size();
}



void TextMarkup::FinishAtom()
{
  if( atomBegin != NullOffset )
  {
    TOffset start = atomBegin;

    atomBegin = NullOffset;

    if( wordWrap && ( currentXOffs > area.x ) )
    {
      EndLine( false, start, 1.0f );
      for( TOffset i = start; i < elements.size(); ++i )
        ArrangeElement( i, false );
    }
  }
}


void TextMarkup::ImageTag( const Tag & tag )
{
  NI_VERIFY( CurrentStyle(), "Could not find text style", return);

  TString name;
  tag.GetValue( &name );

  TPoint size;
  IImage * image = pUiRender->CreateImage( &size, name.c_str() );

  size.x = (TUnit)tag.GetOptionIntValue( NMARKUP_STRING( "width" ), (int)size.x );
  size.y = (TUnit)tag.GetOptionIntValue( NMARKUP_STRING( "height" ), (int)size.y );

  size.x = Max( 0.0f, size.x );
  size.y = Max( 0.0f, size.y );

  SBounds pBounds;

  if( size.y > 0 )
    if( tag.GetOptionBoolValue( NMARKUP_STRING( "fit" ), true ) )
    {
      CurrentStyle()->GetDefaultBounds(&pBounds);
      TUnit h = pBounds.ascent + pBounds.descent;

      size.x = size.x * h / size.y;
      size.y = h;
    }

  TUnit lift = (TUnit)tag.GetOptionIntValue( NMARKUP_STRING( "lift" ), 0 );

  bool spaced = tag.GetOptionBoolValue( NMARKUP_STRING( "spaced" ), true );
  float spaceBefore = tag.GetOptionFloatValue( NMARKUP_STRING( "spaceb" ), 1.f );
  float spaceAfter = tag.GetOptionFloatValue( NMARKUP_STRING( "spacea" ), 1.f );
  int spaceWidth = CurrentStyle()->DefaultGlyphWidth();

  elements.push_back( SElement() );
  SElement & elem = elements.back();
  elem.image = image;
  elem.begin = tag.Begin();
  elem.end = tag.End();
  elem.bounds.descent = -lift;
  elem.bounds.ascent = size.y + lift;
  elem.bounds.gapAbove = 0;
  elem.bounds.gapUnder = 0;
  elem.bounds.width = size.x;
  elem.minSpaceBefore = spaceWidth * spaceBefore;
  elem.minSpaceAfter = spaceWidth * spaceAfter;
  elem.noSpaceBefore = elem.noSpaceAfter = !spaced;

  ArrangeElement( elements.size() - 1, true );
}



void TextMarkup::ValueTag( const Tag & tag, INameMapResolver * map )
{
  if ( !map )
    return;
  TString name, fmt;
  tag.GetValue( &name );
  tag.GetOptionValue( NMARKUP_STRING( "fmt" ), &fmt );

  CObj<NNameMap::ReadonlyVariant> variant = map->GetVariant( NStr::ToMBCS( name ).c_str() );
  if( !variant )
    return;

  wchar_t szValueText[256];
  variant->Format( szValueText, fmt.c_str() );

  AddWord( 0, 0, szValueText, true );
}


void TextMarkup::RecommendedTag()
{
  // Simulate empty image on all recommended: tags

  TPoint size;
  IImage * image = pUiRender->CreateImage( &size, NMARKUP_STRING( "recommendedempty" ));

  SBounds pBounds;
  CurrentStyle()->GetDefaultBounds(&pBounds);
  TUnit h = pBounds.ascent + pBounds.descent;

  size.x = size.x * h / size.y;
  size.y = h;
  
  TUnit lift = 0;
  bool spaced = true;
  float spaceBefore = 1.f;
  float spaceAfter = 1.f;
  int spaceWidth = CurrentStyle()->DefaultGlyphWidth();

  elements.push_back( SElement() );
  SElement & elem = elements.back();
  elem.image = image;
  elem.begin = 0;
  elem.end = 0;
  elem.bounds.descent = -lift;
  elem.bounds.ascent = size.y + lift;
  elem.bounds.gapAbove = 0;
  elem.bounds.gapUnder = 0;
  elem.bounds.width = size.x;
  elem.minSpaceBefore = spaceWidth * spaceBefore;
  elem.minSpaceAfter = spaceWidth * spaceAfter;
  elem.noSpaceBefore = elem.noSpaceAfter = !spaced;

  ArrangeElement( elements.size() - 1, true );
}


void TextMarkup::AddStrutElement( float defaultAscentScale )
{
  NI_VERIFY( CurrentStyle(), "Could not find text style", return);

  int begin = elements.empty() ? 0 : elements.back().end;
  //Empty elements are inserted after forced new lines
  elements.push_back( SElement() );
  SElement & elem = elements.back();
  elem.begin = begin;
  elem.end = begin;

  CurrentStyle()->GetDefaultBounds( &elem.bounds );
  elem.bounds.width = 0;
  elem.bounds.ascent *= defaultAscentScale;
  elem.bounds.gapAbove *= defaultAscentScale;

  elem.minSpaceBefore = elem.minSpaceAfter = 0;
  elem.noSpaceBefore = elem.noSpaceAfter = false;

  ArrangeElement( elements.size() - 1, false );
}



void TextMarkup::ProcessTag( const class Tag & tag, INameMapResolver * map )
{
  //tag.Dump();

  if( tag.NameIs( NMARKUP_STRING( "castle" ) ) )
  {
    skipCaslteTagDepth ++;
  }
  else if( tag.NameIs( NMARKUP_STRING( "/castle" ) ) )
  {
    skipCaslteTagDepth --;
  }

  if (skipCaslteTagDepth>0)
    return;

  if( tag.NameIs( NMARKUP_STRING( "left" ) ) )
  {
    JustifyTag( EJustify::Left, false, tag );
  }
  if( tag.NameIs( NMARKUP_STRING( "right" ) ) )
  {
    JustifyTag( EJustify::Right, false, tag );
  }
  if( tag.NameIs( NMARKUP_STRING( "center" ) ) )
  {
    JustifyTag( EJustify::Center, false, tag );
  }
  else if( tag.NameIs( NMARKUP_STRING( "br" ) ) )
  {
    JustifyTag( currentJustify, true, tag );
  }
  else if( tag.NameIs( NMARKUP_STRING( "space" ) ) )
  {
    SpaceTag( tag );
  }
  else if( tag.NameIs( NMARKUP_STRING( "style" ) ) )
  {
    StyleTag( tag );
  }
  else if( tag.NameIs( NMARKUP_STRING( "/style" ) ) )
  {
    StyleCloseTag();
  }
  else if( tag.NameIs( NMARKUP_STRING( "atom" ) ) )
  {
    StartAtom();
  }
  else if( tag.NameIs( NMARKUP_STRING( "/atom" ) ) )
  {
    FinishAtom();
  }
  else if( tag.NameIs( NMARKUP_STRING( "f_right" ) ) )
  {
    if( currentJustify == EJustify::Left )
      frightBegin = elements.size();
  }
  else if( tag.NameIs( NMARKUP_STRING( "image" ) ) )
  {
    ImageTag( tag );
  }
  else if( tag.NameIs( NMARKUP_STRING( "value" ) ) )
  {
    ValueTag( tag, map );
  }
  else if( tag.NameIs( NMARKUP_STRING( "recommended" ) ) )
  {
    RecommendedTag();
  }
}



void TextMarkup::AlignVertically()
{
  if ( verticalAlign == EVerticalAlign::Bottom )
  {
    TUnit offset = area.y - textBounds.y;
    for( TOffset i = 0; i < elements.size(); ++i )
      elements[i].offset.y += offset;
  }
  else if ( verticalAlign == EVerticalAlign::Center )
  {
    TUnit textHeight = textBounds.y - upperGap - lowerGapAndDescent;
    TUnit offset = 0.50f * ( area.y - textHeight ) - upperGap;

    for( TOffset i = 0; i < elements.size(); ++i )
      elements[i].offset.y += offset;
  }
}



void TextMarkup::Render() const
{
  for( TOffset i = 0; i < elements.size(); ++i )
  {
    const SElement & e = elements[i];

    if( pUiRender )
      if( e.style )
      {
        const wchar_t * txt = e.valueElement ? e.valueText.c_str() : text.c_str();
        e.style->RenderText( e.bounds, e.offset, txt + e.begin, e.end - e.begin );
      }
      else if( e.image )
      {
        TPoint size( e.bounds.width, e.bounds.ascent + e.bounds.descent );
        e.image->RenderImage( e.offset, size );
      }
  }
}



bool TextMarkup::GetCharInfo( TOffset charIndex, TPoint * offset, TPoint * size, int * lineIndex ) const
{
  if( charIndex == NullOffset )
    return false;

  if( !defaultFontStyle )
    return false;

  for( TOffset i = 0; i < elements.size(); ++i )
  {
    const SElement & e = elements[i];
    if( charIndex > e.end && ( i != elements.size() - 1) )
      continue;

    if( !e.style )
      continue;

    TOffset len = 0;
    if( charIndex > e.begin )
      len = charIndex - e.begin;
    else if( charIndex > e.end )
      len = e.end - e.begin;

    const wchar_t * txt = e.valueElement ? e.valueText.c_str() : text.c_str();

    SBounds bounds;
    e.style->GetTextBounds( &bounds, txt + e.begin, len, 0 );
    offset->x = e.offset.x + bounds.width;
    offset->y = e.offset.y;
    size->x = 0; //TODO
    size->y = bounds.ascent + bounds.descent;
    *lineIndex = e.line;
    return true;
  }

  //Empty text
  size->x = 0.0;
  size->y = defaultFontStyle->VisualHeight();
  *lineIndex = 0;

  if ( verticalAlign == EVerticalAlign::Bottom )
    offset->y = area.y - size->y;
  else if ( verticalAlign == EVerticalAlign::Center )
    offset->y = ( area.y - size->y ) / 2;
  else
    offset->y = 0;

  if( currentJustify == EJustify::Left )
    offset->x = 0;
  else if( currentJustify == EJustify::Right )
    offset->x = area.x;
  else if( currentJustify == EJustify::Center )
    offset->x = area.x / 2;

  return true;
}



bool TextMarkup::GetLineInfo( int lineIndex, TPoint & min, TPoint & max, TOffset & start, TOffset & length, TString * destString ) const
{
  TOffset begin = NullOffset;
  TOffset end = NullOffset;

  bool minXValid = false, minYValid = false;
  bool maxXValid = false, maxYValid = false;

  for( TOffset i = 0; i < elements.size(); ++i )
  {
    const SElement & e = elements[i];
    if ( e.line < lineIndex )
      continue;
    if ( e.line > lineIndex )
      break;

    if ( ( begin == NullOffset ) || ( e.begin < begin ))
      begin = e.begin;

    if ( ( end == NullOffset ) || ( e.end > end ))
      end = e.end;

    TUnit xmin = e.offset.x;
    TUnit xmax = e.offset.x + e.bounds.width;
    TUnit ymin = e.offset.y;
    TUnit ymax = e.offset.y + e.bounds.gapAbove + e.bounds.ascent + e.bounds.descent + e.bounds.gapUnder;

    if ( !minXValid || ( xmin < min.x ) )
    {
      min.x = xmin;
      minXValid = true;
    }

    if ( !minYValid || ( ymin < min.y ) )
    {
      min.y = ymin;
      minYValid = true;
    }

    if ( !maxXValid || ( xmax > max.x ) )
    {
      max.x = xmax;
      maxXValid = true;
    }

    if ( !maxYValid || ( ymax > max.y ) )
    {
      max.y = ymax;
      maxYValid = true;
    }
  }

  start = begin;
  length = end - begin;

  if ( destString && begin != NullOffset && end != NullOffset )
  {
    destString->resize( end - begin );
    copy( text.begin() + begin, text.begin() + end, destString->begin() );
  }

  return minXValid && minYValid && maxXValid && maxYValid;
}

bool TextMarkup::WordStartsWithDot(const wchar_t * word, TOffset begin){
  return word[begin] == L'.';
}

bool TextMarkup::WordStartsWithPunctuationMark(const wchar_t * word, TOffset begin)
{
  const nstl::wstring &marks = L"-.,;:!?%\"')»";
  if ( !word )
    return false;

  return marks.find(word[begin]) != nstl::wstring::npos;
}

bool TextMarkup::IsPunctuationMark(const wchar_t * word, TOffset length){
  const nstl::wstring &marks = L"-.,;:!?%\"')»";
  if (!word || length != 1)
    return false;

  return marks.find(word[0]) != nstl::wstring::npos;
}

} //namespace NMarkup
