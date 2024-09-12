#pragma once
#include <Server/Censorship/ICensorClient.h>
#include <ChatSvc/ChatContext.h>

namespace chat
{
  class ChannelContext;
  class UserContext;


  //Another one brilliant linked list implementation
  class CensorCheckOp : public censorship::ICensorClientCallback, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_2( CensorCheckOp, ICensorClientCallback, BaseObjectMT );

  public:
    CensorCheckOp( ChannelContext * _channel, UserContext * _user, timer::DecodedTime _msgtime, wstring const & _srcText ) :
    channel_( _channel ),
    user_( _user ),
    msgtime_( _msgtime ),
    sourceText( _srcText ),
    filteredText( _srcText ),
    finished( false )
    {}

    ~CensorCheckOp() {}

    //ChannelContext * channel() const { return channel_; }
    UserContext * user() const { return user_; }
    const timer::DecodedTime & MsgTime() const { return msgtime_; }
    const wstring & SrcText() const { return sourceText; }
    const wstring & FilteredText() const { return filteredText; }

    bool Finished() const { return finished; }

  private:
    //  censorship::ICensorClientCallback
    void TextCheckResult( censorship::TRequestId _reqId, censorship::TAuxId _auxId, censorship::ECheckResult::Enum _result, const wstring & _filteredText );

    bool TryToComplete();

    WeakMT<ChannelContext> channel_;
    StrongMT<UserContext> user_;
    timer::DecodedTime msgtime_;
    wstring sourceText, filteredText;
    bool finished;
  };
}
