#ifndef ALPHABET_H_INCLUDED
#define ALPHABET_H_INCLUDED

#include <ft2build.h>
#include FT_FREETYPE_H


#include "FontRender.h"

namespace UI
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class FontRenderer;
struct FontFileCache;

class Alphabet : public IAlphabet, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( Alphabet, IAlphabet, BaseObjectST );

public:
  Alphabet( FontRenderer* _fontRenderer );

  void LoadAlphabet( FT_Library ftLibrary, const char* _ttfFileName, int _fontSize, bool _bold, bool _italic, bool loadSystemFont, bool forFlash );

  // from IAlphabet
  virtual const Glyph & GetGlyph( wchar_t symbol );
  virtual void    SetupMetric( SFontMetric & metric, float gapAbove, float gapUnder, const SFontRenderTweaks & tweaks ) const;
  virtual float   GetStringLength( const wchar_t *text, unsigned length, float maxWidth, unsigned * charsFitIn, const SFontRenderTweaks & tweaks );
  virtual void    DrawString( const wchar_t *text, unsigned length, float x, float y, Render::BaseMaterial * fontMaterial, const Render::Color & color, const Rect & cropRect, const SFontRenderTweaks & tweaks, const CVec2& _scale );

  virtual float   GetHeightScale() const    { return heightK; }

private:
  Alphabet() {}

  static void MakeOutlineItalic( FT_GlyphSlot  slot );
  float GetKerningAmount( wchar_t first, wchar_t second ) const;

  typedef nstl::hash_map<wchar_t, Glyph> GlyphHashMap;

  GlyphHashMap glyphHashMap;

  bool bold;
  bool italic;

  float widthK;
  float heightK;

  FT_FaceRec_* face;

  Weak<FontFileCache> fontFileCache;
  Weak<FontRenderer> fontRenderer;

  float fontHeight;
  float fontAscent;

  Glyph spaceGlyph;

  bool flashFont;
};

} // namespace UI

#endif //ALPHABET_H_INCLUDED
