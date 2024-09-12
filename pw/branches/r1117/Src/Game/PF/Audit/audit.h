#ifndef _AUDIT_H_
#define _AUDIT_H_

#include "../../System/UpdateProcessor.h"
#include "../../System/TextFileDumper.h"
#include "../../System/AssertDumper.h"
#include "../../System/ConsoleDumper.h"

namespace NCore
{
  struct StartingAudit;
  struct MapStartInfo;
  struct StartAuditGameInfo;
  struct StartAuditGame;
  struct AuditStarted;
}
namespace NWorld { class PFWorld; }
namespace NScene { struct IScene; }

namespace AuditCore
{

class AuditGameHolder
{
public:
  AuditGameHolder( const NCore::StartAuditGameInfo& info );
  void InitAIContainer();
  
  // Helpers
  inline NWorld::PFWorld const* GetWorld()const { return IsValid(pWorld) ? pWorld.GetPtr() : NULL; }
  
private:
  CObj<NWorld::PFWorld> pWorld;
  CObj<NScene::IScene>  pScene;
  int                   playerId;
};


class AuditCore
  : public Updater::CUpdateProcessor
  , private NonCopyable
{
  OBJECT_METHODS( 0xF647BC1, AuditCore );
public:
  AuditCore();

  int   Open();
  int   Close();
  bool  Update();
  
  // Helpers
  void  SetPause(bool setPause) { m_pause = setPause; }
  void  SetPlaySpeed(float speed) { m_playSpeed = speed;}
  const NWorld::PFWorld* GetWorld(int index = 0) { return m_holders[index] ? m_holders[index]->GetWorld() : NULL; }

private:
  // Updater::CUpdateProcessor
  virtual void SubscribeUpdates();
  void OnStartingAudit( const NCore::StartingAudit& );    
  void OnStartAuditGame( const NCore::StartAuditGame& );
  void OnAuditStarted( const struct NCore::AuditStarted& );
  
  //
  bool FillMapStartInfo( NCore::MapStartInfo* pRes, const string& mapName, const int playersCount);
  
  // Dumpers
  NLogg::CTextFileDumper  m_textLogDumper;
  NLogg::CAssertDumper    m_assertDumper;
  NLogg::ConsoleDumper    m_consoleDumper;
  
  //
  bool                m_pause;
  float               m_playSpeed;
  bool                m_timeInitialized;
  float               m_curTime;
  float               m_lastTimeDelta;
  const float         m_maxTimeDelta;
  NHPTimer::STime     m_lastTime;

  enum { maxPlayers = 10 };
  typedef StaticArray<AutoPtr<AuditGameHolder>, maxPlayers> Holders;
  Holders             m_holders;
  int                 m_playersCount;
};


} // namespace AuditCore

//struct AuditGameHolder : Updater::CUpdateProcessor
//{
//private:
//  OBJECT_METHODS( 0xF63FB80, AuditGameHolder );
//
//public:
//  AuditGameHolder();
//  virtual void SubscribeUpdates();
//
//  void OnStartAuditGame( const struct NCore::StartAuditGame& message );
//  void OnMapLoaded( const struct NCore::MapLoaded& );
//  
//  CObj<NWorld::PFWorld> pWorld;
//  CObj<NScene::IScene>  pScene;
//  string                replayName;
//};
//
//enum
//{
//  TYPE_SUMMON         = 0,
//  TYPE_CREEP          = 1,
//  TYPE_SCREEP         = 2,
//  TYPE_NCREEP         = 3,
//  TYPE_TOWER          = 4,
//  TYPE_BUILDING       = 5,
//  TYPE_SHOP           = 6,
//  TYPE_TREE           = 7,
//  TYPE_PET            = 8,
//  TYPE_PICKABLE       = 9,
//  TYPE_MINIGAMEPLACE  = 10,
//  TYPE_DEADBOY        = 11,
//  
//  TYPE_COUNT
//};
//
//class AuditCore : NonCopyable
//{
//public:
//  AuditCore();
//  ~AuditCore();
//
//  int      Open();
//  int      Open( const string& replayName );
//  int      Close();
//  bool     Update();
//  void     SetPause(bool setPause);
//  void     SetPlaySpeed(float speed) { m_playSpeed = speed;}
//
//  { 
//    if (m_gameHolder == NULL)
//      return NULL;
//    return m_gameHolder->pWorld;
//  }
//
//protected:
//  unsigned long GetTimeDelta() { return m_lastTimeDelta; }
//  bool Step();
//
//  
//
//private:
//};
//

#endif


