#ifndef EASELVIEWALCHEMISTPOT_H_INCLUDED
#define EASELVIEWALCHEMISTPOT_H_INCLUDED


namespace NDb
{
  struct BasicEffectAttached;
}

namespace NScene
{
  class SceneObject;
}

namespace PF_Core
{
  class BasicEffectAttached;
};

namespace PF_Minigames
{

class Easel;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class EaselViewAlchemistPot : public CObjectBase
{
  OBJECT_BASIC_METHODS( EaselViewAlchemistPot );

public:
  EaselViewAlchemistPot() {}
	~EaselViewAlchemistPot() 
	{
		NI_ASSERT(!effect, "Effect in EaselViewAlchemistPot should be removed in OnDestroyContents()");
	}

  virtual void OnDestroyContents();

  bool InitPot( Easel * _easel, const NDb::BasicEffectAttached * dbEffect );

  const Placement & PotPlacement() const { return potPlacement; }

  bool VisualIsValid() const { return effect ? true : false; }

  virtual void Update( float deltaTime, bool gameOnPause );

private:
  CPtr<Easel> easel;
  CObj<PF_Core::BasicEffectAttached> effect;
  Placement  potPlacement;

  void KillEffect();
};

} //namespace PF_Minigames

#endif //EASELVIEWALCHEMISTPOT_H_INCLUDED
