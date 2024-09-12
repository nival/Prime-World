#include "stdafx.h"
#include "MathTools.h"


namespace ni_math {


inline double DistrFun( double x, double x_upper, double scaleMin, double D )
{
  const double e = 2.7182818;
  return scaleMin + ( pow( e, x ) - 1.0 ) / ( pow( e, x_upper ) - 1.0 ) * D;
}



bool CreateLogarithmScale( vector<double> & points, double scaleMin, double scaleMax, double stepLo, double stepHi )
{
  const double D = scaleMax - scaleMin;

  const double eps = 1e-3;

  if ( D < stepLo ) {
    points.push_back( ( scaleMin + scaleMax ) * 0.5 );
    return true;
  }

  if ( D < stepLo + stepHi + eps ) {
    points.push_back( scaleMin );
    points.push_back( scaleMax );
    return true;
  }

  //a little rocket-science here
  //We just want a logarithmic distribution with step 'ratingStepLow' at the begin of interval and 
  //step 'ratingStepHigh' at the end
  double x0=0, x1=0;
  int roots = QuadraticEquation( x0, x1, D - stepHi, stepLo + stepHi - 2.0 * D, D - stepLo, eps );
  NI_VERIFY( roots > 0, "", return false );
  double e_x_step = Max( x0, x1 );
  double x_step = log( e_x_step );
  double e_x_upper = 1.0 + D / stepLo * ( e_x_step - 1.0 );
  double x_upper = log( e_x_upper );

  double check_zero = DistrFun( 0,                x_upper, scaleMin, D );
  double check_step = DistrFun( x_step,           x_upper, scaleMin, D );
  double check_last = DistrFun( x_upper - x_step, x_upper, scaleMin, D );
  double check_max  = DistrFun( x_upper,          x_upper, scaleMin, D );
  NI_VERIFY( fabs( check_zero - scaleMin ) < eps, "", return false );
  NI_VERIFY( fabs( check_step - ( scaleMin + stepLo ) ) < eps, "", return false );
  NI_VERIFY( fabs( check_last - ( scaleMax - stepHi ) ) < eps, "", return false );
  NI_VERIFY( fabs( check_max - scaleMax ) < eps, "", return false );

  points.reserve( 1 + (int)( x_upper / x_step ) );

  double x = x_upper;
  for ( ; x >= 0.0f; x -= x_step )
    points.push_back( DistrFun( x, x_upper, scaleMin, D ) );

  if ( x > -0.5 * x_step )
    points.push_back( DistrFun( 0, x_upper, scaleMin, D ) );

  return true;
}

} //namespace ni_math
