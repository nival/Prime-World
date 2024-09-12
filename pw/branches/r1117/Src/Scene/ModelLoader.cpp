#include "stdafx.h"
#include "ModelLoader.h"

#include "AIGeometry.h"
#include "../Render/DBRender.h"
#include "../Render/DBRenderResources.h"

#include "../Render/StaticMesh.h"
#include "../Render/Color.h"

using namespace Render;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NScene
{

struct SimpleVertexStride
{
	float X, Y, Z;
	Color color;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
bool MakeModelFromAIGeometryInstances( Render::StaticModel *pRes,	const AIGeometry *pGeom, const vector<SGeometryInstanceDef> &instances, bool isPreprocessedGeom, bool alphaTest )
{
	Render::Mesh* mesh = new Render::Mesh;
	pRes->mesh = mesh;
	Render::SubMesh* subMesh = new Render::SubMesh;
	NI_STATIC_ASSERT( sizeof(SimpleVertexStride) == 16, stride_wrong_size );

	const int instancePoints = pGeom->points.size();
	const int totalPoints = pGeom->points.size() * instances.size();
	const int totalTris = pGeom->mesh.size() * instances.size();

	const int vbsize = sizeof(SimpleVertexStride) * totalPoints;

	IVertexBuffer* vertexBuffer = RenderResourceManager::CreateVertexBuffer( vbsize, RENDER_POOL_MANAGED );
	SimpleVertexStride* vbLockData =reinterpret_cast<SimpleVertexStride*> ( vertexBuffer->Lock( 0, vbsize, LOCK_DEFAULT ) );

	int ivertex = 0;
	for ( int inst = 0; inst < instances.size(); ++inst )
	{
		const SGeometryInstanceDef &def = instances[inst];
		for ( int i = 0; i < pGeom->points.size(); ++i )
		{
			vbLockData[ivertex].X = pGeom->points[i].x + def.pos.x;
			vbLockData[ivertex].Y = pGeom->points[i].y + def.pos.y;
			vbLockData[ivertex].Z = pGeom->points[i].z + def.pos.z;
			vbLockData[ivertex].color = def.color;
			++ivertex;
		}
	}
	vertexBuffer->Unlock();

	const int ibsize = 3 * sizeof(unsigned __int32) * totalTris;
	IIndexBuffer* indexBuffer = RenderResourceManager::CreateIndexBuffer( ibsize, RENDER_POOL_MANAGED );
	unsigned __int32* ibLockData = reinterpret_cast<unsigned __int32*>(indexBuffer->Lock( 0, ibsize, LOCK_DEFAULT ));

	int iindex = 0;
	for ( int inst = 0; inst < instances.size(); ++inst )
	{
		for ( int i = 0; i < pGeom->mesh.size(); ++i )
		{
			STriangle t = pGeom->mesh[ i ];

			int i1, i2, i3;
			if ( isPreprocessedGeom )
			{
				if ( t.i1 & 0x8000 )
				{
					i1 = pGeom->edges[ t.i1 & 0x7fff ].wFinish; 
					i2 = pGeom->edges[ t.i1 & 0x7fff ].wStart;
				}
				else
				{
					i1 = pGeom->edges[ t.i1 & 0x7fff ].wStart; 
					i2 = pGeom->edges[ t.i1 & 0x7fff ].wFinish;
				}
				if ( t.i2 & 0x8000 )
					i3 = pGeom->edges[ t.i2 & 0x7fff ].wStart;
				else
					i3 = pGeom->edges[ t.i2 & 0x7fff ].wFinish;
			}
			else
			{
				i1 = t.i1; i2 = t.i2; i3 = t.i3;
			}

			ibLockData[iindex++] = i1 + instancePoints * inst;
			ibLockData[iindex++] = i2 + instancePoints * inst;
			ibLockData[iindex++] = i3 + instancePoints * inst;
		}
	}

	indexBuffer->Unlock();
	subMesh->SetIndexBuffer(indexBuffer);
	subMesh->AddVertexBuffer(vertexBuffer);
	Render::DipDescriptor dipDescr;
	VertexFormatDescriptor formatDescriptor;
	formatDescriptor.AddVertexElement( VertexElementDescriptor(0, 0,	VERTEXELEMENTTYPE_FLOAT3, VERETEXELEMENTUSAGE_POSITION, 0) );
	formatDescriptor.AddVertexElement( VertexElementDescriptor(0, 12, VERTEXELEMENTTYPE_D3DCOLOR, VERETEXELEMENTUSAGE_COLOR, 0) );
	dipDescr.AddVertexStreamDescriptor( VertexStreamDescriptor(0, 16) );
	dipDescr.pVertexFormatDeclaration = SmartRenderer::GetVertexFormatDeclaration(formatDescriptor);
	dipDescr.primitiveType = RENDERPRIMITIVE_TRIANGLELIST;
	dipDescr.baseVertexIndex = 0;
	dipDescr.startIndex = 0;
	dipDescr.numVertices = totalPoints;
	dipDescr.primitiveCount = totalTris;
	subMesh->SetDipDescriptor(dipDescr);
	mesh->AddSubMeshDeprecated(subMesh);


	// material
	Render::BaseMaterial* pMat = new Render::SimpleMaterial(
		Render::ShaderCompiler::CompileVertexShaderFromFile("../data/dummy_shader.hlsl")
		, Render::ShaderCompiler::CompilePixelShaderFromFile("../data/dummy_shader.hlsl")
		);

	pMat->GetRenderStates().blendState.blendIsEnabled = alphaTest;
	pMat->GetRenderStates().alphaState.alphaTestIsEnabled = false;
	if ( alphaTest )
	{
		pMat->GetRenderStates().blendState.sourceFactor = NDb::BLENDFACTOR_ONE;
		pMat->GetRenderStates().blendState.destinationFactor = NDb::BLENDFACTOR_ONE;
	}
	pMat->GetRenderStates().alphaState.alphaReferenceValue = 0;
	pMat->GetRenderStates().alphaState.stateCompareFunction = NDb::COMPAREFUNCTION_GREATER;
	pMat->GetRenderStates().depthState.depthTestIsEnabled = true;
	pMat->GetRenderStates().cullingState.cullingMode = NDb::CULLINGMODE_NONE; //CCW

	pRes->materials.push_back( pMat );
	pRes->mesh = mesh;

	return true; 
}
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MakeModelFromAIGeometryInstances( Render::StaticMesh *pRes,	const AIGeometry *pGeom, const vector<SGeometryInstanceDef> &instances, bool isPreprocessedGeom, bool alphaBlend )
{
	Render::MeshGeometry* geom = new Render::MeshGeometry;
	Render::Primitive* primitive = new Render::Primitive;
	Render::RenderResourceManager::PushPrimitiveToPoolDeprecated(primitive);
	NI_STATIC_ASSERT( sizeof(SimpleVertexStride) == 16, stride_wrong_size );
	
	const int instancePoints = pGeom->points.size();
	const int totalPoints = pGeom->points.size() * instances.size();
	const int totalTris = pGeom->mesh.size() * instances.size();
	const int vbsize = sizeof(SimpleVertexStride) * totalPoints;

	IVertexBuffer* vertexBuffer = RenderResourceManager::CreateVertexBuffer( vbsize, RENDER_POOL_MANAGED );
	SimpleVertexStride* vbLockData = reinterpret_cast<SimpleVertexStride*> ( vertexBuffer->Lock( 0, vbsize, LOCK_DEFAULT ) );

	int ivertex = 0;
	for ( int inst = 0; inst < instances.size(); ++inst )
	{
		const SGeometryInstanceDef &def = instances[inst];
		for ( int i = 0; i < pGeom->points.size(); ++i )
		{
			vbLockData[ivertex].X = pGeom->points[i].x + def.pos.x;
			vbLockData[ivertex].Y = pGeom->points[i].y + def.pos.y;
			vbLockData[ivertex].Z = pGeom->points[i].z + def.pos.z;
			vbLockData[ivertex].color = def.color;
			++ivertex;
		}
	}
	vertexBuffer->Unlock();

	const int ibsize = 3 * sizeof(unsigned __int32) * totalTris;
	IIndexBuffer* indexBuffer = RenderResourceManager::CreateIndexBuffer( ibsize, RENDER_POOL_MANAGED );
	unsigned __int32* ibLockData = reinterpret_cast<unsigned __int32*>(indexBuffer->Lock( 0, ibsize, LOCK_DEFAULT ));

	int iindex = 0;
	for ( int inst = 0; inst < instances.size(); ++inst )
	{
		for ( int i = 0; i < pGeom->mesh.size(); ++i )
		{
			STriangle t = pGeom->mesh[ i ];

			int i1, i2, i3;
			if ( isPreprocessedGeom )
			{
				if ( t.i1 & 0x8000 )
				{
					i1 = pGeom->edges[ t.i1 & 0x7fff ].wFinish; 
					i2 = pGeom->edges[ t.i1 & 0x7fff ].wStart;
				}
				else
				{
					i1 = pGeom->edges[ t.i1 & 0x7fff ].wStart; 
					i2 = pGeom->edges[ t.i1 & 0x7fff ].wFinish;
				}
				if ( t.i2 & 0x8000 )
					i3 = pGeom->edges[ t.i2 & 0x7fff ].wStart;
				else
					i3 = pGeom->edges[ t.i2 & 0x7fff ].wFinish;
			}
			else
			{
				i1 = t.i1; i2 = t.i2; i3 = t.i3;
			}

			ibLockData[iindex++] = i1 + instancePoints * inst;
			ibLockData[iindex++] = i2 + instancePoints * inst;
			ibLockData[iindex++] = i3 + instancePoints * inst;
		}
	}

	indexBuffer->Unlock();
	primitive->SetIndexBuffer(indexBuffer);
	primitive->AddVertexBuffer(vertexBuffer);
	Render::DipDescriptor dipDescr;
	VertexFormatDescriptor formatDescriptor;
	formatDescriptor.AddVertexElement( VertexElementDescriptor(0, 0,	VERTEXELEMENTTYPE_FLOAT3, VERETEXELEMENTUSAGE_POSITION, 0) );
	formatDescriptor.AddVertexElement( VertexElementDescriptor(0, 12, VERTEXELEMENTTYPE_D3DCOLOR, VERETEXELEMENTUSAGE_COLOR, 0) );
	dipDescr.vertexDescriptor = VertexStreamDescriptor(0, 16) ;
	dipDescr.pVertexFormatDeclaration = SmartRenderer::GetVertexFormatDeclaration(formatDescriptor);
	dipDescr.primitiveType = RENDERPRIMITIVE_TRIANGLELIST;
	dipDescr.baseVertexIndex = 0;
	dipDescr.startIndex = 0;
	dipDescr.numVertices = totalPoints;
	dipDescr.primitiveCount = totalTris;
	primitive->SetDipDescriptor(dipDescr);
	geom->primitives.push_back( primitive );

	NDb::Ptr<NDb::MaterialType> pDBMat = NDb::Get<NDb::MaterialType>( NDb::DBID( alphaBlend ? "AIGeomTranspMaterial.xdb" : "AIGeomSolidMaterial.xdb" ) );
	NI_VERIFY( IsValid(pDBMat), "Cannot load material for AIGeometry", return false ); 
	Render::Materials::IMaterial* pMat = Render::Materials::CreateMaterialInstance( pDBMat );
	NI_VERIFY( pMat, "Cannot init material for AIGeometry", return false ); 

	vector<Render::Materials::IMaterial*> materials;
	materials.push_back( pMat );

	Matrix43 m;
	pRes->Initialize( m, geom, materials );
	geom->primitives.resize(0);
	delete geom;

	return true; 
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
bool MakeModelFromAIGeometry( Render::StaticModel *pRes, const AIGeometry *pGeom, const Render::Color& color, bool isPreprocessedGeom )
{
	vector<SGeometryInstanceDef> defs;
	SGeometryInstanceDef def;
	def.pos = VNULL3;
	def.color = color; 
	defs.push_back( def );

	return MakeModelFromAIGeometryInstances( pRes, pGeom, defs, isPreprocessedGeom, color.A != 255 );
}
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MakeModelFromAIGeometry( Render::StaticMesh *pRes, const AIGeometry *pGeom, const Render::Color& color, bool isPreprocessedGeom )
{
	vector<SGeometryInstanceDef> defs;
	SGeometryInstanceDef def;
	def.pos = VNULL3;
	def.color = color; 
	defs.push_back( def );

	return MakeModelFromAIGeometryInstances( pRes, pGeom, defs, isPreprocessedGeom, color.A != 255 );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
