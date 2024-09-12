#ifndef EDITTEXTCHARACTER_H_INCLUDED
#define EDITTEXTCHARACTER_H_INCLUDED

#include "BasicTextCharacter.h"
#include "SwfTypes.h"

namespace SWFParser
{
  struct TagInfo;
};

namespace flash
{

class SwfStreamReader;
class FontsDictionary;
class EditTextTagData;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class EditTextCharacter : public BasicTextCharacter, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( EditTextCharacter, BasicTextCharacter, BaseObjectST );

public:
  EditTextCharacter( FontsDictionary * _fontsDict );

  //ICharacter
  virtual void Load( SwfStreamReader & swf, TagInfo & tagInfo, UI16 characterID );

  virtual void AddDisplayTag( IDisplayTag* _displayTag );
  virtual void InitWithNonDisplayObject( avmplus::ScriptObject* _scriptObject, avmplus::ScriptObject * scriptObject );
  virtual avmplus::ClassClosure* GetDefaultDisplayClass( FlashMovieAvmCore * flashCore );
  virtual void InitObject( avmplus::ScriptObject* _scriptObject );

  //BasicTextCharacter
  virtual void LoadCsmSettings( SwfStreamReader & swf );

private:
  Strong<EditTextTagData>  data;

  EditTextCharacter() {}
};

} //namespace flash

#endif //EDITTEXTCHARACTER_H_INCLUDED
