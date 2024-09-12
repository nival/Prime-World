#include "stdafx.h"

#include "XmlSaver.h"
#include "XMLReader.h"
#include "dbid.h"
#include "System/FileSystem/FilePath.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NDb
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static SConvertCharsTable tblChars( ConvertChar_ToUpperAndSlash );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__forceinline static char ConvertChar( const char chr )
{
	return tblChars.LookUp( chr );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static unsigned int MakeHashKey( const string &fileName, const string &id )
{
	hash<string> hasher;
  return hasher( NStr::GetLower(fileName) ) ^ hasher( NStr::GetLower(id) );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FixFileNameForDBID( string* pFileName )
{
	if ( pFileName->size() < 4 )
		return;

	const char *fileName = pFileName->c_str();
	fileName += pFileName->size() - 4;
	if ( NStr::ICmp( fileName, ".xdb" ) != 0 )
		(*pFileName) += ".xdb";
  NFile::ConvertSlashes( pFileName, '\\', '/' );
	NStr::TrimBoth( *pFileName, '/' );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBID::DBID( const string &_fileName )
{
	const size_t divPos = _fileName.find( ':' );
	if ( divPos == string::npos )
		fileName = _fileName;
	else
	{
		fileName = _fileName.substr( 0, divPos );
		id = _fileName.substr( divPos + 1 );
	}

	FixFileNameForDBID( &fileName );
	hashKey = MakeHashKey( fileName, id );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBID::DBID( const string &_fileName, const string &_id ) : fileName( _fileName ), id( _id )
{
	FixFileNameForDBID( &fileName );
	hashKey = MakeHashKey( fileName, id );
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool DBID::CompareEqual( const string &_fileName, const string &_id ) const
{
	if ( id != _id )
		return false;

	const int size = fileName.size();
	if ( size != _fileName.size() )
		return false;
	
	// compare from the tail - where we can have more differences
	for ( int i = size - 1; i >= 0; --i )
	{
		if ( ConvertChar( fileName[i] ) != ConvertChar( _fileName[i] ) )
			return false;
	}
	
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool DBID::operator <( const DBID &dbid ) const
{
	const int size1 = fileName.size();
	const int size2 = dbid.fileName.size();
	const int size = Min( size1, size2 );
	//
	for ( int i = 0; i < size; ++i )
	{
		const char c1 = ConvertChar( fileName[i] );
		const char c2 = ConvertChar( dbid.fileName[i] );
		if ( c1 < c2 )
			return true;
		if ( c2 < c1 )
			return false;
	}

	if ( size1 != size2 )
		return size1 < size2;

	const int idSize = Min( id.size(), dbid.id.size() );
	for( int i = 0; i < idSize; ++i )
	{
		const char c1 = ConvertChar( id[i] );
		const char c2 = ConvertChar( dbid.id[i] );
		if ( c1 < c2 )
			return true;
		if ( c2 < c1 )
			return false;
	}

	return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBID::OnSerialize( IBinSaver &saver )
{
	if ( saver.IsReading() )
	{
		hashKey = MakeHashKey( fileName, id );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBID::operator&( IXmlSaver &saver )
{
	saver.Add( "href", &fileName );
	saver.Add( "id", &id );
	if ( saver.IsReading() )
	{
		hashKey = MakeHashKey( fileName, id );
	}
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} //namespace NDb

