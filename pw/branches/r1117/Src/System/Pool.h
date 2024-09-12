#ifndef __POOL_H_
#define __POOL_H_
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#ifdef WIN32
#define DECLSPECNOINL __declspec(noinline)
#else
#define DECLSPECNOINL
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, int N_BLOCK_SIZE = 4096>
class CPool
{
	struct SBlock
	{
		T data[N_BLOCK_SIZE];
	};
	list<SBlock> data;
	T *pCurrent, *pLast;

	void operator=( const CPool &a ) { NI_ALWAYS_ASSERT( "" ); }
	CPool( const CPool &a ) { NI_ALWAYS_ASSERT( "" ); }
	int operator&( IBinSaver &f ) { NI_ALWAYS_ASSERT( "" ); return 0; }
	DECLSPECNOINL void AllocNewBlock()
	{
		SBlock *pBlock = &*data.insert( data.end() );
		pCurrent = &pBlock->data[-1];
		pLast = &pBlock->data[N_BLOCK_SIZE - 1];
	}
public:
	struct SIterator
	{
		T *p, *pBlockStart;
		typename list<SBlock>::iterator i;
		CPool *pPool;

		SIterator(): pPool(0), p(0), pBlockStart(0) {}
		SIterator( CPool *_pPool ) { Assign( _pPool ); }
		void Assign( CPool *_pPool )
		{
			pPool = _pPool;
			i = pPool->data.end();
			if ( !pPool->data.empty() )
			{
				--i;
				pBlockStart = &i->data[-1];
			}
			else
				pBlockStart = 0;
			p = pPool->pCurrent;
		}
		void operator--() 
		{
			ASSERT(pPool);
			--p; 
			if ( p == pBlockStart ) 
			{
				if ( i == pPool->data.begin() )
				{
					p = 0;
					pBlockStart = 0;
					return;
				}
				--i;
				p = &i->data[N_BLOCK_SIZE - 1];
				pBlockStart = &i->data[-1];
			}
		}
		bool operator==( const SIterator &a ) const { return p == a.p; }
		bool operator!=( const SIterator &a ) const { return p != a.p; }
	};
	explicit CPool(): pCurrent(0), pLast(0) {}
	T* Alloc()
	{
		if ( pCurrent == pLast )
			AllocNewBlock();
		return ++pCurrent;
	}
	void Clear() { data.clear(); pCurrent = pLast = 0; }
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
