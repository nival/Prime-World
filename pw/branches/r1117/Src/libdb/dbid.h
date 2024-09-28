#ifndef _DBID_H_
#define _DBID_H_

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct IXmlSaver;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DBID is unique resource identifier. It's a wrapper around resource's XPointer
// For one-file resources it looks like <resoruce_file_name>#xpointer(/<resource_type>)
// For inline resources it looks like <resoruce_file_name>#xpointer(id(<resource_id>)/<resource_type>)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NDb
{

class DBID
{
	unsigned int hashKey;
	ZDATA
		string fileName;
		string id;
		ZONSERIALIZE
public:
	ZEND int operator&( IBinSaver &f ) { f.Add(2,&fileName); f.Add(3,&id); OnSerialize( f ); return 0; }
	int operator&( IXmlSaver &saver );
private:
	void OnSerialize( IBinSaver &saver );
	bool CompareEqual( const string &fileName, const string &id ) const;
public:
	DBID() : hashKey( 0 ) {}
	DBID( const DBID &other )
		: hashKey(other.hashKey), fileName(other.fileName), id(other.id) {}
	
	explicit DBID( const string &fileName );
	explicit DBID( const string &fileName, const string &id );

	bool operator==( const DBID &dbid ) const { return hashKey == dbid.hashKey ? CompareEqual( dbid.fileName, dbid.id ) : false; }
	bool operator!=( const DBID &dbid ) const { return !(*this == dbid); }
	bool operator<( const DBID &dbid ) const;

	unsigned int GetHashKey() const { return hashKey; }

	const string &GetFileName() const { return fileName; }
	const string &GetId() const { return id; }
	const bool IsInlined() const { return !id.empty(); }
	
	bool IsEmpty() const { return fileName.empty(); }

  const string GetFormatted() const {
    if ( id.empty() )
		  return fileName;
	  else
		  return fileName + ":" + id;
  }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline const string GetFormattedDbId( const DBID &dbid ) { return dbid.GetFormatted(); } //Legacy

void FixFileNameForDBID( string* pFileName );

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} //namespace NDb
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace nstl
{
	template<> struct hash<NDb::DBID>
	{
		size_t operator()( const NDb::DBID &dbid ) const { return dbid.GetHashKey(); }
	};
} // namespace nstl;

#endif

