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
#ifndef _ANNOTATIONH
#define _ANNOTATIONH

#include <string>
#include <vector>

namespace Schema {

  typedef struct 
  {
    public:
    std::string source;
    std::string appinfo;
  } Appinfo;

  typedef struct 
  {
    public:
    std::string source;
    std::string lang;
    std::string documentation;
  } Documentation;


  class  WSDLPULL_EXPORT Annotation 
  {
  public:
    Annotation(void);
    void addAppinfo(Appinfo appinfo);
    void addDocumentation(Documentation documentation);
    std::vector<Appinfo> getAppinfos();
    std::vector<Documentation> getDocumentations();

  private:
    std::vector<Appinfo> appinfos_;
    std::vector<Documentation> documentations_;
  };

inline
Annotation::Annotation()
{
}

inline
void Annotation::addAppinfo(Schema::Appinfo appinfo)
{
  appinfos_.push_back(appinfo);
}

inline
void Annotation::addDocumentation(Schema::Documentation documentation)
{
  documentations_.push_back(documentation);
}

inline
std::vector<Schema::Appinfo> Annotation::getAppinfos() 
{
  return appinfos_;
}

inline
std::vector<Schema::Documentation> Annotation::getDocumentations()
{
  return documentations_;
}
}
#endif
