#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "LightXML.h"
#include "XmlSaver.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NXml
{
	class CXmlReader;
	class CXmlNode;
}
using namespace NLightXml;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class XmlChunkSaver : public IXmlSaver
{
	OBJECT_METHODS( 0x1E4A8B4F, XmlChunkSaver );
	//
	CObj<NXml::CXmlReader> pXmlReader;
	const NXml::CXmlNode *pReadNode;

  vector<const NXml::CXmlNode*> readChunkLevels;
	int nCurChunkLevel;

  EReadResult lastResult;

	CXmlDocument document;
	CPtr<Stream> pStream;
	CXmlMultiNode *pCurrNode;
	typedef list<CXmlMultiNode*> CChunksList;
	CChunksList chunkLevels;
	bool bReading;

  string srcFileName;
  string srcId;
  IResourceReader* pResourceHandler;

	void PushReadChunkLevel( const NXml::CXmlNode *pNode );
	void PopReadChunkLevel();
	
	int CountChunks();

	bool DataChunk( const chunk_id idChunk, void *pData, int nSize, int nChunkNumber );
	bool DataChunk( const chunk_id idChunk, int *pnData, int nChunkNumber );
	bool DataChunk( const chunk_id idChunk, float *pfData, int nChunkNumber );
	bool DataChunk( const chunk_id idChunk, bool *pData, int nChunkNumber );
  #ifdef WIN32	
	  bool DataChunk( const chunk_id idChunk, GUID *pgData, int nChunkNumber );
  #endif	  
	
	bool DataChunkFilePath( NFile::CFilePath *pFilePath );
	bool DataChunkTextRef( CTextRef *pTextRef );
	bool DataChunkString( string &data );
	bool DataChunkString( wstring &data );
	//
	void StoreObject( CObjectBase *pObject );
	CObjectBase* LoadObject();
	//
	void Start( Stream *pStream );
	void Finish();
	//const string& GetFilePath() const { return szFilePath; }

  EReadResult GetCurrentReadResult() const { return lastResult; }

  XmlChunkSaver() : pReadNode( 0 ), pCurrNode( 0 ), bReading( true ), lastResult( IXmlSaver::RR_ADD ) {	}
public:
	XmlChunkSaver( Stream *_pStream, const bool _bReading, IResourceReader* _pResourceHandler )	
  : pReadNode( 0 ), pCurrNode( 0 ), bReading( _bReading ), pResourceHandler( _pResourceHandler ), lastResult( IXmlSaver::RR_ADD ) 
	{ 
		Start( _pStream );
	}
	~XmlChunkSaver() { Finish(); }

	bool StartChunk( const chunk_id idChunk, int nChunkNumber );

  bool TestInheritableAttrs( const NXml::CXmlNode* pNode );
  void FinishChunk();

	virtual void SetSourceFileName( const string & fileName ) { srcFileName = fileName; }
	virtual const string & GetSourceFileName() const { return srcFileName; }
	virtual void SetSourceId( const string & id ) { srcId = id; }
	virtual const string & GetSourceId() const { return srcId; }
  const vector<const NXml::CXmlNode*> & GetChunkLevels() const { return readChunkLevels; }
  int GetCurChunkLevel() const {return nCurChunkLevel;}
	//
	bool IsReading() const { return bReading; }
	//virtual const string& GetFileName() const { return szFileName; }

	virtual void SetHrefIdAttributes( const string &href, const string &id );
	virtual const string GetTypeOfNextElement() const;
	virtual const bool IsComplexNextElement() const;

	virtual const bool HasHRefAttr() const;
	virtual const string GetHRefAttrValue() const;
	virtual const bool HasIdAttr() const;
	virtual const string GetIdAttrValue() const;
	virtual const bool HasAnimatedAttr() const;
  virtual const bool HasParentAttr() const;
  virtual const string GetParentAttrValue() const;
  virtual const string GetStateNameAttrValue() const;

  virtual IResourceReader* GetResourceReader() const { return pResourceHandler; }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
