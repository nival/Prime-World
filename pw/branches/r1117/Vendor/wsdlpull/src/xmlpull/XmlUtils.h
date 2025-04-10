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
 */

#ifndef _UTILSH
#define _UTILSH

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#ifdef HAVE_CONFIG_H //
#include <config.h>
#endif   
#include "wsdlpull_export.h"


//put all miscellaneous  utiliy functions here
namespace XmlUtils {
  std::string getSuffix();
  std::string getFileName(std::string);
  std::string creUriFile(std::string);
  void delUriFiles();
  void MutexInit();
  void MutexLock();
  void MutexUnlock();
  int parseInt (std::string s, int radix = 10);
  std::ostream & dbsp (std::ostream & str);
  std::ostream & blk (std::ostream & str);
  bool WSDLPULL_EXPORT fetchUri(std::string uri,std::string & path);
  std::string WSDLPULL_EXPORT acceptSecretKey(const std::string& field);
#ifdef _WIN32
  void winPost(const std::string uri,const std::string username,
               const std::string password,const std::string data,
               std::string action,char* &results);
#endif
  //network related stuff 
  bool WSDLPULL_EXPORT getProxy ();
  void WSDLPULL_EXPORT setProxy (const bool bProxy);

  std::string WSDLPULL_EXPORT getProxyHost ();
  void WSDLPULL_EXPORT setProxyHost (const std::string& sProxyHost);

  std::string WSDLPULL_EXPORT getProxyUser ();
  void WSDLPULL_EXPORT setProxyUser (const std::string& sProxyUser);

  std::string WSDLPULL_EXPORT getProxyPass ();
  void WSDLPULL_EXPORT setProxyPass (const std::string& sProxyPass);
}
#endif                                            /*  */
