#pragma once
#include "StaticSceneComponent.h"
#include "Scene.h"
#include "../Render/WaterMesh.h"

namespace NScene
{

class WaterSceneComponent : public StaticSceneComponent
{
public:
	typedef NDb::DBWaterSceneComponent NDbType;

  seDECLARE_RING_CLASS(WaterSceneComponent, waterSCRingPart, WaterSCRing);

  struct WaterSCFunc : public NonCopyable
  {
    virtual void operator() (WaterSceneComponent &wsc) = 0;
  };


	WaterSceneComponent( const NDb::DBWaterSceneComponent* pObject, const NDb::AttachedSceneComponent* pObj, const Placement& pos );
	~WaterSceneComponent();

  Render::WaterMesh *GetWaterMesh() { return dynamic_cast<Render::WaterMesh*>(Get(pStaticMesh)); }
  
  static void ForAllWaterSC(WaterSCFunc &func);

protected:
  static WaterSCRing  waterSCRing;

  WaterSCRing::Part  waterSCRingPart;
};

}

