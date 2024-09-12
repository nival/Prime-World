#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Render
{
	class StaticModel;
	class StaticMesh;
	class Color;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NScene
{
	class AIGeometry;
	struct SGeometryInstanceDef;

	//bool MakeModelFromAIGeometry( Render::StaticModel *pRes, const AIGeometry *pGeom, const Render::Color& color, bool isPreprocessedGeom = true );
	//bool MakeModelFromAIGeometryInstances( Render::StaticModel *pRes,	const AIGeometry *pGeom, const vector<SGeometryInstanceDef> &instances, bool isPreprocessedGeom, bool alphaTest );


	bool MakeModelFromAIGeometry( Render::StaticMesh *pRes, const AIGeometry *pGeom, const Render::Color& color, bool isPreprocessedGeom = true );
	bool MakeModelFromAIGeometryInstances( Render::StaticMesh *pRes,	const AIGeometry *pGeom, const vector<SGeometryInstanceDef> &instances, bool isPreprocessedGeom, bool alphaBlend );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
