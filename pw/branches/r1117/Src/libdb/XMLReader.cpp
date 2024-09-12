#include "stdafx.h"

#include "LightXMLUtils.h"
#include "XMLReader.h"
#include "System/FileSystem/FilePath.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NXml
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static	bool IsWhiteSpace( const char chr )
{
	return (chr == ' ') || ( chr == '\n' ) || ( chr =='\r' ) || ((chr >= 0x09) && (chr <= 0x0d));
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const char* FindNodeStart( const char *p, const char *pEnd )
{
	while ( p < pEnd && *p != '<' )
		++p;

	++p;

	return p;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const char* FindNodeEnd( const char *p, const char *pEnd )
{
	while ( p < pEnd && *p != '>' )
		++p;

	++p;

	return p;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const char* FindNotText( const char *p, const char *pEnd )
{
	while ( p < pEnd && !IsWhiteSpace( *p ) && *p != '>' && *p != '/' && *p != '=' && *p != '<' )
		++p;

	return p;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const char* FindEndOfNodeText( const char *p, const char *pEnd )
{
	while ( p < pEnd && *p != '<' )
		++p;

	return p;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static	const char* SkipWhiteSpace( const char *p, const char *pEnd )
{
	while ( p < pEnd && IsWhiteSpace(*p) ) 
		++p;
	//
	return p;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const char* SkipComments( const char *p, const char *pEnd )
{
	for(;;)
	{
		if ( p >= pEnd )
			return p;
		
		if ( *p != '!' )
			return p;

		++p;
		for(;;)
		{
			if ( p >= pEnd || p+1 >= pEnd || p+2 >= pEnd )
				break;

			if ( *p == '-' && *(p+1) == '-' && *(p+2) == '>' )
			{
				p += 3;
				break;
			}

			++p;
		}
		p = SkipWhiteSpace( p, pEnd );
		++p;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* CXmlNode::ParseNodeAttributes( const char *p )
{
	for(;;)
	{
		p = SkipWhiteSpace( p, pEnd );
		if ( p >= pEnd )
			return p;

		if ( *p == '>' || *p == '/' )
			return p;

		SXmlAttribute *pAttr = pPool->attrPool.Alloc();

		pAttr->name.pszBegin = p;
		p = FindNotText( p, pEnd );
		pAttr->name.nSize = p - pAttr->name.pszBegin;

		p = SkipWhiteSpace( p, pEnd );
		if ( p >= pEnd || *p != '=' )
			return p;

		++p;
		p = SkipWhiteSpace( p, pEnd );
		if ( p >= pEnd || *p != '"' )
			return p;

		++p;
		pAttr->value.pszBegin = p;
		while ( p < pEnd && *p != '"' )
			++p;
		pAttr->value.nSize = p - pAttr->value.pszBegin;
		if ( p < pEnd )
			++p;

		if ( pAttr->name == "href" )
			pHRefAttr = pAttr;
		if ( pAttr->name == "textref" )
			pTextRefAttr = pAttr;
		if ( pAttr->name == "data" )
			pHDataAttr = pAttr;

		attributes.push_back( pAttr );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* CXmlNode::ParseNodeInternal( const char *p )
{
	for(;;)
	{
		p = SkipWhiteSpace( p, pEnd );
		if ( p >= pEnd )
			return p;

		if ( *p == '<' )
		{
			if ( p + 1 >= pEnd )
				return p;

			if ( *(p+1) == '/' )
			{
				p = FindNodeEnd( p, pEnd );
				return p;
			}
			if ( *(p+1) == '!' )
			{
				p = SkipComments( p + 1, pEnd );
				--p;
				continue;
			}

			CXmlNode *pChild = pPool->nodesPool.Alloc();
			p = pChild->Parse( p + 1, pEnd, pPool );
			nodes.push_back( pChild );
		}
		else
		{
			value.pszBegin = p;
			p = FindEndOfNodeText( p, pEnd );
			value.nSize = p - value.pszBegin;
		}
	}
	//return p; //unreachable code here
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* CXmlNode::Parse( const char *p, const char *pszEnd, SPool *_pPool )
{
	pEnd = pszEnd;
	nBestNodeToRead = 0;
	nBestAttrToRead = 0;
	nodes.clear();
	attributes.clear();
	pHRefAttr = 0;
	pTextRefAttr = 0;
	pHDataAttr = 0;
	pPool = _pPool;
	
	p = SkipComments( p, pEnd );
	p = SkipWhiteSpace( p, pEnd );
	if ( p >= pEnd )
		return p;

	name.pszBegin = p;
	p = FindNotText( p, pEnd );
	name.nSize = p - name.pszBegin;

	p = SkipWhiteSpace( p, pEnd );
	if ( p >= pEnd )
		return p;

	if ( *p == '>' )
		p = ParseNodeInternal( p + 1 );
	else if ( *p == '/' )
	{
		++p;
		++p;
	}
	else
	{
		p = ParseNodeAttributes( p );
		if ( *p == '>' )
			p = ParseNodeInternal( p + 1 );
		else if ( *p == '/' )
		{
			++p;
			++p;
		}
	}

	return p;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const CXmlNode* CXmlNode::FindChild( const char *pszChild ) const
{
	if ( !pszChild || pszChild[0] == 0 )
		return this;

	if ( nodes.empty() )
		return 0;

	nBestNodeToRead %= nodes.size();
	if ( nodes[nBestNodeToRead]->GetName() == pszChild )
		return nodes[nBestNodeToRead++];
	
	const int nMemBestNodeToRead = ++nBestNodeToRead;
	while ( nBestNodeToRead < nodes.size() )
	{
		if ( nodes[nBestNodeToRead]->GetName() == pszChild )
			return nodes[nBestNodeToRead++];

		++nBestNodeToRead;
	}

	nBestNodeToRead = 0;
	while ( nBestNodeToRead < nMemBestNodeToRead )
	{
		if ( nodes[nBestNodeToRead]->GetName() == pszChild )
			return nodes[nBestNodeToRead++];

		++nBestNodeToRead;
	}

	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const SXmlAttribute* CXmlNode::GetHRefAttribute() const
{
	return pHRefAttr;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const SXmlAttribute* CXmlNode::GetTextRefAttribute() const
{
	return pTextRefAttr;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const SXmlAttribute* CXmlNode::GetDataAttribute() const
{
	return pHDataAttr;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const SXmlAttribute* CXmlNode::GetAttribute( const char *pszAttr ) const
{
	if ( attributes.empty() )
		return 0;

	nBestAttrToRead %= attributes.size();
	if ( attributes[nBestAttrToRead]->name == pszAttr )
		return attributes[nBestAttrToRead++];
	
	const int nMemBestAttrToRead = ++nBestAttrToRead;
	while ( nBestAttrToRead < attributes.size() )
	{
		if ( attributes[nBestAttrToRead]->name == pszAttr )
			return attributes[nBestAttrToRead++];

		++nBestAttrToRead;
	}

	nBestAttrToRead = 0;
	while ( nBestAttrToRead < nMemBestAttrToRead )
	{
		if ( attributes[nBestAttrToRead]->name == pszAttr )
			return attributes[nBestAttrToRead++];

		++nBestAttrToRead;
	}

	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CXmlReader::Start()
{
	if ( !IsValid( pStream ) || !pStream->IsOk() || pStream->GetSize() == 0 )
		return;

	const char *pBuffer = pStream->GetBuffer();
	NI_VERIFY( pBuffer, "Cannot get direct access to stream's buffer", return );

	const char *pBufferEnd = pBuffer + pStream->GetSize();
	const char *pBufferStart = FindNodeStart( pBuffer, pBufferEnd );
	
	if ( pBufferStart >= pBufferEnd )
		return;

	if ( *pBufferStart == '?' )
		pBufferStart = FindNodeStart( pBufferStart, pBufferEnd );

	if ( pBufferStart >= pBufferEnd )
		return;

	rootNode.Parse( pBufferStart, pBufferEnd, &pool );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CXmlReader::CXmlReader( Stream *_pStream )
{
	pStream = _pStream;
	Start();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_SAVELOAD_CLASS_NM( CXmlReader, NXml );
