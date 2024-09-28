#pragma once

namespace Render
{
  struct CrossColorTable
  {
    Render::Color colorNeg[3];
    Render::Color colorPos[3];
  };

  enum DebugRenderBuffer
  {
    DRBUFFER_DEFAULT = 0,
    DRBUFFER_STEP,

    DRBUFFER_COUNT
  };
  
  namespace DebugRenderer
  {
    enum ETextHAlign { HA_Left, HA_Center, HA_Right };
    enum ETextVAlign { VA_Top,  VA_Center, VA_Bottom };
  };

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  _interface IDebugRender
  {
    virtual void DrawLine2D( int x1, int y1, int x2, int y2, Render::Color color1, Render::Color color2 ) = 0;
    virtual void DrawLine3D( const CVec3& p1, const CVec3& p2, Render::Color color1, Render::Color color2, bool zTest ) = 0;
    
    virtual void DrawPoint2D( const int x, const int y, float size, Render::Color color ) = 0;
    virtual void DrawPoint3D( const CVec3& p, float size, Render::Color color, bool zTest ) = 0;																		 

    virtual void DrawAABB( const struct AABB &aabb, Render::Color color, bool zTest ) = 0;
    
    virtual void DrawBox3D( const Placement &pl, float size, Render::Color color, bool zTest ) = 0;
    virtual void DrawBox3D( const Matrix43 &mtx, float size, Render::Color color, bool zTest ) = 0;
    virtual void DrawCross3D( const Matrix43 &mtx, float sizePos, float sizeNeg, const CrossColorTable &colors, bool zTest ) = 0;
    virtual void DrawCross3D( const Matrix43 &mtx, float sizePos, float sizeNeg, Render::Color color, bool zTest ) = 0;

    virtual void DrawCircle3D( CVec3 const &center, float radius, int numSegments, Render::Color color, bool zTest ) = 0;

    virtual void DrawTriangle3D( const CVec3 &p1, const CVec3 &p2, const CVec3 &p3, Render::Color color, bool zTest) = 0;
    virtual void DrawCustomMesh(const void *points, int stride, const int *indices, int indCount, Render::Color color, bool zTest) = 0;

    virtual void DrawText( const char * text, const CVec2 & uiCoords, int size, const Render::Color & color,    DebugRenderer::ETextHAlign hAlign = DebugRenderer::HA_Center, DebugRenderer::ETextVAlign vAlign = DebugRenderer::VA_Center ) = 0;
    virtual void DrawText( const wchar_t * text, const CVec2 & uiCoords, int size, const Render::Color & color, DebugRenderer::ETextHAlign hAlign = DebugRenderer::HA_Center, DebugRenderer::ETextVAlign vAlign = DebugRenderer::VA_Center ) = 0;
    virtual void DrawText3D( const char * text, const CVec3 & pos, int size, const Render::Color & color ) = 0;
    virtual void DrawText3D( const wchar_t * text, const CVec3 & pos, int size, const Render::Color & color ) = 0;


    virtual void PushBuffer( DebugRenderBuffer buf ) = 0;
    virtual void PopBuffer() = 0;
    virtual void ClearBuffer( DebugRenderBuffer buf ) = 0;
  };

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  namespace DebugRenderer
	{
		void SetMatrix(const SHMatrix& view, const SHMatrix& proj);

		bool Initialize();

    // control current buffer (that receives all drawing)
    void PushBuffer(DebugRenderBuffer buf);
    void PopBuffer();

		void DrawLine2D( int x1, int y1, int x2, int y2, Render::Color color1, Render::Color color2 );
		void DrawLine3D( const CVec3& p1, const CVec3& p2, Render::Color color1, Render::Color color2, bool zTest );

		void DrawPoint2D( const int x, const int y, float size, Render::Color color );
		void DrawPoint3D( const CVec3& p, float size, Render::Color color, bool zTest );																		 

		void DrawAABB( const struct AABB &aabb, Render::Color color, bool zTest );

		void DrawBox3D( const Placement &pl, float size, Render::Color color, bool zTest );
		void DrawBox3D( const Matrix43 &mtx, float size, Render::Color color, bool zTest );
		void DrawCross3D( const Matrix43 &mtx, float sizePos, float sizeNeg, const CrossColorTable &colors, bool zTest );
		void DrawCross3D( const Matrix43 &mtx, float sizePos, float sizeNeg, Render::Color color, bool zTest );

    void DrawCircle3D( CVec3 const &center, float radius, int numSegments, Render::Color color, bool zTest );

		void Draw2D();
		void Draw3D();
    void ClearBuffer(DebugRenderBuffer buf);

		void ProjectPoint( CVec2 *pRes, const CVec3& point, int screenW, int screenH );

		//////////////////////////////////////////////////////////////////////////
		//	- для инициализации использует const vector<CVec3>& points, const vector<int>& indices, const Render::Color color, const bool useZTest
		//	- не работает с ResourceManager'ом, умирает сам - убивает свои ресурсы

		//  

		void DrawTriangle3D( const CVec3 &p1, const CVec3 &p2, const CVec3 &p3, Render::Color color, bool zTest);
    void DrawCustomMesh(const void *points, int stride, const int *indices, int indCount, Render::Color color, bool zTest);
		/* Doesn't implemented
		int DrawCustomMesh(const vector<CVec3>& points, const vector<int>& indices, const Render::Color color, const bool enableZTest, const bool wireframe, const bool persist );

		void DrawAxisAlignedBox(const CVec3& positon, const CVec3& scale, const Render::Color color, const bool enableZTest, const bool wireframe, const bool persist );
		void DrawBox(const Matrix43& positon, const CVec3& scale, const Render::Color color, const bool enableZTest, const bool wireframe, const bool persist );
		void DrawSphere(const CVec3& positon, float radius, const Render::Color color, bool enableZTest, const bool wireframe, const bool persist );
		void DrawCone(const Matrix43& positon, const float height, const float radius, const Render::Color color, const bool enableZTest, const bool wireframe, const bool persist );
		void DrawCylinder(const Matrix43& positon, const float height, const float radius, const Render::Color color, const bool enableZTest, const bool wireframe, const bool persist );
		*/
		//void DrawChoppedCone
		//void DrawFrustum
		
    void DrawText( const char * text, const CVec2 & uiCoords, int size, const Render::Color & color,    ETextHAlign hAlign = HA_Center, ETextVAlign vAlign = VA_Center );
    void DrawText( const wchar_t * text, const CVec2 & uiCoords, int size, const Render::Color & color, ETextHAlign hAlign = HA_Center, ETextVAlign vAlign = VA_Center );
    void DrawText3D( const char * text, const CVec3 & pos, int size, const Render::Color & color );
    void DrawText3D( const wchar_t * text, const CVec3 & pos, int size, const Render::Color & color );

    _interface IDebugTextProcessor
    {
      virtual void On2DText( const wstring & text, const CVec2 & uiCoords, int size, const Render::Color & color, ETextHAlign hAlign, ETextVAlign vAlign ) = 0;
      virtual void On3DText( const wstring & text, const CVec3 & pos, int size, const Render::Color & color, const SHMatrix & projection, ETextHAlign hAlign, ETextVAlign vAlign ) = 0;
    };

    void ImplementationSet3DProjection( const SHMatrix & projectionMatrix );
    void ImplementationProcessDebugText( IDebugTextProcessor * processor );

		void Release();
	};

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class DebugRender : public IDebugRender
  {
    virtual void DrawLine2D( int x1, int y1, int x2, int y2, Render::Color color1, Render::Color color2 )
    {
      DebugRenderer::DrawLine2D(x1, y1, x2, y2, color1, color2);
    }

    virtual void DrawLine3D( const CVec3& p1, const CVec3& p2, Render::Color color1, Render::Color color2, bool zTest )
    {
      DebugRenderer::DrawLine3D( p1, p2, color1, color2, zTest );
    }

    virtual void DrawPoint2D( const int x, const int y, float size, Render::Color color )
    {
      DebugRenderer::DrawPoint2D( x, y, size, color);
    }

    virtual void DrawPoint3D( const CVec3& p, float size, Render::Color color, bool zTest )
    {
      DebugRenderer::DrawPoint3D( p, size, color, zTest);
    }

    virtual void DrawAABB( const struct AABB &aabb, Render::Color color, bool zTest )
    {
      DebugRenderer::DrawAABB( aabb, color, zTest);
    }

    virtual void DrawBox3D( const Placement &pl, float size, Render::Color color, bool zTest )
    {
      DebugRenderer::DrawBox3D(pl, size, color, zTest);
    }

    virtual void DrawBox3D( const Matrix43 &mtx, float size, Render::Color color, bool zTest )
    {
      DebugRenderer::DrawBox3D( mtx, size, color, zTest );
    }

    virtual void DrawCross3D( const Matrix43 &mtx, float sizePos, float sizeNeg, const CrossColorTable &colors, bool zTest )
    {
      DebugRenderer::DrawCross3D( mtx, sizePos, sizeNeg, colors, zTest );
    }

    virtual void DrawCross3D( const Matrix43 &mtx, float sizePos, float sizeNeg, Render::Color color, bool zTest )
    {
     DebugRenderer::DrawCross3D( mtx, sizePos, sizeNeg, color, zTest );
    }

    virtual void DrawCircle3D( CVec3 const &center, float radius, int numSegments, Render::Color color, bool zTest )
    {
      DebugRenderer::DrawCircle3D( center, radius, numSegments, color, zTest );
    }

    virtual void DrawTriangle3D( const CVec3 &p1, const CVec3 &p2, const CVec3 &p3, Render::Color color, bool zTest) 
    {
      DebugRenderer::DrawTriangle3D( p1, p2, p3, color, zTest );
    }

    virtual void DrawCustomMesh(const void *points, int stride, const int *indices, int indCount, Render::Color color, bool zTest)
    {
      DebugRenderer::DrawCustomMesh( points, stride, indices, indCount, color, zTest );
    }

    virtual void DrawText( const char * text, const CVec2 & uiCoords, int size, const Render::Color & color, DebugRenderer::ETextHAlign hAlign, DebugRenderer::ETextVAlign vAlign) 
    {
      DebugRenderer::DrawText( text, uiCoords, size, color, hAlign, vAlign );
    }

    virtual void DrawText( const wchar_t * text, const CVec2 & uiCoords, int size, const Render::Color & color, DebugRenderer::ETextHAlign hAlign, DebugRenderer::ETextVAlign vAlign) 
    {
      DebugRenderer::DrawText( text, uiCoords, size, color, hAlign, vAlign );
    }

    virtual void DrawText3D( const char * text, const CVec3 & pos, int size, const Render::Color & color )
    {
      DebugRenderer::DrawText3D( text, pos, size, color );
    }

    virtual void DrawText3D( const wchar_t * text, const CVec3 & pos, int size, const Render::Color & color ) 
    {
      DebugRenderer::DrawText3D( text, pos, size, color );
    }

    virtual void PushBuffer( DebugRenderBuffer buf ) 
    {
      DebugRenderer::PushBuffer(buf);
    }

    virtual void PopBuffer() 
    {
      DebugRenderer::PopBuffer();
    }

    virtual void ClearBuffer( DebugRenderBuffer buf ) 
    {
      DebugRenderer::ClearBuffer(buf);
    }

  };

  // Wireframe groups
  enum WireframeGroup
  {
    WIREGROUP_NA       = 0,
    WIREGROUP_OPAQUE   = 1,
    WIREGROUP_TERRAIN0 = 2,
    WIREGROUP_TERRAIN1 = 3,
    WIREGROUP_TRANSP   = 4,
    WIREGROUP_ROADS    = 5,
  };

  void WireframeEnable(bool enable, WireframeGroup groupIndex);

  void LogMarker(const char *_text);
  void RenderSequenceMarker(const char *_text);
  inline void RenderSequenceMarker(NDb::MaterialPriority _priority) { RenderSequenceMarker( EnumToString(_priority) ); }
}; 