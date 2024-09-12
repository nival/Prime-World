#pragma once

namespace Pathfinding
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CCommonPathFinder;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class RoutePathFinder : public CObjectBase
{
  OBJECT_METHODS( 0x49788500, RoutePathFinder );

public:
  RoutePathFinder(CCommonPathFinder * _pathFinder);

  void AddRoute(const vector<SVector>& route, int numSteps );
  void CalculateDist() { }

  int FindPath(const SVector& from, const SVector& to, int unitRadius, int numSteps ) const;

  const vector<SVector>& GetPath() const { return buffer; }

private:
  
  RoutePathFinder() {}

  struct Edge
  {
    int index;
    int distance;

    Edge() : index( 0 ), distance( 0 ) {}

    bool operator==( const int _index ) const { return index == _index; }
  };

  struct Point
  {
    SVector position;
    vector<Edge> edges;

    bool operator==( const SVector& p ) const { return position == p; }
  };

  struct TwoPoints
  {
  private:
    int index1;
    int index2;
  public:
    TwoPoints( int _index1, int _index2 ) : index1( min( _index1, _index2 ) ), index2 ( max( _index1, _index2 ) ) { }

    bool operator==( const TwoPoints& p ) const { return index1 == p.index1 && index2 == p.index2; }
    int GetHashCode() const { return index1 ^ index2; }
  };

  struct TwoPointsHash
  {
    int operator()( const TwoPoints& p ) const { return p.GetHashCode(); }
  };

  typedef hash_map<TwoPoints, vector<SVector>, TwoPointsHash> TPaths;

  vector<Point> points;
  TPaths paths;
  mutable vector<SVector> buffer;
  CPtr<CCommonPathFinder> pathFinder;

  int GetPoint( const SVector& p );

  int CalculatePathWeight( int enterIndex, int exitIndex, float dirtWeight, float routeWeight ) const;

  // fill result with pair of index/weight
  void FindNearestPoints( const SVector& p, vector<pair<int, int>>& result ) const;

	// move point p toward to point with specified distance. returns false if new point became outside to, in this case p equals to
  bool MovePoint( SVector& p, const SVector& to, float distance ) const;

  // return length of real path from-to in tiles
  int GetPathLength( const SVector& from, const SVector& to, int unitRadius, int numSteps ) const;

	// build real path from-to for unit with specified radius and write it to result at specified offset (resize if necessary)
  int BuildPath( const SVector& from, const SVector& to, int unitRadius, vector<SVector>& result, int offset, int numSteps ) const;
  int CopyPathSegment( int p1, int p2, vector<SVector>& result, int offset ) const;
  
	void RecalculatePaths( int numSteps );
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}