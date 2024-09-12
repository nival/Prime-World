#pragma once

#include "System/Crc32Checksum.h"

namespace Peered
{

struct WorldData
{
  enum Status
  {
    InProgress,
    Built,
  };
  WorldData(int _step):status(InProgress)
  {
    changes.Reset(_step);
  }

  int GetChangesCount(int _step, const SnapshotInfo& _info, int totalChangesCount)
  {
    if (changes.step == _step)
    {
      return changes.changesAppliedBeforeBuilt-_info.changesAppliedBeforeBuilt+changes.changesAppliedAfterBuilt;
    }
    return totalChangesCount;
  }

  void Append(const Peered::BriefEntityInfo& info, const rpc::MemoryBlock& data)
  {
    if (status != Built)
    {
      entitiesIds.push_back(info);
      int oldSize = entitiesCache.size();
      entitiesOffsets.push_back(oldSize);
      entitiesCache.resize(oldSize+data.size);
      crt::memcpy(entitiesCache.begin()+oldSize, data.size, data.memory, data.size);
      entitiesData.push_back(data);
      for (int i=0;i<entitiesOffsets.size();++i)
      {
        entitiesData[i].memory = entitiesCache.begin()+entitiesOffsets[i];
      }
      all.Add(info.crc);
      changes.changesAppliedBeforeBuilt++;
    } else
    {
      changes.changesAppliedAfterBuilt++;
    }
    
  }

  void Apply(ClientHolder& client, int confirmFrequency)
  {
    if (entitiesIds.size() > 0)
    {
      client.ApplySnapshot(changes.step, all.Get(), entitiesIds, entitiesData);
    }
    client.Rewind(changes.step, confirmFrequency);
  }

  void MarkBuilt() { status = Built; }
  Status GetStatus() const { return status; }
  SnapshotInfo GetChangesInfo() const { return changes; }
private:
  nstl::vector<Peered::BriefEntityInfo> entitiesIds;
  nstl::vector<rpc::MemoryBlock> entitiesData;
  nstl::vector<byte> entitiesCache;
  nstl::vector<int> entitiesOffsets;
  Crc32Checksum all;
  Status status;
  SnapshotInfo changes;
};

}