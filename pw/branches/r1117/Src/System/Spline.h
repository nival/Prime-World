#ifndef __SPLINE_H__
#define __SPLINE_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** basic beta spline (1D)
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CAnalyticBSpline
{
    // b-сплайн

	float p[4];
  float a3, a2, a1, a0;
public:
	CAnalyticBSpline() {	}
	CAnalyticBSpline( const float p0, const float p1, const float p2, const float p3 ) { Setup(p0, p1, p2, p3); }
	CAnalyticBSpline( const CAnalyticBSpline &bs ) { a3 = bs.a3; a2 = bs.a2; a1 = bs.a1; a0 = bs.a0; }
	//
	void Setup( const float p0, const float p1, const float p2, const float p3 )
	{
		p[0] = p0;
    p[1] = p1;
    p[2] = p2;
    p[3] = p3;

    a3 = ( -p0 + 3.0f*(p1 - p2) + p3 ) * (1.0f/6.0f);
		a2 = ( p0 - 2.0f*p1 + p2 ) * (1.0f/2.0f);
		a1 = ( -p0 + p2 ) * (1.0f/2.0f);
		a0 = ( p0 + 4.0f*p1 + p2 ) * (1.0f/6.0f);
	}
  float GetCtrlPoint( int n ) const { return p[n]; }
  float Get( const float t ) const { return ((a3*t + a2)*t + a1)*t + a0; }
	float operator()( const float t ) const { return Get( t ); }

	float GetDiff1( const float t ) const { return (a3*3.0f*t + a2*2.0f)*t + a1; }
	float GetDiff2( const float t ) const { return a3*6.0f*t + a2*2.0f; }
	float GetDiff3( const float	) const { return a3*6.0f; }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** beta spline curve
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CAnalyticBSpline2
{
    // двумерный b-сплайн

	static const int N_PARTS_FOR_CLOSEST_POINT_SEARCHING;
	
	CAnalyticBSpline x, y;
public:
	CAnalyticBSpline2() {	}
	CAnalyticBSpline2( const CVec3 &p0, const CVec3 &p1, const CVec3 &p2, const CVec3 &p3 ) { Setup(p0, p1, p2, p3); }
	CAnalyticBSpline2( const CVec2 &p0, const CVec2 &p1, const CVec2 &p2, const CVec2 &p3 ) { Setup(p0, p1, p2, p3); }
	CAnalyticBSpline2( const CAnalyticBSpline2 &bs ) : x( bs.x ), y( bs.y ) {	}
	//
	void Setup( const CVec3 &p0, const CVec3 &p1, const CVec3 &p2, const CVec3 &p3 )
	{
		x.Setup( p0.x, p1.x, p2.x, p3.x );
		y.Setup( p0.y, p1.y, p2.y, p3.y );
	}
	void Setup( const CVec2 &p0, const CVec2 &p1, const CVec2 &p2, const CVec2 &p3 )
	{
		x.Setup( p0.x, p1.x, p2.x, p3.x );
		y.Setup( p0.y, p1.y, p2.y, p3.y );
	}
  CVec2 GetCtrlPoint( int n ) const { return CVec2(x.GetCtrlPoint(n), y.GetCtrlPoint(n)); }
	const CVec2 Get( const float t ) const { return CVec2( x(t), y(t) ); }
	const CVec2 operator()( const float t ) const { return Get( t ); }

	const CVec2 GetDiff1( const float t ) const { return CVec2( x.GetDiff1(t), y.GetDiff1(t) ); }
	const CVec2 GetDiff2( const float t ) const { return CVec2( x.GetDiff2(t), y.GetDiff2(t) ); }
	const CVec2 GetDiff3( const float t ) const { return CVec2( x.GetDiff3(t), y.GetDiff3(t) ); }
	//
	float GetLength( const int nNumSteps = 100 ) const
	{
		const float fStep = 1.0f / float( nNumSteps );
		CVec2 vLastPos, vPos = Get( 0 );
		float fLen = 0;
		for ( float fT = 0; fT <= 1; fT += fStep )
		{
			vLastPos = vPos;
			vPos = Get( fT );
			fLen += fabs( vLastPos - vPos );
		}
		return fLen;
	}
	float GetLength( const float t, const int nNumSteps = 100 ) const
	{
		if ( t < 1e-4 ) 
			return fabs( Get(t) - Get(0) );
		const float fStep = t / float( nNumSteps );
		CVec2 vLastPos, vPos = Get( 0 );
		float fLen = 0;
		for ( float fT = 0; fT <= t; fT += fStep )
		{
			vLastPos = vPos;
			vPos = Get( fT );
			fLen += fabs( vLastPos - vPos );
		}
		return fLen;
	}
	const float GetLength( const float fT1, const float fT2, const int nNumSteps = 100 ) const
	{
		if ( fT2 - fT1 < 1e-4 ) 
			return fabs( Get(fT2) - Get(fT1) );
		const float fStep = (fT2 - fT1) / float( nNumSteps );
		CVec2 vLastPos, vPos = Get( fT1 );
		float fLen = 0;
		for ( float fT = fT1; fT <= fT2; fT += fStep )
		{
			vLastPos = vPos;
			vPos = Get( fT );
			fLen += fabs( vLastPos - vPos );
		}
		return fLen;
	}
	float GetLengthAdaptive( const float fTolerance, const int nStepLimit = 100 ) const
	{
		float fLen1 = GetLength( 100 );
		float fLen2 = GetLength( 200 );
		int nStepCounter = 2;
		while ( (fabs(fLen1 - fLen2) > fTolerance) && (nStepCounter < nStepLimit) ) 
		{
			++nStepCounter;
			fLen1 = fLen2;
			fLen2 = GetLength( 100 * nStepCounter );
		}
		return fLen2;
	}
	float GetStep( const float fStep ) const { return fStep / GetLength(); }
	// радиус кривизны кривой, заданной параметрически:
	//		 ((x`)^2 + (y`)^2)^(3/2)
	// R = -----------------------
	//				 |x`y`` - y`x``|
	float GetCurvatureRadius( const float t ) const
	{
		const float dx = x.GetDiff1( t );
		const float dy = y.GetDiff1( t );
		const float denominator = fabs( dx*y.GetDiff2(t) - dy*x.GetDiff2(t) );
		return denominator < 1e-5f ? 0 : pow( fabs2( dx ) + fabs2( dy ), 3.0f/2.0f ) / denominator;
	}
	// центр кривизны кривой, заданной параметрически:
	//					(x`)^2 + (y`)^2
	// x0 = x - --------------- * y`
	//					 x`y`` - y`x``
	//					(x`)^2 + (y`)^2
	// y0 = y + --------------- * x`
	//					 x`y`` - y`x``
	const CVec2 GetCurvatureCenter( const float t ) const
	{
		const float dx = x.GetDiff1( t );
		const float dy = y.GetDiff1( t );
		const float denominator = dx*y.GetDiff2(t) - dy*x.GetDiff2(t);
		if ( fabs(denominator) < 1e-5f )
			return VNULL2;
		const float fCoeff = ( fabs2( dx ) + fabs2( dy ) ) / denominator;
		return CVec2( x(t) - fCoeff*dy, y(t) + fCoeff*dx );
	}
	
	// найти ближайшую точку к vPoint (еЄ параметер)
	float GetClosestPoint(const CVec2 &vPoint);
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** beta spline surface
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CBetaSpline3D
{
	// can be stored as raw binary data
	float fBeta1, fBeta2;
	float invdelta;
	float fBeta1_3;
	float fBeta1_2;
	float fVolCoeffs[16];

	float b_2( const float t[3] ) const;
	float b_1( const float t[3] ) const;
	float b0( const float t[3] )	const;
	float b1( const float t[3] )	const;

	float db_2( const float t[3] ) const;
	float db_1( const float t[3] ) const;
	float db0( const float t[3] )	const;
	float db1( const float t[3] )	const;

	void	VolumeCoeffs( float b1, float b2 );

	float F00( const float t[2][4] ) const;
	float F11( const float t[2][4] ) const;
	float F22( const float t[2][4] ) const;
	float F33( const float t[2][4] ) const;
	float F01( const float s[2][4], const float t[2][4] ) const;
	float F02( const float s[2][4], const float t[2][4] ) const;
	float F03( const float s[2][4], const float t[2][4] ) const;
	float F12( const float s[2][4], const float t[2][4] ) const;
	float F13( const float s[2][4], const float t[2][4] ) const;
	float F23( const float s[2][4], const float t[2][4] ) const;

public:
	CBetaSpline3D() { }
	void Init( float fBeta1, float fBeta2 );

	const float Value( float u, float v, const float ptControls[16] ) const;
	void GetNormal( CVec3 *pvNormale, float u, float v, const float ptCtrls[16] ) const;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SampleNURBSCurve( vector<CVec3> *pRes, const float fSampleStep, const vector<CVec3> &ctrlPoints,
	const float fWeight1 = 1.0f, const float fWeight2 = 1.0f, const float fWeight3 = 1.0f, const float fWeight4 = 1.0f );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// cubic spline curve - 1D
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CCubicSpline1D
{
	vector<CVec4> segments; 
public:
	CCubicSpline1D() {}
	CCubicSpline1D( const SHMatrix& coefs, const vector<float>& path )
	{
		Setup( coefs, path );
	}
	CCubicSpline1D( float tension, const vector<float> &path )
	{
		SHMatrix coefs;
		FillCoefMatrix( coefs, tension );
		Setup( coefs, path );
	}

	static void FillCoefMatrix( SHMatrix& coefs, float tension )
	{
		float s =  ( 1 - tension ) / 2;
		coefs.Set( -s, 2 - s, 	  s - 2,  s,
			        2*s, s - 3, 3 - 2 * s, -s,
			         -s,	   0,		 		  s,  0,
			          0,     1,         0,  0 );
	}

	void Setup( const SHMatrix& coefs, const vector<float>& path )
	{
		segments.resize( path.size() - 3 );

		for ( int i = 0; i < segments.size(); ++i )
		{
			CVec4 c( path[i], path[i + 1], path[i + 2], path[i + 3] );
			coefs.RotateHVector( &c, c );
			segments[i] = c;
		}
	}

  void Setup( const vector<SHMatrix>& coefs, const vector<float>& path )
  {
    NI_ASSERT( coefs.size() + 2 == path.size(), "bad size of arrays" )

    segments.resize( path.size() - 3 );

    for ( int i = 0; i < segments.size(); ++i )
    {
      CVec4 c( path[i], path[i + 1], path[i + 2], path[i + 3] );
      coefs[i].RotateHVector( &c, c );
      segments[i] = c;
    }
  }

	float GetValue( int seg, float t )
	{
		NI_VERIFY( seg >= 0 && seg < segments.size(), "segment index out of  range", return 0.f );
		CVec4 tt( t*t*t, t*t, t, 1 );
		return segments[seg] * tt;
	}

	float GetDiff( int seg, float t )
	{
		NI_VERIFY( seg >= 0 && seg < segments.size(), "segment index out of  range", return 0.f );
		// CVec4 tt( 3*t*t, 2*t, 1, 0 );
		//return segments[seg] * tt;
		return GetValue( seg, t ) - GetValue( seg, t - 0.1f );
	}

  float GetDiffT( int seg, float t )
  {
    NI_VERIFY( seg >= 0 && seg < segments.size(), "segment index out of  range", return 0.f );
    CVec4 tt( 3*t*t, 2*t, 1, 0 );
    return segments[seg] * tt;
  }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// cubic spline curve - 3D
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CCubicSpline3D
{
protected:
	CCubicSpline1D x;
	CCubicSpline1D y;
	CCubicSpline1D z;
	vector<float> segEnds; 
public:
	CCubicSpline3D() {}

	bool Setup( const vector<CVec3> &path, const CVec3& startDir, const CVec3& endDir, float tension = 0.f )
	{
		NI_VERIFY( path.size() > 1, "path too short", return false );

		int sz = path.size();
		vector<float> temp;
		temp.resize( sz + 2 );

		SHMatrix coefs;
		CCubicSpline1D::FillCoefMatrix( coefs, tension );

		temp[0] = path[0].x - startDir.x;
		for( int i = 0; i < sz; ++i )
			temp[i + 1] = path[i].x;
		temp[sz + 1] = path[sz - 1].x + endDir.x;
		x.Setup( coefs, temp );

		temp[0] = path[0].y - startDir.y;
		for( int i = 0; i < sz; ++i )
			temp[i + 1] = path[i].y;
		temp[sz + 1] = path[sz - 1].y + endDir.y;
		y.Setup( coefs, temp );

		temp[0] = path[0].z - startDir.z;
		for( int i = 0; i < sz; ++i )
			temp[i + 1] = path[i].z;
		temp[sz + 1] = path[sz - 1].z + endDir.z;
		z.Setup( coefs, temp );

		segEnds.resize( sz - 1 );
		for( int i = 0; i < ( sz - 1) ; ++i )
			segEnds[i] = ( i == 0 ? 0 : segEnds[i - 1] ) + fabs( path[i] - path[i + 1] );

		return true;
	}

	float GetTotalLength() const
	{
		return segEnds.back();
	}

	void FindSegment( int *pSeg, float *pT, float t )
	{
		t = Clamp( t, 0.f, GetTotalLength() );
		int sz = segEnds.size();
		*pSeg = sz - 1;

		for( int i = 0; i < sz; ++i )
		{
			if ( t <= segEnds[i] )
			{
				*pSeg = i;
				break;
			}
		}
		float segStart = ( *pSeg == 0 ? 0 : segEnds[*pSeg - 1] );
    *pT = fabs( t - segStart ) < EPS_VALUE ? 0 : ( t - segStart ) / ( segEnds[*pSeg] - segStart ); 
	}

	void GetValue( CVec3* pRes, float t )
	{
		int seg;
		float t1;
		FindSegment( &seg, &t1, t );
		pRes->x = x.GetValue( seg, t1 );
		pRes->y = y.GetValue( seg, t1 );
		pRes->z = z.GetValue( seg, t1 );
 	}

	void GetDiff( CVec3* pRes, float t )
	{
		int seg;
		float t1;
		FindSegment( &seg, &t1, t );
		pRes->x = x.GetDiff( seg, t1 );
		pRes->y = y.GetDiff( seg, t1 );
		pRes->z = z.GetDiff( seg, t1 );
	}

	int GetSegmentNumber() const
	{
		return segEnds.size();
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// cubic spline curve - Quaternion
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CCubicSplineQuat
{
protected:
  CCubicSpline1D x;
  CCubicSpline1D y;
  CCubicSpline1D z;
  CCubicSpline1D w;
  vector<float> segEnds; 
public:
  CCubicSplineQuat() {}

  bool Setup( const vector<CQuat> &path, const CQuat& startDir, const CQuat& endDir, float tension = 0.f )
  {
    NI_VERIFY( path.size() > 1, "path too short", return false );

    int sz = path.size();
    vector<float> temp;
    temp.resize( sz + 2 );

    SHMatrix coefs;
    CCubicSpline1D::FillCoefMatrix( coefs, tension );

    temp[0] = path[0].x - startDir.x;
    for( int i = 0; i < sz; ++i )
      temp[i + 1] = path[i].x;
    temp[sz + 1] = path[sz - 1].x + endDir.x;
    x.Setup( coefs, temp );

    temp[0] = path[0].y - startDir.y;
    for( int i = 0; i < sz; ++i )
      temp[i + 1] = path[i].y;
    temp[sz + 1] = path[sz - 1].y + endDir.y;
    y.Setup( coefs, temp );

    temp[0] = path[0].z - startDir.z;
    for( int i = 0; i < sz; ++i )
      temp[i + 1] = path[i].z;
    temp[sz + 1] = path[sz - 1].z + endDir.z;
    z.Setup( coefs, temp );

    temp[0] = path[0].w - startDir.w;
    for( int i = 0; i < sz; ++i )
      temp[i + 1] = path[i].w;
    temp[sz + 1] = path[sz - 1].w + endDir.w;
    w.Setup( coefs, temp );

    segEnds.resize( sz - 1 );
    for( int i = 0; i < ( sz - 1) ; ++i )
    {
      CVec4 current;
      CVec4 next;

      current.Set( path[i] );
      next.Set( path[i + 1] );

      segEnds[i] = ( i == 0 ? 0 : segEnds[i - 1] ) + fabs( current - next );
    }
    
    return true;
  }

  bool Setup( const vector<CQuat> &path, const CQuat& startDir, const CQuat& endDir, const vector<float> tension )
  {
    NI_VERIFY( path.size() > 1, "path too short", return false );

    int sz = path.size();
    vector<float> temp;
    temp.resize( sz + 2 );

    vector<SHMatrix> coefs;

    for( int i = 0; i < tension.size(); i++ )
    {
      SHMatrix temp;
      CCubicSpline1D::FillCoefMatrix( temp, tension[i] );
      coefs.push_back( temp );
    }

    temp[0] = path[0].x - startDir.x;
    for( int i = 0; i < sz; ++i )
      temp[i + 1] = path[i].x;
    temp[sz + 1] = path[sz - 1].x + endDir.x;
    x.Setup( coefs, temp );

    temp[0] = path[0].y - startDir.y;
    for( int i = 0; i < sz; ++i )
      temp[i + 1] = path[i].y;
    temp[sz + 1] = path[sz - 1].y + endDir.y;
    y.Setup( coefs, temp );

    temp[0] = path[0].z - startDir.z;
    for( int i = 0; i < sz; ++i )
      temp[i + 1] = path[i].z;
    temp[sz + 1] = path[sz - 1].z + endDir.z;
    z.Setup( coefs, temp );

    temp[0] = path[0].w - startDir.w;
    for( int i = 0; i < sz; ++i )
      temp[i + 1] = path[i].w;
    temp[sz + 1] = path[sz - 1].w + endDir.w;
    w.Setup( coefs, temp );

    segEnds.resize( sz - 1 );
    for( int i = 0; i < ( sz - 1) ; ++i )
    {
      CVec4 current;
      CVec4 next;

      current.Set( path[i] );
      next.Set( path[i + 1] );

      segEnds[i] = ( i == 0 ? 0 : segEnds[i - 1] ) + fabs( current - next );
    }

    return true;
  }

  float GetTotalLength() const
  {
    return segEnds.back();
  }

  void FindSegment( int *pSeg, float *pT, float t )
  {
    t = Clamp( t, 0.f, GetTotalLength() );
    int sz = segEnds.size();
    *pSeg = sz - 1;

    for( int i = 0; i < sz; ++i )
    {
      if ( t <= segEnds[i] )
      {
        *pSeg = i;
        break;
      }
    }
    float segStart = ( *pSeg == 0 ? 0 : segEnds[*pSeg - 1] );
    *pT = fabs( t - segStart ) < EPS_VALUE ? 0 : ( t - segStart ) / ( segEnds[*pSeg] - segStart ); 
  }

  void GetValue( CQuat* pRes, float t )
  {
    int seg;
    float t1;
    FindSegment( &seg, &t1, t );
    pRes->x = x.GetValue( seg, t1 );
    pRes->y = y.GetValue( seg, t1 );
    pRes->z = z.GetValue( seg, t1 );
    pRes->w = w.GetValue( seg, t1 );
  }

  void GetValue( CQuat* pRes, int seg, float t )
  {
    pRes->x = x.GetValue( seg, t );
    pRes->y = y.GetValue( seg, t );
    pRes->z = z.GetValue( seg, t );
    pRes->w = w.GetValue( seg, t );
  }

  void GetDiff( CQuat* pRes, float t )
  {
    int seg;
    float t1;
    FindSegment( &seg, &t1, t );
    pRes->x = x.GetDiff( seg, t1 );
    pRes->y = y.GetDiff( seg, t1 );
    pRes->z = z.GetDiff( seg, t1 );
    pRes->w = w.GetDiff( seg, t1 );
  }

  int GetSegmentNumber() const
  {
    return segEnds.size();
  }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** basic Hermite spline segment
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class TYPE> class CTHermiteSegment
{
	TYPE a3, a2, a1, a0;
public:
	typedef TYPE PointType;

	CTHermiteSegment() {}
	CTHermiteSegment( const TYPE& p0, const TYPE& m0, const TYPE& p1, const TYPE& m1 ) { Setup(p0, m0, p1, m1); }
	CTHermiteSegment( const CTHermiteSegment &hs ) : a3(hs.a3), a2(hs.a2), a1(hs.a1), a0(hs.a0) {}
	//
	void Setup( const TYPE& p0, const TYPE& m0, const TYPE& p1, const TYPE& m1 )
	{
		TYPE p0p1m0 = p0 - p1 + m0;
		a3 = 2.0f * p0p1m0 + m1 - m0;
		a2 = a3 + p0p1m0;
		a1 = m0;
		a0 = p0;
	}
	
	TYPE Get( float t ) const { return ((a3 * t - a2) * t + a1) * t + a0; }
	float operator()( float t ) const { return Get( t ); }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class POINT>
class CCompositeBSpline
{
public:
  struct BoundSection
  {
    POINT p[2];
  };

  struct SegmentQuantum
  {
    float param;  // starting param
    float length; // length of quantum itself
    float integralLength; // integral length from start of the segment to this quantum (not including)
  };

  struct Segment
  {
    nstl::vector<SegmentQuantum> quants;
    float integralLength;

    int FindQuantum(float t);
    float GetLength(float t);
    float GetTotalLength() { return quants[quants.size() - 1].integralLength + quants[quants.size() - 1].length; }
  };

  enum ValidFlags
  {
    VALID_BOUNDS   = (1 << 0),
    VALID_SEGMENTS = (1 << 1),
  };

protected:
  nstl::vector<POINT>   controlPoints;
  unsigned int  validFlags;
  nstl::vector<POINT>   bezierPoints;
  nstl::vector<Segment> segments;

public:
  CCompositeBSpline(POINT const &start, POINT const &end);
  CCompositeBSpline(nstl::vector<POINT> const &points);

  int GetNumPoints() const { return controlPoints.size(); }
  POINT &GetPoint(int index) { return controlPoints[index]; }
  int GetNumSegments() const { return controlPoints.size() - 3; }

  void InsertPoint(int index, POINT const &p);
  void RemovePoint(int index);
  void UpdatePoint(int index, POINT const &p);

  // get coordinates for point on spline at specified parameter value
  POINT Get(float t);

  // get coordinates for point on spline at specified parameter value
  // This method also considers linear extrapolation at spline ends and supports parameters outside [0..numSegments]
  POINT GetExt(float t);

  // get first derivative (tangent) at specified parameter value
  POINT GetDiff1(float t);

  // get first derivative (tangent) at specified parameter value
  // This method also considers linear extrapolation at spline ends and supports parameters outside [0..numSegments]
  POINT GetDiff1Ext(float t);

  // convert spline parameter into (segment, offset) pair
  void SegmentAndOffset(float global, int &segment, float &offset);

  // get spline length in metric units from start point to specified parameter
  float GetLength(float t);
  
  // get spline length in metric units from start point to end point
  float GetTotalLength();

  // get spline length in metric units from start point to specified parameter
  // This method also considers linear extrapolation at spline ends and supports parameters outside [0..numSegments]
  float GetLengthExt(float t);

  // get parameter for point on spline closest to the specified arbitrary point
  float GetClosestPoint(POINT const &p);

  // get parameter for point on spline closest to the specified arbitrary point
  // This method also considers linear extrapolation at spline ends.
  // If one of the end points happens to be the closest point we project given point
  // to linear extension of this end. Thus returning parameter that lies outside [0..numSegments]
  float GetClosestPointExt(POINT const &p);

  // fill given array with sampled spline points
  void Sample(float flatness, float maxDistance, nstl::vector<POINT> &points);

  // precompute data for faster processing
  void PrecomputeBounds();
  void PrecomputeSegments();

protected:
  void SetupBy2Points(POINT const &start, POINT const &end);
  float GetSegmentClosestPoint(int index, POINT const &p);
  void PrecomputeSegment(int index);
};

template <class POINT>
class CCompositeBSplineWidth : public CCompositeBSpline<POINT>
{
  // width is specified only for inner control points, start and end points are not counted
  // so size of this array should be = <number of control points> - 2
  nstl::vector<float>  width;

public:  
  CCompositeBSplineWidth(nstl::vector<POINT> const &points, nstl::vector<float> const &width)
    : CCompositeBSpline<POINT>(points)
    , width (width)
  {
    NI_ASSERT(width.size() == points.size() - 2, "Invalid parameters");
  }

  // get spline width (in metric units) at specified parameter
  float GetWidth(float at);

  // get spline width (in metric units) at specified parameter
  // This method also considers linear extrapolation at spline ends and supports parameters outside [0..numSegments]
  float GetWidthExt(float at);

  // 
  CVec2 GetSection(float at, POINT &p0, POINT &p1);

  // check if specified points lies inside spline area
  bool IsInside(POINT const &p);

  // returns true if convex polygon overlaps the spline area
  bool ClassifyConvexPolygon(nstl::vector<POINT> const &v);

protected:
  bool EdgeIntersectsBounds(POINT const &p0, POINT const &p1);
};


class CubicSpline
{
public:
 CubicSpline() : splines() {}
 ~CubicSpline()  {}
 
 void Build( const nstl::vector<CVec2>& points );
 
 float Get( float x ) const;
 float GetDiff( float x ) const;

private:
  // —труктура, описывающа€ сплайн на каждом сегменте сетки
  struct SplineTuple
  {
    float a0, a1, a2, a3, x;
  };

  nstl::vector<SplineTuple> splines;
  int nodesCount;
};

#include "CompositeSpline.inl"

#endif // __SPLINE_H__
