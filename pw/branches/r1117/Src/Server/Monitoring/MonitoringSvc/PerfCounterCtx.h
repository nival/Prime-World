#pragma once

#include "Network/TransportTypes.h"
#include "System/DebugVar.h"

namespace Monitoring
{
  class PerfCounterCtx : public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_1(PerfCounterCtx, BaseObjectMT);

  public:

    PerfCounterCtx()
      :samplingPeriod_(0), time_(0), lastSampleRecvTime_(0), inprogress_(false)
    {}

    PerfCounterCtx(nstl::string const & _path, Transport::TServiceId const & _svcid,
      nstl::string const & _name, NDebug::DebugVarType::Enum _type = NDebug::DebugVarType::None, unsigned int _period = 10)
      :path_(_path),
      svcid_(_svcid),
      name_(_name),
      type_(_type),
      samplingPeriod_(_period),
      time_(0),
      lastSampleRecvTime_(0),
      inprogress_(false)
    {}

  public:
    virtual nstl::wstring const & val() const;
    void val(nstl::wstring const & _val);

    nstl::string const & path() const;
    void path(nstl::string const & _path);

    NDebug::DebugVarType::Enum type() const;
    void type(NDebug::DebugVarType::Enum _type);

    Transport::TServiceId const & svcid() const;
    nstl::string const & name() const;

    unsigned int samplingPeriod() const;

    time_t  lastSampleRecvTime() const;
    void  lastSampleRecvTime(time_t _t);

    bool inprogress() const;
    void inprogress(bool _flag);

    time_t time() const;
    void time(time_t _t);

  protected:
    mutable nstl::wstring val_;
    nstl::string path_;
    NDebug::DebugVarType::Enum type_;
    Transport::TServiceId svcid_;
    nstl::string name_;
    mutable time_t       time_;    //  time of last sample
    unsigned int samplingPeriod_;  //  seconds
    time_t       lastSampleRecvTime_;
    bool         inprogress_;
  };

  inline
  void PerfCounterCtx::val(nstl::wstring const & _val)
  {
    val_ = _val;
  }

  inline
  nstl::string const & PerfCounterCtx::path() const
  {
    return path_;
  }

  inline
  void PerfCounterCtx::path(nstl::string const & _path)
  {
    path_ = _path;
  }

  inline
  NDebug::DebugVarType::Enum PerfCounterCtx::type() const
  {
    return type_;
  }

  inline
  void PerfCounterCtx::type(NDebug::DebugVarType::Enum _type)
  {
    type_ = _type;
  }

  inline
  Transport::TServiceId const & PerfCounterCtx::svcid() const
  {
    return svcid_;
  }

  inline
  nstl::string const & PerfCounterCtx::name() const
  {
    return name_;
  }

  inline
  unsigned int PerfCounterCtx::samplingPeriod() const
  {
    return samplingPeriod_;
  }

  inline
  time_t PerfCounterCtx::lastSampleRecvTime() const
  {
    return lastSampleRecvTime_;
  }

  inline
  void PerfCounterCtx::lastSampleRecvTime(time_t _t)
  {
    lastSampleRecvTime_ = _t;
  }

  inline
  bool PerfCounterCtx::inprogress() const
  {
    return inprogress_;
  }

  inline
  void PerfCounterCtx::inprogress(bool _flag)
  {
    inprogress_ = _flag;
  }

  inline
  time_t PerfCounterCtx::time() const
  {
    return time_;
  }

  inline
  void PerfCounterCtx::time(time_t _t)
  {
    time_ = _t;
  }
}
