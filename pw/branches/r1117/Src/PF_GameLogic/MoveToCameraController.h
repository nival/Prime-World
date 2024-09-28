#ifndef MOVETOCAMERACONTROLLER_H_716C6E5
#define MOVETOCAMERACONTROLLER_H_716C6E5

#include "Scene/CameraController.h"
#include "System\lerp.h"


namespace PF_Core
{

namespace Interpolation
{
template<class T>
class LerpWrapper
{
public: 
  T Update( float timeRelative )
  {
    return Lerp( from, to, timeRelative );
  }

  void Init( const T &from_, const T &to_ ) 
  {
    from = from_;
    to = to_; 
  } 

private:
  T from;
  T to;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

class MoveToCameraController: public NScene::ICameraController
{
	OBJECT_BASIC_METHODS(MoveToCameraController);

  typedef NScene::SCameraPosition SCameraPosition;
  typedef NScene::Time Time;
  
private:
  virtual void SetCamera( NScene::ICamera *pCamera ) {}
  
public:
  MoveToCameraController();

  virtual const bool IsEffect() const { return false; } 
  virtual const bool IsActive() const { return curTime < totalTime; }

  virtual void Update( 
    SCameraPosition				* pWantedPos,
    const SCameraPosition & currentPos,
    const SCameraPosition & wantedPos,
    Time										timeDiff
  );

  virtual bool ProcessEvent( const Input::Event& _eEvent ){ return false; }
  
  void Init( const SCameraPosition &from, const SCameraPosition &to, Time totalTime );
  void Init( const SCameraPosition &from, const NDb::ViewCamera &to, Time totalTime );
    
private:
  Interpolation::LerpWrapper<CVec3> positionInterpolator;
  Interpolation::LerpWrapper<float> yawInterpolator;
  Interpolation::LerpWrapper<float> pitchInterpolator;
  Interpolation::LerpWrapper<float> rollInterpolator;
  Interpolation::LerpWrapper<float> rodInterpolator;

  Time curTime;
  Time totalTime; 
  CObj<MoveToCameraController> pThis;
};

}

#endif //#define MOVETOCAMERACONTROLLER_H_716C6E5