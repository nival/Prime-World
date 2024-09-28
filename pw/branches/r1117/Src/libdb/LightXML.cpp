#include "stdafx.h"

#include "LightXML.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NLightXml
{

static const char *szEndOfLine = "\x0D\n";
static const char *szTab = "\t";
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** attribute
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* CXmlAttribute::Parse( const char *pszBegin, const char *pszEnd )
{
	const char *p = SkipWhiteSpace( pszBegin );
	if ( !p || !*p ) 
		return 0;

	// Read the name, the '=' and the value.
	p = ReadName( p, &szName );
	if ( !p || !*p )
	{
		// TIXml_ERROR_READING_ATTRIBUTES
		return 0;
	}
	p = SkipWhiteSpace( p );
	if ( !p || !*p || *p != '=' )
	{
		// TIXml_ERROR_READING_ATTRIBUTES
		return 0;
	}

	p = SkipWhiteSpace( p + 1 ); // skip '='
	if ( !p || !*p )
	{
		// TIXml_ERROR_READING_ATTRIBUTES
		return 0;
	}
	
	if ( *p == '\'' )
	{
		++p;
		static const string szEndTag = "\'";
		p = ReadText( &szValue, p, pszEnd, szEndTag, false );
	}
	else if ( *p == '"' )
	{
		++p;
		static const string szEndTag = "\"";
		p = ReadText( &szValue, p, pszEnd, szEndTag, false );
	}
	else
	{
		// All attribute values should be in single or double quotes.
		// But this is such a common error that the parser will try its best, even without them.
		szValue.clear();
		while ( p && *p	&&								// existence
						!IsWhiteSpace(*p) &&			// whitespace
						*p != '/' && *p != '>' )	// tag end
		{
			szValue += *p;
			++p;
		}
	}
	return p;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CXmlAttribute::Store( NLightXml_STREAM &stream ) const
{
	if ( szValue.find('\"') != string::npos )
	{
		stream.WriteChecked( szName );
		stream << "='";
		stream.WriteChecked( szValue );
		stream << "'";
	}
	else
	{
		stream.WriteChecked( szName );
		stream << "=\"";
		stream.WriteChecked( szValue );
		stream << "\"";
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** Xml node general functions
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CXmlNode::CXmlNode( const EType _eType )
: eType( _eType ), dwHashCode( 0 )
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CXmlNode::~CXmlNode()
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** Xml multi-node
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const char* pszXmlHeader = "<?xml";
static const char* pszCommentHeader = "<!--";
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool IsHeader( const char *pszBegin, const char *pszEnd )
{
	// min node <?xml?>
	return (pszEnd - pszBegin >= 7) && ( *((unsigned long*)pszBegin) == *((unsigned long*)pszXmlHeader) ) && ( pszBegin[4] == 'l' );
}
bool IsComment( const char *pszBegin, const char *pszEnd )
{
	// min node <!---->
	return (pszEnd - pszBegin >= 7) && ( *((unsigned long*)pszBegin) == *((unsigned long*)pszCommentHeader) );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CXmlMultiNode::~CXmlMultiNode() 
{	
	for ( CNodesList::iterator it = children.begin(); it != children.end(); ++it )
		delete *it;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CXmlNode* CXmlMultiNode::Identify( const char *pszBegin, const char *pszEnd )
{
	const char *p = SkipWhiteSpace( pszBegin );
	if( !p || !*p || *p != '<' )
		return 0;

	// What is this thing? 
	// - Elements start with a letter or underscore, but xml is reserved.
	// - Comments: <!--
	// - Declaration: <?xml
	// - Everthing else is unknown to tinyxml.
	//
	CXmlNode *pNode = 0;
	if ( IsHeader(p, pszEnd) )
		pNode = new CXmlDeclaration();
	else if ( isalpha(*(p + 1)) || *(p + 1) == '_' )
		pNode = new CXmlElement();
	else if ( IsComment(p, pszEnd) )
		pNode = new CXmlComment();
	else
		pNode = new CXmlUnknown();
	return pNode;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CXmlMultiNode::Store( NLightXml_STREAM &stream, const string &szIndention ) const
{
	for ( CNodesList::const_iterator it = children.begin(); it != children.end(); ++it )
	{
		stream << szIndention;
		(*it)->Store( stream, szIndention );
		stream << szEndOfLine;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CXmlNode* CXmlMultiNode::FindChild( const string &_szValue ) const
{
	const unsigned long dwChildHashCode = hash<string>()( _szValue );
	// try optimized search from optimal search position
	for ( CNodesList::const_iterator it = posOptimal; it != children.end(); ++it )
	{
		if ( (*it)->IsMatch(_szValue, dwChildHashCode) ) 
		{
			posOptimal = it;
			++posOptimal;
			return (*it);
		}
	}
	// search from begin to optimal search position...
	for ( CNodesList::const_iterator it = children.begin(); it != posOptimal; ++it )
	{
		if ( (*it)->IsMatch(_szValue, dwChildHashCode) ) 
		{
			posOptimal = it;
			++posOptimal;
			return (*it);
		}
	}
	// can't find. reset optimal search position
	ResetOptimalPos();
	//
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** Xml element
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CXmlElement::CXmlElement()
: CXmlMultiNode( CXmlNode::ELEMENT )
{
}
CXmlElement::~CXmlElement()
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CXmlElement::SetAttributeLocal( const string &szName, const char *szValue )
{
	CAttributesMap::iterator pos = attrmap.find( szName );
	if ( pos != attrmap.end() ) 
		pos->second->SetValue( szValue );
	else
	{
		attributes.push_back( CXmlAttribute(szName, szValue) );
		attrmap[szName] = &( attributes.back() );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CXmlElement::SetAttribute( const CXmlAttribute &attr )
{
	SetAttributeLocal( attr.GetName(), attr.GetValue().c_str() );
}
void CXmlElement::SetAttribute( const string &szName, const CToStringConvertor &value )
{
	SetAttributeLocal( szName, value );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const CXmlAttribute* CXmlElement::GetAttribute( const string &szName ) const
{
	CAttributesMap::const_iterator pos = attrmap.find( szName );
	return pos != attrmap.end() ? pos->second : 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CXmlElement::RemoveAttribute( const string &szName )
{
	CAttributesMap::iterator pos = attrmap.find( szName );	
	if ( pos != attrmap.end() ) 
	{
		attrmap.erase( pos );
		for ( CAttributesList::iterator it = attributes.begin(); it != attributes.end(); ++it )
		{
			if ( it->GetName() == szName ) 
			{
				attributes.erase( it );
				return;
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* CXmlElement::ReadValue( const char *pszBegin, const char *pszEnd )
{
	// Read in text and elements in any order.
	const char *p = SkipWhiteSpace( pszBegin );
	while ( p && *p )
	{
		if ( *p != '<' )
		{
			// Take what we have, make a text element.
			CXmlText *pTextNode = new CXmlText();
			p = pTextNode->Parse( p, pszEnd );

			if ( !pTextNode->IsBlank() )
				szText = pTextNode->GetValue();

			delete pTextNode;
		} 
		else 
		{
			// We hit a '<'
			// Have we hit a new element or an end tag? (p == "</")
			// HINT: check only *(p + 1) == '/', because here we know, that *p == '<'
			if ( *(p + 1) == '/' )
				return p;
			else
			{
				if ( CXmlNode *pNode = Identify(p, pszEnd) )
				{
					p = pNode->Parse( p, pszEnd );
					AddChild( pNode );
				}				
				else
					return 0;
			}
		}
		p = SkipWhiteSpace( p );
	}

	return p;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* CXmlElement::Parse( const char *pszBegin, const char *pszEnd )
{
	ResetOptimalPos();
	//
	const char *p = SkipWhiteSpace( pszBegin );

	if ( !p || !*p || *p != '<' )
		return 0;
	p = SkipWhiteSpace( p + 1 );
	// Read the name.
	p = ReadName( p, &szValue );
	if ( !p || !*p )
		return 0;

	const string szEndTag = "</" + szValue + ">";
	// Check for and read attributes. Also look for an empty tag or an end tag.
	while ( p && *p )
	{
		p = SkipWhiteSpace( p );
		if ( !p || !*p )
			return 0;
		if ( *p == '/' )
		{
			++p;
			// Empty tag.
			if ( *p	!= '>' )
				return 0;
			return p + 1;
		}
		else if ( *p == '>' )
		{
			// Done with attributes (if there were any.) 
			// Read the value -- which can include other elements - read the end tag, and return.
			++p;
			p = ReadValue( p, pszEnd );		// Note this is an Element method
			if ( !p || !*p )
				return 0;

			// We should find the end tag now
			if ( IsEqualSubstring( szEndTag, p, pszEnd) )
			{
				p += szEndTag.length();
				return p;
			}
			else
				return 0;
		}
		else
		{
			// Try to read an attribute:
			CXmlAttribute attrib;
			p = attrib.Parse( p, pszEnd );
			if ( !p || !*p )
				return 0;
			SetAttribute( attrib );
		}
	}
	return p;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CXmlElement::Store( NLightXml_STREAM &stream, const string &szIndention ) const
{
	stream << "<" << szValue;
	for ( CAttributesList::const_iterator it = attributes.begin(); it != attributes.end(); ++it )
	{
		stream << " ";
		it->Store( stream );
	}
	// If this node has children or text, give it a closing tag. Else make it an empty tag.
	if ( HasChildren() ) 
	{
		string szNextIndention = szIndention + szTab;
		stream << ">";
		stream << szEndOfLine;
		if ( !szText.empty() )
		{
			stream << szNextIndention;
			stream.WriteChecked( szText );
			stream << szEndOfLine;
		}
		CXmlMultiNode::Store( stream, szNextIndention );
		stream << szIndention;
		stream << "</" << szValue << ">";
	}
	else
		if ( !szText.empty() ) 
		{
			stream << ">";
			stream.WriteChecked( szText );
			stream << "</" << szValue << ">";
		}
		else
			stream << "/>";
}
// ************************************************************************************************************************ //
// **
// ** text
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CXmlText::CXmlText()
: CXmlNode( CXmlNode::TEXT )
{
}
CXmlText::~CXmlText()
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* CXmlText::Parse( const char *pszBegin, const char *pszEnd )
{
	szValue.clear();
	static const string szEndTag = "<";
	const char *p = ReadText( &szValue, pszBegin, pszEnd, szEndTag, false );
	//
	return p != 0 ? p - 1 : 0; // don't truncate the '<'
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CXmlText::Store( NLightXml_STREAM &stream, const string & ) const
{
	stream.WriteChecked( szValue );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** Xml Comment
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CXmlComment::CXmlComment()
: CXmlNode( CXmlNode::COMMENT )
{
}
CXmlComment::~CXmlComment()
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* CXmlComment::Parse( const char *pszBegin, const char *pszEnd )
{
	szValue.clear();

	const char *p = SkipWhiteSpace( pszBegin );

	if ( !IsComment(p, pszEnd) )
	{
		// TIXml_ERROR_PARSING_COMMENT
		return 0;
	}
	p += 4; // strlen( "<!--" )
	static string szCommentEndTag = "-->";
	p = ReadText( &szValue, p, pszEnd, szCommentEndTag, false );
	return p;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CXmlComment::Store( NLightXml_STREAM &stream, const string & ) const
{
	stream << "<!--";
	stream.WriteChecked( szValue );
	stream << "-->";
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** declaration
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CXmlDeclaration::CXmlDeclaration()
: CXmlNode( CXmlNode::DECLARATION ), szVersion( "1.0" ), szEncoding( "UTF-8" )
{
}
CXmlDeclaration::~CXmlDeclaration()
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* CXmlDeclaration::Parse( const char *pszBegin, const char *pszEnd )
{
	const char *p = SkipWhiteSpace( pszBegin );
	// Find the beginning, find the end, and look for the stuff in-between.
	if ( !p || !*p || !IsHeader(p, pszEnd) )
	{
		// TIXml_ERROR_PARSING_DECLARATION
		return 0;
	}

	p += 5;

	szVersion.clear();
	szEncoding.clear();
	szStandalone.clear();

	while ( p && *p )
	{
		if ( *p == '>' )
		{
			++p;
			return p;
		}

		p = SkipWhiteSpace( p );
		if ( IsEqualSubstringIC("version", p) )
		{
			// p += 7
			CXmlAttribute attrib;
			p = attrib.Parse( p, pszEnd );		
			szVersion = attrib.GetValue();
		}
		else if ( IsEqualSubstringIC("encoding", p) )
		{
			// p += 8
			CXmlAttribute attrib;
			p = attrib.Parse( p, pszEnd );		
			szEncoding = attrib.GetValue();
		}
		else if ( IsEqualSubstringIC("standalone", p) )
		{
			// p += 10;
			CXmlAttribute attrib;
			p = attrib.Parse( p, pszEnd );		
			szStandalone = attrib.GetValue();
		}
		else
		{
			// Read over whatever it is.
			while( p && *p && *p != '>' && !isspace( (unsigned char)(*p) ) )
				++p;
		}
	}
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CXmlDeclaration::Store( NLightXml_STREAM &stream, const string & ) const
{
	stream << "<?xml";
	//
	if ( !szVersion.empty() )
	{
		stream << " version=\"";
		stream.WriteChecked( szVersion );
		stream << "\"";
	}
	if ( !szEncoding.empty() )
	{
		stream << " encoding=\"";
		stream.WriteChecked( szEncoding );
		stream << "\"";
	}
	if ( !szStandalone.empty() )
	{
		stream << " standalone=\"";
		stream.WriteChecked( szStandalone );
		stream << "\"";
	}
	//
	stream << "?>";
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** Xml Unknown
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CXmlUnknown::CXmlUnknown()
: CXmlNode( CXmlNode::UNKNOWN )
{
}
CXmlUnknown::~CXmlUnknown()
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* CXmlUnknown::Parse( const char *pszBegin, const char * )
{
	const char *p = SkipWhiteSpace( pszBegin );
	if ( !p || !*p || *p != '<' )
		return 0;
	++p;
	szValue.clear();

	while ( p && *p && *p != '>' )
	{
		szValue += *p;
		++p;
	}

	if ( !p )
	{
		// TIXml_ERROR_PARSING_UNKNOWN
	}
	//
	return *p == '>' ? p + 1 : p;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CXmlUnknown::Store( NLightXml_STREAM &stream, const string & ) const
{
	stream << "<" << szValue << ">";		// Don't use entities hear! It is unknown.
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** Xml Document
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CXmlDocument::CXmlDocument()
: CXmlMultiNode( CXmlNode::DOCUMENT )
{
}
CXmlDocument::~CXmlDocument()
{
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* CXmlDocument::Parse( const char *pszBegin, const char *pszEnd )
{
	ResetOptimalPos();
	// Parse away, at the document level. Since a document contains nothing but other tags, most of what happens
	// here is skipping white space.
	// In this variant (as opposed to stream and Parse) we read everything we can.
	if ( !pszBegin || !*pszBegin )
		return 0;
	const char *p = SkipWhiteSpace( pszBegin );
	if ( !p )
		return 0;

	while ( *p )
	{
		if ( CXmlNode *pNode = Identify(p, pszEnd) )
		{
			p = pNode->Parse( p, pszEnd );
			AddChild( pNode );
		}
		else
			break;
		p = SkipWhiteSpace( p );
	}
	// All is well.
	return p;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CXmlDocument::Store( NLightXml_STREAM &stream, const string &szIndention ) const
{
	for ( CXmlMultiNode::const_iterator it = begin(); it != end(); ++it )
	{
		(*it)->Store( stream, szIndention );
		stream << szEndOfLine;
		// Special rule for streams: stop after the root element.
		// The stream in code will only read one element, so don't write more than one.
		if ( (*it)->GetType() == CXmlNode::ELEMENT )
			return;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CXmlElement *CXmlDocument::GetRootElement()
{
	const int nNumChildren = CountChildren();
	NLightXml::CXmlNode *pRootNode = 0;
	for ( int i = 0; i < nNumChildren; ++i )
	{
		pRootNode = GetChild( i );
		if ( pRootNode->GetType() != NLightXml::CXmlNode::ELEMENT )
			pRootNode = 0;
		else
			break;
	}
	//
	return pRootNode != 0 ? static_cast<CXmlElement *>( pRootNode ) : 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
