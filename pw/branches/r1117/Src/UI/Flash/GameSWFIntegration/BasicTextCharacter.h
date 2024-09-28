#ifndef BASICTEXTCHARACTER_H_INCLUDED
#define BASICTEXTCHARACTER_H_INCLUDED

#include "Characters.h"
#include "SwfTypes.h"

namespace flash
{

class SwfStreamReader;
class FontsDictionary;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class BasicTextCharacter : public CharacterBase
{
public:
  BasicTextCharacter() {}
  BasicTextCharacter( FontsDictionary * _fontsDict ) : 
  fontsDictionary( _fontsDict )
  {
  }

  virtual void LoadCsmSettings( SwfStreamReader & swf ) = 0;
  virtual void AddFrameLabel( int frameId, const nstl::string& fameLabel ) {}

protected:
  Weak<FontsDictionary>     fontsDictionary;
};

} //namespace flash


#endif //BASICTEXTCHARACTER_H_INCLUDED
