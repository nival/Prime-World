#include "TamarinPCH.h"

#include <Render/FlashRendererInterface.h>

#include "Tesselate.h"
#include "MeshSet.h"

namespace flash
{

	//
	// edge
	//

	edge::edge() :
		m_cx(0), m_cy(0),
		m_ax(0), m_ay(0)
	{
	}

  edge::edge(float cx, float cy, float ax, float ay)
	{
		// edges can't be infinite
		m_cx = cx >= -3.402823466e+38F && cx <= 3.402823466e+38F ? cx : 0.0f;
		m_cy = cy >= -3.402823466e+38F && cy <= 3.402823466e+38F ? cy : 0.0f;
		m_ax = ax >= -3.402823466e+38F && ax <= 3.402823466e+38F ? ax : 0.0f;
		m_ay = ay >= -3.402823466e+38F && ay <= 3.402823466e+38F ? ay : 0.0f;
	}

	void	edge::tesselate_curve( Tesselator& tesselator ) 
	{
		tesselator.add_curve_segment( m_cx, m_cy, m_ax, m_ay );
	}


	bool	edge::is_straight() const
	{
		return m_cx == m_ax && m_cy == m_ay;
	}

  void  edge::lerp( const edge& e1, const edge& e2, float t )
  {
    m_cx = e1.m_cx * ( 1.f - t ) + e2.m_cx * t;
    m_cy = e1.m_cy * ( 1.f - t ) + e2.m_cy * t;
    m_ax = e1.m_ax * ( 1.f - t ) + e2.m_ax * t;
    m_ay = e1.m_ay * ( 1.f - t ) + e2.m_ay * t;
  }

	//
	// path
	//


	path::path()
		:
		m_new_shape(false)
	{
		reset(0, 0, 0, 0, 0);
	}

	path::path(float ax, float ay, int fill0, int fill1, int line)
	{
		reset(ax, ay, fill0, fill1, line);
	}


	void	path::reset(float ax, float ay, int fill0, int fill1, int line)
	// Reset all our members to the given values, and clear our edge list.
	{
		m_ax = ax;
		m_ay = ay;
		m_fill0 = fill0;
		m_fill1 = fill1;
		m_line = line;

		m_edges.resize(0);
	}


	bool	path::is_empty() const
	// Return true if we have no edges.
	{
		return m_edges.size() == 0;
	}


	bool	path::point_test(float x, float y)
	// Point-in-shape test.  Return true if the query point is on the filled
	// interior of this shape.
	{
		if (m_edges.size() <= 0)
		{
			return false;
		}

		if (m_fill0 < 0)
		{
			// No interior fill.
			
			// @@ This isn't quite right due to some paths
			// doing double-duty with both fill0 and fill1
			// styles.

			// TODO: get rid of this stupid fill0/fill1
			// business -- a path should always be
			// counterclockwise and have one fill.  For
			// input paths with fill1, generate a separate
			// reversed path with fill set to fill1.
			// Group all paths with the same fill into a
			// path group; do the point_test on the whole
			// group.
			return false;
		}

		// Shoot a horizontal ray from (x,y) to the right, and
		// count the number of edge crossings.  An even number
		// of crossings means the point is outside; an odd
		// number means it's inside.

		float x0 = m_ax;
		float y0 = m_ay;

		int ray_crossings = 0;
		for (int i = 0, n = m_edges.size(); i < n; i++)
		{
			const edge& e = m_edges[i];

			float x1 = e.m_ax;
			float y1 = e.m_ay;

			if (e.is_straight()) {
				// Straight-line case.
				
				// See if (x0,y0)-(x1,y1) crosses (x,y)-(infinity,y)
			
				// Does the segment straddle the horizontal ray?
				bool cross_up = (y0 < y && y1 >= y);
				bool cross_down = (!cross_up) && (y0 > y && y1 <= y);
				if (cross_up || cross_down)
				{
					// Straddles.
				
					// Is the crossing point to the right of x?
					float dy = y1 - y0;

					// x_intercept = x0 + (x1 - x0) * (y - y0) / dy;
					float x_intercept_times_dy = x0 * dy + (x1 - x0) * (y - y0);

					// text x_intercept > x
				
					// factor out the division; two cases depending on sign of dy
					if (cross_up)
					{
						assert(dy > 0);
						if (x_intercept_times_dy > x * dy)
						{
							ray_crossings++;
						}
					}
					else
					{
						// dy is negative; reverse the inequality test
						assert(dy < 0);
						if (x_intercept_times_dy < x * dy)
						{
							ray_crossings++;
						}
					}
				}
			}
			else
			{
				// Curve case.
				float cx = e.m_cx;
				float cy = e.m_cy;

				// Find whether & where the curve crosses y
				if ((y0 < y && y1 < y && cy < y)
				    || (y0 > y && y1 > y && cy > y))
				{
					// All above or all below -- no possibility of crossing.
				}
				else if (x0 < x && x1 < x && cx < x)
				{
					// All to the left -- no possibility of crossing to the right.
				}
				else
				{
					// Find points where the curve crosses y.

					// Quadratic bezier is:
					//
					// p = (1-t)^2 * a0 + 2t(1-t) * c + t^2 * a1
					//
					// We need to solve for x at y.
					
					// Use the quadratic formula.

					// Numerical Recipes suggests this variation:
					// q = -0.5 [b +sgn(b) sqrt(b^2 - 4ac)]
					// x1 = q/a;  x2 = c/q;

					float A = y1 + y0 - 2 * cy;
					float B = 2 * (cy - y0);
					float C = y0 - y;

					float rad = B * B - 4 * A * C;
					if (rad < 0)
					{
						// No real solutions.
					}
					else
					{
						float q;
						float sqrt_rad = sqrtf(rad);
						if (B < 0) {
							q = -0.5f * (B - sqrt_rad);
						} else {
							q = -0.5f * (B + sqrt_rad);
						}

						// The old-school way.
						// float t0 = (-B + sqrt_rad) / (2 * A);
						// float t1 = (-B - sqrt_rad) / (2 * A);

						if (A != 0)
						{
							float t0 = q / A;
							if (t0 >= 0 && t0 < 1) {
								float x_at_t0 =
									x0 + 2 * (cx - x0) * t0 + (x1 + x0 - 2 * cx) * t0 * t0;
								if (x_at_t0 > x) {
									ray_crossings++;
								}
							}
						}

						if (q != 0)
						{
							float t1 = C / q;
							if (t1 >= 0 && t1 < 1) {
								float x_at_t1 =
									x0 + 2 * (cx - x0) * t1 + (x1 + x0 - 2 * cx) * t1 * t1;
								if (x_at_t1 > x) {
									ray_crossings++;
								}
							}
						}
					}
				}
			}

			x0 = x1;
			y0 = y1;
		}

		if (ray_crossings & 1)
		{
			// Odd number of ray crossings means the point
			// is inside the poly.
			return true;
		}
		return false;
	}

	void	path::tesselate( Tesselator& tesselator )
	// Push this path into the tesselator.
	{
		tesselator.begin_path(
			m_fill0 - 1,
			m_fill1 - 1,
			m_line - 1,
			m_ax, m_ay);

		for (int i = 0; i < m_edges.size(); i++)
		{
			m_edges[i].tesselate_curve( tesselator );
		}

    tesselator.end_path();
	}

	//
	// Mesh
	//
	
  Mesh::Mesh() :
    colorsCached(false),
    allignedTriangleList(0)
	{

	}

  Mesh::~Mesh()
  {
    if ( allignedTriangleList )
    {
      Aligned_Free( allignedTriangleList );
      allignedTriangleList = 0;
    }
  }

	void Mesh::reserve_triangles( int expected_triangle_count )
	{
		triangleList.reserve( expected_triangle_count * 6 );  // 6 coords per triangle
	}

  void Mesh::reserve_vertices( int expected_vertex_count )
  {

  }

  void Mesh::add_triangle(const PointWithID pts[3])
	{
    for ( int i = 0; i < 3; i++)
    {
      triangleList.push_back( CVec2( pts[i].x, pts[i].y ) );
    }
	}

  void Mesh::ApplyColorsAndUV( SWF_FILLSTYLE& style, Movie* _movie )
  {
    if ( !colorsCached )
    {
      allignedTriangleList = (Render::ShapeVertex *)Aligned_MAlloc( triangleList.size() * sizeof(Render::ShapeVertex) , 16);

      for (int i = 0; i < triangleList.size(); ++i)
      {
        allignedTriangleList[i].x = triangleList[i].x;
        allignedTriangleList[i].y = triangleList[i].y;

        allignedTriangleList[i].color.A = style.Color.a;
        allignedTriangleList[i].color.B = style.Color.b;
        allignedTriangleList[i].color.G = style.Color.g;
        allignedTriangleList[i].color.R = style.Color.r;
      }

      colorsCached = true;
    }
  }

	void Mesh::Display( Render::IFlashRenderer* _renderer, Movie* _movie, SWF_FILLSTYLE& style )
	{
    style.Apply( _renderer, _movie, true );

		if ( triangleList.size() > 0 ) 
    {
      ApplyColorsAndUV( style, _movie );

      NI_VERIFY( allignedTriangleList, "Shape trinale list is not ready", return );
			_renderer->DrawTriangleList( allignedTriangleList, triangleList.size(), -1 );
		}
  }

  void Mesh::DisplayMorph( Render::IFlashRenderer* _renderer, Movie* _movie, SWF_FILLSTYLE& style1, SWF_FILLSTYLE& style2, float rate )
  {
    style1.Apply( _renderer, _movie, true );
    style2.Apply( _renderer, _movie, false );

    if ( triangleList.size() > 0 ) 
    {
      _renderer->SetMorph( rate );
      NI_VERIFY( allignedTriangleList, "Shape trinale list is not ready", return );
      _renderer->DrawTriangleList( allignedTriangleList, triangleList.size(), -1 );
    }
  }

	//
	// LineStrip
	//

	LineStrip::LineStrip() 
	{

  }

	LineStrip::LineStrip(const CVec2 coords[], int coord_count)
	{
		assert(coords != NULL);
		assert(coord_count > 1);

		pointCoords.resize(coord_count);	// 2 coords per vert
		
    memcpy( &pointCoords[0], coords, coord_count * sizeof(CVec2) );
	}


	void	LineStrip::Display( Render::IFlashRenderer* _renderer, Movie* _movie, SWF_LINESTYLE2& style )
	{
    if ( pointCoords.size() > 0 )
    {
      style.Apply( _renderer, _movie );
      _renderer->DrawLineStrip( pointCoords, -1 );
    }
	}

  void	LineStrip::DisplayMorph( Render::IFlashRenderer* _renderer, Movie* _movie, SWF_LINESTYLE2& style1, SWF_LINESTYLE2& style2, float rate )
  {
    if ( pointCoords.size() > 0 )
    {
      style1.ApplyMorph( _renderer, style2, _movie, rate );
      _renderer->SetMorph( rate );
      _renderer->DrawLineStrip( pointCoords, -1 );
    }
  }

	// Utility: very simple greedy tri-stripper.  Useful for
	// stripping the stacks of trapezoids that come out of our
	// tesselator.
	struct tri_stripper
	{
		// A set of strips; we'll join them together into one
		// strip during the flush.
    nstl::vector< nstl::vector<CVec2> >	m_strips;
		int	m_last_strip_used;

		tri_stripper()
			: m_last_strip_used(-1)
		{
		}

		void	add_triangle(const CVec2& v0, const CVec2& v1, const CVec2& v2)
		// Add a triangle to our strip.
		{
			// TODO: should probabably just rip out the
			// tristripper and directly use the trilists
			// produced by the new triangulator.
			//
			// Dumb temp code!
			if (m_strips.size() == 0) {
				// Start a new strip.
				m_strips.resize(m_strips.size() + 1);
			}

			m_strips[0].push_back(v0);
			m_strips[0].push_back(v0);
			m_strips[0].push_back(v1);
			m_strips[0].push_back(v2);
			m_strips[0].push_back(v2);
		}
	};

	//
	// MeshSet
	//


	MeshSet::MeshSet() :
    tesselated(false),
		m_error_tolerance(0)	// invalid -- don't use this constructor; it's only here for array (@@ fix array)
	{
	}

  MeshSet::MeshSet( float error_tolerance ) :
    tesselated(false),
    m_error_tolerance(error_tolerance)
  {
  }

	MeshSet::MeshSet( const ITesselatedShape* sh, float error_tolerance ) :
		m_error_tolerance(error_tolerance)
	{
    Tesselate( sh, error_tolerance );
  }

  void MeshSet::Tesselate( const ITesselatedShape* sh, float error_tolerance )
  {
    m_error_tolerance = error_tolerance;

    NI_VERIFY(m_error_tolerance > 0, "bad tolerance", m_error_tolerance = 1.0f;);

    layers.clear();

		// For collecting triangles emitted by the new tesselator.
		struct collect_tris : public IMeshAccepter
		{
			MeshSet*	meshSet;	// the MeshSet that receives triangles.
			Mesh* mesh;
			bool m_new_layer;

			collect_tris(MeshSet* set) : meshSet(set), mesh(NULL), m_new_layer(true) {
			}
			virtual ~collect_tris() {}

			// Overrides from Mesh_accepter
			
      virtual void	accept_line_strip(int style, const CVec2 coords[], int coord_count)
			// Remember this line strip in our Mesh set.
			{
				if (m_new_layer) 
        {
					meshSet->new_layer();
					m_new_layer = false;
				}

				meshSet->add_line_strip(style, coords, coord_count);
			}

			virtual void begin_trilist( int style, int expected_triangle_count, int expected_vertex_count )
			{
        if (m_new_layer) 
        {
					meshSet->new_layer();
					m_new_layer = false;
				}

				mesh = meshSet->get_mutable_mesh(style);
				mesh->reserve_triangles( expected_triangle_count );
        mesh->reserve_vertices( expected_vertex_count );
			}

			virtual void accept_trilist_batch(const PointWithID trilist[], int point_count)
			// Accept one or more triangles to add to the
			// Mesh for the specified style.
			{
				// Convert input from float coords to
				// coord_component and add them to the Mesh.
				PointWithID tri[3];

				for ( int i = 0; i < point_count; i += 3 ) 
        {
					tri[0] = trilist[i];
          tri[1] = trilist[i + 1];
          tri[2] = trilist[i + 2];

					mesh->add_triangle( tri );
				}
			}

			virtual void end_trilist()
			{
				mesh = NULL;
			}

			virtual void end_shape()
			{
				m_new_layer = true;
			}
		};

		// New tesselator.
		collect_tris	accepter(this);
		sh->Tesselate(error_tolerance, &accepter);

    tesselated = true;
	}


	MeshSet::~MeshSet()
	{
	}

	void MeshSet::new_layer()
	// Make room for a new Layer.
	{
		layers.push_back();
	}

  void	MeshSet::Display( Render::IFlashRenderer* _renderer, Movie* _movie, FillStyles& fills, LineStyles& line_styles ) const
	{
    Layers::const_iterator it = layers.begin();
    Layers::const_iterator last = layers.end();

		for ( ; it != last; ++it ) 
    {
			const Layer& l = *it;
			
      int maxStyle = l.meshes.size() > l.lineStrips.size() ? l.meshes.size() : l.lineStrips.size();

			// Dump Meshes into renderer, one Mesh per style.
			for ( int i = 0; i < maxStyle; ++i ) 
      {
        if ( i < l.meshes.size() )
        {
          if ( l.meshes[i] )
            l.meshes[i]->Display( _renderer, _movie, fills[i] );
        }
			}

      for ( int i = 0; i < maxStyle; ++i ) 
      {
        if ( i < l.lineStrips.size() )
        {
          for ( int k = 0; k < l.lineStrips[i].size(); ++k )
          {
            if ( l.lineStrips[i][k] )
              l.lineStrips[i][k]->Display( _renderer, _movie, line_styles[i] );
          }
        }
      }
		}
	}

  void MeshSet::DisplayMorph( Render::IFlashRenderer* _renderer, Movie* _movie, FillStyles& fills1, LineStyles& line_styles1, 
    FillStyles& fills2, LineStyles& line_styles2, float rate ) const
  {
    Layers::const_iterator it = layers.begin();
    Layers::const_iterator last = layers.end();

    for ( ; it != last; ++it ) 
    {
      const Layer& l = *it;

      int maxStyle = l.meshes.size() > l.lineStrips.size() ? l.meshes.size() : l.lineStrips.size();

      // Dump Meshes into renderer, one Mesh per style.
      for ( int i = 0; i < maxStyle; ++i ) 
      {
        if ( i < l.meshes.size() )
        {
          if ( l.meshes[i] )
            l.meshes[i]->DisplayMorph( _renderer, _movie, fills1[i], fills2[i], rate );
        }
      }

      for ( int i = 0; i < maxStyle; ++i ) 
      {
        if ( i < l.lineStrips.size() )
        {
          for ( int k = 0; k < l.lineStrips[i].size(); ++k )
          {
            if ( l.lineStrips[i][k] )
              l.lineStrips[i][k]->DisplayMorph( _renderer, _movie, line_styles1[i], line_styles2[i], rate );
          }
        }
      }
    }
  }

  void MeshSet::ApplyColorsAndUV( Render::IFlashRenderer* _renderer, Movie* _movie, FillStyles& fills, const LineStyles& line_styles ) const
  {
    Layers::const_iterator it = layers.begin();
    Layers::const_iterator last = layers.end();

    for ( ; it != last; ++it ) 
    {
      const Layer& l = *it;

      int maxStyle = l.meshes.size() > l.lineStrips.size() ? l.meshes.size() : l.lineStrips.size();

      // Dump Meshes into renderer, one Mesh per style.
      for ( int i = 0; i < maxStyle; ++i ) 
      {
        if ( i < l.meshes.size() )
        {
          if ( l.meshes[i] )
            l.meshes[i]->ApplyColorsAndUV( fills[i], _movie );
        }
      }
    }
  }

	void MeshSet::expand_styles_to_include(int style)
	{
		Layer* l = &layers.back();

		// Expand our Mesh list if necessary.
		if (style >= l->meshes.size()) {
			l->meshes.resize(style + 1, 0);
		}

		if (l->meshes[style] == NULL) {
			l->meshes[style] = new Mesh;
		}
	}

	Mesh* MeshSet::get_mutable_mesh(int style)
	{
		expand_styles_to_include(style);
		return layers.back().meshes[style];
	}

	void	MeshSet::add_line_strip(int style, const CVec2 coords[], int coord_count)
	// Add the specified line strip to our list of things to render.
	{
		assert(style >= 0);
		assert(style < 1000);	// sanity check
		assert(coords != NULL);
		assert(coord_count > 1);

    Layer& lastLayer = layers.back();

    if ( style >= lastLayer.lineStrips.size() )
      lastLayer.lineStrips.resize(style + 1);

		lastLayer.lineStrips[style].push_back(new LineStrip(coords, coord_count));
	}

}

