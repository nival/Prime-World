#pragma once

#include "DBGameLogic.h"
#include "PFWorldObjectBase.h"

namespace NWorld
{
  class PFWorld;
  class PFGlyph;

  class PFGlyphsManager : public PFWorldObjectBase
  { 
    WORLD_OBJECT_METHODS(0x2C6853C0, PFGlyphsManager)

    PFGlyphsManager() {}

    typedef vector<CPtr<PFGlyph> > TGlyphs;
    ZDATA_(PFWorldObjectBase)
    TGlyphs       glyphs;    
    CPtr<PFWorld> pWorld;
		NDb::Ptr<NDb::GlyphsDB> pDBGlyphs;
		NDb::GlyphSettings      settings;
    int                     lastGlyph;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFWorldObjectBase*)this); f.Add(2,&glyphs); f.Add(3,&pWorld); f.Add(4,&pDBGlyphs); f.Add(5,&settings); f.Add(6,&lastGlyph); return 0; }
    PFGlyphsManager(CPtr<PFWorld> const& pWorld);
    void Init( const NDb::GlyphManagerParams* overrideGlyphSettings );

    NDb::GlyphSettings const& GetSettings() const { return settings;}
    const NDb::GlyphsDB* GetGlyphsDB() const { return pDBGlyphs; }
    CPtr<PFGlyph> CreateGlyph( CVec3 const& position); 
		virtual bool NeedToBeStepped() { return false; }
  };

}