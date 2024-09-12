#include "stdafx.h"

namespace FMOD
{
class Event;
}

namespace NSoundScene
{
  void SetListener( CVec3 const &position, CVec3 const &forward, CVec3 const &up ) {}
  void EventSystemSetListener( CVec3 const &position, CVec3 const &forward, CVec3 const &up, CVec3 const &anchor ) {}
  bool GetEventLength( FMOD::Event *pEvent, int &_lenght ) { _lenght = 0; return false; }
  FMOD::Event* GetEvent( const NDb::DBFMODEventDesc & eventDesc ) { return 0; }
  FMOD::Event* EventStart( const NDb::DBFMODEventDesc& eventDesc, const CVec3& pPosition ) { return 0; }
  bool EventStop( FMOD::Event *pEvent, bool immediatly = false ) { return false; }
  bool SetEventPos( FMOD::Event * pEvent, const CVec3 * pPosition ) { return false; }
}
