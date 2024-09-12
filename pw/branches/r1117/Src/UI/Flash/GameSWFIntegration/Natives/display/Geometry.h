#pragma once

#include <Gl.h>

namespace flash
{

class Vector2
{
public:
	int x,y;
  Vector2() : x(0), y(0) {}
	Vector2(int a, int b):x(a),y(b){}
	bool operator==(const Vector2& v)const{return v.x==x && v.y==y;}
	bool operator!=(const Vector2& v)const{return v.x!=x || v.y!=y;}
	bool operator<(const Vector2& v) const {return (y==v.y)?(x < v.x):(y < v.y);}
	const Vector2 operator-(const Vector2& v)const { return Vector2(x-v.x,y-v.y);}
	const Vector2 operator+(const Vector2& v)const { return Vector2(x+v.x,y+v.y);}
	Vector2& operator+=(const Vector2& v){ x+=v.x; y+=v.y; return *this;}
	const Vector2 operator*(int p)const { return Vector2(x*p,y*p);}
	Vector2& operator/=(int v) { x/=v; y/=v; return *this;}
	int dot(const Vector2& r) const { return x*r.x+y*r.y;}
};

class GeomShape
{
private:
	void TessellateGLU();
	static void __stdcall GLUCallbackBegin(GLenum type, GeomShape* obj);
	static void __stdcall GLUCallbackEnd(GeomShape* obj);
	static void __stdcall GLUCallbackVertex(Vector2* vertexData, GeomShape* obj);
	static void __stdcall GLUCallbackCombine(GLdouble coords[3], void *vertex_data[4], 
				       GLfloat weight[4], Vector2** outData, GeomShape* obj);

	GLenum curTessTarget;
	nstl::vector<Vector2*> tmpVertices;

// 	void SetStyles(const std::list<FILLSTYLE>* styles);
// 
// 	const FILLSTYLE* style;
// 	arrayElem* varray;

	bool hasFill;
public:
	GeomShape() : curTessTarget(0), /*style(NULL),varray(NULL),*/hasFill(false),color(0){}

  nstl::vector<Vector2> triangles;
	nstl::vector<nstl::vector<Vector2> > triangle_strips;
	nstl::vector<nstl::vector<Vector2> > triangle_fans;
	nstl::vector<nstl::vector<Vector2> > outlines;

	unsigned int color;

  void Precache();

  struct VertexStride
  {
    short x, y;
    float xShift, yShift;
    Render::Color color;
    float aliasing; 
    float aliasingScale;
    CVec2 distanceUV;
    CVec2 textureUV;
  };


//	void Render(int x=0, int y=0) const;
//	void BuildFromEdges(const std::list<FILLSTYLE>* styles);
  
};

typedef nstl::vector<GeomShape> GeometryShapes;

class ShapesBuilder
{
private:
	nstl::map< unsigned int, nstl::vector< nstl::vector<Vector2> > > shapesMap;
	void joinOutlines();
	static bool IsOutlineEmpty(const nstl::vector<Vector2>& outline);
public:
	void extendOutlineForColor(unsigned int color, const Vector2& v1, const Vector2& v2);
	void outputShapes( GeometryShapes& shapes );
};

};
