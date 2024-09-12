#pragma once

#include "IConfigManager.h"

namespace Render
{
// System-side Config Manager interface
class NOVTABLE ConfigManager
{
public:
  virtual HRESULT CheckDeviceCaps(IDirect3DDevice9* _pDevice, bool _checkFormats = true) = 0;
  // SetPerfomanceLevel - level 0 is of most quality
  virtual void SetPerfomanceLevel(IConfigManager::ResourceType _type, UINT _level) = 0;
  // Get adapter video memory in MB; _pAvailableVidMem shows total video memory minus driver-reserved memory
  virtual void GetVidMem(HMONITOR _hMonitor, UINT* _pAvailableVidMem, UINT* _pAdapterRAM) = 0;

  virtual DWORD GetAllFeatures() const = 0; // return all flags at once

protected:
  ConfigManager(void)  {}
  ~ConfigManager(void) {}
};

ConfigManager* GetConfigManager();

}; // namespace Render