#ifndef SPRINGINTERPOLER_H_INCLUDED
#define SPRINGINTERPOLER_H_INCLUDED

#include "../System/MathTools.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace PF_Minigames
{


// spring-damp time based interpolator with inner velocity
//TODO: generalize and move to Foundation
template< class T, class TPolicy >
class SpringInterpoler : public TPolicy
{
public:
  SpringInterpoler() :
    springCoeff( 0 ), dampingCoeff( 0 ), forceDesiredTreshold( 0 ),
    value( TPolicy::ZeroValue() ), velocity( TPolicy::ZeroValue() ),
    enabled( true )
  {
  }

  SpringInterpoler( float damping, float spring, float threshold ) :
    springCoeff( spring ),
    dampingCoeff( damping ),
    forceDesiredTreshold( threshold ),
    value( TPolicy::ZeroValue() ), velocity( TPolicy::ZeroValue() ),
    enabled( true )
  {
  }

  void Enable( bool enable ) { enabled = enable; }

  const T & Get() const { return value; }
  const T & Velocity() const { return velocity; }

  void Set( const T & v ) { value = v; }
  void Reset( const T & v ) { value = v; velocity = TPolicy::ZeroValue(); }

  const T & Update( const T & desired, float deltaTime )
  {
    T offs = TPolicy::Delta( value, desired );
    if ( !enabled || ( ( TPolicy::Norm( offs ) < forceDesiredTreshold ) && ( TPolicy::Norm( velocity ) < forceDesiredTreshold ) ) )
    {
      value = desired;
      velocity = TPolicy::ZeroValue();
      return desired;
    }

    T accel = springCoeff * offs - dampingCoeff * velocity;

    velocity += accel * deltaTime;

    value += velocity * deltaTime;
    return value;
  }

private:
  float springCoeff;
  float dampingCoeff;
  float forceDesiredTreshold;
  T value;
  T velocity;
  bool enabled;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SpringInterpolerFloatPolicy
{
public:
  static float ZeroValue() { return 0; }
  static float Delta( float from, float to ) { return to - from; }
  static float Norm( float value ) { return fabs( value ); }
};

class SpringInterpolerVec3Policy
{
public:
  static const CVec3 & ZeroValue() { return VNULL3; }
  static CVec3 Delta( const CVec3 & from, const CVec3 & to ) { return to - from; }
  static float Norm( const CVec3 & value ) { return value.Length(); }
};

class SpringInterpolerAngularPolicy : public SpringInterpolerFloatPolicy
{
public:
  static float Delta( float from, float to )
  {
    from = NormalizeAngle( from );
    to = NormalizeAngle( to );

    int swapped = 1;

    if(to < from)
    {
      std::swap( from, to );
      swapped = -swapped;
    }

    float delta = to - from;

    if( delta <= FP_PI )
      return delta * swapped;

    swapped = -swapped;

    return ( FP_2PI - delta ) * swapped;
  }

private:
  static float NormalizeAngle( float a )
  {
    float x = ( a + FP_PI ) / FP_2PI;
    x -= floorf( x );
    return FP_2PI * ( x - 0.5f );
  }
};

} // namespace PF_Minigames

#endif //SPRINGINTERPOLER_H_INCLUDED
