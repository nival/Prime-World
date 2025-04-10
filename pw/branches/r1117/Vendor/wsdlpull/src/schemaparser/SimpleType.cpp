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

#include "schemaparser/SimpleType.h"

//TODO .Need to add checks for validating the occurence of consecutive facets_
namespace Schema {

SimpleType::SimpleType(const std::string&  ns)
  :XSDType(ns),
   isList_(false),
   isUnion_(false),
   uTypes_(0)
{
  setContentModel(Schema::Simple);
  facetId_.clear();

  validFacets_ = new int[XSD_ANYURI + 1];

  //This table maintains a flag which indicates what facets_ are valid  for a simple type
  validFacets_[XSD_STRING] = validFacets_[XSD_NMTOKEN] = validFacets_[XSD_NMTOKENS] =
    validFacets_[XSD_TOKEN] =
    LENGTH | MINLEN | MAXLEN | ENUM | WSP | PATTERN;
  validFacets_[XSD_INTEGER] = validFacets_[XSD_INT] = validFacets_[XSD_UINT] =
    validFacets_[XSD_BYTE] = validFacets_[XSD_POSINT] =
    ENUM | WSP | MAXEX | MINEX | MAXINC | MININC | TOTALDIGITS | FRAC |
    PATTERN;
  validFacets_[XSD_LONG] = validFacets_[XSD_ULONG] = validFacets_[XSD_DECIMAL] =
    validFacets_[XSD_INT];
  validFacets_[XSD_SHORT] = validFacets_[XSD_USHORT] = validFacets_[XSD_INT];
  validFacets_[XSD_FLOAT] = validFacets_[XSD_DOUBLE] =
    ENUM | WSP | MAXEX | MINEX | MAXINC | MININC | PATTERN;
  validFacets_[XSD_BOOLEAN] = WSP | PATTERN;
  validFacets_[XSD_TIME] = validFacets_[XSD_DATETIME] = validFacets_[XSD_DATE] =
    ENUM | WSP | MAXEX | MINEX | MAXINC | MININC | PATTERN;
  validFacets_[XSD_QNAME] = validFacets_[XSD_NCNAME] = validFacets_[XSD_ANYURI] =
    LENGTH | MINLEN | MAXLEN | ENUM | WSP | PATTERN;
  validFacets_[XSD_ANY] = validFacets_[XSD_ANYTYPE] = NONE | PATTERN;
  validFacets_[XSD_BASE64BIN] = validFacets_[XSD_STRING];

  //initialize the union??TODO
  facetValue_.numEnums = 0;

  facets_["length"] = LENGTH;
  facets_["minLength"]= MINLEN;
  facets_["maxLength"]= MAXLEN;
  facets_["enumeration"]= ENUM;
  facets_["whiteSpace"]= WSP;
  facets_["pattern"]= PATTERN;
  facets_["maxInclusive"]= MAXINC;
  facets_["maxExclusive"]= MAXEX;
  facets_[ "minInclusive"]= MININC;
  facets_["minExclusive"]= MINEX;
  facets_["totalDigits"]= TOTALDIGITS;
  facets_["fractionDigits"]= FRAC;
}

SimpleType::~SimpleType() {
  delete[] validFacets_;
}

//This function also sets the facet if valid
bool 
SimpleType::isvalidFacet(std::string facet)
{
  if (getBaseTypeId() == 0){
    error("isValidFacet:Unknown base type");
    return false;
  }
  int facetType=facets_[facet];
  if (validFacets_[getBaseTypeId()] | facetType)
    return true;
  else
    return false;
}


//TODO ..need to add checks to see which facets_ can appear together.
void 
SimpleType::setFacetValue(std::string facet,
			  std::string val)
{
  int num = -1;
  int facetType=facets_[facet];
  switch (facetType)
    {
    case ENUM:
      facetValue_.numEnums++;
      enumValues_.push_back(val);
      break;
    case PATTERN:
      facetValue_.pattern = (const char*) val.c_str();
      break;
    case WSP:
      if (val == "preserve")
	facetValue_.wsp = PRESERVE;

      else if (val == "collapse")
	facetValue_.wsp = COLLAPSE;

      else if (val == "replace")
	facetValue_.wsp = REPLACE;

      else
	error("Invalid facet value for whitespace");
      break;
      //all other facet values are numbers
    default:
      num = XmlUtils::parseInt(val);
      break;
    }

  switch (facetType)
    {
    case MAXEX:
      facetValue_.valRange.maxex = num;
      break;
    case MAXINC:
      facetValue_.valRange.maxinc = num;
      break;
    case MININC:
      facetValue_.valRange.mininc = num;
      break;
    case MINEX:
      facetValue_.valRange.minex = num;
      break;
    case LENGTH:
      facetValue_.length = num;
      break;
    case MINLEN:
      facetValue_.lenRange.minlen = num;
      break;
    case MAXLEN:
      facetValue_.lenRange.maxlen = num;
      break;
    case TOTALDIGITS:
      facetValue_.tot = num;
      break;
    case FRAC:
      facetValue_.frac = num;
      break;
    default:
      break;
    }

  int numFacets_=facetId_.size();
  if(!(numFacets_!=0 && (facetId_[numFacets_ - 1] == ENUM)))
    facetId_.push_back(facetType);
  //In case of  enum the new enum value does not define a new facet
}


bool
SimpleType::isValidInt(int val)const
{
  if (!(getBaseTypeId() == Schema::XSD_INT ||
        getBaseTypeId() == Schema::XSD_INTEGER))
    return false;
  int numdigits = 1, tmp = val;
  bool valid = true;
  while ((tmp = tmp / 10))
    numdigits++;
  for (size_t i = 0; i < facetId_.size() && valid; i++)
    {
      switch (facetId_[i])
        {
	case MAXEX:
	  if (val < facetValue_.valRange.maxex)
	    valid = true;
	  else
	    valid = false;
	  break;
	case MAXINC:
	  if (val <= facetValue_.valRange.maxinc)
	    valid = true;

	  else
	    valid = false;
	  break;
	case MININC:
	  if (val >= facetValue_.valRange.mininc)
	    valid = true;

	  else
	    valid = false;
	  break;
	case MINEX:
	  if (val > facetValue_.valRange.minex)
	    valid = true;

	  else
	    valid = false;
	  break;
	case LENGTH:
	  if (numdigits == facetValue_.length)
	    valid = true;

	  else
	    valid = false;
	  break;
	case MINLEN:
	  if (numdigits >= facetValue_.lenRange.minlen)
	    valid = true;

	  else
	    valid = false;
	  break;
	case MAXLEN:
	  if (numdigits <= facetValue_.lenRange.maxlen)
	    valid = true;

	  else
	    valid = false;
	  break;
	default:
	  valid = false;
        }
    }
  return valid;
}


bool
SimpleType::isValidFloat(float val)const
{

  //TODO
  return true;
}


bool
SimpleType::isValidString(std::string val)const
{
  int strlen = val.length();
  bool valid = true;
  std::list < std::string >::const_iterator pEnums;
  for (size_t i = 0; i < facetId_.size(); i++)
    {
      switch (facetId_[i])
        {
	case LENGTH:
	  if (strlen == facetValue_.length)
	    valid = true;

	  else
	    valid = false;
	  break;
	case MINLEN:
	  if (strlen >= facetValue_.lenRange.minlen)
	    valid = true;

	  else
	    valid = false;
	  break;
	case MAXLEN:
	  if (strlen <= facetValue_.lenRange.maxlen)
	    valid = true;

	  else
	    valid = false;
	  break;
	case ENUM:
	  {
	    valid=false;
	    for (pEnums = enumValues_.begin();
		 pEnums != enumValues_.end();
		 pEnums++){

	      if (*pEnums == val)
		valid = true;
	    }
	    break;
	  }
	case PATTERN:
	  valid = true;                     //TODO
	  break;
	default:
	  valid = true;
        }
    }
  return valid;
}


/*This function returns the facet values of the requested facet type
  if the type is restricted by it.
  For enum it returns(via val*) a ptr to std::list<std::string>.
  For all other facets_ related to length,its returns(via val*) an int pointer
  For inclusive and exclusive facets it returns (via val*) ptr to the value
  for example
  int * minex=0;
  simpleType.getFacetValue(SimpleType::MAXINC,minex);
 */

//TODO add cases to return pointers to other facet values
bool 
SimpleType::getFacetValue(int facet, void *& val)
{
  val = 0;
  bool isFacetPresent = false;
  for (size_t i = 0;
       i < facetId_.size() && !isFacetPresent;
       i++)
    isFacetPresent = (facetId_[i] == facet);

  if (!isFacetPresent)
    return false;
  switch (facet)
    {
    case ENUM:
      val = (void *) &(enumValues_);
      return true;
      break;
	case MAXINC:
		val =  &(facetValue_.valRange.maxinc);
		return true;
		break;
	case MAXEX:
		val = (void*) &(facetValue_.valRange.maxex);
		return true;
		break;
	case MININC:
		val = (void*) &(facetValue_.valRange.mininc);
		return true;
		break;
	case MINEX:
		val = (void*) &(facetValue_.valRange.minex);
		return true;
		break;
	case LENGTH:
		val = (void*) &(facetValue_.length);
		return true;
		break;
	case MINLEN:
		val = (void*) &(facetValue_.lenRange.minlen);
		return true;
		break;
	case MAXLEN:
		val = (void*) &(facetValue_.lenRange.minlen);
		return true;
		break;
	case PATTERN:
        val = (void*) &(facetValue_.pattern);
		return true;
		break;
	case TOTALDIGITS:
		val = (void*) &(facetValue_.tot);
		return true;
		break;
	case FRAC:

    default:
      val = 0;
      return false;
    }
}


void SimpleType::error(std::string msg)
{
  msg += "SimpleType::error()";
  SchemaParserException spe(msg);
  throw spe;
  return;
}
}
