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
#ifndef _SCHEMAVALIDATORH
#define _SCHEMAVALIDATORH

#include "xmlpull/wsdlpull_export.h"
#include "xmlpull/XmlSerializer.h"
#include "schemaparser/SchemaParser.h"
#include "schemaparser/SchemaParserException.h"
#include "schemaparser/TypeContainer.h"


namespace Schema {

//class for validating a schema instance
class WSDLPULL_EXPORT SchemaValidator
{
 public:
  /** @name Constructors and Destructors */
  //@{
  /**
   * The constructor for SchemaValidator
   * @param pointer to the schema parser instance for the schema
   * @param output stream to write generated instances
   */
  SchemaValidator(const SchemaParser * sp,
		  std::ostream & os = std::cout);
  ~SchemaValidator();

  //@}

  /** @name methods for validating schema instance*/
  //@{
  /**
   * @name validate 
   * @brief This is the main function to validate any type with its instance
   * @param  XmlPullParser instance of the xml stream containing the
   * instance of the schema type
   * @param pointer to the type whose instance must be validated
   * @param type container to be used (can be null)
   * @return type container containing an instance of the schema type
   */
  
  TypeContainer *validate(XmlPullParser * xpp, int typeId,
                          TypeContainer * ipTc = 0);
  
  TypeContainer *validate(const std::string & val , int typeId,
                          TypeContainer * ipTc = 0, XmlPullParser * xpp = 0); //for simple types
  TypeContainer * validate(void* value ,int typeId,
                           TypeContainer * ipTc = 0, XmlPullParser * xpp = 0);
  //@}

  /** @name methods for generating a schema instance*/
  //@{
  /**
   * @name instance
   * @brief This method generates instance of a type
   * @param The tag name of the root element
   * @param type id of the element

  */
  bool instance(const std::string& tag,
		Schema::Type type_id);

  //@}

 private:
  
  TypeContainer* validateContentModel(XmlPullParser * xpp, 
                                      ContentModel* cm,
                                      TypeContainer * ipTc,
                                      const std::string & elemName,
				      bool nested=false,
				      TypeContainer* btCnt=0);//base contentModel
  
  void extractSimpleType(const std::string & val, int basetype,
                         TypeContainer * ipTc, const SimpleType * st,
                         XmlPullParser * xpp);
  bool    validateListOrUnion(const SimpleType* st,
                           const std::string &val, XmlPullParser * xpp);

  bool  findElement(ContentModel::ContentsIterator start, 
                    ContentModel::ContentsIterator end,
                    std::string name, 
                    ContentModel::ContentsIterator & found);
  bool checkAttributeOccurence(const ComplexType* ct ,XmlPullParser* xpp);
  void instanceCM(ContentModel *cm);
  void error(const std::string & , XmlPullParser* xpp=0);
  bool instance1(const std::string& tag,	Schema::Type type_id);

  XmlSerializer * xmlStream_ ;
  std::ostream &ostr_;
  const SchemaParser *sParser_;

};
}
#endif
