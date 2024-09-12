#pragma once

namespace PF_Minigames
{

// forward declaration
class LuxBall;
class PathConverter;
class BambooRollInConverter;
class WellRollOutConverter;
class LuxPath;

//////////////////////////////////////////////////////////////////////////
//
// ball coords converter class
// converts world coords to client coords
//
//////////////////////////////////////////////////////////////////////////
class BallCoordsConverter : public CObjectBase
{
  OBJECT_BASIC_METHODS( BallCoordsConverter )
public:
  explicit BallCoordsConverter( PathConverter* _converter );
  virtual ~BallCoordsConverter();

  CVec3 GetClientCoords( LuxBall* _ball );
  CVec3 GetClientDirection( LuxBall* _ball );

  PathConverter* GetConverter() const { return pathConverter; }
  
private:
  CPtr<PathConverter> pathConverter;

protected:
  BallCoordsConverter() {}

  virtual CVec3 vCalculateClientCoords( LuxBall* _ball );
  virtual CVec3 vCalculateClientDirection( LuxBall* _ball );
  
};

//////////////////////////////////////////////////////////////////////////
//
// spline ball coords converter class
//
//////////////////////////////////////////////////////////////////////////
class SplineBallCoordsConverter : public BallCoordsConverter
{
  OBJECT_BASIC_METHODS( SplineBallCoordsConverter )

public:
  SplineBallCoordsConverter(PathConverter* _converter,
                            BambooRollInConverter* _rollin,
                            WellRollOutConverter* _rollout);
  ~SplineBallCoordsConverter();

private:
  SplineBallCoordsConverter() {}

  CVec3 CalculateBForRollIn(const SVector &worldCoords);
  CVec3 CalculateBForRollOut(const SVector &worldCoords);

  CPtr<BambooRollInConverter> rollinConverter;
  CPtr<WellRollOutConverter> rolloutConverter;

protected:

  virtual CVec3 vCalculateClientCoords( LuxBall* _ball );  
  virtual CVec3 vCalculateClientDirection( LuxBall* _ball );

};

//////////////////////////////////////////////////////////////////////////
//
// scorpion coords converter class
//
//////////////////////////////////////////////////////////////////////////
class ScorpionCoordsConverter : public CObjectBase
{
  OBJECT_BASIC_METHODS( ScorpionCoordsConverter )
public:
  ScorpionCoordsConverter(PathConverter* _converter,
                          BambooRollInConverter* _rollin,
                          WellRollOutConverter* _rollout);
  ~ScorpionCoordsConverter();

  CVec3 GetClientCoords(LuxPath* _path,
                        int64 currDistance,
                        const SVector &worldCoords);

private:
  ScorpionCoordsConverter() {}

  CVec3 CalculateBForRollIn(const SVector &worldCoords);
  CVec3 CalculateBForRollOut(const SVector &worldCoords);
  CVec3 CalculateBForOnBoard(const SVector &worldCoords);

  CPtr<PathConverter> pathConverter;
  CPtr<BambooRollInConverter> rollinConverter;
  CPtr<WellRollOutConverter>  rolloutConverter;

protected:

};

}

