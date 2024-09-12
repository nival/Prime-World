#pragma once

#include <Render/FlashRendererInterface.h>

namespace flash
{

struct PointWithID;

_interface IMeshAccepter;
_interface ITesselatedShape;
class Tesselator;

struct edge
// Together with the previous anchor, defines a quadratic
// curve segment.
{
	edge();
	edge(float cx, float cy, float ax, float ay);

	void	tesselate_curve( Tesselator& tesselator );
	bool	is_straight() const;
  void  lerp( const edge& e1, const edge& e2, float t );
	
//private:
	// *quadratic* bezier: point = p0 * t^2 + p1 * 2t(1-t) + p2 * (1-t)^2
	float	m_cx, m_cy;		// "control" point
	float	m_ax, m_ay;		// "anchor" point
};


struct path
// A subset of a shape -- a series of edges sharing a single set
// of styles.
{
	path();
	path(float ax, float ay, int fill0, int fill1, int line);

	void	reset(float ax, float ay, int fill0, int fill1, int line);
	bool	is_empty() const;

	bool	point_test(float x, float y);

	// Push the path into the tesselator.
	void	tesselate( Tesselator& tesselator );

//private:
	int	m_fill0, m_fill1, m_line;
	float	m_ax, m_ay;	// starting point
  nstl::vector<edge>	m_edges;
	bool	m_new_shape;
};

class Mesh : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( Mesh, BaseObjectST )

public: 
  Mesh();
  virtual ~Mesh();

	void  reserve_triangles( int expected_triangle_count );
  void  reserve_vertices( int expected_vertex_count );

  void  add_triangle( const PointWithID pts[3] );

	void	Display( Render::IFlashRenderer* _renderer, Movie* _movie, SWF_FILLSTYLE& style );
  void	DisplayMorph( Render::IFlashRenderer* _renderer, Movie* _movie, SWF_FILLSTYLE& style1, SWF_FILLSTYLE& style2, float rate );
  void  ApplyColorsAndUV( SWF_FILLSTYLE& style, Movie* _movie );

  int   NumberOfVertices() const { return triangleList.size(); }
private:

  nstl::vector<CVec2> triangleList;
  Render::ShapeVertex* allignedTriangleList;

  bool colorsCached;
};


class LineStrip : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( LineStrip, BaseObjectST )

public: 
	LineStrip();
	LineStrip(const CVec2 coords[], int coord_count);

	void	Display( Render::IFlashRenderer* _renderer, Movie* _movie, SWF_LINESTYLE2& style );
  void	DisplayMorph( Render::IFlashRenderer* _renderer, Movie* _movie, SWF_LINESTYLE2& style1, SWF_LINESTYLE2& style2, float rate );

private:
  nstl::vector<CVec2>	pointCoords;
};


class MeshSet : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( MeshSet, BaseObjectST )

public: 
	MeshSet();
  MeshSet( float error_tolerance );
	MeshSet( const ITesselatedShape* sh, float error_tolerance );
	~MeshSet();

  void  Tesselate( const ITesselatedShape* sh, float error_tolerance );

	float get_error_tolerance() const { return m_error_tolerance; }

  void  Display( Render::IFlashRenderer* _renderer, Movie* _movie, FillStyles& fills, LineStyles& line_styles ) const;
  void  DisplayMorph( Render::IFlashRenderer* _renderer, Movie* _movie, FillStyles& fills1, LineStyles& line_styles1, 
                                             FillStyles& fills2, LineStyles& line_styles2,
                                             float rate ) const;
  void  ApplyColorsAndUV( Render::IFlashRenderer* _renderer, Movie* _movie, FillStyles& fills, const LineStyles& line_styles ) const;

	void  new_layer();
	void  add_line_strip(int style, const CVec2 coords[], int coord_count);

	Mesh* get_mutable_mesh(int style);

  bool IsTesselated() const { return tesselated; }

private:
	void  expand_styles_to_include(int style);
	
	float	m_error_tolerance;

	struct Layer {
		nstl::vector<Strong<Mesh>> meshes;  // one mesh per style.
    nstl::vector<nstl::vector<Strong<LineStrip>>> lineStrips; // lines per style
	};

  typedef nstl::list<Layer> Layers;

	Layers layers;

  bool tesselated;
};

}	

