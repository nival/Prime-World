#pragma once

#include "../PF_Core/WorldObject.h"

namespace PF_Minigames
{


class EaselWorldObject : public PF_Core::WorldObjectBase
{
  DONOT_REGISTER_SAVELOAD_CLASS
  OBJECT_METHODS( 0x9D8AD402, EaselWorldObject );
public:
  EaselWorldObject( PF_Core::IWorld* _pWorld ) : PF_Core::WorldObjectBase( _pWorld, false ), clientID(-1) {}
  virtual ~EaselWorldObject() {}

  int GetClientID() const { return clientID; }
  void SetClientID( int id ) { clientID = id; }

  int clientID;

protected:
  EaselWorldObject() : clientID(-1) {}
private:
  ZDATA_(PF_Core::WorldObjectBase)

public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PF_Core::WorldObjectBase*)this); return 0; }
};


} // namespace PF_Minigames