// Automatically generated file, don't change it manually!
#include "stdafx.h"
#include "../libdb/Checksum.h"
#include "../libdb/XmlSaver.h"
#include "../Scripts/lua.hpp"
#include "../Scripts/ScriptMacroses.h"
#include "System/StrUtils.h"

#include "DBTestTypes.h"
namespace
{
	char enumToStrBuffer[12];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_DBRESOURCE( JustTestType );
REGISTER_DBRESOURCE( JustTestType2 );
REGISTER_DBRESOURCE( JustTestType3 );
REGISTER_DBRESOURCE( LofComplexInheritable );
REGISTER_DBRESOURCE( LofHardInheritable );
REGISTER_DBRESOURCE( LofSimpleInheritable );
REGISTER_DBRESOURCE( LofSimpleChild );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace NDb
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const FlagEnum value )
{
	switch( value )
	{
		case FLAGENUM_ZERO:
			return "Zero";
		case FLAGENUM_ONE:
			return "One";
		case FLAGENUM_TWO:
			return "Two";
		case FLAGENUM_FOUR:
			return "Four";
		case FLAGENUM_FIVE:
			return "Five";
		case FLAGENUM_EIGHT:
			return "Eight";
		case FLAGENUM_FIFTEEN:
			return "Fifteen";
		case FLAGENUM_SIXTEEN:
			return "Sixteen";
	};

	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const FlagEnum StringToEnum_FlagEnum( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (FlagEnum)(NStr::ToInt( value ));
	if ( strcmp( value, "Zero" ) == 0 || strcmp( value, "FLAGENUM_ZERO" ) == 0 )
		return FLAGENUM_ZERO;
	if ( strcmp( value, "One" ) == 0 || strcmp( value, "FLAGENUM_ONE" ) == 0 )
		return FLAGENUM_ONE;
	if ( strcmp( value, "Two" ) == 0 || strcmp( value, "FLAGENUM_TWO" ) == 0 )
		return FLAGENUM_TWO;
	if ( strcmp( value, "Four" ) == 0 || strcmp( value, "FLAGENUM_FOUR" ) == 0 )
		return FLAGENUM_FOUR;
	if ( strcmp( value, "Five" ) == 0 || strcmp( value, "FLAGENUM_FIVE" ) == 0 )
		return FLAGENUM_FIVE;
	if ( strcmp( value, "Eight" ) == 0 || strcmp( value, "FLAGENUM_EIGHT" ) == 0 )
		return FLAGENUM_EIGHT;
	if ( strcmp( value, "Fifteen" ) == 0 || strcmp( value, "FLAGENUM_FIFTEEN" ) == 0 )
		return FLAGENUM_FIFTEEN;
	if ( strcmp( value, "Sixteen" ) == 0 || strcmp( value, "FLAGENUM_SIXTEEN" ) == 0 )
		return FLAGENUM_SIXTEEN;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum FlagEnum", value ) );
	return FLAGENUM_ZERO;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const SimpleEnum value )
{
	switch( value )
	{
		case SIMPLEENUM_ZERO:
			return "Zero";
		case SIMPLEENUM_ONE:
			return "One";
		case SIMPLEENUM_TWO:
			return "Two";
		case SIMPLEENUM_FOUR:
			return "Four";
		case SIMPLEENUM_FIVE:
			return "Five";
		case SIMPLEENUM_EIGHT:
			return "Eight";
		case SIMPLEENUM_FIFTEEN:
			return "Fifteen";
		case SIMPLEENUM_SIXTEEN:
			return "Sixteen";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum SimpleEnum", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const SimpleEnum StringToEnum_SimpleEnum( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (SimpleEnum)(NStr::ToInt( value ));
	if ( strcmp( value, "Zero" ) == 0 || strcmp( value, "SIMPLEENUM_ZERO" ) == 0 )
		return SIMPLEENUM_ZERO;
	if ( strcmp( value, "One" ) == 0 || strcmp( value, "SIMPLEENUM_ONE" ) == 0 )
		return SIMPLEENUM_ONE;
	if ( strcmp( value, "Two" ) == 0 || strcmp( value, "SIMPLEENUM_TWO" ) == 0 )
		return SIMPLEENUM_TWO;
	if ( strcmp( value, "Four" ) == 0 || strcmp( value, "SIMPLEENUM_FOUR" ) == 0 )
		return SIMPLEENUM_FOUR;
	if ( strcmp( value, "Five" ) == 0 || strcmp( value, "SIMPLEENUM_FIVE" ) == 0 )
		return SIMPLEENUM_FIVE;
	if ( strcmp( value, "Eight" ) == 0 || strcmp( value, "SIMPLEENUM_EIGHT" ) == 0 )
		return SIMPLEENUM_EIGHT;
	if ( strcmp( value, "Fifteen" ) == 0 || strcmp( value, "SIMPLEENUM_FIFTEEN" ) == 0 )
		return SIMPLEENUM_FIFTEEN;
	if ( strcmp( value, "Sixteen" ) == 0 || strcmp( value, "SIMPLEENUM_SIXTEEN" ) == 0 )
		return SIMPLEENUM_SIXTEEN;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum SimpleEnum", value ) );
	return SIMPLEENUM_ZERO;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
JustTestStruct::JustTestStruct() :
		_intValue( 0 )
	, _enumValue( SIMPLEENUM_ZERO )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int JustTestStruct::operator&( IBinSaver &saver )
{
	saver.Add( 2, &_intValue );
	saver.Add( 3, &_enumValue );
	saver.Add( 4, &childObject );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int JustTestStruct::operator&( IXmlSaver &saver )
{
	saver.Add( "_intValue", &_intValue );
	saver.Add( "_enumValue", &_enumValue );
	saver.Add( "childObject", &childObject );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ObjectLockItemT::ObjectLockItemT() :
		x( 0 )
	, y( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ObjectLockItemT::operator&( IBinSaver &saver )
{
	saver.Add( 2, &x );
	saver.Add( 3, &y );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ObjectLockItemT::operator&( IXmlSaver &saver )
{
	saver.Add( "x", &x );
	saver.Add( "y", &y );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ObjectLockMaskT::ObjectLockMaskT() :
		tileSize( 0.5f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ObjectLockMaskT::operator&( IBinSaver &saver )
{
	saver.Add( 2, &tileSize );
	saver.Add( 3, &mask );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ObjectLockMaskT::operator&( IXmlSaver &saver )
{
	saver.Add( "tileSize", &tileSize );
	saver.Add( "mask", &mask );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PseudoStruct::PseudoStruct() :
		x( 0 )
	, y( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PseudoStruct::operator&( IBinSaver &saver )
{
	saver.Add( 2, &x );
	saver.Add( 3, &y );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PseudoStruct::operator&( IXmlSaver &saver )
{
	saver.Add( "x", &x );
	saver.Add( "y", &y );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PseudoStruct::IsEqual( const PseudoStruct& _pseudoStruct ) const
{
	return x == _pseudoStruct.x
		&& y == _pseudoStruct.y;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SimpleTestProperty::SimpleTestProperty()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SimpleTestProperty::operator&( IBinSaver &saver )
{
	saver.Add( 2, &name );
	saver.Add( 3, &field );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SimpleTestProperty::operator&( IXmlSaver &saver )
{
	saver.Add( "name", &name );
	saver.Add( "field", &field );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
JustTestType::JustTestType() :
		simple( SIMPLEENUM_ZERO )
	, flags( FLAGENUM_ZERO )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int JustTestType::operator&( IBinSaver &saver )
{
	saver.Add( 2, &_ints );
	saver.Add( 3, &_vecs );
	saver.Add( 4, &_quats );
	saver.Add( 5, &simple );
	saver.Add( 6, &flags );
	saver.Add( 7, &v3 );
	saver.Add( 8, &quat );
	saver.Add( 9, &avec3 );
	saver.Add( 10, &aquat );
	saver.Add( 11, &srcFileName );
	saver.Add( 12, &text );
	saver.Add( 13, &file );
	saver.Add( 14, &nestedStruct );
	saver.Add( 15, &childObject );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int JustTestType::operator&( IXmlSaver &saver )
{
	bool inheritedStates = false;
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			JustTestType* parentPtr = (JustTestType*)__parent.GetPtr();
			Assign( *parentPtr );
			StateSerializeHelper< JustTestType > parentStateCopier( this, stateManager.states, &JustTestType::NewJustTestType );
			parentStateCopier.InheritStates( parentPtr, parentPtr->GetStatesManager()->states, saver );
			inheritedStates = true;
		}
	}

	SerializeSelf( saver );
	if ( !inheritedStates )
	{
		StateSerializeHelper< JustTestType > reader( this, stateManager.states, &JustTestType::NewJustTestType );
		saver.AddPolymorphicBase( "__states", &reader );
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void JustTestType::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "_ints", &_ints );
	saver.Add( "_vecs", &_vecs );
	saver.Add( "_quats", &_quats );
	saver.Add( "simple", &simple );
	saver.Add( "flags", &flags );
	saver.Add( "v3", &v3 );
	saver.Add( "quat", &quat );
	saver.Add( "avec3", &avec3 );
	saver.Add( "aquat", &aquat );
	saver.Add( "srcFileName", &srcFileName );
	saver.Add( "text", &text );
	saver.Add( "file", &file );
	saver.Add( "nestedStruct", &nestedStruct );
	saver.Add( "childObject", &childObject );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void JustTestType::Assign( const JustTestType& _justTestType )
{
	_ints = _justTestType._ints;
	_vecs = _justTestType._vecs;
	_quats = _justTestType._quats;
	simple = _justTestType.simple;
	flags = _justTestType.flags;
	v3 = _justTestType.v3;
	quat = _justTestType.quat;
	avec3 = _justTestType.avec3;
	aquat = _justTestType.aquat;
	srcFileName = _justTestType.srcFileName;
	text = _justTestType.text;
	file = _justTestType.file;
	nestedStruct._intValue = _justTestType.nestedStruct._intValue;
	nestedStruct._enumValue = _justTestType.nestedStruct._enumValue;
	nestedStruct.childObject = _justTestType.nestedStruct.childObject;
	childObject = _justTestType.childObject;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
JustTestType2::JustTestType2()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int JustTestType2::operator&( IBinSaver &saver )
{
	saver.Add( 1, (JustTestType*)this );
	saver.Add( 2, &intList );
	saver.Add( 3, &structList );
	saver.Add( 4, &ptrList );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int JustTestType2::operator&( IXmlSaver &saver )
{
	bool inheritedStates = false;
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			JustTestType2* parentPtr = (JustTestType2*)__parent.GetPtr();
			Assign( *parentPtr );
			StateSerializeHelper< JustTestType2 > parentStateCopier( this, stateManager.states, &JustTestType2::NewJustTestType2 );
			parentStateCopier.InheritStates( parentPtr, parentPtr->GetStatesManager()->states, saver );
			inheritedStates = true;
		}
	}

	SerializeSelf( saver );
	if ( !inheritedStates )
	{
		StateSerializeHelper< JustTestType2 > reader( this, stateManager.states, &JustTestType2::NewJustTestType2 );
		saver.AddPolymorphicBase( "__states", &reader );
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void JustTestType2::SerializeSelf( IXmlSaver &saver )
{
	JustTestType::SerializeSelf( saver );
	saver.Add( "intList", &intList );
	saver.Add( "structList", &structList );
	saver.Add( "ptrList", &ptrList );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void JustTestType2::Assign( const JustTestType2& _justTestType2 )
{
	intList = _justTestType2.intList;
	structList = _justTestType2.structList;
	ptrList = _justTestType2.ptrList;
	_ints = _justTestType2._ints;
	_vecs = _justTestType2._vecs;
	_quats = _justTestType2._quats;
	simple = _justTestType2.simple;
	flags = _justTestType2.flags;
	v3 = _justTestType2.v3;
	quat = _justTestType2.quat;
	avec3 = _justTestType2.avec3;
	aquat = _justTestType2.aquat;
	srcFileName = _justTestType2.srcFileName;
	text = _justTestType2.text;
	file = _justTestType2.file;
	nestedStruct._intValue = _justTestType2.nestedStruct._intValue;
	nestedStruct._enumValue = _justTestType2.nestedStruct._enumValue;
	nestedStruct.childObject = _justTestType2.nestedStruct.childObject;
	childObject = _justTestType2.childObject;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
JustTestType3::JustTestType3()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int JustTestType3::operator&( IBinSaver &saver )
{
	saver.Add( 2, &lockMask );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int JustTestType3::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			JustTestType3* parentPtr = (JustTestType3*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void JustTestType3::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "lockMask", &lockMask );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void JustTestType3::Assign( const JustTestType3& _justTestType3 )
{
	lockMask.tileSize = _justTestType3.lockMask.tileSize;
	lockMask.mask = _justTestType3.lockMask.mask;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LofComplexInheritable::LofComplexInheritable() :
		_int( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LofComplexInheritable::operator&( IBinSaver &saver )
{
	saver.Add( 2, &_int );
	saver.Add( 3, &_list );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LofComplexInheritable::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			LofComplexInheritable* parentPtr = (LofComplexInheritable*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LofComplexInheritable::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "_int", &_int );
	saver.Add( "_list", &_list );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LofComplexInheritable::Assign( const LofComplexInheritable& _lofComplexInheritable )
{
	_int = _lofComplexInheritable._int;
	_list = _lofComplexInheritable._list;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LofHardInheritable::LofHardInheritable() :
		_int( 0 )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LofHardInheritable::operator&( IBinSaver &saver )
{
	saver.Add( 2, &_int );
	saver.Add( 3, &_list );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LofHardInheritable::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			LofHardInheritable* parentPtr = (LofHardInheritable*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LofHardInheritable::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "_int", &_int );
	saver.Add( "_list", &_list );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LofHardInheritable::Assign( const LofHardInheritable& _lofHardInheritable )
{
	_int = _lofHardInheritable._int;
	_list = _lofHardInheritable._list;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LofSimpleInheritable::LofSimpleInheritable() :
		_bool( false )
	, _int( 0 )
	, _float( 0.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LofSimpleInheritable::operator&( IBinSaver &saver )
{
	saver.Add( 2, &_bool );
	saver.Add( 3, &_int );
	saver.Add( 4, &_float );
	saver.Add( 5, &_string );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LofSimpleInheritable::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			LofSimpleInheritable* parentPtr = (LofSimpleInheritable*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LofSimpleInheritable::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "_bool", &_bool );
	saver.Add( "_int", &_int );
	saver.Add( "_float", &_float );
	saver.Add( "_string", &_string );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LofSimpleInheritable::Assign( const LofSimpleInheritable& _lofSimpleInheritable )
{
	_bool = _lofSimpleInheritable._bool;
	_int = _lofSimpleInheritable._int;
	_float = _lofSimpleInheritable._float;
	_string = _lofSimpleInheritable._string;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LofSimpleChild::LofSimpleChild()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LofSimpleChild::operator&( IBinSaver &saver )
{
	saver.Add( 1, (LofSimpleInheritable*)this );
	saver.Add( 2, &twin );
	saver.Add( 3, &_data );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LofSimpleChild::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			LofSimpleChild* parentPtr = (LofSimpleChild*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LofSimpleChild::SerializeSelf( IXmlSaver &saver )
{
	LofSimpleInheritable::SerializeSelf( saver );
	saver.Add( "twin", &twin );
	saver.Add( "_data", &_data );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LofSimpleChild::Assign( const LofSimpleChild& _lofSimpleChild )
{
	twin = _lofSimpleChild.twin;
	_data.x = _lofSimpleChild._data.x;
	_data.y = _lofSimpleChild._data.y;
	_bool = _lofSimpleChild._bool;
	_int = _lofSimpleChild._int;
	_float = _lofSimpleChild._float;
	_string = _lofSimpleChild._string;
}
}; // namespace NDb
