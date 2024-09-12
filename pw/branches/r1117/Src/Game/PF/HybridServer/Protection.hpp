#pragma once

namespace Peered
{
  namespace Protection
  {
    typedef nstl::list<int> ClientIndexList;
    typedef nstl::vector<int> ClientIndexVector;

    struct ClientMagicInfo
    {
      int clientIndex;
      uint magic;
    };

    typedef nstl::vector<ClientMagicInfo> ClientMagicInfoContainer;

    struct ClientRecord
    {
      uint magic;
      bool received;
      bool reserved;
    };

    class ClientRecords
    {
    public:
      ClientRecords()
        : _records()
        , _revision(0U)
      {
      }

      ~ClientRecords()
      {
      }

      void Reset()
      {
        _records.clear();
        _revision = 0U;
      }

      void AddClient(const int clientIndex, const bool reserved = false)
      {
        ClientRecordMap::const_iterator it = _records.find(clientIndex);

        if (it != _records.end())
          return;

        Record& record = _records[clientIndex];

        record.magic = 0U;
        record.received = false;
        record.reserved = reserved;

        ++_revision;
      }

      void RemoveClient(const int clientIndex)
      {
        ClientRecordMap::iterator it = _records.find(clientIndex);

        if (it == _records.end())
          return;

        _records.erase(it);

        ++_revision;
      }

      void UnreserveClient(const int clientIndex)
      {
        ClientRecordMap::iterator it = _records.find(clientIndex);

        if (it == _records.end())
          return;

        Record& record = it->second;

        record.reserved = false;

        ++_revision;
      }

      void SetClientMagic(const int clientIndex, const uint magic)
      {
        ClientRecordMap::iterator it = _records.find(clientIndex);

        if (it == _records.end())
          return;

        Record& record = it->second;

        record.magic = magic;
        record.received = true;

        ++_revision;
      }

      bool IsAllReceived(const bool includeReserved = false) const
      {
        ClientRecordMap::const_iterator it = _records.begin();
        ClientRecordMap::const_iterator it_end = _records.end();
        for (; it != it_end; ++it)
        {
          const Record& record = it->second;

          if (record.reserved && !includeReserved)
            continue;

          if (!record.received)
            return false;
        }

        return true;
      }

      bool IsAnyReceived(const bool includeReserved = true) const
      {
        ClientRecordMap::const_iterator it = _records.begin();
        ClientRecordMap::const_iterator it_end = _records.end();
        for (; it != it_end; ++it)
        {
          const Record& record = it->second;

          if (record.reserved && !includeReserved)
            continue;

          if (record.received)
            return true;
        }

        return false;
      }

      int GetClientCount(const bool includeReserved = false) const
      {
        if (includeReserved)
          return _records.size();

        int count = 0;

        ClientRecordMap::const_iterator it = _records.begin();
        ClientRecordMap::const_iterator it_end = _records.end();
        for (; it != it_end; ++it)
        {
          const Record& record = it->second;

          if (record.reserved)
            continue;

          ++count;
        }

        return count;
      }

      void GetAsyncClients(ClientIndexVector& asyncClients) const
      {
        typedef nstl::hash_map<uint, ClientIndexList> MagicToClientsMap;

        asyncClients.clear();

        MagicToClientsMap clientsByMagic;

        int clientCount = 0;

        {
          ClientRecordMap::const_iterator it = _records.begin();
          ClientRecordMap::const_iterator it_end = _records.end();
          for (; it != it_end; ++it)
          {
            const Record& record = it->second;

            if (record.reserved)
              continue;

            const int clientIndex = it->first;

            clientsByMagic[record.magic].push_back(clientIndex);

            ++clientCount;
          }
        }

        if (clientCount < 2)
          return;

        if (clientsByMagic.size() == 1)
          return;

        const int safeGroupSize = (clientCount >> 1) + 1;

        {
          MagicToClientsMap::const_iterator it = clientsByMagic.begin();
          MagicToClientsMap::const_iterator it_end = clientsByMagic.end();
          for (; it != it_end; ++it)
          {
            const ClientIndexList& groupClients = it->second;

            if (groupClients.size() >= safeGroupSize)
              continue;

            asyncClients.insert(asyncClients.end(), groupClients.begin(), groupClients.end());
          }
        }
      }

      void GetPendingClients(ClientIndexVector& pendingClients, const bool includeReserved = false) const
      {
        pendingClients.clear();

        ClientRecordMap::const_iterator it = _records.begin();
        ClientRecordMap::const_iterator it_end = _records.end();
        for (; it != it_end; ++it)
        {
          const Record& record = it->second;

          if (record.reserved && !includeReserved)
            continue;

          if (record.received)
            continue;

          pendingClients.push_back(it->first);
        }
      }

      void GetMagicInfo(ClientMagicInfoContainer& infoContainer) const
      {
        infoContainer.clear();
        infoContainer.reserve(_records.size());

        ClientRecordMap::const_iterator it = _records.begin();
        ClientRecordMap::const_iterator it_end = _records.end();
        for (; it != it_end; ++it)
        {
          ClientMagicInfo& info = infoContainer.push_back();

          info.clientIndex = it->first;
          info.magic = it->second.magic;
        }
      }

      uint GetRevision() const { return _revision; }
    private:
      typedef ClientRecord Record;

      typedef nstl::hash_map<int, Record> ClientRecordMap;

      ClientRecordMap _records;
      uint _revision;
    };

    class StepRecord : public NonCopyable
    {
    public:
      struct State
      {
        enum Type
        {
          Assembly,
          Complete,
          Async,
        };
      };

      explicit StepRecord(const int step)
        : _step(step)
        , _revision(0U)
        , _state(State::Assembly)
        , _asyncInfoSent(false)
        , _clients()
        , _asyncClients()
        , _pendingClients()
      {
      }

      ~StepRecord()
      {
      }

      void Reset(const int step)
      {
        _step = step;
        _revision = 0U;
        _state = State::Assembly;
        _asyncInfoSent = false;
        _clients.Reset();
        _asyncClients.clear();
        _pendingClients.clear();
      }

      void AddClient(const int clientIndex, const bool reserved = false)
      {
        _clients.AddClient(clientIndex, reserved);
      }

      void RemoveClient(const int clientIndex)
      {
        _clients.RemoveClient(clientIndex);
      }

      void UnreserveClient(const int clientIndex)
      {
        _clients.UnreserveClient(clientIndex);
      }

      void SetClientMagic(const int clientIndex, const uint magic)
      {
        _clients.SetClientMagic(clientIndex, magic);
      }

      void GetMagicInfo(ClientMagicInfoContainer& infoContainer) const
      {
        return _clients.GetMagicInfo(infoContainer);
      }

      int GetClientCount(const bool includeReserved = false) const
      {
        return _clients.GetClientCount(includeReserved);
      }

      const ClientRecords& GetClientRecords() const { return _clients; }

      bool Update()
      {
        const bool needUpdate = (_revision != _clients.GetRevision());

        if (needUpdate)
        {
          _revision = _clients.GetRevision();

          DoUpdate();

          return true;
        }

        return false;
      }

      bool IsComplete() const { return (_state == State::Complete); }
      bool IsAsync() const { return (_state == State::Async); }

      bool IsFinished() const
      {
        switch (_state)
        {
        case State::Complete:
        case State::Async:
          return true;
        default:
          return false;
        }
      }

      bool IsWaitingForFirstMagic() const
      {
        switch (_state)
        {
        case State::Assembly:
          return !_clients.IsAnyReceived();
        default:
          return false;
        }
      }

      bool IsWaitingForNextMagic() const
      {
        switch (_state)
        {
        case State::Assembly:
          return _clients.IsAnyReceived();
        default:
          return false;
        }
      }

      int GetStep() const { return _step; }

      void NotifyAsyncInfoSent() { _asyncInfoSent = true; }
      bool IsAsyncInfoSent() const { return _asyncInfoSent; }

      const ClientIndexVector& GetAsyncClients() const { return _asyncClients; }
      const ClientIndexVector& GetPendingClients() const { return _pendingClients; }

      bool IsAllClientsAsynced() const
      {
        return IsAsync() && (_asyncClients.size() == GetClientCount());
      }
    private:
      StepRecord();

      void DoUpdate()
      {
        const int clientCount = _clients.GetClientCount(true);

        _asyncClients.clear();
        _pendingClients.clear();

        if (_clients.IsAllReceived())
        {
          _asyncClients.reserve(clientCount);
          _clients.GetAsyncClients(_asyncClients);

          if (_asyncClients.empty())
            _state = State::Complete;
          else
            _state = State::Async;
        }
        else
        {
          _pendingClients.reserve(clientCount);
          _clients.GetPendingClients(_pendingClients);

          _state = State::Assembly;
        }
      }

      int _step;
      uint _revision; // sync state with client records
      State::Type _state;
      bool _asyncInfoSent;
      ClientRecords _clients;
      ClientIndexVector _asyncClients;
      ClientIndexVector _pendingClients;
    };

    typedef nstl::vector<StepRecord*> StepRecordVector;

    class StepRecords : public NonCopyable
    {
    public:
      StepRecords()
        : _records()
        , _recordPool()
        , _firstFinishedStep(NCore::INVALID_STEP)
      {
      }

      ~StepRecords()
      {
        DeleteRecords(_records);
        DeleteRecords(_recordPool);
      }

      StepRecord* AllocateStepRecord(const int step)
      {
        StepRecord* record;

        if (_recordPool.empty())
        {
          record = new StepRecord(step);
        }
        else
        {
          record = _recordPool.back();
          _recordPool.pop_back();
          record->Reset(step);
        }

        _records.push_back(record);

        return record;
      }

      void DeallocateStepRecords(const int count)
      {
        const int recordsToDeallocate = Clamp(count, 0, _records.size() - 1);

        if (recordsToDeallocate < 1)
          return;

        for (int i = 0; i < recordsToDeallocate; ++i)
        {
          _recordPool.push_back(_records[i]);
        }

        _records.erase(_records.begin(), _records.begin() + recordsToDeallocate);
      }

      void AddClient(const int clientIndex, const int fromStep, const bool reserved = false)
      {
        for (int i = 0, count = _records.size(); i < count; ++i)
        {
          StepRecordVector::const_reference record = _records[i];

          if (record->GetStep() >= fromStep)
          {
            record->AddClient(clientIndex, reserved);
          }
        }
      }

      void RemoveClient(const int clientIndex, const int toStep, const bool unreserve = false)
      {
        for (int i = 0, count = _records.size(); i < count; ++i)
        {
          StepRecordVector::const_reference record = _records[i];

          if (record->GetStep() < toStep)
          {
            record->RemoveClient(clientIndex);
          }
          else if (unreserve)
          {
            record->UnreserveClient(clientIndex);
          }
        }
      }

      void UpdateClientMagic(const int clientIndex, const int step, const uint magic)
      {
        for (int i = 0, count = _records.size(); i < count; ++i)
        {
          StepRecordVector::const_reference record = _records[i];

          if (record->GetStep() == step)
          {
            record->SetClientMagic(clientIndex, magic);
            break;
          }
        }
      }

      bool Update()
      {
        bool updated = false;

        for (int i = 0, count = _records.size(); i < count; ++i)
        {
          StepRecordVector::const_reference record = _records[i];

          if (record->Update())
            updated = true;
        }

        return updated;
      }

      int GetLastStep(const int defaultValue = -1) const
      {
        if (_records.empty())
          return defaultValue;

        return _records.back()->GetStep();
      }

      StepRecord* GetStepRecord(const int step) const
      {
        for (int left = 0, right = _records.size() - 1; left <= right; )
        {
          const int mid = (left + right) >> 1;

          StepRecordVector::const_reference record = _records[mid];

          if (step == record->GetStep())
            return record;

          if (step < record->GetStep())
            right = mid - 1;
          else
            left = mid + 1;
        }

        return NULL;
      }

      void DropEmptyRecords()
      {
        if (_firstFinishedStep != NCore::INVALID_STEP)
          return;

        StepRecordVector::const_iterator it_record = FindFirstFinishedRecord(_records);

        if (it_record == _records.end())
          return;

        {
          StepRecordVector::const_reference record = *it_record;

          _firstFinishedStep = record->GetStep();
        }

        {
          // TODO: distance() ?
          const int count = it_record - _records.begin();

          DeallocateStepRecords(count);
        }
      }

      const StepRecordVector& GetStepRecords() const { return _records; }
    private:
      static void DeleteRecords(StepRecordVector& c)
      {
        StepRecordVector::const_iterator it = c.begin();
        StepRecordVector::const_iterator it_end = c.end();
        for (; it != it_end; ++it)
        {
          delete (*it);
        }

        c.clear();
      }

      static StepRecordVector::const_iterator FindFirstFinishedRecord(const StepRecordVector& c)
      {
        bool stopOnEmpty = false;

        StepRecordVector::const_iterator it = c.begin();
        StepRecordVector::const_iterator it_end = c.end();
        for (; it != it_end; ++it)
        {
          StepRecordVector::const_reference record = *it;

          if (record->IsFinished())
            return it;

          if (record->IsWaitingForFirstMagic())
          {
            if (stopOnEmpty)
              break;
          }
          else
          {
            stopOnEmpty = true;
          }
        }

        return c.end();
      }

      StepRecordVector _records;
      StepRecordVector _recordPool;

      int _firstFinishedStep;
    };

    struct MagicRecord
    {
      int   clientIndex;
      int   step;
      uint  magic;
    };
  }
}
