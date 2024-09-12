#pragma once

#include "Server/LiveMMaking/RatingSortMmLogic.h"
#include "SimpleParser.h"


namespace mm_test
{

// expect [10, 20] {1, 2} {3, 4}

class Expectation : public BaseObjectST, public simple_parser::Parser
{
  NI_DECLARE_REFCOUNT_CLASS_1( Expectation, BaseObjectST );

public:
  Expectation() :
  clean( false )
  {
  }

  bool Clean() const { return clean; }
  void Clear() { clean = true; }

  typedef simple_parser::ValuesVector<int> TLineUp[2];

  const simple_parser::ValuesRange<timer::Time> & TimeRange() const { return timeRange; }
  const TLineUp & Sides() { return sides; }

  bool Parse( simple_parser::Context & _ctx )
  {
    if ( !timeRange.Parse( _ctx ) )
      return false;

    for ( int i = 0; i < 2; ++i )
      if ( !sides[i].Parse( _ctx ) )
        return false;

    return true;
  }

private:
  simple_parser::ValuesRange<timer::Time>   timeRange;
  simple_parser::ValuesVector<int>          sides[2];
  bool                                      clean;
};

} //namespace mm_test
