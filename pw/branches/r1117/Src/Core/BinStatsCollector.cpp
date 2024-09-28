#include "stdafx.h"

#include "BinStatsCollector.h"
#include "PF_Core/WorldObject.h"
#include "System/Crc32Checksum.h"
#include "System/FileSystem/FileUtils.h"
#include "System/Stream.h"
#include "System/FileSystem/FileStream.h"
#include "System/MemoryStream.h"
#include "System/InlineProfiler.h"
#include "System/ChunklessSaver.h"
#include "System/Crc32ChecksumFast.h"
#include "System/FileSystem/TinyFileWriteStream.h"
#include "System/LogFileName.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace
{
namespace FileFormat
{
  enum InfoType
  {
    Step = NCore::BinStatsCollector::Step,
    Data = NCore::BinStatsCollector::Data,
    Object = NCore::BinStatsCollector::Object,
    StartChunk = NCore::BinStatsCollector::StartChunk,
    FinishChunk = NCore::BinStatsCollector::FinishChunk
  };

  struct StepRecord
  {
    int step;
    unsigned long crc;

    void Set( int _step, unsigned long _crc )
    {
      step = _step;
      crc = _crc;
    }
  };

  struct DataRecord
  {
    IBinSaver::chunk_id idChunk;
    int size;
    unsigned long crc;

    void Set( const IBinSaver::chunk_id _idChunk, int _size, unsigned long _crc )
    {
      idChunk = _idChunk;
      size = _size;
      crc = _crc;
    }
  };

  struct ObjectRecord
  {
    int typeId;
    int worldId;

    void Set( int _typeId, int _worldId )
    {
      typeId = _typeId;
      worldId = _worldId;
    }
  };

  struct StartChunkRecord
  {
    IBinSaver::chunk_id idChunk;
    int chunkType;

    void Set( const IBinSaver::chunk_id _idChunk, int _chunkType )
    {
      idChunk = _idChunk;
      chunkType = _chunkType;
    }
  };
}

const int INVALID_WORLD_ID = 0x80000000;
const int INVALID_TYPE_ID = INT_MAX;
const int NULL_WORLD_ID = -1;
const int NULL_TYPE_ID = -1;
 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* GetTypeName( int typeId )
{
  if ( typeId == NULL_TYPE_ID )
    return "None";
  else if ( typeId == INVALID_TYPE_ID )
    return "Invalid";

	static hash_map<int, string> typeNames;
	hash_map<int, string>::const_iterator pos = typeNames.find( typeId );
	if ( pos != typeNames.end() )
		return pos->second.c_str();

	CObj<CObjectBase> obj = NObjectFactory::MakeObject( typeId );
	
	const string typeName = NStr::StrFmt( "%s (0x%08X)", (IsValid( obj ) ? obj->GetObjectTypeName() : "Unknown" ),  typeId );
	
	return typeNames.insert( make_pair<int, string>( typeId, typeName ) ).first->second.c_str();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* GetChunkTypeName( int chunk )
{
  switch( chunk )
  {
  case IBinSaver::CHUNK_DATA:
    return "CHUNK_DATA";
  case IBinSaver::CHUNK_SERIALIZABLE_OBJECT:
    return "CHUNK_SERIALIZABLE_OBJECT";
  case IBinSaver::CHUNK_PTR:
    return "CHUNK_PTR";
  case IBinSaver::CHUNK_STRING:
    return "CHUNK_STRING";
  case IBinSaver::CHUNK_WSTRING:
    return "CHUNK_WSTRING";
  case IBinSaver::CHUNK_MEMORYSTREAM:
    return "CHUNK_MEMORYSTREAM";
  case IBinSaver::CHUNK_MEMORYSTREAM_DATA:
    return "CHUNK_MEMORYSTREAM_DATA";
  case IBinSaver::CHUNK_VECTOR:
    return "CHUNK_VECTOR";
  case IBinSaver::CHUNK_HASHMAP:
    return "CHUNK_HASHMAP";
  case IBinSaver::CHUNK_RING:
    return "CHUNK_RING";
  case IBinSaver::CHUNK_MAP:
    return "CHUNK_MAP";
  case IBinSaver::CHUNK_STATICARRAYY:
    return "CHUNK_STATICARRAYY";
  case IBinSaver::CHUNK_HASHSET:
    return "CHUNK_HASHSET";
  case IBinSaver::CHUNK_SET:
    return "CHUNK_SET";
  case IBinSaver::CHUNK_ARRAY2D:
    return "CHUNK_ARRAY2D";
  case IBinSaver::CHUNK_LIST:
    return "CHUNK_LIST";
  case IBinSaver::CHUNK_PAIR:
    return "CHUNK_PAIR";
  case IBinSaver::CHUNK_COBJECTBASE:
    return "CHUNK_COBJECTBASE";
  // TODO: ?
  case IBinSaver::CHUNK_FORCESTR:
    return "CHUNK_FORCESTR";
  case IBinSaver::CHUNK_FIXED_STRING:
    return "CHUNK_FIXED_STRING";
  case IBinSaver::CHUNK_FIXED_WSTRING:
    return "CHUNK_FIXED_WSTRING";
  default:
    return GetTypeName( chunk );
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* GetWorldObjectId( int worldId )
{
  static char buffer[4][16];
  
  //Правильней было бы, конечно, возвращать string или передавать буфер, 
  //но решил сделать так, для поддержания единообразия
  static int nextBuff = 0;
  const int curBuff = nextBuff;
  nextBuff = (nextBuff + 1) % ARRAY_SIZE(buffer);
  
  if ( worldId == NULL_WORLD_ID )
    return "None";
  else if ( worldId == INVALID_WORLD_ID )
    return "Invalid";
  else
  {
    sprintf_s( buffer[curBuff], "%05d", worldId );
    return buffer[curBuff];
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* GetIdent( int ident )
{
	switch( ident )
	{
	case 0:
		return "";
	case 1:
		return "  ";
	case 2:
		return "    ";
	case 3:
		return "      ";
	case 4:
		return "        ";
	case 5:
		return "          ";
	case 6:
		return "            ";
	case 7:
		return "              ";
	case 8:
		return "                ";
	case 9:
		return "                  ";
	case 10:
		return "                    ";
	default:
		return ident < 0 ? "" : "                     >";
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct File
{
  string fileName;
  char* data;
  int size;

	File() : data( 0 ), size( 0 ) { }

	void Load( const string& _fileName )
	{
		fileName = _fileName;
    CObj<FileStream> file = new FileStream( _fileName, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
    NI_VERIFY( file->IsOk(), NStr::StrFmt( "Cannot open file \"%s\"", _fileName.c_str() ), return );
    size = file->GetSize();
    data = new char[size];
    int readen = file->Read( data, size );
    if ( readen != size )
    {
      NI_ALWAYS_ASSERT( NStr::StrFmt( "Cannot read from file \"%s\"", _fileName.c_str() ) );
      delete[] data;
      data = 0;
      size = 0;
    }
	}

  template<typename T>
  int Read( int offset, T& obj ) const
  {
    if ( offset + (int)sizeof( T ) > size )
      return offset;
    obj = *(T*)(&data[offset]);
    return offset + sizeof( T );
  }

  ~File()
  {
    if ( data )
    {
      delete[] data;
      data = 0;
      size = 0;
   }
  }
private:
	File( const File& ) { }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Segment
{
  struct Object
  {
		FileFormat::ObjectRecord objectRecord;
    int offset;
    int offsetEnd;
		int crc;

    struct Iterator
    {
      const File& file;
      const Object& object;
      int offset;

      FileFormat::InfoType type;
      FileFormat::DataRecord data;
      FileFormat::StartChunkRecord startChunk;
      FileFormat::ObjectRecord ptr;
      int level;

      Iterator( const Iterator& it ) : file( it.file ), object( it.object )
      {
        offset = it.offset;
        level = it.level;
        type = it.type;
        data.idChunk = it.data.idChunk;
        data.size = it.data.size;
        data.crc = it.data.crc;
        startChunk.idChunk = it.startChunk.idChunk;
        startChunk.chunkType = it.startChunk.chunkType;
      }

      Iterator( const File& _file, const Object& _object ) : file( _file ), object( _object )
      {
        offset = object.offset;
        level = 0;
        Next();
      }

      bool Next()
      {
        if ( IsFinished() )
          return false;
        offset = file.Read( offset, type );
        switch ( type )
        {
	        case FileFormat::Data:
            offset = file.Read( offset, data );
		        break;
	        case FileFormat::Object:
            offset = file.Read( offset, ptr );
		        break;
	        case FileFormat::StartChunk:
            offset = file.Read( offset, startChunk );
		        ++level;
		        break;
	        case FileFormat::FinishChunk:
		        --level;
		        break;
	        default:
		        NI_ALWAYS_ASSERT( NStr::StrFmt( "File \"%s\" corrupted: Found item with type %d that is not valid duiring processing object at %d",
			        file.fileName.c_str(), type, offset ) );
		        return false;
        }
        return true;
      }

      bool IsFinished() const
      {
        return offset >= object.offsetEnd || offset >= file.size;
      }

      bool operator==( const Iterator& it )
      {
        return offset == it.offset;
      }

      bool operator!=( const Iterator& it )
      {
        return offset != it.offset;
      }

    private:
      void operator=( const Iterator& ) { }
    };

		Object() : offset( -1 ), offsetEnd( -1 ), crc( -1 ) { objectRecord.Set( -1, -1 ); }

		Object( const FileFormat::ObjectRecord& _objectRecord, int _offset, int _offsetEnd, int _crc ) :
			objectRecord( _objectRecord ),
			offset( _offset ),
			offsetEnd( _offsetEnd ),
			crc( _crc )
		{
		}

		bool IsEmpty() const { return offsetEnd <= offset; }
  };

  typedef hash_map<int, Object> IdToObject;
  typedef vector<Object> Objects;  

  IdToObject worldObjects;
  vector<int> worldObjectsIds;
  Objects objects;     

  int step;
  int crc;
	bool broken;
	const File* file;

  void PutObject( const Object& obj )
  {
    if ( obj.objectRecord.worldId == NULL_WORLD_ID ||obj.objectRecord.worldId == -2 || obj.objectRecord.worldId == INVALID_WORLD_ID )
      objects.push_back( obj );
    else
    {
      NI_VERIFY( worldObjects.find( obj.objectRecord.worldId ) == worldObjects.end(), NStr::StrFmt( "Object %d with type 0x%08X stored more than once at segemnt %d", obj.objectRecord.worldId, obj.objectRecord.typeId, step ), return );
      worldObjects[obj.objectRecord.worldId] = obj;
      worldObjectsIds.push_back( obj.objectRecord.worldId );
    }
  }

  void Finish()
  {
    sort( worldObjectsIds.begin(), worldObjectsIds.end() );
  }

  int Load( const File& _file, int offset )
  {
		file = &_file;
		broken = false;
    int result = offset;
    FileFormat::InfoType type;
    result = file->Read( result, type );
    NI_VERIFY( type == FileFormat::Step, NStr::StrFmt( "File \"%s\" corrupted: Found %d instead %d (Step) at %d", 
			file->fileName.c_str(), type, FileFormat::Step, result ), { broken = true; return file->size; } );

    FileFormat::StepRecord stepRecord;
    result = file->Read( result, stepRecord );
    crc = stepRecord.crc;
    step = stepRecord.step;

		int objectStart = -1;
		int level = 0;
		Crc32Checksum crc;
    while ( result < file->size )
    {
      result = file->Read( result, type );
			switch( type )
			{
			case FileFormat::Step:
				{
					Finish();
					return result - sizeof( FileFormat::InfoType );
				}
				break;
			case FileFormat::Data:
				{
					FileFormat::DataRecord data;
					result = file->Read( result, data );
					if ( objectStart >= 0 )
					{
            crc.Add( data.crc ).Add( data.size ).Add( data.idChunk );
					}
				}
				break;
			case FileFormat::Object:
				{
					FileFormat::ObjectRecord object;
					result = file->Read( result, object );
          if ( level == 0 && objectStart >= 0 )
          {
					  PutObject( Object( object, objectStart, result - sizeof( FileFormat::InfoType ) - sizeof( FileFormat::ObjectRecord ), crc.Get() ) );
					  crc.Reset();
					  objectStart = -1;
          }
				}
				break;
			case FileFormat::StartChunk:
				{
					FileFormat::StartChunkRecord startChunk;
					result = file->Read( result, startChunk );
					if ( objectStart >= 0 )
					{
						++level;
						crc.Add( startChunk.idChunk );
					}
					if ( startChunk.chunkType == IBinSaver::CHUNK_COBJECTBASE )
					{
						objectStart = result - sizeof( FileFormat::StartChunkRecord ) - sizeof( FileFormat::InfoType );
						level = 1;
					}
				}
				break;
			case FileFormat::FinishChunk:
				{
					if ( objectStart >= 0 )
					{
						--level;
						NI_VERIFY( level >= 0, NStr::StrFmt( "File \"%s\" corrupted: Found %d (FinishChunk) without record at %d",
							file->fileName.c_str(), FileFormat::FinishChunk, offset ), { broken = true; return file->size; } );
					}
				}
				break;
			default:
				NI_ALWAYS_ASSERT( NStr::StrFmt( "File \"%s\" corrupted: Found %d that is not valid id for chunk type at %d",
					file->fileName.c_str(), type, result ) );
				broken = true;
				return file->size;
				break;
			}
    }
   
		Finish();
    return result;
  }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename TIterator, typename TResult>
int FindSegments( TIterator first, TIterator last, int step, TResult& result )
{
	int count = 0;
	for( ; first != last; ++first )
	{
		if ( first->step == step && !first->broken )
		{
			++count;
			result.push_back( first );
		}
	}

	return count;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CollectDiffObjectsIds( const Segment& segment1, const Segment& segment2, bool all, hash_set<int>& diffObjectsIds )
{
	if ( segment1.crc == segment2.crc )
		return;
	vector<int>::const_iterator n = segment2.worldObjectsIds.begin();
	for( vector<int>::const_iterator i = segment1.worldObjectsIds.begin(); i != segment1.worldObjectsIds.end(); ++i )
	{
		if ( n == segment2.worldObjectsIds.end() || *i < *n )
			diffObjectsIds.insert( *i );
		else if ( *i == *n )
		{
			if ( all || segment1.worldObjects[*i].crc != segment2.worldObjects[*n].crc )
				diffObjectsIds.insert( *i );
			++n;
		}
		else if ( *i > *n )
		{
			while ( n != segment2.worldObjectsIds.end() && *i > *n )
			{
				diffObjectsIds.insert( *n );
				++n;
			}
		}
	}

  while ( n != segment2.worldObjectsIds.end() )
  {
		diffObjectsIds.insert( *n );
		++n;
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DumpSingleItem( const Segment::Object::Iterator& item, const string& prefix, const string& suffix, Stream* result )
{
	switch( item.type )
	{
	case FileFormat::Data:
		result->WriteString( NStr::StrFmt( "%s%sData: %02d %04d 0x%08X%s\n", GetIdent( item.level ), prefix.c_str(), item.data.idChunk,
			item.data.size, item.data.crc, suffix.c_str() ) );
		break;
	case FileFormat::StartChunk:
    result->WriteString( NStr::StrFmt( "%s%s%02d %s%s\n", GetIdent( item.level - 1 ), prefix.c_str(), item.startChunk.idChunk,
			GetChunkTypeName( item.startChunk.chunkType ), suffix.c_str() ) );
    result->WriteString( NStr::StrFmt( "%s%s{%s\n", GetIdent( item.level - 1 ), prefix.c_str(), suffix.c_str() ) );
		break;
	case FileFormat::Object:
    result->WriteString( NStr::StrFmt( "%s%sObject: 0x%08X (%s), id = %s%s\n", GetIdent( item.level ), prefix.c_str(), item.ptr.typeId,
			GetTypeName( item.ptr.typeId ), GetWorldObjectId( item.ptr.worldId ), suffix.c_str() ) );
		break;
	case FileFormat::FinishChunk:
    result->WriteString( NStr::StrFmt( "%s%s}%s\n", GetIdent( item.level ), prefix.c_str(), suffix.c_str() ) );
		break;
	default:
		NI_ALWAYS_ASSERT( NStr::StrFmt( "File \"%s\" corrupted: Found %d that is not valid duiring processing object at %d",
			item.file.fileName.c_str(), item.type, item.offset ) );
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DumpSingleObject( const Segment::Object& object, const File& file, bool right, Stream* result )
{
	const string prefix = right ? "            - " : "";
	const string suffix = right ? "" : " -";

  result->WriteString( "\n" );
	result->WriteString( NStr::StrFmt( "%sObject 0x%08X (%s), id = %s, crc = 0x%08X%s\n", prefix.c_str(),
		object.objectRecord.typeId, GetTypeName( object.objectRecord.typeId ), GetWorldObjectId( object.objectRecord.worldId ), object.crc, suffix.c_str() ) );

  for( Segment::Object::Iterator it = Segment::Object::Iterator( file, object ); !it.IsFinished(); it.Next() )
    DumpSingleItem( it, prefix, suffix, result );
	result->WriteString( NStr::StrFmt( "%s}%s\n\n", prefix.c_str(), suffix.c_str() ) );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FindNextSameData( Segment::Object::Iterator& it1, Segment::Object::Iterator& it2 )
{
  for( ; !it1.IsFinished(); it1.Next() )
  {
    for( Segment::Object::Iterator tempIt2( it2 ); !tempIt2.IsFinished(); tempIt2.Next() )
    {
      if ( it1.level == tempIt2.level && it1.type == tempIt2.type )
      {
        if ( it1.type == FileFormat::Data )
        {
          if ( it1.data.idChunk == tempIt2.data.idChunk )
          {
            it2.offset = tempIt2.offset;
            return;
          }
        }
        else if ( it1.type == FileFormat::StartChunk )
        {
          if ( it1.startChunk.idChunk == tempIt2.startChunk.idChunk && it1.startChunk.chunkType == tempIt2.startChunk.chunkType )
          {
            it2.offset = tempIt2.offset;
            return;
          }
        }
        else if ( it1.type == FileFormat::FinishChunk )
        {
          it2.offset = tempIt2.offset;
          return;
        }
      }
    }
  }

  while ( !it2.IsFinished() )
    it2.Next();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CompareObjects( const Segment::Object& object1, const File& file1, const Segment::Object& object2, const File& file2, Stream* result )
{
	if ( object1.IsEmpty() && object2.IsEmpty() )
		return;
	else if ( object1.IsEmpty() )
		DumpSingleObject( object2, file2, true, result );
	else if ( object2.IsEmpty() )
		DumpSingleObject( object1, file1, false, result );
	else if ( object1.objectRecord.typeId != object2.objectRecord.typeId )
	{
		DumpSingleObject( object1, file1, false, result );
		DumpSingleObject( object2, file2, true, result );
	}
	else
	{
	  result->WriteString( NStr::StrFmt( "Object 0x%08X (%s), id = %s, crc = 0x%08X - 0x%08X\n",
		  object1.objectRecord.typeId, GetTypeName( object1.objectRecord.typeId ), GetWorldObjectId( object1.objectRecord.worldId ), object1.crc, object2.crc ) );

    Segment::Object::Iterator it1 = Segment::Object::Iterator( file1, object1 );
    Segment::Object::Iterator it2 = Segment::Object::Iterator( file2, object2 );

    while( !it1.IsFinished() && !it2.IsFinished() )
    {
      bool diff = it1.type != it2.type;
      if ( !diff )
      {
		    switch( it1.type )
		    {
		    case FileFormat::Data:
          diff = it1.data.idChunk != it2.data.idChunk;
          if ( !diff )
          {
			      result->WriteString( NStr::StrFmt( "%sData: %02d %04d 0x%08X - %04d 0x%08X%s\n", GetIdent( it1.level ), it1.data.idChunk,
              it1.data.size, it1.data.crc, it2.data.size, it2.data.crc, ( it1.data.crc == it2.data.crc ? "" : " (!)" ) ) );
          }
			    break;
		    case FileFormat::StartChunk:
          diff = it1.startChunk.idChunk != it2.startChunk.idChunk || it1.startChunk.chunkType != it2.startChunk.chunkType;
          if ( !diff )
          {
            result->WriteString( NStr::StrFmt( "%s%02d %s\n", GetIdent( it1.level - 1 ), it1.startChunk.idChunk,
				      GetChunkTypeName( it1.startChunk.chunkType ) ) );
            result->WriteString( NStr::StrFmt( "%s{\n", GetIdent( it1.level - 1 ) ) );
          }
			    break;
        case FileFormat::Object:
          if ( it1.ptr.typeId == it2.ptr.typeId && it1.ptr.worldId == it2.ptr.worldId )
          {
    	      result->WriteString( NStr::StrFmt( "%sObject: 0x%08X (%s), id = %s\n", GetIdent( it1.level ),
              it1.ptr.typeId, GetTypeName( it1.ptr.typeId ), GetWorldObjectId( it1.ptr.worldId ) ) );
          }
          else if ( it1.ptr.worldId != it2.ptr.worldId )
          {
    	      result->WriteString( NStr::StrFmt( "%sObject: 0x%08X (%s), id = %s - id = %s (!)\n", GetIdent( it1.level ),
              it1.ptr.typeId, GetTypeName( it1.ptr.typeId ), GetWorldObjectId( it1.ptr.worldId ), GetWorldObjectId( it2.ptr.worldId ) ) );
          }
          else
          {
    	      result->WriteString( NStr::StrFmt( "%sObject: 0x%08X (%s), id = %s - 0x%08X (%s), id = %s (!)\n", GetIdent( it1.level ),
              it1.ptr.typeId, GetTypeName( it1.ptr.typeId ), GetWorldObjectId( it1.ptr.worldId ), it2.ptr.typeId, GetTypeName( it2.ptr.typeId ),  GetWorldObjectId( it2.ptr.worldId ) ) );
          }
          break;
		    case FileFormat::FinishChunk:
          result->WriteString( NStr::StrFmt( "%s}\n", GetIdent( it1.level ) ) );
			    break;
        }
      }
      if ( diff )
      {
        Segment::Object::Iterator sameIt1( it1 );
        Segment::Object::Iterator sameIt2( it2 );
        FindNextSameData( sameIt1, sameIt2 );

        for( ; it1 != sameIt1 && !it1.IsFinished(); it1.Next() )
          DumpSingleItem( it1, "", " -", result );
        for( ; it2 != sameIt2 && !it2.IsFinished(); it2.Next() )
          DumpSingleItem( it2, "            - ", "", result );
      }
      else
      {
        it1.Next();
        it2.Next();
      }
    }
    result->WriteString( "}\n\n" );
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename TIterator, typename TComparer>
void FindNextSameObject( TIterator& it1, const TIterator& end1, TIterator& it2, const TIterator& end2, TComparer comparer )
{
  TIterator bestIt1 = end1;
  TIterator bestIt2 = end2;
  int bestDist = INT_MAX;
  int dist1 = 0;
  int dist2 = 0;
  for( TIterator i1 = it1; i1 != end1 && dist1 < bestDist; ++i1 )
  {
    dist2 = 0;
    for( TIterator i2 = it2; i2 != end2 && dist1 + dist2 < bestDist; ++i2 )
    {
      if ( comparer( i1, i2 ) )
      {
        bestIt1 = i1;
        bestIt2 = i2;
        bestDist = dist1 + dist2;
        break;
      }
      ++dist2;
    }
    ++dist1;
  }
  it1 = bestIt1;
  it2 = bestIt2;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct ObjectsComparer
{
  bool operator()( const vector<Segment::Object>::const_iterator& it1, const vector<Segment::Object>::const_iterator& it2 )
  {
    return it1->objectRecord.typeId == it2->objectRecord.typeId;
  }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CompareSegments( const Segment& segment1, const Segment& segment2, const hash_set<int>& diffObjectsIds, bool all, Stream* result )
{
	Segment::Object empty;
	vector<int> ids;
	for( hash_set<int>::const_iterator it = diffObjectsIds.begin(); it != diffObjectsIds.end(); ++it )
		ids.push_back( *it );
	sort( ids.begin(), ids.end() );
	result->WriteString( NStr::StrFmt( "Compare %d step from \"%s\" (0x%08X) and \"%s\" (0x%08X)\n",segment1.step, 
		segment1.file->fileName.c_str(), segment1.crc, segment2.file->fileName.c_str(), segment2.crc ) );
	for( vector<int>::const_iterator it = ids.begin(); it != ids.end(); ++it )
	{
		hash_map<int, Segment::Object>::const_iterator objPos1 = segment1.worldObjects.find( *it );
		hash_map<int, Segment::Object>::const_iterator objPos2 = segment2.worldObjects.find( *it );
		CompareObjects( objPos1 == segment1.worldObjects.end() ? empty : objPos1->second, *(segment1.file), 
			objPos2 == segment2.worldObjects.end() ? empty : objPos2->second, *(segment2.file), result );
	}

  vector<Segment::Object>::const_iterator it2 = segment2.objects.begin();
	for( vector<Segment::Object>::const_iterator it1 = segment1.objects.begin(); it1 != segment1.objects.end(); )
	{
    if ( it1->objectRecord.typeId == it2->objectRecord.typeId )
    {
      if ( it1->crc != it2->crc || all )
		    CompareObjects( *it1, *(segment1.file), *it2, *(segment2.file), result );
      ++it1;
      ++it2;
    }
    else
    {
      vector<Segment::Object>::const_iterator nextIt1 = it1;
      vector<Segment::Object>::const_iterator nextIt2 = it2;
      FindNextSameObject( nextIt1, segment1.objects.end(), nextIt2, segment2.objects.end(), ObjectsComparer() );
      for( ; it1 != nextIt1; ++it1 )
        CompareObjects( *it1, *(segment1.file), empty, *(segment2.file), result );
      for( ; it2 != nextIt2; ++it2 )
        CompareObjects( empty, *(segment1.file), *it2, *(segment2.file), result );
    }
	}

  while ( it2 != segment2.objects.end() )
  {
    CompareObjects( empty, *(segment1.file), *it2, *(segment2.file), result );
    ++it2;
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class FileWriter
{
public:
  explicit FileWriter( CObj<Stream> stream ): indent(0), stream(stream) {}
  
  template<class StrategyT>
  bool Element( const StrategyT &st )
  {
    FileFormat::InfoType type;
    st.Read( type );
    
    switch( type )
    {
    case FileFormat::Step:
      {
        FileFormat::StepRecord rec;
        st.Read( rec );
        stream->WriteString( NStr::StrFmt("%*sStep %d, %d\n", indent * 2, "", rec.step, rec.crc) );
      }
      break;
    case FileFormat::Data:
      {
        FileFormat::DataRecord rec;
        st.Read( rec );
        stream->WriteString( NStr::StrFmt("%*sData %d, %d\n", indent * 2, "", rec.idChunk,  rec.crc) );
      }
      break;
    case FileFormat::Object:
      {
        FileFormat::ObjectRecord rec;
        st.Read( rec );
        stream->WriteString( NStr::StrFmt("%*sObject %s, %s\n", indent * 2, "", GetTypeName(rec.typeId), GetWorldObjectId(rec.worldId) ) );
      }
      break;
    case FileFormat::StartChunk:
      {
        FileFormat::StartChunkRecord rec;
        st.Read( rec );
        stream->WriteString( NStr::StrFmt("%*sStartChunk %d, %s {\n", indent * 2, "", rec.idChunk, GetChunkTypeName(rec.chunkType) ) );
        ++indent;
      }
      break;
    case FileFormat::FinishChunk:
      {
        --indent;
        stream->WriteString( NStr::StrFmt("%*sFinishChunk }\n", indent * 2, "" ) );
      }
      break;
      
    default:
      return false;
    }
    
    return true;
  }

private:
  int indent;
  CObj<Stream> stream;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct FileReader
{
  FileReader( const File &file, int &result ): file(file), result(result) {}

  template<class T>
  void Read( T &t ) const
  {
    result = file.Read( result, t );
  }

private:
  const File &file;
  int &result;
  
private:
  FileReader &operator=( const FileReader & );
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ConvertToText( const File& file, int beginOffset, int endOffset, CObj<Stream> stream )
{   
  FileReader reader(file, beginOffset);
  FileWriter writer(stream);

  while ( beginOffset < endOffset )
    if( !writer.Element( reader ) )
    {
      NI_ALWAYS_ASSERT( NStr::StrFmt( "File \"%s\" corrupted: Found type that is not valid id for chunk type at %d",
        file.fileName.c_str(), beginOffset ) );
      
      return;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ConvertToText( const File& file, const Segment::Object &obj, CObj<Stream> stream )
{   
  stream->WriteString( NStr::StrFmt("Start Object %s, %s, 0x%08X {\n", GetChunkTypeName(obj.objectRecord.typeId), GetWorldObjectId(obj.objectRecord.worldId), obj.crc ) );
  ConvertToText( file, obj.offset, obj.offsetEnd, stream );
  stream->WriteString( NStr::StrFmt("Finish Object %s }\n", GetChunkTypeName(obj.objectRecord.typeId) ) );
    
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ConvertToText( const File& file, const Segment::IdToObject &out, const Segment::IdToObject &exclude, CObj<Stream> stream )
{
  typedef Segment::IdToObject::const_iterator IterMap;

  for( IterMap it = out.begin(); it != out.end(); ++it )
  {
    IterMap res = exclude.find( it->first );

    if( res == out.end() || it->second.crc != res->second.crc )
      ConvertToText( file, it->second, stream ); 
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ConvertToText( const File& file, const Segment::Objects &out, const Segment::Objects &exclude, CObj<Stream> stream )
{
  typedef map<int, int> TypeIdToCrc;
  typedef Segment::Objects::const_iterator IterObj;

  TypeIdToCrc typeIdToCrc;

  for( IterObj it = exclude.begin(); it != exclude.end(); ++it )
    typeIdToCrc[it->objectRecord.typeId] = it->crc; 

  for( IterObj it = out.begin(); it != out.end(); ++it ) 
  {
    TypeIdToCrc::const_iterator res = typeIdToCrc.find( it->objectRecord.typeId );

    if( res == typeIdToCrc.end() || it->crc != res->second )
      ConvertToText( file, *it, stream ); 
  } 
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ConvertToText( const Segment &out, const Segment &exclude, CObj<Stream> stream )
{
  stream->WriteString( NStr::StrFmt("=== Step %d, 0x%08X\n", out.step, out.crc ) );
  ConvertToText( *out.file, out.worldObjects, exclude.worldObjects, stream );
  ConvertToText( *out.file, out.objects, exclude.objects, stream );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CompareCRC( const char *name, const vector<wstring> &params )
{
  if ( params.size() < 2 ) 
  {
      systemLog( NLogg::LEVEL_MESSAGE ) << "usage: " << name << 
        " crc_file crc_file [crc_file] ... [-o:output_file] [-h|-s] [-a] [-t]" << endl;
      return true;
  }

  bool history = false;
  bool single = false;
  bool all = false;
  bool convertToText = false;
	list<string> fileNames;
	string outFileName;
	for( vector<wstring>::const_iterator it = params.begin(); it != params.end(); ++it )
	{
		string param = NStr::ToMBCS( *it );
    if ( param.empty() )
      continue;
    if ( param[0] != '-' )
			fileNames.push_back( param );
    else if ( param.size() > 1 )
    {
      switch ( param[1] )
      {
      case 'o':
      case 'O':
        outFileName = param.substr( 3 );
        break;
      case 'h':
      case 'H':
        single = false;
        history = true;
        break;
      case 's':
      case 'S':
        single = true;
        history = false;
        break;
      case 'a':
      case 'A':
        all = true;
        break;     
      case 't':
      case 'T':
        convertToText = true;
        break;
      }
    }
	}

  list<File> files;
	for( list<string>::const_iterator it = fileNames.begin(); it != fileNames.end(); ++it )
		files.push_back().Load( *it );

  //Оставим старый вариант, как самый простой и надёжный
  if( convertToText && all && history )
  {
    int fileNum = 1;
        
    for( list<File>::const_iterator it = files.begin(); it != files.end(); ++it )
    {
      CObj<Stream> stream = new TinyFileWriteStream( NDebug::GenerateDebugFileName(NStr::StrFmt("diff_async_%d", fileNum++), "log", "." ).c_str(), TinyFileWriteStream::TEXT );
      ConvertToText( *it, 0, it->size, stream );     
    }
 
    return true;
  }

	int minStep = INT_MAX;
	int maxStep = INT_MIN;
	list<Segment> segments;
	for( list<File>::const_iterator it = files.begin(); it != files.end(); ++it )
	{
		int offset = 0;
		while ( offset < it->size )
    {
		  offset = segments.push_back().Load( *it, offset );
		  minStep = Min( minStep, segments.back().step );
		  maxStep = Max( maxStep, segments.back().step );
    }
	}

	hash_set<int> diffObjectsIds;
	if ( history && !all )
	{
		for( int step = minStep; step <= maxStep; ++step )
		{
			vector<list<Segment>::const_iterator> thisSegments;
			if ( FindSegments( segments.begin(), segments.end(), step, thisSegments ) < 2 )
				continue;

			for( vector<list<Segment>::const_iterator>::const_iterator i = thisSegments.begin(); i != thisSegments.end(); ++i )
			{
				vector<list<Segment>::const_iterator>::const_iterator n = i;
				++n;
				for( ; n != thisSegments.end(); ++n )
					CollectDiffObjectsIds( **i, **n, false, diffObjectsIds );
			}
		}
	}

  bool found = false;
  
  CObj<Stream> file1, file2;
  
  if( !convertToText )
  {
    if ( outFileName.empty() )
      outFileName = NDebug::GenerateDebugFileName("async", "log", "." );
 
	  file1 = new TinyFileWriteStream( outFileName, TinyFileWriteStream::TEXT );
	}
	else
	{
    file1 = new TinyFileWriteStream( NDebug::GenerateDebugFileName("diff_async_1", "log", "." ).c_str(), TinyFileWriteStream::TEXT );
    file2 = new TinyFileWriteStream( NDebug::GenerateDebugFileName("diff_async_2", "log", "." ).c_str(), TinyFileWriteStream::TEXT );
  }
		
	for( int step = minStep; step <= maxStep && ( !found || !single ); ++step )
	{
		vector<list<Segment>::const_iterator> thisSegments;
		if ( FindSegments( segments.begin(), segments.end(), step, thisSegments ) < 2 )
			continue;

		for( vector<list<Segment>::const_iterator>::const_iterator i = thisSegments.begin(); i != thisSegments.end(); ++i )
		{
			if ( (*i)->broken )
				continue;
			vector<list<Segment>::const_iterator>::const_iterator n = i;
			++n;
			for( ; n != thisSegments.end(); ++n )
			{
        if ( !history && (*i)->crc == (*n)->crc )
					continue;
				if ( (*n)->broken )
					continue;
        found = true;
				
				if( !convertToText )
				{
          if ( all || !history )
          {
            diffObjectsIds.clear();
            CollectDiffObjectsIds( **i, **n, all, diffObjectsIds );
          }
				  
				  CompareSegments( **i, **n, diffObjectsIds, all, file1 );
				}
				else
				{
				  if( !all )
				  {
				    ConvertToText( **i, **n, file1 );
				    ConvertToText( **n, **i, file2 );
				  }
				  else
				  {
            Segment empty;
            ConvertToText( **i, empty, file1 );
            ConvertToText( **n, empty, file2 );
				  }
				}	  
			}
		}
	}

  return true;
}
} // namespace
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NCore
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BinStatsCollector::Init( unsigned char* _buffer, size_t _size, int step )
{
  buffer = _buffer;
  buffCurr = _buffer;
  buffEnd = _buffer + _size;
  isOverrun = false;
  AppendObject<Step>().Set( step );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class BinStatsCollector::DebugPrintData: NonCopyable
{
public:
  DebugPrintData( FILE *flOut ): 
    indent(0), flOut(flOut), pPtrsData(0) 
  {
    NI_ASSERT( flOut != 0, "" );
  }
  
  DebugPrintData(const char *szFileName ): 
    indent(0), pPtrsData(0) 
  {
    if( fopen_s(&flOut, szFileName, "w") != 0 )
      NI_ALWAYS_ASSERT( "Can't open file" );
  }
  
  ~DebugPrintData()
  {
    fclose(flOut);
  }
  
  void ProcessRecord( const Record<Step> &rec )
  {
    fprintf( flOut, "%*sStep %d, %d\n", indent * 2, "", rec.step, rec.crc );
  }

  void ProcessRecord( const Record<Data> &rec )
  {
    fprintf( flOut, "%*sData %d, %d\n", indent * 2, "", rec.idChunk, rec.crc );
  }

  void ProcessRecord( const Record<Object> &rec )
  {
    NI_ALWAYS_ASSERT( "BinStatsCollector format error" );
  }

  void ProcessRecord( const Record<StartChunk> &rec )
  {
    fprintf( flOut, "%*sStartChunk %d, %s {\n", indent * 2, "", rec.idChunk, GetChunkTypeName(rec.chunkType) );
    ++indent;
  }

  void ProcessRecord( const Record<FinishChunk> &rec )
  {
    --indent;
    fprintf( flOut, "%*sFinishChunk }\n", indent * 2, "" );
  }

  void ProcessRecord( const Record<Pointer> &rec )
  {
    fprintf( flOut, "%*sPointer %d, ", indent * 2, "", rec.idChunk );
    PrintPtr( rec.pointer );
    fprintf( flOut, "\n" );
  }

  void ProcessRecord( const Record<StartObject> &rec )
  {
    fprintf( flOut, "%*sStartObject {\n", indent * 2, "" );
    ++indent;
  }

  void ProcessRecord( const Record<FinishObject> &rec )
  {
    --indent;
    fprintf( flOut, "%*sFinishObject %s, ", indent * 2, "", GetChunkTypeName(rec.typeId) );
    PrintPtr( rec.pointer );
    fprintf( flOut, " }\n" );
  }
    
  void ProcessRecord( const Record<CurrentCrcObject> &rec )
  {
    fprintf( flOut, "%*sCurrentCrc %d\n", indent * 2, "", rec.crc );
  }
  
  void SetPtrsData( const PointersData &ptrsData )
  {
    pPtrsData = &ptrsData;   
  }
  
private:
  void PrintPtr( CObjectBase *pPtr )
  {
    if( pPtrsData )
    {
      PointersData::const_iterator it = pPtrsData->find( pPtr );
      
      if( it != pPtrsData->end() )
      {
        fprintf( flOut, "%s - %s", GetTypeName(it->second.typeId), GetWorldObjectId(it->second.worldId) );
        return;
      }
    }
    
    fprintf( flOut, "%p", pPtr );
  }

private:
  int indent;
  FILE *flOut;
  const PointersData *pPtrsData;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class BinStatsCollector::CollectPointerData
{
public:
  CollectPointerData(PointersData &ptrsData): 
    ptrsData(ptrsData) 
  {
    PointerData data;
    data.typeId = NULL_TYPE_ID;
    data.worldId = NULL_WORLD_ID;
    ptrsData.insert( PointersData::value_type(0, data) );
  }
  
  template<char Type>
  void ProcessRecord( const Record<Type> &rec )
  {
    //Nothing
  }
  
  void ProcessRecord( const Record<StartObject> &rec )
  {  
    stack.push_back( WaitingChunk );
  }
  
  void ProcessRecord( const Record<StartChunk> &rec )
  {
    if( rec.chunkType == PF_Core::WorldObjectBase::typeId ) 
      stack.push_back(WaitingData);  
    else
      stack.push_back(NonInterestingChunk);   
  }
  
  void ProcessRecord( const Record<Data> &rec )
  {
    if( stack.empty() )
      return;

    if( stack.back().state == WaitingData && rec.idChunk == PF_Core::WorldObjectBase::OBJECT_ID_CHUNK_NUM )
    {
      stack.back().worldId = rec.crc;
      stack.back().state = WaitingChunkFinish;
    }
  }
  
  void ProcessRecord( const Record<FinishChunk> &rec )
  {
    NI_VERIFY( !stack.empty(), "BinStatsCollector format error", return );
  
    if( stack.back().state == NonInterestingChunk ) 
      stack.pop_back();
    else
    {
      NI_ASSERT( stack.back().state == WaitingChunkFinish, "BinStatsCollector format error" );
      const int worldId = stack.back().worldId;
      stack.pop_back();
      NI_VERIFY( !stack.empty(), "BinStatsCollector format error", return );
      stack.back().worldId = worldId;
      stack.back().state = WaitingChunkFinish;
    }
  }

  void ProcessRecord( const Record<FinishObject> &rec )
  {  
    NI_VERIFY( !stack.empty(), "BinStatsCollector format error", return );
    
    PointerData data;
    data.typeId = rec.typeId;
    
    if( stack.back().state == WaitingChunkFinish )
      data.worldId = stack.back().worldId;
    else
    {
      NI_ASSERT( stack.back().state == WaitingChunk, "BinStatsCollector format error");
      data.worldId = INVALID_WORLD_ID;
    }
      
    const bool isInserted = ptrsData.insert( PointersData::value_type(rec.pointer, data) ).second;
    NI_ASSERT( isInserted, "BinStatsCollector format error" );
    stack.pop_back();
  }
  
private:
  enum State
  {
    WaitingChunk,
    NonInterestingChunk,
    WaitingData,
    WaitingChunkFinish
  }; 
  
  struct StackData
  {
    State state;
    int worldId;
    
    StackData() {}
    StackData( State state, int worldId = 0 ): 
      state(state), worldId(worldId) {}
  };
  
  typedef vector<StackData> Stack;
  
  CollectPointerData &operator=( const CollectPointerData & );
 
private:
  PointersData &ptrsData;
  Stack stack;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class BinStatsCollector::WriteObjectsToFile
{
public:
  WriteObjectsToFile(const PointersData &ptrsData, Stream &stream): 
    ptrsData(ptrsData), stream(stream) {}

  void ProcessRecord( const Record<Step> &rec )
  {
    FileFormat::StepRecord out;
    out.Set( rec.step, rec.crc );
    stream << FileFormat::Step << out;
  }

  void ProcessRecord( const Record<Data> &rec )
  {
    FileFormat::DataRecord out;
    out.Set( rec.idChunk, 0, rec.crc );
    stream << FileFormat::Data << out;
  }

  void ProcessRecord( const Record<Object> &rec )
  {
    NI_ALWAYS_ASSERT( "BinStatsCollector format error" );
  }

  void ProcessRecord( const Record<StartChunk> &rec )
  {
    FileFormat::StartChunkRecord out;
    out.Set( rec.idChunk, rec.chunkType );
    stream << FileFormat::StartChunk << out;
  }

  void ProcessRecord( const Record<FinishChunk> &rec )
  {
    stream << FileFormat::FinishChunk;
  }

  void ProcessRecord( const Record<Pointer> &rec )
  {
    Record<StartChunk> outChunckStart;
    outChunckStart.Set( rec.idChunk, IBinSaver::CHUNK_PTR );
    ProcessRecord( outChunckStart );

    FileFormat::ObjectRecord out;

    PointersData::const_iterator const it = ptrsData.find(rec.pointer);
    
    if( it != ptrsData.end() )
      out.Set( it->second.typeId, it->second.worldId );
    else
      out.Set( INVALID_TYPE_ID, INVALID_WORLD_ID );
    
    stream << FileFormat::Object << out;
    
    Record<FinishChunk> outChunckFinish;
    outChunckFinish.Set();
    ProcessRecord( outChunckFinish );
  }

  void ProcessRecord( const Record<StartObject> &rec )
  {
    Record<StartChunk> outChunckStart;
    outChunckStart.Set( 1, IBinSaver::CHUNK_COBJECTBASE );
    ProcessRecord( outChunckStart );
  }

  void ProcessRecord( const Record<FinishObject> &rec )
  {
    Record<FinishChunk> outChunckFinish;
    outChunckFinish.Set();
    ProcessRecord( outChunckFinish );
    
    FileFormat::ObjectRecord out;
    
    PointersData::const_iterator const it = ptrsData.find(rec.pointer);

    if( it != ptrsData.end() )
    { 
      NI_ASSERT( rec.typeId == it->second.typeId, "BinStatsCollector format error" );
      out.Set( it->second.typeId, it->second.worldId );
    }
    else
    {
      out.Set( rec.typeId, INVALID_WORLD_ID );
      NI_ALWAYS_ASSERT( "BinStatsCollector format error" );
    }

    stream << FileFormat::Object << out;
  }
 
  void ProcessRecord( const Record<CurrentCrcObject> &rec )
  {
    (void)rec;
    //Nothing
  }
  
private:  
  WriteObjectsToFile &operator=( const WriteObjectsToFile & );

private:
  const PointersData &ptrsData;
  Stream &stream;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class BinStatsCollector::LinearizeData
{
public:
  explicit LinearizeData( BuffersStack &buffStack ): 
    buffStack(buffStack), curBuffNum(0) 
  {
    buffStack.clear();
    buffStack.reserve(30);
    buffStack.push_back( Buffer() );  
  }
  
  template< int num >
  void ProcessRecord( const Record<num> &rec )
  {
    ProcessRecordImpl(rec);  
  }
  
  void ProcessRecord( const Record<StartObject> &rec )
  {
    ++curBuffNum;
    
    if( curBuffNum == buffStack.size() )
      buffStack.push_back( Buffer() );  
  
    ProcessRecordImpl(rec);  
  }
  
  void ProcessRecord( const Record<FinishObject> &rec )
  {
    ProcessRecordImpl(rec);
  
    if( curBuffNum > 0 )
      --curBuffNum;
    else
      NI_ALWAYS_ASSERT( "Format error" );   
  }
  
private:
  template< int num >
  void ProcessRecordImpl( const Record<num> &rec )
  {
    NI_ASSERT( curBuffNum < buffStack.size(), "" );
    buffStack[curBuffNum].insert( buffStack[curBuffNum].end(), PtrToBuff(&rec), PtrToBuff(&rec + 1) );
  }
  
  template<class T>
  const Buffer::value_type *PtrToBuff( const T *p )
  {
    return static_cast<const Buffer::value_type *>( static_cast<const void *>(p) );
  }

private:  
  LinearizeData &operator=( const LinearizeData & );
  
private:
  BuffersStack &buffStack;
  int curBuffNum;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


template<class Strategy>
class BinStatsCollector::ObjectsParser: public Strategy
{
public:
  explicit ObjectsParser( Strategy st = Strategy() ): 
    Strategy(st) { fillArray<0>(); }
 
  template< class T >
  explicit ObjectsParser( const T &t ): 
    Strategy(t) { fillArray<0>(); }

  const char *Process( const char *pCur, const char * const pEnd )
  { 
    NI_ASSERT( *pCur >= 0 && *pCur < ARRAY_SIZE(parseFnc), "BinStatsCollector format error" );
    return (this->*parseFnc[*pCur])( pCur, pEnd );
  }

private:  
  template<char Type>
  const char *ParseRecord( const char *pCur, const char * const pEnd )
  { 
    NI_ASSERT( pEnd - pCur >= sizeof(Record<Type>), "BinStatsCollector format error" );

    const Record<Type> * const pResult = static_cast<const Record<Type> *>( static_cast<const void *>(pCur) );
    Strategy::ProcessRecord( *pResult );
    return pCur + sizeof(Record<Type>);
  }
  
  template<char Type>
  void fillArray()
  {
    parseFnc[Type] = &ObjectsParser::ParseRecord<Type>;
    fillArray<Type + 1>();
  }

  template<>
  void fillArray<InfoType_Count>()
  {
    //Nothing
  }
  
private:
  typedef const char *( ObjectsParser::*ParseRecordFnc )( const char *pCur, const char * const pEnd );
  ParseRecordFnc parseFnc[InfoType_Count];
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class T>
void BinStatsCollector::ParseBuff( const char *pBeg, const char *pEnd, T &obj )
{
  while( pBeg < pEnd )
    pBeg = obj.Process(pBeg, pEnd);
   
  NI_ASSERT( pBeg == pEnd, "BinStatsCollector format error" );  
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class T>
void BinStatsCollector::ParseBuff( const BuffersStack &buffStack, T &obj )
{
  for( int i = 0; i < buffStack.size(); ++i )
  {
    const char * const pBeg = &buffStack[i].front();
    const char * const pEnd = pBeg + buffStack[i].size();

    ParseBuff( pBeg, pEnd, obj );
  }      
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      
//Создаём новый файл, если файл с таким именем уже есть, то возвращаем 0
static FILE *CreateNewFileForWriteImpl( const char *szPath )
{
  FILE* pFile = fopen(szPath, "a+");

  if( pFile == NULL )
    return NULL;
  
  //Если файл только что создан, то позиция будет стоять на нуле  
  fpos_t pos;
  fgetpos( pFile, &pos );
 
  if( pos != 0 ) 
  { 
    fclose(pFile);
    pFile = NULL;
  }  

  return pFile;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static FILE *CreateNewFileForWrite( const void *buffer, const char *szSuffix )
{ 
  int step = BinStatsCollector::getStepFromBuffer(buffer);
  unsigned int crc = BinStatsCollector::getCrcFromBuffer(buffer); 
  
  int fileNum = 0;
  FILE *flResult = 0;
  
  do 
  {
    const string result = NDebug::GenerateDebugFileName(NStr::StrFmt("%s-%d-%08X_%d", szSuffix, step, crc, fileNum++), "txt", "." );
    flResult = CreateNewFileForWriteImpl( result.c_str() );
  } 
  while ( flResult == 0 );
  
  return flResult;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BinStatsCollector::writeToFile( const void *buffer, size_t size, Stream &stream )
{
  //После того как был написан код сравнения дампов, поменялся формат их хранения на
  //более эффективный и для того, чтобы не переписывать код сравнения, переконвертируем 
	//в старый формат во время записи
  const char *pBeg = static_cast<const char *>(buffer);
  const char * const pEnd = pBeg + size;
     
  //Отладочная печать
  if( false )
  {    
    ObjectsParser<DebugPrintData> printer( CreateNewFileForWrite(buffer, "raw_async") );
    ParseBuff( pBeg, pEnd, printer );  
  }
  
  //Собираем информацию по объектам исходя из информации об указателях
  PointersData ptrsData;
  ObjectsParser<CollectPointerData> collector( ( CollectPointerData(ptrsData) ) );
  ParseBuff( pBeg, pEnd, collector );
  
  if( false )
  {    
    ObjectsParser<DebugPrintData> printer( CreateNewFileForWrite(buffer, "raw_async_ptrs") );
    printer.SetPtrsData(ptrsData);
    ParseBuff( pBeg, pEnd, printer );  
  }
  
  //Преобразовываем вложенную структуру нового формата в плоскую структуру старого 
  BuffersStack buffStack;
  ObjectsParser<LinearizeData> linealizer( ( LinearizeData(buffStack) ) );
  ParseBuff( pBeg, pEnd, linealizer );
  
  //Снова отладочная печать
  if( false )
  {
    ObjectsParser<DebugPrintData> printer( CreateNewFileForWrite(buffer, "raw_async_linear") );
    printer.SetPtrsData(ptrsData);
    ParseBuff( buffStack, printer ); 
  }
  
  //Окончательный вывод в поток
  ObjectsParser<WriteObjectsToFile> writer( WriteObjectsToFile(ptrsData, stream) );
  ParseBuff( buffStack, writer );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int BinStatsCollector::getStepFromBuffer( const void *buffer ) 
{ 
  return static_cast<const Record<Step> *>(buffer)->step; 
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int BinStatsCollector::getCrcFromBuffer( const void *buffer ) 
{ 
  return static_cast<const Record<Step> *>(buffer)->crc; 
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BinStatsCollector::setStepToBuffer( void *buffer, int _step )
{
  static_cast<Record<Step> *>(buffer)->step = _step;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BinStatsCollector::setCrcToBuffer( void *buffer, unsigned int _crc )
{
  static_cast<Record<Step> *>(buffer)->crc = _crc;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace NCore
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_DEV_CMD( compare_crc, CompareCRC );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
