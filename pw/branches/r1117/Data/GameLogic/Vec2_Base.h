#ifndef VEC2_BASE_H_8FB8E987_D19D_4077_9
#define VEC2_BASE_H_8FB8E987_D19D_4077_9


#ifdef WIN32
  #pragma warning( push )
  #pragma warning( disable: 4201 ) // warning C4201: nonstandard extension used : nameless struct/union
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 2D vector
class CVec2
{
public:
	union
	{
		struct { float x, y; };
		struct { float u, v; };						 // for texture coord
		float m[2];
	};
public:
	CVec2()	{	}
	CVec2( const float _x, const float _y ) : x( _x ), y( _y ) {	}
	// setup
	void Set( const float _x, const float _y ) { x = _x; y = _y; }
	// indexed access
	float& operator[]( int i ) { return m[i]; };
	const float& operator[]( int i ) const { return m[i]; }
	// comparison
	// internal data non-math modification
	void Maximize( const CVec2 &v );
	void Minimize( const CVec2 &v );
	//
	void Negate( const CVec2 &v ) { x = -v.x; y = -v.y; } // this = -v
	void Negate() { x = -x; y = -y; }		 // this = -this
	float Length() const { return sqrt(x*x+y*y); }		 
	float LengthSqr() const { return x*x+y*y; }
  void Add( const CVec2 &v1, const CVec2 &v2 ) { x = v1.x + v2.x; y = v1.y + v2.y; } // this = v1 + v2
	void Sub( const CVec2 &v1, const CVec2 &v2 ) { x = v1.x - v2.x; y = v1.y - v2.y; } // this = v1 - v2
	void Displace( const CVec2 &v1, const CVec2 &v2, const float t ) { x = v1.x + t*v2.x; y = v1.y + t*v2.y; } //	this = v1 + t*v2
	void Displace( const CVec2 &v, const float t ) { x += t*v.x; y += t*v.y; } //	this += t*v;
	void Lerp( const float t, const CVec2 &v1, const CVec2 &v2 ) { x = t*v2.x + (1 - t)*v1.x; y = t*v2.y + (1 - t)*v1.y; } //this = (1 - t)*v1 + t*v2
	void Interpolate( const CVec2 &v1, const CVec2 &v2, const float t ) { Lerp(t, v1, v2); }
	float Dot( const CVec2 &v ) const { return x*v.x + y*v.y; }
	CVec2& CProduct( const CVec2& v ) {	const float oldX = x; x = oldX * v.x - y * v.y; y = oldX * v.y + y * v.x; return *this; }
	
	// mathematical operations
	CVec2& operator^=( const CVec2& v ) {	const float oldX = x; x = oldX * v.x - y * v.y; y = oldX * v.y + y * v.x; return *this; }
	CVec2& operator+=( const CVec2 &v ) { x += v.x; y += v.y; return *this; }
	CVec2& operator-=( const CVec2 &v ) { x -= v.x; y -= v.y; return *this; }
	CVec2& operator*=( const float d ) { x *= d; y *= d; return *this; }
	CVec2& operator/=( const float d ) { float d1 = 1.0f / d; x *= d1; y *= d1; return *this; }
  // check it
  bool IsFinite() const;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef WIN32
  #pragma warning( pop )
#endif

#endif //#define VEC2_BASE_H_8FB8E987_D19D_4077_9
