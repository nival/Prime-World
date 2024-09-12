#ifndef FEMALEMALEASSISTEFFECT_H_73625CF
#define FEMALEMALEASSISTEFFECT_H_73625CF
#include "./../DBVisualRoots.h"

namespace NWorld 
{ 
class PFBaseHero;
class PFBaseUnit;

namespace AIWorldFacets
{
struct IFemaleMaleAssistEffectFlashConnection;

class FemaleMaleAssistEffect: public CObjectBase
{
  OBJECT_METHODS(0x67863B01, FemaleMaleAssistEffect)
  
public:
  typedef vector< PFBaseHero * > HeroesCont;
  class ClientObject;
  
public:
  FemaleMaleAssistEffect();
  ~FemaleMaleAssistEffect();
  void OnUnitDie( CPtr<PFBaseUnit> pVictim, CPtr<PFBaseUnit> pKiller, const HeroesCont &assistants ) const;
  
private:
  void PlayEffect( CPtr<PFBaseUnit> pKiller, CPtr<PFBaseUnit> pAssistant ) const;

private:
  ScopedPtr<IFemaleMaleAssistEffectFlashConnection> pFlashConnection;

  ZDATA
public:
  ZEND int operator&( IBinSaver &f ) { return 0; }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}}

#endif //#define FEMALEMALEASSISTEFFECT_H_73625CF