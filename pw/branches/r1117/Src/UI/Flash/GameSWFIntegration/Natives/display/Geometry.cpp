#include "TamarinPCH.h"

#include <GLU.h>

#include "geometry.h"

// void GeomShape::SetStyles(const std::list<FILLSTYLE>* styles)
// {
// 	static FILLSTYLE* clearStyle=NULL;
// 	if(!clearStyle)
// 	{
// 		clearStyle=new FILLSTYLE;
// 		clearStyle->FillStyleType=0x00;
// 		clearStyle->Color=RGBA(0,0,0,0);
// 	}
// 
// 	if(styles)
// 	{
// 		if(color)
// 		{
// 			if(color > styles->size())
// 				throw RunTimeException("Not enough styles in GeomShape::SetStyles");
// 
// 			//Simulate array access :-(
// 			list<FILLSTYLE>::const_iterator it=styles->begin();
// 			for(unsigned int i=0;i<(color-1);i++)
// 				it++;
// 			style=&(*it);
// 		}
// 		else
// 			style=clearStyle;
// 	}
// }

namespace flash
{

// void GeomShape::BuildFromEdges(const std::list<FILLSTYLE>* styles)
// {
// 	if(outlines.empty())
// 		return;
// 
// 	SetStyles(styles);
// 
// 	TessellateGLU();
// }

void GeomShape::TessellateGLU()
{
	//NOTE: do not invalidate the contents of outline in this function
	GLUtesselator* tess = gluNewTess();

	gluTessCallback(tess, GLU_TESS_BEGIN_DATA, (void (_stdcall*)())GLUCallbackBegin );
	gluTessCallback(tess, GLU_TESS_VERTEX_DATA, (void(_stdcall*)())GLUCallbackVertex );
	gluTessCallback(tess, GLU_TESS_END_DATA, (void(_stdcall*)())GLUCallbackEnd );
	gluTessCallback(tess, GLU_TESS_COMBINE_DATA, (void(_stdcall*)())GLUCallbackCombine );
	gluTessProperty(tess, GLU_TESS_WINDING_RULE,GLU_TESS_WINDING_ODD);
	
	//Let's create a vector of pointers to store temporary coordinates
	//passed to GLU
	vector<GLdouble*> tmpCoord;
	gluTessBeginPolygon(tess,this);

	for ( int i = 0; i < outlines.size(); i++ )
	{
		//Check if the contour is closed
		if ( outlines[i].front()==outlines[i].back() )
			hasFill = true;
		else
			continue;

		gluTessBeginContour(tess);

			//First and last vertex are automatically linked
			for ( int j = 1; j < outlines[i].size(); j++ )
			{
				GLdouble* loc = new GLdouble[3];
				loc[0] = outlines[i][j].x;
				loc[1] = outlines[i][j].y;
				loc[2] = 0;
				tmpCoord.push_back(loc);

				//As the data we pass the Vector2 pointer
				gluTessVertex(tess,loc,&outlines[i][j]);
			}

		gluTessEndContour(tess);
	}
	gluTessEndPolygon(tess);
	
	//Clean up locations
	for ( int i = 0; i < tmpCoord.size(); i++ )
		delete[] tmpCoord[i];
	
	//Clean up temporary vertices
	for ( int i = 0; i < tmpVertices.size(); i++ )
		delete tmpVertices[i];

	gluDeleteTess(tess);
}

void GeomShape::GLUCallbackBegin(GLenum type, GeomShape* obj)
{
	NI_ASSERT( !obj->curTessTarget, "Must be 0" );

	if ( type == GL_TRIANGLE_FAN )
	{
		obj->triangle_fans.push_back(vector<Vector2>());
		obj->curTessTarget = GL_TRIANGLE_FAN;
	}
	else if ( type == GL_TRIANGLE_STRIP )
	{
		obj->triangle_strips.push_back(vector<Vector2>());
		obj->curTessTarget = GL_TRIANGLE_STRIP;
	}
	else if ( type == GL_TRIANGLES )
	{
		obj->curTessTarget = GL_TRIANGLES;
	}
  else
  {
    NI_ALWAYS_ASSERT( "Wrong primitive type" );
  }
}

void GeomShape::GLUCallbackVertex(Vector2* vertexData, GeomShape* obj)
{
	if ( obj->curTessTarget == GL_TRIANGLE_FAN )
	{
		obj->triangle_fans.back().push_back(*vertexData);
	}
	else if( obj->curTessTarget == GL_TRIANGLE_STRIP )
	{
		obj->triangle_strips.back().push_back(*vertexData);
	}
	else if( obj->curTessTarget == GL_TRIANGLES )
	{
		obj->triangles.push_back(*vertexData);
	}
}

void GeomShape::GLUCallbackEnd(GeomShape* obj)
{
  NI_ASSERT( obj->curTessTarget, "Must be not 0" )

	if ( obj->curTessTarget == GL_TRIANGLES )
  {
		NI_ASSERT( obj->triangles.size() % 3 == 0, "Number of vertices must be " );
  }

	obj->curTessTarget=0;
}

void GeomShape::GLUCallbackCombine(GLdouble coords[3], void* vertex_data[4], 
				   GLfloat weight[4], Vector2** outData, GeomShape* obj)
{
	//No real operations, apart from generating a new vertex at the passed coordinates
	obj->tmpVertices.push_back( new Vector2(coords[0],coords[1]) );
	*outData=obj->tmpVertices.back();
}


void GeomShape::Precache()
{
  TessellateGLU();
}

bool ShapesBuilder::IsOutlineEmpty( const nstl::vector< Vector2 >& outline )
{
	return outline.empty();
}

void ShapesBuilder::joinOutlines()
{
  nstl::map< unsigned int, nstl::vector< nstl::vector<Vector2> > >::iterator it=shapesMap.begin();

	for( ;it != shapesMap.end(); it++ )
	{
		vector< vector<Vector2> >& outlinesForColor=it->second;
		//Repack outlines of the same color, avoiding excessive copying
		for(int i=0;i<int(outlinesForColor.size());i++)
		{
      NI_ASSERT(outlinesForColor[i].size() >= 2, "Wrong outline size");

			//Already closed paths are ok
			if ( outlinesForColor[i].front()==outlinesForColor[i].back() )
				continue;

			for ( int j = outlinesForColor.size() - 1; j >= 0; j-- )
			{
				if( j == i || outlinesForColor[j].empty() )
					continue;

				if ( outlinesForColor[i].front()==outlinesForColor[j].back() )
				{
					//Copy all the vertex but the origin in this one
					outlinesForColor[j].insert(outlinesForColor[j].end(),
									outlinesForColor[i].begin()+1,
									outlinesForColor[i].end());
					//Invalidate the origin, but not the high level vector
					outlinesForColor[i].clear();

					break;
				}
				else if(outlinesForColor[i].back()==outlinesForColor[j].back())
				{
					//CHECK: this works for adjacent shapes of the same color?
					//Copy all the vertex but the origin in this one

// 					outlinesForColor[j].insert(outlinesForColor[j].end(),
// 									outlinesForColor[i].rbegin()+1,
// 									outlinesForColor[i].rend());

          if ( outlinesForColor[i].size() > 0 )
          {
            int startID = outlinesForColor[j].size();

            outlinesForColor[j].resize( outlinesForColor[j].size() + outlinesForColor[i].size() - 1 );

            for ( int k = outlinesForColor[i].size() - 2, i = 0; k >= 0; --k, ++i )
            {
              outlinesForColor[j][startID + i] = outlinesForColor[i][k];
            }
          }

					//Invalidate the origin, but not the high level vector
					outlinesForColor[i].clear();

					break;
				}
			}
		}
		
		//Kill all the empty outlines
		outlinesForColor.erase(remove_if(outlinesForColor.begin(),outlinesForColor.end(), IsOutlineEmpty),
				       outlinesForColor.end());

    NI_ASSERT( !outlinesForColor.empty(), "Outlines must be filled" );
	}
}

void ShapesBuilder::extendOutlineForColor(unsigned int color, const Vector2& v1, const Vector2& v2)
{
  nstl::vector< nstl::vector<Vector2> >& outlinesForColor=shapesMap[color];
	//Search a suitable outline to attach this new vertex
	for(int i=0;i<outlinesForColor.size();i++)
	{
    NI_ASSERT(outlinesForColor[i].size() >= 2, "Wrong outline size");

		if(outlinesForColor[i].front()==outlinesForColor[i].back())
			continue;
		if(outlinesForColor[i].back()==v1)
		{
			outlinesForColor[i].push_back(v2);
			return;
		}
	}
	//No suitable outline found, create one
	outlinesForColor.push_back(nstl::vector<Vector2>());
	outlinesForColor.back().reserve(2);
	outlinesForColor.back().push_back(v1);
	outlinesForColor.back().push_back(v2);
}

void ShapesBuilder::outputShapes( GeometryShapes& shapes )
{
	//Let's join shape pieces together
	joinOutlines();

	nstl::map< unsigned int, nstl::vector< nstl::vector<Vector2> > >::iterator it=shapesMap.begin();

	for(;it!=shapesMap.end();it++)
	{
		shapes.push_back(GeomShape());
		shapes.back().outlines.swap(it->second);
		shapes.back().color=it->first;
	}
}

}