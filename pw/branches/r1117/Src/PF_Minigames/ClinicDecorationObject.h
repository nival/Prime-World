#ifndef CLINICDECORATIONOBJECT_H_INCLUDED
#define CLINICDECORATIONOBJECT_H_INCLUDED

#include "MinigameClientObject.h"

namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Clinic;

class ClinicDecorationClientObject : public MinigameClientObject
{
	OBJECT_BASIC_METHODS( ClinicDecorationClientObject )

public:
  ClinicDecorationClientObject() {}

  void SetClinic( Clinic * _clinic ) { }
};

} // namespace PF_Minigames

#endif //CLINICDECORATIONOBJECT_H_INCLUDED
