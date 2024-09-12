#include "ChatSvc/stdafx.h"
#include "ChatSvc/ChatChannelHistory.h"

NI_DEFINE_REFCOUNT(chat::ChannelHistory);

namespace chat
{

void ChannelHistory::addMessage( const HistoryMsg & _msg )
{
  if ( !historyCapacity_ )
    return;

  history_.push_back( _msg );

  while ( history_.size() > (int)historyCapacity_ )
    history_.erase( history_.begin() );
}

}
