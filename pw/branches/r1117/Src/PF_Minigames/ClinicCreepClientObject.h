#ifndef CLINICCREEPCLIENTOBJECT_H_INCLUDED
#define CLINICCREEPCLIENTOBJECT_H_INCLUDED

#include "MovingUnitClientObject.h"
#include "MinigameWorldObject.h"
#include "DBClinic.h"

namespace UI
{
class ImageLabel;
class ProgressBar;
};


namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Clinic;
class ClinicCreep;

class ClinicCreepClientObject : public MovingUnitClientObject, public IClientNotifyCallback
{
	OBJECT_BASIC_METHODS( ClinicCreepClientObject )

public:
  ClinicCreepClientObject();
  virtual ~ClinicCreepClientObject();

  virtual void SetVisible( bool _visible );
  virtual void Update(float deltaTime, bool gameOnPause);

  void SetClinic( Clinic * _clinic ) { clinic = _clinic; }
  void InitClinicCreep( ClinicCreep * creep );

  virtual MinigameClientObject * RedirectMouseOver();
  virtual void OnMouseEnter();
  virtual void OnMouseLeave();

  virtual bool NeedHighlight() const;
  virtual const Render::HDRColor& GetHighlightColor() const;

private:
  enum ECreepAnimNodes
  {
    eIdle,
    eFriendshipIdle,
    eLazy,
    eUnsatisfied,
    eSatisfied,
    eUsingTable,
    eUsingBed,
    eUsingWashtab,
    eUsingGamePlace,
    eLastAnimNode
  };

  const NDb::DBMinigame_Clinic & GetClinicDesc() const;
  const NDb::BaseUIMaterial* GetWishUIMaterial() const;
  const NDb::BaseUIMaterial* GetFriendshipUIMaterial() const;

  CPtr<Clinic>            clinic;
  CPtr<ClinicCreep>       clinicCreep;

  bool                    visible;
  bool                    mouseOver;
  Weak<UI::ImageLabel>    wndName;
  Weak<UI::ProgressBar>   wndProgress;
  Weak<UI::ImageLabel>    wndWish, wndFriendship;

  struct SAnimInfo
  {
    SAnimInfo(const char * name = NULL) : nodeId(0), nodeName(name) {}
    unsigned              nodeId;
    const char *          nodeName;
  };

  SAnimInfo               animNodes[eLastAnimNode];

  //IOvertipTarget:
  virtual bool IsOvertipVisible() const { return visible; }
  virtual void SetupOvertipLayout(UI::Window * pWindow, const Overtips::SOvertipId & overtipId);
  virtual void UpdateOvertipLayout(UI::Window * pWindow, const Overtips::SOvertipId & overtipId);

  //IClientNotifyCallback:
  virtual void OnClientNotification(const char * eventId);

  void SetMovingAnimNode(bool moving, ECreepAnimNodes node);
  void PlayAnimNode(ECreepAnimNodes node);
};

} // namespace PF_Minigames


#endif //CLINICCREEPCLIENTOBJECT_H_INCLUDED
