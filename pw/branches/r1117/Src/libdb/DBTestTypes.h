#pragma once
// Automatically generated file, don't change it manually!

#include "../libdb/Db.h"
#include "../libdb/Animated.h"
#include "../libdb/AnimatedAlgorithms.h"

struct IXmlSaver;

namespace NDb
{
struct JustTestType;
struct LofSimpleInheritable;

enum FlagEnum
{
	FLAGENUM_ZERO = 0,
	FLAGENUM_ONE = 1,
	FLAGENUM_TWO = 2,
	FLAGENUM_FOUR = 4,
	FLAGENUM_FIVE = 5,
	FLAGENUM_EIGHT = 8,
	FLAGENUM_FIFTEEN = 15,
	FLAGENUM_SIXTEEN = 16,
};

const char *EnumToString( const FlagEnum value );
const FlagEnum StringToEnum_FlagEnum( const char* value );

template <>
struct KnownEnum< FlagEnum >
{
	enum { isKnown = 1 };
	enum { sizeOf = 8 };
	static const char *ToString( const FlagEnum value ) { return EnumToString( value ); }
	static const FlagEnum ToEnum( const char* value ) { return StringToEnum_FlagEnum( value ); }
	static const FlagEnum ToEnum( const string& value ) { return StringToEnum_FlagEnum( value.c_str() ); }
	static const int SizeOf() { return 8; }
};

enum SimpleEnum
{
	SIMPLEENUM_ZERO = 0,
	SIMPLEENUM_ONE = 1,
	SIMPLEENUM_TWO = 2,
	SIMPLEENUM_FOUR = 4,
	SIMPLEENUM_FIVE = 5,
	SIMPLEENUM_EIGHT = 8,
	SIMPLEENUM_FIFTEEN = 15,
	SIMPLEENUM_SIXTEEN = 16,
};

const char *EnumToString( const SimpleEnum value );
const SimpleEnum StringToEnum_SimpleEnum( const char* value );

template <>
struct KnownEnum< SimpleEnum >
{
	enum { isKnown = 1 };
	enum { sizeOf = 8 };
	static const char *ToString( const SimpleEnum value ) { return EnumToString( value ); }
	static const SimpleEnum ToEnum( const char* value ) { return StringToEnum_SimpleEnum( value ); }
	static const SimpleEnum ToEnum( const string& value ) { return StringToEnum_SimpleEnum( value.c_str() ); }
	static const int SizeOf() { return 8; }
};

struct JustTestStruct
{
public:
	int _intValue;
	SimpleEnum _enumValue;
	Ptr< JustTestType > childObject;

	JustTestStruct();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct ObjectLockItemT
{
public:
	int x;
	int y;

	ObjectLockItemT();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct ObjectLockMaskT
{
public:
	float tileSize;
	vector< ObjectLockItemT > mask;

	ObjectLockMaskT();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct PseudoStruct
{
public:
	int x;
	int y;

	PseudoStruct();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	bool operator==( const PseudoStruct &_pseudoStruct ) const { return IsEqual( _pseudoStruct ); }
	bool operator!=( const PseudoStruct &_pseudoStruct ) const { return !IsEqual( _pseudoStruct ); }
	bool IsEqual ( const PseudoStruct &_pseudoStruct ) const;
};

struct SimpleTestProperty
{
public:
	string name;
	string field;

	SimpleTestProperty();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct JustTestType : public DbResource
{
	DBRESOURCE_METHODS( JustTestType );
protected:
	mutable DBResourceStateManager stateManager;
	virtual DBResourceStateManager* GetStatesManager() const { return &stateManager; }
public:
	Animated<int, NDb::AnimatedAlgorithms::Linear> _ints;
	Animated<CVec3, NDb::AnimatedAlgorithms::Linear> _vecs;
	Animated<CQuat, NDb::AnimatedAlgorithms::Linear> _quats;
	SimpleEnum simple;
	FlagEnum flags;
	CVec3 v3;
	CQuat quat;
	Animated<CVec3, NDb::AnimatedAlgorithms::Linear> avec3;
	Animated<CQuat, NDb::AnimatedAlgorithms::Linear> aquat;
	string srcFileName;
	CTextRef text;
	string file;
	JustTestStruct nestedStruct;
	Ptr< JustTestType > childObject;

	JustTestType();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	JustTestType& operator = ( const JustTestType &_justTestType ) { Assign( _justTestType ); return *this; }
	JustTestType( const JustTestType &_justTestType ) { Assign( _justTestType ); }
	virtual void Assign( const JustTestType &_justTestType );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const JustTestType * pOther = dynamic_cast< const JustTestType * > ( _pResource );
		if ( pOther ) JustTestType::Assign( *pOther );
	}
};

struct JustTestType2 : public JustTestType
{
	DBRESOURCE_METHODS( JustTestType2 );
public:
	vector< int > intList;
	vector< SimpleTestProperty > structList;
	vector< Ptr< JustTestType > > ptrList;

	JustTestType2();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	JustTestType2& operator = ( const JustTestType2 &_justTestType2 ) { Assign( _justTestType2 ); return *this; }
	JustTestType2( const JustTestType2 &_justTestType2 ) { Assign( _justTestType2 ); }
	virtual void Assign( const JustTestType2 &_justTestType2 );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const JustTestType2 * pOther = dynamic_cast< const JustTestType2 * > ( _pResource );
		if ( pOther ) JustTestType2::Assign( *pOther );
	}
};

struct JustTestType3 : public DbResource
{
	DBRESOURCE_METHODS( JustTestType3 );
public:
	ObjectLockMaskT lockMask;

	JustTestType3();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	JustTestType3& operator = ( const JustTestType3 &_justTestType3 ) { Assign( _justTestType3 ); return *this; }
	JustTestType3( const JustTestType3 &_justTestType3 ) { Assign( _justTestType3 ); }
	virtual void Assign( const JustTestType3 &_justTestType3 );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const JustTestType3 * pOther = dynamic_cast< const JustTestType3 * > ( _pResource );
		if ( pOther ) JustTestType3::Assign( *pOther );
	}
};

struct LofComplexInheritable : public DbResource
{
	DBRESOURCE_METHODS( LofComplexInheritable );
public:
	int _int;
	vector< PseudoStruct > _list;

	LofComplexInheritable();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	LofComplexInheritable& operator = ( const LofComplexInheritable &_lofComplexInheritable ) { Assign( _lofComplexInheritable ); return *this; }
	LofComplexInheritable( const LofComplexInheritable &_lofComplexInheritable ) { Assign( _lofComplexInheritable ); }
	virtual void Assign( const LofComplexInheritable &_lofComplexInheritable );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const LofComplexInheritable * pOther = dynamic_cast< const LofComplexInheritable * > ( _pResource );
		if ( pOther ) LofComplexInheritable::Assign( *pOther );
	}
};

struct LofHardInheritable : public DbResource
{
	DBRESOURCE_METHODS( LofHardInheritable );
public:
	int _int;
	vector< int > _list;

	LofHardInheritable();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	LofHardInheritable& operator = ( const LofHardInheritable &_lofHardInheritable ) { Assign( _lofHardInheritable ); return *this; }
	LofHardInheritable( const LofHardInheritable &_lofHardInheritable ) { Assign( _lofHardInheritable ); }
	virtual void Assign( const LofHardInheritable &_lofHardInheritable );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const LofHardInheritable * pOther = dynamic_cast< const LofHardInheritable * > ( _pResource );
		if ( pOther ) LofHardInheritable::Assign( *pOther );
	}
};

struct LofSimpleInheritable : public DbResource
{
	DBRESOURCE_METHODS( LofSimpleInheritable );
public:
	bool _bool;
	int _int;
	float _float;
	string _string;

	LofSimpleInheritable();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	LofSimpleInheritable& operator = ( const LofSimpleInheritable &_lofSimpleInheritable ) { Assign( _lofSimpleInheritable ); return *this; }
	LofSimpleInheritable( const LofSimpleInheritable &_lofSimpleInheritable ) { Assign( _lofSimpleInheritable ); }
	virtual void Assign( const LofSimpleInheritable &_lofSimpleInheritable );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const LofSimpleInheritable * pOther = dynamic_cast< const LofSimpleInheritable * > ( _pResource );
		if ( pOther ) LofSimpleInheritable::Assign( *pOther );
	}
};

struct LofSimpleChild : public LofSimpleInheritable
{
	DBRESOURCE_METHODS( LofSimpleChild );
public:
	Ptr< LofSimpleInheritable > twin;
	PseudoStruct _data;

	LofSimpleChild();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	LofSimpleChild& operator = ( const LofSimpleChild &_lofSimpleChild ) { Assign( _lofSimpleChild ); return *this; }
	LofSimpleChild( const LofSimpleChild &_lofSimpleChild ) { Assign( _lofSimpleChild ); }
	virtual void Assign( const LofSimpleChild &_lofSimpleChild );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const LofSimpleChild * pOther = dynamic_cast< const LofSimpleChild * > ( _pResource );
		if ( pOther ) LofSimpleChild::Assign( *pOther );
	}
};

}; // namespace NDb
