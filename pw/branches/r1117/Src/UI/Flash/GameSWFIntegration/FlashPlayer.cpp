#include "TamarinPCH.h"
#include "FlashPlayer.h"

namespace flash
{

Player::Player()
{
  MMgc::GCHeap::EnterLockInit();
  MMgc::GCHeapConfig conf;
  MMgc::GCHeap::Init(conf);
}

Player::~Player()
{
  MMgc::GCHeap::Destroy();
  MMgc::GCHeap::EnterLockDestroy();
}

Player* Player::Get()
{
  static Player player;

  return &player; 
}

}

