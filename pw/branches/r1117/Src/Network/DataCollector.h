#pragma once
#include "../System/NonCopyable.h"
#include "../System/nalgobase.h"

#ifdef min
	#undef min
#endif
#ifdef max
	#undef max
#endif

namespace Network
{
	class DataCollector
		: private NonCopyable
	{
		char* destination;
		unsigned int max_size;
		unsigned int counter;
	public:
		DataCollector(char* destination, unsigned int max_size)
		{
			set(destination, max_size);
		}

		const char* append(const char* data, unsigned int& size) 
		{
			const unsigned int write_size = nstl::min( size, max_size - counter );
			memcpy( destination + counter, data, write_size );
			size -= write_size;
			counter += write_size;
			return size > 0 ? data + write_size : 0;
		}

		void set( char* _destination, unsigned int _max_size )
		{
			destination = _destination;
			max_size = _max_size;
			counter = 0;
		}

		void reset() 
		{
			counter = 0;
		}

		bool isReady() const 
		{
			return counter >= max_size;
		}
	};
}