#ifndef PFAICONTROLLERINTERFACES_H_89410
#define PFAICONTROLLERINTERFACES_H_89410


namespace NWorld
{

class PFBaseUnit;
class PFBaseMaleHero;
class Target;

static const int RANDOM_LINE = -1;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
interface IPFAIController : public IObjectBase
{
  virtual PFBaseMaleHero* GetHero() const = 0;
  virtual int GetLineNumber() const  = 0;

  virtual int GetStackSize() const = 0;
  virtual const char* GetCurrentStateName() = 0;

  virtual void Step( float timeDelta ) = 0;
  virtual void StopHero() = 0;
  virtual bool OnMinimapSignal( const Target& target, bool dedicated ) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
interface IPFSeriesAIController
{
  virtual void StartPushPath( const vector<CVec2>& path ) = 0;
  virtual void StartSupport( PFBaseUnit* pMaster ) = 0;
  virtual void StartGuardPoint( const CVec2& point, float radius, float lookToAreaRadius ) = 0;
  virtual void EnableMinimapSignal( bool enable ) = 0;
};

} // namespace NWorld


#endif //#define PFAICONTROLLERINTERFACES_H_89410