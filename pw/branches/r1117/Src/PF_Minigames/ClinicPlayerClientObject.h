#ifndef CLINICPLAYERCLIENTOBJECT_H_INCLUDED
#define CLINICPLAYERCLIENTOBJECT_H_INCLUDED

#include "MovingUnitClientObject.h"
#include "MinigameWorldObject.h"
#include "DBClinic.h"

class DiAnimGraph;
class DiAnGrExtPars;

namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Clinic;
class ClinicPlayer;

class ClinicPlayerClientObject : public MovingUnitClientObject, public IClientNotifyCallback
{
	OBJECT_BASIC_METHODS( ClinicPlayerClientObject )

public:
  ClinicPlayerClientObject() : pDefaultAG( 0 ), pDefaultAGExtPars( 0 ) {}
  virtual ~ClinicPlayerClientObject();

  void SetClinic( Clinic * _clinic ) { clinic = _clinic; }
  void InitClinicPlayer( ClinicPlayer * player );

  virtual MinigameClientObject * RedirectMouseOver();

private:
  virtual void CreateSceneObject( const NDb::DBSceneObject* dbSceneObject );

  //IClientNotifyCallback:
  virtual void OnClientNotification(const char * eventId);

  const NDb::DBMinigame_Clinic & GetClinicDesc() const;

  CPtr<Clinic>            clinic;
  CPtr<ClinicPlayer>      clinicPlayer;
  DiAnimGraph *           pDefaultAG;
  DiAnGrExtPars *         pDefaultAGExtPars;
};

} // namespace PF_Minigames

#endif //CLINICPLAYERCLIENTOBJECT_H_INCLUDED
