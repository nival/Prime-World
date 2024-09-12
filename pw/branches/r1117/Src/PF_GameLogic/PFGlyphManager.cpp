#include "stdafx.h"
#include "PFGlyphManager.h"

#include "PFWorld.h"
#include "PFGlyph.h"
#include "PFClientObjectHelpers.h"

#include "Scene/DiAnGr.h"

namespace NWorld
{
PFGlyphsManager::PFGlyphsManager(CPtr<PFWorld> const& pWorld)
: PFWorldObjectBase( pWorld, 0 )
, pWorld(pWorld)
, lastGlyph(0)
{
}

void NWorld::PFGlyphsManager::Init( const NDb::GlyphManagerParams* overrideGlyphSettings )
{
  if ( overrideGlyphSettings == 0 )
  {
    NDb::Ptr<NDb::SessionRoot> pRoot = NDb::SessionRoot::GetRoot();

    pDBGlyphs = pRoot->logicRoot->glyphsDB;
    settings  = pRoot->logicRoot->aiLogic->glyphSettings;
  }
  else 
  {
    pDBGlyphs = overrideGlyphSettings->glyphs;
    settings  = overrideGlyphSettings->settings;
  }

  NI_VERIFY( IsValid( pDBGlyphs ), "Cannot find glyphs DB!" , return );

  GetWorld()->GetIAdventureScreen()->PreloadEffectsInResourceTree( pDBGlyphs, BADNODENAME );

  glyphs.resize(pDBGlyphs->glyphs.size());
}


CPtr<NWorld::PFGlyph> PFGlyphsManager::CreateGlyph( CVec3 const& position)
{
  vector<int> emptyIndices;
  for(int i = 0, count = glyphs.size(); i < count; ++i)
  { 
    if( !IsValid( glyphs[i] ) )
      emptyIndices.push_back(i);
  }
  
  if( settings.maxInstances <= ( glyphs.size() - emptyIndices.size() ) || emptyIndices.empty() )
    return NULL; // can`t create glyphs -> too much glyphs are already created

  int slotId = 0;

  if ( settings.spawnMode == NDb::GLYPHSPAWNMODE_RANDOMWEIGHT )
  {
    struct WeightGetter : NonCopyable
    {
      WeightGetter( const vector<NDb::GlyphEntry>& _container ) : container(_container) {}
      const vector<NDb::GlyphEntry>& container;
      int operator()( const int& item ) const
      {
        return container[item].weight;
      }
    } wg( pDBGlyphs->glyphs );

    slotId = GetWorld()->GetRndGen()->RollFromContainerByWeight( emptyIndices, wg );
  }
  else if ( settings.spawnMode == NDb::GLYPHSPAWNMODE_ORDERED )
  {
    slotId = lastGlyph;
    lastGlyph = ( lastGlyph + 1 ) % pDBGlyphs->glyphs.size();
  }

  const NDb::GlyphEntry& glyphEntry = pDBGlyphs->glyphs[slotId];

  NI_DATA_VERIFY( glyphEntry.glyph, "Invalid glyph entry", return 0 );
  
  glyphs[slotId] = new PFGlyph( pWorld, glyphEntry.glyph, position );
  
  return glyphs[slotId];
} 

} // namespace NWorld

REGISTER_WORLD_OBJECT_NM(PFGlyphsManager, NWorld);
