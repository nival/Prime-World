#pragma once

namespace Peered
{
struct ClientHolder;

struct CrcStatus
{
  uint crc;
  bool isVerified;
  bool isRecieved;
  bool isReserved;
  void Set(uint _crc) { crc = _crc; isRecieved = true; }
};

struct UpdateResult
{
  bool needToPatch;
  bool needToVerify;
  bool isAllRecieved;
};

struct ClientPatchData
{
  int clientIndex;
  nstl::vector<Peered::BriefEntityInfo> entitiesIds;
  nstl::vector<rpc::MemoryBlock> entitiesData; 
};

struct PatchData
{
  int step;
  uint crc;
  nstl::vector<ClientPatchData> patches;
};

struct AsyncInfoInternal
{
  uint clientIndex;
  uint crc;
};

class CrcStatuses
{
  typedef nstl::hash_map<int, CrcStatus> CrcStatusContainer;
public:
  enum Status
  {
    WaitingForFirstCrc,
    WaitingForOtherCrc,
    Complete,
    AsyncDetected,
  };

  CrcStatuses(Status _status=WaitingForFirstCrc)
  {
    Reset(_status);
  }

  uint GetCrc(int clientIndex) const
  {
    CrcStatusContainer::const_iterator it = crcs.find(clientIndex);
    if (it != crcs.end())
    {
      return it->second.crc;
    }
    return 0;
  }

  void GetCrcInfo(nstl::vector<AsyncInfoInternal>& asyncs) const
  {
    asyncs.reserve(crcs.size());
    asyncs.resize(0);
    for (CrcStatusContainer::const_iterator it=crcs.begin();it!=crcs.end();++it)
    {
      const CrcStatus& crcStatus = it->second;
      AsyncInfoInternal& info = asyncs.push_back();
      info.clientIndex = it->first;
      info.crc = crcStatus.crc;
    }
  }

  // Returns clients count registred in CrcStatuses, optionaly excluding reserved clients
  int GetClientsCount(bool includeReserved = true)
  {
    if (includeReserved)
      return crcs.size();

    int clientsCount = 0;
    for (CrcStatusContainer::const_iterator itCrc = crcs.begin(); itCrc != crcs.end(); ++itCrc)
    {
      if (!itCrc->second.isReserved)
      {
        ++clientsCount;
      }
    }
    return clientsCount;
  }

  bool GetAsyncClients(vector<int> & asyncClients, list<int> * clientsForCrcRequest)
  {
    bool isResultValid = false;

    if (IsAllRecieved(false))
    {
      asyncClients.reserve(crcs.size());

      nstl::map<uint, nstl::list<int> > clientsByCrc;
      int clientsCount = 0;

      for (CrcStatusContainer::const_iterator itCrc = crcs.begin(); itCrc != crcs.end(); ++itCrc)
      {
        if (!itCrc->second.isReserved)
        {
          clientsByCrc[itCrc->second.crc].push_back(itCrc->first);
          ++clientsCount;
        }
      }

      if (clientsCount == 1)
      {
        // If we have only one client left - we don't have someone to compare with, therefore we kick him
        isResultValid = true;
        asyncClients.push_back(*clientsByCrc.begin()->second.begin());
      }
      else if ( clientsByCrc.size() > 1 )
      {
        // We enter here only if there are 2 or more crc groups. 
        isResultValid = true;

        int minimumSafeCount = (clientsCount>>1) + 1;  // At least half rounded down + 1, i.e. it is always more than half

        // It will work for non-desidable 2 async clients case: both will be added to the async list and kicked
        for (nstl::map<uint, nstl::list<int> >::const_iterator itClients = clientsByCrc.begin(); 
              itClients != clientsByCrc.end(); ++itClients)
        {
          if (itClients->second.size() < minimumSafeCount)
          {
            // Copy async clients
            int count = asyncClients.size();
            asyncClients.resize(count + itClients->second.size());
            nstl::copy( itClients->second.begin(), itClients->second.end(), asyncClients.begin() + count );
            if (clientsForCrcRequest)
            {
              // Push back, so clients with bad crc won't be the first one in the list
              clientsForCrcRequest->push_back(itClients->second.front());
            }
          }
          else
          {
            // If we found a safe group - set its CRC as agreed
            agreedCrc = itClients->first;
            if (clientsForCrcRequest)
            {
              // Push front, so client with good crc will be the first one in the list
              clientsForCrcRequest->push_front(itClients->second.front());
            }
          }
        }
      }
    }

    return isResultValid;
  }

  void AddClient(int clientIndex, bool isReserved = false)
  {
    CrcStatus crcStatus = { 0, false, false, isReserved };
    crcs.insertUnique(clientIndex, crcStatus);

    if (status == Complete)
    {
      status = WaitingForOtherCrc;
    }
  }

  void RemoveClient(int clientIndex)
  {
    CrcStatusContainer::iterator it = crcs.find(clientIndex);
    if (it != crcs.end())
    {
      crcs.erase(it);
    }
  }

  void UnreserveClient(int clientIndex)
  {
    CrcStatusContainer::iterator it = crcs.find(clientIndex);
    if (it != crcs.end())
    {
      it->second.isReserved = false;
    }
  }

  void ApplyTrustedCrc(uint crc, UpdateResult& result)
  {
    status = Complete; 
    agreedCrc = crc;
    for (CrcStatusContainer::iterator itCrc = crcs.begin(); itCrc != crcs.end(); ++itCrc)
    {
      CrcStatus& crcStatus = itCrc->second;
      if (crcStatus.isRecieved)
      {
        if (crcStatus.crc == crc)
        {
          crcStatus.isVerified = true;
        } else 
        {
          result.needToPatch = true;
        }
      }
    }
  }

  void SetClientCrc(uint crc, int clientIndex, UpdateResult& result)
  {
    CrcStatusContainer::iterator it = crcs.find(clientIndex);
    if (it != crcs.end())
    {
      CrcStatus& crcStatus = it->second;
      crcStatus.Set(crc);
      if (status != Complete)
      {
        if (status == WaitingForFirstCrc)
        {
          agreedCrc = crc;
          status = WaitingForOtherCrc;
        } 
        else
        if (status == WaitingForOtherCrc)
        {
          if (agreedCrc != crc)
          { 
            status = AsyncDetected;
            result.needToVerify = true;
          } 
        } 
        else
        if (status == AsyncDetected)
        {
          result.needToVerify = true;
        }
      } else 
      {
        if (agreedCrc == crc)
        { 
          crcStatus.isVerified = true;
        }
      }
    }
  }

  CrcStatus* GetClientCrcStatus(int clientIndex)
  {        
    CrcStatusContainer::iterator it = crcs.find(clientIndex);
    if (it != crcs.end())
    {
      return &it->second;
    }
    return 0;
  }

  void MarkAsCompleted() 
  {
    for (CrcStatusContainer::iterator it=crcs.begin();it!=crcs.end();++it)
    {
      it->second.isVerified = true;
    }
    status = Complete;
  }

  void CheckAgreedCrc()
  {
    uint firstCrcValue = 0;
    bool firstCrcFound = false;
    bool agreedCrcOk = false;

    for (CrcStatusContainer::const_iterator it = crcs.begin(); !agreedCrcOk && it != crcs.end(); ++it)
    {
      const CrcStatus& crcStatus = it->second;
      if (crcStatus.isRecieved)
      {
        if (!firstCrcFound)
        {
          firstCrcFound = true;
          firstCrcValue = crcStatus.crc;
        }

        if (crcStatus.crc == agreedCrc)
        {
          agreedCrcOk = true;
        }
      }
    }

    if (!agreedCrcOk && firstCrcFound)
    {
      agreedCrc = firstCrcFound;
    }
  }

  bool IsAllAgreed() const
  {
    if (status == Complete)
    {
      return true;
    }
    if (status == WaitingForFirstCrc || status == AsyncDetected)
    {
      return false;
    } 
    for (CrcStatusContainer::const_iterator it=crcs.begin();it!=crcs.end();++it)
    {
      const CrcStatus& crcStatus = it->second;
      if (!crcStatus.isRecieved || crcStatus.crc != agreedCrc)
      {
        return false;
      }
    }
    return true;
  }

  bool IsAllRecieved(bool includeReserved = true) const
  {
    for (CrcStatusContainer::const_iterator it=crcs.begin();it!=crcs.end();++it)
    {
      const CrcStatus& crcStatus = it->second;
      if (!crcStatus.isRecieved && (includeReserved || !crcStatus.isReserved))
      {
        return false;
      }
    }
    return true;
  }

  void FillPatchData(PatchData& patch)
  {
    patch.crc = agreedCrc;
    bool isCompleted = true;
    for (CrcStatusContainer::iterator it=crcs.begin();it!=crcs.end();++it)
    {
      CrcStatus& crcStatus = it->second;
      if (crcStatus.isRecieved)
      {
        if (crcStatus.crc != agreedCrc)
        {
          ClientPatchData& data = patch.patches.push_back();
          data.clientIndex = it->first;
          crcStatus.isVerified = true;
        }
      } else
      {
        isCompleted = false;
      }
    }
    if (isCompleted)
    {
      status = Complete;
    }
  }
  Status GetStatus() const { return status; }

  void Reset(Status _status) 
  {
    agreedCrc = 0;
    status = _status;
    crcs.clear();
  }

  void UpdateStatus()
  {
    int receivedCount = 0;
    bool asyncDetected = false;

    CheckAgreedCrc();

    for (CrcStatusContainer::iterator it = crcs.begin(); it!=crcs.end(); ++it)
    {
      CrcStatus& crcStatus = it->second;

      if (crcStatus.isRecieved)
      {
        ++receivedCount;

        if (crcStatus.crc != agreedCrc)
        {
          asyncDetected = true;
        }
      }
    }

    if (asyncDetected || status == AsyncDetected && receivedCount < 2)
    {
      status = AsyncDetected;
    }
    else if (receivedCount == 0)
    {
      status = WaitingForFirstCrc;
    }
    else if (receivedCount < crcs.size())
    {
      status = WaitingForOtherCrc;
    }
    else 
    {
      status = Complete;
    }
  }

private:
  CrcStatusContainer crcs;
  uint agreedCrc;
  Status status;
};

class WorldSnapshot
{
  typedef nstl::vector<CrcStatus> CrcStatusContainer;
  typedef nstl::vector<rpc::MemoryBlock> WorldDataParts;

public:
  WorldSnapshot(int _step, CrcStatuses::Status _status=CrcStatuses::WaitingForFirstCrc):
  step(_step),
  crcs(_status),
  asyncInfoSent(false)
  {
  }

  ~WorldSnapshot()
  {
    ClearWorldDataParts();
  }

  uint GetCrc(int clientIndex) const
  {
    return crcs.GetCrc(clientIndex);
  }

  void GetCrcInfo(nstl::vector<AsyncInfoInternal>& asyncs) const
  {
    return crcs.GetCrcInfo(asyncs);
  }

  // Returns clients count registred in WorldSnapshot, optionaly excluding reserved clients
  int GetClientsCount(bool includeReserved = true)
  {
    return crcs.GetClientsCount(includeReserved);
  }

  bool GetAsyncClients(vector<int> & asyncClients, list<int> * clientsForCrcRequest)
  {
    return crcs.GetAsyncClients(asyncClients, clientsForCrcRequest);
  }

  CrcStatuses::Status GetStatus() const { return crcs.GetStatus(); }

  void AddClient(int clientIndex, bool isReserved = false)
  {
    crcs.AddClient(clientIndex, isReserved);
  }
  void RemoveClient(int clientIndex)
  {
    crcs.RemoveClient(clientIndex);
  }

  void UnreserveClient(int clientIndex)
  {
    crcs.UnreserveClient(clientIndex);
  }

  UpdateResult Update(int clientIndex, uint crc, bool isTrusted)
  {
    UpdateResult result = { false, false, false };
    if (isTrusted)
    {
      // TODO: here apply data from trusted source
      crcs.ApplyTrustedCrc(crc, result);
      result.isAllRecieved = true;
    } else
    {
      crcs.SetClientCrc(crc, clientIndex, result);
      if ((!result.needToPatch &&  !result.needToVerify))
      {
        if (CheckIfComplete())
        {
          result.isAllRecieved = true;
        } else
        {
          result.isAllRecieved = crcs.IsAllRecieved();
        }
      } else
      {
        result.isAllRecieved = crcs.IsAllRecieved();
      }
    }
    return result;
  }

  bool CheckIfComplete()
  {
    if (crcs.IsAllAgreed())
    {
      crcs.MarkAsCompleted();
      return true;
    }
    return false;
  }

  void Reset(int _step, CrcStatuses::Status _status) 
  {
    step = _step;
    crcs.Reset(_status);
    asyncInfoSent = false;
  }

  void UpdateStatus()
  {
    crcs.UpdateStatus();
  }

  void MarkAsCompleted() 
  {
    crcs.MarkAsCompleted();
  }

  void FillPatchData(PatchData& patch)
  {
    patch.step = step;
    crcs.FillPatchData(patch);
  }
  int GetStep() const { return step; }
  bool IsAsyncDetected() const { return crcs.GetStatus() == CrcStatuses::AsyncDetected; } 
  bool IsAllRecieved(bool includeReserved = true) const { return crcs.IsAllRecieved(includeReserved); }

  void AddWorldDataPart(const rpc::MemoryBlock& worldDataPart)
  {
    void * dataPartBuffer = new char[worldDataPart.size];
#if defined( NV_WIN_PLATFORM )
    memcpy_s(dataPartBuffer, worldDataPart.size, worldDataPart.memory, worldDataPart.size);
#elif defined( NV_LINUX_PLATFORM )
    memcpy(dataPartBuffer, worldDataPart.memory, min<int>(worldDataPart.size, worldDataPart.size));
#endif
    rpc::MemoryBlock & newWorldDataPart = worldDataParts.push_back();
    newWorldDataPart.memory = dataPartBuffer;
    newWorldDataPart.size = worldDataPart.size;
  }

  void ClearWorldDataParts()
  {
    for (WorldDataParts::iterator it = worldDataParts.begin(); it != worldDataParts.end(); ++it)
      delete [] (char *)((*it).memory);
    worldDataParts.clear();
  }

  int GetWorldDataPartsCount()
  {
    return worldDataParts.size();
  }

  rpc::MemoryBlock & GetWorldDataPart(int index)
  {
    return worldDataParts[index];
  }

  void ReserveWorldDataParts(int partsCount)
  {
    worldDataParts.reserve(partsCount);
  }

  void SetAsyncInfoSent(bool _asyncInfoSent) { asyncInfoSent = _asyncInfoSent; }
  bool IsAsyncInfoSent() const { return asyncInfoSent; }

 private:
  DUMMY_ASSIGNMENT( WorldSnapshot );
  
  int step;
  CrcStatuses crcs;
  WorldDataParts worldDataParts;
  bool asyncInfoSent;
};

}