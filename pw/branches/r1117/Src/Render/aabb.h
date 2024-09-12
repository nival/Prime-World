#pragma once

namespace NDb
{
	struct AABB;
}

namespace Render
{
	__declspec(align(16))
	struct AABB
	{
		CVec3 center;
		float x; //align to 4 floats for SSE instructions
		CVec3 halfSize;
		float y;
		
		AABB () {}
    AABB (const CVec3 &_center, const CVec3 &_halfSize) : center(_center), halfSize(_halfSize) {}

		void Init2Empty();

    bool IsEmpty() const { return halfSize.x < 0.0f; }
    bool IsValid() const;

		void Set( float minX, float maxX, float minY, float maxY, float minZ, float maxZ );

		void Set( const NDb::AABB &dbAABB );

		void Set( const CVec3 &vmin, const CVec3 &vmax );

    void Assign( const CVec3 &_center, const CVec3 &_halfSize );

		void Transform( const Matrix43 &mtx, const AABB &src );

		void Calculate( int numPoints, const CVec3 *pPoints, int stride	);

		void AddPoint( const CVec3 &point );

    void Grow( const AABB& aabb );

    void Intersect( const AABB& aabb );

    bool IsIntersectedBy(const AABB &aabb) const;

    static const AABB& Huge()
    {
      static const AABB bb( CVec3::Zero(), CVec3::Huge() );
      return bb;
    }
	};

  inline bool operator==(const AABB& _lhs, const AABB& _rhs)
  {
    return _lhs.center == _rhs.center && _lhs.halfSize == _rhs.halfSize;
  }

  inline bool operator!=(const AABB& _lhs, const AABB& _rhs)
  {
    return !operator==(_lhs, _rhs);
  }

  class IAABB
  {
  public:
		virtual const Render::AABB &GetWorldAABB() const = 0;
  };

} //namespace Render