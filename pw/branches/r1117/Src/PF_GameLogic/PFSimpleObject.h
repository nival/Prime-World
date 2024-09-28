#pragma once

#include "PFLogicObject.h"

namespace NGameX { class PFClientSimpleObject; class PFClientMultiStateObject; }

namespace NWorld
{

class PFSimpleObject : public PFWorldObjectBase
{
	WORLD_OBJECT_METHODS_WITH_CLIENT( 0x2C59BAC1, PFSimpleObject, NGameX::PFClientSimpleObject )
protected:
  explicit PFSimpleObject() {}
  ZDATA_(PFWorldObjectBase);
  ZNOCRC
  ZNOMAPOBJECT
  NDb::AdvMapObject dbObject;
  ZNOMAPOBJECTEND
  ZNOCRCEND
  bool isHidden;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFWorldObjectBase*)this);  if(!f.IsChecksum()){  if(!IsMapObject()){ f.Add(2,&dbObject);  }  } f.Add(3,&isHidden); return 0; }
	PFSimpleObject(PFWorld* pWorld, const NDb::AdvMapObject &_dbObject);
  void Hide(bool hide);
	virtual void Reset();
	virtual bool Step( float );

   using PFWorldObjectBase::Die;
};

class PFMultiStateObject : public PFLogicObject
{
  WORLD_OBJECT_METHODS_WITH_CLIENT( 0xF64C3C0, PFMultiStateObject, NGameX::PFClientMultiStateObject )
protected:
  explicit PFMultiStateObject() {}
  ZDATA_(PFLogicObject);
  ZNOCRC
  ZNOMAPOBJECT
  NDb::AdvMapObject dbObject;
  ZNOMAPOBJECTEND
  ZNOCRCEND
  int prevNatureType;
  bool prevNight;
  bool isHidden;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFLogicObject*)this);  if(!f.IsChecksum()){  if(!IsMapObject()){ f.Add(2,&dbObject);  }  } f.Add(3,&prevNatureType); f.Add(4,&prevNight); f.Add(5,&isHidden); return 0; }
  PFMultiStateObject(PFWorld* pWorld, const NDb::AdvMapObject &_dbObject);
	virtual void UpdateNatureType();
  virtual void UpdateDayNightState(const bool night);
  void Hide(bool hide);
	virtual void Reset();
	virtual bool Step( float );

protected:
  virtual bool NeedToBeStepped();
  NDb::DBSceneComponent const * GetDBSceneComponent();
  
};

class PFAdvMapObstacle : public PFWorldObjectBase
{
	WORLD_OBJECT_METHODS( 0xE7879C41, PFAdvMapObstacle )

protected:
  explicit PFAdvMapObstacle() {}
  ZDATA_(PFWorldObjectBase);
  ZNOCRC
  ZNOMAPOBJECT
  NDb::AdvMapObject dbObject;
  ZNOMAPOBJECTEND
  ZNOCRCEND
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFWorldObjectBase*)this);  if(!f.IsChecksum()){  if(!IsMapObject()){ f.Add(2,&dbObject);  }  } return 0; }
	PFAdvMapObstacle(PFWorld* pWorld, const NDb::AdvMapObject &_dbObject);
  void Hide(bool hide);
};

class PFWarFogUnblock : public PFWorldObjectBase
{
  WORLD_OBJECT_METHODS( 0xEF91A283, PFWarFogUnblock )

protected:
  explicit PFWarFogUnblock() {}
  ZDATA_(PFWorldObjectBase);
  ZNOCRC
  ZNOMAPOBJECT
  NDb::AdvMapObject dbObject;
  ZNOMAPOBJECTEND
  ZNOCRCEND
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFWorldObjectBase*)this);  if(!f.IsChecksum()){  if(!IsMapObject()){ f.Add(2,&dbObject);  }  } return 0; }
  PFWarFogUnblock(PFWorld* pWorld, const NDb::AdvMapObject &_dbObject);
};

}
