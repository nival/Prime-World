#pragma once

#include "Network/TransportTypes.h"
#include "System/DebugVar.h"

namespace Monitoring
{
  class PerfCounter : public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_1(PerfCounter, BaseObjectMT);

  public:

    PerfCounter()
      :id_(0),
      samplingPeriod_(0),
      toCumulate_(false)
    {}

    PerfCounter(int _id, nstl::string const & _name, NDebug::IDebugVar* _debugVar, bool _toCumulate, int _samplingPeriod)
      :id_(_id),
      name_(_name),
      debugVar_(_debugVar),
      samplingPeriod_(_samplingPeriod),
      toCumulate_(_toCumulate)
    {}

  public:

    int id() const { return id_; }

    nstl::string const & name() const { return name_; }
    virtual nstl::wstring const & val() const;

    NDebug::DebugVarType::Enum type() const { return NDebug::DebugVarType::Enum(debugVar_->GetType()); }
    void type(NDebug::DebugVarType::Enum _type);

    int samplingPeriod() const { return samplingPeriod_; }

    bool toCumulate() const { return toCumulate_; }

  protected:
    int id_;
    NDebug::IDebugVar* debugVar_;
    nstl::string name_;
    int samplingPeriod_;  //  seconds
    mutable nstl::wstring val_;
    bool toCumulate_;
  };
}
