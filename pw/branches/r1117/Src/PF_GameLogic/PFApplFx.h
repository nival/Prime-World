#pragma once

#include "PFApplBuff.h"

namespace NWorld
{

class PFLogicObject;

class PFApplFX : public DBLinker<PFApplBuff, NDb::FXApplicator>
{
  WORLD_OBJECT_METHODS(0xE7A6C481, PFApplFX);

  explicit PFApplFX() {}

  virtual PFLogicObject* GetEffectOrigin();
  virtual PFLogicObject* GetEffectTarget();

public:

  PFApplFX( PFApplCreatePars const &cp ) : Base(cp) {}

  virtual bool Start();

  virtual const IUnitFormulaPars* GetObject( char const* objName ) const;

private:
  ZDATA_(DBLinker)
  Target origin;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&origin); return 0; }
};


}