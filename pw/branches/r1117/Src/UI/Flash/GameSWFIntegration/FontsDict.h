#ifndef FONTSDICT_H_INCLUDED
#define FONTSDICT_H_INCLUDED

namespace flash
{

class SwfFont;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class FontsDictionary : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( FontsDictionary, BaseObjectST );

public:
  FontsDictionary() {}

  void Put( SwfFont * font );
  SwfFont * GetFontById( int id );
  SwfFont * GetFontByName( const char * name );
  void FontNameUpdated( int id );

private:
  typedef map<int, Strong<SwfFont>> TFontsById;
  typedef map<string, Strong<SwfFont>> TFontsByName;

  TFontsById    byId;
  TFontsByName  byName;
};

} //namespace flash

#endif //FONTSDICT_H_INCLUDED
