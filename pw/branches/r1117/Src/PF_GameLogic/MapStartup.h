#ifndef MAPSTARTUP_H_INCLUDED
#define MAPSTARTUP_H_INCLUDED

#include "Core/GameTypes.h"


namespace NDb
{
  struct AdvMap;
  struct AdvMapSettings;
  struct AdventureCameraSettings;
}


class LoadingProgress;


namespace NWorld
{

class PFWorld;

class MapLoadingJob : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( MapLoadingJob, BaseObjectMT )

public:
  MapLoadingJob( NCore::IWorldBase * _world, const NCore::MapStartInfo & _mapStartInfo, const NDb::AdvMapDescription * _advMapDescription, const NDb::AdvMapSettings * _advMapSettings, const NDb::AdvMap * _advMap, bool _isReconnecting );

  LoadingProgress * GetProgress() const { return progress; }

  const NDb::AdvMap * MapResource() const { return advMap; }
  const NDb::AdvMapDescription * MapDescriptionResource() const { return advMapDescription; }
  const NDb::AdvMapSettings * MapSettingsResource() const { return advMapSettings; }

  bool DoTheJob(); //To be called from parallel thread

  const NDb::AdventureCameraSettings * GetCameraSettings() {return camSettings.GetPtr();}

  CObj<PFWorld> GetWorld() const { return world; }

private:
  bool InitializeEnvironment();
  void SetupCamera();

  CObj<PFWorld>           world;
  NCore::MapStartInfo     mapStartInfo;
  NDb::Ptr<NDb::AdvMap>   advMap;
  NDb::Ptr<NDb::AdvMapDescription>  advMapDescription;
  NDb::Ptr<NDb::AdvMapSettings>     advMapSettings;
  CObj<LoadingProgress>   progress;
  NDb::Ptr<NDb::AdventureCameraSettings> camSettings;
  bool isReconnecting;
};

} //namespace NWorld

#endif //MAPSTARTUP_H_INCLUDED
