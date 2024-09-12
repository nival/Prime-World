#ifndef GAMEMENUINTERFACES_H_INCLUDED
#define GAMEMENUINTERFACES_H_INCLUDED

namespace NGameX
{ 

_interface IGameMenuMinigameActions : public IObjectBase
{
public:
  virtual bool NeedToShowMinigameMenuItems() = 0;
  virtual bool OnGameMenuEscapeButton() = 0;
  virtual void OnGameMenuPopup() = 0;
  virtual void GameMenuClosed() = 0;
  virtual void AbortMinigameLevel() = 0;
};

} // End of namespace NGameX

#endif //GAMEMENUINTERFACES_H_INCLUDED
