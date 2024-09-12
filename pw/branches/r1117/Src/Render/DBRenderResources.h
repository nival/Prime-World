#pragma once
// Automatically generated file, don't change it manually!

#include "../libdb/Db.h"
#include "../libdb/Animated.h"
#include "../libdb/AnimatedAlgorithms.h"
#include "../Render/DBRender.h"

struct IXmlSaver;
// forward declarations for factories
namespace Render
{
	class Texture;
}; //namespace Render

namespace NDb
{
struct AnimGraphCreator;
struct Material;
struct Texture;

enum EAnGrMarkerOwner
{
	ANGRMARKEROWNER_ANGRM_NODE = 0,
	ANGRMARKEROWNER_ANGRM_TRANSACTION = 1,
};

const char *EnumToString( const EAnGrMarkerOwner value );
const EAnGrMarkerOwner StringToEnum_EAnGrMarkerOwner( const char* value );

template <>
struct KnownEnum< EAnGrMarkerOwner >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const EAnGrMarkerOwner value ) { return EnumToString( value ); }
	static const EAnGrMarkerOwner ToEnum( const char* value ) { return StringToEnum_EAnGrMarkerOwner( value ); }
	static const EAnGrMarkerOwner ToEnum( const string& value ) { return StringToEnum_EAnGrMarkerOwner( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

enum EAnGrNodeType
{
	ANGRNODETYPE_NORMAL = 0,
	ANGRNODETYPE_DISPATCHER = 1,
	ANGRNODETYPE_SUBNODE = 2,
};

const char *EnumToString( const EAnGrNodeType value );
const EAnGrNodeType StringToEnum_EAnGrNodeType( const char* value );

template <>
struct KnownEnum< EAnGrNodeType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const EAnGrNodeType value ) { return EnumToString( value ); }
	static const EAnGrNodeType ToEnum( const char* value ) { return StringToEnum_EAnGrNodeType( value ); }
	static const EAnGrNodeType ToEnum( const string& value ) { return StringToEnum_EAnGrNodeType( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum EAnGrTransactionKind
{
	ANGRTRANSACTIONKIND_UNIFORM = 0,
	ANGRTRANSACTIONKIND_PARABOLIC3 = 1,
	ANGRTRANSACTIONKIND_RECPARABOLIC3 = 2,
	ANGRTRANSACTIONKIND_SINE = 3,
	ANGRTRANSACTIONKIND_RECSINE = 4,
	ANGRTRANSACTIONKIND_SPLINE = 5,
	ANGRTRANSACTIONKIND_RECSPLINE = 6,
};

const char *EnumToString( const EAnGrTransactionKind value );
const EAnGrTransactionKind StringToEnum_EAnGrTransactionKind( const char* value );

template <>
struct KnownEnum< EAnGrTransactionKind >
{
	enum { isKnown = 1 };
	enum { sizeOf = 7 };
	static const char *ToString( const EAnGrTransactionKind value ) { return EnumToString( value ); }
	static const EAnGrTransactionKind ToEnum( const char* value ) { return StringToEnum_EAnGrTransactionKind( value ); }
	static const EAnGrTransactionKind ToEnum( const string& value ) { return StringToEnum_EAnGrTransactionKind( value.c_str() ); }
	static const int SizeOf() { return 7; }
};

enum EAnGrTransactionUpdate
{
	ANGRTRANSACTIONUPDATE_POSETOPOSE = 0,
	ANGRTRANSACTIONUPDATE_ANIMTOPOSE = 1,
	ANGRTRANSACTIONUPDATE_POSETOANIM = 2,
	ANGRTRANSACTIONUPDATE_ANIMTOANIM = 3,
};

const char *EnumToString( const EAnGrTransactionUpdate value );
const EAnGrTransactionUpdate StringToEnum_EAnGrTransactionUpdate( const char* value );

template <>
struct KnownEnum< EAnGrTransactionUpdate >
{
	enum { isKnown = 1 };
	enum { sizeOf = 4 };
	static const char *ToString( const EAnGrTransactionUpdate value ) { return EnumToString( value ); }
	static const EAnGrTransactionUpdate ToEnum( const char* value ) { return StringToEnum_EAnGrTransactionUpdate( value ); }
	static const EAnGrTransactionUpdate ToEnum( const string& value ) { return StringToEnum_EAnGrTransactionUpdate( value.c_str() ); }
	static const int SizeOf() { return 4; }
};

enum EGeometryUsageFlags
{
	GEOMETRYUSAGEFLAGS_NONE = 0,
	GEOMETRYUSAGEFLAGS_LIGHTING = 1,
	GEOMETRYUSAGEFLAGS_NORMALMAPPING = 2,
	GEOMETRYUSAGEFLAGS_VERTEXCOLORS = 4,
};

const char *EnumToString( const EGeometryUsageFlags value );
const EGeometryUsageFlags StringToEnum_EGeometryUsageFlags( const char* value );

template <>
struct KnownEnum< EGeometryUsageFlags >
{
	enum { isKnown = 1 };
	enum { sizeOf = 4 };
	static const char *ToString( const EGeometryUsageFlags value ) { return EnumToString( value ); }
	static const EGeometryUsageFlags ToEnum( const char* value ) { return StringToEnum_EGeometryUsageFlags( value ); }
	static const EGeometryUsageFlags ToEnum( const string& value ) { return StringToEnum_EGeometryUsageFlags( value.c_str() ); }
	static const int SizeOf() { return 4; }
};

enum MipLevel
{
	MIPLEVEL_AUTOGENERATE = 0,
	MIPLEVEL_NOMIPS = 1,
};

const char *EnumToString( const MipLevel value );
const MipLevel StringToEnum_MipLevel( const char* value );

template <>
struct KnownEnum< MipLevel >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const MipLevel value ) { return EnumToString( value ); }
	static const MipLevel ToEnum( const char* value ) { return StringToEnum_MipLevel( value ); }
	static const MipLevel ToEnum( const string& value ) { return StringToEnum_MipLevel( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

enum TextureType
{
	TEXTURETYPE_COLOR = 0,
	TEXTURETYPE_NORMAL = 1,
};

const char *EnumToString( const TextureType value );
const TextureType StringToEnum_TextureType( const char* value );

template <>
struct KnownEnum< TextureType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 2 };
	static const char *ToString( const TextureType value ) { return EnumToString( value ); }
	static const TextureType ToEnum( const char* value ) { return StringToEnum_TextureType( value ); }
	static const TextureType ToEnum( const string& value ) { return StringToEnum_TextureType( value.c_str() ); }
	static const int SizeOf() { return 2; }
};

struct AABB
{
public:
	float minX;
	float maxX;
	float minY;
	float maxY;
	float minZ;
	float maxZ;

	AABB();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct AnGrExternalParameter
{
public:
	string paramName;
	float defaultValue;

	AnGrExternalParameter();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct AnGrExternalParameterCoeff
{
public:
	string name;
	float value;

	AnGrExternalParameterCoeff();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct AnGrFormula
{
public:
	float value;
	vector< AnGrExternalParameterCoeff > coeffs;

	AnGrFormula();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct AnGrMarker
{
public:
	string name;
	float virtPar;

	AnGrMarker();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct AnGrFlTransaction
{
public:
	EAnGrTransactionUpdate blending;
	EAnGrTransactionKind kind;
	AnGrFormula parA;
	AnGrFormula parB;
	AnGrFormula fromMin;
	AnGrFormula fromMax;
	AnGrFormula toParam;
	float duration;
	vector< AnGrMarker > markers;

	AnGrFlTransaction();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct AnGrFlMultiTransaction
{
public:
	enum { typeId = 0x14591F84 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AnGrFlMultiTransaction::typeId; }
	string targetNode;
	float probability;
	AnGrFlTransaction parameters;

	AnGrFlMultiTransaction();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct AnGrMacronode
{
public:
	string nodeName;
	EAnGrNodeType nodeType;
	string nextNode;
	float surfSpeedX;
	float surfSpeedY;
	string sequenceName;
	AnGrFormula startPar;
	AnGrFormula stopPar;
	AnGrFormula speed;
	vector< AnGrFlMultiTransaction > simpleTransactions;
	int posX;
	int posY;
	vector< AnGrMarker > markers;

	AnGrMacronode();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct AnimKey
{
public:
	float time;
	string name;

	AnimKey();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct Animation
{
public:
	string name;
	vector< AnimKey > animkeys;
	string srcFileName;
	string animationFileName;

	Animation();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct FaceFX
{
public:
	string srcFileName;
	string fxaFileName;

	FaceFX();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct FlatSplineControlPointDesc
{
public:
	CVec2 location;
	float width;

	FlatSplineControlPointDesc();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct FlatSplineDesc
{
public:
	vector< FlatSplineControlPointDesc > points;
	bool HasWidth;
	bool IsCircle;
	bool AbsolutePosition;

	FlatSplineDesc();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct FullScreenFXParams
{
public:
	CVec3 InMin;
	CVec3 InMax;
	CVec3 OutMin;
	CVec3 OutMax;
	CVec3 Gamma;
	Render::HDRColor Color;
	float ColorCastCoef;
	float SharpPixelSize;
	float SharpCoef;

	FullScreenFXParams();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct SkinPartBase
{
public:
	string srcFileName;
	string geometryFileName;
	string skinPartName;
	vector< Ptr< Material > > materialsReferences;

	SkinPartBase();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct Spline3DControlPointDesc
{
public:
	CVec3 rotation;
	CVec3 position;
	float tension;

	Spline3DControlPointDesc();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct TextureSize
{
public:
	int width;
	int height;

	TextureSize();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct TgaTextureName
{
public:
	enum { typeId = 0xC867EC41 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)TgaTextureName::typeId; }
	string name;

	TgaTextureName();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct UVPair
{
public:
	CVec2 uvTopLeft;
	CVec2 uvBottomRight;

	UVPair();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct AnimGraphCreator : public DbResource
{
	DBRESOURCE_METHODS( AnimGraphCreator );
public:
	enum { typeId = 0x145573F8 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AnimGraphCreator::typeId; }
	string defaultNode;
	vector< AnGrMacronode > macroNodes;

	AnimGraphCreator();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AnimGraphCreator& operator = ( const AnimGraphCreator &_animGraphCreator ) { Assign( _animGraphCreator ); return *this; }
	AnimGraphCreator( const AnimGraphCreator &_animGraphCreator ) { Assign( _animGraphCreator ); }
	virtual void Assign( const AnimGraphCreator &_animGraphCreator );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AnimGraphCreator * pOther = dynamic_cast< const AnimGraphCreator * > ( _pResource );
		if ( pOther ) AnimGraphCreator::Assign( *pOther );
	}
};

struct OmniLight : public DbResource
{
	DBRESOURCE_METHODS( OmniLight );
public:
	Render::HDRColor diffuseColor;
	Render::HDRColor specularColor;
	float radius;

	OmniLight();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	OmniLight& operator = ( const OmniLight &_omniLight ) { Assign( _omniLight ); return *this; }
	OmniLight( const OmniLight &_omniLight ) { Assign( _omniLight ); }
	virtual void Assign( const OmniLight &_omniLight );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const OmniLight * pOther = dynamic_cast< const OmniLight * > ( _pResource );
		if ( pOther ) OmniLight::Assign( *pOther );
	}
};

struct PaintPackedMasks : public DbResource
{
	DBRESOURCE_METHODS( PaintPackedMasks );
public:
	enum { typeId = 0xC867EC40 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)PaintPackedMasks::typeId; }
	vector< Ptr< Texture > > packedMasks;

	PaintPackedMasks();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	PaintPackedMasks& operator = ( const PaintPackedMasks &_paintPackedMasks ) { Assign( _paintPackedMasks ); return *this; }
	PaintPackedMasks( const PaintPackedMasks &_paintPackedMasks ) { Assign( _paintPackedMasks ); }
	virtual void Assign( const PaintPackedMasks &_paintPackedMasks );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const PaintPackedMasks * pOther = dynamic_cast< const PaintPackedMasks * > ( _pResource );
		if ( pOther ) PaintPackedMasks::Assign( *pOther );
	}
};

struct ParticleFX : public DbResource
{
	DBRESOURCE_METHODS( ParticleFX );
public:
	string srcFileName;
	string fxFileName;

	ParticleFX();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ParticleFX& operator = ( const ParticleFX &_particleFX ) { Assign( _particleFX ); return *this; }
	ParticleFX( const ParticleFX &_particleFX ) { Assign( _particleFX ); }
	virtual void Assign( const ParticleFX &_particleFX );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ParticleFX * pOther = dynamic_cast< const ParticleFX * > ( _pResource );
		if ( pOther ) ParticleFX::Assign( *pOther );
	}
};

struct Skeleton : public DbResource
{
	DBRESOURCE_METHODS( Skeleton );
public:
	string srcFileName;
	string skeletonFileName;
	vector< SkinPartBase > skins;
	vector< Animation > animations;
	Ptr< AnimGraphCreator > animGraph;
	Ptr< AnimGraphCreator > additionalGraph;
	vector< FaceFX > faceFXAnims;

	Skeleton();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	Skeleton& operator = ( const Skeleton &_skeleton ) { Assign( _skeleton ); return *this; }
	Skeleton( const Skeleton &_skeleton ) { Assign( _skeleton ); }
	virtual void Assign( const Skeleton &_skeleton );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const Skeleton * pOther = dynamic_cast< const Skeleton * > ( _pResource );
		if ( pOther ) Skeleton::Assign( *pOther );
	}
};

struct StaticMesh : public DbResource
{
	DBRESOURCE_METHODS( StaticMesh );
public:
	enum { typeId = 0x9E5573C0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)StaticMesh::typeId; }
	string srcFileName;
	string geometryFileName;
	vector< Ptr< Material > > materialsReferences;
	AABB aabb;

	StaticMesh();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	StaticMesh& operator = ( const StaticMesh &_staticMesh ) { Assign( _staticMesh ); return *this; }
	StaticMesh( const StaticMesh &_staticMesh ) { Assign( _staticMesh ); }
	virtual void Assign( const StaticMesh &_staticMesh );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const StaticMesh * pOther = dynamic_cast< const StaticMesh * > ( _pResource );
		if ( pOther ) StaticMesh::Assign( *pOther );
	}
};

struct Texture : public TextureBase
{
	DBRESOURCE_METHODS( Texture );
public:
	string srcFileName;
	string textureFileName;

	Texture();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	Texture& operator = ( const Texture &_texture ) { Assign( _texture ); return *this; }
	Texture( const Texture &_texture ) { Assign( _texture ); }
	virtual void Assign( const Texture &_texture );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const Texture * pOther = dynamic_cast< const Texture * > ( _pResource );
		if ( pOther ) Texture::Assign( *pOther );
	}

#ifndef VISUAL_CUTTED
	virtual CObj<Render::Texture> Load() const;
	virtual CObj<Render::Texture> LoadInPool( bool canBeVisualDegrade, void * texturePoolId ) const;
#endif // #ifndef VISUAL_CUTTED
};

}; // namespace NDb
