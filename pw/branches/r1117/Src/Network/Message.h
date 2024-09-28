#pragma once

namespace Transport
{
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	struct MessageBase
	{
		virtual int GetTypeId() const = 0;

		virtual ~MessageBase() {}
		virtual int operator&( IBinSaver &f ) = 0;

		typedef MessageBase* (*CreateFun)();
    typedef void (*DestroyFun)(MessageBase*);

		template <typename T>
		const T* Query() const
		{
			return (T*)_Query(T::GetType());
		}

		inline const void* _Query(uint id) const
		{
			return (id == (uint)GetTypeId())?this:0;
		}
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename TypeEnum>
	struct TypedMessageBase : public MessageBase
	{
		virtual int GetTypeId() const { return GetType(); }
		virtual TypeEnum GetType() const = 0;
	};
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class MessageFactory
	{
    typedef nstl::pair<MessageBase::CreateFun, MessageBase::DestroyFun> Funcs;
    typedef hash_map<int, Funcs> MessagesMap;
    MessagesMap messages;
	public:
		MessageFactory() {}
		void Clear()
		{
			messages.clear();
		}

		void RegisterInFactory( int type, MessageBase::CreateFun fun, MessageBase::DestroyFun = NULL );

		MessageBase* Create( int type );
    void Destroy(MessageBase* msg);
	};
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	MessageFactory* CCDECL GetGlobalMessageFactory();
}
