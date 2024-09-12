#pragma once

#ifndef __PFWorldRealProtectionHeader__
#error Do not include this header directly!
#endif

#include "PFHero.h"
#include "PFClientCreature.h"

#include "ClientVisibilityHelper.h"

namespace
{
  using NWorld::PFWorld;
  using NWorld::PFPlayer;
  using NWorld::PFLogicObject;

  typedef CPtr<PFPlayer> PlayerPtr;
  typedef vector<PlayerPtr> PlayerVector;

  typedef CPtr<PFLogicObject> ObjectPtr;
  typedef vector<ObjectPtr> ObjectVector;

  struct Mutex : NonCopyable
  {
    Mutex()
    {
      ::InitializeCriticalSectionAndSpinCount(&cs, 2500);
    }

    ~Mutex()
    {
      ::DeleteCriticalSection(&cs);
    }

    void Lock() const
    {
      ::EnterCriticalSection(&cs);
    }

    void Unlock() const
    {
      ::LeaveCriticalSection(&cs);
    }

    bool TryLock() const
    {
      return (::TryEnterCriticalSection(&cs) != FALSE);
    }
  private:
    mutable CRITICAL_SECTION cs;
  };

  struct ScopedLock : NonCopyable
  {
    explicit ScopedLock(const Mutex& mutex)
      : _mutex(mutex)
    {
      _mutex.Lock();
    }

    ~ScopedLock()
    {
      _mutex.Unlock();
    }
  private:
    ScopedLock();

    const Mutex& _mutex;
  };

  // TODO: better name?
  struct ScopedLockQuery : NonCopyable
  {
    explicit ScopedLockQuery(const Mutex& mutex)
      : _mutex(mutex)
      , _locked(mutex.TryLock())
    {
    }

    ~ScopedLockQuery()
    {
      if (!_locked)
        return;

      _mutex.Unlock();
    }

    bool IsLocked() const
    {
      return _locked;
    }
  private:
    ScopedLockQuery();

    const Mutex& _mutex;
    const bool _locked;
  };

  void DisposeThread(HANDLE& handle)
  {
    HANDLE h = NULL;

    swap(h, handle);

    if (!h)
      return;

    if (::WaitForSingleObject(h, 30000) != WAIT_OBJECT_0)
    {
      ErrorTrace("P: thread did not finish in time, terminating");

      ::TerminateThread(h, 0);
    }

    ::CloseHandle(h);
  }

  void DisposeEvent(HANDLE& handle)
  {
    HANDLE h = NULL;

    swap(h, handle);

    if (!h)
      return;

    ::CloseHandle(h);
  }

  void CollectPlayers(const PFWorld* const world, PlayerVector& players)
  {
    players.clear();
    players.reserve(10);

    for (int i = 0, count = world->GetPlayersCount(); i < count; ++i)
    {
      NWorld::PFPlayer* const player = world->GetPlayer(i);

      if (!player)
        continue;

      if (player->IsBot())
        continue;

      switch (player->GetTeamID())
      {
      case NCore::ETeam::Team1:
      case NCore::ETeam::Team2:
        break;
      default:
        continue;
      }

      players.push_back(player);
    }

    struct Comparer : nstl::binary_function<PlayerVector::const_reference, PlayerVector::const_reference, bool>
    {
      result_type operator()(first_argument_type lhs, second_argument_type rhs) const
      {
        return lhs->GetPlayerID() < rhs->GetPlayerID();
      }
    };

    const Comparer cmp;

    nstl::sort(players.begin(), players.end(), cmp);
  }

  PlayerPtr FindLocalPlayer(const PlayerVector& players)
  {
    PlayerVector::const_iterator it = players.begin();
    PlayerVector::const_iterator it_end = players.end();
    for (; it != it_end; ++it)
    {
      PlayerVector::const_reference player = *it;

      if (player->IsLocal())
        return player;
    }

    return PlayerPtr();
  }

  namespace Visibility
  {
    namespace Flags
    {
      enum
      {
        CanBeVisible                    = (1 << 0),
        CanBePartiallyVisible           = (1 << 1),
        ClientObjectVisible             = (1 << 2),
        ClientObjectInvisible           = (1 << 3),
        SceneObjectVisible              = (1 << 4),
        SceneObjectInvisible            = (1 << 5),
      };

      enum
      {
        KnownStateMask = ClientObjectVisible | ClientObjectInvisible | SceneObjectVisible | SceneObjectInvisible
      };
    }

    enum
    {
      maxPlayers = 10,
      maxObjects = 16,
    };

    struct ObjectInfo
    {
      typedef nstl::vector<ObjectInfo> Vector;

      ZDATA
      ZNOPARENT(NonCopyable)
      int objectId;
      int flags;
      ZEND int operator&( IBinSaver &f ) { f.Add(2,&objectId); f.Add(3,&flags); return 0; }

      ObjectInfo()
        : objectId(-1)
        , flags(0)
      {
      }
    };

    inline void UpdateInfoOther(const PlayerPtr& player, const ObjectPtr& object, ObjectInfo& info)
    {
      using namespace NGameX;

      info.objectId = object->GetObjectId();

      ClientVisibilityFlags flags;

      ClientVisibilityHelper::UpdateFlags(player.GetPtr(), object.GetPtr(), flags);

      if (ClientVisibilityHelper::IsVisibleForPlayer(flags))
        info.flags |= Flags::CanBeVisible;
      else if (ClientVisibilityHelper::IsPartialVisibilityApplicable(flags))
        info.flags |= Flags::CanBePartiallyVisible;
    }

    inline void UpdateInfoLocal(const PlayerPtr&, const ObjectPtr& object, ObjectInfo& info)
    {
      NI_VERIFY(info.objectId >= 0, "Invalid object info!", return);

      PFLogicObject::TClientObject* const clientObject = object->ClientObject();

      if (!clientObject)
        return;

      const bool clientObjectVisible =
        clientObject->IsVisible();

      if (clientObjectVisible)
        info.flags |= Flags::ClientObjectVisible;
      else
        info.flags |= Flags::ClientObjectInvisible;

      const bool sceneObjectVisible =
        !!clientObject->GetSceneObject() &&
        !!clientObject->GetSceneObject()->getVoxelGrid();

      if (sceneObjectVisible)
        info.flags |= Flags::SceneObjectVisible;
      else
        info.flags |= Flags::SceneObjectInvisible;
    }

    STARFORCE_FORCE_INLINE bool VerifyInfo(const ObjectInfo& info)
    {
      if (info.objectId < 0)
        return false;

      switch (info.flags)
      {
      case Flags::CanBeVisible:
      case Flags::CanBePartiallyVisible:
      case Flags::ClientObjectInvisible | Flags::SceneObjectInvisible:
      case Flags::ClientObjectInvisible | Flags::SceneObjectInvisible | Flags::CanBePartiallyVisible:
      case Flags::ClientObjectInvisible | Flags::SceneObjectVisible | Flags::CanBePartiallyVisible:
      case Flags::ClientObjectVisible | Flags::CanBeVisible | Flags::SceneObjectVisible:
        return true;
      default:
        return false;
      }
    }

    STARFORCE_FORCE_INLINE void CompleteInfo(ObjectInfo& info)
    {
      if (info.flags & Flags::KnownStateMask)
        return;

      if (info.flags & Flags::CanBeVisible)
        info.flags |= Flags::ClientObjectVisible;
      else
        info.flags |= Flags::ClientObjectInvisible;

      // NOTE: в данном случае, мы не можем знать наверн€ка, видим ли SceneObject, т.к. частична€ видимость определ€етс€ эффектами
      if (info.flags & Flags::CanBePartiallyVisible)
        ;
      else
        info.flags |= Flags::SceneObjectInvisible;
    }

    STARFORCE_FORCE_INLINE int GetInfoErrorBit(const ObjectInfo& info)
    {
      if (info.flags & Flags::CanBeVisible)
        return 0;

      if (info.flags & Flags::ClientObjectVisible)
        return 1;

      if (info.flags & Flags::CanBePartiallyVisible)
        return 0;

      if (info.flags & Flags::SceneObjectInvisible)
        return 0;

      return 1;
    }

    void CollectObjectsToCheckVisibility(const PlayerVector& players, ObjectVector& objects)
    {
      objects.clear();
      objects.reserve(maxObjects);

      PlayerPtr localPlayer;

      PlayerVector::const_iterator it = players.begin();
      PlayerVector::const_iterator it_end = players.end();
      for (; it != it_end; ++it)
      {
        PlayerVector::const_reference player = *it;

        if (player->IsLocal())
          localPlayer = player;

        if (player->GetHero())
          objects.push_back(ObjectPtr(player->GetHero()));
      }

      if (!IsValid(localPlayer))
        return;

      struct Collector
      {
        ObjectVector objects;

        Collector()
          : objects()
        {
          objects.reserve(32);
        }

        void operator()(NWorld::PFBaseUnit& unit)
        {
          objects.push_back(ObjectPtr(&unit));
        }
      };

      struct Predicate
      {
        bool operator()(NWorld::PFBaseUnit& unit) const
        {
          switch (unit.GetUnitType())
          {
          case NDb::UNITTYPE_SUMMON:
          case NDb::UNITTYPE_PICKUPABLE:
          case NDb::UNITTYPE_DUMMYUNIT:
            return true;
          default:
            return false;
          }
        }
      };

      Collector collector;
      const Predicate predicate;

      PFWorld* const world = localPlayer->GetWorld();

      world->GetAIWorld()->ForAllUnits(collector, predicate);

      const int objectsAvailable = collector.objects.size();
      const int objectsToAdd = maxObjects - objects.size();

      if (objectsAvailable <= 0)
        return;
      if (objectsToAdd <= 0)
        return;

      if (objectsAvailable > objectsToAdd)
      {
        const int offset = world->GetStepNumber();
        const int delta = objectsAvailable / objectsToAdd;

        for (int i = 0, index = offset; i < objectsToAdd; ++i, index += delta)
        {
          objects.push_back(collector.objects[index % objectsAvailable]);
        }
      }
      else
      {
        objects.insert(objects.end(), collector.objects.begin(), collector.objects.end());
      }

      // TODO: shuffle objects?
    }
  }

  namespace Internal
  {
    using NCore::ProtectionResult;

    using Visibility::ObjectInfo;

    struct ProtectionQuery
    {
      enum
      {
        dataCapacity = 64,
        visibilityDataCapacity = Visibility::maxPlayers * Visibility::maxObjects,
      };

      int size;

      int step;
      int stepLength;

      int data[dataCapacity];

      ProtectionQuery()
        : size(0)
      {
      }

      void Prepare(NWorld::PFWorld& world)
      {
        size = 0;

        step = world.GetStepNumber();
        stepLength = world.GetStepLength();
      }

      template <typename T>
      friend inline ProtectionQuery& operator<<(ProtectionQuery& self, T x);
    };

    // NOTE: single reader, single writer!
    template <class T, const unsigned Capacity = 32U>
    class Queue
    {
      typedef Queue<T, Capacity> ThisType;

      friend struct Writer;
    public:
      struct Writer : NonCopyable
      {
        Writer(ThisType& queue)
          : _queue(queue)
        {
          if (!_queue.ReserveItem(_item))
            _item = NULL;
        }

        ~Writer()
        {
          if (_item)
            _queue.CommitItem();

          _item = NULL;
        }

        inline bool IsAvailable() const { return !!_item; }

        // NOTE: check first!
        inline T* operator->() const { return _item; }
        // NOTE: check first!
        inline T& operator*() const { return *_item; }
      private:
        Writer();

        ThisType& _queue;
        T* _item;
      };

      Queue()
        : _mutex()
        , _r(0U)
        , _w(0U)
        , _w_commit(0U)
      {
      }

      ~Queue()
      {
        Clear();
      }

      inline void Clear()
      {
        const ScopedLock lock(_mutex);

        _r = 0U;
        _w = 0U;
        _w_commit = 0U;
      }

      inline bool IsEmpty() const
      {
        {
          const ScopedLock lock(_mutex);

          if (GetSizeInternal() == 0U)
            return true;
        }

        return false;
      }

      inline bool PopItem(T* (&item))
      {
        unsigned index;

        {
          const ScopedLock lock(_mutex);

          if (GetSizeInternal() == 0U)
            return false;

          index = _r;

          ++_r;
        }

        item = _items + index % Capacity;

        return true;
      }
    private:
      inline bool ReserveItem(T* (&item))
      {
        unsigned index;

        {
          const ScopedLock lock(_mutex);

          NI_VERIFY(GetSizeInternal() < Capacity, "Queue capacity exceeded!", return false);

          index = _w;

          ++_w;
        }

        item = _items + index % Capacity;

        return true;
      }

      inline void CommitItem()
      {
        {
          const ScopedLock lock(_mutex);

          ++_w_commit;
        }
      }

      inline unsigned GetSizeInternal() const
      {
        return _w_commit - _r;
      }

      Mutex _mutex;

      T _items[Capacity];

      unsigned _r;
      unsigned _w;
      unsigned _w_commit;
    };

    template <>
    inline ProtectionQuery& operator<<(ProtectionQuery& self, const int x)
    {
      if (x != 0)
      {
        NI_VERIFY(self.size < ProtectionQuery::dataCapacity, "Insufficient buffer!", return self);

        self.data[self.size++] = x;
      }

      return self;
    }

    template <>
    inline ProtectionQuery& operator<<(ProtectionQuery& self, const float x)
    {
      return (self << static_cast<int>(floor(x)));
    }
  }
}
