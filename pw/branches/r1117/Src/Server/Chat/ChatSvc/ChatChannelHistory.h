#pragma once
#include <ChatTypes.h>

namespace chat
{

class UserContext;

struct HistoryMsg
{
  timer::DecodedTime time;
  StrongMT<UserContext> userctx;
  MessageText sourceText;
  MessageText filteredText;

  HistoryMsg()
  {}

  HistoryMsg( const StrongMT<UserContext> & _userctx, const timer::DecodedTime & _time, const MessageText & _srcText, const MessageText & _filrdText ) :
  userctx( _userctx ),
  time( _time ),
  sourceText( _srcText ),
  filteredText( _filrdText )
  {}
};

class ChannelHistory : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( ChannelHistory, BaseObjectMT );

public:
  typedef list<HistoryMsg> HistoryT;

public:
  ChannelHistory( uint _historyCapacity ) :
  historyCapacity_( _historyCapacity )
  {}

  ~ChannelHistory()
  {}

public:
  void addMessage( const HistoryMsg & _msg );
  HistoryT const & history() const { return history_; }
  uint capacity() const { return historyCapacity_; }

  void clear() {
    history_.clear();
  }

private:
  HistoryT history_;
  uint historyCapacity_;
};

} //namespace chat

