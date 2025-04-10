/* 
 * wsdlpull - A C++ parser  for WSDL  (Web services description language)
 * Copyright (C) 2005-2007 Vivek Krishna
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *
 */
#ifndef _SCHEMAPARSERH
#define _SCHEMAPARSERH


#include "xmlpull/wsdlpull_export.h"
#include "xmlpull/XmlPullParser.h"
#include "xmlpull/XmlPullParserException.h"
#include "schemaparser/Schema.h"
#include "schemaparser/SchemaParserException.h"
#include "schemaparser/Group.h"
#include "schemaparser/Element.h"
#include "schemaparser/Constraint.h"
#include "schemaparser/AttributeGroup.h"
#include "schemaparser/ComplexType.h"
#include "schemaparser/SimpleType.h"
#include "schemaparser/TypesTable.h"


namespace Schema {

//class Schema Parser
class WSDLPULL_EXPORT SchemaParser
{
 public:

  /**
   * typedefs 
   */
  //@{
  typedef std::list<Element> ElementList;
  typedef std::list<Attribute> AttributeList;
  typedef std::list<Group> GroupList;
  typedef std::list<AttributeGroup*> AttributeGroupList;
  typedef std::list<Constraint*> ConstraintList;
  typedef std::list<Qname>  QNameList;
  typedef std::list < const XSDType *> ConstTypeList;

    typedef struct
    {
      SchemaParser* sParser;
      std::string ns;
    } ImportedSchema ;

  //@}
  
  /** @name Constructors and Destructors */
  //@{

  /**
   * The constructor for SchemaParser
   * @param the URI schema definition file.
   * @param target namespace
   * @param output stream for any error outputs
   * @param confPath The path where schema files for soap and other namespaces are located.
   *        This is required only if you have stored them other than src/schemas on windows.
   *        On *nix it is almost never required if you install using the make install
   */
  SchemaParser(const std::string&  Uri, std::string tns = "", 
	       std::ostream & log = std::cout,const std::string & confPath="");

  /**
   * The constructor for SchemaParser
   * @param XmlPullParser instance for the schema definition file.
   * @param target namespace
   * @param output stream for any error outputs
   * @param confPath The path where schema files for soap and other namespaces are located.
   *        This is required only if you have stored them other than src/schemas on windows.
   *        On *nix it is almost never required if you install using the make install
   */
  SchemaParser(XmlPullParser * parser, std::string tns = "",
	       std::ostream & log = std::cout,const std::string & confPath="");

  ~SchemaParser();

  //@}

  /** @name methods used for parsing */
  //@{
  /**
   * parseSchemaTag
   * @return true if parsing was successful ,false otherwise
   */
  bool parseSchemaTag();

  //@}

  /** @name Various Getter methods*/
  //@{

  /**
   * getType
   * @param Qname refering to the type
   * @return pointer to the type
   * @checkImports set this to false to search for types defined in this schema
   */
  const XSDType *getType(const Qname & type, bool  checkImports = true) ;

  /**
   * @param the types unique id
   * @return pointer to the type
   */
  const XSDType *getType(int id) const;

  /**
    * @param the types unique id
    * @param the namespace of the type
    * @return pointer to the type
    */
    const XSDType *getType(int id, std::string &nameSpace);

    /**
   * @return a std::list of all types defined in the schema
   *         including anonymous types
   *         caller *MUST* free the std::list but not the std::list members
   */
  ConstTypeList *getAllTypes() const;

  /**
   * @param Qname of the element
   * @return  pointer to a globally defined element in the schema 
   * @checkImports set this to false to search for elements defined in this schema
   */
  const Element *getElement(const Qname & element,bool checkImports=true) const;
  
  /**
   *
   * returns the std::list of all the  global elements in the schema
   * @param void
   * @return std::list<Element>
   */
  const ElementList&  getElements() const;

  /**
   * @return number of globally defined elements in the schema
   */
  int getNumElements() const;

  /**
   * getAttribute
   * @param Qname of the attribute
   * @return  pointer to a globally defined attribute in the schema
   */
  Attribute *getAttribute(const Qname & attribute) ;

  /**
   *
   * returns a std::list of global attributes in the schema
   * @param void
   * @return std::list<Attribute>
   */
  const AttributeList&  getAttributes()const;
  
  /**
   * @return number of globally defined attributes in the schema
   */
  int getNumAttributes() const;


  /**
   * @return target namespace of the schema document
   */
  std::string getNamespace(void) const;

  /**
   * @return number of types defined in the schema (includes anonymous types)
   */
  int getNumTypes() const;


  /**
   * getTypeId :Search for a type ,if not present create one,checks in imported types as well
   * @param Qname of the type
   * @param bool:create
   * @return type id
   */
  int getTypeId(const Qname &, bool create = false);

  /**
   * isBasicType
   * @param unique type identifier
   * @return  true if its a basic schema type false otherwise
   */
  bool isBasicType(int sType) const;

  /**
   * getBasicContentType
   *
   * If the type has a simple content model then this method returns
   * the basic schema type which defines its contents
   * For example calling on a type like below would return Schema::STRING
   
   <xsd:complexType>
   <xsd:simpleContent> 
   <xsd:extension base = "xsd:std::string">
   <xsd:attribute name = "lang" type = "xsd:std::string"/>
   </xsd:extension>
   </xsd:simpleContent> 
   </xsd:complexType>
   *    
   * 
   * @param unique type identifier 
   * @return  type id of the basic type from which this type is derived
   *          or  if the typeId is one of the atomic types,the same value is returned
   *          If the typeId is a complex type Schema::XSD_INVALID is returned
   *
   */
  int getBasicContentType(int typeId)const;
  
  /**
   * getGroup
   * @param unique type identifier
   * @return  Group*
   */
  Group* getGroup(const Qname& name);
  
  /**
   * getAttributeGroup
   * @param unique type identifier
   * @return  AttributeGroup*
   */
  AttributeGroup* getAttributeGroup(const Qname& name);
 
  //@}

  /** @name Methods for handling Imports*/
  //@{
  /**
   *  isImported 
   *  true if the schema parser imports a namespace
   */
  bool isImported(const std::string & ns)const;
  const SchemaParser* getImportedSchemaParser(const std::string & ns)const;
  /**
   * addImport .Instructs the schema parser to import a namespace
   * @param namespace of the schema
   * @param (optional)schemaLocation .If this is not passed ,schema file is not processed
   *                                  but any refernces to the namespace are not flagged as errors
   * @return true if the schema was succesfully imported.If location is not passed always returns true
   */
  bool addImport(std::string ns, std::string location="");
  /**
   * addImport . imports the namespace of the schemaparser
   * @param  SchemaParser instance which has parsed the namespace
   * @return true if the schema was succesfully imported .
   */
  bool addImport(SchemaParser* sp);
  /*
   * addImports .To add an array of schema parsers for imported schemas
   * @param array of schema parsers
   * @param number of schema parsers added
   */
  bool addImports(const std::vector<SchemaParser *>& schemaParsers); //to be removed soon

  //@}


  /** @name Miscellaneous Methods */
  //@{
  /**
   * finalize : tries to match unresolved types and references with imported schemas
   *            you *must* call this to ensure successful type resolution
   * @return  true if all type references are resolved ,false otherwise
   */
  bool finalize(void);

  /** 
   * setWarningLevel
   * default is 0 .
   * 1 is wanrning level 
   * 2 is information level //quite verbose
   */
  void setWarningLevel(int l);
  /*
   * path to the directory where the config file for handling 
   * imports is located
   */
  void setSchemaPath(const std::string& s);

  /* Set the path to the uri from where references to  imported schemas
   * may be resolved. One level up the actual location.
   * Example if you set uri as "tempuri.org" ,a reference to imported schema location "x.xsd"
   * will be mapped to "tempuri.org/x.xsd"
   */ 
  void setUri(const std::string& u );
  /**
   * getTypeName()
   * return the type name given the id
   */
  std::string getTypeName(Schema::Type t)const;
  TypesTable *getTypesTable();
  const SchemaParser *getImportedSchema(std::string &nameSpace);
  std::vector<ImportedSchema> &getImportedSchemas();

  /** getVersion()
   * return the schema version
   */
  std::string getVersion()const;  

  bool getElementQualified() const;
  std::string getTnsPrefix( void) const;

#ifdef LOGGING
  /**
   * for logging purposes
   */
  void print(std::ostream &) ;
#endif
  //@}

 private:
  //This function parses global elements
  Element  parseElement(bool & fwdRef);
  //This function parses global attributes
  Attribute parseAttribute(bool & fwdRef);
  void init();

  //This  function parses <annotation> tag
  void parseAnnotation();
  ComplexType *parseComplexType();
  SimpleType *parseSimpleType();


  Element addAny(ContentModel* cm);
  Group parseGroup(ContentModel* cm=0);
  Constraint* parseConstraint(Schema::ConstraintType cstr);
  AttributeGroup* parseAttributeGroup(ComplexType* cType=0);
  Attribute addAnyAttribute(ComplexType * cType);

  void parseRestriction(SimpleType * st,ComplexType * ct=0);
  void parseComplexContent(ComplexType * ct);
  void parseSimpleContent(ComplexType * ct);

  void parseContent(ContentModel * cm);
  bool parseImport(void);
  bool parseInclude();
  bool parseSchema(std::string tag="schema");
  bool parseRedefine();
  int checkImport(std::string nsp)const;
  void copyImports(SchemaParser * sp);
  void resolveForwardElementRefs();
  void resolveForwardAttributeRefs();
  bool& shouldResolve();
  bool makeListFromSoapArray (ComplexType * ct);

  std::string fname_;
  std::string tnsUri_;
  std::string tnsPrefix_;
  std::string version_;
  XmlPullParser * xParser_;
  bool elementQualified_;
  bool attributeQualified_;
  bool deleteXmlParser_;
  bool resolveFwdRefs_;
  TypesTable typesTable_;
  std::ifstream xmlStream_;
  ElementList lElems_;
  AttributeList lAttributes_;
  GroupList lGroups_;
  AttributeGroupList  lAttributeGroups_;
  ConstraintList  constraints_;
  QNameList  lForwardElemRefs_;
  QNameList lForwardAttributeRefs_;
  
  std::vector<ImportedSchema> importedSchemas_;  
  void error(std::string, int level = 0);
  int level_;//warning level
  std::ostream & logFile_;
  std::string confPath_;
  std::string uri_; //The uri to use to resolve imports.1 level up the location of the schema file
};


inline
bool &
SchemaParser::shouldResolve()
{
  return resolveFwdRefs_;
  
}

inline
const SchemaParser::ElementList&
SchemaParser::getElements() const
{
  return lElems_;
}
  
inline
const SchemaParser::AttributeList&
SchemaParser::getAttributes() const
{
  return lAttributes_;
}

inline
void
SchemaParser::setWarningLevel(int l)
{
  level_ = l;
}
inline
bool 
SchemaParser::isImported(const std::string & ns)const
{
  return checkImport(ns) != -1;
}
inline
const SchemaParser*
SchemaParser::getImportedSchemaParser(const std::string & ns)const
{
  int i= checkImport(ns);
  if (i == -1 )
    return 0;

  return importedSchemas_[i].sParser;
}

inline
void
SchemaParser::setSchemaPath(const std::string& s)
{
  confPath_ = s;
}

inline
void
SchemaParser::setUri(const std::string& s)
{
  uri_ = s;
}

inline
TypesTable*
SchemaParser::getTypesTable() 
{
  return &typesTable_;
}

inline
std::vector<SchemaParser::ImportedSchema>&
SchemaParser::getImportedSchemas() 
{
  return importedSchemas_;
}

inline
std::string
SchemaParser::getVersion()const
{
  return version_;
}

inline
bool
SchemaParser::getElementQualified() const
{
  return elementQualified_ ;
}

inline

std::string
SchemaParser::getTnsPrefix( void) const
{
  return tnsPrefix_;
}

}
#endif                                            /*  */


