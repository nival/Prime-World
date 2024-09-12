#pragma once

#define __PFWorldRealProtectionHeader__

#include "PFWorldProtection.h"
#include "PFWorldRealProtectionUtility.hpp"

class PFWorldRealProtection
  : public NWorld::PFWorldProtection
{
  enum
  {
    // NOTE: этот диапазон не проверяется! убедитесь, что checkIntervalMin строго меньше checkIntervalMax.
    checkIntervalMin = 3000,
    checkIntervalMax = 10000,
  };

  WORLD_OBJECT_METHODS(0x15C5DC01, PFWorldRealProtection)
public:
  explicit PFWorldRealProtection(NWorld::PFWorld* const world)
    : PFWorldProtection(world)
    , _ok(1L)
    , players()
    , objectsToCheckVisibility()
    , visibilityData()
    , protectionThread(NULL)
    , eventUpdate(NULL)
    , eventFinish(NULL)
    , queries()
    , results()
    , updateOffset(0)
    , updateFrequency(1)
  {
    Initialize();
    Start();
  }

  virtual ~PFWorldRealProtection()
  {
    Stop();
  }

  virtual void Update()
  {
    NI_VERIFY(!!protectionThread, "Invalid state", return);

    NI_VERIFY(!!eventUpdate, "Invalid state", return);
    NI_VERIFY(!!eventFinish, "Invalid state", return);

    NWorld::PFWorld* const world = GetWorld();

    const int step = world->GetStepNumber();

    if (updateFrequency <= 0)
      return;
    if ((step - updateOffset) % updateFrequency)
      return;

    const QueryQueue::Writer query_writer(queries);

    if (!query_writer.IsAvailable())
    {
      WarningTrace("P: failed to allocate query");
      return;
    }

    Internal::ProtectionQuery& query = *query_writer;

    query.Prepare(*world);

    PlayerVector::const_iterator it = players.begin();
    PlayerVector::const_iterator it_end = players.end();
    for (int index = 0; it != it_end; ++it, ++index)
    {
      PlayerVector::const_reference player = *it;

      const NWorld::PFBaseHero* const hero = player->GetHero();

      if (!hero)
        continue;

      const CVec3 position(hero->GetPosition());

      query
        << position.x
        << position.y
        << position.z
        << hero->GetHealth()
        << hero->GetEnergy()
        << hero->GetNafta();
    }

    if (::WaitForSingleObject(protectionThread, 0) == WAIT_OBJECT_0)
    {
      ErrorTrace("P: thread stopped unexpectedly, restarting");

      Stop();
      Start();
    }

    NotifyUpdate();
  }

  virtual bool IsOK() const
  {
    return (::InterlockedCompareExchange(&_ok, 0L, 0L) != 0L);
  }

  virtual bool PopResult(NCore::ProtectionResult& result)
  {
    NCore::ProtectionResult* item;

    if (!results.PopItem(item))
      return false;

    result = *item;

    return true;
  }

  virtual void SetUpdateFrequency(const int offset, const int frequency)
  {
    updateOffset = offset;
    updateFrequency = frequency;
  }
protected:
  PFWorldRealProtection()
    : PFWorldProtection()
    , _ok(1L)
    , players()
    , objectsToCheckVisibility()
    , visibilityData()
    , protectionThread(NULL)
    , eventUpdate(NULL)
    , eventFinish(NULL)
    , queries()
    , results()
    , updateOffset(0)
    , updateFrequency(1)
  {
  }
private:
  void Serialize(IBinSaver& f)
  {
    f.Add(1, static_cast<NWorld::PFWorldProtection*>(this));
    f.Add(2, &players);
  }

  bool UpdateVisibilityData(const int step)
  {
    if (players.size() < 2)
      return false;

    const int stage = step % 2;

    switch (stage)
    {
    case 0:
      {
        Visibility::CollectObjectsToCheckVisibility(players, objectsToCheckVisibility);

        visibilityData.clear();
        visibilityData.resize(players.size() * objectsToCheckVisibility.size());

        PlayerVector::const_iterator it_player = players.begin();
        PlayerVector::const_iterator it_player_end = players.end();
        for (int objectVisibilityInfoIndexBase = 0; it_player != it_player_end; ++it_player, objectVisibilityInfoIndexBase += objectsToCheckVisibility.size())
        {
          PlayerVector::const_reference player = *it_player;

          ObjectVector::const_iterator it_object = objectsToCheckVisibility.begin();
          ObjectVector::const_iterator it_object_end = objectsToCheckVisibility.end();
          for (int objectIndex = 0; it_object != it_object_end; ++it_object, ++objectIndex)
          {
            ObjectVector::const_reference object = *it_object;

            Visibility::UpdateInfoOther(player, object, visibilityData[objectVisibilityInfoIndexBase + objectIndex]);
          }
        }

        return false;
      }
    case 1:
      {
        PlayerVector::const_iterator it_player = players.begin();
        PlayerVector::const_iterator it_player_end = players.end();
        for (int objectVisibilityInfoIndexBase = 0; it_player != it_player_end; ++it_player, objectVisibilityInfoIndexBase += objectsToCheckVisibility.size())
        {
          PlayerVector::const_reference player = *it_player;

          if (!player->IsLocal())
            continue;

          ObjectVector::const_iterator it_object = objectsToCheckVisibility.begin();
          ObjectVector::const_iterator it_object_end = objectsToCheckVisibility.end();
          for (int objectIndex = 0; it_object != it_object_end; ++it_object, ++objectIndex)
          {
            ObjectVector::const_reference object = *it_object;

            Visibility::UpdateInfoLocal(player, object, visibilityData[objectVisibilityInfoIndexBase + objectIndex]);
          }
        }

        return true;
      }
    }

    // ?
    return false;
  }

  bool IsFinished() const
  {
    if (!eventFinish)
      return true;

    return (::WaitForSingleObject(eventFinish, 0) == WAIT_OBJECT_0);
  }

  void NotifyUpdate() const
  {
    if (!eventUpdate)
      return;

    ::SetEvent(eventUpdate);
  }

  void NotifyFinish() const
  {
    if (!eventFinish)
      return;

    ::SetEvent(eventFinish);
  }

  void Initialize()
  {
    CollectPlayers(GetWorld(), players);

    visibilityData.reserve(players.size() * Visibility::maxObjects);
  }

  void Reinitialize()
  {
    // just for sure
    queries.Clear();
    results.Clear();

    visibilityData.reserve(players.size() * Visibility::maxObjects);
  }

#pragma code_seg(push, "~")

  STARFORCE_EXPORT void ProtectionExecute()
  {
    DebugTrace("P: start");

    // NOTE: эти значения должны быть больше 0 перед началом работы
    unsigned chances = 3U;
    unsigned stepsUntilFailure = 50U;
    unsigned stepsUntilTerminate = 10U;

    // scheduler
    int nextCheckStep = 5;

    for (;;)
    {
      if (queries.IsEmpty())
        ::WaitForSingleObject(eventUpdate, 1000U);

      if (IsFinished())
        break;

      Internal::ProtectionQuery* query;

      if (!queries.PopItem(query))
        continue;

      const bool calculate =
        !!chances &&
        !!stepsUntilFailure;

      const bool check = (nextCheckStep <= query->step);

      // << update scheduler >>
      if (check)
      {
        const int timeToNextCheck = checkIntervalMin + rand() % (checkIntervalMax - checkIntervalMin + 1);

        nextCheckStep = query->step;

        nextCheckStep += timeToNextCheck / query->stepLength;
        nextCheckStep += timeToNextCheck % 5;
      }

      const unsigned a = query->step;
      const unsigned b = query->stepLength;
      const unsigned kinda_random = ((a * a * b) ^ 0xF135793BU) * ((a * b * b) ^ 0x2AC4860E) + a;

      int hash = kinda_random;

      // << calculate >>
      if (calculate)
      {
        unsigned shift = kinda_random;

        shift *= 1917435091U;
        shift += 2019712139U;

        hash ^= shift;

        if (shift + static_cast<unsigned>(query->size) < shift)
          shift += static_cast<unsigned>(query->size);

        for (int i = 0, count = query->size; i < count; ++i)
        {
          const int x = query->data[(shift + i) % count];

          const int test = (hash & 0xF0000000);

          hash = (hash << 4) + x;

          if (test)
            hash ^= (test >> 24);
        }
      }

      // << post result >>
      {
        const ResultQueue::Writer result_writer(results);

        if (!result_writer.IsAvailable())
        {
          WarningTrace("P: failed to allocate result");
        }
        else
        {
          Internal::ProtectionResult& result = *result_writer;

          result.step = query->step;
          result.magic = hash;
        }
      }

      // << check >>
      if (check)
      {
        if (!Protection::CheckReadOnlyAndExecutableImmediate())
        {
          if (chances)
            --chances;
        }
      }

      // << state >>
      if (!chances)
      {
        ::InterlockedExchange(&_ok, 0L);

        if (stepsUntilFailure)
        {
          --stepsUntilFailure;
        }
        else
        {
          if (stepsUntilTerminate)
          {
            --stepsUntilTerminate;
          }
          else
          {
            break;
          }
        }
      }

      if (IsFinished())
        break;
    }

    DebugTrace("P: finish");

    const bool failed =
      !chances &&
      !stepsUntilFailure &&
      !stepsUntilTerminate;

    if (failed)
    {
      ErrorTrace("P: THE END");

      exit(0xDEADBEEF);
    }
  }

#pragma code_seg(pop)

  void Start()
  {
    struct Local
    {
      static DWORD WINAPI ProtectionThreadThunk(LPVOID p)
      {
        static_cast<PFWorldRealProtection*>(p)->ProtectionExecute();

        return 0U;
      }
    };

    NI_VERIFY(!protectionThread, "Thread already exists!", return);

    NI_VERIFY(!eventUpdate, "Event 'update' already exists!", return);
    NI_VERIFY(!eventFinish, "Event 'finish' already exists!", return);

    eventUpdate = ::CreateEvent(NULL, FALSE, FALSE, NULL);
    eventFinish = ::CreateEvent(NULL, TRUE, FALSE, NULL);

    NI_VERIFY(!!eventUpdate, "Failed to create event 'update'!", return);
    NI_VERIFY(!!eventFinish, "Failed to create event 'finish'!", return);

    protectionThread = ::CreateThread(NULL, 16384U, &Local::ProtectionThreadThunk, this, 0U, NULL);

    NI_VERIFY(!!protectionThread, "Failed to create thread!", return);

    ::SetThreadPriority(protectionThread, THREAD_PRIORITY_ABOVE_NORMAL);
  }

  void Stop()
  {
    queries.Clear();
    results.Clear();

    NotifyFinish();
    NotifyUpdate();

    DisposeThread(protectionThread);

    DisposeEvent(eventUpdate);
    DisposeEvent(eventFinish);
  }

  HANDLE protectionThread;

  HANDLE eventUpdate;
  HANDLE eventFinish;

  typedef Internal::Queue<Internal::ProtectionQuery, 2048U> QueryQueue;
  typedef Internal::Queue<Internal::ProtectionResult, 2048U> ResultQueue;

  QueryQueue  queries;
  ResultQueue results;

  int updateOffset;
  int updateFrequency;

  // state
  mutable volatile LONG _ok;

  PlayerVector players;

  ObjectVector                    objectsToCheckVisibility;
  Visibility::ObjectInfo::Vector  visibilityData;
public:
  // NOTE: сериализатор сделан вручную. стандартная реализация, генерируемая с помощью макроса, здесь не годится из-за сложности объекта
  int operator&( IBinSaver &f );

};

int PFWorldRealProtection::operator&(IBinSaver &f)
{
  if (f.IsReading())
  {
    Stop();
    Serialize(f);
    Reinitialize();
    Start();
  }
  else
  {
    Serialize(f);
  }

  return 0;
}

REGISTER_WORLD_OBJECT(PFWorldRealProtection)
