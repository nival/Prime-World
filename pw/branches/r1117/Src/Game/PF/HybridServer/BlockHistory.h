#ifndef BLOCKHISTORY_H_INCLUDED
#define BLOCKHISTORY_H_INCLUDED


namespace Peered
{

class BlockHistory
{
  struct IndexedBlockInfo
  {
    int offset;
    int size;
    int GetEnd() const { return offset+size; }
  };

public:  
  BlockHistory() : startStep(0), startBlock(0), startData(0), serverId(0)
  {
  }

  struct StepInfo
  {
    int startIndex;
    int endIndex;
    int size() const { return endIndex-startIndex; }
  };

  void Append(const void* data, uint size)
  {
    threading::MutexLock lock(locker);
    IndexedBlockInfo info = { buffer.size()+startData, size };
    blocks.push_back(info);
    int oldSize = buffer.size();
    buffer.resize(oldSize+size);
#if defined( NV_WIN_PLATFORM )
    memcpy_s(buffer.begin()+oldSize, size, data, size);
#elif defined( NV_LINUX_PLATFORM )
    memcpy(buffer.begin()+oldSize, data, size);
#endif
  }

  bool CopyStep(int step, nstl::vector<rpc::MemoryBlock>& data, int startIndex=0) 
  {
    threading::MutexLock lock(locker);
    StepInfo stepInfo = GetStep(step);
    int newSize = stepInfo.size()-startIndex;
    if (newSize > 0)
    {
      data.resize(newSize);
      for (int i=startIndex;i<stepInfo.size();++i)
      {
        data[i-startIndex] = GetBlock(stepInfo.startIndex+i);
      }
      return true;
    } else
    {
      data.clear();
      return false;
    }
  }

  template <typename T>
  void CopyStep(int step, nstl::vector<T>& data, int startIndex=0) 
  {
    threading::MutexLock lock(locker);
    StepInfo stepInfo = GetStep(step);
    int newSize = stepInfo.size()-startIndex;
    if (newSize > 0)
    {
      data.resize(newSize);
      for (int i=startIndex;i<stepInfo.size();++i)
      {
        rpc::MemoryBlock block = GetBlock(stepInfo.startIndex+i);
        T* item = data.begin()+i-startIndex;
        NI_ASSERT(sizeof(T) == block.size, "Data sizes should be the same");
        *item = *((T*)block.memory);
      }
    } else
    {
      data.clear();
    }
  }

  // For testing puposes only...
  bool CopyStepsRaw(int fromStep, int toStep, rpc::MemoryBlock & data) 
  {
    if (fromStep > toStep)
      return false;

    threading::MutexLock lock(locker);
    StepInfo fromStepInfo = GetStep(fromStep);
    StepInfo toStepInfo = GetStep(toStep);

    if (toStepInfo.endIndex - fromStepInfo.startIndex <= 0)
      return false;

    const IndexedBlockInfo& fromBlockInfo = blocks[fromStepInfo.startIndex];
    const IndexedBlockInfo& toBlockInfo = blocks[toStepInfo.endIndex - 1];

    //const int totalSize = fromBlockInfo.offset-startData + toBlockInfo.offset-startData + toBlockInfo.size;
    const int totalSize = (toBlockInfo.offset - startData) - (fromBlockInfo.offset - startData);

    if (totalSize <= 0)
      return false;

    data = rpc::MemoryBlock(buffer.begin()+fromBlockInfo.offset-startData, totalSize);

    return true;
  }

  int EraseSteps(int _endStep)
  {
    int result = 0;
    threading::MutexLock lock(locker);
    int step1 = _endStep-startStep;
    if (step1 > 0)
    {
      int block1 = 0;
      if (step1 < steps.size())
      {
        block1 = steps[step1-1];
      } else if (steps.size() > 0)
      {
        block1 = steps[steps.size()-1];
        step1 = steps.size();
      } else
      {
        return 0;
      }
      steps.erase(steps.begin(), steps.begin()+step1);
      block1 -= startBlock;
      if (block1 > 0)
      {
        int data1 = (block1-1 >= 0)?blocks[block1-1].GetEnd():0;
        blocks.erase(blocks.begin(), blocks.begin()+block1);
        result = block1;
        data1 -= startData;
        if (data1 > 0)
        {
          buffer.erase(buffer.begin(), buffer.begin()+data1); 
          startData += data1;
        }
        startBlock += block1;
      }
      startStep += step1;
    }
    return result;
  }

  void FinishStep()
  {
    threading::MutexLock lock(locker);
    steps.push_back(blocks.size()+startBlock);
  }

  int GetAccumulatedItemsCount()
  {
    if (steps.size() > 0)
    {
      int lastIndex = *(steps.end()-1);
      return blocks.size()-lastIndex;
    } else
    {
      return blocks.size();
    }
  }

  int GetStartStep() const { return startStep; }
  int GetPendingStep() const { return startStep+steps.size(); }
  void SetServerId(TSessionId _serverId) { serverId = _serverId; }

private:
  StepInfo GetStep(int _step) const 
  {
    StepInfo result = {0, 0};
    int step = _step-startStep;
    if (step >=0 && step < steps.size())
    {
      result.endIndex = steps[step]-startBlock;
      result.startIndex = (step-1 >= 0) ? steps[step-1]-startBlock:0;
    }
    else
    {
      NI_ALWAYS_ASSERT(NI_STRFMT(
        "GameServer: BlockHistory::GetStep: Step not found (sid=%016x step=%d startStep=%d stepsCount=%d)", 
          serverId, _step, startStep, steps.size()));
    }
    return result;
  }

  rpc::MemoryBlock GetBlock(int index)
  {
    const IndexedBlockInfo& info = blocks[index];
    return rpc::MemoryBlock(buffer.begin()+info.offset-startData, info.size);
  }

  threading::Mutex locker; // trash, should be lock free algo here
  nstl::vector<int> steps;
  nstl::vector<IndexedBlockInfo> blocks;
  nstl::vector<byte> buffer;
  int startStep;
  int startBlock;
  int startData;
  TSessionId serverId;
};

}
#endif
