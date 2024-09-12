// Game logic cheat commands and other stuff

#pragma once

#ifndef _SHIPPING

namespace NGameX
{

struct CheatData
{
  ZDATA;
  CPtr<NWorld::PFBaseHero> cheater;
  CPtr<NWorld::PFBaseUnit> selectedObject;
  CPtr<NWorld::PFBaseUnit> pickedObject;
  CVec3 pickedPosition;
  int   localPlayerId;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&cheater); f.Add(3,&selectedObject); f.Add(4,&pickedObject); f.Add(5,&pickedPosition); f.Add(6,&localPlayerId); return 0; }
  CheatData() : localPlayerId(0) {}
};

void CreateCheatCmd(const char *cmdName);
void CreateCheatCmd(const char *cmdName, vector<wstring> const& cmdParams);
void CreateCheatCmd(const char *cmdName, const CheatData& data);
void CreateCheatCmd(const char *cmdName, string const& param, const CheatData& data);
void CreateCheatCmd(const char *cmdName, string const& param1, string const& param2, const CheatData& data);

}

#endif // #ifndef _SHIPPING
