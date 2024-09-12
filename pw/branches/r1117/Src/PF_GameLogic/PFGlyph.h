#pragma once

#include "../System/NameMap.h"
#include "PFPickupable.h"

#include "DBStats.h"

namespace NGameX
{
  class GlyphsDB;
  class PFWorld;
  class PFClientChest;
  class PFClientGlyph;
}

namespace NWorld
{

class PFBaseMaleHero;
class PFGlyphsManager;
class PFGlyph;

//////////////////////////////////////////////////////////////////////////
class PFGlyphSpawner : public PFWorldObjectBase
{
  WORLD_OBJECT_METHODS( 0xF61DC02, PFGlyphSpawner );

public:
  PFGlyphSpawner( const CPtr<PFWorld>& pWorld, const NDb::AdvMapObject& dbObject );

  virtual void Hide(bool hide);
private:
  PFGlyphSpawner() : hidden(false) {}
  virtual bool Step(float dtInSeconds);
  const NDb::GlyphSettings& GetSettings() const;
  CPtr<NWorld::PFGlyph> CreateGlyph( CVec3 const& position);

  ZDATA_(PFWorldObjectBase);
  CVec3                 position;
  float                 spawnOffset;
  CPtr<PFGlyph>         pSpawnedGlyph;  
  CPtr<PFGlyphsManager> pManager;
  NDb::Ptr<NDb::GlyphSpawner>  pDesc;
  string scriptName;
  bool hidden;
  int lastGlyph;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFWorldObjectBase*)this); f.Add(2,&position); f.Add(3,&spawnOffset); f.Add(4,&pSpawnedGlyph); f.Add(5,&pManager); f.Add(6,&pDesc); f.Add(7,&scriptName); f.Add(8,&hidden); f.Add(9,&lastGlyph); return 0; }
};



//////////////////////////////////////////////////////////////////////////
class PFGlyph : public PFPickupableObjectBase, public NNameMap::Map
{
  WORLD_OBJECT_METHODS_WITH_CLIENT(0xF61DC03, PFGlyph, NGameX::PFClientGlyph);
  NAMEMAP_DECLARE;

protected:
  wstring const &GetName() const { return pDesc->name.GetText(); }

  virtual void  OnPickedUp( PFBaseUnit* pPicker );
  virtual void  OnDie();
  virtual bool  IsVulnerable() const { return false; }
  explicit PFGlyph() {};
  virtual const NDb::Ability* GetPickupAbility() const { return pDesc->pickupAbility; }

  ZDATA_(PFPickupableObjectBase);
  ZNOPARENT(NNameMap::Map)
  int visUnitID1;
  int visUnitID2;
  NDb::Ptr<NDb::Glyph>  pDesc;
  string scriptName;
  bool enabled;
  bool hidden;
  int glyphNumber;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFPickupableObjectBase*)this); f.Add(2,&visUnitID1); f.Add(3,&visUnitID2); f.Add(4,&pDesc); f.Add(5,&scriptName); f.Add(6,&enabled); f.Add(7,&hidden); f.Add(8,&glyphNumber); return 0; }

  PFGlyph( const CPtr<PFWorld>& pWorld, const NDb::Ptr<NDb::Glyph>& pGlyphDesc, const CVec3& position );

  virtual void Reset();
  virtual bool CanBePickedUpBy( const PFBaseUnit* pPicker ) const;

  void SetEnabled( bool _enabled ) { enabled = _enabled; }


  NDb::Ptr<NDb::Glyph> const& GetDBDesc() const { return pDesc; }
  void SetScriptName( const string& scriptName_ ) { scriptName = scriptName_; }

  virtual void Hide(bool hide);
  virtual void OpenWarFog();
  virtual void CloseWarFog();
};



//////////////////////////////////////////////////////////////////////////
class PFNatureGlyph : public PFPickupableObjectBase, public NNameMap::Map
{
  WORLD_OBJECT_METHODS_WITH_CLIENT(0xF624BC0, PFNatureGlyph, NGameX::PFClientChest);
  NAMEMAP_DECLARE;

public:
  PFNatureGlyph( const CPtr<PFBaseMaleHero>& targetHero_, NDb::ERoute routeID_, const CPtr<PFWorld>& pWorld, const NDb::Ptr<NDb::GameObject> _gameObject, const CVec3& position );
  void SetPosition( const CVec3 newPosition );
  void SetVisible( bool newVisible );
  void Destroy();
  virtual void Reset();
protected:
  wstring const &GetName() const 
  { 
    static wstring tmpName = L"Nature Glyph (Temporary string)";
    return tmpName; 
  }

  virtual void  OnPickedUp( const CPtr<PFBaseHero>& pPicker );
  explicit PFNatureGlyph() {};

  ZDATA_(PFPickupableObjectBase);
  ZNOPARENT(NNameMap::Map)
    bool                  bVisible;   // видимость глифа (глиф не виден, если он находится в самом конце линии)
  CPtr<PFBaseMaleHero>  targetHero; // герой-мальчик, который будет видеть глиф
  NDb::ERoute           routeID;    // ID линии в nature-карте
  int visUnitID;
  NDb::Ptr<NDb::GameObject> gameObject;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFPickupableObjectBase*)this); f.Add(2,&bVisible); f.Add(3,&targetHero); f.Add(4,&routeID); f.Add(5,&visUnitID); f.Add(6,&gameObject); return 0; }
};

} //namespace NWorld
