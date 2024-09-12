#pragma once

#include "../Render/texture.h"

#include "FontRender.h"
#include "Alphabet.h"


namespace UI
{

struct FontFileCache : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( FontFileCache, BaseObjectST );

  vector<unsigned char> alphaBytes;
  vector<unsigned char> kerningBytes;
};

namespace EFontLocation
{
  enum Enum
  {
    SystemFont,
    GameFont,
    Last
  };
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class FontRenderer : public IFontRenderer, public BaseObjectST
{
	NI_DECLARE_REFCOUNT_CLASS_2( FontRenderer, IFontRenderer, BaseObjectST );

public:
  FontRenderer();
  ~FontRenderer();

  // from FontRenderer
  void AllocatePlace( Glyph& glyph, int _width, int _height );

  // from IFontRenderer
  virtual void Initialize();
  virtual void Release();

  virtual Render::Texture2DRef & GetFontsTexture() { return fontTexture; }

  virtual IAlphabet * FindNearestAlphabet( const char * ttfFileName, int size, bool systemFont, bool bold, bool italic, bool forFlash );

  virtual const Rect & GetNoCropRect();

  virtual IFontStyle* GetFontStyle( const NDb::UIFontStyle* _style ); 
  virtual IFontStyle* GetDebugFontStyle( int size );

  FontFileCache* GetFontFileCache( const char * ttfFileName, EFontLocation::Enum fontLocation );

private:

  void InitDefaultFontCache();
  void CopyFileToCache( Stream* _stream, FontFileCache* _cache, const char* _fileName );

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class FontKey
  {
    //FIXME: hacky way to store name to avoid extra allocations on std::map::find() calls etc
    //Use with great caution!
    const char * pszName;
    nstl::string strName;
    int size;
    bool bold;
    bool italic;
    bool flashFont;

    FontKey() : pszName( 0 ), size( 0 ) {}

  public:
    enum StringKeyTypeEnum { StringKeyType };
    enum PszKeyTypeEnum { PszKeyType };
    FontKey( StringKeyTypeEnum, const char * _name, int _size, bool _bold, bool _italic, bool _flashFont ) 
      : pszName( 0 ), strName( _name ), size( _size ), bold( _bold ), italic( _italic ), flashFont(_flashFont) {}
    FontKey( PszKeyTypeEnum, const char * _name, int _size, bool _bold, bool _italic, bool _flashFont ) 
      : pszName( _name ), strName(nstl::string::eNotAllocateOnConstruct), size( _size ), bold( _bold ), italic( _italic ), flashFont(_flashFont) {}

    const char * GetName() const { return pszName ? pszName : strName.c_str(); }
    int GetSize() const { return size; }

    bool operator == ( const FontKey & other ) const
    {
      return ( bold == other.bold ) && ( italic == other.italic ) && 
             ( size == other.size ) && ( flashFont == other.flashFont ) && !strcmp( GetName(), other.GetName() );
    }
  };

  struct FontKeyHash
  {
    int operator()( const FontKey &fontKey ) const
    {
      //TODO: add 'size', 'bold' and 'italic' members to hash!
      return nstl::hash<const char *>()( fontKey.GetName() ) ^ fontKey.GetSize();
    }
  };

  typedef nstl::hash_map< FontKey, Strong<Alphabet>, FontKeyHash > AlphabetCache;
  typedef nstl::hash_map< NDb::DBID, Strong<IFontStyle> > FontStyles;
  typedef nstl::hash_map< int, Strong<IFontStyle> > DebugFontStyles;
  typedef nstl::hash_map< nstl::string, Strong<FontFileCache > > FontFileCaches;

  FontFileCaches fontFileCaches[EFontLocation::Last];
  Strong<FontFileCache> defualtFontCache;

  AlphabetCache alphabetCache;
  FontStyles fontStyles;
  DebugFontStyles debugFontStyles;

  FT_Library ftLibrary;

  Render::Texture2DRef fontTexture;

  size_t freeX;
  size_t freeY;
  size_t maxY;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace UI
