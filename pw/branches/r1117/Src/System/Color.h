#pragma once

namespace Render
{
	class Color
	{
	public:

    typedef unsigned char TValue;

  #ifdef WIN32
	  #pragma warning(disable:4201) //warning C4201: nonstandard extension used : nameless struct/union
	#endif
	
		union 
		{
			struct{ TValue B, G, R, A; }; // intel byte order aka little-endian 
			unsigned long Dummy;
		};
		
    #ifdef WIN32
	    #pragma warning(default:4201)
   #endif

		Color() : B(0), G(0), R(0), A(0) {}

		Color( TValue _R, TValue _G, TValue _B, TValue _A = 255 )
			:	B(_B), G(_G), R(_R), A(_A)
		{

		}

		explicit Color( TValue _Alpha )
			:	B(255), G(255), R(255), A(_Alpha)
		{

		}

		explicit Color( unsigned long dummy ) : Dummy(dummy)
		{
		}
    explicit Color(int dummy ) : Dummy( (unsigned long)dummy)
    {
    }

		Color operator*(float _k) const
		{
			return Color( 
			              (TValue)floor(float(this->R) * _k), 
			              (TValue)floor(float(this->G) * _k), 
			              (TValue)floor(float(this->B) * _k), 
			              (TValue)floor(float(this->A) * _k) 
			            );
		}
		
		Color& operator=(const Color& col)
		{
		  Dummy = col.Dummy; return *this;
		}

		Color operator*(const Color& _k) const
		{
			return Color( i_mul( this->R, _k.R ), i_mul( this->G, _k.G ), i_mul( this->B, _k.B ), i_mul( this->A, _k.A ) );
		}

		Color operator-(const Color& _k) const
		{
			return Color( this->R - _k.R, this->G - _k.G, this->B - _k.B, this->A - _k.A );
		}

		Color operator+(const Color& _k) const
		{
			return Color( 0xFF & (this->R + _k.R), 0xFF & (this->G + _k.G), 0xFF & (this->B + _k.B), 0xFF & (this->A + _k.A) );
			//return Color( (this->R + _k.R),	(this->G + _k.G),	(this->B + _k.B), (this->A + _k.A) );
		}

		bool operator==( const Color &C ) const
		{
			return Dummy == C.Dummy;
		}
		bool operator!=( const Color& C ) const
		{
			return Dummy != C.Dummy;
		}

	private:
		TValue i_mul( TValue i1, TValue i2 ) const
		{
			return ( int(i1) * int(i2) ) / 255;
		}
	};

class HDRColor
{
public:

  // predefined color constants (as functions to allow correct DLL linkage)
  static const HDRColor& WHITE();
  static const HDRColor& BLACK();

#ifdef WIN32
#pragma warning(disable:4201) //warning C4201: nonstandard extension used : nameless struct/union
#endif

	union 
	{
		struct{ float R, G, B, A; }; 
	};

#ifdef WIN32
#pragma warning(default:4201)
#endif

	HDRColor() : R(0.0f), G(0.0f), B(0.0f), A(0.0f) {}

	HDRColor( float _R, float _G, float _B, float _A = 1.0f )
		:	R(_R), G(_G), B(_B), A(_A)
	{

	}

	explicit HDRColor( float _Alpha )
		:	R(1.f), G(1.f), B(1.f), A(_Alpha)
	{

	}

  explicit HDRColor( const Color & color )
    : R( color.R / 255.f ), G( color.G / 255.f ), B( color.B / 255.f ), A( color.A / 255.f )
  {
  }

  operator const Color () const
  {
    Color c;
    c.A = (Color::TValue)(Clamp( A, 0.f, 1.f ) * 255.0f );
    c.R = (Color::TValue)(Clamp( R, 0.f, 1.f ) * 255.0f );
    c.G = (Color::TValue)(Clamp( G, 0.f, 1.f ) * 255.0f );
    c.B = (Color::TValue)(Clamp( B, 0.f, 1.f ) * 255.0f );
    return c;
  }

  const CVec3& AsVec3D() const { return reinterpret_cast<const CVec3&>(*this); }
  CVec3& AsVec3D() { return reinterpret_cast<CVec3&>(*this); }

  void Add(const HDRColor &a, const HDRColor &b)
  {
    R = a.R + b.R;
    G = a.G + b.G;
    B = a.B + b.B;
    A = a.A + b.A;
  }

	void Mul(const HDRColor &a, const HDRColor &b)
	{
		R = a.R * b.R;
		G = a.G * b.G;
		B = a.B * b.B;
		A = a.A * b.A;
	}

	void Mad(const HDRColor &a, const HDRColor &b, const HDRColor &c)
	{
		R = a.R * b.R + c.R;
		G = a.G * b.G + c.G;
		B = a.B * b.B + c.B;
		A = a.A * b.A + c.A;
	}

  void Lerp(const HDRColor &a, const HDRColor &b, float s)
  {
    R = a.R + (b.R - a.R) * s;
    G = a.G + (b.G - a.G) * s;
    B = a.B + (b.B - a.B) * s;
    A = a.A + (b.A - a.A) * s;
  }
};

inline const HDRColor operator+( const HDRColor &a, const HDRColor &b ) { return HDRColor( a.R + b.R, a.G + b.G, a.B + b.B, a.A + b.A ); }
inline const HDRColor operator-( const HDRColor &a, const HDRColor &b ) { return HDRColor( a.R - b.R, a.G - b.G, a.B - b.B, a.A - b.A ); }
inline const HDRColor operator*( const HDRColor &a, const HDRColor &b ) { return HDRColor( a.R * b.R, a.G * b.G, a.B * b.B, a.A * b.A ); }
inline const HDRColor operator*( const HDRColor &a, float s ) { return HDRColor( a.R * s, a.G * s, a.B * s, a.A * s ); }
inline const HDRColor operator*( float s, const HDRColor &a ) { return HDRColor( a.R * s, a.G * s, a.B * s, a.A * s ); }
inline const HDRColor operator/( const HDRColor &a, float s ) { return a * (1.0f / s); }

// for using as key in std::map<...>
inline bool operator<( const Render::HDRColor& a, const Render::HDRColor& b ) 
{
	HDRColor c(b-a); 
	return c.R > 0.0f || (c.R == 0.0f && (c.G > 0.0f || (c.G == 0.0f && (c.B > 0.0f || (c.B == 0.0f && c.A > 0.0f)))));
}

HDRColor HSL2RGB(const float h, const float s, const float l);
HDRColor HSV2RGB(const float h, const float s, const float v);

HDRColor Saturate( const HDRColor& _source, float _sat, const CVec4& _fadeColor );

} //namespace Render

inline float fabs( const Render::HDRColor &c ) { return fabs(c.R, c.G, c.B, c.A); }
inline float fabs2( const Render::HDRColor &c ) { return fabs2(c.R, c.G, c.B, c.A); }
