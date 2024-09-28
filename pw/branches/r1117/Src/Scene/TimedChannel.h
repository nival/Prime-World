#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NScene
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct TimedChannelValueBase
{
	Time startTime;
	Time GetEndTime() const { return startTime; } 
	bool IsEssential() const { return true; }

	TimedChannelValueBase(): startTime(ANIM_START_TIME) {}
	TimedChannelValueBase( Time _startTime ): startTime(_startTime) {}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class Value>
struct TimedChannel 
{
	list<Value> data;
	bool neverUpdated;
public:
	TimedChannel() : neverUpdated( true ) {}

	bool Update( Time cur )
	{
		if ( data.empty() )
			return false;

		bool changed = neverUpdated;
		neverUpdated = false;
		while ( data.size() > 1 )
		{
			Value& next = *( ++data.begin() );
			if( next.startTime > cur )
				break;

			changed = true;
			data.pop_front();
		}

		return changed;
	}

	bool NeedUpdate( Time cur )
	{
		if ( data.empty() )
			return false;

		if ( neverUpdated )
			return true;

		if ( data.size() == 1 )
			return false;

		Value& next = *( ++data.begin() );
		return next.startTime <= cur;
	}

	void Purge( Time t )
	{
		list<Value>::iterator it = data.begin();
		for ( ; it != data.end(); ++it )
		{
			if ( it->startTime > t )
			{
				if ( it != data.begin() )
					--it;
				data.erase( it, data.end() );
				break;
			}
		}
	}

	void Add( const Value &value )
	{
		data.push_back( value );
	}

	void Insert( const Value &value )
	{
		list<Value>::iterator it = data.begin();
		for ( ; it != data.end() && it->startTime <= value.startTime; ++it )
			;
		data.insert( it, value );
	}

	bool Empty() const 
	{
		return data.empty();
	}

	const Value &Last() const
	{
		if ( data.empty() )
		{
			static Value tmp = Value();
			return tmp;
		}
		return data.back();
	}

	const Value &Current() const
	{
		if ( data.empty() )
		{
			static Value tmp = Value();
			return tmp;
		}
		return data.front();
	}

	Time GetIdleTime() const
	{
		if ( data.empty() )
			return ANIM_START_TIME;

		list<Value>::const_iterator it = data.end();
		do 
		{
			--it;
			const Value& val = *it;
			if ( val.IsEssential() )
				return val.GetEndTime();
		}
		while ( it != data.begin() );

		return ANIM_START_TIME;
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class Value>
struct TimedQueue 
{
	list<Value> data;
public:
	TimedQueue() {}

	void Add( const Value &value )
	{
		NI_VERIFY( data.empty() || data.back().startTime <= value.startTime
			, NStr::StrFmt("Timed value error: adding value @ %f, last value @ %f. Ask S.Eliseev.", value.startTime, data.back().startTime ), return );
		data.push_back( value );
	}

	void Insert( const Value &value )
	{
		list<Value>::iterator it = data.begin();
		for ( ; it != data.end() && it->startTime <= value.startTime; ++it )
			;
		data.insert( it, value );
	}

	bool HasCommands( Time cur ) const
	{
		return !data.empty() && data.front().startTime <= cur;
	}

	bool Next( Time cur )
	{
		if ( data.empty() || data.front().startTime > cur )
			return false;

		data.pop_front();
		return true;
	}

	const Value& Current()
	{
		if ( data.empty() )
		{
			static Value tmp = Value();
			return tmp;
		}
		return data.front();
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct TimedPosition : public TimedChannelValueBase
{
	Matrix43 position;
};
typedef TimedChannel<TimedPosition> TTimedPositionChannel;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
