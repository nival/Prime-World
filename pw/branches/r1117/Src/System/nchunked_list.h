#pragma once
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace nstl
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, size_t chunkSize = 64>
class chunked_list
{
	struct Chunk
	{
		char data[sizeof(T) * chunkSize];
		size_t allocated;		
		Chunk *prev;

		Chunk() : allocated( 0 ), prev( 0 ) {}
		~Chunk()
		{
			_Destroy( (T*)data, (T*)data + allocated );
		}

		T* GetItem( size_t n ) { return (T*)data + n; }
	};

	Chunk *pLastChunk;

	void _AllocChunk()
	{
		Chunk *pNewChunk = new Chunk();
		pNewChunk->prev = pLastChunk;
		pLastChunk = pNewChunk;
	}

	T *_AllocItem() 
	{
		if ( !pLastChunk || pLastChunk->allocated >= chunkSize )
			_AllocChunk();
		
		return (T*)(pLastChunk->data + sizeof(T) * (pLastChunk->allocated++) ); 
	}

public:
	chunked_list() : pLastChunk(0) {};

	chunked_list( const chunked_list &other ) : pLastChunk(0) { NI_ASSERT( other.empty(), "Copying not empty list, (performance hit)" ); }
	const chunked_list &operator =( const chunked_list &other ) { clear(); NI_ASSERT( other.empty(), "Copying not empty list, (performance hit)" ); return *this; }

	~chunked_list()  { clear(); }
	bool empty() const { return pLastChunk == 0 || ( pLastChunk->allocated == 0 && pLastChunk->prev == 0 ); }
	void clear() 
	{ 
		Chunk *chunk = pLastChunk;
		pLastChunk = 0; 
		while( chunk ) 
		{
			Chunk *temp = chunk;
			chunk = chunk->prev;
			delete temp;			
		}; 
	}

	T& add( const T& __x ) 
	{ 
		T *p = _AllocItem(); 
		construct( p, __x ); 
		return *p; 
	}

	T& add( ) 
	{ 
		T *p = _AllocItem(); 
		construct( p ); 
		return *p; 
	}

	template<class TRef>
	struct _it
	{
		Chunk *chunk;
		size_t pos;

		_it() : chunk(0), pos(0) {};
		_it( Chunk *_chunk ) : chunk(_chunk), pos(0) {};

		template<class TR>
		_it( const typename chunked_list<T, chunkSize>::template _it<TR> &a ) : chunk(a.chunk), pos(a.pos) 
		{
			// Type conversion check
			TR *pOther = 0;	TRef *p = pOther;	p;
		}

		TRef& operator *() { return *chunk->GetItem( pos ); }
		TRef* operator ->() { return chunk->GetItem( pos ); }
		_it &operator ++() { ++pos; if ( pos == chunk->allocated ) { chunk = chunk->prev; pos = 0; }; return *this; }
		operator bool() const { return chunk != 0; }
	};

	typedef /*typename*/ _it<T> iterator;
	typedef /*typename*/ _it<const T> const_iterator;

	iterator begin() 
	{ 
		if ( pLastChunk && pLastChunk->allocated == 0 )
			return iterator( pLastChunk->prev );
		return iterator( pLastChunk ); 
	}
	const_iterator begin() const 
	{ 
		if ( pLastChunk && pLastChunk->allocated == 0 )
			return iterator( pLastChunk->prev );
		return iterator( pLastChunk ); 
	};

	iterator remove( iterator &__pos )
	{
		T *removeItem = &(*__pos);
		_Destroy( removeItem );

		if ( pLastChunk->allocated == 0 )
		{
			Chunk *prevChunk = pLastChunk->prev;
			delete pLastChunk;
			pLastChunk = prevChunk;
		}

		T *lastItem = pLastChunk->GetItem( pLastChunk->allocated - 1 );
		--pLastChunk->allocated;

		if ( lastItem != removeItem )
		{
			construct( removeItem, *lastItem );
			_Destroy( lastItem );
			if ( __pos.chunk != pLastChunk )
				++__pos;
			return __pos;
		}
		else
		{			 
			return iterator( pLastChunk->prev );
		}
	}

	void swap( chunked_list<T> &__x )
	{
		::swap( pLastChunk, __x.pLastChunk );
	}
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
