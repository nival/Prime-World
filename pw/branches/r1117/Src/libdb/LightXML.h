#ifndef __LIGHTXml_H__
#define __LIGHTXml_H__
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "LightXMLUtils.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef NLightXml::CWriteStream NLightXml_STREAM;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NLightXml
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** base class for all Xml elements
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CXmlBase
{
public:
	virtual ~CXmlBase() {	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** An attribute is a name-value pair. Elements have an arbitrary number of attributes, each with a unique name.
// ** The attributes are not Nodes, since they are not part of the Xml Document Object Model. There are other
// ** suggested ways to look at this problem.
// ** Attributes have a parent
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CXmlAttribute : public CXmlBase
{
	friend class CXmlElement;	// only element can set attribute value directly
	//
	string szName;										// name
	string szValue;									// value
	mutable unsigned long dwHashCode;							// internal hash code value (for fast search)
	//
	void SetValue( const string &_szValue ) { szValue = _szValue; }
	unsigned long GetHashCode() const 
	{
		if ( dwHashCode == 0 ) 
			dwHashCode = hash<string>()( szName );
		return dwHashCode;
	}
public:
	CXmlAttribute() : dwHashCode( 0 ) {	}
	CXmlAttribute( const string &_szName, const string &_szValue )
		: szName( _szName ), szValue( _szValue ), dwHashCode( 0 ) {	}
	virtual ~CXmlAttribute() {	}
	//
	bool operator==( const CXmlAttribute &attr ) const
	{
		return GetHashCode() == attr.GetHashCode() ? szName == attr.szName : false;
	}
	bool operator<( const CXmlAttribute &attr ) const
	{
		return GetHashCode() != attr.GetHashCode() ? szName < attr.szName : false;
	}
	//
	const char* Parse( const char *pszBegin, const char *pszEnd );
	void Store( NLightXml_STREAM &stream ) const;
	// set/get value
	void Set( const string &_szValue ) { szValue = _szValue; }
	void Set( const CToStringConvertor &value ) { szValue = value; }
	const string& GetValue() const { return szValue; }
	const string& GetName() const { return szName; }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** The parent class for everything in the Document Object Model. (Except for attributes, which are contained in elements.)
// ** Nodes have siblings, a parent, and children. A node can be in a document, or stand on its own. The type of a Node
// ** can be queried, and it can be cast to its more defined type.
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CXmlNode : public CXmlBase
{
	DUMMY_ASSIGNMENT( CXmlNode );
public:
	enum EType
	{
		DOCUMENT,
		DECLARATION,
		COMMENT,
		UNKNOWN,
		ELEMENT,
		TEXT
	};
private:
	const EType eType;										// node type (to avoid dynamic_cast)
	unsigned long dwHashCode;											// hash code for this node by value (== 0 if empty)
protected:
	string szValue;									// node value
public:
	CXmlNode( const EType _eType );
	virtual ~CXmlNode();
	//
	EType GetType() const { return eType; }
	//
	virtual const char* Parse( const char *pszBegin, const char *pszEnd ) = 0;
	virtual void Store( NLightXml_STREAM &stream, const string &szIndention ) const = 0;
	//
	const string& GetValue() const { return szValue; }
	void SetValue( const string &_szValue ) { szValue = _szValue; dwHashCode = 0; }
	bool IsMatch( const string &szMatchValue, const unsigned long dwMatchHashCode )
	{
		if ( dwHashCode == 0 ) 
			dwHashCode = hash<string>()( szValue );
		if ( dwHashCode == dwMatchHashCode ) 
			return szMatchValue == szValue;
		else
			return false;
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** The parent class for document and element in the Document Object Model.
// ** Multinodes have children. A node can be in a document or user element. 
// ** 
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CXmlMultiNode : public CXmlNode
{
	typedef vector<CXmlNode*> CNodesList;

	DUMMY_ASSIGNMENT( CXmlMultiNode );
public:
	typedef CNodesList::iterator iterator;
	typedef CNodesList::const_iterator const_iterator;
private:
	CNodesList children;									// children nodes
	mutable const_iterator posOptimal;		// optimal search position (for fast incremental search)
protected:
	void ResetOptimalPos() const { posOptimal = children.begin(); }
	CXmlNode* Identify( const char *pszBegin, const char *pszEnd );
public:
	CXmlMultiNode( const CXmlNode::EType _eType ) 
		: CXmlNode( _eType ) {	}
	virtual ~CXmlMultiNode();
	//
	virtual void Store( NLightXml_STREAM &stream, const string &szIndention ) const;
	//
	iterator begin() { return children.begin(); }
	iterator end() { return children.end(); }
	const_iterator begin() const { return children.begin(); }
	const_iterator end() const { return children.end(); }
	//
	void AddChild( CXmlNode *pNode ) { children.push_back( pNode ); ResetOptimalPos(); }
	bool HasChildren() const { return !children.empty(); }
	CXmlNode* GetChild( const int nIndex ) const { return nIndex < children.size() ? children[nIndex] : 0; }
	CXmlNode* GetChildFast( const int nIndex ) const { return children[nIndex]; }
	int CountChildren() const { return children.size(); }
	CXmlNode* FindChild( const string &_szValue ) const;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** comment
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CXmlComment : public CXmlNode
{
	CXmlComment &operator=( const CXmlComment & ) { return *this; }
public:
	CXmlComment();
	virtual ~CXmlComment();
	//
	virtual const char* Parse( const char *pszBegin, const char *pszEnd );
	virtual void Store( NLightXml_STREAM &stream, const string &szIndention ) const;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** Xml text. Contained in an element.
// **
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CXmlText : public CXmlNode
{
	DUMMY_ASSIGNMENT( CXmlText );
public:
	CXmlText();
	virtual ~CXmlText();
	//
	virtual const char* Parse( const char *pszBegin, const char *pszEnd );
	virtual void Store( NLightXml_STREAM &stream, const string &szIndention ) const;
	//
	bool IsBlank() const
	{
		for ( string::const_iterator it = szValue.begin(); it != szValue.end(); ++it )
		{
			if ( !isspace( (unsigned char)(*it) ) )
				return false;
		}
		return true;
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** In correct Xml the declaration is the first entry in the file.
// **		<?xml version="1.0" standalone="yes"?>
// ** LigntXml will happily read or write files without a declaration, however.
// ** There are 3 possible attributes to the declaration: version, encoding, and standalone.
// ** Note: In this version of the code, the attributes are handled as special cases, not generic attributes, simply
// ** because there can only be at most 3 and they are always the same.
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CXmlDeclaration : public CXmlNode
{
	string szVersion;
	string szStandalone;
	string szEncoding;

	DUMMY_ASSIGNMENT( CXmlDeclaration );
public:
	CXmlDeclaration();
	virtual ~CXmlDeclaration();
	//
	virtual const char* Parse( const char *pszBegin, const char *pszEnd );
	virtual void Store( NLightXml_STREAM &stream, const string &szIndention ) const;
	//
	void SetVersion( const string &szValue ) { szVersion = szValue; }
	const string& GetVersion() const { return szVersion; }
	void SetStandalone( const string &szValue ) { szStandalone = szValue; }
	const string& GetStandalone() const { return szStandalone; }
	void SetEncoding( const string &szValue ) { szEncoding = szValue; }
	const string& GetEncoding() const { return szEncoding; }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** Any tag that LightXml doesn't recognize is save as an unknown. It is a tag of text, but should not be modified.
// ** It will be written back to the Xml, unchanged, when the file is saved.
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CXmlUnknown : public CXmlNode
{
	DUMMY_ASSIGNMENT( CXmlUnknown );
public:
	CXmlUnknown();
	virtual ~CXmlUnknown();
	//
	virtual const char* Parse( const char *pszBegin, const char *pszEnd );
	virtual void Store( NLightXml_STREAM &stream, const string &szIndention ) const;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** The element is a container class. It has a value, the element name, 
// ** and can contain other elements, text, comments, and unknowns.
// ** Elements also contain an arbitrary number of attributes.
// **
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CXmlElement : public CXmlMultiNode
{
	typedef list<CXmlAttribute> CAttributesList;
	typedef hash_map<string, CXmlAttribute*> CAttributesMap;
	CAttributesList attributes;						// attributes
	CAttributesMap attrmap;								//
	string szText;										// text of this element
	//
	const char* ReadValue( const char *pszBegin, const char *pszEnd );
	void SetAttributeLocal( const string &szName, const char *szValue );

	DUMMY_ASSIGNMENT( CXmlElement );
public:
	CXmlElement();
	virtual ~CXmlElement();
	//
	virtual const char* Parse( const char *pszBegin, const char *pszEnd );
	virtual void Store( NLightXml_STREAM &stream, const string &szIndention ) const;
	// attributes
	void SetAttribute( const CXmlAttribute &attribute );
	void SetAttribute( const string &szName, const CToStringConvertor &value );
	void SetAttribute( const string &szName, const string &szValue ) { SetAttributeLocal( szName, szValue.c_str() ); }
	const CXmlAttribute* GetAttribute( const string &szName ) const;
	void RemoveAttribute( const string &szName );
	const list<CXmlAttribute> &GetAttributesList() const { return attributes; }
	// text
	const string& GetText() const { return szText; }
	void SetText( const string &_szText ) { szText = _szText; }
	void RemoveText() { szText.clear(); } 
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ************************************************************************************************************************ //
// **
// ** Always the top level node. A document binds together all the Xml pieces. It can be saved, loaded and modified
// ** 
// ** 
// **
// ************************************************************************************************************************ //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CXmlDocument : public CXmlMultiNode
{
	DUMMY_ASSIGNMENT( CXmlDocument );
public:
	CXmlDocument();
	virtual ~CXmlDocument();
	//
	virtual const char* Parse( const char *pszBegin, const char *pszEnd );
	virtual void Store( NLightXml_STREAM &stream, const string &szIndention = "" ) const;
	//
	CXmlElement *GetRootElement();
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}; // end of namespace NLightXml
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __LIGHTXml_H__
