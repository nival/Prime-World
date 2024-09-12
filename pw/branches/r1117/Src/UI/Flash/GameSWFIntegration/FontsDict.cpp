#include "TamarinPCH.h"
#include "FontsDict.h"

#include "FontTags.h"

NI_DEFINE_REFCOUNT( flash::FontsDictionary )

namespace flash
{


void FontsDictionary::Put( SwfFont * font )
{
  Strong<SwfFont> & slot = byId[font->Data().FontID];
  NI_DATA_ASSERT( !slot, NStr::StrFmt( "Duplicate font id %d (%s)", (int)font->Data().FontID, font->Data().FontName.c_str() ) );
  slot = font;

  NI_ASSERT( !font->Data().FontName.empty(), "" );
  byName[font->Data().FontName] = font;
}



SwfFont * FontsDictionary::GetFontById( int id )
{
  TFontsById::iterator it = byId.find( id );
  NI_VERIFY( it != byId.end(), NStr::StrFmt( "Unknown font id %d", id ), return 0 );
  return it->second;
}



SwfFont * FontsDictionary::GetFontByName( const char * name )
{
  TFontsByName::iterator it = byName.find( name );
  //TODO add db fonts 
  //NI_VERIFY( it != byName.end(), NStr::StrFmt( "Unknown font name '%s'", name ), return 0 );
  if (it == byName.end()) 
    return 0;
  return it->second;
}



void FontsDictionary::FontNameUpdated( int id )
{
  TFontsById::iterator it = byId.find( id );
  NI_VERIFY( it != byId.end(), NStr::StrFmt( "Unknown font id %d", id ), return );

  NI_ASSERT( !it->second->Data().FontName.empty(), "" );

  for ( TFontsByName::iterator nameIt = byName.begin(); nameIt != byName.end(); ++nameIt )
    if ( nameIt->second == it->second )
    {
      byName.erase( nameIt );
      break;
    }

  byName[it->second->Data().FontName] = it->second;
}

} //namespace flash
