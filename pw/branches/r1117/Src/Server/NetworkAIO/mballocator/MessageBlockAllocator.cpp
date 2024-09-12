#include "mballocator/stdafx.h"
#include "mballocator/MessageBlockAllocator.h"

namespace TransportLayer
{
  MessageBlockAllocator::MessageBlockAllocator(char const * _name)
    :name_(_name)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);
  }

  MessageBlockAllocator::~MessageBlockAllocator()
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    dump(-2);
    clear();
  }

  ACE_Message_Block* MessageBlockAllocator::alloc_msg(size_t length)
  {
    return alloc_msg(length, MBType::NOTYPE_BLOCK);
  }

  ACE_Message_Block* MessageBlockAllocator::alloc_msg (size_t length, MBType::Enum _type, unsigned long long const _tag)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    if (!length)
      return 0;

    //  get index
    unsigned int idx = getIndex(length);
    if (idx > CHAIN_NUMBER - 1)
      return 0;

    msgchain* chain = &chains[idx];
    MessageBlock* mb = 0;

    ACE_Guard<ACE_Thread_Mutex> lock(chain->mutex_);
    NI_VERIFY(msgchain::OPENED == chain->state_, "", return 0);

    if (chain->head_)
    {
      mb = chain->head_;
      chain->head_ = static_cast<MessageBlock*>(mb->cont());
      mb->cont(0);
      NI_ASSERT(chain->freed_ > 0, "");
      chain->freed_--;

      mb->reset();
      mb->size(length);
    }
    else
    {
      unsigned int size = getBlockSize(idx);
      mb = new MessageBlock(size);
      mb->size(length);
    }

    mb->type(_type);
    mb->tag(_tag);

    chain->allocated_++;
    chain->allocCount_++;

    NHPTimer::STime tm;
    NHPTimer::GetTime(tm);
    mb->alloctime(tm);

    return mb;
  }

  void MessageBlockAllocator::free_msg (ACE_Message_Block * mb)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    NI_ASSERT(mb, "");

    MessageBlock* _mb = static_cast<MessageBlock*>(mb);

    NHPTimer::STime freetime;
    NHPTimer::GetTime(freetime);

    while (_mb != 0)
    {
      MessageBlock *tmp = _mb;
      _mb = static_cast<MessageBlock*>(tmp->cont());

      unsigned int size = tmp->size();
      unsigned int idx = getIndex(size);

      if (idx > CHAIN_NUMBER - 1)
      {
        tmp->cont(0);
        tmp->release();
        continue;
      }

      msgchain* chain = &chains[idx];

      ACE_Guard<ACE_Thread_Mutex> lock(chain->mutex_);
      NI_ASSERT(msgchain::OPENED == chain->state_, "");
      if (msgchain::OPENED == chain->state_)
      {
        NHPTimer::STime delta = freetime - tmp->alloctime();
        int usetime = NHPTimer::Time2Milliseconds(delta);
        ThresholdInfo& ti = thresholdInfo[tmp->type()];
        if (ti.threshold_ && usetime > ti.threshold_)
        {
          if (ti.empty_) ti.empty_ = false;

          ThresholdData& td = chain->thresholdsData[tmp->type()];
          td.addSample(usetime);
          if (ti.logEach_)
          {
            LOG_M(0).Trace("Block use time threshold reached(bsz=%d usetime=%d type=%d threshold=%d tag=%d)",
                            getBlockSize(idx), usetime, (int)tmp->type(), ti.threshold_, tmp->tag());
          }
          else
          if (ti.tag_filter_size && tmp->tag())
          {
            for(unsigned int i = 0; i < ti.tag_filter_size; ++i)
            {
              if (tmp->tag() == ti.tag_filter[i])
              {
                LOG_M(0).Trace("Block use time threshold reached for tag(tag=%d bsz=%d usetime=%d type=%d threshold=%d)",
                               tmp->tag(), getBlockSize(idx), usetime, (int)tmp->type(), ti.threshold_);
                break;
              }
            }
          }
        }

        tmp->cont(chain->head_);
        chain->head_ = tmp;
        chain->freed_++;
        NI_ASSERT(chain->allocated_ > 0, "");
        chain->allocated_--;
        chain->freeCount_++;

        chain->calcStatistic(usetime);
      }
      else
      {
        tmp->cont(0);
        tmp->release();
      }
    }
  }

  void MessageBlockAllocator::dump(int tag)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    ThresholdInfo const & nti = thresholdInfo[MBType::NOTYPE_BLOCK];
    ThresholdInfo const & rti = thresholdInfo[MBType::READ_BLOCK];
    ThresholdInfo const & wti = thresholdInfo[MBType::WRITE_BLOCK];

    nstl::string s;
    s.reserve(4096);
            s.append("\n===========================================================================================================================\n");
    s.append(NI_STRFMT("MessageBlockAllocator dump(name=%s tag=%d nt=%d nt_data=%d rt=%d rt_data=%d wt=%d wt_data=%d)                                                                                \n", 
      name_.c_str(), tag, nti.threshold_, int(nti.empty_ == false), 
      rti.threshold_, int(rti.empty_ == false), wti.threshold_, int(wti.empty_ == false)));
              s.append("===========================================================================================================================\n");
    s.append(NI_STRFMT("blocks       | ablocks | fblocks | tblocks |      bytes |       acount |       fcount |  nzu_avg | nzu_max |      nzu_cnt |\n"));

    unsigned int allocated_total = 0;
    unsigned int freed_total = 0;
    unsigned long long acount_total = 0;
    unsigned long long fcount_total = 0;
    for (unsigned int i=0; i < CHAIN_NUMBER; ++i)
    {
      msgchain* chain = &chains[i];
      unsigned int allocated = 0;
      unsigned int freed = 0;
      double noZeroUseAvgTime = 0.0;
      int noZeroUseMaxTime = 0;
      unsigned long long noZeroUseCount = 0;
      unsigned long long allocCount = 0;
      unsigned long long freeCount = 0;

      {
        ACE_Guard<ACE_Thread_Mutex> lock(chain->mutex_);
        allocated = chain->allocated_;
        freed = chain->freed_;
        noZeroUseAvgTime = chain->noZeroUseAvgTime_;
        noZeroUseMaxTime = chain->noZeroUseMaxTime_;
        noZeroUseCount = chain->noZeroUseCount_;
        allocCount = chain->allocCount_;
        freeCount = chain->freeCount_;
      }

      unsigned int blocksize = getBlockSize(i);
      s.append(NI_STRFMT("block %7d| %7d | %7d | %7d | %10d | %12d | %12d | %8.3f | %7d | %12d |\n", 
        blocksize, allocated, freed, allocated+freed, blocksize*(allocated+freed), allocCount, freeCount, noZeroUseAvgTime, noZeroUseMaxTime, noZeroUseCount));
      allocated_total += allocated*blocksize;
      freed_total += freed*blocksize;
      acount_total += allocCount;
      fcount_total += freeCount;
    }

    s.append("---------------------------------------------------------------------------------------------------------------------------\n");
    s.append(NI_STRFMT("summary      | allocated bytes               %10d | allocation count %10d |                                   |\n",allocated_total, acount_total));
    s.append(NI_STRFMT("             | freed bytes                   %10d | free count       %10d |                                   |\n",freed_total, fcount_total));
    s.append(NI_STRFMT("             | total bytes                   %10d |                             |                                   |\n",allocated_total+freed_total));
    s.append("===========================================================================================================================\n");
    LOG_M(0) << s;

    //  dump no-type block threshold statistic
    dump_block_use_thresholds(s, tag, MBType::NOTYPE_BLOCK);

    //  dump read block threshold statistic
    dump_block_use_thresholds(s, tag, MBType::READ_BLOCK);

    //  dump write block threshold statistic
    dump_block_use_thresholds(s, tag, MBType::WRITE_BLOCK);
  }

  void MessageBlockAllocator::dump_block_use_thresholds(nstl::string& s, int tag, MBType::Enum _type)
  {
    ThresholdInfo const & ti = thresholdInfo[_type];

    if (ti.threshold_ <= 0 || ti.empty_)
      return;

    s.clear();
            s.append("\n============================================================\n");
    s.append(NI_STRFMT("Block use thresholds dump(name=%s tag=%d type=%d threshold=%d)\n", name_.c_str(), tag, (int)_type, ti.threshold_));
              s.append("============================================================\n");
    s.append(NI_STRFMT("blocks       | min(ms) |  avg(ms) | max(ms) |        count |\n"));

    for (unsigned int i=0; i < CHAIN_NUMBER; ++i)
    {
      msgchain* chain = &chains[i];
      int   minSample = 0;
      double avgSample = 0.0;
      int   maxSample = 0;
      int   count = 0;

      {
        ACE_Guard<ACE_Thread_Mutex> lock(chain->mutex_);
        ThresholdData const & td = chain->thresholdsData[_type];
        minSample = td.minSample_;
        avgSample = td.avgSample_;
        maxSample = td.maxSample_;
        count = td.count_;
      }

      unsigned int blocksize = getBlockSize(i);
      s.append(NI_STRFMT("block %7d| %7d | %8.3f | %7d | %12d |\n", blocksize, minSample, avgSample, maxSample, count));
    }

    s.append("============================================================\n");
    LOG_M(0) << s;
  }

  void MessageBlockAllocator::clear()
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    for (unsigned int i=0; i < CHAIN_NUMBER; ++i)
    {
      msgchain* chain = &chains[i];
      ACE_Message_Block *mb = 0;

      {
        ACE_Guard<ACE_Thread_Mutex> lock(chain->mutex_);
        mb = chain->head_;
        chain->head_ = 0;
        chain->freed_ = 0;
        NI_ASSERT(msgchain::OPENED == chain->state_, "");
        chain->state_ = msgchain::CLOSED;
      }

      while (mb != 0)
      {
        ACE_Message_Block *tmp = mb;
        mb = tmp->cont ();
        tmp->cont (0);
        tmp->release ();
      }
    }
  }

  void MessageBlockAllocator::msgchain::calcStatistic(int blockUseTime)
  {
    if (blockUseTime <= 0)
      return;

    noZeroUseAvgTime_ = noZeroUseAvgTime_ * noZeroUseCount_;
    noZeroUseAvgTime_ += blockUseTime;
    noZeroUseCount_++;
    noZeroUseAvgTime_ = noZeroUseAvgTime_/noZeroUseCount_;

    if (-1 == noZeroUseMaxTime_ || noZeroUseMaxTime_ < blockUseTime)
      noZeroUseMaxTime_ = blockUseTime;
  }

  void MessageBlockAllocator::ThresholdData::addSample(int _sample)
  {
    if (-1 == minSample_ || minSample_ > _sample)
      minSample_ = _sample;

    if (-1 == maxSample_ || maxSample_ < _sample)
      maxSample_ = _sample;

    avgSample_ = avgSample_*count_;
    avgSample_ += _sample;
    ++count_;
    avgSample_ /= count_;
  }
}
