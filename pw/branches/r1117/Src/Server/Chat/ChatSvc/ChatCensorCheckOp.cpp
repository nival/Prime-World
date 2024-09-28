#include <ChatSvc/ChatCensorCheckOp.h>
#include <ChatSvc/ChatUserContext.h>
#include <ChatSvc/ChatSvcLogging.h>

namespace chat
{

//  censorship::ICensorClientCallback
void CensorCheckOp::TextCheckResult( censorship::TRequestId _reqId, censorship::TAuxId _auxId, censorship::ECheckResult::Enum _result, const wstring & _filteredText )
{
  if ( finished )
  {
    LOG_W(CHATLOG).Trace("Operation already completed (userG=%d useridL=%d)", user_->useridGlobal(), user_->useridLocal() );
    return;
  }

  if ( _result == censorship::ECheckResult::Dirty )
    filteredText = _filteredText;

  finished = true;
}

}
