#pragma once
#include <IOTerabit/MessageBlockFactory.h>
#include <mballocator/MessageBlock.h>

namespace TransportLayer
{
  namespace TL = TransportLayer;

  class MessageBlockAllocator : public Terabit::MessageBlockFactory
  {
    static const unsigned int INDEX_BASE = 6;  //  2 в 6й -> 64байта -> блок минимального размера в фабрике
    static const unsigned int CHAIN_NUMBER = 22 - INDEX_BASE; //  последняя цепочка содержит блоки 2Мб

  public:
    MessageBlockAllocator(char const * _name);
    ~MessageBlockAllocator();

    virtual ACE_Message_Block *alloc_msg (size_t length);
    virtual void free_msg (ACE_Message_Block * mb);

    ACE_Message_Block *alloc_msg (size_t length, MBType::Enum _type, unsigned long long const tag = 0);

    void dump(int tag);

    char const * name() const;

    void threshold(MBType::Enum _type, int _threshold, unsigned long long const * _tag_filter, int _tag_filter_size, bool _logEach = false);
    int  threshold(MBType::Enum _type) const;

  private:
    struct ThresholdData
    {
      ThresholdData()
        :minSample_(-1),
        avgSample_(0.0),
        maxSample_(-1),
        count_(0)
      {
      }

      int   minSample_;
      double avgSample_;
      int   maxSample_;
      int   count_;

      void addSample(int _sample);
    };

    struct msgchain
    {
      enum state
      {
        OPENED,
        CLOSED
      };

      msgchain()
        :head_(0),
        freed_(0),
        allocated_(0),
        state_(OPENED),
        noZeroUseAvgTime_(0.0),
        noZeroUseMaxTime_(-1),
        noZeroUseCount_(0),
        allocCount_(0),
        freeCount_(0)
      {
      }

      MessageBlock* head_;
      unsigned int freed_;
      unsigned int allocated_;
      mutable ACE_Thread_Mutex mutex_;
      state state_;
      double noZeroUseAvgTime_;
      int noZeroUseMaxTime_;
      unsigned long long noZeroUseCount_;
      unsigned long long allocCount_;
      unsigned long long freeCount_;
      ThresholdData thresholdsData[MBType::NUMBER_OF_BLOCK_TYPE];  //  для подсчета threshold'ов времени использования блоков разного типа

      void calcStatistic(int blockUseTime);
    };

    struct ThresholdInfo
    {
      static const unsigned int TAG_FILTER_MAXSIZE = 64;
      ThresholdInfo()
        :threshold_(0), logEach_(false), empty_(true), tag_filter_size(0)
      {
      }

      ThresholdInfo(int _value, unsigned long long const * _tag_filter, int _tag_filter_size, bool _logEach)
        :threshold_(_value), logEach_(_logEach), empty_(true), tag_filter_size(_tag_filter_size)
      {
        if (tag_filter_size > TAG_FILTER_MAXSIZE)
          tag_filter_size = TAG_FILTER_MAXSIZE;

        if (_tag_filter && tag_filter_size)
          memcpy(tag_filter, _tag_filter, tag_filter_size*sizeof(tag_filter[0]));
      }

      int   threshold_;
      bool  logEach_;
      bool  empty_;
      unsigned long long tag_filter[TAG_FILTER_MAXSIZE];
      unsigned int tag_filter_size;
    };

  private:
    unsigned int getIndex(size_t size) const;
    unsigned int getBlockSize(unsigned int index) const;

    void clear();

    void dump_block_use_thresholds(nstl::string& s, int tag, MBType::Enum _type);

  private:
    msgchain chains[CHAIN_NUMBER];  //  2 в степени INDEX_BASE+index - размер блока в цепочке
    ThresholdInfo thresholdInfo[MBType::NUMBER_OF_BLOCK_TYPE];
    nstl::string name_;
  };

  inline
  unsigned int MessageBlockAllocator::getIndex(size_t length) const
  {
    unsigned int idx = 0;
    size_t l = length - 1;
    l >>= INDEX_BASE;

    while(l)
    {
      idx++;
      l >>= 1;
    }

    return idx;
  }

  inline
  unsigned int MessageBlockAllocator::getBlockSize(unsigned int index) const
  {
    return 1 << (INDEX_BASE+index);
  }

  inline
  char const * MessageBlockAllocator::name() const
  {
    return name_.c_str();
  }

  inline
  void MessageBlockAllocator::threshold(MBType::Enum _type, int _threshold, unsigned long long const * _tag_filter, int _tag_filter_size, bool _logEach)
  {
    if (_type < MBType::FIRST_BLOCK_TYPE || _type > MBType::LAST_BLOCK_TYPE)
      return;

    thresholdInfo[_type] = ThresholdInfo(_threshold, _tag_filter, _tag_filter_size, _logEach);
  }

  inline
  int  MessageBlockAllocator::threshold(MBType::Enum _type) const
  {
    if (_type < MBType::FIRST_BLOCK_TYPE || _type > MBType::LAST_BLOCK_TYPE)
      return -1;

    return thresholdInfo[_type].threshold_;
  }
}
