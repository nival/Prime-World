#include "stdafx.h"

#include "XmlChunkSaver.h"
#include "XMLReader.h"
#include "XmlUtils.h"
#include "../System/Texts.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const int START_CHUNK_LEVELS = 50;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void XmlChunkSaver::PushReadChunkLevel( const NXml::CXmlNode *pNode )
{
	++nCurChunkLevel;
	if ( readChunkLevels.size() <= nCurChunkLevel )
		readChunkLevels.resize( nCurChunkLevel * 2 );
	
	readChunkLevels[nCurChunkLevel] = pNode;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void XmlChunkSaver::PopReadChunkLevel()
{
	--nCurChunkLevel;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void XmlChunkSaver::Start( Stream *_pStream )
{
	pStream = 0;
	nCurChunkLevel = -1;
	readChunkLevels.resize( START_CHUNK_LEVELS );

	if ( IsReading() ) 
	{
		pXmlReader = new NXml::CXmlReader( _pStream );
	}
	else
	{
		NI_VERIFY( _pStream->CanWrite(), "Read only stream passed", return );

		pStream = _pStream;
		// add Xml declaration
		CXmlDeclaration *pDeclaration = new CXmlDeclaration();
		pDeclaration->SetVersion( "1.0" );
		document.AddChild( pDeclaration );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void XmlChunkSaver::Finish()
{
	if ( !IsReading() ) 
	{
		NI_VERIFY( pStream != 0, "", return );
		NLightXml_STREAM stream( pStream );
		document.Store( stream );
	}
	pStream = 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool XmlChunkSaver::StartChunk( const chunk_id idChunk, int nChunkNumber )
{
	//currentChunks.push_back( make_pair( idChunk, nChunkNumber ) );

	if ( IsReading() ) 
	{
		if ( nChunkNumber > 0 )	// elements container
		{
			const vector<const NXml::CXmlNode*> &nodes = pReadNode->GetNodes();
			if ( nChunkNumber - 1 < nodes.size() )
			{
				const NXml::CXmlNode *pNode = nodes[nChunkNumber - 1];

        if ( !TestInheritableAttrs(pNode) )
        {
          return false;
        }

        NI_ASSERT( (pNode->GetName() == "Item") || (pNode->GetName() == "item") || (pNode->GetName() == "State") || (pNode->GetName() == "state")
          , NI_STRFMT("Wrong %dth item of container (%s)", nChunkNumber, pNode->GetName().ToString().c_str()) );
				PushReadChunkLevel( pReadNode );
				pReadNode = pNode;
        lastResult = RR_ADD;
				return true;
			}
		}
		else if ( idChunk != 0 )	// try single element by name
		{
			if ( !pReadNode )
			{
				//PushReadChunkLevel( pReadNode );
				pReadNode = pXmlReader->GetRootElement();
				return true;
			}
			else if ( const NXml::CXmlNode *pNode = pReadNode->FindChild( idChunk ) )
			{
				PushReadChunkLevel( pReadNode );
				pReadNode = pNode;
				return true;
			}
		}
		else	// use this node
		{
			PushReadChunkLevel( pReadNode );
			return true;
		}
	}
	else
	{
		if ( pCurrNode )
			chunkLevels.push_back( pCurrNode );
		//
		CXmlMultiNode *pNode = 0;
		if ( nChunkNumber > 0 )	// elements container
		{
			pNode = new CXmlElement();
			pNode->SetValue( "Item" );
		}
		else if ( idChunk != 0 ) // single or first element
		{
			pNode = new CXmlElement();
			pNode->SetValue( idChunk );
		}
		else	// use this node
			pNode = pCurrNode;
		//
		if ( !pCurrNode )
			document.AddChild( pNode );
		else if ( pCurrNode != pNode )
			pCurrNode->AddChild( pNode );

		pCurrNode = pNode;
		return true;
	}

	//currentChunks.pop_back();
	return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void XmlChunkSaver::FinishChunk()
{
	//currentChunks.pop_back();

	if ( IsReading() )
	{
		if ( nCurChunkLevel != -1 ) 
		{
			pReadNode = readChunkLevels[nCurChunkLevel];
			PopReadChunkLevel();
		}
		else
			pReadNode = 0;

    lastResult = RR_ADD;
	}
	else
	{
		if ( !chunkLevels.empty() ) 
		{
			pCurrNode = chunkLevels.back();
			chunkLevels.pop_back();
		}
		else
			pCurrNode = 0;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int XmlChunkSaver::CountChunks()
{
	if ( IsReading() )
		return pReadNode != 0 ? pReadNode->GetNodes().size() : 0;
	else
		return pCurrNode != 0 ? pCurrNode->CountChildren() : 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool XmlChunkSaver::DataChunk( const chunk_id idChunk, int *pnData, int nChunkNumber )
{
	if ( IsReading() ) 
	{
		if ( const NXml::CXmlNode *pNode = pReadNode->FindChild( idChunk ) )
		{
      if ( !TestInheritableAttrs(pNode) )
      {
        return false;
      }
			*pnData = NStr::ReadInt( pNode->GetValue().pszBegin, pNode->GetValue().nSize );
      lastResult = RR_ADD;
			return true;
		}
		else
		{
			if ( (strcmp(idChunk, "Item") == 0) || (strcmp(idChunk, "item") == 0) ) 
			{
				if ( const NXml::CXmlNode *pNode = pReadNode->FindChild("item") )
				{
					const NXml::SXmlAttribute *pAttribute = pNode->GetDataAttribute();
					//int nCheck = 0;
					if ( pAttribute && pAttribute->value.nSize )
						*pnData = NStr::ReadInt( pAttribute->value.pszBegin, pAttribute->value.nSize );
					return true;
				}
			}
			else
			{
				const NXml::SXmlAttribute *pAttribute = pReadNode->GetAttribute( idChunk );
				//int nCheck = 0;
				if ( pAttribute && pAttribute->value.nSize ) 
					*pnData = NStr::ReadInt( pAttribute->value.pszBegin, pAttribute->value.nSize );
				return true;
			}
		}
	}
	else if ( pCurrNode ) 
	{
		if ( idChunk != 0 )
		{
			CXmlElement *pElement = new CXmlElement();
			pElement->SetValue( idChunk );
			pElement->SetText( NI_STRFMT("%d", *pnData) );
			pCurrNode->AddChild( pElement );
		}
		else
		{
			checked_cast<CXmlElement*>(pCurrNode)->SetText( NI_STRFMT("%d", *pnData) );
		}
		return true;
	}
	return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool XmlChunkSaver::DataChunk( const chunk_id idChunk, float *pfData, int nChunkNumber )
{
	if ( IsReading() ) 
	{
		if ( const NXml::CXmlNode *pNode = pReadNode->FindChild( idChunk ) )
		{
      if ( pNode->GetValue().nSize )
      {
			  *pfData = NStr::ReadFloat( pNode->GetValue().pszBegin, pNode->GetValue().nSize );
			  return true;
      }
      else
        return false;
		}
		else
		{
			if ( (strcmp(idChunk, "Item") == 0) || (strcmp(idChunk, "item") == 0) ) 
			{
				if ( const NXml::CXmlNode *pNode = pReadNode->FindChild("item") )
				{
					const NXml::SXmlAttribute *pAttribute = pNode->GetDataAttribute();
					if ( pAttribute && pAttribute->value.nSize )
					{
						*pfData = NStr::ReadFloat( pAttribute->value.pszBegin, pAttribute->value.nSize );
						return true;
					}
					return false;
				}
			}
			else
			{
				const NXml::SXmlAttribute *pAttribute = pReadNode->GetAttribute( idChunk );
				if ( pAttribute && pAttribute->value.nSize )
				{
					*pfData = NStr::ReadFloat( pAttribute->value.pszBegin, pAttribute->value.nSize );
					return true;
				}
				return false;
			}
		}
	}
	else if ( pCurrNode ) 
	{
		if ( idChunk != 0 )
		{
			CXmlElement *pElement = new CXmlElement();
			pElement->SetValue( idChunk );
			pElement->SetText( NI_STRFMT("%g", *pfData) );
			pCurrNode->AddChild( pElement );
		}
		else
		{
			checked_cast<CXmlElement*>(pCurrNode)->SetText( NI_STRFMT("%d", *pfData) );
		}
		return true;
	}
	return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool String2Bool( const char *pszStr )
{
	switch ( *pszStr )
	{
		case 'T':
		case 't':
		case '1':
			return true;

		case 'F':
		case 'f':
		case '0':
			return false;
	}
	
	systemLog( NLogg::LEVEL_ASSERT ) << "Can't convert value \"" << pszStr << "\" to bool" << endl;
	return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool XmlChunkSaver::DataChunk( const chunk_id idChunk, bool *pData, int nChunkNumber )
{
	if ( IsReading() ) 
	{
		if ( const NXml::CXmlNode *pNode = pReadNode->FindChild(idChunk) )
		{
			if ( pNode->GetValue().nSize )
			{
				*pData = String2Bool( pNode->GetValue().pszBegin );
				return true;
			}
			return false;
		}
		else
		{
			if ( strcmp(idChunk, "Item") == 0 ) 
			{
				if ( const NXml::CXmlNode *pNode = pReadNode->FindChild("item") )
				{
					const NXml::SXmlAttribute *pAttribute = pNode->GetDataAttribute();
					if ( pAttribute && pAttribute->value.nSize ) 
					{
						*pData = String2Bool( pAttribute->value.pszBegin );
						return true;
					}
					else
						return false;
				}
			}
			else
			{
				const NXml::SXmlAttribute *pAttribute = pReadNode->GetAttribute( idChunk );
				if ( pAttribute && pAttribute->value.nSize ) 
				{
					*pData = String2Bool( pAttribute->value.pszBegin );
					return true;
				}
				else
					return false;
			}
		}
	}
	else if ( pCurrNode ) 
	{
		CXmlElement *pElement = new CXmlElement();
		pElement->SetValue( idChunk );
		const char *pszText = ( *pData == false ? "false" : "true" );
		pElement->SetText( pszText );
		pCurrNode->AddChild( pElement );
		return true;
	}
	return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool XmlChunkSaver::DataChunk( const chunk_id idChunk, void *pData, int nSize, int nChunkNumber )
{
	if ( idChunk != 0 && StartChunk(idChunk, nChunkNumber) == false )
		return false;
	NI_ASSERT( nSize > 0, "Wrong size passed" );
	string szString;
	if ( IsReading() ) 
	{
		DataChunkString( szString );
		if ( !szString.empty() )
		{
			NI_ASSERT( szString.size() == nSize * 2, "Wrong bin chunk size" );
			NStr::StringToBin( szString.c_str(), pData, 0 );
		}
		else
			memset( pData, 0, nSize );
	}
	else
	{
		szString.resize( nSize * 2 );
		NStr::BinToString( pData, nSize, &(szString[0]) );
		DataChunkString( szString );
	}
	//
	if ( idChunk != 0 )
		FinishChunk();
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef WIN32
bool XmlChunkSaver::DataChunk( const chunk_id idChunk, GUID *pgData, int nChunkNumber )
{
	if ( idChunk != 0 && StartChunk(idChunk, nChunkNumber) == false )
		return false;
	//
	bool bRetVal = false;
	string szValue;
	if ( IsReading() )
	{
		if ( DataChunkString(szValue) )
		{
			NStr::String2GUID( szValue.c_str(), pgData );
			bRetVal = true;
		}
	}
	else
	{
		NStr::GUID2String( &szValue, *pgData );
		bRetVal = DataChunkString( szValue );
	}
	FinishChunk();
	return bRetVal;
}
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const string XmlChunkSaver::GetTypeOfNextElement() const
{
	if ( pReadNode == 0 || pReadNode == pXmlReader->GetRootElement() )
		return pXmlReader->GetRootElement()->GetName().ToString();

	const vector<const NXml::CXmlNode*> &nodes = pReadNode->GetNodes();
	if ( nodes.size() != 1 )
		return string();

	return nodes[0]->GetName().ToString();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const bool XmlChunkSaver::IsComplexNextElement() const
{
	if ( pReadNode == 0 || pReadNode == pXmlReader->GetRootElement() )
		return true;

	return !pReadNode->GetNodes().empty();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const bool XmlChunkSaver::HasHRefAttr() const
{
	return pReadNode->GetHRefAttribute() != 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const bool XmlChunkSaver::HasIdAttr() const
{
	return pReadNode->GetAttribute( "id" ) != 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const bool XmlChunkSaver::HasAnimatedAttr() const
{
	return pReadNode->GetAttribute( "Animated" ) != 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const string XmlChunkSaver::GetHRefAttrValue() const
{
	if ( !HasHRefAttr() )
		return string();
	else
		return pReadNode->GetHRefAttribute()->value.ToString();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const string XmlChunkSaver::GetIdAttrValue() const
{
	if ( !HasIdAttr() )
		return string();
	else
		return pReadNode->GetAttribute( "id" )->value.ToString();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void XmlChunkSaver::SetHrefIdAttributes( const string &_href, const string &id )
{
	if ( !IsReading() && pCurrNode )
	{
		string href;
		NStr::MBCSToUTF8( &href, _href );
		static_cast<CXmlElement*>(pCurrNode)->SetAttribute( "href", "/" + href );
		static_cast<CXmlElement*>(pCurrNode)->SetAttribute( "id", "/" + id );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const bool XmlChunkSaver::HasParentAttr() const
{
  return pReadNode->GetAttribute( "parent" ) != 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const string XmlChunkSaver::GetParentAttrValue() const
{
  if ( !HasParentAttr() )
    return string();
  else
    return pReadNode->GetAttribute( "parent" )->value.ToString();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const string XmlChunkSaver::GetStateNameAttrValue() const
{
  const NXml::SXmlAttribute* attr = pReadNode->GetAttribute( "name" );
  if ( !attr )
    return string();
  else
    return attr->value.ToString();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool XmlChunkSaver::DataChunkFilePath( NFile::CFilePath *pFilePath )
{
	if ( IsReading() )
	{
		if ( pReadNode )
		{
			string szFilePath;
			if ( const NXml::SXmlAttribute *pAttrib = pReadNode->GetHRefAttribute() )
			{
				const string &szRefValue = pAttrib->value.ToString();
				if ( !szRefValue.empty() )
				{
					//if ( szRefValue[0] == '/' || szRefValue[0] == '\\' )
						szFilePath = szRefValue.c_str() + 1;
					//else
					//	szFilePath = GetFilePath() + szRefValue;
				}
				else
					szFilePath = "";
			}
			else
				szFilePath = pReadNode->GetValue().ToString();
			//
			if ( szFilePath.empty() )
				*pFilePath = "";
			else
				NStr::UTF8ToMBCS( pFilePath, szFilePath );
			//
			return true;
		}
	}
	else
	{
		if ( pCurrNode )
		{
			string szFilePath;
			NStr::MBCSToUTF8( &szFilePath, *pFilePath );
			checked_cast<CXmlElement*>(pCurrNode)->SetAttribute( "href", "/" + szFilePath );
			return true;
		}
	}
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool XmlChunkSaver::DataChunkTextRef( CTextRef *pTextRef )
{
	if ( IsReading() )
	{
		if ( pReadNode )
		{
			string szTextFilePath;
			if ( const NXml::SXmlAttribute *pAttrib = pReadNode->GetTextRefAttribute() )
			{
				const string & szRefValue = pAttrib->value.ToString();
				if ( !szRefValue.empty() )
					szTextFilePath = szRefValue.c_str() + 1;
				else
					szTextFilePath = "";
			}
			else
				szTextFilePath = pReadNode->GetValue().ToString();

			if ( szTextFilePath.empty() )
				pTextRef->fileName.clear();
			else
      {
        if ( szTextFilePath[0] != '/' )
          szTextFilePath = "/" + szTextFilePath;
				NStr::UTF8ToMBCS( &pTextRef->fileName, szTextFilePath );
        if ( pResourceHandler && pResourceHandler->NeedPrecacheTexts() )
          pTextRef->GetText();
      }
			return true;
		}
	}
	else
	{
	}

	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool XmlChunkSaver::DataChunkString( string &data )
{
	if ( IsReading() ) 
	{
		if ( pReadNode )
		{
			data = pReadNode->GetValue().ToString();
			NXml::ConvertToString( &data );

			return true;
		}
	}
	else if ( pCurrNode ) 
	{
		checked_cast<CXmlElement*>(pCurrNode)->SetText( data );
		return true;
	}
	return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool XmlChunkSaver::DataChunkString( wstring &data )
{
	if ( IsReading() ) 
	{
		if ( pReadNode )
		{
			string szData = pReadNode->GetValue().ToString();
			NXml::ConvertToString( &szData );
			NStr::UTF8ToUnicode( &data, szData );
			return true;
		}
	}
	else if ( pCurrNode ) 
	{
		string szString;
		NStr::UnicodeToUTF8( &szString, data );
		checked_cast<CXmlElement*>(pCurrNode)->SetText( szString );
		return true;
	}
	return false;
}

bool XmlChunkSaver::TestInheritableAttrs( const NXml::CXmlNode* pNode )
{
  if ( const NXml::SXmlAttribute* pAttr = pNode->GetAttribute( "skip" ) )
  {
    lastResult = RR_SKIP;
    return false;
  }
  if ( const NXml::SXmlAttribute* pAttr = pNode->GetAttribute( "delete" ) )
  {
    lastResult = RR_DELETE;
    return false;
  }
  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IXmlSaver *CreateXmlSaver( Stream *pStream, const bool reading, IResourceReader* pResourceHandler )
{
	NI_VERIFY( IsValid( pStream ), "Invalid stream", return 0 );
	NI_VERIFY( !reading || pStream->GetSize() > 0, "Invalid stream", return 0 );

	return new XmlChunkSaver( pStream, reading, pResourceHandler );
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_SAVELOAD_CLASS( XmlChunkSaver );
