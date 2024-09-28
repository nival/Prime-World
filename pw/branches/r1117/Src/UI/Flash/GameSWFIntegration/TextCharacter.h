#ifndef TEXTCHARACTER_H_INCLUDED
#define TEXTCHARACTER_H_INCLUDED

#include "BasicTextCharacter.h"
#include "SwfTypes.h"


namespace SWFParser
{
  struct TagInfo;
};

namespace flash
{

class StaticTextTagData;
_interface IFontRender;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class TextCharacter : public BasicTextCharacter, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( TextCharacter, BasicTextCharacter, BaseObjectST );

public:
  TextCharacter() {}
  TextCharacter( FontsDictionary * _fontsDict );

  //ICharacter
  virtual void Load( SwfStreamReader & swf, TagInfo & tagInfo, UI16 characterID );

  virtual void InitWithNonDisplayObject( avmplus::ScriptObject* _scriptObject, avmplus::ScriptObject * scriptObject ) {}

  virtual void AddDisplayTag( IDisplayTag* _displayTag );
  virtual avmplus::ClassClosure* GetDefaultDisplayClass( FlashMovieAvmCore * flashCore );
  virtual void InitObject( avmplus::ScriptObject* _scriptObject );

  //BasicTextCharacter
  virtual void LoadCsmSettings( SwfStreamReader & swf );

private:
  Strong<StaticTextTagData>  data;
};

} //namespace flash

#endif //TEXTCHARACTER_H_INCLUDED
