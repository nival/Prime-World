#ifndef __LOCK_FREE_STACK_H_INCLUDED__50671__
#define __LOCK_FREE_STACK_H_INCLUDED__50671__

#include "atomic.h"
#include "Stack.h"

namespace nvl {

	template< typename T > class CLFStack
	{
	public:

		~CLFStack()
		{ DestroyStack( m_HeadNode ); }

		void Push( T * pEntity )
		{
			assert( NULL != pEntity );

			T * pCurrentHead;

			do {

				pCurrentHead = m_HeadNode;
				pEntity->SetNextEntity( pCurrentHead );

			} while ( m_HeadNode.compare_exchange_strong( pCurrentHead, pEntity ) == false );
		}

		void PushStack( T * pStack )
		{
			assert( NULL != pStack );

			T * pLastEntity = FindLastStackEntity( pStack );

			do {

				pLastEntity->SetNextEntity( m_HeadNode.load( nstd::memory_order_acquire ) );

			} while ( m_HeadNode.compare_exchange_strong( pLastEntity->template GetNextEntity< T >(), pStack ) == false );
		}

		// Be very careful! This method must be called from one thread only! The case is known as ABA problem.
		T * Pop()
		{
			T * pEntity;
			do {

				pEntity = m_HeadNode;

			} while ( pEntity && m_HeadNode.compare_exchange_strong( pEntity, pEntity->template GetNextEntity< T >() ) == false );

			return pEntity;
		}

		T * PopStack()
		{
			T * pStack;
			do {

				pStack = m_HeadNode;

			} while ( pStack && m_HeadNode.compare_exchange_strong( pStack, NULL ) == false );

			return pStack;
		}

		T * PopReversedStack()
		{ return ReverseStack( PopStack() ); }

		bool IsEmpty() const
		{ return NULL == m_HeadNode; }

	private:

		nstd::atomic< T * > m_HeadNode;

	};

} // namespace nvl

#endif // __LOCK_FREE_STACK_H_INCLUDED__50671__
