#pragma once

#include "Characters.h"

namespace flash
{

class ButtonCharacter : public CharacterBase, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( ButtonCharacter, CharacterBase, BaseObjectST );

public:
  ButtonCharacter() {}

  virtual void Load( SwfStreamReader & streamReader, TagInfo & tagInfo, UI16 characterID );

  virtual void AddDisplayTag( IDisplayTag* _displayTag ) {}
  virtual void InitWithNonDisplayObject( avmplus::ScriptObject* _scriptObject, avmplus::ScriptObject * scriptObject ) {}

  virtual avmplus::ClassClosure* GetDefaultDisplayClass( FlashMovieAvmCore * flashCore ); 
  virtual void InitObject( avmplus::ScriptObject* _scriptObject );

  virtual void AddFrameLabel( int frameId, const nstl::string& fameLabel ) {}

private:
};

}