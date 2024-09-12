#pragma once

#include "../../SwfTypes.h"

namespace gameswf
{
  struct point;
}

namespace flash
{
  struct PointWithID
  {
    float	x;
    int   uniqueID1;
    float	y;
    int   uniqueID2;
  };

  _interface IMeshAccepter 
  {
    virtual void begin_trilist( int style, int expected_triangle_count, int expected_vertex_count ) = 0;
    virtual void accept_trilist_batch( const PointWithID trilist[], int point_count ) = 0;
    virtual void end_trilist() = 0;

    virtual void accept_line_strip( int style, const CVec2 coords[], int point_count ) = 0;
    virtual void end_shape() = 0;
  };

  _interface ITesselatedShape
  {
    virtual const FillStyles& GetFillStyles() const = 0;
    virtual const LineStyles& GetLineStyles() const = 0;

    virtual void  Tesselate( float error_tolerance, IMeshAccepter * accepter ) const = 0;
  };

  class Tesselator
  {
  public:  
		void	begin_shape( const ITesselatedShape* shape, IMeshAccepter* accepter, float curve_error_tolerance );
		void	end_shape();

		// A path is a subpart of a shape, having a consistent style.
		void	begin_path(int style_left, int style_right, int line_style, float ax, float ay);
		void	add_line_segment(float ax, float ay);
		int 	add_curve_segment(float cx, float cy, float ax, float ay );
		void	end_path();

  private:

    int  curve(float p0x, float p0y, float p1x, float p1y, float p2x, float p2y, int curDepth );

    const ITesselatedShape * shape;
    IMeshAccepter * accepter;
  };
}

