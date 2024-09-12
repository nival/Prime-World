#ifndef TEXTMARKUPCOMMON_H_INCLUDED
#define TEXTMARKUPCOMMON_H_INCLUDED

#include "../UI/Root.h"

#define NMARKUP_STRING( s ) ( L##s )
#define NMARKUP_DUMP 


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NMarkup
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef wchar_t TChar;
typedef wstring TString;
typedef int TOffset;

const static TOffset NullOffset = TString::npos;
typedef float TUnit; //еденица измерения геометрических параметров текста; м.б. int или float

struct TPoint
{
  //NOTICE: Желательно не городить здесь функционал!!
  //Если понадобится что-либо кроме конструкторов, нужно обращатся к уже реализованным классам CVec2 и CTPoint<>
  TUnit x, y;
  TPoint() : x( 0 ), y( 0 ) {}
  TPoint( TUnit _x, TUnit _y ) : x( _x ), y( _y ) {}
};



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SBounds
{
  TUnit   width; //Габаритная ширина текста
  TUnit   ascent; //Визуальная высота текста
  TUnit   descent; //Визуальная высота "хвостиков" под baseline. П о л о ж и т е л ь н а я величина
  TUnit   gapAbove; //Дополнительный отступ сверху
  TUnit   gapUnder; //Дополнительный отступ снизу
  SBounds() : width( 0 ), ascent( 0 ), descent( 0 ), gapAbove( 0 ), gapUnder( 0 ) {}
};



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
_interface IStyle;
_interface IImage;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
_interface IUiRender
{
public:
  virtual IStyle *  GetStyle( const TChar * style ) = 0; // for ( style == 0) should return default style; should never return 0
  virtual IImage *  CreateImage( TPoint * size, const TChar * image ) = 0;
};



_interface IImage
{
public:
  virtual void      RenderImage( const TPoint & offset, const TPoint & size ) = 0;
};



_interface IStyle
{
public:
  //получить размер строки текста
  //возвращает учтенное (учитывая 'maxWidth', если не 0) количество символов текста
  virtual TOffset   GetTextBounds( SBounds * bounds, const TChar * text, TOffset length, TUnit maxWidth ) const = 0;

  //получить вертикальные размеры строки; пересекается с DefaultLineGap() и VisualHeight()
  virtual void      GetDefaultBounds( SBounds * bounds ) const = 0;

  //ширина пробела
  virtual TUnit     DefaultGlyphWidth() const = 0;

  //межстрочый интервал (между base-line-ами), используется для отбивки пустых строк
  virtual TUnit     DefaultLineGap() const = 0;

  //Высота заглавных букв шрифта над baseline; Используется для выравнивания изображений по высоте текста
  virtual TUnit     VisualHeight() const = 0;

  virtual void      RenderText( const SBounds & bounds, const TPoint & offset, const TChar * text, TOffset length ) = 0;
};

}; //namespace NMarkup

#endif //TEXTMARKUPCOMMON_H_INCLUDED
