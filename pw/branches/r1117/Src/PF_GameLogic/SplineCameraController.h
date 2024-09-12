#ifndef SPLINECAMERACONTROLLER_H_661044B
#define SPLINECAMERACONTROLLER_H_661044B

#include "Scene/CameraController.h"
#include "Scene/Camera.h"

#include "System/PlacementSpline.h"

namespace PF_Core
{

class SplineCameraController: public NScene::ICameraController
{
	OBJECT_BASIC_METHODS(SplineCameraController);

  typedef NScene::SCameraPosition SCameraPosition;
  typedef NScene::Time Time;

private:
  virtual void SetCamera( NScene::ICamera *pCamera ) {}
  
public:
  SplineCameraController( bool correctTiming = false);

  virtual const bool IsEffect() const { return false; } 
  virtual const bool IsActive() const { return !finalizing && curTime < totalTime; }

  virtual void Update( 
    SCameraPosition				* pWantedPos,
    const SCameraPosition & currentPos,
    const SCameraPosition & wantedPos,
    Time										timeDiff
  );

  virtual bool ProcessEvent( const Input::Event& _eEvent ){ return false; }
  
  void Init( const vector<CVec3>& positions, const vector<CVec3>& rotations, Time _totalTime );
  void Init( const vector<CVec3>& positions, const vector<CVec3>& rotations, Time _totalTime, const vector<float>& tensions );
  void Shutdown();

private:

  bool UpdateInternal( 
    SCameraPosition				* pWantedPos,
    const SCameraPosition & currentPos,
    const SCameraPosition & wantedPos,
    Time										timeDiff
  );


  Time curTime;
  Time totalTime; 
  CObj<SplineCameraController> pThis;

  CPlacementSpline placementSpline;

  bool firstUpdate;
  float saveRod;

  CVec3 lastPos;
  float velocity;
  float lastRelativeCurTime;

  float deltaReminder;
  bool finalizing;
  float scaleCameraFPS;
};

}
#endif //#define SPLINECAMERACONTROLLER_H_661044B
