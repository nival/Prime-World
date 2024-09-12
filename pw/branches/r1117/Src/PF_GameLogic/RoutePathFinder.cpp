#include "stdafx.h"
#include "RoutePathFinder.h"
#include "CommonPathFinder.h"
#include "TileMap.h"
#include "System/InlineProfiler.h"
#include "System/LogFileName.h"
#include "System/FastMath.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace
{
static const int DIRT_DISTANCE_COEFF = 16;
static const float DIRT_LEN_STRETCH = 1.5f;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
class circle_queue
{
public:
  circle_queue( int size ) : pushIndex( 0 ), popIndex( 0 ), isEmpty( true )
  {
    queue.resize( size );
  }

  void push( const T& item )
  {
    NI_ASSERT( pushIndex != popIndex || isEmpty, "circle_queue overflow" );
    queue[pushIndex] = item;
    pushIndex = ( pushIndex + 1 ) % queue.size();
    isEmpty = false;
  }

  template<typename TComparer>
  void push( const T& item, TComparer& comparer )
  {
    NI_ASSERT( pushIndex != popIndex || isEmpty, "circle_queue overflow" );
    if ( isEmpty )
      queue[pushIndex] = item;
    else
    {
      int index = popIndex;
      while ( comparer( item, queue[index] ) )
      {
        index = ( index + 1 ) % queue.size();
        if ( index == pushIndex )
          break;
      }
      
      int index2 = pushIndex;
      while ( index2 != index )
      {
        const int prevIndex2 = index2 == 0 ? queue.size() - 1 : index2 - 1;
        queue[index2] = queue[prevIndex2];
        index2 = prevIndex2;
      }

      queue[index] = item;
    }
    pushIndex = ( pushIndex + 1 ) % queue.size();
    isEmpty = false;
  }

  T& pop()
  {
    const int index = popIndex;
    popIndex = ( popIndex + 1 ) % queue.size();
    isEmpty = popIndex == pushIndex;
    return queue[index];
  }

  bool empty() const
  {
    return isEmpty;
  }

private:
  vector<T> queue;
  int pushIndex;
  int popIndex;
  bool isEmpty;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Weight
{
  int weight;
  int neibour;
  bool inQueue; // point already queued
  bool finished; // there is no exits from this point

  Weight() : weight( INT_MAX / 2 ), neibour( -1 ), inQueue( false ), finished( false ) { }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct WeightsSorter
{
  const vector<Weight>* weights;
  WeightsSorter( const vector<Weight>* _weights ) : weights( _weights ) { }

  bool operator()( int i1, int i2 ) const
  {
    return (*weights)[i1].weight >= (*weights)[i2].weight;
  }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool FindNearestPoint( const SVector& p1, const SVector& p2, const SVector& from, SVector& result )
{
  // line p1-p2 describes via ax + by + c = 0
  float a, b;
  if ( p1.x == p2.x )
  {
    a = 1.0f;
    b = 0;
  }
  else if ( p1.y == p2.y )
  {
    a = 0;
    b = 1.0f;
  }
  else
  {
    a = (float)(p2.y - p1.y)/(float)(p1.x - p2.x);
    b = 1.0f;
  }
  const float c = -(a*p1.x + b*p1.y);
  // line perpendicular p1-p2 and goes throw from describes via bx - ay + c2 = 0;
  const float c2 = a*from.y - b*from.x;
  // find intersection between p1-p2 and perpendicular that goes throw from
  if ( a == 0 )
  {
    result.x = -c2 / b;
    result.y = -c / b;
  }
  else
  {
    result.x = -(c*(a*a+b*b)+b*c2*a-b*b*c)/ (a*a*a+b*b*a);
    result.y = (a*c2-b*c) / (a*a + b*b);
  }
  // clamp intersection point with bounds of cut p1-p2
  if ( p1.x == p2.x )
  {
    const SVector& min = p1.y < p2.y ? p1 : p2;
    const SVector& max = p1.y >= p2.y ? p1 : p2;
    if ( result.y <= min.y )
    {
      result = min;
      return false;
    }
    else if ( result.y >= max.y )
    {
      result = max;
      return false;
    }
  }
  else
  {
    const SVector& min = p1.x < p2.x ? p1 : p2;
    const SVector& max = p1.x >= p2.x ? p1 : p2;
    if ( result.x <= min.x )
    {
      result = min;
      return false;
    }
    else if ( result.x >= max.x )
    {
      result = max;
      return false;
    }
  }

  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InsertPoint( int index, int dist, vector<pair<int, int>>& result )
{
  if ( dist < result[0].second )
  {
    int n = 1;
    for ( ; n < result.size() && dist < result[n].second; ++n );
    int insertPos = n - 1;
    for ( n = 0; n < insertPos; ++n )
      result[n] = result[n + 1];
    result[insertPos].first = index;
    result[insertPos].second = dist;
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GetDistance( const SVector& a, const SVector& b )
{
  return abs( a.x - b.x ) + abs( a.y - b.y );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Pathfinding
{
RoutePathFinder::RoutePathFinder(CCommonPathFinder * _pathFinder): pathFinder (_pathFinder)
{
  buffer.reserve( 5000 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RoutePathFinder::AddRoute( const vector<SVector>& route, int numSteps )
{
  NI_PROFILE_FUNCTION

  NI_ASSERT( route.size() > 1, "Route should have more that 1 point" );
  for( int i = 0; i < route.size() - 1; ++i )
  {
    const int p1 = GetPoint( route[i] );
    const int p2 = GetPoint( route[i + 1] );
    if ( find( points[p1].edges.begin(), points[p1].edges.end(), p2 ) == points[p1].edges.end() )
    {
      points[p1].edges.push_back().index = p2;
      points[p2].edges.push_back().index = p1;
    }
  }
  RecalculatePaths( numSteps );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RoutePathFinder::FindPath( const SVector& from, const SVector& to, int unitRadius, int numSteps ) const
{
  NI_PROFILE_FUNCTION

  // 1. find N nearest points for _to_
  // 2. add N nearest to queue and set their weight to m. distance
  // 3. perform wave search to points that marked as finished
  // 4. find N nearert points for _from_
  // 5. try find best way from _from_ to finish points and check finish points
  // 6. collect path

  vector<Weight> weights( points.size() );
  WeightsSorter sorter( &weights );
  circle_queue<int> tiles( points.size() );

  vector<pair<int, int>> nearestPoints( 4 );
  FindNearestPoints( to, nearestPoints );
  for( vector<pair<int, int>>::const_iterator it = nearestPoints.begin(); it != nearestPoints.end(); ++it )
  {
    if ( it->first >= 0 )
    {
      int length = GetPathLength( points[it->first].position, to, unitRadius, numSteps );
		  if ( length == 0 )
			  continue;

      weights[it->first].weight = DIRT_DISTANCE_COEFF * length; // out of road path are slightly expensive
      weights[it->first].inQueue = true;
      weights[it->first].finished = false;
    }
  }
  for( vector<pair<int, int>>::const_iterator it = nearestPoints.begin(); it != nearestPoints.end(); ++it )
  {
    if ( it->first >= 0 )
      tiles.push( it->first, sorter );
  }

  while ( !tiles.empty() )
  {
    int i = tiles.pop();
    const Point& point = points[i];
    for( vector<Edge>::const_iterator edge = point.edges.begin(); edge != point.edges.end(); ++edge )
    {
      int weight = weights[i].weight + edge->distance;
      if ( weight < weights[edge->index].weight && !weights[edge->index].finished )
      {
        weights[edge->index].weight = weight;
        weights[edge->index].neibour = i;
        if ( !weights[edge->index].inQueue )
        {
          weights[edge->index].inQueue = true;
          tiles.push( edge->index, sorter );
        }
      }
    }
    weights[i].finished = true;
    weights[i].inQueue = false;
  }

  FindNearestPoints( from, nearestPoints );
  int index = -1;
  int dist = INT_MAX / 2;
  for( vector<pair<int, int>>::const_iterator it = nearestPoints.begin(); it != nearestPoints.end(); ++it )
  {
    if ( it->first < 0 || !weights[it->first].finished )
      continue;

    int length = GetPathLength( from, points[it->first].position, unitRadius, numSteps );
		if ( length == 0 )
			continue;

    const int thisDist = DIRT_DISTANCE_COEFF * length + weights[it->first].weight;
    if ( thisDist < dist )
    {
      index = it->first;
      dist = thisDist;
    }
  }
  
  if ( index == -1 || weights[index].neibour == -1 )
  {
    buffer.clear();
    return 0;
  }

  buffer.resize( 5000 );

  int length = 0;
  int prevIndex = -1;
	int entryIndex = 0; // first point in buffer on route
	int exitIndex = 0; // last point in buffer on route

	// build path from from to first or second point on route
	SVector entryPoint;
	if ( FindNearestPoint( points[index].position, points[weights[index].neibour].position, from, entryPoint ) )
	{
		MovePoint( entryPoint, points[weights[index].neibour].position, fabs( from - entryPoint ) * DIRT_LEN_STRETCH );
		if ( from != entryPoint )
		{
			int length2 = BuildPath( from, entryPoint, unitRadius, buffer, length, numSteps );
			if ( length2 == 0 )
			{
				buffer.clear();
				return 0;
			}
			length += length2 - 1;
		}
    else
      buffer[0] = from;
		entryIndex = length;
		// one segment case will be proceed on finish
		if ( weights[weights[index].neibour].neibour >= 0 )
		{
			if ( entryPoint != points[weights[index].neibour].position )
			{
				int length2 = BuildPath( entryPoint, points[weights[index].neibour].position, unitRadius, buffer, length, numSteps );
				if ( length2 == 0 )
				{
					buffer.clear();
					return 0;
				}
				length += length2 - 1;
			} 
			prevIndex = index;
			index = weights[index].neibour;
		}
	}
	else
	{
		int length2 = BuildPath( from, points[index].position, unitRadius, buffer, length, numSteps );
		if ( length2 == 0 )
		{
			buffer.clear();
			return 0;
		}
		length += length2 - 1;
		entryIndex = length;
	}

  //copy path from route
  while ( weights[weights[index].neibour].neibour >= 0 )
  {
    length += CopyPathSegment( index, weights[index].neibour, buffer, length );
    prevIndex = index;
    index = weights[index].neibour;
  }

	SVector exitPoint;
	if ( FindNearestPoint( points[index].position, points[weights[index].neibour].position, to, exitPoint ) )
	{
		MovePoint( exitPoint, buffer[length], fabs( to - exitPoint ) * DIRT_LEN_STRETCH );
		if ( exitPoint == entryPoint )
		{
			buffer.clear();
			return 0;
		}
		if ( exitPoint != buffer[length] )
		{
			int length2 = BuildPath( buffer[length], exitPoint, unitRadius, buffer, length, numSteps );
			if ( length2 == 0 )
			{
				buffer.clear();
				return 0;
			}
			length += length2 - 1;
		}
		exitIndex = length;
    if ( buffer[length] != to )
		{
      int length2 = BuildPath( buffer[length], to, unitRadius, buffer, length, numSteps );
			if ( length2 == 0 )
			{
				buffer.clear();
				return 0;
			}
			length += length2 - 1;
		}
	}
	else
	{
    if ( buffer[length] == points[index].position )
    {
      length += CopyPathSegment( index, weights[index].neibour, buffer, length );
		  exitIndex = length;
    }
    else
    {
		  exitIndex = length;
      length += BuildPath( buffer[length], points[weights[index].neibour].position, unitRadius, buffer, length, numSteps ) - 1;
    }
    if ( to != buffer[length] )
		{
      int length2 = BuildPath( buffer[length], to, unitRadius, buffer, length, numSteps );
      if ( length2 == 0 )
      {
        buffer.clear();
        return 0;
      }
			length += length2 - 1;
		}
	}

	buffer.resize( length );

  return CalculatePathWeight( entryIndex, exitIndex, 1.0f, 0.8f );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RoutePathFinder::GetPoint( const SVector& p )
{
  for( int i = 0; i < points.size(); ++i )
  {
    if ( points[i].position == p )
      return i;
  }

  points.push_back().position = p;
  return points.size() - 1;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RoutePathFinder::CalculatePathWeight( int entryIndex, int exitIndex, float dirtWeight, float routeWeight ) const
{
  return CalculatePathLen( buffer, 0, entryIndex, dirtWeight ) +
    CalculatePathLen( buffer, entryIndex, exitIndex - entryIndex, routeWeight ) +
    CalculatePathLen( buffer, exitIndex, buffer.size() - exitIndex, dirtWeight );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RoutePathFinder::FindNearestPoints( const SVector& p, vector<pair<int, int>>& result ) const
{
  NI_ASSERT( result.size() > 0, "size of points should be greater than 0" );
  for( vector<pair<int, int>>::iterator it = result.begin(); it != result.end(); ++it )
  {
    it->first = -1;
    it->second = INT_MAX / 2;
  }

  for( int i = 0; i < points.size(); ++i )
    InsertPoint( i, GetDistance( p, points[i].position ), result );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool RoutePathFinder::MovePoint( SVector& p, const SVector& to, float distance ) const
{
	if ( p == to )
		return false;

	float k = distance / fabs( p - to );
	if ( k > 1.0f )
	{
		p = to;
		return false;
	}

	p.x += ( to.x - p.x ) * k;
	p.y += ( to.y - p.y ) * k;

  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RoutePathFinder::GetPathLength( const SVector& from, const SVector& to, int unitRadius, int numSteps ) const
{
  if ( !pathFinder->CreatePath( unitRadius, unitRadius, from, to, from, 0, -1, numSteps ) )
    return 0;

  return CalculatePathLen( pathFinder->GetCurrentPath(), 0, pathFinder->GetPathLength() );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RoutePathFinder::BuildPath( const SVector& from, const SVector& to, int unitRadius, vector<SVector>& result, int offset, int numSteps ) const
{
  if ( !pathFinder->CreatePath( unitRadius, unitRadius, from, to, from, 0, -1, numSteps ) )
    return 0;

  int length = pathFinder->GetPathLength();
  if ( result.size() < offset + length )
    result.resize( offset + length );
  pathFinder->GetTiles( &result[offset], length );
  return length;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RoutePathFinder::CopyPathSegment( int p1, int p2, vector<SVector>& result, int offset ) const
{
  const vector<SVector>& path = paths[TwoPoints( p1, p2 )];
  if ( p1 < p2 )
    memcpy( &buffer[offset], path.begin(), sizeof( SVector) * path.size() );
  else
  {
    for( int i = 0; i < path.size(); ++i )
      buffer[offset + i] = path[path.size() - i - 1];
  }
  return path.size() - 1;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RoutePathFinder::RecalculatePaths( int numSteps )
{
  for( int i = 0; i < points.size(); ++i )
  {
    Point& point = points[i];
    for( vector<Edge>::iterator edge = point.edges.begin(); edge != point.edges.end(); ++edge )
    {
      vector<SVector>& path = paths[TwoPoints( i, edge->index )];
      if ( path.empty() )
        BuildPath( point.position, points[edge->index].position, 0, path, 0, numSteps );
      edge->distance = path.size();
    }
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace Pathfinding

BASIC_REGISTER_CLASS(Pathfinding::RoutePathFinder);