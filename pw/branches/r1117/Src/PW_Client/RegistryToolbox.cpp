
#include "stdafx.h"
#include "RegistryToolbox.h"
#include "Version.h"

RegistryExtentionAssociation::RegistryExtentionAssociation(const string& appClassName,const string& ext,const string& desc)
:registry::Storage(), appClassName(appClassName.c_str()), appFileExt(ext.c_str()), appClassDesc(desc.c_str()){}

RegistryExtentionAssociation::~RegistryExtentionAssociation()
{
  CloseKey(&hKey);
}

bool RegistryExtentionAssociation::Update( const std::string& cmdParam, const std::string& iconParam )
{
  const std::string rootPath("Software\\Classes\\");
  std::string path = rootPath + appFileExt;

  std::string value;

  bool result = ReadRegPath(path, value);
  bool rewriteMode = false;

  if (!result || value.compare(appClassName) != 0)
  {
    result = StoreRegParam(path, appClassName);
    NI_VERIFY( result, "Could not open registry key", return false);

	  rewriteMode = true;
  }

  path = rootPath + appClassName + std::string("\\shell\\open\\command");
  result = ReadRegPath(path, value);

  if(value.compare(cmdParam) != 0)
    rewriteMode = true;

  if ( rewriteMode )
  {
    std::string ext_desc_path = rootPath + appClassName;

    result = StoreRegParam(ext_desc_path, appClassDesc);
    NI_VERIFY( result, "Could not open registry key", return false);

    result = StoreRegParam(path, cmdParam);
    NI_VERIFY( result, "Could not open registry key", return false);

    std::string icon_path = ext_desc_path + std::string("\\DefaultIcon");

    result = StoreRegParam(icon_path, iconParam);
    NI_VERIFY( result, "Could not open registry key", return false);
  }

  return true;
}

bool RegistryExtentionAssociation::ReadRegPath( const std::string& path, std::string& value )
{
  value.clear();

  bool result = OpenSubKey(path.c_str(), &hKey, false, true);
  NI_VERIFY( result, "Could not open registry key", return false);

  DWORD type = 0;
  DWORD size = 0;
  LSTATUS code = ::RegQueryValueEx(hKey, NULL, 0, &type, NULL, &size);
  if ((code != ERROR_SUCCESS) || (type != REG_SZ) || (size < 1))
  {
    return false;
  }

  value.resize(size - 1);

  code = ::RegQueryValueEx(hKey, NULL, 0, NULL, (LPBYTE)value.c_str(), &size);

  if ((code != ERROR_SUCCESS) || (type != REG_SZ))
  {
    return false;
  }

  CloseKey(&hKey);
  return true;
}

bool RegistryExtentionAssociation::StoreRegParam( const std::string& path, const std::string& value )
{
  bool result = OpenSubKey(path.c_str(), &hKey, false, true);
  NI_VERIFY( result, "Could not open registry key", return false);

  LSTATUS code = ::RegSetValueEx(hKey, NULL, 0, REG_SZ, (BYTE *)value.c_str(), strlen(value.c_str()) + 1);
  NI_VERIFY( code == EXIT_SUCCESS, "Could not set registry value", return false);

  CloseKey(&hKey);
  return true;
}

///////////////////////////////////////////////////////////////////////////////

//NI_DEFINE_REFCOUNT(RegistryExtentionAssociation)

///////////////////////////////////////////////////////////////////////////////

void RegisterReplayFileExtentionAssociation()
{
  string appPath = NFile::GetBaseDir() + "Bin\\" + string(PRODUCT_EXECUTABLE);
  string appRunPath = string("\"") + appPath + string("\" \"%1\"");
  string appIconPath = appPath + string(",0");

  Weak<RegistryExtentionAssociation> rea =
    new RegistryExtentionAssociation(REGISTRY_APPLICATION_NAME, REGISTRY_REPLAY_EXT, REGISTRY_EXT_DESCRIPTION);
  rea->Update(appRunPath.c_str(), appIconPath.c_str());

}
