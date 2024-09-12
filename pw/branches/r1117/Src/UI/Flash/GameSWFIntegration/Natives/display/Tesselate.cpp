#include "TamarinPCH.h"

#include "ear_clip_triangulate.h"
#include "Tesselate.h"

#include <Vendor/Gl/include/GLU.h>

namespace flash
{

# define GLUCALLBACKTYPE void (CALLBACK *)()

class Tesselator2
{
public:

  struct ResultVertex
  {
    GLdouble result[3];
    int index;
    int pathID;
  };

  Tesselator2() : 
    tesselator( gluNewTess() ),
    primitiveType( GL_TRIANGLES ),
    primitiveCount( 0 ),
    trilist( 0 )
  {
    gluTessCallback( tesselator, GLU_TESS_ERROR, reinterpret_cast<GLUCALLBACKTYPE>( Tesselator2::Error ) );
    gluTessCallback( tesselator, GLU_TESS_COMBINE_DATA, reinterpret_cast<GLUCALLBACKTYPE>( Tesselator2::Combine ) );
    gluTessCallback( tesselator, GLU_TESS_BEGIN_DATA, reinterpret_cast<GLUCALLBACKTYPE>( Tesselator2::BeginData ) );
    gluTessCallback( tesselator, GLU_TESS_END_DATA, reinterpret_cast<GLUCALLBACKTYPE>( Tesselator2::EndData ) );
    gluTessCallback( tesselator, GLU_TESS_VERTEX_DATA, reinterpret_cast<GLUCALLBACKTYPE>( Tesselator2::VertexData ) ); 
    
    if( !Compatibility::IsRunnedUnderWine() )
      gluTessProperty( tesselator, GLU_TESS_TOLERANCE, 400.f );
  }

  ~Tesselator2()
  {
    ClearCrossings();
    gluDeleteTess( tesselator );  
  }

  void BeginPolygon()
  {
    gluTessBeginPolygon( tesselator, this );
    results.clear();
    ClearCrossings();
  }

  void BeginContour()
  {
    gluTessBeginContour( tesselator );
  }

  void ReserveBuffer( int numPaths )
  {
    results.resize( numPaths );
  }

  void Feed( nstl::vector<nstl::pair<float, int>>& path, int pathID )
  {
    int count = path.size();

    NI_ASSERT( count % 2 == 0, "Path length should be even" );
    NI_ASSERT( 0 <= pathID && pathID < results.size(), "Results reserved incorrectly" );

    results[pathID].reserve( results[pathID].size() + count / 2 );

    for ( int i = 0; i < count; i += 2 ) 
    {
      ResultVertex& vertex = results[pathID].push_back();

      vertex.result[0] = path[i].first;
      vertex.result[1] = path[i + 1].first;
      vertex.result[2] = 0.f;
      vertex.index = path[i].second;
      vertex.pathID = pathID;

      gluTessVertex( tesselator, vertex.result, &vertex );
    }
  }

  void EndContour()
  {
    gluTessEndContour( tesselator );  
  }

  void Tesselate( nstl::vector<nstl::pair<float, int>>* _trilist )
  {
    trilist = _trilist;
    gluTessEndPolygon( tesselator );
    trilist = 0;
  }

  static void CALLBACK BeginData( GLenum type, void * polygon_data )
  {
    Tesselator2* _this = reinterpret_cast<Tesselator2*>( polygon_data );

    _this->primitiveType = type;
    _this->primitiveCount = 0;
  }

  static void CALLBACK EndData( void * polygon_data )
  {

  }

  static void CALLBACK VertexData( void * vertex_data, void * polygon_data )
  {
    Tesselator2* _this = reinterpret_cast<Tesselator2*>( polygon_data );

    NI_VERIFY( _this->trilist, "Trilist should not be null", return );

    ResultVertex* vertex = (ResultVertex*)vertex_data;

    if ( ( _this->primitiveType == GL_TRIANGLE_FAN || _this->primitiveType == GL_TRIANGLE_STRIP ) && _this->primitiveCount > 2 )
    {
      int size = _this->trilist->size();
      nstl::pair<float, int> v1x = (*_this->trilist)[ size - 4 ];
      nstl::pair<float, int> v1y = (*_this->trilist)[ size - 3 ];
      nstl::pair<float, int> v2x = (*_this->trilist)[ size - 2 ];
      nstl::pair<float, int> v2y = (*_this->trilist)[ size - 1 ];

      if ( _this->primitiveType == GL_TRIANGLE_FAN )
      {
        _this->trilist->push_back( nstl::make_pair( _this->v0x.first, _this->v0x.second ) );
        _this->trilist->push_back( nstl::make_pair( _this->v0y.first, _this->v0y.second ) );
      }
      else
      {
        _this->trilist->push_back( nstl::make_pair( v1x.first, v1x.second ) );
        _this->trilist->push_back( nstl::make_pair( v1y.first, v1y.second ) );
      }

      _this->trilist->push_back( nstl::make_pair( v2x.first, v2x.second ) );
      _this->trilist->push_back( nstl::make_pair( v2y.first, v2y.second ) );
    }

    _this->trilist->push_back( nstl::make_pair( float( vertex->result[0] ), vertex->index ) );
    _this->trilist->push_back( nstl::make_pair( float( vertex->result[1] ), vertex->index ) );

    if ( _this->primitiveCount == 0)
    {
      _this->v0x = nstl::make_pair( float( vertex->result[0] ), vertex->index );
      _this->v0y = nstl::make_pair( float( vertex->result[1] ), vertex->index );
    }

    _this->primitiveCount++;
  }

  static void CALLBACK Combine(GLdouble coords [3], ResultVertex * vertex_data[4],
    GLfloat weight[4], void **outData, void * polygon_data )
  {
    Tesselator2* _this = reinterpret_cast<Tesselator2*>( polygon_data );

    NI_VERIFY( vertex_data[0], "first vertex should not be null", return );

    ResultVertex* vertex = new ResultVertex();
      
    _this->crossings.push_back( vertex );

    vertex->result[0] = coords[0];
    vertex->result[1] = coords[1];
    vertex->result[2] = coords[2];
    vertex->pathID = vertex_data[0]->pathID;
    vertex->index = vertex_data[0]->index;

    *outData = vertex;
  }

  static void CALLBACK Error( GLenum error )
  {  
    //DebugTrace("Tesselation error: %s", gluErrorString( error ) );
  }

  void ClearCrossings()
  {
    for ( int i = 0; i < crossings.size(); ++i )
    {
      delete crossings[i];
    }

    crossings.clear();
  }

  GLUtesselator* tesselator;

  nstl::vector<nstl::vector<ResultVertex>> results;
  nstl::vector<ResultVertex*> crossings;

  GLenum primitiveType;
  int primitiveCount;

  nstl::pair<float, int> v0x;
  nstl::pair<float, int> v0y;

  nstl::vector<nstl::pair<float, int>>* trilist;
};

// Curve subdivision error tolerance.
static float	s_tolerance = 1.0f;

struct path_part
{
	path_part()
		:
		m_left_style(-1),
		m_right_style(-1),
		m_line_style(-1),
		m_closed(false),
		m_processed(false)
	{
	}

	int m_left_style;
	int m_right_style;
	int m_line_style;
	bool m_closed;
	bool m_processed;

  nstl::vector<CVec2> m_verts;
};


static nstl::vector<path_part>	s_path_parts;
static CVec2	s_last_point;


void Tesselator::begin_shape( const ITesselatedShape* _shape, IMeshAccepter* _accepter, float curve_error_tolerance )
{
  shape = _shape;
  accepter = _accepter;

	// ensure we're not already in a shape or path.
	// make sure our shape state is cleared out.
	NI_ASSERT(s_path_parts.size() == 0, "not clear path");

	NI_ASSERT(curve_error_tolerance > 0, "small curve error tolerance");
	
  if (curve_error_tolerance > 0)
	{
		s_tolerance = curve_error_tolerance;
	}
	else
	{
		s_tolerance = 1.0f;
	}
}


bool try_to_combine_path(int index)
// Return true if we did any work.
{
	path_part* pp = &s_path_parts[index];
	if (pp->m_closed || pp->m_right_style == -1 || pp->m_verts.size() <= 0) {
		return false;
	}

	if (pp->m_verts[0] == pp->m_verts.back()) {
		pp->m_closed = true;
		return true;
	}

	// Look for another unclosed path of the same style,
	// which could join our begin or end point.
	int style = pp->m_right_style;
	for (int i = 0; i < s_path_parts.size(); i++) {
		if (i == index) {
			continue;
		}

		path_part* po = &s_path_parts[i];
		if (!po->m_closed && po->m_right_style == style && po->m_verts.size() > 0) {
			// Can we join?
			if (po->m_verts[0] == pp->m_verts.back()) {
				// Yes, po can be appended to pp.
				for (int j = 1; j < po->m_verts.size(); j++) {
					pp->m_verts.push_back(po->m_verts[j]);
				}
				po->m_right_style = -1;
				return true;
			} else if (po->m_verts.back() == pp->m_verts[0]) {
				// Yes, pp can be appended to po.
				for (int j = 1; j < pp->m_verts.size(); j++) {
					po->m_verts.push_back(pp->m_verts[j]);
				}
				pp->m_right_style = -1;
				return true;
			}
		}
	}

	return false;
}

void copy_points_into_array( nstl::vector<nstl::pair<float, int>>* out, const nstl::vector<CVec2>& in, int& uniqueID )
{
	if (in.size() > 0) {
		// Don't copy the end point, which should be a
		// dupe of the begin point, since the
		// triangulator does that implicitly.
		assert(in[0] == in[in.size() - 1]);
		out->resize((in.size() - 1) * 2);
		for (int i = 0; i < in.size() - 1; i++) 
    {
			(*out)[i * 2].first = in[i].x;
      (*out)[i * 2].second = uniqueID;
			(*out)[i * 2 + 1].first = in[i].y;
      (*out)[i * 2 + 1].second = uniqueID;

      uniqueID++;
		}
	}
}


void Tesselator::end_shape()
{
	// TODO: there's a ton of gratuitous array copying in
	// here! Fix it by being smarter, and by better
	// abstracting the I/O methods for the triangulator.
	
	// Convert left-fill paths into new right-fill paths,
	// so we only have to deal with right-fill below.
	for (int i = 0, n = s_path_parts.size(); i < n; i++) {
		int lstyle = s_path_parts[i].m_left_style;
		int rstyle = s_path_parts[i].m_right_style;

		if (lstyle >= 0)
		{
			if (rstyle == -1)
			{
				s_path_parts[i].m_right_style = s_path_parts[i].m_left_style;
				s_path_parts[i].m_left_style = -1;
				int n = s_path_parts[i].m_verts.size();
				for (int j = 0, k = n >> 1; j < k; j++)
				{
          nstl::swap( s_path_parts[i].m_verts[j], s_path_parts[i].m_verts[n - j - 1] );
				}
			}
			else
			{
				// Move the data into a new
				// proxy right path.
				s_path_parts.resize(s_path_parts.size() + 1);
				path_part* pold = &s_path_parts[i];
				path_part* pnew = &s_path_parts.back();

				// Copy path, in reverse, into a new right-fill path_part.
				pnew->m_right_style = lstyle;
				pnew->m_verts.reserve(pold->m_verts.size());
				for (int k = pold->m_verts.size() - 1; k >= 0; k--) {
					pnew->m_verts.push_back(pold->m_verts[k]);
				}
				pold->m_left_style = -1;
			}
		}
	}

	// Join path_parts together into closed paths.
	for (;;) {
		bool did_work = false;
		for (int i = 0; i < s_path_parts.size(); i++) {
			did_work = did_work || try_to_combine_path(i);
		}
		if (did_work == false) {
			break;
		}
	}
	
  int uniqueID = 0;

	// Triangulate and emit.
	for (int i = 0; i < s_path_parts.size(); i++) 
  {
		path_part* pp = &s_path_parts[i];

		if (!pp->m_processed && pp->m_right_style != -1 && pp->m_closed && pp->m_verts.size() > 0) 
    {
			pp->m_processed = true;
			int style = pp->m_right_style;
      nstl::vector<nstl::vector<nstl::pair<float, int>>> paths;
			paths.resize(paths.size() + 1);
			// TODO fix gratuitous array copying
			copy_points_into_array( &paths.back(), pp->m_verts, uniqueID );
			// Grab all the path parts.
			for (int j = i + 1; j < s_path_parts.size(); j++) 
      {
				path_part* pj = &s_path_parts[j];

				if (!pj->m_processed
				    && pj->m_right_style == style
				    && pj->m_closed
				    && pj->m_verts.size() > 0) 
        {
					paths.resize(paths.size() + 1);
					copy_points_into_array( &paths.back(), pj->m_verts, uniqueID );
					pj->m_processed = true;
				}
			}

      nstl::vector<nstl::pair<float, int>> trilist2;

      {
        Tesselator2 tesselator;
        tesselator.BeginPolygon();

        nstl::vector<nstl::vector<nstl::pair<float, int>>>::iterator itP = paths.begin();
        nstl::vector<nstl::vector<nstl::pair<float, int>>>::iterator lastP = paths.end();

        tesselator.ReserveBuffer( paths.size() );

        for ( int countBuffer = 0 ; itP != lastP; ++itP, ++countBuffer )
        {
          tesselator.BeginContour();
          tesselator.Feed( *itP, countBuffer );
          tesselator.EndContour();
        }

        tesselator.Tesselate( &trilist2 );
      }

			// Give the results to the accepter.
			if ( trilist2.size() > 0 ) 
      {
        int count_AA_tris = 0;
        for ( int i = 0; i < paths.size(); ++i )
        {
          count_AA_tris += paths[i].size() / 2;
        }

        accepter->begin_trilist( style, trilist2.size() / 6 + count_AA_tris * 4, uniqueID );

        accepter->accept_trilist_batch( reinterpret_cast<PointWithID*>(&trilist2[0]), trilist2.size() / 2 );

				accepter->end_trilist();
			}
		}
	}

	accepter->end_shape();
	accepter = NULL;
	s_path_parts.resize(0);
}

void Tesselator::begin_path(int style_left, int style_right, int line_style, float ax, float ay)
{
	s_path_parts.resize(s_path_parts.size() + 1);
  s_path_parts.back().m_left_style = style_left;
	s_path_parts.back().m_right_style = style_right;
	s_path_parts.back().m_line_style = line_style;

	s_last_point.x = ax;
	s_last_point.y = ay;

	s_path_parts.back().m_verts.push_back(s_last_point);
}


void Tesselator::add_line_segment(float ax, float ay)
// Add a line running from the previous anchor point to the
// given new anchor point.
{
	s_last_point.x = ax;
	s_last_point.y = ay;
	s_path_parts.back().m_verts.push_back(s_last_point);
}


int Tesselator::curve(float p0x, float p0y, float p1x, float p1y, float p2x, float p2y, int curDepth )
// Recursive routine to generate bezier curve within tolerance.
{
	// Midpoint on line between two endpoints.
	float	midx = (p0x + p2x) * 0.5f;
	float	midy = (p0y + p2y) * 0.5f;

	// Midpoint on the curve.
	float	qx = (midx + p1x) * 0.5f;
	float	qy = (midy + p1y) * 0.5f;

	float	dist = fabsf(midx - qx) + fabsf(midy - qy);

	if ( dist < s_tolerance )
	{
		add_line_segment( p2x, p2y );
    return curDepth;
	}
	else
	{
		int d1 = curve( p0x, p0y, (p0x + p1x) * 0.5f, (p0y + p1y) * 0.5f, qx, qy, curDepth + 1 );
		int d2 = curve( qx, qy, (p1x + p2x) * 0.5f, (p1y + p2y) * 0.5f, p2x, p2y, curDepth + 1 );

    return max( d1, d2 );
	}
}


int Tesselator::add_curve_segment(float cx, float cy, float ax, float ay )
{
	if ( cx == ax && cy == ay ) 
  {
		add_line_segment( ax, ay );
    return 0;
  }
  else 
  {
		int depth = curve( s_last_point.x, s_last_point.y, cx, cy, ax, ay, 0 );
    return depth;
  }
}


void Tesselator::end_path()
// Mark the end of a set of edges that all use the same styles.
{
	if (s_path_parts.back().m_line_style >= 0 && s_path_parts.back().m_verts.size() > 1) {
		// Emit our line.
		accepter->accept_line_strip(
			s_path_parts.back().m_line_style,
			&s_path_parts.back().m_verts[0],
			s_path_parts.back().m_verts.size());
	}
}

}
