#pragma once

namespace MMgc
{
  class GC;
}

namespace gameswf
{
  struct render_handler;
}

namespace flash
{

class Player
{
public:
  static Player* Get();

private:
  Player();
  ~Player();
};

bool  InitializeFlash();
bool  ReleaseFlash();

}