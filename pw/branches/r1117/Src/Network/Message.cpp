#include "stdafx.h"
#include "Message.h"
#include "TransportMessages.h"

namespace Transport
{
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void MessageFactory::RegisterInFactory( int type, MessageBase::CreateFun fun, MessageBase::DestroyFun dfun)
	{
		MessagesMap::iterator it = messages.find( type );

    if ( it != messages.end() ) //CRAP for multiple build paths ( from Town.component and PF.sln )
      return;
    // NI_VERIFY( it == messagesMap.end(), NI_STRFMT( "Chat message type id=%d is already registred",	type ), return );

    messages[type] = nstl::pair<MessageBase::CreateFun, MessageBase::DestroyFun>(fun, dfun);
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	MessageBase* MessageFactory::Create( int type )
	{
		MessagesMap::iterator it = messages.find( type );

		if ( it != messages.end() )
			return it->second.first();

		systemLog(NLogg::LEVEL_WARNING) << "Unknown type of message: " << type; // был NI_ALWAYS_ASSERT
		return 0;
	}

  void MessageFactory::Destroy(MessageBase* msg)
  {
    MessagesMap::iterator it = messages.find(msg->GetTypeId());
    if (messages.end() == it)
      return;

    if (it->second.second)
      it->second.second(msg);
    else
      delete msg;
  }

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	namespace
	{
		class SMessageFactoryGuard
		{
			MessageFactory* factory;

		public:
			SMessageFactoryGuard() : factory(0) {}
			~SMessageFactoryGuard() { delete factory; }

			MessageFactory* Get()
			{
				if ( !factory )
					factory = new MessageFactory();

				return factory; 
			}
		};
	}

#if defined( NV_WIN_PLATFORM )
	MessageFactory* __cdecl GetGlobalMessageFactory()
#elif defined( NV_LINUX_PLATFORM )
    MessageFactory* GetGlobalMessageFactory()
#endif
	{
		static SMessageFactoryGuard messageFactoryGuard;
		return messageFactoryGuard.Get();
	}
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}