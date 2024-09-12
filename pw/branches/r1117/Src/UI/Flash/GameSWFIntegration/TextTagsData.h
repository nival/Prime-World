#ifndef TEXTTAGSDATA_H_INCLUDED
#define TEXTTAGSDATA_H_INCLUDED

#include "SwfTypes.h"

namespace SWFParser
{
  struct TagInfo;
};

namespace flash
{

class SwfStreamReader;
class SwfFont;
class FontsDictionary;



namespace ECsmTextFlashType
{
  enum Enum
  {
    Normal = 0,
    Advanced = 1
  };
}



namespace ECsmTextGridFit
{
  enum Enum
  {
    Off = 0,
    Pixel = 1,
    SubPixel = 2
  };
}



struct SCsmTextSettings
{
  ECsmTextFlashType::Enum   UseFlashType; //2 bits
  ECsmTextGridFit::Enum     GridFit; //3 bits
  //3 bits reserved
  float                     Thickness; //F32
  float                     Sharpness; //F32
  //8 bit reserved


  SCsmTextSettings() : UseFlashType(), GridFit(), Thickness(), Sharpness() {}
  void Load( SwfStreamReader & swf );
};



struct STextTag_GLYPHENTRY
{
  UI32      glyphIndex;
	SI32      glyphAdvance;

  STextTag_GLYPHENTRY() : glyphIndex( 0 ), glyphAdvance( 0 ) {}
};



struct STextTag_TEXTRECORD
{
  // 1 bit textRecordType
  // 3 bit styleFlagsReserved
  bool      styleFlagsHasFont; // 1 bit
  bool      styleFlagsHasColor; // 1 bit
  bool      styleFlagsHasYOffset; // 1 bit
  bool      styleFlagsHasXOffset; // 1 bit
	UI16      fontID;
  SWF_RGBA  textColor;
	SI16      xOffset;
	SI16      yOffset;
	UI16      textHeight;
	//UI8 glyphCount

  vector<STextTag_GLYPHENTRY>  glyphEntries;

  Weak<SwfFont>  font;

  wstring   rawText;

  STextTag_TEXTRECORD();
};



struct SStaticTextTagData
{
  SWF_RECT    textBounds;
  SWF_MATRIX  textMatrix;
  vector<STextTag_TEXTRECORD> textRecords;

  void Load( SwfStreamReader & swf, TagInfo & tagInfo, FontsDictionary * fontsDict );
};



//public inheritance from structure for easy data access
class StaticTextTagData : public SStaticTextTagData, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( StaticTextTagData, BaseObjectST );

public:
  StaticTextTagData() {}

  void Copy( const StaticTextTagData * source );

  SCsmTextSettings csmSettings;
};






namespace EEditTextAlign
{
  enum Enum
  {
    Left = 0,
    Right = 1,
    Center = 2,
    Justify = 3
  };
}



struct SEditTextTagData
{
  SWF_RECT  Bounds;

  bool      HasText; //1 bit
  bool      WordWrap; //1 bit
  bool      Multiline; //1 bit
  bool      Password; //1 bit
  bool      ReadOnly; //1 bit
  bool      HasTextColor; //1 bit
  bool      HasMaxLength; //1 bit
  bool      HasFont; //1 bit
  bool      HasFontClass; //1 bit
  bool      AutoSize; //1 bit
  bool      HasLayout; //1 bit
  bool      NoSelect; //1 bit
  bool      Border; //1 bit
  bool      WasStatic; //1 bit
  bool      HTML; //1 bit
  bool      UseOutlines; //1 bit

  UI16      FontID;
  string    FontClass;
  UI16      FontHeight;
  SWF_RGBA  TextColor;
  UI16      MaxLength;
  EEditTextAlign::Enum Align;
  UI16      LeftMargin;
  UI16      RightMargin;
  UI16      Indent;
  SI16      Leading;
  string    VariableName;
  wstring   InitialText;

  Weak<SwfFont>  font;

  SEditTextTagData();

  void Load( SwfStreamReader & swf, FontsDictionary * fontsDict );
};



//public inheritance from structure for easy data access
class EditTextTagData : public SEditTextTagData, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( EditTextTagData, BaseObjectST );

public:
  EditTextTagData() {}

  void Copy( const EditTextTagData * source );

  SCsmTextSettings csmSettings;
};


} //namespace flash

#endif //TEXTTAGSDATA_H_INCLUDED

