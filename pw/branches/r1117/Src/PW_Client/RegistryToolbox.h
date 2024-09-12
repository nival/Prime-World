#pragma once
#ifndef REGISTRY_TOOLBOX_H
#define REGISTRY_TOOLBOX_H

#include "stdafx.h"
#include "System/RegistryStorage.h"

//#include <sstream>
#include <string>

const string REGISTRY_REPLAY_EXT = ".pwrp";
const string REGISTRY_APPLICATION_NAME = "PrimeWorld.Replay.v1";
const string REGISTRY_EXT_DESCRIPTION = "PrimeWorld Replay File";

class RegistryExtentionAssociation: public registry::Storage
{
  NI_DECLARE_REFCOUNT_CLASS_1( RegistryExtentionAssociation, registry::Storage );
public:

  RegistryExtentionAssociation(const string&,const string&, const string&);
  virtual ~RegistryExtentionAssociation();

  bool Update(const std::string&, const std::string&);

private:
  bool ReadRegPath( const std::string&, std::string& );
  bool StoreRegParam( const std::string&, const std::string& );

private:
  std::string appClassName;
  std::string appFileExt;
  std::string appClassDesc;

  HKEY hKey;

};


void RegisterReplayFileExtentionAssociation();


#endif//REGISTRY_TOOLBOX_H
