#include "stdafx.h"

#include "LightXMLUtils.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NLightXml
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const string szEntityAmp		= "amp;";		// '&'
static const string szEntityLt		= "lt;";		// '<'
static const string szEntityGt		= "gt;";		// '>'
static const string szEntityQuot	= "quot;";	// '\"'
static const string szEntityApos	= "apos;";	// '\''
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** write stream
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWriteStream::WriteChecked( const string &str )
{
	int i = 0;
	while( i < str.length() )
	{
		const int chr = str[i];

		switch ( chr ) 
		{
			case '&':
				if ( (i < ( (int)str.length() - 2 )) && (str[i + 1] == '#') && (str[i + 2] == 'x') ) 
				{
					// Hexadecimal character reference.
					// Pass through unchanged.
					// &#xA9;	-- copyright symbol, for example.
					while ( i < (int)str.length() )
					{
						buffer << str[i];
						++i;
						if ( str[i] == ';' )
							break;
					}
				}
				else
				{
					buffer << '&' << szEntityAmp;
					++i;
				}
				break;
			case '<':
				buffer << '&' << szEntityLt;
				++i;
				break;
			case '>':
				buffer << '&' << szEntityGt;
				++i;
				break;
			case '\"':
				buffer << '&' << szEntityQuot;
				++i;
				break;
			case '\'':
				buffer << '&' << szEntityApos;
				++i;
				break;
			default:
//				if ( chr < 32 || chr > 126 )
//				{
//					// Easy pass at non-alpha/numeric/symbol
//					// 127 is the delete key. Below 32 is symbolic.
//					char buf[8];
//					sprintf( buf, "&#x%02X;", (unsigned int)(chr & 0xff) );
//					buffer << buf;
//					++i;
//				}
//				else
				{
					buffer << char( chr );
					++i;
				}
		}
	}
	Dump();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* GetEntity( const char *p, char *pValue )
{
	const char *phx = "#x";
	// Presume an entity, and pull it out.
	// Ignore the &#x entities.
	if ( (*((unsigned short*)p) == *((unsigned short*)phx)) && *(p + 2) && *(p + 3) ) 
	{
		if ( isalpha(*(p + 2)) ) 
			*pValue = ( tolower( *(p + 2) ) - 'a' + 10 ) * 16;
		else						 
			*pValue = ( *(p + 2) - '0' ) * 16;

		if ( isalpha(*(p + 3)) ) 
			*pValue += ( tolower( *(p + 3) ) - 'a' + 10 );
		else						 
			*pValue += ( *(p + 3) - '0' );

		return p + 5;
	}
	// Now try to match it.
	if ( IsEqualSubstring(szEntityAmp, p) )
	{
		*pValue = '&';
		return p + szEntityAmp.length();
	}
	else if ( IsEqualSubstring(szEntityLt, p) )
	{
		*pValue = '<';
		return p + szEntityLt.length();
	}
	else if ( IsEqualSubstring(szEntityGt, p) )
	{
		*pValue = '>';
		return p + szEntityLt.length();
	}
	else if ( IsEqualSubstring(szEntityQuot, p) )
	{
		*pValue = '\"';
		return p + szEntityQuot.length();
	}
	else if ( IsEqualSubstring(szEntityApos, p) )
	{
		*pValue = '\'';
		return p + szEntityApos.length();
	}
	// So it wasn't an entity, its unrecognized, or something like that.
	*pValue = *( p - 1 );	// Don't put back the last one, since we return it!
	return p;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* ReadName( const char *p, string *pszName )
{
	pszName->clear();
	ASSERT( p );

	// Names start with letters or underscores. After that, they can be letters, underscores, numbers, hyphens, or colons. 
	// (Colons are valid ony for namespaces, but LightXml can't tell namespaces from names.)
	if ( p && *p && ( isalpha((unsigned char) *p) || *p == '_' ) )
	{
		while ( p && *p && ( isalnum((unsigned char ) *p) || *p == '_' || *p == '-' || *p == ':' ) )
		{
			*pszName += *p;
			++p;
		}
		return p;
	}
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* ReadText( string *pszText, const char *pszBegin, const char *pszEnd, 
											const string &szEndTag, const bool bTrimWhiteSpace )
{
	pszText->clear();
	CStringComposer buffer;
	const char *p = pszBegin;
	if ( !bTrimWhiteSpace ) // certain tags always keep whitespace
	{
		// Keep all the white space.
		while ( p && *p && !IsEqualSubstring(szEndTag, p, pszEnd) )
		{
			char c;
			p = GetChar( p, &c );
			buffer << c;
		}
	}
	else
	{
		bool bWhitespace = false;

		// Remove leading white space:
		p = SkipWhiteSpace( p );
		while ( p && *p && !IsEqualSubstring(szEndTag, p, pszEnd) )
		{
			if ( IsWhiteSpace(*p) )
			{
				bWhitespace = true;
				++p;
			}
			else
			{
				// If we've found whitespace, add it before the new character. Any whitespace just becomes a space.
				if ( bWhitespace )
				{
					buffer << ' ';
					bWhitespace = false;
				}
				char c;
				p = GetChar( p, &c );
				buffer << c;
			}
		}
	}
	pszText->insert( pszText->end(), buffer.str(), buffer.str() + buffer.GetSize() );
	return p + szEndTag.length();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}; // end of namespace NLightXml
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
