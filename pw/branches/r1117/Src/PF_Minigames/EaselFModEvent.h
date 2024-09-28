#pragma once

namespace NDb
{
  enum   EEaselSoundType;
  struct DBEaselSoundsData;
}

namespace FMOD
{
  class Event;
}

namespace NSoundScene
{
  class FMODGroup;
}

namespace PF_Minigames
{

//////////////////////////////////////////////////////////////////////////
//
// basic FMod event wrapper class
//
//////////////////////////////////////////////////////////////////////////
class EaselFModEvent : public CObjectBase
{
  OBJECT_BASIC_METHODS( EaselFModEvent )
public:
  EaselFModEvent(NDb::EEaselSoundType _type, FMOD::Event *_pEvent);
  virtual ~EaselFModEvent();

  bool Play();
  bool Stop(bool fImmediately = true);
  bool Pause(bool _pause);

  bool IsPlaying() const;
  bool IsPaused() const;
  bool IsLooped() const  { return fIsLooped; };
 
  int  GetLength() const { return eventLenght; };    // getting event sample length in ms
  
private:
  EaselFModEvent() {}
  EaselFModEvent(const EaselFModEvent &rhs);
  EaselFModEvent& operator=(const EaselFModEvent &rhs);

  FMOD::Event *pFMODEvent;
  NDb::EEaselSoundType soundType;

  bool fIsLooped;
  int  eventLenght;

protected:

};

//////////////////////////////////////////////////////////////////////////
//
// Easel sound events factory
//
//////////////////////////////////////////////////////////////////////////
class EaselFModEventFactory
{
public:
  EaselFModEventFactory( const NDb::DBEaselSoundsData* _data, NSoundScene::FMODGroup *_group );
  ~EaselFModEventFactory();

  EaselFModEvent* CreateEvent(NDb::EEaselSoundType _eventType);
  EaselFModEvent* CreateEmptyEvent(NDb::EEaselSoundType _eventType);
  
private:
  EaselFModEventFactory();
  EaselFModEventFactory(const EaselFModEventFactory &rhs);
  EaselFModEventFactory& operator=(const EaselFModEventFactory &rhs);

  NDb::Ptr<NDb::DBEaselSoundsData> soundsData;
  NSoundScene::FMODGroup *pMinigameGrp;

protected:

};

}